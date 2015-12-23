ifeq ($(VERBOSE), true)
	VERBOSEFLAG = -DVERBOSE
else
	VERBOSEFLAG = 
endif

main: main.cpp
	g++ main.cpp -o main -O2 $(VERBOSEFLAG)

debug: main.cpp
	g++ main.cpp -o main -ggdb -Wall $(VERBOSEFLAG)

test: main.cpp
	g++ main.cpp -o test -O2 -DTEST $(VERBOSEFLAG)
