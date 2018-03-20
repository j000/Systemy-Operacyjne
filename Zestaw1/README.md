Jarosław Rymut

# Zestaw1 (Procesy)

## Zadanie 4

Przykładowy wynik programu procesy.x:
	./procesy.x: pid: 23591 | ppid:13940 | pgid:23591 | uid:  1000 | gid:  1000
	./procesy.x: pid: 23592 | ppid:23591 | pgid:23591 | uid:  1000 | gid:  1000
	./procesy.x: pid: 23594 | ppid:23592 | pgid:23591 | uid:  1000 | gid:  1000
	./procesy.x: pid: 23609 | ppid:23591 | pgid:23591 | uid:  1000 | gid:  1000
	./procesy.x: pid: 23610 | ppid:23594 | pgid:23591 | uid:  1000 | gid:  1000
	./procesy.x: pid: 23616 | ppid:23609 | pgid:23591 | uid:  1000 | gid:  1000
	./procesy.x: pid: 23617 | ppid:23592 | pgid:23591 | uid:  1000 | gid:  1000
	./procesy.x: pid: 23626 | ppid:23591 | pgid:23591 | uid:  1000 | gid:  1000

"Drzewo genealogiczne" procesów:
	./procesy.x: pid: 23591 | ppid:13940
	|
	+---./procesy.x: pid: 23592 | ppid:23591
	|   |
	|	+---./procesy.x: pid: 23594 | ppid:23592
	|   |   |
	|	|   +---./procesy.x: pid: 23610 | ppid:23594
	|   |
	|	+---./procesy.x: pid: 23617 | ppid:23592
	|
	+---./procesy.x: pid: 23609 | ppid:23591
	|   |
	|	+---./procesy.x: pid: 23616 | ppid:23609
	|
	+---./procesy.x: pid: 23626 | ppid:23591

# Makefile

Makefile obłsuguje dodatkowe polecenia:

- `all` (domyślne): kompiluje wszystkie programy
- `clean`: usuwa skompilowane programy
- `tar`: pakuje cały katalog
