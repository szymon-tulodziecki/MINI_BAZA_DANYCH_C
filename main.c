#include "funkcje.h"
#include <stdio.h>


int main() {
    Plik LAPTOPY_BAZA;
    LAPTOPY_BAZA.bazaOtwarta = 0;
    LAPTOPY_BAZA.nazwaOtwartejBazy[0] = '\0';
    LAPTOPY_BAZA.otwartyPlik = NULL;

    while(1) {
        menu(&LAPTOPY_BAZA);
    }
}
