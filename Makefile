CC=gcc
CFILE=calculator.c
BINARY=calc
DIR=~/.calculator/
TERMINAL=~/.bashrc

output: $(CFILE)
	mkdir -p $(DIR)
	$(CC) $(CFILE) -o $(BINARY)
	mv $(BINARY) $(DIR)
	grep -l calc=\"$(DIR)$(BINARY)\" $(TERMINAL) || echo "alias calc=\"$(DIR)$(BINARY)\"" >> $(TERMINAL)

clean:
	rm -rf $(CFILE) $(BINARY) Makefile
