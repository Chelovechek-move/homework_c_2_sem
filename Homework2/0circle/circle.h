#pragma once

class Circle
{
private:
	Point center;
	float radius;

public:
	Circle(const Point& acenter, float aradius);
	Circle();
	Circle(const Circle& circle);

	Point get_center() const;
	float get_radius() const;
	void set_center(Point center);
	void set_radius(float radius);
	float get_area() const;
	float get_distance(const Point& p) const;
	bool is_colliding(const Circle& c) const;
	void move(const Point& p);
};