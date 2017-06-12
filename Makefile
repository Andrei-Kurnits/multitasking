EXEC_A	= pra
EXEC_B	= prb
EXEC_C	= prc

all: $(EXEC_A) $(EXEC_B) $(EXEC_C)

$(EXEC_A):
	gcc $(EXEC_A).c -o $(EXEC_A)

$(EXEC_B):
	gcc $(EXEC_B).c -o $(EXEC_B)

$(EXEC_C):
	gcc $(EXEC_C).c -o $(EXEC_C)


clean:
	rm -rf $(EXEC_A) $(EXEC_B) $(EXEC_C)	