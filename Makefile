CC          = g++
CFLAGS      = -std=c++11 -Wall -pedantic -O3
SRCLOC      = src
BINLOC      = bin
OBJLOC      = obj

OBJS        = $(addprefix $(OBJLOC)/,player.o board.o heuristic.o)
PLAYERNAME  = link_dismissal

all: $(PLAYERNAME) testgame

tests: testminimax testheuristic

$(PLAYERNAME): $(OBJS) $(OBJLOC)/wrapper.o
	$(CC) -o $(BINLOC)/$@ $^

testgame:  $(OBJLOC)/testgame.o
	$(CC) -o $(BINLOC)/$@ $^

testminimax: $(OBJS) $(OBJLOC)/testminimax.o
	$(CC) -o $(BINLOC)/$@ $^

testheuristic: $(OBJS) $(OBJLOC)/testheuristic.o
	$(CC) -o $(BINLOC)/$@ $^

$(OBJLOC)/%.o: $(SRCLOC)/%.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

java:
	make -C java/

cleanjava:
	make -C java/ clean

clean:
	rm -f bin/* obj/*

.PHONY: java testminimax
