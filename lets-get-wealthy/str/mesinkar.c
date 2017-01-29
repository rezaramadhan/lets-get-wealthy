/* NIM/Nama		:  */
/* Nama file	:  */
/* Topik		:  */
/* Tanggal		:  */
/* Deskripsi	:  */

#include "mesinkar.h"

FILE *fp;

void START(char *filename)
/* 	I.S. sembarang
	F.S. CC adalah karakter pertama pita (stdin)
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
{
	
	fp = fopen(filename, "r");
	CC = fgetc(fp);
}

void ADV()
/*	I.S. CC!=mark
	F.S. CC adalah karakter berikutnya yang dapat diakuisisi
		 contoh untuk pita "IF", bila CC menunjuk 'I', maka CC berikutnya adalah 'F'
		 Bila Kondisi EOP terpenuhi, nyalakan EOP
*/
{
	CC = fgetc(fp);
}

boolean EOP()
/*	true jika CC==mark */
{
	if(CC==MARK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void close()
{
    fclose(fp);
}

