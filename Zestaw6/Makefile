# Jarosław Rymut

# numer zestawu
zestaw := $(notdir $(lastword $(CURDIR)))
# nazwa spakowanego pliku
tar := Rymut_$(zestaw).tar.gz

# flagi
CFLAGS := -std=c99 -O2 -Wall -Wextra

ARFLAGS += -c -s

ifeq ($(shell $(CC) -dumpversion),4.7)
	# welcome to 2012
	# -Wpedantic is available since gcc 4.8
	CFLAGS += -pedantic
else
	CFLAGS += -Wpedantic
endif

# CFLAGS += -fPIC -fPIE
# LDFLAGS += -fPIC -fPIE -pie
# PIC > PIE > no-pie
CFLAGS += -fPIC
LDFLAGS += -fPIC -pie

HELPERS := msg.c
FILES := $(filter-out $(HELPERS),$(wildcard *.c))

.PHONY: all
all: $(FILES:.c=.x)

# ifneq (3.82,$(firstword $(sort $(MAKE_VERSION) 3.82)))
# 	$(error "*** PLEASE USE AT LEAST VERSION 3.82 FROM 2010 ***")
# endif

.PHONY: clean
clean:
	-$(RM) $(FILES:.c=.x) $(tar) lib*

.PHONY: tar
tar:
# poprawka na błąd 'file changed as we read it'
	[ -f $(tar) ] || touch $(tar)
	tar -caf ./$(tar) --exclude=$(tar) --exclude=*.x --exclude=.* --exclude=lib* -C .. $(zestaw)

# kopia wbudowanej reguły, z nowym rozszerzeniem
# %.x: CFLAGS += -fPIE
# %.x: private LDFLAGS += -fPIE -pie
%.x: private LDFLAGS += -fPIC -pie
%.x: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)

# lib%.so: CFLAGS += -fPIC
# lib%.so: private LDFLAGS += -fPIC -pie
lib%.so: private LDFLAGS += -shared
lib%.so: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) $(OUTPUT_OPTION)

####################

# zmodyfikuj ścieżkę szukania dla wszystkich plików
$(FILES:.c=.x): private LDLIBS += -Wl,-R.
# wszystko potrzebuje biblioteki
$(FILES:.c=.x): private LDLIBS += -L. -lmsg

all: libmsg.so libmsg.a(msg.o)

# wszystko zależy od msg.h i od Makefile
$(FILES:.c=.o): msg.h Makefile | libmsg.so libmsg.a(msg.o)
$(HELPERS:.c=.o): msg.h Makefile

####################

# to korzysta z semaforów
# glowny.x producent.x konsument.x: private LDLIBS += -L. -lsem
# glowny.o producent.o konsument.o: sem.h common.h | libsem.so

####################
# make może usunąć pliki "tymczasowe"
.INTERMEDIATE: $(HELPERS:.c=.o) $(FILES:.c=.o)
