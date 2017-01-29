#include "str.h"

void STARTSTD() {
	scanf("%c", &CC);
}

void ADVSTD() {
    if (!EOPS()) {
		scanf("%c", &CC);
    }
}

boolean EOPS() {
	return CC == Mark;
}

void ig_blank() {
	while (CC == Blank) {
		ADVSTD();
	}
}

void StartS() {
	STARTSTD();
	if (!EOPS()) {
		ig_blank();
		CopyS();
	}
}

void AdvS() {
    ig_blank();
    CopyS();
}

void CopyS() {
	int i;

	for (i=0; i<Length(S); i++) {
		String(S,i) = '\0';
	}
	Length(S) = 0;
	while (!EOPS() && CC != Blank) {
		if (Length(S) < NMax) {
			Length(S) += 1;
			String(S,Length(S)-1) = CC;
		}
		ADVSTD();
	}
}

int LS (char *arg) {
    int i, l;

    i = 0;
    l = 0;
    while (arg[i] != '\0') {
        l++;
        i++;
    }
    return l;
}

boolean CompS(Str S, char *arg) {
	int i = 0;

    if (Length(S) == LS(arg)) {
        if (String(S,i) != '\0') {
            while (i < Length(S) && String(S,i) == arg[i]) {
                i++;
            }
            if (i == Length(S)) {
                return true;
            }
            else return false;
            }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void readS (int *x, char **arg) {
/* Membaca sebuah string dari user, kemudian mengubahkan ke dalam bentuk command dan argumen2
 * contoh string yang dibaca adalah roll dice
 * */
    *arg = malloc(NMax);
    StartS();
    if (CompS(S,"roll")) {
        AdvS();
        if (CompS(S,"dice")) {
            *x = 1;
        }
        else {
            *x = 0;
        }
        *arg = '\0';
    }
    else if (CompS(S,"info")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 0;
            *arg = '\0';
        }
        else {
            *x = 2;
            *arg = StringS(S);
        }
    }
    else if (CompS(S,"buy")) {
        AdvS();
        if (CompS(S,"offered")) {
            AdvS();
            if (String(S,0) == '\0') {
                *x = 0;
                *arg = '\0';
            }
            else {
                *x = 7;
                *arg = StringS(S);
            }
        }
        else if (String(S,0) == '\0') {
            *x = 3;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else if (CompS(S,"sell")) {
        AdvS();
        if (CompS(S,"bank")) {
            AdvS();
            if (String(S,0) == '\0') {
                *x = 0;
                *arg = '\0';
            }
            else {
                *x = 5;
                *arg = StringS(S);
            }
        }
        else if (String(S,0) == '\0') {
            *x = 0;
            *arg = '\0';
        }
        else {
            *x = 4;
            *arg = StringS(S);
        }
    }
    else if (CompS(S,"show")) {
        AdvS();
        if (CompS(S,"offered")) {
            *x = 6;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else if (CompS(S,"upgrade")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 8;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else if (CompS(S,"board")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 12;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else if (CompS(S,"leaderboard")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 13;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else if (CompS(S,"end")) {
        AdvS();
        if (CompS(S,"turn")) {
            *x = 16;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else if (CompS(S,"save")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 0;
            *arg = '\0';
        }
        else {
            *x = 17;
            *arg = StringS(S);
        }
    }
    else if (CompS(S,"off")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 0;
            *arg = '\0';
        }
        else {
            *x = 22;
            *arg = StringS(S);
        }
    }
    else if (CompS(S,"protect")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 0;
            *arg = '\0';
        }
        else {
            *x = 23;
            *arg = StringS(S);
        }
    }
    else if (CompS(S,"help")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 24;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else if (CompS(S,"quit")) {
        AdvS();
        if (String(S,0) == '\0') {
            *x = 25;
            *arg = '\0';
        }
        else {
            *x = 0;
            *arg = '\0';
        }
    }
    else {
        *x = 0;
        *arg = '\0';
    }
}
