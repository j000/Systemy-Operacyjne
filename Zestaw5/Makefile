# Jarosław Rymut

# numer zestawu
zestaw := $(notdir $(lastword $(CURDIR)))
# nazwa spakowanego pliku
tar := Rymut_$(zestaw).tar.gz

# flagi
CFLAGS := -std=c99 -O2 -Wall -Wextra -fPIC -fPIE

ARFLAGS += -c -s

ifeq ($(shell $(CC) -dumpversion),4.7)
	# welcome to 2012
	# -Wpedantic is available since gcc 4.8
	CFLAGS += -pedantic
else
	CFLAGS += -Wpedantic
endif

HELPERS := shmem.c sem.c
FILES := $(filter-out $(HELPERS),$(wildcard *.c))

.PHONY: all
all: $(FILES:.c=.x)

.PHONY: clean
clean:
	-$(RM) $(FILES:.c=.x) $(tar) libshmem.so libsem.so shmuse2.x schowek.txt

.PHONY: tar
tar:
# poprawka na błąd 'file changed as we read it'
	[ -f $(tar) ] || touch $(tar)
	tar -caf ./$(tar) --exclude=$(tar) --exclude=*.x --exclude=.* --exclude=*.so -C .. $(zestaw)

# kopia wbudowanej reguły, z nowym rozszerzeniem
%.x: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)

lib%.so: private LDFLAGS += -shared
lib%.so: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)

####################

# zmodyfikuj ścieżkę szukania dla wszystkich plików
$(FILES:.c=.x): private LDLIBS += -Wl,-R.
# wszystko potrzebuje biblioteki
$(FILES:.c=.x) shmuse2.x: private LDLIBS += -L. -lshmem

all: shmuse2.x
shmuse2.x: shmuse.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)

# wszystko zależy od shmem.h
$(FILES:.c=.o): shmem.h | libshmem.so
shmem.o: shmem.h

####################

# to korzysta z semaforów
glowny.x producent.x konsument.x: private LDLIBS += -L. -lsem
glowny.o producent.o konsument.o: sem.h common.h | libsem.so

####################
# make może usunąć pliki "tymczasowe"
.INTERMEDIATE: $(HELPERS:.c=.o) $(FILES:.c=.o)
