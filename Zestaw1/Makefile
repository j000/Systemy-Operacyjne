# Jarosław Rymut

# numer zestawu
zestaw := 1
# nazwa spakowanego pliku
tar := Rymut_Zestaw$(zestaw).tar.gz

# flagi
CFLAGS := -std=c11 -O2 -Wall -Wextra
LDFLAGS := -Wl,--as-needed

ifeq ($(shell $(CC) -dumpversion),4.7)
	# welcome to 2012
	# -Wpedantic is available since gcc 4.8
	CFLAGS += -pedantic
else
	CFLAGS += -Wpedantic
endif

HELPERS := procinfo.o
FILES := $(filter-out $(HELPERS:.o=.c),$(wildcard *.c))

.PHONY: all
all: $(FILES:.c=.x)

# wszystko poza kopiuj.x zależy od procinfo.o
$(filter-out kopiuj.x,$(FILES:.c=.x)): $(HELPERS)

# make może usunąć te pliki
.INTERMEDIATE: $(HELPERS)

.PHONY: clean
clean:
	-$(RM) $(FILES:.c=.x) $(tar)

.PHONY: tar
tar:
# 'file changed as we read it'
	[ -f $(tar) ] || touch $(tar)
	tar -caf ./$(tar) --exclude=$(tar) --exclude=*.x -C .. Zestaw$(zestaw)

# kopia wbudowanej reguły, z nowym rozszerzeniem
%.x: %.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
