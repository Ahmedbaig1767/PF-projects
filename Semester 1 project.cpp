#include<time.h>
#include<iostream>
#include<conio.h>
#include<string.h>
#include"Header.h"
#include<tgmath.h>
#include <fstream>

using namespace std;

int position_X = 502;
int position_y = 212;
int tilt_x = 18;
int tilt_y = 18;
int angle = 0;
int R = 255, B = 255, G = 255;
int width = 2;
bool cmpstr(char a1[], const char b1[])
{
	int a = strlen(a1);
	int b = strlen(b1);
	if (a == b || a == b - 1)
	{
		for (int i = 0; i < a; i++)
		{
			if (a1[i] != b1[i])
				return false;
		}
		return true;
	}
	return false;
}
void breakstr(char a[], int& num)
{
	int length = strlen(a);

	for (int i = 0; i < length; i++)
	{
		if (a[i] >= '0' && a[i] <= '9')
		{
			num = atoi(&a[i]);
			a[i] = '\0';
			break;
		}
	}
}
bool checkrepeat(char command[], const char a[])
{
	int i = 0;
	for (; i < strlen(a) - 1; i++);
	{
		if (command[i] != a[i])
		{
			return false;
		}
	}
	return true;
}
char* breakstr(char a[], char b[])
{
	char* al = nullptr;
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] == ' ')
		{
			al = &a[i + 1];
			a[i] = '\0';
			break;
		}
	}
	if (al != nullptr)
		b = al;
	return b;
}
void clearArrow()
{
	bool temp = IsPenDown;
	IsPenDown = true;
	float rad;
	float pie = 3.14;
	int angle1 = angle + 180;
	angle1 += 45;
	rad = angle1 * (pie / 180);
	int aX = tilt_x * cos(rad);
	int aY = tilt_y * sin(rad);
	myLine(position_X, position_y, position_X + aX, position_y - aY, 0, 0, 0, width);
	angle1 = angle1 - 90;
	rad = angle1 * (pie / 180);
	aX = tilt_x * cos(rad);
	aY = tilt_y * sin(rad);
	myLine(position_X, position_y, position_X + aX, position_y - aY, 0, 0, 0, width);

	IsPenDown = temp;

}
void putArrow()
{

	bool temp = IsPenDown;
	IsPenDown = true;

	float rad;
	float pie = 3.14;
	int angle1 = angle + 180;
	angle1 += 45;
	rad = angle1 * (pie / 180);
	int aX = tilt_x * cos(rad);
	int aY = tilt_y * sin(rad);
	myLine(position_X, position_y, position_X + aX, position_y - aY, R, B, G, width);
	angle1 -= 90;
	rad = angle1 * (pie / 180);
	aX = tilt_x * cos(rad);
	aY = tilt_y * sin(rad);
	myLine(position_X, position_y, position_X + aX, position_y - aY, R, B, G, width);

	IsPenDown = temp;

}
void go_Forward(int pixal)
{
	float pie = 3.14;
	float rad = angle * (pie / 180);
	int aX = pixal * cos(rad);
	int aY = pixal * sin(rad);

	if (position_y + aY > 0 && position_X + aX > 0 && position_X + aX < 810 && position_y + aY < 500)
	{
		clearArrow();

		myLine(position_X, position_y, position_X + aX, position_y - aY, R, B, G, width);

		position_X += aX;
		position_y -= aY;
		putArrow();
		gotoxy(1, 28);
		cout << "Enter commands:";
	}
	else {
		gotoxy(1, 28);
		cout << "At Borderline cant go reach the limit enter other command: ";
	}
}
void go_Backward(int pixal)
{

	int a = position_X;
	int b = position_y;
	float pie = 3.14;
	int angle1 = angle + 180;
	float rad = angle1 * (pie / 180);
	unsigned int aX = pixal * cos(rad);
	unsigned int aY = pixal * sin(rad);

	if (position_y + aY > 0 && position_X + aX > 0 && position_X + aX < 810 && position_y + aY < 500)
	{
		clearArrow();
		myLine(position_X, position_y, position_X + aX, position_y - aY, R, B, G, width);

		position_X += aX;
		position_y -= aY;
		putArrow();
		gotoxy(1, 28);
		cout << "Enter commands:";
	}
	else {
		gotoxy(1, 28);
		cout << "At Borderline cant go reach the limit  enter other command: ";
	}
}
void left(int angl)
{
	if ((angl % 45) == 0 || (angl % 30) == 0)
	{
		clearArrow();
		float rad;
		float pie = 3.14;
		angle += angl;
		if (angle >= 360)
		{
			angle = angle % 360;
		}
		int angle1 = angle;
		angle1 += 180;
		angle1 += 45;
		rad = angle1 * (pie / 180);
		unsigned int aX = tilt_x * cos(rad);
		unsigned int aY = tilt_y * sin(rad);

		int temp = IsPenDown;
		IsPenDown = true;

		myLine(position_X, position_y, position_X + aX, position_y - aY, R, B, G, 2);
		angle1 -= 90;
		rad = angle1 * (pie / 180);
		aX = tilt_x * cos(rad);
		aY = tilt_y * sin(rad);
		myLine(position_X, position_y, position_X + aX, position_y - aY, R, B, G, 2);

		IsPenDown = temp;
	}


}
void right(int angl)
{
	if ((angle % 45) == 0 || (angle % 30) == 0)
	{
		left(360 - angl);
	}
}
void CreateCircle(int rad)
{
	myEllipse(position_X - (rad / 2), position_y - (rad / 2), position_X + (rad / 2), position_y + (rad / 2), R, B, G, width);
}
bool Validation(char command[]);
bool repeat(char a[])
{
	char* p;
	int num;
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] >= '0' && a[i] <= '9') {
			char* k = &a[i];
			p = &a[i];
			int j = 0;
			for (; j < strlen(p); j++) {
				if (p[j] == '[') {
					k = &p[j];
					break;
				}
			}
			p[j] = '\0';
			k++;
			int a = atoi(p);
			num = a;
			p[0] = '\0';
			int counter = 0;
			char command[5][20];
			while (*k != ']') {

				int idx = 0;
				while (*k != ' ' && *k != ']' && idx < 20) {
					command[counter][idx++] = *k++;
				}
				command[counter][idx] = '\0';
				if (*k == ' ') k++;
				counter++;
			}

			for (int temp = 0; temp < num; temp++) {
				for (int po = 0; po < counter; po++)
				{
					char numbers[20];
					for (int it = 0; it < strlen(command[po]); it++)
					{
						numbers[it] = command[po][it];
					}
					bool a = Validation(numbers);
					if (!a)
					{
						return false;
					}
				}

			}
			break;
		}
	}
}
bool DefineColor(char a[])
{
	if (cmpstr(a, "RED"))
	{
		R = 255;
		B = 0;
		G = 0;
		return true;
	}
	else if (cmpstr(a, "GREEN"))
	{
		G = 255;
		B = 0;
		R = 0;
		return true;
	}
	else if (cmpstr(a, "DARKBLUE"))
	{
		B = 255;
		R = 0;
		G = 0;
		return true;
	}
	else if (cmpstr(a, "YELLOW"))
	{
		R = 255;
		B = 0;
		G = 255;
		return true;
	}
	else if (cmpstr(a, "PINK"))
	{
		R = 255;
		B = 255;
		G = 0;
		return true;
	}
	else if (cmpstr(a, "BROWN"))
	{
		R = 128;
		B = 0;
		G = 0;
		return true;
	}
	else if (cmpstr(a, "BLUE"))
	{
		B = 255;
		R = 0;
		G = 255;
		return true;
	}
	else if (cmpstr(a, "PURPLE"))
	{
		R = 128;
		B = 128;
		G = 0;
		return true;
	}
	else if (cmpstr(a, "ORANGE"))
	{
		R = 255;
		G = 165;
		B = 0;
		return true;
	}
	else if (cmpstr(a, "GREY"))
	{
		R = 128;
		G = 128;
		B = 128;
		return true;
	}
	else
	{
		cout << "color not present";
		return false;
	}
}
void width1()
{
	width = 5;
}
void width2()
{
	width = 8;
}
void width3()
{
	width = 12;
}
bool Validation(char command[])
{
	if (cmpstr(command, "cs"))
	{
		system("cls");
		position_X = 502;
		position_y = 212;
		angle = 0;
		putArrow();
		gotoxy(1, 28);
		cout << "Enter commands:";
		return true;
	}
	else if (checkrepeat(command, "repeat"))
	{
		bool a = repeat(command);
		return a;
	}
	else if (checkrepeat(command, "color"))
	{
		char* color = nullptr;
		color = breakstr(command, color);
		bool a = DefineColor(color);
		return a;
	}
	int a = 0;
	breakstr(command, a);
	if (cmpstr(command, "fd"))
	{
		go_Forward(a);
		return true;
	}
	else if (cmpstr(command, "forward"))
	{
		go_Forward(a);
		return true;
	}
	else if (cmpstr(command, "bk"))
	{
		go_Backward(a);
		return true;
	}
	else if (cmpstr(command, "backward"))
	{
		go_Backward(a);
		return true;
	}
	else if (cmpstr(command, "lt"))
	{
		left(a);
		return true;
	}
	else if (cmpstr(command, "rt"))
	{
		right(a);
		return true;
	}
	else if (cmpstr(command, "pu"))
	{

		IsPenDown = false;
	}
	else if (cmpstr(command, "pd"))
	{

		IsPenDown = true;
	}
	else if (cmpstr(command, "circle"))
	{
		CreateCircle(a);
		return true;
	}
	else if (cmpstr(command, "WIDTH"))
	{
		if (a == 1)
		{
			width1();
		}
		else if (a == 2)
		{
			width2();
		}
		else if (a == 3)
		{
			width3();
		}
	}
	else
	{
		gotoxy(1, 28);
		cout << "Invalid Command Enter command Again:";
		return false;
	}
}
void saveList(char a1[10][20], int a) {
	ofstream outFile("History.txt");
	
	for (int i = 0; i < a; ++i) {
		outFile << a1[i] << endl;
	}
	outFile.close();
	gotoxy(1, 28);
	cout << "Commands saved to History.txt" << endl;
}
void loadAndRun() {
	std::ifstream inFile("History.txt");
	if (!inFile.is_open()) {
		gotoxy(1, 28);
		cout << "History.txt not found. No commands to load." << endl;
		return;
	}

	char command[30];
	while (!inFile.eof())
	{
		inFile.getline(command, sizeof(command));
		Validation(command);
	}
	inFile.close();
}



int main()
{
	system("color 0F");
	char hist[5][20];
	//	int a;
	int i = 0;
	char list[30];
	int p = 0;
	bool  cheak = false;
	putArrow();
	gotoxy(1, 28);
	cout << "Enter commands:";
	while (true)
	{

		myLine(0, 430, 810, 430, 255, 0, 0, 6);
		myLine(810, 370, 810, 480, 255, 0, 0, 6);
		myLine(810, 370, 970, 370, 255, 0, 0, 6);
		gotoxy(40, 28);
		cin.getline(list, 30);
		if (cmpstr(list, "history"))
		{
			break;
		}
		else if (cmpstr(list, "save"))
		{
			saveList(hist, i);
			continue;
		}
		else if (cmpstr(list, "load"))
		{
			loadAndRun();
			continue;
		}
		gotoxy(40, 28);
		cout << "                      ";
		char buf[20];
		for (int k = 0; k < 20; k++)
		{
			buf[k] = list[k];
		}

		bool p = Validation(buf);
		if (p)
		{
			for (int k = 0; k < 20; k++)
			{
				hist[i % 5][k] = list[k];
			}
			i++;
		}
	}

	gotoxy(105, 28);
	cout << "history\n";
	int x = 105;
	int y = 25;

	int temp = i % 5;


	int index = 1;
	for (int size = temp; size < 5; size++)
	{
		gotoxy((100), (y = y + 1));
		cout << index << "\t" << hist[size] << endl;
		index++;

	}
	for (int size = 0; size < temp; size++)
	{
		gotoxy((100), (y = y + 1));
		cout << index << "\t" << hist[size] << endl;
		index++;

	}


	Sleep(50000);
	return 0;
}