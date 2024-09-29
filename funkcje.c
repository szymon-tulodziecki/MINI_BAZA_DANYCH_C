#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include "funkcje.h"

void menu(Plik *LAPTOPY_BAZA) {
    int k, opcja;
    do {
        printf("==========MINIBAZA==========\n");
        printf("1. Otworz baze danych\n");
        printf("2. Utworz nowa baze\n");
        printf("3. Przeglad bazy\n");
        printf("4. Sortowanie bazy\n");
        printf("5. Usun baze\n");
        printf("6. Zakoncz program\n");
        printf("Wybierz opcje: ");
        k = scanf("%d", &opcja);
        if (k != 1 || opcja < 1 || opcja > 6) {
            system("cls");
            printf("Niepoprawna opcja... \n");
            while (getchar() != '\n');
        }
    } while (k != 1 || opcja < 1 || opcja > 6);

    switch (opcja) {
        case 1:
            otworzBaze(LAPTOPY_BAZA);
            break;

        case 2:
            utworzBaze(LAPTOPY_BAZA);
            break;

        case 3:
            przegladBazy(LAPTOPY_BAZA);
            break;

        case 4:
            sortowanieBazy(LAPTOPY_BAZA);
            break;

        case 5:
            usunBaze(LAPTOPY_BAZA);
            break;

        case 6:
            printf("Zakonczono program...\n");
            exit(0);
            break;
    }
}

void utworzBaze(Plik *LAPTOPY_BAZA) {
        if(czyZamknacBaze(LAPTOPY_BAZA)){

            char nowaNazwaBazy[11];
            printf("Podaj nazwe nowej bazy (bazaXX.dat): ");
            scanf("%10s", nowaNazwaBazy);
            getchar();

            if (!sprawdzNazweBazy(nowaNazwaBazy)) {
                system("cls");
                printf("Nazwa bazy jest niepoprawna.\n");
                return;
            }

            FILE *plik = fopen(nowaNazwaBazy, "r+b");
            if (plik != NULL) {
                fclose(plik);
                system("cls");
                printf("Plik o tej nazwie już istnieje.\n");
                return;
            }
            plik = fopen(nowaNazwaBazy, "w+b");
            if (plik == NULL) {
                system("cls");
                printf("Blad tworzenia pliku minibazy.\n");
                return;
            }

            LAPTOPY_BAZA->bazaOtwarta = 1;
            LAPTOPY_BAZA->otwartyPlik = plik;

            strcpy(LAPTOPY_BAZA->nazwaOtwartejBazy, nowaNazwaBazy);
            Laptop default_laptops[5] = {
                {"Dell", "Inspiron 15", 8, 512, 2999.99, 23, 1},
                {"HP", "Pavilion 14", 16, 1024, 3599.99, 23, 2},
                {"Apple", "MacBook Air", 8, 256, 4999.99, 23, 3},
                {"Lenovo", "ThinkPad X1", 16, 512, 4999.99, 23, 4},
                {"Asus", "ZenBook 13", 8, 512, 3999.99, 23, 5}
            };

            fseek(plik, 0, SEEK_SET);
            for(int i = 0; i < 5; i++){
                fwrite(&default_laptops[i], sizeof(Laptop), 1, plik);
            }
            system("cls");
            printf("Nowa baza danych zostala utworzona: %s\n", nowaNazwaBazy);
            przegladBazy(LAPTOPY_BAZA);
        }
        else{
            return;
        }
    }

int sprawdzNazweBazy(char* nazwaBazy) {
    char lan1[5], lan2[3], lan3[5];

    if (strlen(nazwaBazy) != 10) {
        return 0;
    }

    strncpy(lan1, nazwaBazy, 4);
    lan1[4] = '\0';

    strncpy(lan2, nazwaBazy + 4, 2);
    lan2[2] = '\0';

    strcpy(lan3, nazwaBazy + 6);

    if (strcmp(lan1, "baza") != 0) {
        return 0;
    }

    if (!isdigit(lan2[0]) || !isdigit(lan2[1])) {
        return 0;
    }

    if (strcmp(lan3, ".dat") != 0) {
        return 0;
    }

    return 1;
}

void usunBaze(Plik *LAPTOPY_BAZA) {
    if(czyZamknacBaze(LAPTOPY_BAZA)){
        char nazwaBazy[11];
        printf("Podaj nazwe bazy do usuniecia: ");
        scanf("%10s", nazwaBazy);
        while (getchar() != '\n');

        if (!sprawdzNazweBazy(nazwaBazy)) {
            system("cls");
            printf("Nazwa bazy jest niepoprawna.\n");
            return;
        }

        FILE *plik = fopen(nazwaBazy, "r+b");
        if (plik == NULL) {
            system("cls");
            printf("Plik o tej nazwie nie istnieje.\n");
            return;
        }

        fclose(plik);
        if (remove(nazwaBazy) == 0) {
            system("cls");
            printf("Plik minibazy %s zostal usuniety.\n", nazwaBazy);
        } else {
            system("cls");
            printf("Blad usuwania pliku minibazy %s.\n", nazwaBazy);
        }
    }
}

int czyZamknacBaze(Plik *LAPTOPY_BAZA) {
    if (LAPTOPY_BAZA->bazaOtwarta == 1) {
        printf("Zamknac baze danych %s? (T/N): ", LAPTOPY_BAZA->nazwaOtwartejBazy);
        char odpowiedz;
        scanf(" %c", &odpowiedz);
        while (getchar() != '\n');

        if (toupper(odpowiedz) == 'T') {
            fclose(LAPTOPY_BAZA->otwartyPlik);
            LAPTOPY_BAZA->bazaOtwarta = 0;
            LAPTOPY_BAZA->nazwaOtwartejBazy[0] = '\0';
            LAPTOPY_BAZA->otwartyPlik = NULL;
            return 1;
        } else {
            system("cls");
            return 0;
        }
    }
    system("cls");
    return 1;
}

void przegladBazy(Plik *LAPTOPY_BAZA) {
    if (!LAPTOPY_BAZA->bazaOtwarta) {
        printf("Zadna baza nie jest otwarta.\n");
        return;
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_END);
    int iloscStruktur = ftell(LAPTOPY_BAZA->otwartyPlik) / sizeof(Laptop);
    Laptop *oryginalnaBaza = (Laptop *)malloc(iloscStruktur * sizeof(Laptop));
    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
    fread(oryginalnaBaza, sizeof(Laptop), iloscStruktur, LAPTOPY_BAZA->otwartyPlik);

    Laptop laptop;
    int pozycja = 0;
    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);

    while (1) {
        fseek(LAPTOPY_BAZA->otwartyPlik, pozycja * sizeof(Laptop), SEEK_SET);
        if (fread(&laptop, sizeof(Laptop), 1, LAPTOPY_BAZA->otwartyPlik) != 1) {
            printf("Koniec bazy danych.\n");
            break;
        }

        system("cls");
        wyswietlLaptop(&laptop);

        printf("Nacisnij klawisz:\n");
        printf("Y - Poprzedni\n");
        printf("B - Nastepny\n");
        printf("G - Poczatek\n");
        printf("H - Koniec\n");
        printf("D - Dopisz nowa strukture\n");
        printf("U - Usun biezaca strukture\n");
        printf("M - Modyfikuj biezaca strukture\n");
        printf("Q - Wyjdz\n");

       char ch = getch();

        switch (ch) {
            case 'Y': case 'y':
                if (pozycja > 0) pozycja--;
                break;
            case 'B': case 'b':
                fseek(LAPTOPY_BAZA->otwartyPlik, (pozycja + 1) * sizeof(Laptop), SEEK_SET);
                if (fread(&laptop, sizeof(Laptop), 1, LAPTOPY_BAZA->otwartyPlik) == 1) {
                    pozycja++;
                }
                break;
            case 'G': case  'g':
                pozycja = 0;
                break;
            case 'H': case 'h':
                fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_END);
                pozycja = ftell(LAPTOPY_BAZA->otwartyPlik) / sizeof(Laptop) - 1;
                break;
            case 'D': case 'd':
                dopiszStrukture(LAPTOPY_BAZA, pozycja);
                break;
            case 'U': case 'u':
                usunStrukture(LAPTOPY_BAZA, pozycja);
                if (pozycja > 0) pozycja--;
                break;
            case 'M': case 'm':
                modyfikujStrukture(LAPTOPY_BAZA, pozycja);
                break;
            case 'Q': case 'q':
                czyZapisac(LAPTOPY_BAZA, oryginalnaBaza, iloscStruktur);
                free(oryginalnaBaza);
                system("cls");
                return;
            default:
                printf("Niepoprawna opcja.\n");
                break;
        }}

}

void wyswietlLaptop(const Laptop *laptop) {
    printf("ID: %d\n", laptop->id);
    printf("Producent: %s\n", laptop->nazwa_producenta);
    printf("Model: %s\n", laptop->model);
    printf("RAM: %d GB\n", laptop->ram);
    printf("Pojemnosc: %d GB\n", laptop->pojemnosc);
    printf("Cena: %.2f PLN\n", laptop->cena);
    printf("VAT: %d%%\n", laptop->vat);
    printf("-----------------------------\n");
}

void otworzBaze(Plik *LAPTOPY_BAZA) {
    if(czyZamknacBaze(LAPTOPY_BAZA)){
        char nazwaBazy[11];
        printf("Podaj nazwe bazy do otwarcia: ");
        scanf("%10s", nazwaBazy);
        while (getchar() != '\n');

        if (!sprawdzNazweBazy(nazwaBazy)) {
            system("cls");
            printf("Nazwa bazy jest niepoprawna.\n");
            return;
        }

        FILE *plik = fopen(nazwaBazy, "r+b");
        if (plik == NULL) {
            system("cls");
            printf("Plik o tej nazwie nie istnieje.\n");
            return;
        }

        LAPTOPY_BAZA->bazaOtwarta = 1;
        LAPTOPY_BAZA->otwartyPlik = plik;
        strcpy(LAPTOPY_BAZA->nazwaOtwartejBazy, nazwaBazy);

        system("cls");
        printf("Baza danych %s zostala otwarta.\n", nazwaBazy);
        przegladBazy(LAPTOPY_BAZA);
    }
}

void wyswietlBaze(Laptop *baza, int iloscStruktur, const char *tytul) {
    printf("%s:\n", tytul);
    for (int i = 0; i < iloscStruktur; i++) {
         printf("ID: %d, Producent: %s, Model: %s, RAM: %d, Pojemnosc: %d, Cena: %.2f\n",
             baza[i].id, baza[i].nazwa_producenta, baza[i].model, baza[i].ram, baza[i].pojemnosc, baza[i].cena);
         printf("\n");
    }
    printf("\n");
}

void sortowanieBazy(Plik *LAPTOPY_BAZA) {
    system("cls");
    if (!LAPTOPY_BAZA->bazaOtwarta) {
        printf("Brak otwartej bazy danych.\n");
        return;
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_END);
    long rozmiarPliku = ftell(LAPTOPY_BAZA->otwartyPlik);
    int iloscStruktur = rozmiarPliku / sizeof(Laptop);

    Laptop *laptops = (Laptop*)malloc(rozmiarPliku);
    Laptop *oryginalnaBaza = (Laptop*)malloc(rozmiarPliku);

    if (laptops == NULL || oryginalnaBaza == NULL) {
        printf("Blad alokacji pamieci.\n");
        return;
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
    fread(laptops, sizeof(Laptop), iloscStruktur, LAPTOPY_BAZA->otwartyPlik);
    memcpy(oryginalnaBaza, laptops, rozmiarPliku);

    wyswietlBaze(oryginalnaBaza, iloscStruktur, "Przed sortowaniem");

    int opcjaSortowania, k;

    do {
        printf("Menu Sortowania\n");
        printf("1. Alfabetycznie po producencie\n");
        printf("2. Alfabetycznie po modelu\n");
        printf("3. Po pojemnosci\n");
        printf("4. Po cenie\n");
        printf("Wybierz opcje: ");
        k = scanf("%d", &opcjaSortowania);
        if (k != 1 || opcjaSortowania < 1 || opcjaSortowania > 4) {
            printf("Niepoprawna opcja... Nacisnij dowolny klawisz, aby sprobowac raz jeszcze...\n");
            while (getchar() != '\n');
        }
        getchar();
    } while (k != 1 || opcjaSortowania < 1 || opcjaSortowania > 4);

    switch (opcjaSortowania) {
        case 1:
            qsort(laptops, iloscStruktur, sizeof(Laptop), porownajProducent);
            break;
        case 2:
            qsort(laptops, iloscStruktur, sizeof(Laptop), porownajModel);
            break;
        case 3:
            qsort(laptops, iloscStruktur, sizeof(Laptop), porownajPojemnosc);
            break;
        case 4:
            qsort(laptops, iloscStruktur, sizeof(Laptop), porownajCene);
            break;
        default:
            printf("Niepoprawna opcja sortowania.\n");
            free(laptops);
            free(oryginalnaBaza);
            return;
    }

    for (int i = 0; i < iloscStruktur; i++) {
        laptops[i].id = i + 1;
    }

    wyswietlBaze(laptops, iloscStruktur, "\nPo sortowaniu");

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
    fwrite(laptops, sizeof(Laptop), iloscStruktur, LAPTOPY_BAZA->otwartyPlik);
    fflush(LAPTOPY_BAZA->otwartyPlik);

    czyZapisac(LAPTOPY_BAZA, oryginalnaBaza, iloscStruktur);

    free(laptops);
    free(oryginalnaBaza);
    system("cls");
}

int porownajProducent(const void *a, const void *b) {
    Laptop *laptop1 = (Laptop *)a;
    Laptop *laptop2 = (Laptop *)b;
    return strcmp(laptop1->nazwa_producenta, laptop2->nazwa_producenta);
}

int porownajModel(const void *a, const void *b) {
    Laptop *laptop1 = (Laptop *)a;
    Laptop *laptop2 = (Laptop *)b;
    return strcmp(laptop1->model, laptop2->model);
}

int porownajPojemnosc(const void *a, const void *b) {
    Laptop *laptop1 = (Laptop *)a;
    Laptop *laptop2 = (Laptop *)b;
    return laptop1->pojemnosc - laptop2->pojemnosc;
}

int porownajCene(const void *a, const void *b) {
    Laptop *laptop1 = (Laptop *)a;
    Laptop *laptop2 = (Laptop *)b;
    if (laptop1->cena < laptop2->cena) return -1;
    if (laptop1->cena > laptop2->cena) return 1;
    return 0;
}

void czyZapisac(Plik *LAPTOPY_BAZA, Laptop *oryginalnaBaza, int iloscStruktur) {
    char decyzja;
    printf("Czy chcesz zapisac zmiany? (T/N): ");
    decyzja = getch();
    switch(decyzja){
        case 'T': case 't':
        printf("Zmiany zapisane.\n");
        break;
        case 'N': case 'n':
        printf("Zmiany nie zostana zapisane.\n");
        fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
        fwrite(oryginalnaBaza, sizeof(Laptop), iloscStruktur, LAPTOPY_BAZA->otwartyPlik);
        fflush(LAPTOPY_BAZA->otwartyPlik);
        break;
        default:
        printf("Niepoprawna opcja.\n");
        break;

    }

}

void dopiszStrukture(Plik *LAPTOPY_BAZA, int pozycja){
    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_END);
    long rozmiarPliku = ftell(LAPTOPY_BAZA->otwartyPlik);
    int iloscStruktur = rozmiarPliku / sizeof(Laptop);
    Laptop *laptops = (Laptop*)malloc(rozmiarPliku);
    Laptop *oryginalnaBaza = (Laptop*)malloc(rozmiarPliku);

    if (laptops == NULL || oryginalnaBaza == NULL) {
        printf("Blad alokacji pamieci.\n");
        return;
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
    fread(laptops, sizeof(Laptop), iloscStruktur, LAPTOPY_BAZA->otwartyPlik);
    memcpy(oryginalnaBaza, laptops, rozmiarPliku);

    Laptop nowyLaptop;
    printf("Podaj producenta: ");
    scanf("%19s", nowyLaptop.nazwa_producenta);
    while (getchar() != '\n');
    printf("Podaj model: ");
    scanf("%19s", nowyLaptop.model);
    while (getchar() != '\n');
    printf("Podaj RAM: ");
    scanf("%d", &nowyLaptop.ram);
    while (getchar() != '\n');
    printf("Podaj pojemnosc: ");
    scanf("%d", &nowyLaptop.pojemnosc);
    while (getchar() != '\n');
    printf("Podaj cene: ");
    scanf("%lf", &nowyLaptop.cena);
    while (getchar() != '\n');
    printf("Podaj VAT: ");
    scanf("%d", &nowyLaptop.vat);
    while (getchar() != '\n');

    nowyLaptop.id = iloscStruktur + 1;

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_END);
    fwrite(&nowyLaptop, sizeof(Laptop), 1, LAPTOPY_BAZA->otwartyPlik);
    fflush(LAPTOPY_BAZA->otwartyPlik);

    free(laptops);
    free(oryginalnaBaza);
    system("cls");
    printf("Nowa struktura zostala dodana.\n");
}

void usunStrukture(Plik *LAPTOPY_BAZA, int pozycja){
    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_END);
    long rozmiarPliku = ftell(LAPTOPY_BAZA->otwartyPlik);
    int iloscStruktur = rozmiarPliku / sizeof(Laptop);
    Laptop *laptops = (Laptop*)malloc(rozmiarPliku);
    Laptop *oryginalnaBaza = (Laptop*)malloc(rozmiarPliku);

    if (laptops == NULL || oryginalnaBaza == NULL) {
        printf("Blad alokacji pamieci.\n");
        return;
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
    fread(laptops, sizeof(Laptop), iloscStruktur, LAPTOPY_BAZA->otwartyPlik);
    memcpy(oryginalnaBaza, laptops, rozmiarPliku);

    for (int i = pozycja; i < iloscStruktur - 1; i++) {
        laptops[i] = laptops[i + 1];
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
    fwrite(laptops, sizeof(Laptop), iloscStruktur - 1, LAPTOPY_BAZA->otwartyPlik);
    fflush(LAPTOPY_BAZA->otwartyPlik);

    free(laptops);
    free(oryginalnaBaza);
    system("cls");
    printf("Struktura zostala usunieta.\n");
}

void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void wyswietlRekord(Laptop *laptop, int x, int y) {
    gotoxy(x, y);
    printf("1. Producent: %s", laptop->nazwa_producenta);
    gotoxy(x, y + 1);
    printf("2. Model: %s", laptop->model);
    gotoxy(x, y + 2);
    printf("3. RAM: %d", laptop->ram);
    gotoxy(x, y + 3);
    printf("4. Pojemnosc: %d", laptop->pojemnosc);
    gotoxy(x, y + 4);
    printf("5. Cena: %.2f", laptop->cena);
    gotoxy(x, y + 5);
    printf("6. VAT: %d", laptop->vat);
}

void modyfikujStrukture(Plik *LAPTOPY_BAZA, int pozycja) {
    if (!LAPTOPY_BAZA->bazaOtwarta) {
        printf("Brak otwartej bazy danych.\n");
        return;
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_END);
    long rozmiarPliku = ftell(LAPTOPY_BAZA->otwartyPlik);
    int iloscStruktur = rozmiarPliku / sizeof(Laptop);

    if (pozycja < 0 || pozycja >= iloscStruktur) {
        printf("Niepoprawna pozycja.\n");
        return;
    }

    Laptop *laptops = (Laptop*)malloc(rozmiarPliku);
    if (laptops == NULL) {
        printf("Blad alokacji pamieci.\n");
        return;
    }

    fseek(LAPTOPY_BAZA->otwartyPlik, 0, SEEK_SET);
    fread(laptops, sizeof(Laptop), iloscStruktur, LAPTOPY_BAZA->otwartyPlik);

    Laptop *laptop = &laptops[pozycja];
    int x = 10, y = 5;

    char wybor;
    do {
        system("cls");
        wyswietlRekord(laptop, x, y);
        gotoxy(x, y + 6);
        printf("Podaj nr pola (lub ESC aby anulowac, 7 aby wyjsc): ");

        wybor = getchar();
        if (wybor == 27) {
            break;
        }
        while (getchar() != '\n');
        gotoxy(x, y + 8);
        switch (wybor) {
            case '1':
                printf("Podaj nowego producenta: ");
                scanf("%19s", laptop->nazwa_producenta);
                break;
            case '2':
                printf("Podaj nowy model: ");
                scanf("%19s", laptop->model);
                break;
            case '3':
                printf("Podaj nowy RAM: ");
                while (scanf("%d", &laptop->ram) != 1) {
                    printf("Niepoprawny format. Podaj RAM: ");
                    while (getchar() != '\n');
                }
                break;
            case '4':
                printf("Podaj nowa pojemnosc: ");
                while (scanf("%d", &laptop->pojemnosc) != 1) {
                    printf("Niepoprawny format. Podaj pojemnosc: ");
                    while (getchar() != '\n');
                }
                break;
            case '5':
                printf("Podaj nowa cene: ");
                while (scanf("%lf", &laptop->cena) != 1) {
                    printf("Niepoprawny format. Podaj cene: ");
                    while (getchar() != '\n');
                }
                break;
            case '6':
                printf("Podaj nowy VAT: ");
                while (scanf("%d", &laptop->vat) != 1) {
                    printf("Niepoprawny format. Podaj VAT: ");
                    while (getchar() != '\n');
                }
                break;
            case '7':
                wybor = 27;
                break;
            default:
                printf("Niepoprawny numer pola.\n");
                break;
        }

        fseek(LAPTOPY_BAZA->otwartyPlik, pozycja * sizeof(Laptop), SEEK_SET);
        fwrite(laptop, sizeof(Laptop), 1, LAPTOPY_BAZA->otwartyPlik);
        fflush(LAPTOPY_BAZA->otwartyPlik);

    } while (wybor != 27);

    free(laptops);
    gotoxy(x, y + 10);
    printf("Struktura zostala zmodyfikowana.\n");
}
