CC=g++
CFLAGS=-std=gnu++0x -c -g -Wall -O2
LDFLAGS=
SOURCES=Monomer.cpp Polymer.cpp \
Rand.cpp Functions.cpp Stat.cpp Histo.cpp\
Thermostat.cpp Andersen.cpp Lowe_Andersen.cpp Berendsen.cpp Bussi.cpp \
Gaussian.cpp Nose_Hoover.cpp Nose_Hoover_Chain.cpp Thermostat_None.cpp    
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(SOURCES:.cpp=.h)
EXECUTABLE=sim_histo sim_position sim_thermostat

all: $(SOURCES) $(HEADERS) simulation_histo.o simulation_position.o test_Thermostat.o
	make sim_histo
	make sim_position
	make sim_thermostat
	
sim_histo: simulation_histo.o $(OBJECTS)
	$(CC) $(LDFLAGS) simulation_histo.o $(OBJECTS) -o $@

sim_position: simulation_position.o $(OBJECTS)
	$(CC) $(LDFLAGS) simulation_position.o $(OBJECTS) -o $@

sim_thermostat: test_Thermostat.o $(OBJECTS)
	$(CC) $(LDFLAGS) test_Thermostat.o $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -f simulation_histo.o simulation_position.o test_Thermostat.o $(OBJECTS) $(EXECUTABLE)
