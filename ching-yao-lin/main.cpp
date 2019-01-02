#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "utilwin32.h"
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct Vocab
{
    int * color; // ��letter�S���ܦ�A����0�F���ܦ�A����1�C
    char* letter;
};
/// ================== DECLARATION OF GLOBAL VARIABLES ================== ///
const int MAX_WORDS = 1001;
const int MAX_WORD_LEN = 20;
int width = 50, height = 25, length = 10;
int randPosition = 0, orgX = 0, orgY = 0;
string c;
/// ================== DECLARATION OF GLOBAL FUNCTIONS ================== ///
void Drop(int x, int y, string c, double velocity, Vocab* vocabs, int numOfVocabs);
void colorChange(Vocab* vocabs, int numOfVocabs, char ch);
void printInColor(Vocab* vocabs, int numOfVocabs);
void eraseVocabsIfNeeded(Vocab* vocabs, int numOfVocabs);
void colorPlate(); // �i�H�Ψ���ܽզ�L("�Ʀr" ���� "�r���C��")
int RandX(int ran)
{
	int randPosition = 0;
	srand( time(NULL) );//�T�w�üƺؤl
	randPosition = rand() % (width - length + 1);
	return randPosition;
}
void SetColor(int color = 7) // �w�]�G�©��զr
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
}
/*
void SetColor(int f = 7, int b = 0)
{
    unsigned short ForeColor = f + 16 * b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}
*/

/// ======================== MAIN FUNCTIONS ======================== ///
int main(){

	int x = 0, y = 0, i = 0;
	double velocity = 0;
	system("color F0"); // �թ��¦r

	//colorPlate();

    Vocab* vocabs = new Vocab[MAX_WORDS];
    for(int i = 0; i < MAX_WORDS; i++)
        vocabs[i].letter = new char[MAX_WORD_LEN];
    for(int i = 0; i < MAX_WORDS; i++)
    {
        vocabs[i].color = new int[MAX_WORD_LEN];
        for(int j = 0; j < MAX_WORD_LEN; j++)
            vocabs[i].color[j] = 0;
    }

    /*
    cout << "< test >: " << endl;
    for(int i = 0; i < MAX_WORDS; i++)
        cout << "vocabs[" << i << "].letter = " << vocabs[i].letter << endl;
    for(int i = 0; i < MAX_WORDS; i++)
    {
        cout << "vocabs[" << i << "].color = ";
        for(int j = 0; j < MAX_WORD_LEN; j++)
             cout << vocabs[i].color[j] << " ";
        cout << endl;
    }
    */


    srand(unsigned(time(0))) ;
    int randomNum = 0 ;
    int n = 0;

    ifstream file("file.txt");

    const int TOTAL_VOCAB_NUM = MAX_WORDS - 1;
    if(file.is_open())
    {
        for(i = 1; i <= TOTAL_VOCAB_NUM; ++i)
        {
            file >> vocabs[i].letter;
        }
    }
    else
        cout << "Error in reading files" << endl;
    //for (i = 1 ; i <= TOTAL_VOCAB_NUM ; i++)
        //cout << vocabs[i].letter << "\n" ;

    //cin >> n;

	while(1){

	    n = 1;
		for (i = 0 ; i < n ; i++)
	    {
	        randomNum = (rand() % 1000); // generate number from 0 -999
	        //cout << randomNum << " ";
	        c = vocabs[randomNum].letter;
	        //cout << vocabs[randomNum].letter << "\n";

	    }
		if (velocity < 400) velocity = velocity + 40;
		if (velocity == 400) velocity = 400;//�����[�t

        Drop(x, y, c, velocity, vocabs, TOTAL_VOCAB_NUM);
	}

	/** �L�[ģ - �����D�ө���̪�CODE
	cout << "Type any letter to change colors: " << endl;
    for(;1;)
    {
        char ch;
        ch = getch();
        cout << "Entering >> " << ch << " : ";
        colorChange(vocabs, numOfVocabs, ch);
        cout << endl;
        eraseVocabsIfNeeded(vocabs, numOfVocabs);
    }
	**/

	system("PAUSE");
	return 0 ;
}
/// ======================== GLOBAL FUNCTIONS ======================== ///
void Drop(int x, int y, string c, double velocity, Vocab* vocabs, int numOfVocabs)
{
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
void colorChange(Vocab* vocabs, int numOfVocabs, char ch)
{
    for(int i = 0; i < numOfVocabs; i++)
    {
        ///Find the first color-unchanged letter for each vocab, check if it's ch.
        for(int j = 0; j < strlen(vocabs[i].letter); j++)
        {
            if(vocabs[i].color[j] == 0) // the first unchanged letter
            {
                if(vocabs[i].letter[j] == ch) // this letter matches the input char
                {
                    vocabs[i].color[j] = 1; // mark the color as 1, meaning "to be changed"
                }
                break;
            }
        }
    }

    printInColor(vocabs, numOfVocabs);

}
void printInColor(Vocab* vocabs, int numOfVocabs)
{
    for(int i = 0; i < numOfVocabs; i++)
    {
        int j = 0;
        while(vocabs[i].color[j] != 0)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 224);
            cout << vocabs[i].letter[j];
            j++;
        }
        SetColor();

        while(j <= strlen(vocabs[i].letter))
        {
            cout << vocabs[i].letter[j];
            j++;
        }
    }
}
void eraseVocabsIfNeeded(Vocab* vocabs, int numOfVocabs)
{
    /// Calculate the sum of color array for each vocab
    int* sum = new int[numOfVocabs];
    for(int i = 0; i < numOfVocabs; i++)
    {
        sum[i] = 0;
        for(int j = 0; j < MAX_WORD_LEN; j++)
            sum[i] += vocabs[i].color[j];
    }
    /*
    cout << "< test sum >:" << endl;
    for(int i = 0; i < numOfVocabs; i++)
        cout << "sum[" << i << "] = " << sum[i] << endl;

    cout << "< test strlen >:" << endl;
    for(int i = 0; i < numOfVocabs; i++)
        cout << "strlen(vocabs[" << i << "].letter) = " << strlen(vocabs[i].letter) << endl;
    */


    /// if the sum of color array == strlen(letter array of vocab), reset the memory
    bool wordDisappear = false;
    for(int i = 0; i < numOfVocabs; i++)
    {
        if(sum[i] == strlen(vocabs[i].letter)) // ���r�O�����ܦ⪺
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "======== Erase " << vocabs[i].letter << " !!!========" << endl;
            SetColor();
            //delete[] vocabs[i].letter;
            strcpy(vocabs[i].letter, "*ERASED*");
            for(int j = 0; j < MAX_WORD_LEN; j++)
            {
                vocabs[i].color[j] = 0;
            }

            wordDisappear = true;
        }

        if(wordDisappear == true) // if there's a word disappeared, reset all colors
        {
            for(int j = 0; j < MAX_WORD_LEN; j++)
                vocabs[i].color[j] = 0; /// reset all colors
            /// �O���O + 1 (�y��)
        }
    }

}
void colorPlate() // �i�H�Ψ���ܽզ�L("�Ʀr" ���� "�r���C��")
{
    cout << "     ===================================== COLOR PLATE ===================================== " << endl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    cout << "||";
    for(int k = 1; k <= 255; k++)
    {
        // pick the colorattribute k you want
        SetConsoleTextAttribute(hConsole, k);
        cout <<"<" << setw(3)<< k <<">";
        if(k % 20 == 0)
        {
            SetColor();
            cout << "||" << endl << "||";
        }

    }
    SetColor();
    cout << endl;
}




//	clock_t sTime = clock();
//	for(i = 0; i < 10000000; i++){
//	}
//	clock_t eTime = clock();
//	cout << sTime << " " << eTime << " " << static_cast<double>(eTime - sTime) / CLOCKS_PER_SEC;
//	cout << " " << randPosition;
