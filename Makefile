CC = gcc
CFLAGS = -Wall -Wextra

$(FILE).c: 
	echo "#include <stdio.h>" > $@
	echo "int main () {" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

run: $(FILE).c
	$(CC) $(CFLAGS) -o $(FILE) $<
	./$(FILE)
