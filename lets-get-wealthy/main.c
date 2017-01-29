#include "bool/boolean.h"
#include "arrKota/arrKota.h"
#include "arrCard/arrCard.h"
#include "listBoard/listBoard.h"
#include "listPlayer/listPlayer.h"
#include "listOffered/listOffered.h"
#include "listSabotage/listSabotage.h"
#include "str/str.h"
#include "str/mesinkata.h"

void WhatHappened(ListPlayer *L, Kota Tkota, Card *Tcard, ListBoard Board, ListSabotage LS);

void playing (ListPlayer *LP, ListOffered *LO, ListBoard *LB, ListSabotage *LS, Kota *K, Card *C);
/* I.S. Semua terdefinisi dan tidak kosong
 * F.S. Memainkan game monopoli klasik mulai dari roll dice diulang sampai
 * 		hanya satu pemain yang memiliki harta benda, pemain lain bangkrut
 * 		definisi bangkrut adalah tidak memiliki uang sama sekali dan tidak memiliki
 * 		properti apapun*/

void doCommand (int i, char *arg, ListPlayer *LP, ListOffered *LO, ListBoard *LB, ListSabotage *LS, Kota *K, Card *C, boolean *h);
/* Melakukan command-command tertentu sesuai input player seperti buy, sell, dll
 * */

void Init (ListPlayer *LP, ListBoard *LB, ListOffered *LO, ListSabotage *LS, Kota *K, Card *C);
/* Melakukan inisialisasi permainan */

void Loadall(Kota *X, ListPlayer *P, ListBoard *B, ListOffered *O, ListSabotage *S);
/* Meload semua data yang telah disimpan sebelumnya*/
void Help ();
/* Petunjuk bantuan */

void SaveAll(Kota X, ListPlayer P, ListBoard B, ListOffered O, ListSabotage S);

void NextTurn(ListPlayer *LP, Card *C);


int main () {
	Kota K;
	ListBoard LB;
	ListPlayer LP;
	ListSabotage LS;
	ListOffered LO;
	Card C;
	Init(&LP, &LB, &LO, &LS, &K, &C);
	playing(&LP, &LO, &LB, &LS, &K, &C);
return 0;
}

void Init (ListPlayer *LP, ListBoard *LB, ListOffered *LO, ListSabotage *LS, Kota *K, Card *C)
/* Melakukan inisialisasi permainan */
//ngasih welcome screen
//new, load
//load nama file :
//start : load file init, minta jumlah pemain
//inisialisasi duit;
{
	//KAMUS LOKAL
	int pilihan, jumlahply;
	//AddressP Pp;


	//ALGORITMA
	//WELCOME SCREEN
	printf("====================================================\n");
	printf("====================================================\n");
	printf("================ LET'S GET WHEALTY =================\n");
	printf("====================================================\n");
	printf("====================================================\n");
	printf("\n\n");
	printf("Main menu : \n");
	printf("1. New Game \n");
	printf("2. Load Game \n");
	do {
		printf("Masukkan pilihan Anda (1/2) : "); scanf("%d", &pilihan);
		if ((pilihan != 1)&&(pilihan != 2)) {
			printf("Input pilihan salah. Coba lagi...\n");
		}
	} while ((pilihan != 1)&&(pilihan != 2));

	if (pilihan == 1) {
		InisiasiBoard(LB); //inisiasi board
		//Input jumlah pemain.
		do {
			printf("Masukkan jumlah pemain (2-4) : "); scanf("%d", &jumlahply);
			if ((jumlahply >4) || (jumlahply <2)) {
				printf("Jumlah pemain antara 2 sampai 4\n");
			}
		} while ((jumlahply > 4) || (jumlahply < 2));

		InisiasiPlayer(jumlahply, LP, *LB);

		//Inisiasi List Sabotage
		FirstS(*LS) = Nil;

		//Inisiasi List Offered
		FirstO(*LO) = Nil;

		//Inisiasi Chance
		InisiasiChance(C);
		//Inisiasi Kota
		LoadKota(K, "kotaawal.txt");
		printf("\n> Permainan akan segera dimulai, gunakan command 'help' untuk bantuan\n\n\n");
	} else {
		Loadall(K, LP, LB, LO, LS);
		printf("\n> Permainan akan segera dimulai, gunakan command 'help' untuk bantuan\n\n\n");
	}
}

void Loadall(Kota *X, ListPlayer *P, ListBoard *B, ListOffered *O, ListSabotage *S)
{
	InisiasiBoard(B);
    LoadPlayer(P, *B);
    LoadKota(X, "kota.txt");
    Loadoffered(O);
    LoadSabotage(S);
}

void SaveAll(Kota X, ListPlayer P, ListBoard B, ListOffered O, ListSabotage S)
{
	savekota(X);
	saveoffered(O);
	saveosabotage(S);
	saveplayer(P, B);
}

void NextTurn(ListPlayer *LP, Card *C)
{
	char x;

	FirstP(*LP) = NextP(FirstP(*LP));
	do {
		if (IsInJail(FirstP(*LP)) > 0) {
			if (IsInJail(FirstP(*LP)) >= LamaPenjara) { //bebas dari penjara
				IsInJail(FirstP(*LP)) = 0;
				printf("\n> Player %c terbebas dari penjara pada giliran ini!\n", PlayerId(FirstP(*LP)));
				printf("  Sekarang player %c dapat melakukan permainan kembali seperti biasa\n", PlayerId(FirstP(*LP)));

			} else { //masih di penjara
				printf("\n> Player %c masih dipenjara pada giliran ini!\n", PlayerId(FirstP(*LP)));
				if (CardFreePrison(FirstP(*LP))>0) { 					//apakah mau freejail
					do {
						printf("  Apakah anda ingin menggunakan kartu bebas penjara? (y/n)");
						scanf("%c", &x);
						if (x != 'y' && x != 'Y' && x != 'N'&&x != 'n')
							printf("  Input anda tidak valid!\n");
					} while (x != 'y' && x != 'Y' && x != 'N'&&x != 'n');
					if (x == 'y' || x == 'Y') {
						FreeJail(LP, C);
						printf("  Selamat, anda telah keluar dari penjara!\n");
					}
				} else {
					do {
						printf("  Apakah player %c ingin membayar uang sebesar 300K untuk keluar dari penjara? (y/n)", PlayerId(FirstP(*LP)));
						scanf("%c", &x);
						if (x != 'y' && x != 'Y' && x != 'N'&&x != 'n')
							printf("  Input anda tidak valid!\n");
					} while (x != 'y' && x != 'Y' && x != 'N'&&x != 'n');
					if (x == 'y' || x == 'Y') {
						long price = 300000;
						if (Money(FirstP(*LP))>price) {
							Money(FirstP(*LP))-=price;
							IsInJail(FirstP(*LP)) = 0;
							printf("  Selamat, anda telah keluar dari penjara!\n");
						} else {
							printf("  Uang anda tidak cukup untuk membayar denda penjara!\n");
						}
						printf("  Uang anda sekarang adalah "); tulisNominal(Money(FirstP(*LP))); printf("\n");
					} else {
						IsInJail(FirstP(*LP))++;
						printf("> Anda tetap berada di penjara pada giliran ini\n");
						printf("  Anda harus menunggu selama %d putaran untuk keluar dari penjara\n\n", (LamaPenjara-IsInJail(FirstP(*LP))+1));
						FirstP(*LP) = NextP(FirstP(*LP));
					}
				}
			}
		}
	} while (IsInJail(FirstP(*LP)) > 0);
}
void playing (ListPlayer *LP, ListOffered *LO, ListBoard *LB, ListSabotage *LS, Kota *K, Card *C)
/* I.S. Semua terdefinisi dan tidak kosong
 * F.S. Memainkan game monopoli klasik mulai dari roll dice diulang sampai
 * 		hanya satu pemain yang memiliki harta benda, pemain lain bangkrut
 * 		definisi bangkrut adalah tidak memiliki uang sama sekali dan tidak memiliki
 * 		properti apapun*/

{
	/*KAMUS*/
	AddressP nowPlaying;
	boolean finish = false;
	boolean same = false;
	boolean hasUpgrade;
	AddressB Pthen = Nil, Pnow = Nil;
	char *arg;
	char x;

	int comm, i;

	/*ALGORITMA*/
	getchar();
	do {
		nowPlaying = FirstP(*LP);
		printf("\n> Sekarang adalah giliran pemain %c\n", PlayerId(nowPlaying));
		do {
			//rolldice
			if (same)
				printf("> Kesempatan re-roll untuk player %c!\n", PlayerId(nowPlaying));
			hasUpgrade = false;
			do {
				printf("\n>> "); readS(&comm, &arg);
				if (comm == 1) {
					Pthen = Where(FirstP(*LP));
					rolldice(LB, LP, &same);
					if (same) {
						printf("  Player %c mendapatkan kesempatan re-roll!\n", PlayerId(nowPlaying));
						printf("  Lakukan giliran seperti biasa, lalu anda akan mendapatkan kesempatan re-roll setelah endturn!\n");
					}
					Pnow = Where(FirstP(*LP));
					if (!IsSpecial(Pnow))
						printf("  Player %c tiba di %s!\n", PlayerId(nowPlaying), NamaKota(*K, (PetakId(Where(nowPlaying)))));
				} else if (comm == 24)
					Help();
				else if (comm == 0) {
					printf("> Perintah yang anda masukkan tidak valid!\n");
					printf("  Silakan masukan perintah lainnya\n"); }
				else
					printf("> Anda harus melakukan roll dice sebelum anda melakukan command lain!\n");
			} while  (comm != 1);
			//ceklewatstart && lewatwc
			if (IsPassStart(Pthen, Pnow)) {
				printf("  Selamat anda telah melewati start!\n");
				BonusUang(&FirstP(*LP));
				//delete dari list sabotage
			}
			if (IsPassWC(Pthen, Pnow)) {
				for (i = KotaMin; i<=KotaMax; i++) {
					if (IsHost(*K, i)) {
						printf("  Anda telah melewati petak world cup!\n");
						printf("  Kota %s tidak lagi menjadi host world cup!\n\n", NamaKota(*K, i));
					}
					IsHost(*K, i) = false;
				}
			}
			//whathappened
			WhatHappened(LP, *K, C, *LB, *LS);
			do {
				//readinput
				printf("\n>> "); readS(&comm, &arg);
				//docommand
				if (comm >= 1 && comm <= 24)
					doCommand(comm, arg, LP, LO, LB, LS, K, C, &hasUpgrade);
				else if (comm == 0) {
					printf("> Perintah yang anda masukkan tidak valid!\n");
					printf("  Silakan masukan perintah lainnya\n");
				}
				finish = IsWin(nowPlaying) || comm == 25;
			 } while (comm != 16 && !finish);
			 if (IsInJail(nowPlaying) == 0)
				same = false;
		} while (same && !finish && IsInJail(nowPlaying) == 0);
		if (!finish)
			printf("  Giliran pemain %c telah berakhir\n", PlayerId(nowPlaying));
		//cek kemenangan
		if (IsWin(nowPlaying))
			finish = true;
		else
			NextTurn(LP, C);
	} while (!finish);
	if (comm == 25) {
		printf("> Anda akan meninggalkan permainan ini, apakah anda ingin\n");
		printf("  menyimpan permainan terlebih dahulu? (y/n)"); scanf("%c", &x);
		if (x == 'y' || x == 'Y') {
			SaveAll(*K, *LP, *LB, *LO, *LS);
			printf("> Permainan telah berhasil disimpan, selamat bermain lagi pada lain kali!\n");
		} else
			printf("  Anda telah keluar dari permainan!\n");
	} else{
		//ada yg menang
		printf("\n\n\n >>=============================================<< \n");
		printf("> Pemain %c telah memenangkan permainan!\n", PlayerId(nowPlaying));
		printf("  Uang pemain %c sekarang adalah ", PlayerId(nowPlaying)); tulisNominal(Money(nowPlaying));printf("\n");
		printf(">>=============================================<< \n");
	}
}

void doCommand (int i, char *arg, ListPlayer *LP, ListOffered *LO, ListBoard *LB, ListSabotage *LS, Kota *K, Card *C, boolean *h)
/* Melakukan command-command tertentu sesuai input player seperti buy, sell, dll
 * i >= 1, i <= 23, i selalu valid
 * */
{
	AddressP aP = FirstP(*LP);
	//AddressB aB = Where(aP);
	char pId = PlayerId(aP);

	switch (i) {
		case 1 : {
			printf("  Anda tidak bisa melakukan re-roll pada saat ini\n");
			break;
		}
		case 2 : {
			printInfo(*K, arg);
			break;
		}
		case 3 : {
			buy(pId, LP, K, *LB);
			break;
		}
		case 4 : {
			sellOffered(*LP, pId, *K, *LB, arg, LO);
			break;
		}
		case 5 : {
			sellBank(LP, pId, K, *LB, arg);
			break;
		}
		case 6 : {
			showOffered(*LO, *K);
			break;
		}
		case 7 : {
			buyOffered(pId, LP, K, LO, arg);
			break;
		}
		case 8 : {
			if (!*h) { //belum pernah upgrade
				*h = true;
				upgrade(pId, LP, *LB, K);
			} else {
				printf("  Anda pernah meng-upgrade petak ini pada giliran yang sama!\n");
				printf("  Lakukan upgrade pada petak ini pada giliran anda berikutnya!\n");
			}
			break;
		}
		case 12 : {
			Board(*K, *LP, *LB);
			break;
		}
		case 13 : {
			leaderBoard(*LP, *K);
			break;
		}
		case 17 : {
			SaveAll(*K, *LP, *LB, *LO, *LS);
			break;
		}
		case 22 : {
			Sabotage(LP, arg, *K, LS);
			break;
		}
		case 23 : {
			Shield(LP, arg, *K, LS);
			break;
		}
		case 24 : {
			Help();
			break;
		}
	}
}

void WhatHappened(ListPlayer *L, Kota Tkota, Card *Tcard, ListBoard Board, ListSabotage LS)
{
	/* kamus lokal */
	char nama[50], x;
	AddressP P;
	//AddressS Psab;
	boolean foundsab;
	boolean yes;
	/* algoritma */
	P = FirstP(*L);
	if (IsSpecial(Where(P)))
	{
		switch (PetakId(Where(P)))
		{
			case 0: {
						printf("> Anda mencapai petak Start.\n");
						break;
					}
			case 1: {
						printf("> Anda berada di petak Bonus.\n");
						printf("> Selamat! Anda akan mendapat uang.\n");
						BonusUang(&P);
						break;
					}
			case 2: {
						printf("> Anda berada di Deserted Island.\n");
						break;
					}
			case 3: {
						printf("> Anda berada di petak Chance.\n");
						printf("> Silakan buka kartu yang anda dapatkan.\n");
						KartuChance (&P, Tcard, Board);
						break;
					}
			case 4: {
						printf("> Anda berada di petak World Cup.\n");
						printf("  Masukkan nama kota host piala dunia: \n");
						printf("> ");
						scanf("%c", nama);
						Host(nama, &Tkota, Board, &P);
						break;
					}
			case 5:{
						printf("> Anda berada di petak World Travel.\n");
						printf("  Selamat mengelilingi dunia!\n");
						printf("> Masukkan nama kota yang dituju: \n");
						printf("> ");
						scanf("%c", nama);
						Travel (nama, &P, Board, Tkota);
						break;
					}
			case 6: {
						x = false;
						printf("> Anda berada di petak Tax.\n");
						yes = true;
						if (CardFreeTax(P)>0) {
							do {
								printf("  Apakah anda ingin menggunakan kartu bebas pajak? (y/n)");
								scanf("%c", &x);
								if (x != 'y' || x != 'Y' || x != 'N'||x != 'n')
									printf("  Input anda tidak valid!");
							} while (x != 'y' || x != 'Y' || x != 'N'||x != 'n');
							if (x == 'y' || x == 'Y')
								FreeTax(L, &yes, Tcard, Board);
						}
						if (yes)
							Pajak(&P);		//membayar pajak
						break;
					}
		}
	} else 			// berada di kota/rekreasi
	{
			// mengecek apakah kota yg dikunjungi kena sabotase //
			//Psab = FirstS(LS);
			foundsab = Search(LS, PetakId(Where(P))) != Nil;

			if (!foundsab)	//kota yang dikunjungi mengalami sabotase
			{
				PayWhenVisit(L,&Tkota,Board);
			}
	}
}

void Help () {
	printf("   Petunjuk Permainan Let's Get Whealty.\n");
	printf("\n");
	printf("  Instruksi permainan : \n");
	printf("   > roll dice \t\t (Untuk mengocok dadu)\n");
	printf("   > info <nama petak> \t\t (Untuk melihat harga petak/properti)\n");
	printf("   > buy \t\t (Untuk membeli petak yang sedang ditempatin)\n");
	printf("   > sell <nama petak> \t\t (Untuk menjual petak/properti yang dimiliki ke pemain lain)\n");
	printf("   > sell bank <nama petak> \t\t (Untuk menjual petak/properti yang dimiliki ke bank)\n");
	printf("   > show offered \t\t (Untuk menampilkan petak yang dijual pemain lain)\n");
	printf("   > buy offered <nama petak> \t\t (Untuk membeli petak yang dijual pemain lain)\n");
	printf("   > upgrade \t\t (Untuk mengupgrade level bangunan yang sedang ditempati)\n");
	printf("   > board \t\t (Untuk menampilkan board permainan)\n");
	printf("   > leaderboard \t\t (Untuk menampilkan urutan kekayaan player)\n");
	printf("   > end turn \t\t (Untuk mengakhiri giliran)\n");
	printf("   > save <nama file> \t\t (Untuk menyimpan permainan)\n");
	printf("  \n");
	printf("  Kondisi menang : ");
	printf("   1. Ketika semua pemain lawan bangkrut.\n");
	printf("   2. Tourism Monopoli (menguasai semua petak rekreasi).\n");
	printf("   3. Triple Monopoli (menguasai tiga buah blok).\n");
	printf("\n");
	printf(" Keep roll your dice!\n");
	printf("\n");
}
