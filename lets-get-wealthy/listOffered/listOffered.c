#include "listOffered.h"

boolean isEmptyO (ListOffered Lo)
//mengembalikan seperti biasa
{
	if (FirstO(Lo) == Nil)
		return true;
	else
		return false;
}

AddressO AlokasiO (id X){
/*	Mengirimkan Address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka Address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/
	//KAMUS
	AddressO P;
	
	//ALGORITMA
	P = (AddressO) malloc (sizeof(ElmtListOffered));
	
	if (P == Nil) {
		return Nil;
	} else {
		Id(P) = X;
		NextO(P) = Nil;
		return P;
	}
}

void DealokasiO (AddressO *P){
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian Address P
*/
	//KAMUS
	//ALGORITMA
	free(*P);
}

void DeleteAfterO (ListOffered *L, AddressO *Pdel, AddressO Prec){
/*	I.S. List tidak kosong. Prec adalah anggota list L.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen list yang dihapus
*/
	//KAMUS
	//ALGORITMA
	(*Pdel) = NextO(Prec);
	NextO(Prec) = NextO(NextO(Prec));
	NextO(*Pdel) = Nil;
}

void DeleteFirstO (ListOffered *L, AddressO *P){
/*	I.S. List tidak kosong
	F.S. P adalah alamat elemen pertama list sebelum penghapusan
	Elemen list berkurang satu (mungkin menjadi kosong)
	First element yang baru adalah suksesor elemen pertama yang lama
*/
	//KAMUS
	//ALGORITMA
	(*P) = FirstO(*L);
	FirstO(*L) = NextO(FirstO(*L));
	NextO(*P) = Nil;
}

void InsertFirstO (ListOffered *L, AddressO P) {
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-Address P sebagai elemen pertama
*/
	//KAMUS
	//ALGORITMA
	NextO(P) = FirstO(*L);
	FirstO(*L) = P;
}

void buyOffered(char Pid, ListPlayer *P, Kota *K, ListOffered *Lo, char* namakota)
/*Membeli sebuah kota dari list offered*/
/*I.S. List Offered tidak kosong*/
/*F.S. Kota dibeli jika uang player cukup*/
{
	AddressP PA = SearchPlayerid(*P, Pid);
	AddressP PA1;
	AddressO Po = FirstO(*Lo);
	AddressO Prec = Nil;
	boolean found = false;
	int idB;
	long price;
	
	while (Po != Nil && !found) {
		found = strcmp(namakota, NamaKota(*K, Id(Po))) == 0;
		if (!found) {
			Prec = Po;
			Po = NextO(Po);
		}
	}
	if (found) {	
		idB = Id(Po);
		price = hargaTotal(*K, idB);
		if (Money(PA) >= price) { //beli sukses
			PA1 = SearchPlayerid(*P, OwnerKota(*K, idB));
			OwnerKota(*K, idB) = PlayerId(PA);
			Money(PA) -= price;
			Money(PA1) += price;
			BlokPlayer(PA, BlokKota(*K, idB))++;
			BlokPlayer(PA1, BlokKota(*K, idB))--;
			printf("  Selamat, kota %s sekarang menjadi milikmu!\n", NamaKota(*K, idB)); 
			printf("  Sisa uangmu adalah: ");  tulisNominal(Money(PA)); printf("\n");
			printf("  Player %c mendapatkan uang sebesar ", PlayerId(PA1));
			tulisNominal(price);
			printf("  dari penjualan kota %s!", NamaKota(*K, idB)); printf("\n");
			//delete elemen dari list offered
			if (Prec != Nil) //bukan elemen pertama
				DeleteAfterO(Lo, &Po, Prec);
			else //elemen pertama
				DeleteFirstO(Lo, &Po);
			DealokasiO(&Po);
		} else  { //uang kurang
			printf("  Maaf, uang anda tidak mencukupi untuk membeli kota %s\n", NamaKota(*K, idB));
			printf("  Sisa uangmu adalah: \n");  tulisNominal(Money(PA)); 
			printf("  Harga pembelian kota %s adalah: ", NamaKota(*K, idB));  tulisNominal(price); printf("\n");
		}
	} else
		printf("Kota %s tidak ada di List Offered!\n", namakota);
}

void sellOffered (ListPlayer Lp, char Pid, Kota K, ListBoard Lb, char* namakota, ListOffered *Lo)
/*Menyimpan petak dengan nama namakota ke list offered*/
/*Kalo namakota engga ada atau punya pemain lain maka tulis pesan kesalahan*/
{
	AddressB PB = SearchNamaKota(Lb, K, namakota);
	AddressO PO;
	
	if (PB != Nil) { //ketemu
		if (Pid == OwnerKota(K, PetakId(PB))) { //punya sendiri
			PO = AlokasiO(PetakId(PB));
			if (PO != Nil) { //berhasil alokasi
				InsertFirstO(Lo, PO);
				printf("  %s berhasil dimasukkan ke list offered!\n", namakota);
			} else
				printf("  Maaf, proses gagal, silahkan mencoba lagi\n");
		} else
			printf("  Anda tidak bisa memasukkan petak milik pemain lain ke List Offered!\n");		
	} else //ga ada namakota di list
		printf("Tidak ada kota bernama %s di permainan ini!\n", namakota);
}

void showOffered (ListOffered Lo, Kota K)
/*Menuliskan isi dari List offered*/
{
	AddressO Po = FirstO(Lo);
	int i = 1;
	long price;
	
	if (isEmptyO(Lo))
		printf("  List Offered kosong\n");
	else {
		while (Po != Nil) {
			price = hargaTotal(K, Id(Po));
			printf("%d. %s harga: ", i, NamaKota(K, Id(Po))); tulisNominal(price); printf("\n");
			i++;
			Po = NextO(Po);
		}
	}	
}

void Loadoffered(ListOffered *X)
{
    char *input = "offered.txt";
    //AddressO P;
	id XO;
	
    FirstO(*X) = Nil;

    STARTKATA(input);

    while(!EOP())
    {
        ADVKATA();
        XO = bil(CKata.TabKata[0]);
        AlokasiO(XO);
        ADVKATA();
    }
}

void saveoffered(ListOffered X)
{
        FILE *file;
        //int i;
        AddressO P;

        remove("offered.txt");
        file = fopen("offered.txt", "w");

        P = FirstO(X);

        while(P!=Nil){
            fprintf(file,"> ");
            fprintf(file,"%d \n",Id(P));
            P = NextO(P);
        }

        fprintf(file,".");
        fclose(file); //tutup file
}
