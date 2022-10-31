/* File: i_o.c */
/* Implementasi Input / Output */

#include <stdio.h>
#include "i_o.h"



void configMakanan(char *filename, MAKANAN *makanan);
/* Membaca file figurasi config dan membaca makanan */
/* I.S. Makanan sembarang */
/* F.S. Makanan terdefinisi dari file */


void configMap(char *filename, MAP *peta){
    /* Membaca file figurasi config dan membaca map */
    /* I.S. Map sembarang */
    /* F.S. Map terdefinisi dari file */
    /* Prekondisi: filename pasti valid dan exist */
    // KAMUS LOKAL
    int M[2], i;
    // ALGORITMA
    ADVFile(filename);
    i = 0;
    while (currentChar != LINEMARK) {
        int value = 0;
        while (currentChar != BLANK && currentChar != LINEMARK) {
            value = value * 10 + (currentChar - 48);
            ADV();
        }
        M[i] = value;
        if (currentChar == BLANK) {
            ADV();
        }
        i++;
    }    
    
    createMatrix(M[0] + 2, M[1] + 2, &(MATRIX(*peta)));
    // creating border for matrix peta
    for (int i = 0; i < M[1] + 2; i++) {
        (*peta).m.mem[0][i] = '*';
        (*peta).m.mem[M[0] + 1][i] = '*';
    }
    for (int i = 0; i < M[0] + 2; i++) {
        (*peta).m.mem[i][0] = '*';
        (*peta).m.mem[i][M[1] + 1] = '*';
    }

    ADV(); // next after LINEMARK
    while (currentChar != FILEMARK) {
        for (int i = 1; i < M[0] + 1; i++) {
            if (currentChar == LINEMARK) {
                ADV();
            }
            for (int j = 1; j < M[1] + 1; j++) {
                if (currentChar == '#') {
                    (*peta).m.mem[i][j] = BLANK;
                    ADV();
                } else {
                    (*peta).m.mem[i][j] = currentChar;
                    ADV();
                }
            }
        }
    }
    fclose(pita);
}

void configResep(char *filename, Tree *resep){
    /* Membaca file figurasi config dan membaca resep */
    /* I.S. Resep sembarang */
    /* F.S. Resep terdefinisi dari file */
    //KAMUS LOKAL
    int i,j,k;
    int nResep;
    int child[100];
    int ctr;

    nResep = 0;
    //ALGORITMA
    ADVFILE(filename);
    while(currentChar != LINEMARK){
        nResep = nResep * 10 + (currentChar - 48);
        ADV();
    }

    ADV(); // next after LINEMARK
    //Membuat array of tree
    Tree *p = (Tree) malloc(nResep*sizeof(Tree));

    for(j = 0; j < nResep; j++){
        i = 0;
        while (currentChar != BLANK)
        {
            i = i * 10 + (currentChar - 48);
            ADV();
        }
        //currentChar == BLANK
        p[j] = newTreeNode(i);
        ADV();
        
        ctr = 0;
        i = 0;
        while(currentChar != FILEMARK && currentChar != LINEMARK){
            while (currentChar != BLANK  && currentChar != LINEMARK && currentChar != FILEMARK)
                {
                i = i * 10 + (currentChar - 48);
                ADV();
                }
            //currentChar == BLANK or LINEMARK or FILEMARK
            child[ctr] = i;
            if(currentChar == BLANK){
                i = 0;
                ADV(); //Lanjut ke angka selanjutnya  
            }
        }

        addressChild(p[j]) = (Tree) malloc(ctr *sizeof(Tree));

        for(k = 0; k < ctr; k++){
            getChild(p[j],k) = newTreeNode(child[k]);
        }

        }
    
    resep = p;
    free(p);

    fclose(pita);
}


boolean validateString();
/* Mengembalikan true jika string yang dimasukkan valid */