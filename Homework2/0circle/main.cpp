#include <iostream>
#include "point.h"
#include <cmath>

using namespace std;

class Circle
{
private:
	Point center;
	float radius;

public:
	Circle(const Point& acenter, float aradius)
	{
		center = acenter;
		radius = aradius;
	}

	Circle()
	{
		center = {0, 0};
		radius = 0;
	}

	Circle(const Circle& circle)
	{
		center = circle.center;
		radius = circle.radius;
	}

	Point get_center() const
	{
		return center;
	}

	float get_radius() const
	{
		return radius;
	}

	void set_center(Point center)
	{
		this->center = center;
	}

	void set_radius(float radius)
	{
		this->radius = radius;
	}

	float get_area() const
	{
		float PI = 3.14;
		float s = PI * radius * radius;
		return s; 
	}

	float get_distance(const Point& p) const
	{
		float l = sqrt((center.get_x() - p.get_x())* (center.get_x() - p.get_x()) + (center.get_y() - p.get_y()) * (center.get_y() - p.get_y()));
		float distance = l - radius;
		return distance;
	}

	bool is_colliding(const Circle& c) const
	{
		float l = sqrt((center.get_x() - c.get_center().get_x()) * (center.get_x() - c.get_center().get_x()) + (center.get_y() - c.get_center().get_y()) * (center.get_y() - c.get_center().get_y()));
		if(l <= radius + c.get_radius())
			return true;
		else
			return false;
	}

	void move(const Point& p)
	{
		center.set_x(p.get_x());
		center.set_y(p.get_y());
	}
};

int main()
{
	
	Point p = {7, -1};
	Point q = {4, -2};
	cout << "Point p = " << p << endl;
	cout << "Point q = " << q << endl;
	cout << "p + q = " << p + q << endl;
	

	Circle a {{4, 1}, 3};
	Circle b;

	cout << "Circle a: center: " << a.get_center() << " radius: " << a.get_radius() << endl; 
	cout << "Circle b: center: " << b.get_center() << " radius: " << b.get_radius() << endl;

	cout << "Area of a = " << a.get_area() << endl;
	cout << "Distance from point p to circle a = " << a.get_distance(p) << endl;



	cout << "Collisions:" << endl;
	if (a.is_colliding(b))
		cout << "Yes, a is colliding b" << endl;
	else
		cout << "No, a isn't colliding b" << endl;



	cout << "Moving b by {1, 1}:" << endl;
	b.move({1, 1});
	if (a.is_colliding(b))
		cout << "Yes, a is colliding b" << endl;
	else
		cout << "No, a isn't colliding b" << endl;



}