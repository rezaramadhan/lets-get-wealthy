#include "arrKota.h"

void tulisNominal (long l) {
	long lt;
	long li = l;
	boolean f =false;

	lt = li/1000000000;
	if (lt > 0) {
		printf("%liB ", lt); //billion
		li = li%1000000000;
		f = true;
	}
	lt = li/1000000;
	if (lt > 0) {
		printf("%liM ", lt); //million
		li = li%1000000;
		f = true;
	}
	lt = li/1000;
	if (lt > 0) {
		printf("%liK ", lt); //kilo
		li = li % 1000;
		f = true;
	}
	if (!f)
		printf("%li", li);
}

void printInfo (Kota K, char *name) {
/*  I.S. K terdefinisi, name merupakan input user
    F.S. Menampilkan data kota bernama name jika name ada di tabel kota
*/
    IdxType i = KotaMin;
    boolean found = false;

    while (i <= KotaMax && !found) {
        if (strcmp(name, NamaKota(K,i)) == 0) {
            found = true;
        }
        else i++;
    }
    if (!found) {
        printf("> Kota tidak ditemukan\n");
    }
    else {
        if (OwnerKota(K,i) != '0') {
            if (LevelKota(K,i) <= 3) {
                printf("> %s, pemilik properti %c, bangunan level %d\n", NamaKota(K,i), OwnerKota(K,i), LevelKota(K,i));
            }
            else {
                printf("> %s, pemilik properti %c\n", NamaKota(K,i), OwnerKota(K,i));
                printf("  Kota ini memiliki Landmark\n");
            }
        }
        else {
            printf("> %s, pemilik properti tidak ada\n", NamaKota(K,i));
        }
        printf("> Biaya sewa: "); tulisNominal(HargaKota(K,i)); printf("\n");
        if (BlokKota(K, i) == 0) {
            printf("> Kota ini rekreasi\n");
        }
        else {
            printf("> Blok kota: %d\n", BlokKota(K,i));
        }
        printf("> Biaya ambil alih: "); tulisNominal(hargaTotal(K,i)*2); printf("\n");
        if (OwnerKota(K,i) != '0') {
			printf("> Biaya upgrade bangunan: "); tulisNominal(hargaUpgrade(K,i)); printf("\n");
        }
    }
}

long hargaTotal(Kota K, int i)
/*Mencari nilai properti total sebuah kota*/
{
	long retval = (HargaKota(K, i))*LevelKota(K, i);
	return retval;
}

long hargaUpgrade(Kota K, int i)
/*Mencari harga untuk meng-upgrade sebuah kota*/
{
	long retval = (HargaKota(K, i))*(LevelKota(K, i) + 1);
	return retval;
}

boolean IsBlokDikuasai(Kota T, int blok)
/* menghasilkan true jika suatu blok dikuasai seseorang */
{
	/* kamus lokal */
	int i;
	boolean dikuasai;
	boolean found;
	char juragan;

	/* algoritma */
	dikuasai = true;

	// mencari indeks blok yg sesuai dan paling awal //
	i = KotaMin;
	found = false;
	while (i<= KotaMax && !found)
	{
		if (BlokKota(T, i) == blok)
		{
			found = true;
		} else
		{
			i++;
		}
	}

	//traversal sepanjang kota dengan blok sama //
	juragan = OwnerKota(T,i);
	while (BlokKota(T, i)==blok && dikuasai)
	{
		if (OwnerKota(T,i)==juragan)
		{
			dikuasai = true;
		} else
		{
			dikuasai = false;
		}
		i++;
	}

	if (dikuasai)		// blok dikuasai juragan
	{
		return true;
	} else 				// blok belum dikuasai
	{
		return false;
	}
}

void LoadKota(Kota *X, char *input)
{
    int i=1;
    long int b = 0;
    int j=1;

    STARTKATA(input);

    for(j=1;j<=23;j++)
    {
        b = 0;
        ADVKATA();

        for(i=0;i<CKata.Length;i++)
        {
            b = b*10 + bil(CKata.TabKata[i]);
        }
        (*X).TabKota[j].price = b;

        ADVKATA();

        strcpy((*X).TabKota[j].name,CKata.TabKata);
        ADVKATA();

        (*X).TabKota[j].blok = bil(CKata.TabKata[0]);
        ADVKATA();

        (*X).TabKota[j].level = bil(CKata.TabKata[0]);

        ADVKATA();

        if(strcmp(CKata.TabKata,"false")==0)
        {
            (*X).TabKota[j].host = false;
        }
        else
        {
            (*X).TabKota[j].host = true;
        }
        ADVKATA();

        if(strcmp(CKata.TabKata,"false")==0)
        {
            (*X).TabKota[j].rekreasi = false;
        }
        else
        {
            (*X).TabKota[j].rekreasi = true;
        }
		ADVKATA();

        (*X).TabKota[j].owner = CKata.TabKata[0];
    }
}

void savekota(Kota X)
{
        FILE *file;
        int pr; //harga kota
        int bl; //masuk blok apa kotak ini
        int lvl; //level bangunan di kota ini. 1-3 = rumah, 4 keatas landmark
        boolean rek; //apakah sebuah kota rekreasi atau bukan
        boolean h; //apakah sebuah kota jadi host world cup atau bukan
        char own;
        char nm[50]; //nama kota
        int i;

        remove("kota.txt");
        if((file = fopen("kota.txt", "a+")) == NULL)
        {
            printf("File kota.txt Tidak Ditemukan\n");
        }
        else
        {
            for(i=1;i<=23;i++)
            {
                pr = X.TabKota[i].price; //harga kota
                strcpy(nm,X.TabKota[i].name); //nama kota
                bl = X.TabKota[i].blok; //masuk blok apa kotak ini
                lvl = X.TabKota[i].level; //level bangunan di kota ini. 1-3 = rumah, 4 keatas landmark
                rek = X.TabKota[i].rekreasi; //apakah sebuah kota rekreasi atau bukan
                h = X.TabKota[i].host; //apakah sebuah kota jadi host world cup atau bukan
                own = X.TabKota[i].owner;

                fprintf(file,"> ");
                fprintf(file,"%d ",pr);
                fprintf(file,"%s ",nm);
                fprintf(file,"%d ",bl);
                fprintf(file,"%d ",lvl);

                if(h == true)
                {
                    fprintf(file,"true ");
                }
                else
                {
                    fprintf(file,"false ");
                }

                if(rek == true)
                {
                    fprintf(file,"true ");
                }
                else
                {
                    fprintf(file,"false ");
                }

                fprintf(file,"%c\n", own);
            }

        }
        fprintf(file, ".");
        fclose(file); //tutup file
}
