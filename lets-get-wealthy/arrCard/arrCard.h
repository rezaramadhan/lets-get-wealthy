#ifndef ARRCARD_H
#define ARRCARD_H

#include "../bool/boolean.h"
#include "../listPlayer/listPlayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define CardMax 25
#define CardMin 1

//TIPE2
typedef int IdxType;
typedef struct {
	long value;
	boolean taken;
	char type;
} ElTypeCard;
typedef struct {
	ElTypeCard TabCard[CardMax+1];
} Card;

//SELEKTOR
#define CardVal(T, i) (T).TabCard[i].value
#define CardType(T, i) (T).TabCard[i].type
#define IsTaken(T, i) (T).TabCard[i].taken

//////////////////////////////////////////////PRIMITIF
void InisiasiChance (Card *Chance);
/* Inisiasi kartu chance */

void KartuChance (AddressP *Player, Card *Kartu, ListBoard Board);
/*     I.S : sembarang, Player adalah pemain yang mendapat chance,
 *    	   Card adalah container yang menyimpan kartu kesempatan.
    F.S : semua PlayerCard Player ditambah 1 dan container
    *       Card dikurangi 1, sesuai dengan hasil pengacakan. Jika
    *       mendapat kartu masuk penjara, panggil fungsi GoToJail yang
    *       akan merubah posisi Player ke penjara dan men-set IsInJail
    *       Player menjadi True.
*/

void FreeTax(ListPlayer *L, boolean *applyfreetax, Card *T, ListBoard Board);
/* Prosedur ini merupakan pengaplikasian kartu chance Free Tax oleh player
 * yang memilik kartu tersebut dan memasukan command yang tepat.
 * I.S : Player berada di petak pajak dan diharuskan membayar pajak
 * F.S : Player dibebaskan dari pajak dan kartu bebas pajak milik player
 * 		 berkurang 1, applyfreetax bernilai true jika penggunaan kartu
 * 		 berhasil.
 */
 
void FreeJail(ListPlayer *L, Card *T);
/* Prosedur ini digunakan saat player dipenjara dan ingin terbebas darinya
 * I.S : Player berada di deserted island dan tidak bisa bepergian saat
 * 		 gilirannya tiba
 * F.S : Player dibebaskan dari penjara (bisa bepergian saat gilirannya
 * 		 tiba), kartu bebas penjara milik player berkurang satu dan 
 * 		 applyfreejail bernilai true jika penggunaan kartu tersebut berhasil
 */
 


#endif
