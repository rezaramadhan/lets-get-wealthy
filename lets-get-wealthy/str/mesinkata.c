/*
*	NIM/Nama 	:
*	Nama file 	:
*	Topik 		:
*	Tanggal 	:
*	Deskripsi 	:
*/

#include "mesinkata.h"

//primitif-primitif mesin kata
void Ignore_Blank() {
/*	Mengabaikan satu atau beberapa BLANK
	I.S. : CC sembarang
	F.S. : CC != BLANK atau CC == MARK
*/
	//ALGORITMA
	while (!EOP() && (CC==BLANK)) {
		ADV();
	}
	if (EOP())
		EndKata=true;
}

void STARTKATA(char *filename) {
/*	I.S. : CC sembarang
	F.S  : Salah satu dari dua kondisi dibawah.
		1. EndKata = true dan CC == Mark
		2. EndKata = false, CKata adalah kata yang sudah diakuisisi, dan CC adalah satu karakter setelah karakter terakhir kata

		Keterangan: CC mengacu pada yang disebut pada mesinkarakter
*/
	//ALGORITMA
	START(filename);
	if (!EOP()) {
		EndKata=false;
		Ignore_Blank();
		SalinKata();
	}
	else {
		EndKata=true;
	}
}

void ADVKATA() {
/*	I.S. : EndKata = false; CC adalah karakter sesudah karakter terakhir
	dari kata yg sudah diakuisisi
	F.S. : Jika CC = MARK, maka EndKata = true
	atau EndKata = false, CKata adalah kata terakhir yang sudah diakuisisi;
	CC karakter pertama sesudah karakter terakhir kata
*/
	//ALGORITMA
	if (CC==MARK) {
		EndKata=true;
		int i;
		for (i=0; i<CKata.Length; i++)
			CKata.TabKata[i]='\0';
	}
	else {
		Ignore_Blank();
		SalinKata();
	}
}

void SalinKata() {
/*	Mengakuisisi kata, menyimpan dalam CKata
	I.S. : CC adalah karakter pertama dari kata
	F.S. : CKata berisi kata yang sudah diakuisisi, jika karakternya melebihi
	NMax, sisa "kata" dibuang; CC = BLANK atau CC = MARK; CC adalah
	karakter sesudah karakter terakhir yang diakuisisi
*/
	//KAMUS LOKAL
	int i;
	//ALGORITMA

	//reset CKata terlebih dahulu
	for (i=0; i<NMax; i++)
		CKata.TabKata[i]='\0';
	CKata.Length=0;
	while ((CC!=BLANK) && !EOP()) {
		if (CKata.Length<NMax) {
			CKata.Length+=1;
			CKata.TabKata[CKata.Length-1] = CC;
		}
		ADV();
	}
	if (EOP())
		EndKata = true;
}

long bil(char c) {
/*	Mengembalikan nilai bilangan dari CKata
*/
	return c - '0';

}
