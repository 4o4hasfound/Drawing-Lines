#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "settings.h"
#include "Segment.h"

#define endl "\n"

enum Status {
    PicKStartPoint,
    EnterAngle,
    PickEndPoint,
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
    Finish
};
void getNum(sf::RenderWindow& window, std::vector<bool> &numPressed, std::string &AngleString) {
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
}

int main() {
    Status status = PicKStartPoint;
    Point StartPos, EndPos;
    Segment StartPoint, EndPoint;
    glm::vec2 offset(0.0f);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PointsInteract!!!!!!!!!!!!!!");
    bool leftPressed = false;
    std::vector<bool> numPressed(10);
    std::vector<Segment> First(2);
    std::vector<Segment> Second(2);
    std::vector<Segment> Third(2);
    std::vector<Segment> Fourth(2);
    Point p1, p2, p3, p4;
    Segment line1, line2, line3, line4;
    Point CurrentPointA;
    Point CurrentPointB;
    std::vector<Point> points;
    int line = 1;
    bool bsPressed = false;
    bool enterPressed = false;
    bool spacePressed = false;
    bool delPressed = false;
    bool move = false;
    sf::Vector2f oldPos;
    sf::View view = window.getDefaultView();
    std::string AngleString = "";
    std::string showString = "";
    sf::Font font;
    if (!font.loadFromFile("consola.ttf")) {
        std::wcout << "Error load font!\n";
    }
    sf::Text text;
    text.setCharacterSize(20);
    text.setFont(font);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
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

        window.clear();
        switch (status) {
        case PicKStartPoint:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    StartPos = Point(glm::vec2(pos.x, pos.y));
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
            text.setString(showString);
            window.draw(text);
            StartPos.draw(window);
        }
            break;
        case PickEndPoint:
        {
            StartPoint.draw(window);
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            Point p = StartPoint.getClosest(Point(glm::vec2(pos.x, pos.y)));
            p.draw(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    StartPoint = Segment(StartPos, p);
                    leftPressed = true;
                    AngleString.clear();
                    showString.clear();
                    bsPressed = false;
                    status = FirstDotA;
                }
            }
            else {
                leftPressed = false;
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
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window);
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
            window.draw(text);
            StartPoint.draw(window);
            First[0].draw(window, sf::Color::Red);
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
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window);
            First[0].draw(window, sf::Color::Red);
            First[1].draw(window, sf::Color::Red);
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
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window);
            p1.draw(window, sf::Color::Red);
            Second[0].draw(window, sf::Color::Green);
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
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window);
            p1.draw(window, sf::Color::Red);
            Second[0].draw(window, sf::Color::Green);
            Second[1].draw(window, sf::Color::Green);
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
            text.setString(showString);
            window.draw(text);
            StartPoint.draw(window);
            p1.draw(window, sf::Color::Red);
            p2.draw(window, sf::Color::Green);
            Third[0].draw(window, sf::Color::Blue);
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
            window.draw(text);
            StartPoint.draw(window);
            p1.draw(window, sf::Color::Red);
            p2.draw(window, sf::Color::Green);
            Third[0].draw(window, sf::Color::Blue);
            Third[1].draw(window, sf::Color::Blue);
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
            StartPoint.draw(window);
            p1.draw(window, sf::Color::Red);
            p2.draw(window, sf::Color::Green);
            p3.draw(window, sf::Color::Blue);
            Fourth[0].draw(window, sf::Color::Yellow);
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
                    status = FindPointA;
                }
            }
            else {
                enterPressed = false;
            }
            StartPoint.draw(window);
            p1.draw(window, sf::Color::Red);
            p2.draw(window, sf::Color::Green);
            p3.draw(window, sf::Color::Blue);
            Fourth[0].draw(window, sf::Color::Yellow);
            Fourth[1].draw(window, sf::Color::Yellow);
        }
        break;
        case FindPointA:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    leftPressed = true;
                    bool find = false;
                    if (p1.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointA = p1; find = true; points.push_back(p1); }
                    if (p2.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointA = p2; find = true; points.push_back(p2); }
                    if (p3.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointA = p3; find = true; points.push_back(p3); }
                    if (p4.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointA = p4; find = true; points.push_back(p4); }
                    if (find) {
                        status = FindPointB;
                    }
                }
            }
            else {
                leftPressed = false;
            }
            StartPoint.draw(window);
            p1.draw(window);
            p2.draw(window);
            p3.draw(window);
            p4.draw(window);
            line1.draw(window);
            line2.draw(window);
            line3.draw(window);
            line4.draw(window);
        }
        break;
        case FindPointB:
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!leftPressed) {
                    leftPressed = true;
                    bool find = false;
                    if (p1.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointB = p1; find = true; }
                    if (p2.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointB = p2; find = true; }
                    if (p3.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointB = p3; find = true; }
                    if (p4.PointInCircle(glm::vec2(pos.x, pos.y))) { CurrentPointB = p4; find = true; }
                    if (find) {
                        switch (line) {
                        case 1:
                            line1 = Segment(CurrentPointA, CurrentPointB);
                            line++;
                            status = FindPointA;
                            break;
                        case 2:
                            line2 = Segment(CurrentPointA, CurrentPointB);
                            line++;
                            status = FindPointA;
                            break;
                        case 3:
                            line3 = Segment(CurrentPointA, CurrentPointB);
                            line++;
                            status = FindPointA;
                            break;
                        case 4:
                            line4 = Segment(CurrentPointA, CurrentPointB);
                            status = Finish;
                            break;
                        }
                    }
                }
            }
            else {
                leftPressed = false;
            }
            sf::Vertex vertices[] = {
                sf::Vertex(sf::Vector2f(pos.x, pos.y)),
                sf::Vertex(sf::Vector2f(CurrentPointA.pos.x, CurrentPointA.pos.y))
            };
            window.draw(vertices, 2, sf::Lines);
            StartPoint.draw(window);
            line1.draw(window);
            line2.draw(window);
            line3.draw(window);
            line4.draw(window);
            p1.draw(window, sf::Color::Red);
            p2.draw(window, sf::Color::Green);
            p3.draw(window, sf::Color::Blue);
            p4.draw(window, sf::Color::Yellow);
        }
            break;
        case Finish:
            const int& x = 0;
            sf::ConvexShape convex;

            convex.setPointCount(4);

            convex.setPoint(0, sf::Vector2f(points[0].pos.x, points[0].pos.y));
            convex.setPoint(1, sf::Vector2f(points[1].pos.x, points[1].pos.y));
            convex.setPoint(2, sf::Vector2f(points[2].pos.x, points[2].pos.y));
            convex.setPoint(3, sf::Vector2f(points[3].pos.x, points[3].pos.y));

            window.draw(convex);
            StartPoint.draw(window);

            p1.draw(window, sf::Color::Red);
            p2.draw(window, sf::Color::Green);
            p3.draw(window, sf::Color::Blue);
            p4.draw(window, sf::Color::Yellow);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!spacePressed) {
                    spacePressed = true;
                    sf::Texture texture;
                    texture.create(window.getSize().x, window.getSize().y);
                    texture.update(window);
                    if (texture.copyToImage().saveToFile("Image.png")) {
                        std::cout << "Save to file: Image.png!\n";
                    }
                }
            }
            else {
                spacePressed = false;
            }
        }
        window.display();
    }

    return 0;
}