#pragma once
#ifndef _SEGMENT_H_
#define _SEGMENT_H_
#define Radius 10

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <math.h>
#include <iostream>
#include "settings.h"

class Point {
public:
	Point() = default;
	Point(glm::vec2 p);
	glm::vec2 pos;
	float drawRadius = Radius;
	void draw(sf::RenderWindow& window, sf::Color c = sf::Color::White);
	bool PointInCircle(glm::vec2 point);
};

class Segment {
public:
	Segment() = default;
	Segment(Point point, float angle);
	Segment(Point p1, Point p2);
	Point p1, p2;
	void draw(sf::RenderWindow &window, sf::Color c = sf::Color::White);
	Point getClosest(Point p);
	Point Intersect(Segment s);

};


#endif