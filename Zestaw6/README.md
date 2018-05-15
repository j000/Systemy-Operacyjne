Jarosław Rymut

# Zestaw6 (Kolejki komunikatów)

## Biblioteka libmsg.so (libmsg.a)

Własna biblioteka do obsługi kolejki komunikatów. Obsługuje funkcje:

* `int msgCreate(int id)` Tworzy kolejkę komunikatów.
* `void msgRm(int msgid)` Usuwa kolejkę komunikatów o identyfikatorze msgid.
* `void msgSend(int msgid, komunikat *msg)` Wysyła komunikat wskazywany przez msg do kolejki o identyfikatorze msgid.
* `void msgRecv(int msgid, komunikat *msg, int mtype)` Odbiera z kolejki msgid komunikat typu mtype i zapisuje do msg.
* `void msgInfo(int msgid)` Wypisuje informacje o kolejce komunikatów.


Komunikat:

    typedef struct {
    	long type;
    	pid_t pid;
    	char msg[20];
    } komunikat;

## Serwer i klient (serwer.c, klient.c)

Proces klient wczytuje ciąg znaków i wysyła go do serwera.

Proces serwera zamienia małe litery na duże, a duże na małe i odsyła tak zmienioną wiadomość do klienta.

## Makefile

Do zestawu dołączony jest plik `Makefile`, który korzysta w jak największym stopniu z reguł wbudowanych.
