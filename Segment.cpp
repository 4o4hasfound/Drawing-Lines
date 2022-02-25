#include "Segment.h"

Segment::Segment(Point point, float angle) {
	angle -= 90.0f;
	angle = glm::radians(angle);
	this->p1 = point;
	this->p2.pos.x = point.pos.x + sqrtf(powf(WIDTH, 2) + powf(HEIGHT, 2)) * cosf(angle);
	this->p2.pos.y = point.pos.y + sqrtf(powf(WIDTH, 2) + powf(HEIGHT, 2)) * sinf(angle);
}

Segment::Segment(Point p1, Point p2) {
	this->p1 = p1;
	this->p2 = p2;
}

void Segment::draw(sf::RenderWindow& window, sf::Color c)
{
	this->p1.draw(window);
	this->p2.draw(window);
	sf::Vertex vertices[] = {
		sf::Vertex(sf::Vector2f(this->p2.pos.x, this->p2.pos.y), c),
		sf::Vertex(sf::Vector2f(this->p1.pos.x, this->p1.pos.y), c)
	};
	window.draw(vertices, 2, sf::Lines);

}

Point Segment::getClosest(Point p) {
	Point toReturn;
	glm::vec2 a_to_p = p.pos - this->p1.pos;
	glm::vec2 a_to_b = this->p2.pos - this->p1.pos;
	float atb2 = powf(a_to_b.x, 2) + powf(a_to_b.y, 2);
	float atp_dot_atb = a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y;
	float  t = atp_dot_atb / atb2;
	return Point(glm::vec2(this->p1.pos.x + a_to_b.x * t, this->p1.pos.y + a_to_b.y * t));
}

Point Segment::Intersect(Segment s) {
	float a = s.p2.pos.y - s.p1.pos.y;
	float b = s.p1.pos.x - s.p2.pos.x;
	float c = s.p2.pos.x * s.p1.pos.y - s.p1.pos.x * s.p2.pos.y;
	float u = fabs(a * this->p1.pos.x + b * this->p1.pos.y + c);
	float v = fabs(a * this->p2.pos.x + b * this->p2.pos.y + c);
	return Point(glm::vec2((this->p1.pos.x * v + this->p2.pos.x * u) / (u + v), (this->p1.pos.y * v + this->p2.pos.y * u) / (u + v)));
}

Point::Point(glm::vec2 p) {
	this->pos = p;
}

void Point::draw(sf::RenderWindow& window, sf::Color c){
	sf::CircleShape toDraw(this->drawRadius);
	toDraw.setPosition(sf::Vector2f(this->pos.x - this->drawRadius, this->pos.y - this->drawRadius));
	toDraw.setFillColor(c);
	window.draw(toDraw);
}

bool Point::PointInCircle(glm::vec2 point) {
	return sqrtf(powf(this->pos.x - point.x, 2) + powf(this->pos.y - point.y, 2)) <= this->drawRadius;
}
