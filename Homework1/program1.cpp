#include <cstdio>
#include <iostream>

namespace myspace
{
	void print_n_times(const char str[], int n = 10)
	{
		for(int i = 0; i < n; i++)
		{
			std::cout << str;
			std::cout << "\n";
		}
	}
}

int main()
{
	myspace::print_n_times("lol");
}