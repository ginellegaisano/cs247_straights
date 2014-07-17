CXX = g++
CXXFLAGS = -Wall -O -g `pkg-config --cflags --libs gtkmm-2.4`
OBJS = helloWorld.o DeckGUI.o
EXEC = helloWorld

helloWorld: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC) 

helloWorld.o: helloWorld.cpp

# 	CPP = g++
# FLAGS = -Wall -g -MMD
# TARGETS = Card.o Command.o Table.o Player.o Computer.o Human.o Status.o Global.o Game.o
# EXE = straights

# all: $(TARGETS)
# 	$(CPP) $(FLAGS) Main.cpp $(TARGETS) -o $(EXE)

tags:
		ctags -R -a --c++-kinds=+p --fields=+iaS --extra=+q

clean:
		rm -rf *.d *.o *.dSYM $(EXE)