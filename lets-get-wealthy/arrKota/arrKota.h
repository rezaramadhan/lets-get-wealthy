#ifndef ARRKOTA_H
#define ARRKOTA_H

#include "../bool/boolean.h"
#include "../str/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define KotaMax 23
#define KotaMin 1

//DEFINISI TIPE
typedef int IdxType;
typedef struct {
	char name[20]; //nama kota
	long price; //harga kota
	long sewa; //harga kota
	boolean rekreasi; //apakah sebuah kota rekreasi atau bukan
	boolean host; //apakah sebuah kota jadi host world cup atau bukan
	int blok; //masuk blok apa kotak ini
	int level; //level bangunan di kota ini. 1-3 = rumah, 4 keatas landmark
	char owner; //siapa yg punya kotak ini
} ElType;
typedef struct {
	ElType TabKota[KotaMax+1];
} Kota;

//SELEKTOR
#define NamaKota(T, i) (T).TabKota[(i)].name
#define HargaKota(T, i) (T).TabKota[(i)].price
#define IsRekreasi(T, i) (T).TabKota[(i)].rekreasi
#define IsHost(T, i) (T).TabKota[(i)].host
#define BlokKota(T, i) (T).TabKota[(i)].blok
#define LevelKota(T, i) (T).TabKota[(i)].level
#define OwnerKota(T, i) (T).TabKota[(i)].owner
#define NowKota(T, i) (T).TabKota[(i)].now
#define SewaKota(T, i) (T).TabKota[(i)].sewa


///////////////////////////////////////////////////////PRIMITIF
void tulisNominal (long l);
/*Cara panggil tulisNominal(nominalygpengenditulis)*/
/*Menulis nominal uang l dengan format: M untuk Million, dst*/

void printInfo (Kota K, char *name);
/*  I.S. K terdefinisi, name merupakan input user
    F.S. Menampilkan data kota bernama name jika name ada di tabel kota
*/

long hargaTotal(Kota K, int i);
/*Mencari nilai properti total sebuah kota*/

long hargaUpgrade(Kota K, int i);
/*Mencari harga untuk meng-upgrade sebuah kota*/

boolean IsBlokDikuasai(Kota T, int blok);
/* menghasilkan true jika suatu blok dikuasai seseorang */

void LoadKota(Kota *X, char *input);

void savekota(Kota X);

#endif
