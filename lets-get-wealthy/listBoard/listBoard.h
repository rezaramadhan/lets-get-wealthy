#ifndef LISTBOARD_H
#define LISTBOARD_H

#include "../arrKota/arrKota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Nil NULL

//DEFINISI TIPE
typedef struct {
	int number; //nomer si petak
	int idPetak; //id petak
	boolean special; //apakah petak itu spesial atau tidak
} InfotypeBoard;

typedef struct TElmtListBoard *AddressB; //address board

typedef struct TElmtListBoard {
	InfotypeBoard	info;
	AddressB 	next;
} ElmtListBoard;

typedef struct {
	AddressB		first;
} ListBoard;


//SELEKTOR
#define FirstB(L) (L).first
#define NextB(P) (P)->next
#define Number(P) (P)->info.number
#define PetakId(P) (P)->info.idPetak
#define IsSpecial(P) (P)->info.special

///////////////////////////////////////////////PRIMITIF

boolean IsPassStart (AddressB Before, AddressB After);
/* Fungsi untuk memeriksa apakah pemain melewati Start
 * atau tidak. Before adalah posisi pemain SEBELUM melempar
 * dadu dan after adalah posisi pemain SETELAH melempar dadu
 * */
 
boolean IsPassWC (AddressB Before, AddressB After);
/* Fungsi untuk memeriksa apakah pemain melewati petak
 * World Cup. Before adalah posisi pemain SEBELUM melempar
 * dadu dan after adalah posisi SETELAH melempar dadu
 * */


AddressB SearchNamaKota (ListBoard Lb, Kota K, char* X);
/*Prekondisi: ListPlayer sudah terbentuk*/
/*Kota mungkin tidak ada*/

AddressB SearchNum (ListBoard L, int X);
/*	Mencari apakah ada elemen list dengan Number(P) = X
	Jika ada, mengirimkan Address elemen tersebut
	Jika tidak ada, mengirimkan Nil
*/

AddressB LastB(ListBoard L) ;
/*	I.S. sembarang
	F.S. Mengirim address terakhir dari List. Jika List kosong, kembalikan Nil.
*/

boolean IsListEmptyB (ListBoard L);
/* Mengirim true jika list kosong */

void InsVLastB (ListBoard *L, InfotypeBoard X);
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen list di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/

void InsertFirstB (ListBoard *L, AddressB P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/

void InsertAfterB (ListBoard *L, AddressB P, AddressB Prec);
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir, P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
void InsertLastB (ListBoard *L, AddressB P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/

AddressB AlokasiB (InfotypeBoard X);
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/

void InisiasiBoard (ListBoard *LB);
/* Inisiasi Board jika pemain ingin New game */ 

#endif
