include Makefile.inc

DIRS	= graphs seq_utils file_io
EXE	= iggraph

LIBS	= -lemon -lboost_regex
SOURCES = $(wildcard graphs/*.cpp) $(wildcard seq_utils/*.cpp) $(wildcard file_io/*.cpp)
#SOURCES = $(shell for d in $(DIRS); do $(wildcard $d/*.cpp); done)

OBJECTS=$(SOURCES:.cpp=.o)
TESTSRC	= $(wildcard unit_tests/*.cpp)
TESTOBJ	= $(TESTSRC:.cpp=.o)


all : subdirs $(EXE)

subdirs : 
	-for d in $(DIRS); do (cd $$d; $(MAKE) $@ ); done

$(EXE) : RunIgGraph.o $(OBJECTS)
	$(ECHO) $(CC) -o $(EXE) $(OBJECTS) RunIgGraph.o $(LIBS)
	$(CC) -o $(EXE) $(OBJECTS) RunIgGraph.o $(LIBS)

RunIgGraph.o: RunIgGraph.cpp
	$(ECHO) $(CC) $(CFLAGS) $< -o $@
	$(CC) $(CFLAGS)  $< -o $@

#debug : CFLAGS	+= -DDEBUG
debug : CFLAGS = $(DBGFLAGS)
debug :	subdirs_debug $(EXE)

subdirs_debug : 
	-for d in $(DIRS); do (cd $$d; $(MAKE) $@ ); done

test : $(EXE)
	cd unit_tests; $(MAKE) $@
	$(ECHO) $(CC) -o unit_test $(TESTOBJ) $(OBJECTS) -lcpptest $(LIBS)
	$(CC) -o unit_test $(TESTOBJ) $(OBJECTS) -lcpptest $(LIBS)

clean : 
	$(ECHO) cleaning up
	$(RM) RunIgGraph.o
	$(RM) $(OBJECTS)	
	$(RM) $(EXE)
	$(RM) $(TESTOBJ)
