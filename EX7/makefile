list= add.o parse.o print.o
libPlus.so: $(list)
	g++ -shared $? -o $@
clean:
	rm -f *.so *.o plus
plus:main.o libPlus.so
	g++ -o $@ $< -L. -lPlus