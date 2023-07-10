#include "Segment.h"

Segment::Segment(Point point, float angle) {
	angle = -90 - angle;
	angle = radians(angle);
	this->p1 = point;
	this->p2.pos.x = point.pos.x + sqrtf(powf(WIDTH, 2) + powf(HEIGHT, 2)) * cosf(angle);
	this->p2.pos.y = point.pos.y + sqrtf(powf(WIDTH, 2) + powf(HEIGHT, 2)) * sinf(angle);
}

Segment::Segment(Point p1, Point p2) {
	this->p1 = p1;
	this->p2 = p2;
}

Segment::Segment(Point point, float angle, float length) {
	angle = -90 - angle;
	angle = radians(angle);
	this->p1 = point;
	this->p2.pos.x = point.pos.x + length * cosf(angle);
	this->p2.pos.y = point.pos.y + length * sinf(angle);
} 

void Segment::draw(sf::RenderWindow& window, float width, float radius, sf::Color c)
{
	p1.draw(window, radius, c);
	p2.draw(window, radius, c);

	sf::ConvexShape convex;
	convex.setFillColor(c);
	convex.setPointCount(4);

	sf::Vector2f V(p2.pos.x - p1.pos.x, p2.pos.y - p1.pos.y);
	sf::Vector2f P(V.y, -V.x);

	float Length = sqrtf(P.x * P.x + P.y * P.y);
	sf::Vector2f N(P.x / Length, P.y / Length);
	convex.setPoint(0, sf::Vector2f(p1.pos.x + N.x * width / 2, p1.pos.y + N.y * width / 2));
	convex.setPoint(1, sf::Vector2f(p1.pos.x - N.x * width / 2, p1.pos.y - N.y * width / 2));
	convex.setPoint(2, sf::Vector2f(p2.pos.x - N.x * width / 2, p2.pos.y - N.y * width / 2));
	convex.setPoint(3, sf::Vector2f(p2.pos.x + N.x * width / 2, p2.pos.y + N.y * width / 2));
	window.draw(convex);

}

Point Segment::getClosest(Point p) {
	Point toReturn;
	vec2 a_to_p = p.pos - this->p1.pos;
	vec2 a_to_b = this->p2.pos - this->p1.pos;
	float atb2 = powf(a_to_b.x, 2) + powf(a_to_b.y, 2);
	float atp_dot_atb = a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y;
	float  t = atp_dot_atb / atb2;
	return Point(vec2(this->p1.pos.x + a_to_b.x * t, this->p1.pos.y + a_to_b.y * t));
}

Point Segment::Intersect(Segment s) {
	float a = s.p2.pos.y - s.p1.pos.y;
	float b = s.p1.pos.x - s.p2.pos.x;
	float c = s.p2.pos.x * s.p1.pos.y - s.p1.pos.x * s.p2.pos.y;
	float u = fabs(a * this->p1.pos.x + b * this->p1.pos.y + c);
	float v = fabs(a * this->p2.pos.x + b * this->p2.pos.y + c);
	return Point(vec2((this->p1.pos.x * v + this->p2.pos.x * u) / (u + v), (this->p1.pos.y * v + this->p2.pos.y * u) / (u + v)));
}

float Segment::getAngleWithSegment(Segment s) {
	float dx21 = p2.pos.x - p1.pos.x;
	float dx31 = s.p2.pos.x - p1.pos.x;
	float dy21 = p2.pos.y - p1.pos.y;
	float dy31 = s.p2.pos.y - p1.pos.y;
	float m12 = sqrt(dx21 * dx21 + dy21 * dy21);
	float m13 = sqrt(dx31 * dx31 + dy31 * dy31);
	float theta = acos((dx21 * dx31 + dy21 * dy31) / (m12 * m13));
	return degrees(theta);
}

Point::Point(vec2 p) {
	this->pos = p;
}

void Point::draw(sf::RenderWindow& window, float radius, sf::Color c){
	sf::CircleShape toDraw(radius);
	toDraw.setPosition(sf::Vector2f(this->pos.x - radius, this->pos.y - radius));
	toDraw.setFillColor(c);
	window.draw(toDraw);
}

bool Point::PointInCircle(vec2 point) {
	return sqrtf(powf(this->pos.x - point.x, 2) + powf(this->pos.y - point.y, 2)) <= this->drawRadius;
}
