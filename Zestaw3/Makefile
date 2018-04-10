# Jarosław Rymut

# numer zestawu
zestaw := $(notdir $(lastword $(CURDIR)))
# nazwa spakowanego pliku
tar := Rymut_$(zestaw).tar.gz

# flagi
CFLAGS := -std=c99 -O2 -Wall -Wextra

ifeq ($(shell $(CC) -dumpversion),4.7)
	# welcome to 2012
	# -Wpedantic is available since gcc 4.8
	CFLAGS += -pedantic
else
	CFLAGS += -Wpedantic
endif

HELPERS :=
FILES := $(filter-out $(HELPERS),$(wildcard *.c))

.PHONY: all
all: $(FILES:.c=.x)

# wszystko zależy od pomocników
$(FILES:.c=.x): $(HELPERS:.c=.o)

# make może automatycznie usunąć te pliki
.INTERMEDIATE: $(HELPERS:.c=.o)

.PHONY: clean
clean: removepipe
	-$(RM) $(FILES:.c=.x) $(tar) schowek.txt

.PHONY: tar
tar:
# poprawka na błąd 'file changed as we read it'
	[ -f $(tar) ] || touch $(tar)
	tar -caf ./$(tar) --exclude=$(tar) --exclude=*.x --exclude=.* -C .. $(zestaw)

# kopia wbudowanej reguły, z nowym rozszerzeniem
%.x: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@


####################

# wszystko zależy od prodkons.h
$(FILES:.c=.o): prodkons.h
.INTERMEDIATE: $(FILES:.c=.o)

.PHONY: porownaj
porownaj:
	diff -sq magazyn.txt schowek.txt

pipe:
	mkfifo pipe

.PHONY: removepipe
removepipe:
	-rm -f pipe

.PHONY: zad2
zad2: pipe run_zad2 removepipe porownaj

.PHONY: run_zad2
run_zad2: producent.x konsument.x
	./producent.x pipe & ./konsument.x pipe

