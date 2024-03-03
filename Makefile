CFILE=calculator.c
BINARY=calc
DIR=~/.calculator/

output:
	mkdir -p $(DIR)
	gcc $(CFILE) -o $(BINARY)
	cp $(CFILE) Makefile $(DIR)
	mv $(BINARY) $(DIR)
	grep -l calc=\"$(DIR)$(BINARY)\" ~/.bashrc || echo "alias calc=\"$(DIR)$(BINARY)\"" >> ~/.bashrc

clean:
	rm -rf $(CFILE) $(BINARY) Makefile
