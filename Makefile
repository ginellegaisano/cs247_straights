CXX = g++
CXXFLAGS = -Wall -O -g `pkg-config --cflags --libs gtkmm-2.4`
OBJS = View.o DeckGUI.o Card.o Command.o Table.o Player.o Status.o Model.o Observer.o Subject.o Controller.o
EXEC = straights

helloWorld: $(OBJS)
	$(CXX) $(OBJS) Main.cpp $(CXXFLAGS) -o $(EXEC) 

View.o: View.cpp
DeckGUI.o: DeckGUI.cc
Card.o: Card.cpp
Command.o: Command.cpp
Table.o: Table.cpp
Player.o: Player.cpp
Status.o: Status.cpp
Model.o: Model.cpp
Observer.o: Observer.cpp
Subject.o: Subject.cpp
Controller.o: Controller.cpp


tags:
		ctags -R -a --c++-kinds=+p --fields=+iaS --extra=+q

clean:
		rm -rf *.d *.o *.dSYM $(EXE)