/* NIM/Nama		:  */
/* Nama file	:  */
/* Topik		:  */
/* Tanggal		:  */
/* Deskripsi	:  */

#ifndef mesinkar_h
#define mesinkar_h

#include <stdio.h>
#include "../bool/boolean.h"

#define MARK '.'

/* State Mesin */
char CC;

void close();

void START(char *filename);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
   Jika CC != MARK maka EOP akan padam (false)
   Jika CC = MARK maka EOP akan menyala (true) */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
   CC mungkin = MARK
   Jika  CC = MARK maka EOP akan menyala (true) */

boolean EOP();
/*	true jika CC==mark */

#endif
