CC = gcc
CFLAGS = -Wall -Wextra

$(FILE).c: | bin 
	echo "#include <stdio.h>" > $@
	echo "int main () {" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

bin: 
	mkdir -p $@

run: $(FILE).c
	$(CC) -o ./bin/$(FILE) $<
	./bin/$(FILE)

run-s: $(FILE).c
	$(CC) $(CFLAGS) -o ./bin/$(FILE) $<
	./bin/$(FILE)
