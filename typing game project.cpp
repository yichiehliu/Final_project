//
//  main.cpp
//  typing game
//
//  Created by Veronica on 2018/12/24.
//  Copyright © 2018 Veronica. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
const int MAX_N = 1001;
const int MAX_M = 20;
using namespace std;
struct vocab
{
    int * color;
    char letter[MAX_M];
} ;

int main()
{
    
    vocab myVocab[MAX_N]={0};
    
    srand(unsigned(time(0))) ;
    int randomNum = 0 ;
    int n = 0;
    
    ifstream file("file.txt");
    
    if(file.is_open())
    {
        
        for(int i = 1; i <= 1000; ++i)
        {
            file >> myVocab[i].letter;
        }
    }
    for (int i = 1 ; i <= 1000 ; i++)
        cout << myVocab[i].letter << "\n" ;
    
    
    cin >> n;
    for (int i = 0 ; i < n ; i++)
    {
        randomNum = (rand() % 1000); // generate number from 0 -999
        cout << randomNum << " ";
        cout << myVocab[randomNum].letter << "\n";
        
    }
    
}
