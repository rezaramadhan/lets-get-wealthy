#include "listPlayer.h"
#include <time.h>

AddressP SearchPlayerid (ListPlayer Lp, char X)
/*Prekondisi: ListPlayer sudah terbentuk dgn id player a, b, c, d*/
/*Nilai X pasti terdapat di list player*/
{
	AddressP Pa = FirstP(Lp);
	boolean found = false;

	while (NextP(Pa) != FirstP(Lp) && !found) {
		found = PlayerId(Pa) == X;
		if (!found)
			Pa = NextP(Pa);
	}
	return Pa;
}

boolean IsWin (AddressP P) {
/* Fungsi untuk memeriksa apakah pemain P sudah menang.
 * kemenangan didapat jika pemain selain P memiliki
 * uang 0.
 * */
 	boolean winMoney=false, winBlok=false, winRekreasi=false;
	AddressP Ptemp;
	int sumBlok=0, i;

	Ptemp = NextP(P);
	while ((Ptemp != P)&&(winMoney)) {
		if ((Money(Ptemp) != 0)&&(IsEmptyBlok(Ptemp))) {
			winMoney = false;
		} else {
			Ptemp = NextP(Ptemp);
		}
	}

	for (i=0; i<=BlokMax; i++) {
		if (i==0) {
			if (BlokPlayer(P, i) == 4) {
				winRekreasi = true;
			}
		}
		else if (i==1 || i==4 || i==5 || i==7 || i==8) {
			if (BlokPlayer(P, i) == 2) {
				sumBlok++;
			}
		} else {
			if (BlokPlayer(P, i) == 3) {
				sumBlok++;
			}
		}
	}

	if (sumBlok >= 3) {
		winBlok = true;
	} else {
		winBlok = false;
	}

	return (winMoney || winBlok || winRekreasi);
}

void GoToJail (AddressP *Player, ListBoard Board){
/* I.S : Player dan Board terdefinisi
 * F.S : Memindahkan posisi Player ke Penjara dan men-set IsInJail
 *    	  Player menjadi True;
*/
    AddressB P;

    P = FirstB(Board);
    while ((NextB(P) != FirstB(Board))&&((IsSpecial(P))&&(PetakId(P) != 2))) {
   	 P = NextP(P);
    } //IsSpecial OR PetakID=2 OR P=FirstB

    if (IsSpecial(P) && (PetakId(P) == 2)) {
   	 Where(*Player) = P;
    }

    IsInJail(*Player) = 1;
    printf("\n  Kamu sekarang berada di Deserted island!");

}

boolean IsEmptyBlok(AddressP P) {
/* Fungsi untuk memeriksa apakah pemain P memiliki kota
 * atau tidak.
 * */
    int i=0;
    boolean f=true;

    while ((i<=BlokMax)&&(f)) {
   	 if (BlokPlayer(P, i) != 0) {
   		 f = false;
   	 } else {
   		 i++;
   	 }
    }

    return f;

}

void rolldice(ListBoard *B, ListPlayer *P, boolean *same) {
/*  I.S. B dan P terdefinisi, same sembarang
    F.S. Memperbaharui P setelah pemain mengocok dadu yaitu mengubah Where(FirstP(P));
         Same menghasilkan true jika kedua mata dadu menghasilkan nilai yang sama
*/
    int d1, d2, d3, i;
    AddressP aP = FirstP(*P);
    AddressB aB = Where(aP);

    srand(time(NULL));
    d1 = 1 + rand()%6;
    d2 = 1 + rand()%6;
    d3 = d1 + d2;
    printf("> %d + %d = %d\n", d1, d2, d3);
    for (i=1; i<=d3; i++) {
        aB = NextB(aB);
    }
    Where(aP) = aB;
    *same = (d1 == d2);
}

void leaderBoard(ListPlayer L, Kota K) {
/*  I.S. L dan K terdefinisi
    F.S. Menampilkan kondisi ranking semua pemain dan asset total mereka
*/
    int i, j, temp;
    AddressP P = FirstP(L);
    long total[5];
    char id;
	int nb = 1;

	while (NextP(P)!= FirstP(L)) {
		P = NextP(P);
		nb++;
	}
	P = FirstP(L);
    for (i=1; i<=nb; i++){
        j = (int)PlayerId(P) - 64;
        total[j] = Money(P);
        P = NextP(P);
    }
    for (i=KotaMin; i<=KotaMax; i++){
        if (OwnerKota(K,i) == '0') {
            j = 0;
        }
        else {
            j = (int)OwnerKota(K,i) - 64;
        }
        total[j] += hargaTotal(K,i);
    }
    temp = 1;
    for (i=1; i<=nb; i++) {
        for (j=1; j<=nb; j++) {
            if (total[temp] < total[j]) {
                temp = j;
            }
        }
        id = (char)(temp + 64);
        printf("> Player %c ", id); tulisNominal(total[temp]); printf("\n");
        total[temp] = 0;
    }
}

void buy (char Pid, ListPlayer *LP, Kota *K, ListBoard LB)
/*PA adalah address player yg membeli bangunan*/
/*Membeli (baik secara paksa atau tidak) petak yg sedang ditempati player*/
/*I.S. Semua terdefinisi, petak yg dibeli bukan petak rekreasi (CEK DI PEMANGGILAN!)*/
/*I.S. Petak dibeli oleh player jika syarat terpenuhi, dan jika tidak terpenuhi maka tidak*/
{
	AddressP PA = SearchPlayerid(*LP, Pid);
	AddressP PA1;
	AddressB Pwhere = Where(PA);
	int idP = PetakId(Pwhere);
	boolean rek = IsRekreasi(*K, idP);
	boolean CanBuy = false;
	boolean isPaksa = false;
	long price;

	if (!IsSpecial(Pwhere)) {
		if (OwnerKota(*K, idP) != '0') {//Beli paksa
			if (rek) //Petak rekreasi ga bisa dibeli
				printf("  Anda tidak bisa membeli petak rekreasi!\n");
			else if (LevelKota(*K, idP) > 3) //landmark (level > 3) ga bisa dibeli
				printf("  Anda tidak bisa membeli kota %s yang telah menjadi Landmark!\n", NamaKota(*K, idP));
			else { //sukses beli
				price = hargaTotal(*K, idP) * 2;
				isPaksa = true;
				CanBuy = true;
			}
		} else { //beli murni
			price = HargaKota(*K, idP);
			CanBuy = true;
		}

		if (CanBuy) {
			if (Money(PA) >= price) { //beli sukses
				if (isPaksa) {
					PA1 = SearchPlayerid(*LP, OwnerKota(*K, idP));
					Money(PA1) += price;
					BlokPlayer(PA1, (BlokKota(*K, idP)))--;
				} else
					LevelKota(*K, idP) = 1;
				BlokPlayer(PA, BlokKota(*K, idP))++;
				OwnerKota(*K, idP) = PlayerId(PA);
				Money(PA) -= price;
				printf("> Selamat, kota %s sekarang menjadi milikmu!\n", NamaKota(*K, idP));
				printf("  Sisa uangmu adalah: ");  tulisNominal(Money(PA)); printf("\n");
				if (isPaksa) {
					printf("  Player %c mendapatkan uang sebesar ", PlayerId(PA1));
					tulisNominal(price);
					printf(" dari penjualan kota %s!", NamaKota(*K, idP)); printf("\n");
				}
			} else  { //uang kurang
				printf("  Maaf, uang anda tidak mencukupi untuk membeli kota %s\n", NamaKota(*K, idP));
				printf("  Sisa uangmu adalah: ");  tulisNominal(Money(PA)); printf("\n");
				printf("  Harga kota %s adalah: ", NamaKota(*K, idP));  tulisNominal(Money(PA)); printf("\n");
			}
		}
	} else {
		printf("  Anda tidak bisa membeli petak selain petak kota dan rekreasi!\n");
	}
}

void sellBank (ListPlayer *Lp, char Pid, Kota *K, ListBoard Lb, char* namakota)
/*Menyimpan petak dengan nama namakota ke list offered*/
{
	AddressB PB = SearchNamaKota(Lb, *K, namakota);
	AddressP PP = SearchPlayerid(*Lp, Pid);
	int idB;
	long price;

	if (PB != Nil)
		idB = PetakId(PB);

	if (OwnerKota(*K, idB) == Pid) { //punya sendiri
		price = hargaTotal(*K, idB) - hargaTotal(*K, idB)/10;
		Money(PP) += price;
		BlokPlayer(PP, BlokKota(*K, idB))--;
		OwnerKota(*K, idB) = '0';
		LevelKota(*K, idB) = 0;
		printf("  Kota %s terjual ke bank dengan harga \n", namakota); tulisNominal(price); printf("!\n");
		printf("  Uang anda sekarang adalah \n"); tulisNominal(Money(PP)); printf("\n");
	} else //punya orang
		printf("  Anda tidak bisa menjual petak milik orang lain!");
}

void upgrade (char idP, ListPlayer *LP, ListBoard Lb, Kota *K) {
/*Mengupgrade petak yang sedang "dipijak" oleh player*/
/*Menampilkan pesan kesalahan jika mengupgrade petak gagal*/
	AddressP PP = SearchPlayerid(*LP, idP);
	int idB = PetakId(Where(PP));
	long price;

	if (!IsSpecial(Where(PP))) {
		if (OwnerKota(*K, idB) == idP) {//punya sendiri
			price = hargaUpgrade(*K, idB);
			if (Money(PP) >= price) { //duit cukup
				LevelKota(*K, idB)++;
				printf("  Selamat, kota %s sekarang menjadi level %d!\n", NamaKota(*K, idB), LevelKota(*K, idB));
				Money(PP) -= price;
				if (LevelKota(*K, idB) > 3)
					printf("  Kota %s sekarang telah menjadi landmark dan tidak bisa dibeli paksa oleh pemain lain!\n", NamaKota(*K, idB));
				printf("  Sisa uangmu adalah: ");  tulisNominal(Money(PP)); printf("\n");
			} else {
				printf("  Maaf, uang anda tidak mencukupi untuk mengupgrade kota %s\n", NamaKota(*K, idB));
				printf("  Sisa uangmu adalah: ");  tulisNominal(Money(PP)); printf("\n");
				printf("  Harga untuk mengupgrade kota %s adalah: ", NamaKota(*K, idB)); tulisNominal(Money(PP)); printf("\n");
			}
		} else //bukan punya sendiri
			printf("  Anda tidak bisa meng-upgrade petak milik pemain lain!\n");
	} else {
		printf("  Anda tidak bisa membeli petak selain petak kota dan rekreasi!\n");
	}
}

void BonusUang (AddressP *Player) {
/*    I.S : Player terdefinisi.
 *    F.S    : Uang Player akan bertambah secara acak dengan nominal 100K,
 *    	   200K, dan 300K. Kemudian menampilkan pesan sesuai format.
*/
    int c;
    long bonus;

    //Proses Random
    srand(time(NULL));
    c = rand() % 3 + 1;

    bonus = 100000 * c;
    Money(*Player) = Money(*Player) + bonus;

    printf("  Selamat, kamu mendapatkan "); tulisNominal(bonus); printf("\n");
    printf("  Uangmu sekarang "); tulisNominal(Money(*Player)); printf("\n");
}

void Pajak (AddressP *Player){
/*    I.S : Player terdefinisi.
 *    F.S    : Uang Player akan berkurang sebanyak 10% dari uang total
 *    	   yang dimiliki Player. Kemudian menampilkan pesan sesuai
 *    	   format.
*/
    int total;
    //boolean card;
    //char y;

    //harus pake konversi uang dulu

    total = Money(*Player)/10;
    Money(*Player) = Money(*Player) - total;

    printf("  Pajak Bumi dan Bangunan, uangmu berkurang ");tulisNominal(total); printf("\n");
    printf("  Sisa uang "); tulisNominal(Money(*Player)); printf("\n");

}

void Travel (char *kota, AddressP *Player, ListBoard Board, Kota K) {
/*    I.S : kota, player, board, K terdefinisi
 *     F.S : Memindahkan posisi Player ke kota. Search Board dgn
 *    	   nama kota board = *kota.
*/
    AddressB P;
	char input[25];
	strcpy(input, kota);
    do {
		P = SearchNamaKota(Board, K, input);
		if (P != Nil) {
			Where(*Player) = P;
			printf("  Player %c sampai di %s\n", PlayerId(*Player), kota);
		} else {
			printf("> Kota tidak ditemukan. Posisi anda tetap!\n");
			printf("  Masukkan nama kota yang lain : "); scanf("%s", input);

		}
    } while(P == Nil);
}

void PayWhenVisit(ListPlayer *L, Kota *T, ListBoard Board)
{
	/* kamus lokal */
	AddressP P;			//address player yang sedang bermain
	AddressP Powner;	//address player yang memiliki property di suatu kota yang disinggahi
	int i;

	/* algoritma */
	P = FirstP(*L);
	if ((OwnerKota(*T,PetakId(Where(P)))!='0')&&(!IsSpecial(Where(P)))) //ada yang punya
	{
		//mencari address Powner
		Powner = P;
		while (PlayerId(Powner)!=OwnerKota(*T,PetakId(Where(P))))
		{
			Powner = NextP(Powner);	//mengembalikan Address Powner
		}

		if (Powner!= P)		//pemilik property bukan player itu sendiri
		{

			i = PetakId(Where(P));
			long sewa = hargaTotal(*T, i)/10;
			if (IsHost(*T,i))	//kota tersebut host world cup atau dikuasai juragan
			{
				// yg dibayarkan menjadi 2x lipat //
				sewa = 2 * sewa;
			}
			if (IsBlokDikuasai(*T,BlokKota(*T,i)))
			{
				sewa = 2 * sewa;
			}
			char nama[50];
			while (Money(P) < sewa && !IsEmptyBlok(P)) {
				printf("  Uang anda saat ini kurang untuk membayar sewa!\n");
				printf("  Uang anda adalah "); tulisNominal(Money(P)); printf("\n");
				printf("  Biaya membayar sewa adalah "); tulisNominal(sewa); printf("\n");
				printf("> Masukkan nama properti yang akan dijual ke bank: "); scanf("%c", nama);
				sellBank(L, PlayerId(P), T, Board, nama);
			} //ga punya properti atau punya uang
			if (Money(P) >= sewa) {
				Money(P) -= sewa;
				Money(Powner) += sewa;
				printf("  Anda telah membayar sewa ke pemain %c sebesar ", PlayerId(Powner)); tulisNominal(sewa); printf("\n");
			} else { //ga cukup duit
				Money(Powner) += Money(P);
				Money(P) = 0;
				printf("> Anda telah bangkrut!\n");
				printf("  GAME OVER UNTUK PEMAIN %c", PlayerId(P));

			}

		}
	} else //gaada yang punya
	{
		// do nothing
	}
}

boolean IsListEmptyP (ListPlayer L){
/* Mengirim true jika list kosong */
	boolean empty;

	if (FirstP(L) == Nil) {
		empty = true;
	} else {
		empty = false;
	}

	return empty;
}
AddressP AlokasiP (InfotypePlayer X) {
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/
	//KAMUS
	AddressP P;
	int i;

	//ALGORITMA
	P = (AddressP) malloc (sizeof(ElmtListPlayer));

	if (P == Nil) {
		return Nil;
	} else {
		PlayerId(P) = X.playerId;
		Money(P) = X.money;
		IsInJail(P) = X.jail;
		Where(P) = X.where;
		CardFreeTax(P) = X.c.FreeTax;
		CardFreePrison(P) = X.c.FreePrison;
		CardProtect(P) = X.c.Protect;
		CardOff(P) = X.c.Off;
		for (i = 0; i<= BlokMax; i++)
			BlokPlayer(P, i) = X.bl.TabBlok[i];
		NextB(P) = Nil;
		return P;
	}
}
AddressP LastP (ListPlayer L) {
/*	I.S. sembarang
	F.S. Mengirim address terakhir dari List. Jika List kosong, kembalikan Nil.
*/
	AddressP P;

	if (IsListEmptyP(L)) {
		return Nil;
	} else {
		P = FirstP(L);
		while (NextP(P)!= FirstP(L)) {
			P = NextP(P);
		}
		return P;
	}
}


void InsertFirstP (ListPlayer *L, AddressP P) {
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/
	if (IsListEmptyP(*L)) {
		NextP(P) = P;
	} else {
		NextP(P) = FirstP(*L);
		NextP(LastP(*L)) = P;
	}
	FirstP(*L) = P;
}

void InsertAfterP (ListPlayer *L, AddressP P, AddressP Prec) {
/*	I.S. Prec pastilah elemen list dan bukan elemen terakhir, P sudah dialokasi
	F.S. Insert P sebagai elemen sesudah elemen beralamat Prec
*/
	NextP(P) = NextP(Prec);
	NextP(Prec) = P;
}

void InsertLastP (ListPlayer *L, AddressP P) {
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/
	if (IsListEmptyP(*L)) {
		InsertFirstP(L, P);
	} else {
		InsertAfterP(L, P, LastP(*L));
	}
}

void InsVLastP (ListPlayer *L, InfotypePlayer X) {
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen terakhir L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen list di akhir :
	elemen terakhir yang baru bernilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/
	AddressP P;

	P = AlokasiP(X);
	if (P != Nil) {
		InsertLastP(L, P);
		NextP(LastP(*L)) = FirstP(*L);
	}

}

void LoadPlayer(ListPlayer *X, ListBoard L)
{
    int i, num;
    InfotypePlayer XP;
    long b,v;
    //AddressP P;
    //P = FirstP(*X);
    //AddressB Q;
    //Q = Where(P);
    FirstP(*X) = Nil;
	char input[11];
	strcpy(input, "player.txt");
    STARTKATA(input);

    do
    {
        v = 0;
        ADVKATA();

        for(i=0;i<CKata.Length;i++)
        {
            b = bil(CKata.TabKata[i]);
            XP.bl.TabBlok[i] = b;
        }

        //printf("block player : %s\n",CKata.TabKata);

        ADVKATA();

        XP.c.FreePrison = bil(CKata.TabKata[0]);
        //printf("cfp : %d\n",XP.c.FreePrison);

        ADVKATA();

        XP.c.FreeTax = bil(CKata.TabKata[0]);
        //printf("cft : %d\n",XP.c.FreeTax);

        ADVKATA();

        XP.c.Off = bil(CKata.TabKata[0]);
        //printf("coff : %d\n",XP.c.FreePrison);

        ADVKATA();

        XP.c.Protect = bil(CKata.TabKata[0]);
        //printf("cptc : %d\n",XP.c.Protect);

        ADVKATA();

        for(i=0;i<CKata.Length;i++)
        {
            v = v*10 + bil(CKata.TabKata[i]);
        }

        XP.money = v;
        //printf("mny : %ld\n",XP.money);

        ADVKATA();

        XP.jail = bil(CKata.TabKata[0]);
        //printf("brp kali masuk jail? : %d\n",XP.jail);

		ADVKATA();

		//printf("here1\n");
        XP.playerId = CKata.TabKata[0];
        //printf("here2\n");
        //printf("player id? : %c\n",XP.playerId);
		//printf("here3\n");
        ADVKATA();
		//printf("here4\n");
		num = 0;
         for(i=0;i<CKata.Length;i++)
        {
            num = num*10 + bil(CKata.TabKata[i]);
        }
        //printf("%d\n", CKata.Length);
        //printf("player where? : %d\n\n",num);
		XP.where = SearchNum(L, num);
        //printf("player where? : %p\n\n",XP.where);

        InsVLastP(X, XP);

		ADVKATA();
    } while (!EndKata);
}

void InisiasiPlayer (int JmlPlayer, ListPlayer *LP, ListBoard LB) {

	InfotypePlayer Xp;
	int i, j;
	FirstP(*LP) = Nil;
	//inisiasi pemain
	for (i=1; i<=JmlPlayer; i++) {
		//inisiasi where(p)
		Xp.where = FirstB(LB);
		//Inisiasi ID
		if (i == 1) {
			Xp.playerId = 'A';
		} else if (i == 2) {
			Xp.playerId = 'B';
		} else if (i == 3) {
			Xp.playerId = 'C';
		} else if (i == 4) {
			Xp.playerId = 'D';
		}
		//inisiasi isJail
		Xp.jail = false;
		//inisiasi money
		Xp.money = 1000000;
		//Inisiasi Player Card
		Xp.c.FreePrison = 0;
		Xp.c.FreeTax = 0;
		Xp.c.Off = 0;
		Xp.c.Protect = 0;
		//Inisiasi Blok
		for (j=0; j<=BlokMax; j++) {
			Xp.bl.TabBlok[j] = 0;
		}
		InsVLastP(LP, Xp);
	}

}

void printIsiL (Kota K, ListPlayer P, int num, int id, AddressB AB, char *Sp[]) {
    AddressP aP = FirstP(P);
    AddressB aB = Where(aP);

    if (!IsSpecial(AB)) {
        printf("%d. %d: %s\n", num, id, NamaKota(K,id));
        printf("    Harga: "); tulisNominal(HargaKota(K,id)); printf("\n");
        if (OwnerKota(K,id) != 0 && LevelKota(K,id) != 0) {
            printf("    Pemilik: %c\n", OwnerKota(K,id));
            printf("    Level: %d\n", LevelKota(K,id));
        }
        if (BlokKota(K,id) != 0) {
            printf("    Blok: %d\n", BlokKota(K,id));
        } else
			printf("    Rekreasi\n");
    }
    else {
        printf("%d. %s\n", num, Sp[id]);
    }
    while (NextP(aP) != FirstP(P)) {
        aB = Where(aP);
        if (Number(aB) == num) {
            printf("    Player: %c\n", PlayerId(aP));
        }
        aP = NextP(aP);
    }
}

void printL (Kota K, ListPlayer P, ListBoard B) {
    AddressB aB = FirstB(B);
    int num = Number(aB);
    int id;
    char *Sp[7];

    Sp[0] = "Start";
    Sp[1] = "Bonus";
    Sp[2] = "Deserted Island";
    Sp[3] = "Chance";
    Sp[4] = "World Cup";
    Sp[5] = "World Travel";
    Sp[6] = "Tax";
    do
    {
        id = PetakId(aB);
        printIsiL(K,P,num,id,aB,Sp);
        aB = NextB(aB);
        num = Number(aB);
        printf("\n");
    } while (aB != FirstB(B));
}

void Board (Kota K, ListPlayer P, ListBoard B) {
    printf("\t\t/===================================\\\n");
    printf("\t\t| S | 1 | B | 2 | 3 | 4 | 5 | 6 | D |\n");
    printf("\t\t|---+---------------------------+---|\n");
    printf("\t\t| 23|\t\t\t\t| 7 |\n");
    printf("\t\t|---|\t\t\t\t|---|\n");
    printf("\t\t| T |\t\t\t\t| 8 |\n");
    printf("\t\t|---|\tS : Start\t\t|---|\n");
    printf("\t\t| 22|\tB : Bonus\t\t| 9 |\n");
    printf("\t\t|---|\tD : Deserted Island\t|---|\n");
    printf("\t\t| C |\tC : Chance\t\t| C |\n");
    printf("\t\t|---|\tWC: World Cup\t\t|---|\n");
    printf("\t\t| 21|\tWT: World Travel\t|10 |\n");
    printf("\t\t|---|\tT : Tax\t\t\t|---|\n");
    printf("\t\t| 20|\t\t\t\t|11 |\n");
    printf("\t\t|---|\t\t\t\t|---|\n");
    printf("\t\t| 19|\t\t\t\t|12 |\n");
    printf("\t\t|---+---------------------------+---|\n");
    printf("\t\t| WT| 18| 17| 16| C |15 |14 |13 |WC |\n");
    printf("\t\t\\===================================/\n\n");

    printL(K,P,B);
}

void saveplayer(ListPlayer LP, ListBoard LB)
{
    FILE *file;
    AddressP P;
    AddressB B;
    Blok b; //blok yg dimiliki player
	PlayerCard cr; //card yg dimiliki player
	long mny; //uang player
	int jl; //apakah player masuk jail
	char pId; //id player
	int wr; //player berada dimana

    remove("player.txt");
    file = fopen("player.txt", "a+");

    P = FirstP(LP);
    B = FirstB(LB);
    //printf("sas\n");
    do
    {
        int i;
        fprintf(file,"> ");
        cr.FreePrison = CardFreePrison(P);
        cr.FreeTax = CardFreeTax(P);
        cr.Off = CardOff(P);
        cr.Protect = CardProtect(P);
        mny = Money(P);
        jl = IsInJail(P);
        pId = PlayerId(P);

        B = Where(P);
        wr = Number(B);

        for(i=1;i<=BlokMax;i++)
        {
            fflush(stdin);
            b.TabBlok[i] = BlokPlayer(P,i);
        }

        for(i=1;i<=BlokMax-1;i++)
        {
            fprintf(file,"%d",b.TabBlok[i]);
        }
        fprintf(file,"%d ",b.TabBlok[BlokMax]);

        fprintf(file,"%d ",cr.FreePrison);
        fprintf(file,"%d ",cr.FreeTax);
        fprintf(file,"%d ",cr.Off);
        fprintf(file,"%d ",cr.Protect);
        fprintf(file,"%ld ",mny);

        fprintf(file,"%d ",jl);
        fprintf(file,"%c ",pId);
        fprintf(file,"%d \n",wr);
        //fprintf(file,"\n");

		P = NextP(P);
		//printf("12\n");
    }while(P!=FirstP(LP));
    fprintf(file,".");
    fclose(file);
}

void Host (char *kota, Kota *City, ListBoard Board, AddressP *Play) {
/* I.S	: Kota terdefinisi.
 * F.S	: Set semua IsHost kota menjadi false karena tidak mungkin
 * 		  ada dua Host dalam waktu yg bersamaan. Kemudian Set IsHost
 * 		  *kota menjadi true.
*/
	AddressB P, Pset;

	Pset = FirstB(Board);
	while (NextB(Pset) != FirstB(Board)) {
		IsHost(*City, PetakId(Pset)) = false;
		Pset = NextB(Pset);
	} // Pset = Last element list
	IsHost(*City, PetakId(Pset)) = false; 	// set IsHost Last element list
	do {
		P = SearchNamaKota(Board, *City, kota);
		if (P != Nil) {
			if (OwnerKota(*City, PetakId(P)) == PlayerId(*Play)) {
				IsHost(*City, PetakId(P)) = true;
				printf("  %s menjadi host World Cup. Uang sewa di %s menjadi ", NamaKota(*City, PetakId(P)), NamaKota(*City, PetakId(P)));
				tulisNominal(HargaKota(*City, PetakId(P)) * 2);
				printf("\n");
			} else {
				printf("  Kota tersebut bukan milikmu!\n");
				printf("  Anda hanya bisa menjadikan kota milik sendiri untuk menjadi host world cup!\n");
			}
		} else {
			printf("  Kota tidak ditemukan.\n");
			printf("  Masukkan nama kota yang lain : "); scanf("%s", kota);
		}
    } while (P == Nil);
}
