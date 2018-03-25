Jarosław Rymut

# Zestaw1 (Procesy)

## Zadanie 1: kopiuj.c

Program kopiuje zawartość jednego pliku do drugiego. Jako argumenty program przyjmuje nazwy plików: źródłowego i docelowego.

Użycie: `./kopiuj.x źródłowy docelowy`

## Zadanie 2: Makefile

Makefile korzysta w jak największym stopniu z reguł wbudowanych. Poza kompilacją pojedynczych programów z zestawu Makefile obsługuje dodatkowe polecenia:

- `all` (domyślne): kompiluje wszystkie programy
- `clean`: usuwa skompilowane programy
- `tar`: pakuje cały katalog

Kompilacja używa standardu c99 i odbywa się z włączoną optymalizacją.

## Zadanie 3: procinfo.c, procinfo.h

Funkcja `int procinfo(const char*)` wypisuje identyfikatory PID, PPID, PGID, UID i GID. Plik nagłówkowy zawiera tylko deklarację, plik źródłowy implementację.

## Zadanie 4: procesy.c

Przykładowy wynik działania programu procesy.x:

    ./procesy.x: pid: 23591 | ppid:13940 | pgid:23591 | uid:  1000 | gid:  1000
    ./procesy.x: pid: 23592 | ppid:23591 | pgid:23591 | uid:  1000 | gid:  1000
    ./procesy.x: pid: 23594 | ppid:23592 | pgid:23591 | uid:  1000 | gid:  1000
    ./procesy.x: pid: 23609 | ppid:23591 | pgid:23591 | uid:  1000 | gid:  1000
    ./procesy.x: pid: 23610 | ppid:23594 | pgid:23591 | uid:  1000 | gid:  1000
    ./procesy.x: pid: 23616 | ppid:23609 | pgid:23591 | uid:  1000 | gid:  1000
    ./procesy.x: pid: 23617 | ppid:23592 | pgid:23591 | uid:  1000 | gid:  1000
    ./procesy.x: pid: 23626 | ppid:23591 | pgid:23591 | uid:  1000 | gid:  1000

"Drzewo genealogiczne" procesów:

    o
    |
    >                                ./procesy.x: pid: 23591 | ppid:13940 | ...
    +---------------.
    |               >                ./procesy.x: pid: 23592 | ppid:23591 | ...
    +-------.       +-------.
    |       |       |       >        ./procesy.x: pid: 23594 | ppid:23592 | ...
    |       >       |       |        ./procesy.x: pid: 23609 | ppid:23591 | ...
    +---.   +---.   +---.   +---.
    |   |   |   |   |   |   |   >    ./procesy.x: pid: 23610 | ppid:23594 | ...
    |   |   |   >   |   |   |   |    ./procesy.x: pid: 23616 | ppid:23609 | ...
    |   |   |   |   |   >   |   |    ./procesy.x: pid: 23617 | ppid:23592 | ...
    |   >   |   |   |   |   |   |    ./procesy.x: pid: 23626 | ppid:23591 | ...
    o   o   o   o   o   o   o   o

### Pytanie:

__Ile powstaje procesów i dlaczego?__

Poza głównym procesem powstaje 7 procesów potomnych. Każde wywołanie funkcji `fork()` podwaja liczbę procesów, skoro wywołujemy ją 3 razy otrzymamy 2^3 = 8 procesów.

## Zadanie 5: drzewko1.c, drzewko2.c

Programy generujące poniższe drzewa genealogiczne:

    drzewko1:        drzewko2:
    o                o
    |                +--.
    +--o             |  +--.
    |                |  |  +--.
    +--o             |  |  |  |
    |                |  |  |  o
    +--o             |  |  o
    |                |  o
    o                o

## Zadanie 6: macierzysty.c, potomny.c

Komunikaty procesów potomnych są wypisywane przez program `potomny.x` uruchamiany funkcją execv.

### Pytanie:

__Ile teraz powstaje procesów i dlaczego?__

Poza procesem głównym powstaną 3 procesy. W przeciwieństwie do programu z zadania 4. procesy potomne wykonują inny program, nie wywołują więc funkcji `fork()`.
