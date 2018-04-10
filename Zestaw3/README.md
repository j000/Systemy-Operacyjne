Jarosław Rymut

# Zestaw3 (Potoki)

## Część wspólna: prodkons.h

Implementacja problemu *producenta i konsumenta*. Producent (funkcja `void producent(int fd)`) czyta dane z pliku `magazyn.txt` i zapisuje je do deskryptora podanego jako argument funkcji (`fd`). Konsument (funkcja `void konsument (int fd)`) czyta dane z deskryptora podanego jako argument i zapisuje je do pliku `schowek.txt`.

W trakcie kopiowania danych procesy są usypiane na losową ilość czasu - symulacja różnego czasu działania programów.

## Zadanie 1: prodkons.c

Implementacja problemu *producenta i konsumenta* przy pomocy dwóch wątków i potoku. Program tworzy nowy potok przy pomocy funkcji `pipe()`, a następnie tworzy nowy wątek (`fork()`). Każdy z wątków zamyka odpowiednie końce potoku i następuje przesył danych. *Producent* po wyczerpaniu danych zamyka potok, dzięki temu *konsument* odczytuje `EOF` i następuje zakończenie programu.

## Zadanie 2: producent.c, konsument.c, fifo.c

Implementacja problemu *producenta i konsumenta* przy pomocy oddzielnych programów i potoków nazwanych.

`producent.x` przyjmuje jeden argument - nazwę istniejącego pliku, do którego należy zapisać dane.

`konsument.x` przyjmuje jeden argument - nazwę istniejącego pliku, z którego należy odczytywać dane. W przypadku braku argumentu program odczytuje dane ze standardowego wejścia.

`fifo.x` tworzy potok nazwany (o nazwie `pipe` w bieżącym katalogu), a następnie w dwóch wątkach uruchamia `producent.x` i `konsument.x` z odpowiednimi parametrami. Po zakończeniu działania programów potok zostaje usunięty.

Potoki nazwane działają także z linii komend:

    mkfifo test
    ./producent.x test &
    ./konsument.x test
    rm test
    diff -sq magazyn.txt schowek.txt

## Makefile

Do zestawu dołączony jest plik `Makefile`, który korzysta w jak największym stopniu z reguł wbudowanych. Poza kompilacją pojedynczych programów z zestawu Makefile obsługuje dodatkowe polecenia:

- `all` (domyślne): kompiluje wszystkie programy
- `clean`: usuwa skompilowane programy i `schowek.txt`
- `tar`: pakuje cały katalog
- `porownaj`: porównuje pliki `magazyn.txt` i `schowek.txt`
- `zad2`: tworzy potok nazwany, uruchamia *producenta* i *konsumenta*, kasuje potok i sprawdza poprawność przepisanych danych

Kompilacja używa standardu c99 i odbywa się z włączoną optymalizacją.


