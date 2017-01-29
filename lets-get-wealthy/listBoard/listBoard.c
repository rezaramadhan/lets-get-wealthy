#include "listBoard.h"
#include <time.h>

AddressB SearchNamaKota (ListBoard Lb, Kota K, char* X)
/*Prekondisi: ListPlayer sudah terbentuk*/
/*Kota mungkin tidak ada*/
{
	AddressB Pa = FirstB(Lb);
	boolean found = false;
	
	while (NextB(Pa) != FirstB(Lb) && !found) {
		found = !IsSpecial(Pa) && strcmp(X, (NamaKota(K, PetakId(Pa)))) == 0;
		if (!found)
			Pa = NextB(Pa);
	}
	if (NextB(Pa) == FirstB(Lb))
		found = strcmp(X, (NamaKota(K, PetakId(Pa)))) == 0;

	if (found)
		return Pa;
	else
		return Nil;
}

AddressB SearchNum (ListBoard L, int X){
/*	Mencari apakah ada elemen list dengan Number(P) = X
	Jika ada, mengirimkan Address elemen tersebut
	Jika tidak ada, mengirimkan Nil
*/
	//KAMUS
	AddressB P;
	boolean f;
	//ALGORITMA
	P = FirstB(L);
	f = false;
	while ((P != Nil)&&(!f)) {
		if (Number(P) == X) {
			f = true;
		} else {
			P = NextB(P);
		}
	}
	
	return P;
}

boolean IsPassStart (AddressB Before, AddressB After){
/* Fungsi untuk memeriksa apakah pemain melewati Start
 * atau tidak. Before adalah posisi pemain SEBELUM melempar
 * dadu dan after adalah posisi pemain SETELAH melempar dadu
 * */
 
    if ((Number(After) - Number(Before)) < 0 ) {
   	 return true;
    } else {
   	 return false;
    }

}

boolean IsPassWC (AddressB Before, AddressB After){
/* Fungsi untuk memeriksa apakah pemain melewati petak
 * World Cup. Before adalah posisi pemain SEBELUM melempar
 * dadu dan after adalah posisi SETELAH melempar dadu
 * */
	
    if ((Number(Before)<16)&&(Number(After)>=16)) {
   	 return true;
    } else {
   	 return false;
    }
}

AddressB AlokasiB (InfotypeBoard X) {
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/
	//KAMUS
	AddressB P;
	
	//ALGORITMA
	P = (AddressB) malloc (sizeof(ElmtListBoard));
	
	if (P == Nil) {
		return Nil;
	} else {
		Number(P) = X.number;
		PetakId(P) = X.idPetak;
		IsSpecial(P) = X.special;
		NextB(P) = Nil;
		return P;
	}
}

boolean IsListEmptyB (ListBoard L){
/* Mengirim true jika list kosong */
	boolean empty;
	
	if (FirstB(L) == Nil) {
		empty = true;
	} else {
		empty = false;
	}
	
	return empty;
}

AddressB LastB(ListBoard L) {
/*	I.S. sembarang
	F.S. Mengirim address terakhir dari List. Jika List kosong, kembalikan Nil.
*/
	AddressB P;
	
	if (IsListEmptyB(L)) {
		return Nil;
	} else {
		P = FirstB(L);
		while (NextB(P)!= FirstB(L)) {
			P = NextB(P);
		}
		return P;
	}
}
void InsertFirstB (ListBoard *L, AddressB P) {
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/
	if (IsListEmptyB(*L)) {
		NextB(P) = P;
	} else {
		NextB(P) = FirstB(*L);
		NextB(LastB(*L)) = P;
	}
	FirstB(*L) = P;
}

void InsertAfterB (ListBoard *L, AddressB P, AddressB Prec) {
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir, P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
	NextB(P) = NextB(Prec);
	NextB(Prec) = P;
}
void InsertLastB (ListBoard *L, AddressB P) {
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/
	if (IsListEmptyB(*L)) {
		InsertFirstB(L, P);
	} else {
		InsertAfterB(L, P, LastB(*L));
	}
}

void InsVLastB (ListBoard *L, InfotypeBoard X) {
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen list di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/
	AddressB P;
	
	P = AlokasiB(X);
	if (P != Nil) {
		InsertLastB(L, P);
		NextB(LastB(*L)) = FirstB(*L);
	}
	
}

void InisiasiBoard (ListBoard *LB) {
	int i=0, idptk=1;
	InfotypeBoard Xb;
	
	FirstB(*LB) = Nil;
	
	for (i=0; i<=31; i++){
		//Inisiasi Petak Spesial
		Xb.number = i;
		if (i == 0 || i == 2 || i == 8 || i == 12 || i == 16 || i == 20 || i == 24 || i == 28 || i == 30) {
			Xb.special = true;
			//Inisiasi IdBoard
			if (i == 0) {
				Xb.idPetak = 0; //start
			} else if (i == 2) {
				Xb.idPetak = 1; //bonus
			}else if (i == 8) {
				Xb.idPetak = 2; //deserted island
			}else if (i == 12 || i == 20 || i == 28) {
				Xb.idPetak = 3; //chance
			} else if (i == 16) {
				Xb.idPetak = 4; //world cup
			} else if (i == 24) {
				Xb.idPetak = 5; //world travel
			} else if (i == 30) {
				Xb.idPetak = 6; //tax
			}
			
			InsVLastB(LB, Xb);
			
		} else {
			Xb.number = i;
			Xb.idPetak = idptk;
			Xb.special = false;
			InsVLastB(LB, Xb);
			
			idptk++;
		}
	}
}






