#include "listSabotage.h"

boolean IsListEmptyS (ListSabotage L)
/* Mengirim true jika list kosong */
{
	/* algoritma */
	if (FirstS(L)== Nil)
	{
		return true;
	} else
	{
		return false;
	}
}

AddressS AlokasiS(id X)
/* fungsi ini mengalokasi sebuah AddressS */
{
	/* kamus lokal */
	AddressS P;
	
	/* algoritma */
	P = malloc(1* sizeof (ElmtListSabotage));
	if (P!= Nil)
	{
		IdS(P) = X;
		NextS(P) = Nil;
	} else
	{
		P = Nil;
	}
	return P;
}

void DealokasiS (AddressS *P)
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/
{
	/* algoritma */
	free(*P);
}

AddressS Search (ListSabotage L, id X)
/*	Mencari apakah ada elemen list dengan Info(P) = X
	Jika ada, mengirimkan Address elemen tersebut
	Jika tidak ada, mengirimkan Nil
*/

{
	/* kamus lokal */
	AddressS P;
	boolean found;
	
	/* algoritma */
	if (IsListEmptyS(L))
	{
		return Nil;
	} else
	{
		found = false;
		P = FirstS(L);
		while ((P!=Nil)&&(!(found)))
		{
			if (IdS(P)==X)
			{
				found=true;
			} else
			{
				P = NextS(P);
			}
		}
		return P;
	}
}

AddressS SearchPrec (ListSabotage L, id X)
/*	Mengirimkan Address elemen sebelum elemen yang nilainya = X
	Mencari apakah ada elemen list dengan Info(P) = X
	Jika ada, mengirimkan Address Prec, dengan Next(Prec) = P dan Info(P) = X
	Jika tidak ada, mengirimkan Nil
	Jika P adalah elemen pertama, maka mengirimkan Nil
	Search dengan spesifikasi seperti ini menghindari traversal ulang jika setelah
	Search akan dilakukan operasi lain
*/
{
	/* kamus lokal */
	AddressS Prec,P;
	boolean found;
	
	/* algoritma */
	if (IsListEmptyS(L))
	{
		return Nil;
	} else
	{
		found = false;
		P = FirstS(L);
		Prec = Nil;
		if (! (Search(L,X) == Nil))
		{
			while ((P!=Nil) && (!found))
			{
				if (IdS(P)==X)
				{
					found=true;
				} else
				{
					P = NextS(P);
					Prec = P;
				}
			}
		}
		return Prec;
	}
}



void InsVFirst (ListSabotage *L, id X)
/*	I.S. L mungkin kosong
	F.S. X ditambahkan sebagai elemen pertama L
	Proses : Melakukan alokasi sebuah elemen dan menambahkan elemen pertama dengan
	nilai X jika alokasi berhasil.
	Jika alokasi gagal: I.S.= F.S.
*/
{
	/* kamus lokal */
	AddressS P;
	
	/* algoritma */
	P = AlokasiS(X);
	if (P!=Nil)
	{
		NextS(P) = FirstS(*L);
		FirstS(*L) = P;
	}
}

void DelVFirst (ListSabotage *L)
/*	I.S. List L tidak kosong
	F.S. Elemen pertama list dihapus : nilai info disimpan pada X
	dan alamat elemen pertama di-dealokasi
*/
{
	/* kamus lokal */
	AddressS P;
	
	/* algoritma */
	P = FirstS(*L);
	FirstS(*L) = NextS(FirstS(*L));
	NextS(P) = Nil;
	DealokasiS(&P);
}

void DeleteAfter (ListSabotage *L, AddressS *Pdel, AddressS Prec)
/*	I.S. List tidak kosong. Prec adalah anggota list L.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen list yang dihapus
*/
{
	/* algoritma */
	*Pdel= NextS(Prec);
	NextS(Prec) = NextS(NextS(Prec));
}

void DeleteP (ListSabotage *L, id X)
/*	I.S. Sembarang
	F.S. Jika ada elemen list ber-Address P, dengan Info(P) = X
	Maka P dihapus dari list dan di-dealokasi
	Jika tidak ada elemen list dengan Info(P) = X, maka list tetap
	List mungkin menjadi kosong karena penghapusan
*/
{
	/* kamus lokal */
	AddressS P;
	
	/* algoritma */
	if (Search(*L,X)==FirstS(*L))
	{
		DelVFirst(L);
	} else
	{
		P = SearchPrec(*L,X);
		DeleteAfter(L, &NextS(P), P);
		DealokasiS(&P);
	}
}





// FUNGSI UTAMA //
void Sabotage(ListPlayer *L, char *nama, Kota T, ListSabotage *LS)
/* Prosedur ini digunakan saat player ingin melakukan sabotase terhadap
 * suatu kota sehingga kota tersebut mati listrik dan biaya sewa bagi
 * pemain luar yang mampir di kota tsb menjadi 0.
 * I.S : Biaya sewa di suatu kota terdefinisi dan normal.
 * F.S : Biaya sewa di kota yang dimaksud pengguna menjadi 0 (berhasil
 * 		 disabotase) dan biaya sewa disimpan temporary di sewa (sewa 
 * 		 terdefinisi).
 */
{
	/* KAMUS LOKAL */
	boolean found;
	int i;
	AddressP P;
	//AddressS P1;
	
	
	/* ALGORITMA */
	P = FirstP(*L);
	if (CardOff(P)>0)
	{
		// Searching Id Kota //
		found = false;
		i=KotaMin;
		while (!found && i<=KotaMax)
		{
			if (NamaKota(T, i)==nama)
			{
				found = true; 
			} else
			{
				i++;
			}
		}
		
		// menambahkan Kota Sabotage //
		if (found) {
			if (OwnerKota(T, i) != '0') {
				InsVFirst(LS,i);
				
				CardOff(P) -= 1;
				printf("> Selamat! Listrik di kota tersebut telah dipadamkan. Biaya sewa di kota tersebut = 0. \n");
			} else {
				printf("> Kota %s tidak ada yang memiliki!\n", NamaKota(T, i));
				printf("  Penggunaan kartu sabotage gagal\n");
			}
		} else {
			printf("> Tidak ditemukan kota bernama %s\n",nama);
			printf("  Penggunaan kartu sabotage gagal\n");
		}
	} else
	{
		printf("> Sayang sekali, anda tidak mempunyai kartu sabotage\n");
		printf("> Penggunaan kartu ini gagal\n");
	}
}


void Shield(ListPlayer *L, char *nama, Kota T, ListSabotage *LS)
/* Prosedur ini digunakan saat player (kemungkinan besar merupakan player
 * yang kota miliknya disabotase) ingin mengembalikan biaya sewa kotanya
 * menjadi normal kembali.
 * I.S : Biaya sewa di suatu kota 0.
 * F.S : Biaya sewa di kota yang dimaksud pengguna menjadi normal sesuai
 * 		 seharusnya (mengacu pada parameter input: sewa).
 */
{
	/* kamus lokal */
	boolean found;
	int i;
	AddressP P;
	
	/* algoritma */
	P = FirstP(*L);
	if (CardProtect(P)>0)
	{
		//Searching Id Kota
		found = false;
		i=KotaMin;
		while (!found && i<=KotaMax)
		{
			if (NamaKota(T,i)==nama)
			{
				found = true; 
			} else
			{
				i++;
			}
		}
		
		// menghapus kota dari list sabotage //
		if (found) {
			if (Search(*LS, i) != Nil) {
				DeleteP(LS,i);					
				CardProtect(P) -=1;
				printf("> Selamat! Kota tersebut berhasil dilindungi. Biaya sewa di kota itu kembali normal.\n");
			} else {
				printf("> Kota ini tidak sedang disabotase saat ini\n");
				printf("  Penggunaan kartu shield gagal\n");
			} 
		} else {
			printf("> Tidak ditemukan kota bernama %s\n", nama);
			printf("  Penggunaan kartu shield gagal\n");
		}
	} else
	{
		printf("> Sayang sekali, anda tidak mempunyai kartu protect\n");
		printf("> Penggunaan kartu ini gagal\n");
	}
}

void SabotageOff(ListPlayer *L, Kota  T, ListSabotage *LS)
/* procedure ini digunakan untuk membuat kota yang terkena sabotase milik player
 * kembali normal setelah player tsb melewati start 
 * I.S : kota merupakan element listSabotage 
 * F.S : kota di hapus dari element listSabotage */
{
	/* kamus lokal */
	int i;
	AddressP P;
	AddressS P1;
	
	/* algoritma */
	P = FirstP(*L);
	i = KotaMin;
	// pengulangan berhenti jika menemukan kota anggota list sabotage
	// atau telah mencapai ujung array TabKota
	while (i<= KotaMax)
	{
		if (OwnerKota(T, i)==PlayerId(P))
		{
			P1 = Search(*LS,i);
			if (P1 != Nil)
			{
				DeleteP(LS,i);
			} else
			{
				i++;
			}
		} else
		{
			i++;
		}
	}
}

void LoadSabotage(ListSabotage *X)
{
    char *input = "sabotage.txt";
    //AddressS P;
	id XS;
	
    FirstS(*X) = Nil;

    STARTKATA(input);

    while(!EOP())
    {
        ADVKATA();
        XS = bil(CKata.TabKata[0]);
        InsVFirst(X, XS);
        ADVKATA();
    }
}

void saveosabotage(ListSabotage X)
{
        FILE *file;
        AddressS P;

        remove("sabotage.txt");
        file = fopen("sabotage.txt", "w");

        P = FirstS(X);

        while(P!=Nil){
            fprintf(file,"> ");
            fprintf(file,"%d \n",IdS(P));
            P = NextS(P);
        }
        fprintf(file,".");
        fclose(file); //tutup file
}
