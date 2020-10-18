CPPFLAGS=-I.. -g -O0
INCLUDES=../MULLERCALC/StokesVector.h ../MULLERCALC/StokesVector.icc \
         ../MULLERCALC/MullerMatrix.h ../MULLERCALC/MullerMatrix.icc

../local/bin/polarization:polarization.cpp $(INCLUDES)
	mkdir -p ../local/bin
	$(CXX) $< $(CPPFLAGS) $(LDFLAGS) -o $@ 

clean:
	rm -rf *~ ../MULLERCALC/*~ ../local
