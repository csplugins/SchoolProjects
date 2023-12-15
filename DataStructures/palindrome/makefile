CC = g++
FLAGS = -std=c++11

all: palindrome.out clean
Palindrome.o: Palindrome.cpp
	      ${CC} ${FLAGS} -c Palindrome.cpp

palindrome.out: Palindrome.o test_palindrome.cpp
		${CC} ${FLAGS} test_palindrome.cpp *.o -o palindrome.out
		
clean:  
	rm -f *.o
	rm -f *~
	rm -f \#*

