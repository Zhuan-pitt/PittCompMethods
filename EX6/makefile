list= add.o parse.o print.o

plus:main.o libPlus.a
	g++ -o $@ $< -L. -lPlus
libPlus.a: $(list)
	ar rc $@ $?
clean:
	rm -f *.a *.o plus
