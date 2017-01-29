#ifndef LISTPLAYER_H
#define LISTPLAYER_H

#include "../bool/boolean.h"
#include "../listBoard/listBoard.h"
#include "../arrKota/arrKota.h"
#include "../str/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//KONSTANTA
#define Nil NULL
#define BlokMax 8
#define LamaPenjara 4

//DEFINISI TIPE
typedef struct {
	int TabBlok[BlokMax+1];
} Blok; //array isi blok, ada berapa rumah di tiap blok yg dimiliki player

typedef struct {
	int FreeTax;
	int FreePrison;
	int Off;
	int Protect;
} PlayerCard; //tipe bentukan buat kartu apa aja yg dimiliki player

typedef struct TElmtListBoard *AddressB;

typedef struct {
	Blok bl; //blok yg dimiliki player
	PlayerCard c; //card yg dimiliki player
	long money; //uang player
	int jail; //apakah player masuk jail
	char playerId; //id player
	AddressB where; //player berada dimana
} InfotypePlayer;

typedef struct TElmtListPlayer *AddressP; //address player
typedef struct TElmtListPlayer {
	InfotypePlayer 	info;
	AddressP 	next;
} ElmtListPlayer;

typedef struct {
	AddressP	first;
} ListPlayer;


//SELEKTOR
#define FirstP(L) (L).first
#define NextP(P) (P)->next
#define PlayerId(P) (P)->info.playerId
#define Money(P) (P)->info.money
#define IsInJail(P) (P)->info.jail
#define Where(P) (P)->info.where
#define CardFreeTax(P) (P)->info.c.FreeTax
#define CardFreePrison(P) (P)->info.c.FreePrison
#define CardProtect(P) (P)->info.c.Protect
#define CardOff(P) (P)->info.c.Off
#define BlokPlayer(P, i) (P)->info.bl.TabBlok[(i)]

///////////////////////////////////////////////PRIMITIF
AddressP SearchPlayerid (ListPlayer Lp, char X);
/*Prekondisi: ListPlayer sudah terbentuk dgn id player a, b, c, d*/
/*Nilai X pasti terdapat di list player*/

boolean IsWin (AddressP P);
/* Fungsi untuk memeriksa apakah pemain P sudah menang.
 * kemenangan didapat jika pemain selain P memiliki
 * uang 0.  
 * */


void GoToJail (AddressP *Player, ListBoard Board);
/* I.S : Player dan Board terdefinisi
 * F.S : Memindahkan posisi Player ke Penjara dan men-set IsInJail
 *    	  Player menjadi True;
*/

boolean IsEmptyBlok(AddressP P);
/* Fungsi untuk memeriksa apakah pemain P memiliki kota
 * atau tidak.
 * */
 
void rolldice(ListBoard *B, ListPlayer *P, boolean *same);
/*  I.S. B dan P terdefinisi, same sembarang
    F.S. Memperbaharui P setelah pemain mengocok dadu yaitu mengubah Where(FirstP(P));
         Same menghasilkan true jika kedua mata dadu menghasilkan nilai yang sama
*/
void leaderBoard(ListPlayer L, Kota K);
/*  I.S. L dan K terdefinisi
    F.S. Menampilkan kondisi ranking semua pemain dan asset total mereka
*/

void buy (char Pid, ListPlayer *LP, Kota *K, ListBoard LB);
/*PA adalah address player yg membeli bangunan*/
/*Membeli (baik secara paksa atau tidak) petak yg sedang ditempati player*/
/*I.S. Semua terdefinisi, petak yg dibeli bukan petak rekreasi (CEK DI PEMANGGILAN!)*/
/*I.S. Petak dibeli oleh player jika syarat terpenuhi, dan jika tidak terpenuhi maka tidak*/

void sellBank (ListPlayer *Lp, char Pid, Kota *K, ListBoard Lb, char* namakota);
/*Menyimpan petak dengan nama namakota ke list offered*/

void upgrade (char idP, ListPlayer *LP, ListBoard Lb, Kota *K);
/*Mengupgrade petak yang sedang "dipijak" oleh player*/
/*Menampilkan pesan kesalahan jika mengupgrade petak gagal*/

void PayWhenVisit(ListPlayer *L, Kota *T, ListBoard Board);
/* Player membayar uang sewa ketika sampai di petak milik
 * player lain dan petak tersebut tidak sedang disabotage
 * */

void BonusUang (AddressP *Player);
/*    I.S : Player terdefinisi.
 *    F.S    : Uang Player akan bertambah secara acak dengan nominal 100K,
 *    	   200K, dan 300K. Kemudian menampilkan pesan sesuai format.
*/

void Pajak (AddressP *Player);
/*    I.S : Player terdefinisi.
 *    F.S    : Uang Player akan berkurang sebanyak 10% dari uang total
 *    	   yang dimiliki Player. Kemudian menampilkan pesan sesuai
 *    	   format.
*/

void Travel (char *kota, AddressP *Player, ListBoard Board, Kota K);
/*    I.S : kota, player, board, K terdefinisi
 *     F.S : Memindahkan posisi Player ke kota. Search Board dgn
 *    	   nama kota board = *kota.
*/

AddressP LastP (ListPlayer L) ;
/*	I.S. sembarang
	F.S. Mengirim address terakhir dari List. Jika List kosong, kembalikan Nil.
*/

boolean IsListEmptyP (ListPlayer L);
/* Mengirim true jika list kosong */

void InsVLastP (ListPlayer *L, InfotypePlayer X);
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen list di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/

void InsertFirstP (ListPlayer *L, AddressP P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/

void InsertAfterP (ListPlayer *L, AddressP P, AddressP Prec);
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir, P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
void InsertLastP (ListPlayer *L, AddressP P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/

AddressP AlokasiP (InfotypePlayer X) ;
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/

void InisiasiPlayer (int JmlPlayer, ListPlayer *LP, ListBoard LB);
/* Inisiasi Pemain sejumlah JmlPlayer */

void LoadPlayer(ListPlayer *X,ListBoard L);

void printIsiL (Kota K, ListPlayer P, int num, int id, AddressB AB, char *Sp[]);

void printL (Kota K, ListPlayer P, ListBoard B);

void Board (Kota K, ListPlayer P, ListBoard B);

void saveplayer(ListPlayer LP, ListBoard LB);

void Host (char *kota, Kota *City, ListBoard Board, AddressP *Play);
/* I.S    : Kota terdefinisi.
 * F.S    : Traversal ke semua Board, jika petak bukan spesial dan
 *    	   NamaKota = kota, maka IsHost = true, dan kota lainnya
 *    	   IsHost = false, karena tidak mungkin ada dua Host dalam
 *    	   waktu yg bersamaan.
*/

#endif
