
#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <stdio.h>

typedef struct Laptop {
    char nazwa_producenta[20];
    char model[20];
    int ram;
    int pojemnosc;
    double cena;
    int vat;
    int id;
} Laptop;

typedef struct Plik {
    int bazaOtwarta;
    char nazwaOtwartejBazy[20];
    FILE* otwartyPlik;
} Plik;

void menu(Plik *LAPTOPY_BAZA);
void utworzBaze(Plik *LAPTOPY_BAZA);
int sprawdzNazweBazy(char* nazwaBazy);
void przegladBazy(Plik *LAPTOPY_BAZA);
void sortowanieBazy(Plik *LAPTOPY_BAZA);
void usunBaze(Plik *LAPTOPY_BAZA);
void otworzBaze(Plik *LAPTOPY_BAZA);
int czyZamknacBaze(Plik *LAPTOPY_BAZA);
int porownajCene(const void *a, const void *b);
int porownajPojemnosc(const void *a, const void *b);
int porownajModel(const void *a, const void *b);
void wyswietlLaptop(const Laptop *laptop);
void dopiszStrukture(Plik *LAPTOPY_BAZA, int pozycja);
void usunStrukture(Plik *LAPTOPY_BAZA, int pozycja);
void modyfikujStrukture(Plik *LAPTOPY_BAZA, int pozycja);
int porownajProducent(const void *a, const void *b);
void czyZapisac(Plik *LAPTOPY_BAZA, Laptop *oryginalnaBaza, int iloscStruktur);
void gotoxy(short x, short y);
void wyswietlRekord(Laptop *laptop, int x, int y);

#endif //FUNKCJE_H
