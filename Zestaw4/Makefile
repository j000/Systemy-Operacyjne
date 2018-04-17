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

HELPERS := sem.c
FILES := $(filter-out $(HELPERS),$(wildcard *.c))

.PHONY: all
all: $(FILES:.c=.x)

.PHONY: clean
clean:
	-$(RM) $(FILES:.c=.x) $(tar) libsem.a

.PHONY: tar
tar:
# poprawka na błąd 'file changed as we read it'
	[ -f $(tar) ] || touch $(tar)
	tar -caf ./$(tar) --exclude=$(tar) --exclude=*.x --exclude=.* -C .. $(zestaw)

# kopia wbudowanej reguły, z nowym rozszerzeniem
%.x: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

####################

LDLIBS += -L. -lsem
ARFLAGS += -c -s

# wszystko zależy od sem.h i libsem.a
$(FILES:.c=.o): sem.h libsem.a(sem.o)
.INTERMEDIATE: $(FILES:.c=.o)
