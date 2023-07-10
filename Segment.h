#pragma once
#ifndef _SEGMENT_H_
#define _SEGMENT_H_
#define Radius 8

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Vector.h"
#include "utility.h"
#include "settings.h"

class Point {
public:
	Point() = default;
	Point(vec2 p);
	vec2 pos;
	float drawRadius = Radius;
	void draw(sf::RenderWindow& window, float radius = 8.0f, sf::Color c = sf::Color::Black);
	bool PointInCircle(vec2 point);
};

class Segment {
public:
	Segment() = default;
	Segment(Point point, float angle);
	Segment(Point point, float angle, float length);
	Segment(Point p1, Point p2);
	Point p1, p2;
	void draw(sf::RenderWindow &window, float width = 1.0f, float radius = 8.0f, sf::Color c = sf::Color::Black);
	Point getClosest(Point p);
	Point Intersect(Segment s);
	float getAngleWithSegment(Segment s);

};


#endif
