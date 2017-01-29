#include "arrCard.h"


void InisiasiChance (Card *Chance) {
/* Inisiasi kartu chance */
	int i;
	for (i=1; i<=5; i++){
		CardVal(*Chance, i) = 5;
		IsTaken(*Chance, i) = false;
		switch (i) {
			case 1 : {
				CardType(*Chance, i) = '1';
				break;
			}
			case 2 : { 
				CardType(*Chance, i) = '2';
				break;
			}
			case 3 : {
				CardType(*Chance, i) = '3';
				break;
			}
			case 4 : {
				CardType(*Chance, i) = '4';
				break;
			}
			case 5 : {
				CardType(*Chance, i) = '5';
				break;
			}
		}
	}
	
}

void KartuChance (AddressP *Player, Card *Kartu, ListBoard Board) {
/*     I.S : sembarang, Player adalah pemain yang mendapat chance,
 *    	   Card adalah container yang menyimpan kartu kesempatan.
    F.S : semua PlayerCard Player ditambah 1 dan container
    *       Card dikurangi 1, sesuai dengan hasil pengacakan. Jika
    *       mendapat kartu masuk penjara, panggil fungsi GoToJail yang
    *       akan merubah posisi Player ke penjara dan men-set IsInJail
    *       Player menjadi True.
*/
    int c, jumlah_chance;

    jumlah_chance = 5;
    
    //Proses Random
    do {
   	 srand(time(NULL));
   	 c = rand() % jumlah_chance + 1;
    } while (IsTaken(*Kartu, c));
    //Output
    printf("  Kamu mendapat kartu ");
   	 switch (c) {
   		 case 1 : {
   			 CardFreePrison(*Player)++;
   			 printf("bebas dari penjara. ");
   			 break;
   		 }
   		 case 2 : {
   			 CardFreeTax(*Player)++;
   			 printf("bebas pajak. ");
   			 break;
   		 }
   		 case 3 : {
   			 printf("masuk penjara. \n");
   			 GoToJail(Player, Board);   			 
   			 break;
   		 }
   		 case 4 : {
   			 CardOff(*Player)++;
   			 printf("mati lampu. ");
   			 break;
   		 }
   		 case 5 : {
   			 CardProtect(*Player)++;
   			 printf("perlindungan. ");
   			 break;
   		 }
   	 } printf("\n");
    
    if (c != 3) {
   	 printf("  Simpan kartu ini untuk penggunaan selanjutnya.\n");
   	 CardVal(*Kartu, c)--;
   	 if (CardVal(*Kartu, c) == 0) {
   		 IsTaken(*Kartu, c) = true;
   	 }
    } else {
   	 printf("\n");
    }
}

void FreeTax(ListPlayer *L, boolean *applyfreetax, Card *T, ListBoard Board)
/* Prosedur ini merupakan pengaplikasian kartu chance Free Tax oleh player
 * yang memilik kartu tersebut dan memasukan command yang tepat.
 * I.S : Player berada di suatu petak tertentu
 * F.S : Player dibebaskan dari pajak dan kartu bebas pajak milik player
 * 		 berkurang 1, applyfreetax bernilai true jika penggunaan kartu
 * 		 berhasil.
 */
{
	/* kamus lokal  */
	AddressP P;
	/* algoritma */
	P = FirstP(*L);
	if ((PetakId(Where(P))==6)&&(IsSpecial(Where(P)))) 										// player di petak pajak
	{
		if (CardFreeTax(P)>0)																// player punya minimal 1 kartu free tax
		{
			CardFreeTax(P) -= 1; 															// mengurangi jumlah kartu free tax milik player
			CardVal(*T, 2) += 1; 															// menambah jumlah kartu free tax yang dimiliki sistem
			*applyfreetax = true;
			
			// pesan output //
			printf("> Selamat! Anda baru saja berhasil menggunakan kartu bebas pajak.\n");
			printf("  Jumlah kartu bebas pajak anda sekarang %d buah\n", CardFreeTax(P));
			
		} else
		{
			*applyfreetax = false;
			
			// pesan output //
			printf("> Sayang sekali, anda tidak punya kartu bebas pajak\n");
			printf("  Penggunaan kartu ini gagal\n");
			
		} 	
	} else 																					// player tdk berada di petak pajak
	{
		*applyfreetax = false;
		
		// pesan output //
		printf("> Anda tidak dapat menggunakan kartu bebas pajak\n");
		printf("  Anda harus berada di kotak Tax untuk menggunakannya\n");
	}
}

void FreeJail(ListPlayer *L, Card *T)
/* Prosedur ini digunakan saat player dipenjara dan ingin terbebas darinya
 * I.S : Player berada di deserted island dan tidak bisa bepergian saat
 * 		 gilirannya tiba
 * F.S : Player dibebaskan dari penjara (bisa bepergian saat gilirannya
 * 		 tiba), kartu bebas penjara milik player berkurang satu dan 
 * 		 applyfreejail bernilai true jika penggunaan kartu tersebut berhasil
 */
{
	/* kamus lokal  */
	AddressP P;
	
	/* algoritma	*/
	P = FirstP(*L);
	if (IsInJail(P)>0)																			//player berada di penjara
	{
		if (CardFreePrison(P)>0)																//player memiliki kartu free prison
		{
			CardFreePrison(P) -= 1;																//mengurangi jumlah kartu free prison milik player
			CardVal(*T, 1) += 1; 																//menambah jumlah kartu free prison yang dimiliki sistem
			IsInJail(P) = 0;
			
			// pesan output //
			printf("> Selamat! Anda baru saja berhasil menggunakan kartu bebas penjara.\n");
			printf("  Jumlah kartu bebas penjara anda sekarang %d buah\n", CardFreePrison(P));
		} else 																					//player tidak memiliki kartu free prison
		{
			
			// pesan output //
			printf("> Sayang sekali, anda tidak mempunyai kartu bebas penjara\n");
			printf("  Penggunaan kartu ini gagal\n");
			
		}
	} else 																						// player tidak berada di penjara
	{
		
		// pesan output //
		printf("> Anda tidak dapat menggunakan kartu ini\n");
		printf("> Anda harus berada di deserted land untuk menggunakan kartu ini\n");
		
	}
}

