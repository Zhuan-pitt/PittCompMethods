list= add.o parse.o print.o

libPlus.a: $(list)
	ar rc $@ $?
clean:
	rm -f *.a *.o plus
plus:main.o libPlus.a
	g++ -o $@ $< -L. -lPlus