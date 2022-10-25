/* File: wordmachine.c */
/* Realisasi Word Machine: Model Akuisisi Versi I */

#include <stdio.h>
#include <stdlib.h>
#include "../boolean/boolean.h"
#include "../charmachine/charmachine.h"
#include "wordmachine.h"

/* State Mesin Word */
boolean endWord;
Word currentWord;

void IgnoreBlanks(){
/* Mengabaikan satu atau beberapa BLANK
    I.S. : currentChar sembarang
    F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while(currentChar == BLANK){
        ADV();
    }
}

void STARTWORD(){
/* I.S. : currentChar sembarang
    F.S. : EndWord = true, dan currentChar = MARK;
            atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
            currentChar karakter pertama sesudah karakter terakhir kata */
    START();
    IgnoreBlanks();
    if(currentChar == MARK){
        endWord = true;
    }
    else{
        endWord = false;
        CopyWord();
    }
}

void ADVWORD(){
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
    F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
            currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
            Jika currentChar = MARK, EndWord = true.
    Proses : Akuisisi kata menggunakan procedure SalinWord */
    IgnoreBlanks();
    if (currentChar == MARK){
        endWord = true;
    }
    else{
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord(){
/* Mengakuisisi kata, menyimpan dalam currentWord
    I.S. : currentChar adalah karakter pertama dari kata
    F.S. : currentWord berisi kata yang sudah diakuisisi;
            currentChar = BLANK atau currentChar = MARK;
            currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
            Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    int i;
    i=0;
    while((currentChar != MARK) && (currentChar != BLANK)){
        if(i<50){
            currentWord.TabWord[i] = currentChar;
            i++;
        }
        ADV();
    }
    currentWord.Length = i;
}