#include <iostream>
#include <string>
using namespace std;

template <class T>
class SmartPointer
{
private:
	T* pointer;
public:
	SmartPointer(T* new_pointer)
	{
//		pointer = new T[new_pointer]; 
		pointer = new_pointer;
	}

	T& operator*()
	{
		return *pointer;
	}

	~SmartPointer()
	{
		delete pointer;
	}
}; 

int main()
{
	SmartPointer<int> pi = new int(123);
	SmartPointer<string> ps = new string("Hello");
	*pi = 543;
	*ps = "World";
	cout << *pi << " " << *ps << endl;
}