#include "stack.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty(Stack *S) {
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */
    Top(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty(Stack S) {
/* Mengirim true jika Stack kosong: lihat definisi di atas */
    return Top(S) == Nil;
}
boolean IsFull(Stack S) {
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
    return Top(S) == MaxEl - 1;
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push(Stack * S, infotype X) {
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
    if (IsEmpty(*S)) {
        Top(*S) = 0;
    }
    else {
        Top(*S)++;
    }
    InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop(Stack * S, infotype* X) {
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    *X = InfoTop(*S);
    if (Top(*S) == 0) {
        Top(*S) = Nil;
    } else {
        Top(*S)--;
    }
}

void Undo(Stack *S1, Stack *S2) {
/* Menghapus Top dari Stack S1 dan menambahkannya ke S2 */
/* I.S. S1 tidak kosong, S1 adalah Undo Stack, S2 adalah Redo Stack */
/* F. S. */
    int temp;
    // Proses undo
    Push(S2, InfoTop(*S1));
    Pop(S1, &temp);
}

void Redo(Stack *S1, Stack *S2) {
/* Menghapus Top dari S2 dan menambahkannya ke S1 */
/* I.S. S2 tidak kosong, S1 adalah Undo Stack, S2 adalah Redo Stack */
/* F. S. */
    int temp;
    // Proses redo
    Push(S1, InfoTop(*S2));
    Pop(S2, &temp);
}
