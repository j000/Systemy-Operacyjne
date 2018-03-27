Jarosław Rymut

# Zestaw2 (Sygnały)

## Zadanie 1: obsluga.c

Program do obsługi sygnałów. Program przyjmuje argumenty z linii komend:

- jedną z liter:
    - `d` - domyślna obsługa sygnału
    - `i` - ignorowanie sygnału
    - `p` - przechwycenie i wypisanie sygnału
- numer sygnału

Użycie: `./obsluga.x [dip] numer_sygnału`

## Zadanie 2: wysylaj.c

Program w procesie potomnym wywołuje `./obsluga.x` poprzez funkcję `execl()` i po sekundzie wysyła do niego sygnały poprzez `kill()`.

Użycie: `./wysylaj.x [dip] numer_sygnału`

## Zadanie 3: grupa.c

Program w kilku procesach potomnych wywołuje `./obsluga.x` i poprzez `kill()` wysyła sygnały do całej grupy procesów.

## Zadanie 4: Pytania

#### Krótko opisać funkcję i znaczenie czterech wybranych sygnałów, w tym dwóch nieprzechwytywalnych

- `SIGKILL` (9) - nieprzechwytywalny, proces musi się zakończyć
- `SIGSTOP` (19) - nieprzechwytywalny, proces zawiesza wykonywanie
- `SIGCONT` (18) - kontynuacja wykonywania procesu
- `SIGTERM` (15) - sygnał zakończenia pracy procesu

#### Które sygnały możemy wysłać w terminalu przy użyciu skrótów klawiszowych?

- `SIGINT` (2) - Ctrl+C
- `SIGQUIT` (3) - Ctrl+/
- `SIGSTOP` (19) - Ctrl+Z, działa w większości powłok na typowych desktopach
