CC = gcc
CFLAGS = -o
file=
port=0.0.0.0 
SRC1 = server.c
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
run-cli: 
			$(CC) $(SRC2) $(CFLAGS) $(exe2)
	 -- ./$(exe2) $(file) $(port)

clean:
	rm *.o
