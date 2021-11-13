#include <iostream>
#include <string>
using namespace std;

template <class T, class U>
class Pair
{
public:
	T first;
	U second;
	Pair(T new_first, U new_second)
	{
		first = new_first;
		second = new_second;
	}
}; 

int main()
{
	Pair<int, string> a = {777, "Axolotl"};
	Pair<string, float> b = {"Hippo", 6.45};
	cout << a.first << " " << a.second << endl;
	b.first += "potamus";
	b.second = 3.14;
	cout << b.first << " " << b.second << endl;
}