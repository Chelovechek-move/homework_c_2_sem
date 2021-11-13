#include <iostream>
#include "point.h"
#include "circle.h"
#include <cmath>

using namespace std;

Circle::Circle(const Point& acenter, float aradius)
	{
		center = acenter;
		radius = aradius;
	}

Circle::Circle()
{
	center = {0, 0};
	radius = 0;
}

Circle::Circle(const Circle& circle)
{
	center = circle.center;
	radius = circle.radius;
}

Point Circle::get_center() const
{
	return center;
}

float Circle::get_radius() const
{
	return radius;
}

void Circle::set_center(Point center)
{
	this->center = center;
}

void Circle::set_radius(float radius)
{
	this->radius = radius;
}

float Circle::get_area() const
{
	float PI = 3.14;
	float s = PI * radius * radius;
	return s; 
}

float Circle::get_distance(const Point& p) const
{
	float l = sqrt((center.get_x() - p.get_x())* (center.get_x() - p.get_x()) + (center.get_y() - p.get_y()) * (center.get_y() - p.get_y()));
	float distance = l - radius;
	return distance;
}

bool Circle::is_colliding(const Circle& c) const
{
	float l = sqrt((center.get_x() - c.get_center().get_x()) * (center.get_x() - c.get_center().get_x()) + (center.get_y() - c.get_center().get_y()) * (center.get_y() - c.get_center().get_y()));
	if(l <= radius + c.get_radius())
		return true;
	else
		return false;
}

void Circle::move(const Point& p)
{
	center.set_x(p.get_x());
	center.set_y(p.get_y());
}