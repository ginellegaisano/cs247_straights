CPP = g++
FLAGS = -Wall -O -g `pkg-config --cflags --libs gtkmm-2.4 glibmm-2.4` -MMD
TARGETS = View.o DeckGUI.o Card.o Command.o Table.o Player.o Computer.o Human.o Status.o Model.o
EXEC = straights

all: $(TARGETS)
	$(CPP) $(FLAGS) Main.cpp $(TARGETS) -o $(EXEC)

tags:
		ctags -R -a --c++-kinds=+p --fields=+iaS --extra=+q

clean:
		rm -rf *.d *.o *.dSYM $(EXE)