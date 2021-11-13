#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "complex.h"
using namespace std;

// В этой программе мы рисуем в картинку комплексную функцию,
// которая задаётся в функции func

struct Color
{
	unsigned char r, g, b;
};

Complex func(Complex z, Complex c, int n)
{
	for(int i = 0; i < n; i++)
	{
		if(abs(z) > 65025)
		{
			break;
		}
		z = z * z + c;
	}
	z.re = fabs(z.re);
	z.im = fabs(z.im);
	if (z.re > 255)
		z.re = 255;
	if (z.im > 255)
		z.im = 255;
	z.re = 255 - z.re;
	z.im = 255 - z.im;
	return z;
	
}


int main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("Error!\n");
		printf("To use this program: a <Re> <Im> <N>\n");
		exit(1);
	}
	Complex c;
	int n;
	sscanf(argv[1], "%f", &c.re);
	sscanf(argv[2], "%f", &c.im);
	sscanf(argv[3], "%d", &n);


	int width = 800, height = 800;
	float x0 = -2.0f, x1 = 2.0f;
	float y0 = -2.0f, y1 = 2.0f;
	
	// Выделяем память под пиксели
	Color* data = (Color*)malloc(sizeof(Color) * width * height);

	// data - это массив цветов размером width * height
	// Задаём значения этого массива так, чтобы
	// реальная часть функции func соответствовала зелёному цвету,
	// а мнимая часть -- синей компоненте цвета
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{	
			Complex z = {x0 + (x1-x0) / width * i, y0 + (y1-y0) / width * j};
			Complex f = func(z, c, n);
			data[i + width * j].r = 0;
			data[i + width * j].g = f.re;
			data[i + width * j].b = f.im;
		}
	}

	// Сохраняем массив цветов data как картинку в формате .ppm
	FILE* file = fopen("image5.ppm", "wb");
	fprintf(file, "P6\n%d %d\n255\n", width, height);
	fwrite(data, sizeof(Color), height * width, file);
	fclose(file);

	// Освобождаем память
	free(data);
}