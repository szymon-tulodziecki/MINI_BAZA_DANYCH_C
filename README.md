# 💻 Mini Baza Danych Laptopów 📊

Aplikacja w C do zarządzania danymi o laptopach. Pozwala na tworzenie, przeglądanie, sortowanie i modyfikowanie bazy danych, z możliwością zapisu i odczytu z plików. Idealna do nauki operacji na plikach i podstawowych struktur danych w C! 🚀

[![GitHub Stars](https://img.shields.io/github/stars/szymon-tulodziecki/Mini-Baza-Danych?style=social)](https://github.com/szymon-tulodziecki/Mini-Baza-Danych)
[![GitHub Forks](https://img.shields.io/github/forks/szymon-tulodziecki/Mini-Baza-Danych?style=social)](https://github.com/szymon-tulodziecki/Mini-Baza-Danych)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## ✨ Funkcjonalności

*   **Dodawanie laptopów:** Dodawaj nowe rekordy laptopów do bazy danych. ➕
*   **Usuwanie laptopów:** Usuwaj istniejące rekordy z bazy danych. ➖
*   **Modyfikacja informacji:** Edytuj szczegóły istniejących laptopów (producent, model, RAM, pojemność, cena, VAT). ✏️
*   **Przeglądanie:** Wyświetlaj zawartość bazy danych laptopów, nawiguj po rekordach. 👁️‍🗨️
*   **Sortowanie:** Sortuj laptopy według różnych kryteriów (cena, model, pojemność, producent). ⇦ ⇧ ⇨
*   **Zapis i odczyt:** Zapisuj i odczytuj bazę danych z plików (obsługa formatu `.dat`). 💾

## ⚙️ Wymagania

*   Kompilator C (np. GCC)
*   CMake (opcjonalnie, jeśli używasz CMake do budowy projektu)
*   Biblioteki standardowe C (stdio.h, stdlib.h, string.h, ctype.h, windows.h)

## ⬇️ Instalacja

1.  Sklonuj repozytorium:

    ```
    git clone https://github.com/szymon-tulodziecki/Mini-Baza-Danych.git
    cd Mini-Baza-Danych
    ```

2.  Kompilacja (bez CMake):

    ```
    gcc main.c funkcje.c -o baza_laptopow
    ```

    Lub (z CMake, jeśli używasz):

    ```
    mkdir build
    cd build
    cmake ..
    make
    ```

## 💻 Użycie

Uruchom skompilowany program:

./baza_laptopow # Linux/macOS

baza_laptopow.exe # Windows


Postępuj zgodnie z instrukcjami w menu programu.

## 🗂️ Struktura plików

*   `main.c`: Główny plik programu, zawierający funkcję `main`.
*   `funkcje.c`: Implementacja funkcji zarządzających bazą danych laptopów.
*   `funkcje.h`: Plik nagłówkowy, deklaracje struktur i funkcji.
*   `README.md`: Ten plik, zawierający informacje o projekcie.
*   *(Opcjonalnie)* `CMakeLists.txt`: Plik konfiguracji CMake.

## 🔑 Kluczowe Fragmenty Kodu

*   **Struktura `Laptop`:**

    ```
    typedef struct Laptop {
    char nazwa_producenta;
    char model;
    int ram;
    int pojemnosc;
    double cena;
    int vat;
    int id;
    } Laptop;
    ```

    Definicja struktury danych `Laptop`, przechowującej informacje o każdym laptopie.
*   **Funkcja `menu`:**

    ```
    void menu(Plik *LAPTOPY_BAZA) {
    // ... wyświetlanie opcji menu i obsługa wyboru użytkownika ...
    }
    ```

    Funkcja odpowiedzialna za wyświetlanie menu i obsługę interakcji z użytkownikiem.
*   **Funkcje obsługi plików:** `otworzBaze`, `utworzBaze`, `usunBaze`, implementują operacje na plikach bazy danych.

## 📝 Uwagi

*   Program korzysta z konsoli, użyte funkcje `gotoxy` i `wyswietlRekord` z `funkcje.c` bazują na `windows.h` co czyni program niekompatybilnym z innymi systemami operacyjnymi.
*   Format nazwy pliku bazy danych musi być zgodny ze wzorem `bazaXX.dat` (gdzie XX to dwie cyfry).
*   Sortowanie zmienia `id` elementów.

## 🤝 Wkład

Zachęcamy do zgłaszania błędów i proponowania ulepszeń!

## 📜 Licencja

Ten projekt jest udostępniany na licencji MIT. Szczegóły w pliku `LICENSE`.
