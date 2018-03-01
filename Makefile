pierwszy: pierwszy.c

.PHONY: run
run: pierwszy
	./$<

.PHONY: test
test: run
	@diff -s -q kopia_pierwszy.c pierwszy.c
