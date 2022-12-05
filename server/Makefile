CC = gcc
CFLAGS = -o
file=
SRC1 = pserver.c
SRC2 = pclient.c
exe1 = pserver
exe2 = pcli

$(exe1): $(SRC1)
	$(CC) $(SRC1) $(CFLAGS) $(exe1)

$(exe2): $(SRC2)
	$(CC) $(SRC2) $(CFLAGS) $(exe2)

run-server: $(exe1) 
			$(CC) $(SRC1) $(CFLAGS) $(exe1)
	 -- ./$(exe1) 
run-cli: $(exe2) $(file)
	 -- ./$(exe2) $(file)

clean:
	rm *.o
