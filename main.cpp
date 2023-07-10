#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "settings.h"
#include "Segment.h"
#include "Vector.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui-SFML.h"
#define endl "\n"

enum Status {
    PicKStartPoint,
    EnterAngle,
    PickEndPoint,
    ForN,
    FirstDotA,
    FirstDotB,
    SecondDotA,
    SecondDotB,
    ThirdDotA,
    ThirdDotB,
    FourthDotA,
    FourthDotB,
    Check,
    FindPointA,
    FindPointB,
    Finish,
    EnterConvexN,
    CustomFinish,
    Esc,
    GetConvex,
    Custom
};
void getNum(sf::RenderWindow& window, std::vector<bool>& numPressed, std::string& AngleString);

int main1() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PointsInteract!!!!!!!!!!!!!!");
    std::vector<Point> p;
    bool lmb = false;
    bool rmb = false;
    while (window.isOpen()) {
        sf::Event event;
        sf::Texture t;
        if (!t.loadFromFile("RainMap2.png")) {
            std::cout << "fail to load image!\n";
        }   
        sf::Sprite s(t);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.draw(s);
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!lmb) {
                p.push_back(Point(vec2(pos.x, pos.y)));
                std::cout << p.size() << endl;
                lmb = true;
            }
        }
        else {
            lmb = false;
        }
        for (Point& point : p) {
            point.draw(window, 8.0f, sf::Color::White);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            float Angle = 0;
            int size = p.size();
            for (int i = 0; i < size; i++) {
                float angle = Segment(p[i], p[((i + 1 < size) ? i + 1 : size - 1 - i)]).getAngleWithSegment(Segment(p[((i + 1 < size) ? i + 1 : size - 1 - i)], p[((i + 2 < size) ? i + 2 : size - i)]));
                int LeftAll = -1, out = false;
                for (int j = 0; j < size; j++) {
                    if (j == i) continue;
                    int nextPoint;
                    if (j == i - 1) {
                        nextPoint = j + 2;
                    }
                    if (j + 1 >= size) {
                        nextPoint = size - 1 - j;
                    }
                    else {
                        nextPoint = j;
                    }
                    bool left = ((p[nextPoint].pos.x - p[j].pos.x) * (p[i].pos.y - p[j].pos.y) - (p[nextPoint].pos.y - p[j].pos.y) * (p[i].pos.x - p[j].pos.x)) > 0;
                    if (LeftAll >= 0 && left != LeftAll) {
                        out = true;
                        break;
                    }
                    LeftAll = left;
                }
                if (out) Angle += std::min(angle, 360 - angle);
                else Angle += std::max(angle, 360 - angle);
                std::cout << angle;
            }
            std::cout << "Angle: " << Angle << "\n";
        }
        window.display();

    }
    return 0;
}

int main() {
    //std::ifstream in("in1.txt");
    //std::streambuf* cinbuf = std::cin.rdbuf(); //save old buf
    //std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    int n = 4;
    int currentI = 0;
    int AB = 0;
    Status status = PicKStartPoint;
    Status last;
    Point StartPos, EndPos;
    Segment StartPoint, EndPoint;
    vec2 offset(0.0f);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PointsInteract!!!!!!!!!!!!!!");
    ImGui::SFML::Init(window);
    bool leftPressed = false;
    std::vector<bool> numPressed(11);
    std::vector<Segment> First(2);
    std::vector<Segment> Second(2);
    std::vector<Segment> Third(2);
    std::vector<Segment> Fourth(2);
    Point p1, p2, p3, p4;
    std::string convexPointCount = "";
    int convexPointCountIl;
    std::vector<sf::ConvexShape> convexs;
    std::vector<Segment> lines;
    std::vector<Segment> convexLine;
    std::vector<Point> convexPoints;
    int currentConvexLine = 0;
    std::vector<Point> p(n);
    std::vector<Segment> s(n);
    std::vector<Segment[2]> Line(n);
    Segment line1, line2, line3, line4;
    Point CurrentPointA;
    Point CurrentPointB;
    std::vector<Point> points;
    int line = 0;
    bool bsPressed = false;
    bool enterPressed = false;
    bool spacePressed = false;
    bool delPressed = false;
    bool move = false;
    bool escPressed = false;
    float lineWidth = 1.0f;
    float circleRadius = 8.0f;
    bool showLine = true;
    float TableColor[3] = { 200.0f / 255.0f, 40.0f / 255.0f, 40.0f / 255.0f };
    float lineColor[3] = { 0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f };
    float bgColor[3] = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };
    sf::Vector2f oldPos;
    sf::View view = window.getDefaultView();
    std::string AngleString = "";
    std::string showString = "";
    sf::Font font;
    sf::Texture lastFrame;
    sf::RectangleShape lastFrameRect;
    lastFrameRect.setSize(sf::Vector2f(WIDTH, HEIGHT));
    sf::Clock deltaClock;
    if (!font.loadFromFile("consola.ttf")) {
        std::wcout << "Error load font!\n";
    }
    std::vector<sf::Text> nums(n);
    for (int i = 0; i < n; i++) {
        nums[i] = sf::Text();
        nums[i].setString(std::to_string(i));
        nums[i].setCharacterSize(20);
        nums[i].setFillColor(sf::Color::White);
        nums[i].setFont(font);
    }
    sf::Text text;
    text.setCharacterSize(20);
    text.setFont(font);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (status == Finish) {
                switch (event.type) {
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        move = true;
                        oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        move = false;
                    }
                    break;
                case sf::Event::MouseMoved:
                    if (!move) break;
                    const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    sf::Vector2f deltaPos = oldPos - newPos;
                    view.move(deltaPos);
                    window.setView(view);

                    oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                    break;
                }
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear(sf::Color(bgColor[0] * 255, bgColor[1] * 255, bgColor[2] * 255));
        switch (status) {
        case PicKStartPoint:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    StartPos = Point(vec2(pos.x, pos.y));
                    leftPressed = true;
                    status = EnterAngle;
                }
            }
            else {
                leftPressed = false;
            }
        }
            break;
        case EnterAngle:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        StartPoint = Segment(StartPos, std::stof(AngleString));
                        status = PickEndPoint;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setFillColor(sf::Color::Black);
            text.setString(showString);
            window.draw(text);
            StartPos.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
            break;
        case PickEndPoint:
        {
            StartPoint.draw(window, lineWidth);
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            Point p = StartPoint.getClosest(Point(vec2(pos.x, pos.y)));
            p.draw(window, circleRadius);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    StartPoint = Segment(StartPos, p);
                    leftPressed = true;
                    AngleString.clear();
                    showString.clear();
                    bsPressed = false;
                    status = ForN;
                }
            }
            else {
                leftPressed = false;
            }
        }
            break;
        case ForN:
        {
            switch (AB) {
            case 0:
            {
                getNum(window, numPressed, AngleString);
                showString = AngleString;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                    if (!delPressed) {
                        delPressed = true;
                        if (currentI - 1 >= 0) {
                            currentI--;
                            AB = 1;
                        }
                    }
                }
                else {
                    delPressed = false;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (!enterPressed) {
                        enterPressed = true;
                        if (AngleString.empty()) {
                            showString = "Error!!!!";
                        }
                        else {
                            std::cout << std::stof(AngleString) << endl;
                            Line[currentI][0] = (Segment(StartPoint.p1, std::stof(AngleString)));
                            AngleString.clear();
                            showString.clear();
                            AB = 1;
                        }
                    }
                }
                else {
                    enterPressed = false;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                    if (!bsPressed && !AngleString.empty()) {
                        AngleString.pop_back();
                        bsPressed = true;
                    }
                }
                else {
                    bsPressed = false;
                }
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                text.setPosition(pos.x + 20, pos.y);
                text.setFillColor(sf::Color::Black);
                text.setString(showString);
                window.draw(text);
                StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                for (int t = 0; t < currentI - 1; t++) {
                    p[t].draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                }
                if (currentI - 1 >= 0) {
                    Line[currentI - 1][0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                    Line[currentI - 1][1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                }
                for (int t = 0; t < currentI - 1; t++) {
                    nums[t].setPosition(sf::Vector2f(p[t].pos.x, p[t].pos.y));
                    window.draw(nums[t]);
                }
            }
            break;
            case 1:
            {
                getNum(window, numPressed, AngleString);
                showString = AngleString;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                    if (!delPressed) {
                        delPressed = true;
                        AB = 0;
                        if (currentI - 1 >= 0)
                            currentI--;
                    }
                }
                else {
                    delPressed = false;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (!enterPressed) {
                        enterPressed = true;
                        if (AngleString.empty()) {
                            showString = "Error!!!!";
                        }
                        else {
                            std::cout << std::stof(AngleString) << endl;
                            Segment s(StartPoint.p2, std::stof(AngleString));
                            p[currentI] = Line[currentI][0].Intersect(s);
                            Line[currentI][0] = Segment(StartPoint.p1, p[currentI]);
                            Line[currentI][1] = Segment(StartPoint.p2, p[currentI]);
                            AngleString.clear();
                            showString.clear();
                            if (currentI >= n - 1) {
                                //status = GetConvex;
                                status = GetConvex;
                            }
                            else {

                                currentI++;
                            }
                            AB = 0;
                        }
                    }
                }
                else {
                    enterPressed = false;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                    if (!bsPressed && !AngleString.empty()) {
                        AngleString.pop_back();
                        bsPressed = true;
                    }
                }
                else {
                    bsPressed = false;
                }
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                text.setPosition(pos.x + 20, pos.y);
                text.setString(showString);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
                StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                for (int t = 0; t < currentI; t++) {
                    p[t].draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                }
                Line[currentI][0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                for (int t = 0; t < currentI; t++) {
                    nums[t].setPosition(sf::Vector2f(p[t].pos.x, p[t].pos.y));
                    window.draw(nums[t]);
                }
            }
            break;
            }
        }
            break;
        case EnterConvexN:
        {
            getNum(window, numPressed, convexPointCount);
            showString = convexPointCount;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (convexPointCount.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        convexPointCountIl = std::stoi(convexPointCount);
                        std::cout << convexPointCountIl << endl;
                        showString.clear();
                        convexLine.resize(convexPointCountIl);
                        convexPoints.resize(convexPointCountIl);
                        status = FindPointA;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !convexPointCount.empty()) {
                    convexPointCount.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            for (int t = 0; t <= currentI; t++) {
                p[t].draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setString(showString);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
        }
        break;
        case GetConvex:
        {
            int l=0, c=1;
            //std::cin >> l >> c;
            std::vector<int> lineIndex(2 * l);
            std::vector<std::vector<int> > convexIndex(c);
            for (int i = 0; i + 1 < 2 * l; i+=2) {
                int index1, index2;
                std::cin >> index1 >> index2;
                lineIndex[i] = index1;
                lineIndex[i + 1] = index2;
            }
            for (int i = 0; i < c; i++) {
                int convexPointsCount=n;
                //std::cin >> convexPointsCount;
                for (int r = 0; r < convexPointsCount; r++) {
                    int index = r;
                    //std::cin >> index;
                    convexIndex[i].push_back(index);
                }

            }
            for (int i = 0; i + 1 < 2 * l; i+=2) {
                lines.push_back(Segment(p[lineIndex[i]], p[lineIndex[i + 1]]));
                std::cout << lineIndex[i] << " " << lineIndex[i + 1] << endl;

            }
            convexs.resize(c);
            for (int i = 0; i < c; i++) {
                int size = convexIndex[i].size();
                convexs[i] = sf::ConvexShape(size);
                convexs[i].setFillColor(sf::Color(TableColor[0] * 255, TableColor[1] * 255, TableColor[2] * 255));
                for (int r = 0; r < size; r++) {
                    convexs[i].setPoint(r, sf::Vector2f(p[convexIndex[i][r]].pos.x, p[convexIndex[i][r]].pos.y));
                }
            }
            status = CustomFinish;
        }
            break;
        case CustomFinish:
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    AB = 1;
                    if (currentI - 1 >= 0)
                        currentI--;
                }
            }
            else {
                delPressed = false;
            }
            /*sf::ConvexShape convex;
            convex.setFillColor(sf::Color(TableColor[0] * 255, TableColor[1] * 255, TableColor[2] * 255));
            convex.setPointCount(convexPointCountIl);

            for (int i = 0; i < convexPointCountIl; i++) {
                convex.setPoint(i, sf::Vector2f(convexPoints[i].pos.x, convexPoints[i].pos.y));
            }*/
            for (int i = 0, len = convexs.size(); i < len; i++) {
                convexs[i].setFillColor(sf::Color(TableColor[0] * 255, TableColor[1] * 255, TableColor[2] * 255));
                window.draw(convexs[i]);
            }
            for (int i = 0, len = lines.size(); i < len; i++) {
                lines[i].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            }
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));

            for (int i = 0; i < n; i++) {
                p[i].draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            }
            for (int i = 0; i < n; i++) {
                sf::Text t;
                t.setFont(font);
                t.setCharacterSize(20);
                t.setString(std::to_string(i));
                t.setFillColor(sf::Color::Blue);
                t.setPosition(p[i].pos.x, p[i].pos.y);
                window.draw(t);
            }
            if (showLine) {
                for (int i = 0; i < n; i++) {
                    Line[i][0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                    Line[i][1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!spacePressed) {
                    spacePressed = true;
                    sf::Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    std::string fileName;
                    //std::cout << "fileName: ";
                    //std::cin >> fileName;
                    //if (texture.copyToImage().saveToFile(fileName + ".png")) {
                    //    std::cout << "Save to file: " + fileName + ".png" + "!\n";
                    //}
                    float Angle = 0;
                    for (int i = 0; i < 21; i++) {
                        float angle = Segment(p[i], p[((i + 1 < 21) ? i + 1 : 20 - i)]).getAngleWithSegment(Segment(p[((i + 1 < 21) ? i + 1 : 20 - i)], p[((i + 2 < 21) ? i + 2 : 21 - i)]));
                        int LeftAll=-1,out=false;
                        for (int j = 0; j < 21; j++) {
                            if (j == i) continue;
                            int nextPoint;
                            if (j == i - 1) {
                                nextPoint = j + 2;
                            }
                            if (j + 1 >= 21) {
                                nextPoint = 20 - j;
                            }
                            else {
                                nextPoint = j;
                            }
                            bool left=((p[nextPoint].pos.x - p[j].pos.x)* (p[i].pos.y - p[j].pos.y) - (p[nextPoint].pos.y - p[j].pos.y) * (p[i].pos.x - p[j].pos.x)) > 0;
                            if (LeftAll>=0&&left != LeftAll) {
                                out = true;
                                break;
                            }
                            LeftAll = left;
                        }
                        if (out) Angle += (angle < 180 ? angle : 360 - angle);
                        else Angle += (angle > 180 ? angle : 360 - angle);
                        std::cout << angle;
                    }
                    std::cout << "Angle: " << Angle << "\n";
                    std::string out = fileName + ": " + std::to_string(Angle) + "\n";
                    std::ofstream file("Angle.txt", std::ofstream::out | std::ofstream::app);
                    file << out;
                    file.close();
                }
            }
            else {
                spacePressed = false;
            }

        }
            break;
        case FirstDotA:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        First[0] = (Segment(StartPoint.p2, std::stof(AngleString)));
                        AngleString.clear();
                        showString.clear();
                        status = FirstDotB;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setFillColor(sf::Color::Black);
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
            break;
        case FirstDotB:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    status = FirstDotA;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        Segment s(StartPoint.p1, std::stof(AngleString));
                        p1 = First[0].Intersect(s);
                        First[0] = Segment(StartPoint.p1, p1);
                        First[1] = Segment(StartPoint.p2, p1);
                        AngleString.clear();
                        showString.clear();
                        status = SecondDotA;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setString(showString);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            First[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case SecondDotA:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    status = FirstDotB;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        Second[0] = (Segment(StartPoint.p2, std::stof(AngleString)));
                        AngleString.clear();
                        showString.clear();
                        status = SecondDotB;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setFillColor(sf::Color::Black);
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            First[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            First[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case SecondDotB:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    status = SecondDotA;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        Segment s(StartPoint.p1, std::stof(AngleString));
                        p2 = Second[0].Intersect(s);
                        Second[0] = Segment(StartPoint.p1, p2);
                        Second[1] = Segment(StartPoint.p2, p2);
                        AngleString.clear();
                        showString.clear();
                        status = ThirdDotA;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setFillColor(sf::Color::Black);
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p1.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Second[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case ThirdDotA:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    status = SecondDotB;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        Third[0] = (Segment(StartPoint.p2, std::stof(AngleString)));
                        AngleString.clear();
                        showString.clear();
                        status = ThirdDotB;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setFillColor(sf::Color::Black);
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window, lineWidth);
            p1.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Second[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Second[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case ThirdDotB:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    status = ThirdDotA;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        Segment s(StartPoint.p1, std::stof(AngleString));
                        p3 = Third[0].Intersect(s);
                        Third[0] = Segment(StartPoint.p1, p3);
                        Third[1] = Segment(StartPoint.p2, p3);
                        AngleString.clear();
                        showString.clear();
                        status = FourthDotA;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setFillColor(sf::Color::Black);
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p1.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p2.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Third[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case FourthDotA:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed - true;
                    status = ThirdDotB;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        Fourth[0] = (Segment(StartPoint.p2, std::stof(AngleString)));
                        AngleString.clear();
                        showString.clear();
                        status = FourthDotB;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setString(showString);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p1.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p2.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Third[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Third[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case FourthDotB:
        {
            getNum(window, numPressed, AngleString);
            showString = AngleString;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    status = FourthDotA;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    if (AngleString.empty()) {
                        showString = "Error!!!!";
                    }
                    else {
                        std::cout << std::stof(AngleString) << endl;
                        Segment s(StartPoint.p1, std::stof(AngleString));
                        p4 = Fourth[0].Intersect(s);
                        Fourth[0] = Segment(StartPoint.p1, p4);
                        Fourth[1] = Segment(StartPoint.p2, p4);
                        AngleString.clear();
                        showString.clear();
                        status = Check;
                    }
                }
            }
            else {
                enterPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                if (!bsPressed && !AngleString.empty()) {
                    AngleString.pop_back();
                    bsPressed = true;
                }
            }
            else {
                bsPressed = false;
            }
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            text.setPosition(pos.x + 20, pos.y);
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p1.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p2.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p3.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Fourth[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case Check:
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (!delPressed) {
                    delPressed = true;
                    status = FourthDotA;
                }
            }
            else {
                delPressed = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (!enterPressed) {
                    enterPressed = true;
                    status = Finish;
                }
            }
            else {
                enterPressed = false;
            }
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p1.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p2.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p3.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Fourth[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            Fourth[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        }
        break;
        case FindPointA:
        {
            int ind = -1;
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            for (int i = 0; i < n; i++) {
                if (p[i].PointInCircle(vec2(pos.x, pos.y))) {
                    ind = i;
                    break;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    leftPressed = true;
                    if (ind >= 0) {
                        CurrentPointA = p[ind];
                        convexPoints[currentConvexLine] = CurrentPointA;
                        status = FindPointB;
                    }
                }
            }
            else {
                leftPressed = false;
            }
            StartPoint.draw(window, lineWidth);
            for (int i = 0; i < currentConvexLine; i++) {
                convexLine[i].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            }
            for (int i = 0; i < n; i++) {
                if (i == ind) {
                    p[i].draw(window, circleRadius, sf::Color::Red);
                }
                else {
                    p[i].draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                }
                nums[i].setPosition(sf::Vector2f(p[i].pos.x, p[i].pos.y));
                window.draw(nums[i]);
            }
        }
        break;
        case FindPointB:
        {
            int ind = -1;
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            for (int i = 0; i < n; i++) {
                if (p[i].PointInCircle(vec2(pos.x, pos.y))) {
                    ind = i;
                    break;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    leftPressed = true;
                    if (ind >= 0) {
                        CurrentPointB = p[ind];
                        convexLine[currentConvexLine] = Segment(CurrentPointA, CurrentPointB);
                        currentConvexLine++;
                        if (currentConvexLine >= convexPointCountIl) {
                            status = CustomFinish;
                        }
                        else {
                            status = FindPointA;
                        }
                    }
                }
            }
            else {
                leftPressed = false;
            }
            StartPoint.draw(window, lineWidth);
            for (int i = 0; i < currentConvexLine; i++) {
                convexLine[i].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            }
            for (int i = 0; i < currentConvexLine; i++) {
                convexLine[i].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            }
            for (int i = 0; i < n; i++) {
                if (i == ind) {
                    p[i].draw(window, circleRadius, sf::Color::Red);
                }
                else {
                    p[i].draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                }
                nums[i].setPosition(sf::Vector2f(p[i].pos.x, p[i].pos.y));
                window.draw(nums[i]);
            }

            sf::Vertex vertices[] = {
                sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::Black),
                sf::Vertex(sf::Vector2f(CurrentPointA.pos.x, CurrentPointA.pos.y), sf::Color::Black)
            };
            window.draw(vertices, 2, sf::Lines);
        }
            break;
        case Finish:
        {
            sf::ConvexShape convex;
            convex.setFillColor(sf::Color(TableColor[0] * 255, TableColor[1] * 255, TableColor[2] * 255));
            convex.setPointCount(4);

            convex.setPoint(0, sf::Vector2f(p1.pos.x, p1.pos.y));
            convex.setPoint(1, sf::Vector2f(p2.pos.x, p2.pos.y));
            convex.setPoint(2, sf::Vector2f(p3.pos.x, p3.pos.y));
            convex.setPoint(3, sf::Vector2f(p4.pos.x, p4.pos.y));

            window.draw(convex);
            StartPoint.draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));

            p1.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p2.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p3.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            p4.draw(window, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            if (showLine) {
                First[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                First[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                Second[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                Second[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                Third[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                Third[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                Fourth[0].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
                Fourth[1].draw(window, lineWidth, circleRadius, sf::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!spacePressed) {
                    spacePressed = true;
                    sf::Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    std::string fileName;
                    std::cout << "fileName: ";
                    std::cin >> fileName;
                    if (texture.copyToImage().saveToFile(fileName +".png")) {
                        //float p1Angle = Segment(p1, p2).getAngleWithSegment(Segment(p1, p4));
                        //float p2Angle = Segment(p2, p3).getAngleWithSegment(Segment(p2, p1));
                        //float p3Angle = Segment(p3, p4).getAngleWithSegment(Segment(p3, p2));
                        //float p4Angle = Segment(p4, p1).getAngleWithSegment(Segment(p4, p3));
                        //float average = (abs(p1Angle - 90) + abs(p2Angle - 90) + abs(p3Angle - 90) + abs(p4Angle - 90)) / 4;
                        //std::cout << "Averagve angle error: " << average << "\n";
                        //std::string out = fileName + ": " + std::to_string(average) + "\n";
                        //std::ofstream file("AngleError.txt", std::ofstream::out | std::ofstream::app);
                        //file << out;
                        //file.close();
                        std::cout << "Save to file: " + fileName + ".png" + "!\n";
                        status = Custom;
                    }
                }
            }
            else {
                spacePressed = false;
            }
        }
        break;
        case Esc:
        {
            window.draw(lastFrameRect);
            ImGui::Begin("Settings");
            ImGui::ColorEdit3("Background Color", bgColor);
            ImGui::SliderFloat("Line Width", &lineWidth, 1.0f, 10.0f);
            ImGui::SliderFloat("Point Radius", &circleRadius, 1.0f, 20.0f);
            ImGui::Checkbox("Show Line", &showLine);
            ImGui::ColorEdit3("Line Color", lineColor);
            ImGui::ColorEdit3("Table Color", TableColor);
            ImGui::End();
        }
        break;
        case Custom:
        {
            StartPoint = Segment(Point(vec2(450, 750)), 80.0f, 175.0f);
            status = ForN;
        }
        break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (!escPressed) {
                escPressed = true;
                if (status != Esc) {
                    last = status;
                    lastFrame.create(window.getSize().x, window.getSize().y);
                    lastFrame.update(window);
                    lastFrameRect.setTexture(&lastFrame);
                    status = Esc;
                }
                else {
                    status = last;
                }
            }
        }
        else {
            escPressed = false;
        }
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

void getNum(sf::RenderWindow& window, std::vector<bool>& numPressed, std::string& AngleString) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
        if (!numPressed[0]) {
            AngleString.push_back('1');
            numPressed[0] = true;
        }
    }
    else {
        numPressed[0] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
        if (!numPressed[1]) {
            AngleString.push_back('2');
            numPressed[1] = true;
        }
    }
    else {
        numPressed[1] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
        if (!numPressed[2]) {
            AngleString.push_back('3');
            numPressed[2] = true;
        }
    }
    else {
        numPressed[2] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) {
        if (!numPressed[3]) {
            AngleString.push_back('4');
            numPressed[3] = true;
        }
    }
    else {
        numPressed[3] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
        if (!numPressed[4]) {
            AngleString.push_back('5');
            numPressed[4] = true;
        }
    }
    else {
        numPressed[4] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) {
        if (!numPressed[5]) {
            AngleString.push_back('6');
            numPressed[5] = true;
        }
    }
    else {
        numPressed[5] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7)) {
        if (!numPressed[6]) {
            AngleString.push_back('7');
            numPressed[6] = true;
        }
    }
    else {
        numPressed[6] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) {
        if (!numPressed[7]) {
            AngleString.push_back('8');
            numPressed[7] = true;
        }
    }
    else {
        numPressed[7] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) {
        if (!numPressed[8]) {
            AngleString.push_back('9');
            numPressed[8] = true;
        }
    }
    else {
        numPressed[8] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
        if (!numPressed[9]) {
            AngleString.push_back('0');
            numPressed[9] = true;
        }
    }
    else {
        numPressed[9] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash) || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
        if (!numPressed[10]) {
            if (AngleString[0] == '-') {
                AngleString.erase(AngleString.begin());
            }
            else {
                AngleString.insert(AngleString.begin(), '-');
            }
            numPressed[10] = true;
        }
    }
    else {
        numPressed[10] = false;
    }
}