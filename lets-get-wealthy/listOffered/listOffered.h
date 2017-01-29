#ifndef LISTOFFERED_H
#define LISTOFFERED_H

#include "../bool/boolean.h"
#include "../listPlayer/listPlayer.h"
#include "../str/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef int id;
typedef struct TElmtListOffered *AddressO; //address offered

typedef struct TElmtListOffered {
	id 		 	info; //id kota yg di offer
	AddressO 	next;
} ElmtListOffered;

typedef struct {
	AddressO		first;
} ListOffered;


//SELEKTOR
#define FirstO(L) (L).first
#define NextO(P) (P)->next
#define Id(P) (P)->info

/////////////////////////////////////////////////PRIMITIF
boolean isEmptyO (ListOffered Lo);
//mengembalikan seperti biasa

AddressO AlokasiO (id X);
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/

void DealokasiO (AddressO *P);
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/

void DeleteAfterO (ListOffered *L, AddressO *Pdel, AddressO Prec);
/*	I.S. List tidak kosong. Prec adalah anggota list L.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen list yang dihapus
*/

void DeleteFirstO (ListOffered *L, AddressO *P);
/*	I.S. List tidak kosong
	F.S. P adalah alamat elemen pertama list sebelum penghapusan
	Elemen list berkurang satu (mungkin menjadi kosong)
	First element yang baru adalah suksesor elemen pertama yang lama
*/

void InsertFirstO (ListOffered *L, AddressO P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/

void buyOffered(char Pid, ListPlayer *P, Kota *K, ListOffered *Lo, char* namakota);
/*Membeli sebuah kota dari list offered*/
/*I.S. List Offered tidak kosong*/
/*F.S. Kota dibeli jika uang player cukup*/

void sellOffered (ListPlayer Lp, char Pid, Kota K, ListBoard Lb, char* namakota, ListOffered *Lo);
/*Menyimpan petak dengan nama namakota ke list offered*/

void showOffered (ListOffered Lo, Kota K);
/*Menuliskan isi dari List offered*/

void Loadoffered(ListOffered *X);

void saveoffered(ListOffered X);
#endif
