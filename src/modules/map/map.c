#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "../i_o/i_o.h"


/* Loader */
void createMap(MAP *M)
/* I.S. map sembarang */
/* F.S. map dengan ukuran row x col terbentuk */
{
    ROW_MAP(*M) = IDX_UNDEF;
    COL_MAP(*M) = IDX_UNDEF;
    int i,j;
    for (i = 0; i < 50; i++)
    {
        for (j = 0; j < 50; j++)
        {
            ElmtMap(*M,i,j) = '*';
        }
    }
    Absis(S(*M))=IDX_UNDEF;
    Ordinat(S(*M))=IDX_UNDEF;
}

void loadMap(MAP *M, char *filename)
/* I.S. map sembarang */
/* F.S. map terbentuk dari file eksternal */
{
    ADVFILE("peta.txt");
    int i = 0;
    int s[2];
    while (currentChar != LINEMARK) {
        int value = 0;
        while (currentChar != BLANK && currentChar != LINEMARK) {
            value = value * 10 + (currentChar - 48);
            ADV();
        }
        s[i] = value;
        if (currentChar == BLANK) {
            ADV();
        }
        i++;
    }    
    
    createMatrix(s[0] + 2, s[1] + 2, &MATRIX(*M));
    // creating border for matrix peta
    for (int i = 0; i < s[1] + 2; i++) {
        (*M).m.mem[0][i] = '*';
        (*M).m.mem[s[0] + 1][i] = '*';
    }
    for (int i = 0; i < s[0] + 2; i++) {
        (*M).m.mem[i][0] = '*';
        (*M).m.mem[i][s[1] + 1] = '*';
    }

    ADV(); // next after LINEMARK
    while (currentChar != FILEMARK) {
        for (int i = 1; i < s[0] + 1; i++) {
            if (currentChar == LINEMARK) {
                ADV();
            }
            for (int j = 1; j < s[1] + 1; j++) {
                if (currentChar == '#') {
                    (*M).m.mem[i][j] = BLANK;
                    ADV();
                } else if (currentChar != 'S') {
                    (*M).m.mem[i][j] = currentChar;
                    ADV();
                } else {
                    (*M).m.mem[i][j] = BLANK;
                    Absis(S(*M)) = i-1;
                    Ordinat(S(*M)) = j-1;
                    ADV();
                }
            }
        }
    }
    fclose(pita);
}
/* Validator */
boolean isEmptyMap(MAP M)
/* Mengembalikan true jika map kosong */
{
    return (ROW_MAP(M) == IDX_UNDEF && COL_MAP(M) == IDX_UNDEF);
}

boolean isIdxMapValid(int i, int j)
/* Mengembalikan true jika indeks map valid */
{
    return (i > IDX_MIN && i <= CAPACITYMAP && j > IDX_MIN && j <= CAPACITYMAP);
}

boolean isIdxMapEff(MAP M, int i, int j)
/* Mengembalikan true jika indeks map efektif */
{
    return (i > IDX_MIN && i <= ROW_MAP(M) && j > IDX_MIN && j <= COL_MAP(M));
}

void printMap(MAP M)
/* I.S. map terdefinisi */
/* F.S. map ditampilkan ke layar */
{
    for (int i = 0; i < ROW_MAP(M); i++) {
        for (int j = 0; j < COL_MAP(M); j++) {
            if (i == Absis(S(M)) + 1 && j == Ordinat(S(M)) + 1) {
                printf("S ");
            } else {
                printf("%c ", ElmtMap(M, i, j));
            }
        }
        printf("\n");
    } 
}

boolean isNear(MAP M, char ch) {
// /* Mengembalikan true jika ada bangunan dengan karakter ch yang berdekatan dengan bangunan lain */
// {
//     if(Absis(S(M)) != 0){
//         if(ElmtMap(M, (int)Absis(S(M))-1, (int)Ordinat(S(M))) == ch){
//             return true;
//         }
//     }

//     if(Absis(S(M)) != ROW_MAP(M)){
//         if(ElmtMap(M, (int)Absis(S(M))+1, (int)Ordinat(S(M))) == ch){
//             return true;
//         }
//     }

//     if(Ordinat(S(M)) != 0){
//         if(ElmtMap(M, (int)Absis(S(M)), (int)Ordinat(S(M))-1) == ch){
//             return true;
//         }
//     }

//     if(Ordinat(S(M)) != COL_MAP(M)-1){
//         if(ElmtMap(M, (int)Absis(S(M)), (int)Ordinat(S(M))+1) == ch){
//             return true;
//         }
//     }

//     return false;
    if (ElmtMap(M, (int)Absis(S(M)) + 1, (int)Ordinat(S(M))) == ch ||
        ElmtMap(M, (int)Absis(S(M)), (int)Ordinat(S(M)) + 1) == ch ||
        ElmtMap(M, (int)Absis(S(M)) + 1, (int)Ordinat(S(M)) + 2) == ch ||
        ElmtMap(M, (int)Absis(S(M)) + 2, (int)Ordinat(S(M)) + 1) == ch) {
            return true;
    } else {
        return false;
    }
}

void move_map(MAP *M, Word command) 
/* I.S. map terdefinisi */
/* F.S. map bergerak sesuai dengan command */
{
    if(same(command, "NORTH") || same(command, "MOVE NORTH")){
        if(ElmtMap(*M, (int)Absis(S(*M)), (int)Ordinat(S(*M))+1) == ' '){
            Absis(S(*M))--;
            printf("%d",Absis(S(*M)));
        }
    }
    else if(same(command, "SOUTH") || same(command, "MOVE SOUTH")){
        if(ElmtMap(*M, (int)Absis(S(*M))+2, (int)Ordinat(S(*M))+1) == ' '){
            Absis(S(*M))++;
        }
    }
    else if(same(command, "EAST") || same(command, "MOVE EAST")){
        if(ElmtMap(*M, (int)Absis(S(*M))+1, (int)Ordinat(S(*M))+2) == ' '){
            Ordinat(S(*M))++;
        }
    }
    else if(same(command, "WEST") || same(command, "MOVE WEST")){
        if(ElmtMap(*M, (int)Absis(S(*M))+1, (int)Ordinat(S(*M))) == ' '){
            Ordinat(S(*M))--;
        }
    }
}

int move_detector(Word command){
/* Mengembalikan nilai base dari command move */
/* Prekondisi: command move terdefinisi dan tidak kosong */
    if(same(command, "WEST") || same(command, "MOVE WEST")){
        return 1;
    }
    else if(same(command, "SOUTH") || same(command, "MOVE SOUTH")){
        return 2;
    }
    else if(same(command, "EAST") || same(command, "MOVE EAST")){
        return 3;
    }
    else if(same(command, "NORTH") || same(command, "MOVE NORTH")){
        return 4;
    }
    else{
        return 0;
    }
}
