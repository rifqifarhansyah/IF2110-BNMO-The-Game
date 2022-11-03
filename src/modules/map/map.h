#ifndef MAP_H
#define MAP_H

#include "../boolean/boolean.h"
#include "../point/point.h"
#include "../matriks/matriks.h"
#include "../list/liststatik.h"
#include "../wordmachine/wordmachine.h"
#include "../simulator/simulator.h"

/* *** Definisi BATASAN MAP *** */
#define CAPACITYMAP 100
#define IDX_MIN 0
#define IDX_UNDEF -1
#define ROW_MIN 10
#define ROW_MAX 50
#define COL_MIN 10
#define COL_MAX 50

/* *** Definisi TYPE MAP *** */
typedef struct {
    Matrix m;
    ListStatik Lokasi; 
    ListStatik ListBuilding;
    SIMULATOR sim;
} MAP;

/* *** Notasi Akses: selektor MAP *** */
#define WIDTH(P) (P).(m).colEff
#define HEIGHT(P) (P).(m).rowEff
#define MATRIX(P) (P).m

/* *** Selektor: Untuk sebuah MAP M yang terdefinisi: *** */
#define ROW_MAP(M) (M).m.rowEff
#define COL_MAP(M) (M).m.colEff
#define ElmtMap(M,i,j) ELMT((M).m, (((M).sim.LOCATION).X-1), (((M).sim.LOCATION).Y))
#define S(m) (m).sim.LOCATION

/* Loader */
void createMap(MAP *M);
/* I.S. map sembarang */
/* F.S. map dengan ukuran row x col terbentuk */
void loadMap(MAP *M, char *filename);
/* I.S. map sembarang */
/* F.S. map terbentuk dari file eksternal */

/* Validator */
boolean isEmptyMap(MAP M);
/* Mengembalikan true jika map kosong */
boolean isIdxMapValid(int i, int j);
/* Mengembalikan true jika indeks map valid */
boolean isIdxMapEff(MAP M, int i, int j);
/* Mengembalikan true jika indeks map efektif */
void printMap(MAP M);
/* I.S. map terdefinisi */
/* F.S. map ditampilkan ke layar */
boolean isNear(MAP M, char ch);
/* Mengembalikan true jika ada bangunan dengan karakter ch yang berdekatan dengan bangunan lain */
boolean move_map(MAP *M, Word command);
/* I.S. map terdefinisi */
/* F.S. map bergerak sesuai dengan command */

#endif