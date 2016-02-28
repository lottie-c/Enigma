enigma: main.o plugboard.o reflector.o rotor.o helper.o
	g++ -Wall -g main.o plugboard.o reflector.o rotor.o helper.o -o enigma

main.o: main.cpp errors.h plugboard.h reflector.h rotor.h helper.h
	g++ -Wall -c main.cpp

plugboard.o: plugboard.cpp plugboard.h helper.h
	g++ -Wall -c plugboard.cpp

reflector.o: reflector.cpp reflector.h helper.h
	g++ -Wall -c reflector.cpp

rotor.o: rotor.cpp rotor.h helper.h
	g++ -Wall -c rotor.cpp

helper.o: helper.cpp helper.h
	g++ -Wall -c helper.cpp




.PHONY: clean
clean:
	rm -f enigma *.o


