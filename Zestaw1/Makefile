# Jarosław Rymut

# numer zestawu
zestaw := $(notdir $(lastword $(CURDIR)))
# nazwa spakowanego pliku
tar := Rymut_$(zestaw).tar.gz

# flagi
CFLAGS := -std=c11 -O2 -Wall -Wextra

ifeq ($(shell $(CC) -dumpversion),4.7)
	# welcome to 2012
	# -Wpedantic is available since gcc 4.8
	CFLAGS += -pedantic
else
	CFLAGS += -Wpedantic
endif

HELPERS := procinfo.c
FILES := $(filter-out $(HELPERS),$(wildcard *.c))

.PHONY: all
all: $(FILES:.c=.x)

# wszystko poza kopiuj.x zależy od procinfo.o
$(filter-out kopiuj.x,$(FILES:.c=.x)): $(HELPERS:.c=.o)

# make może automatycznie usunąć te pliki
.INTERMEDIATE: $(HELPERS:.c=.o)

.PHONY: clean
clean:
	-$(RM) $(FILES:.c=.x) $(tar)

.PHONY: tar
tar:
# poprawka na błąd 'file changed as we read it'
	[ -f $(tar) ] || touch $(tar)
	tar -caf ./$(tar) --exclude=$(tar) --exclude=*.x --exclude=.* -C .. $(zestaw)

# kopia wbudowanej reguły, z nowym rozszerzeniem
%.x: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
