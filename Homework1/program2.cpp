#include <cstdio>
#include <iostream>

void cube(int& k)
{
	k = k * k * k;
}

int main()
{
	int k = 2;
	cube(k);
	std::cout << k;
}