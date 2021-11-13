#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

struct Vector3f
{
    float x;
    float y;
    float z;
};

Vector3f operator+(const Vector3f& a, const Vector3f& b)
{
	Vector3f result = {a.x + b.x, a.y + b.y, a.z + b.z};
	return result;
}

Vector3f operator-(const Vector3f& a, const Vector3f& b)
{
    Vector3f result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

Vector3f operator*(const Vector3f& a, float b)
{
    Vector3f result = a;
    result.x *= b;
    result.y *= b;
    result.z *= b;
    return result;
}

Vector3f operator*(float b, const Vector3f& a)
{
    Vector3f result = a;
    result.x *= b;
    result.y *= b;
    result.z *= b;
    return result;
}

Vector3f operator/(const Vector3f& a, float b)
{
    Vector3f result = a;
    result.x /= b;
    result.y /= b;
    result.z /= b;
    return result;
}

float operator*(const Vector3f& a, const Vector3f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3f operator-(const Vector3f& a)
{
    Vector3f result = {(-1) * a.x, (-1) * a.y, (-1) * a.z};
    return result;
}

Vector3f operator+(const Vector3f& a)
{
    Vector3f result = {(1) * a.x, (1) * a.y, (1) * a.z};
    return result;
}

bool operator==(const Vector3f& a, const Vector3f& b)
{
    if(a.x == b.x && a.y == b.y && a.z == b.z)
    {
    	return true;
    }
    else
    {
    	return false;
    }
}

bool operator!=(const Vector3f& a, const Vector3f& b)
{
    if(a.x == b.x && a.y == b.y && a.z == b.z)
    {
    	return false;
    }
    else
    {
    	return true;
    }
}

Vector3f operator+=(Vector3f& a, const Vector3f& b)
{
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;
    return a;
}

Vector3f operator-=(Vector3f& a, const Vector3f& b)
{
    a.x = a.x - b.x;
    a.y = a.y - b.y;
    a.z = a.z - b.z;
    return a;
}

Vector3f operator*=(Vector3f& a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    return a;
}

Vector3f operator/=(Vector3f& a, float b)
{
    a.x /= b;
    a.y /= b;
    a.z /= b;
    return a;
}

float norm(const Vector3f& a)
{
	Vector3f result = a;
	float norm = sqrt((result.x * result.x) + (result.y * result.y) + (result.z * result.z));
	return norm;
}

float squared_norm(const Vector3f& a)
{
	Vector3f result = a;
	float norm = sqrt((result.x * result.x) + (result.y * result.y) + (result.z * result.z));
	return norm * norm;
}

void normalize(Vector3f& a)
{
	float norm = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	a.x = a.x / norm;
	a.y = a.y / norm;
	a.z = a.z / norm;
}

ostream& operator<<(ostream& first, Vector3f second)
{
	first << "(" << second.x << ", " << second.y << ", " << second.z << ")";
    return first;
}

istream& operator>>(istream& first, Vector3f second)
{
	first >> second.x;
	first >> second.y;
	first >> second.z;
    return first;
}
