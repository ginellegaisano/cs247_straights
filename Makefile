CPP = g++
FLAGS = -Wall -g -MMD
CXXFLAGS += -g
TARGETS = Card.o Command.o Table.o Player.o Computer.o Human.o Status.o Global.o
EXE = straights

all: $(TARGETS)
	$(CPP) $(FLAGS) Main.cpp $(TARGETS) -o $(EXE)

tags:
		ctags -R -a --c++-kinds=+p --fields=+iaS --extra=+q

clean:
		rm -rf *.d *.o *.dSYM $(EXE)
