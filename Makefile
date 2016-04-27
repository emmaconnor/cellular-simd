all:
	gcc -g -o automata-simd   driver.c -msse -msse2 -msse3 -msse4.1 -D SIMD
	gcc -g -o automata-naive  driver.c

clean:
	rm -f automata-naive automata-simd
