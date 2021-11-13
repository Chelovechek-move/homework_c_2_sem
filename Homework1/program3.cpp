#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

void count_letters(char str[], int& n_letters, int& n_digits, int& n_other)
{
	unsigned int length = strlen(str);

	for(int i = 0; i < length; i++)
	{
		if(str[i] >= 48 && str[i] <= 57)
		{
			n_digits++;
		}
		else
		{
			if((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			{
				n_letters++;
			}
			else
			{
				n_other++;
			}
		}
	}
}


int main()
{
	int n_other = 0;
	int n_letters = 0;
	int n_digits = 0;
	char str[] = "234popolol<<*";

	count_letters(str, n_letters, n_digits, n_other);
	cout << "n_letters = " << n_letters << ", n_digits = " << n_digits << ", n_other = " << n_other << endl;
}