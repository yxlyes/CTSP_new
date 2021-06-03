tar = ils_ctsp.exe
obj = main.o read.o 
deps = basic.h read.h
cc = g++
RMRF = del
# RMRF :=rm -rf


$(tar): $(obj)     
	$(cc) $^ -o $@

%.o: %.c $(deps)    # head files
	$(cc) -c %.c -o %.o   # transfer a file

.PHONY:
clearall:
	$(RMRF) $(obj) $(tar)
clear:
	$(RMRF) $(obj) 