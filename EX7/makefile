list= add.o parse.o print.o
CXXFLAGS="-fPIC"

plus:main.o libPlus.so
	g++ -o $@ $< -L. -lPlus
libPlus.so: $(list)
	g++ -shared $? -o $@
clean:
	rm -f *.so *.o plus

