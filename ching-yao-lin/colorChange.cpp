#include <iostream>
#include <windows.h>
#include <cstring>
#include <conio.h>
#include <iomanip>

using namespace std;

const int MAX_WORD_LEN = 20;
const int numOfVocabs = 5;


struct Vocab
{
    int* color;
    char* letter;
};
/// ================== DECLARATION OF GLOBAL FUNCTIONS ==================
void colorChange(Vocab* vocabs, int numOfVocabs, char ch);
void eraseVocabsIfNeeded(Vocab* vocabs, int numOfVocabs);
void SetColor(int f = 7, int b = 0)
{
    unsigned short ForeColor = f + 16 * b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}
void colorPlate()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    for(int k = 1; k < 255; k++)
    {
        // pick the colorattribute k you want
        SetConsoleTextAttribute(hConsole, k);
        cout <<"<" << setw(3)<< k <<">";
        if(k % 20 == 0)
            cout << endl;
    }
    SetColor();
    cout << endl;
}

int main()
{

    SetColor(0,7);   //在想要改變顏色的字串前加上這行SetColor(字顏色碼,背景顏色碼)
    cout<<"△▲☆★◆◇"<<endl;
    SetColor(); //復原顏色為白字黑底
    system("pause");





    Vocab* vocabs = new Vocab[5];
    for(int i = 0; i < numOfVocabs; i++)
        vocabs[i].letter = new char[MAX_WORD_LEN];
    for(int i = 0; i < numOfVocabs; i++)
    {
        vocabs[i].color = new int[MAX_WORD_LEN];
        for(int j = 0; j < MAX_WORD_LEN; j++)
            vocabs[i].color[j] = 0;
    }

    cout << "< test >: " << endl;
    for(int i = 0; i < numOfVocabs; i++)
        cout << "vocabs[" << i << "].letter = " << vocabs[i].letter << endl;
    for(int i = 0; i < numOfVocabs; i++)
    {
        cout << "vocabs[" << i << "].color = ";
        for(int j = 0; j < MAX_WORD_LEN; j++)
             cout << vocabs[i].color[j] << " ";
        cout << endl;
    }


    cout << "< Initialiazing testVocabs... >:" << endl;
    char** testVocabs = new char*[numOfVocabs];
    for(int i = 0; i < numOfVocabs; i++)
        testVocabs[i] = new char[MAX_WORD_LEN];
    testVocabs[0] = "kitten";
    testVocabs[1] = "kitchen";
    testVocabs[2] = "its";
    testVocabs[3] = "still";
    testVocabs[4] = "dogs";
    for(int i = 0; i < 5; i++)
        cout << "testVocabs[" << i << "] = " << testVocabs[i] << endl;

    //SetColor(<strong>115</strong>);

    strcpy(vocabs[0].letter, testVocabs[0]);
    strcpy(vocabs[1].letter, testVocabs[1]);
    strcpy(vocabs[2].letter, testVocabs[2]);
    strcpy(vocabs[3].letter, testVocabs[3]);
    strcpy(vocabs[4].letter, testVocabs[4]);
    cout << "< After assigning words...>: " << endl;
    for(int i = 0; i < numOfVocabs; i++)
        cout << "vocabs[" << i << "].letter = " << vocabs[i].letter << endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // pick the colorattribute k you want
    SetConsoleTextAttribute(hConsole, 224);
    cout << "The color is 224!" << endl;

    cout << "< After changing colors...>: " << endl;
    for(int i = 0; i < numOfVocabs; i++)
        cout << "vocabs[" << i << "].letter = " << vocabs[i].letter << endl;

    SetColor();

    cout << "< After cleaning out colors...>: " << endl;
    for(int i = 0; i < numOfVocabs; i++)
        cout << "vocabs[" << i << "].letter = " << vocabs[i].letter << endl;

    colorPlate();


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


    return 0;
}
/// ======================== GLOBAL FUNCTIONS ========================
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

    for(int i = 0; i < numOfVocabs; i++)
    {
        int j = 0;
        while(vocabs[i].color[j] != 0)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // pick the colorattribute k you want
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


    /// if the sum of color array == strlen(letter array of vocab), clean the memory
    for(int i = 0; i < numOfVocabs; i++)
    {
        if(sum[i] == strlen(vocabs[i].letter))
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // pick the colorattribute k you want
            SetConsoleTextAttribute(hConsole, 4);
            cout << "======== Erase " << vocabs[i].letter << " !!!========" << endl;
            SetColor();
            delete[] vocabs[i].letter;
            for(int j = 0; j < MAX_WORD_LEN; j++)
            {
                vocabs[i].color[j] = 0;
            }
        }
    }

}
