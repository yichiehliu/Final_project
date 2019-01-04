#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "utilwin32.h"
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <omp.h>

using namespace std;

struct Vocab
{
    int * color; // 該letter沒有變色，等於0；有變色，等於1。
    char* letter;
};
/// ================== DECLARATION OF GLOBAL VARIABLES ================== ///
const int MAX_WORDS = 1001;  // 從單字庫抽出的單字數
const int MAX_WORD_LEN = 20; // 單字的最長長杜
const int WORDS_DROPPING = 3; // 一輪總共要掉幾個字
int width = 50, height = 25, length = 10; // 單字的活動範圍
int randPosition = 0, orgX = 0, orgY = 0;
/// ================== DECLARATION OF GLOBAL FUNCTIONS ================== ///
void drop(int x, int y, char* word, double velocity, Vocab* vocabs, int numOfVocabs);
void printSpace(int numOfSpace);
void colorChange(Vocab* vocabs, int numOfVocabs, char ch); // 根據輸入，將第一個未變色字母變色
void printInColor(Vocab* vocabs, int numOfVocabs); // 根據 "color不為0的字母要變色" 的規則，印出該單字
void eraseVocabsIfNeeded(Vocab* vocabs, int numOfVocabs); // 當單字全部變色，清空該單字
void colorPlate(); // 可以用來顯示調色盤("數字" 對應 "字體顏色")
int RandX(int ran) // 隨機選出一個水平位置
{
	int randPosition = 0;
	srand( time(NULL) );//固定亂數種子
	randPosition = rand() % (width - length + 1);
	return randPosition;
}
void SetColor(int color = 7) // 預設：黑底白字
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

/// ======================== MAIN FUNCTION ======================== ///
int main(){

    // 基本設定初始化
	system("color F0"); // 白底黑字

	//colorPlate(); // 查看調色盤

	// 動態記憶體配置 & 初始化
    Vocab* vocabs = new Vocab[MAX_WORDS];
    for(int i = 0; i < MAX_WORDS; i++)
        vocabs[i].letter = new char[MAX_WORD_LEN];
    for(int i = 0; i < MAX_WORDS; i++)
    {
        vocabs[i].color = new int[MAX_WORD_LEN];
        for(int j = 0; j < MAX_WORD_LEN; j++)
            vocabs[i].color[j] = 0;
    }
    char** c = new char*[MAX_WORDS];
    for(int i = 0; i < MAX_WORDS; i++)
        c[i] = new char[MAX_WORD_LEN];

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

    // 從檔案匯入單字庫
    ifstream file("file.txt");
    const int TOTAL_VOCAB_NUM = MAX_WORDS - 1;
    int i = 0;
    if(file.is_open())
    {
        for(i = 1; i <= TOTAL_VOCAB_NUM; ++i)
        {
            file >> vocabs[i].letter; // 物件vocabs被依序填滿單字
        }
    }
    else
        cout << "Error in reading files" << endl;
    /*
    for (i = 1 ; i <= TOTAL_VOCAB_NUM ; i++)
        cout << vocabs[i].letter << "\n" ;
    */

    // 隨機從單字庫抽出單字
    int n = 1;
    int x = 0, y = 0;
	double velocity = 0;
    int randomNum = 0;
    int numOfVocabs = 3;
    srand( unsigned(time(0)) );
    //cin >> n;

	while(1)
    {

		for (i = 0 ; i < MAX_WORDS; i++)
	    {
	        randomNum = (rand() % 1000); // generate random number from 0 ~ 999
	        //cout << randomNum << " ";
	        //strcpy(c[i], vocabs[randomNum].letter); // 從物件vocabs隨機挑出一個單字，共挑MAX_WORDS個
	        //cout << vocabs[randomNum].letter << "\n";
	        //cout << "c[" << i << "] = " << c[i] << "\n";

	        if (velocity < 400) velocity = velocity + 40; //漸漸加速
            else if (velocity == 400) velocity = 400;

            drop(x, y, vocabs[randomNum].letter, velocity, vocabs, numOfVocabs);
	    }

	}

	/** 林璟耀 - 不知道該放哪裡的CODE
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
void play(int x, int y, char* word, double velocity, Vocab* vocabs, int numOfVocabs)
{

}
void drop(int x, int y, char* word, double velocity, Vocab* vocabs, int numOfVocabs)
{
    /*
    double velocity = 0;
    if (velocity < 400) velocity = velocity + 40; //漸漸加速
    else if (velocity == 400) velocity = 400;
    */

	int ran = 0;
	x = RandX(ran) + 1;
	gotoxy(x,orgY); // 游標移到隨機的x座標

	int freq = numOfVocabs;

	#pragma omp parallel for
    for(y = orgY; y <= height; y++) // 讓一個單字從(y座標=0)掉到(y座標=height)
    {

        delay(500 - velocity); // 每次移動之間間隔 0.5 秒 (500ms), 不過input的velocity會越來越大、直到400會固定
        //gotoxy(x,y), printSpace(strlen(word))/*cout << "                     "*/; // 移動到下一個座標前先清除原來的文字

        SetColor(); // 恢復原本的顏色(預設：黑底白字)
        gotoxy(x, y + 1), cout << word;
        //cout << "(x,y): " << x << "," << y << " ";
        //cout << "len = " << strlen(word);
        SetColor(255);

        gotoxy(x,y), printSpace(strlen(word))/*cout << "                     "*/; // 移動到下一個座標前先清除原來的文字

        char ch;
        if (_kbhit())//如果有按键按下，则_kbhit()函数返回真
        {
            ch = _getch();//使用_getch()函数获取按下的键值
            colorChange(vocabs, numOfVocabs, ch);
            if (ch == 27){ break; }//当按下ESC时循环，ESC键的键值时27.
        }
    }
        SetColor(255);
        gotoxy(x,y), printSpace(strlen(word))/*cout << "                     "*/;
}
void printSpace(int numOfSpace)
{
    for(int i = 0; i < numOfSpace; i++)
        cout << " ";
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
        if(sum[i] == strlen(vocabs[i].letter)) // 有字是全部變色的
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
            /// 記分板 + 1 (宜婕)
        }
    }

}
void colorPlate() // 可以用來顯示調色盤("數字" 對應 "字體顏色")
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
