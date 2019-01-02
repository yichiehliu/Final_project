#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "utilwin32.h"
#include <stdlib.h>

using namespace std;

void SetColor(int color);
void Drop(int x, int y, string c);
int RandX(int ran);

int width = 50, height = 25, length = 10;
int randPosition = 0, orgX = 0, orgY = 0;
string c;

int RandX(int ran){
	int randPosition = 0;
	srand( time(NULL) );//�T�w�üƺؤl
	randPosition = rand() % (width - length + 1); 
	return randPosition;
}

void Drop(int x, int y, string c, double velocity){
	int ran = 0;
	x = RandX(ran) + 1;
	
	gotoxy(x,orgY);

		for (y = orgY; y <= height; y++)
		{
			
		    delay(500-velocity); // �C�����ʤ������j 0.5 �� (500ms)
		    gotoxy(x,y), cout << "                     "; // ���ʨ�U�@�Ӯy�Ыe���M����Ӫ���r
		    SetColor(15);
			gotoxy(x,y+1), cout << c;
			cout << "(x,y): " << x << "," << y;
			SetColor(255);
		}
			SetColor(255);
			gotoxy(x,y), cout << "                     ";
	
}


int main(){
	
	int x = 0, y = 0;
	double velocity = 0;
	system("color F0");//�թ��¦r 
	c = "Vocab";
	
	while(1){
		if (velocity < 400) velocity = velocity + 40;
		if (velocity == 400) velocity = 400;//�����[�t 
		Drop(x, y, c, velocity);
	}
	
	system("PAUSE");
	return 0 ;
}

void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
}


//	clock_t sTime = clock();
//	for(i = 0; i < 10000000; i++){
//	}
//	clock_t eTime = clock();
//	cout << sTime << " " << eTime << " " << static_cast<double>(eTime - sTime) / CLOCKS_PER_SEC;
//	cout << " " << randPosition;
