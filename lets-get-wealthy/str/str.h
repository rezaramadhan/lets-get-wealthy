#ifndef ReadString_H
#define ReadString_H
#include "../bool/boolean.h"
#include <stdio.h>
#include <stdlib.h>
#define Mark '\n'
#define Blank ' '
#define NMax 50

typedef struct {
	char ing[NMax];
	int len;
} Str;

#define Length(S) S.len
#define StringS(S) S.ing
#define String(S,i) S.ing[i]

char CC;
Str S;

void START();

void ADV();

boolean EOPS();

void ig_blank();

void StartS();

void AdvS();

void CopyS();

int LS (char *arg);

boolean CompS(Str S, char *arg);

void readS (int *x, char **arg);
/* Membaca sebuah string dari user, kemudian mengubahkan ke dalam bentuk command dan argumen2
 * contoh string yang dibaca adalah roll dice
 * */

#endif
