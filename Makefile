# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CC = g++
CFLAGS = -o sprawlops.exe

exec: sprawlops-glob.h sprawlops-io.h sprawlops-io.cpp sprawlops.cpp
	$(CC) $(CFLAGS) sprawlops.cpp

clean: 
	rm sprawlops.exe
	rm data/*.csv
	rm data/*.png

