#ifndef LISTSABOTAGE_H
#define LISTSABOTAGE_H

#include "../bool/boolean.h"
#include "../listPlayer/listPlayer.h"
#include "../str/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef int id;
typedef struct TElmtListSabotage *AddressS; //address Sabotage

typedef struct TElmtListSabotage {
	id 		 	info; //id kota yg sedang disabotage
	AddressS 	next;
} ElmtListSabotage;

typedef struct {
	AddressS		first;
} ListSabotage;


//SELEKTOR
#define FirstS(L) (L).first
#define NextS(P) (P)->next
#define IdS(P) (P)->info


boolean IsListEmptyS (ListSabotage L);

AddressS AlokasiS(id X);

void DealokasiS (AddressS *P);

void InsVFirst (ListSabotage *L, id X);

void DeleteP (ListSabotage *L, id X);

void DelVFirst (ListSabotage *L);

void DeleteAfter (ListSabotage *L, AddressS *Pdel, AddressS Prec);

AddressS SearchPrec (ListSabotage L, id X);

AddressS Search (ListSabotage L, id X);

void SabotageOff(ListPlayer *L, Kota  T, ListSabotage *LS);

void Sabotage(ListPlayer *L, char nama[4], Kota T, ListSabotage *LS);
/* Prosedur ini digunakan saat player ingin melakukan sabotase terhadap
 * suatu kota sehingga kota tersebut mati listrik dan biaya sewa bagi
 * pemain luar yang mampir di kota tsb menjadi 0.
 * I.S : Biaya sewa di suatu kota terdefinisi dan normal.
 * F.S : Biaya sewa di kota yang dimaksud pengguna menjadi 0 (berhasil
 * 		 disabotase) dan biaya sewa disimpan temporary di sewa (sewa 
 * 		 terdefinisi).
 */
 
void Shield(ListPlayer *L, char nama[4], Kota T, ListSabotage *LS);
/* Prosedur ini digunakan saat player (kemungkinan besar merupakan player
 * yang kota miliknya disabotase) ingin mengembalikan biaya sewa kotanya
 * menjadi normal kembali.
 * I.S : Biaya sewa di suatu kota 0.
 * F.S : Biaya sewa di kota yang dimaksud pengguna menjadi normal sesuai
 * 		 seharusnya (mengacu pada parameter input: sewa).
 */
 
void LoadSabotage(ListSabotage *X);

void saveosabotage(ListSabotage X);

#endif
