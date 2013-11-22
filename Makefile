comp =clang++

CXX_OPTS =-c -g $(WARNINGS)
WARNINGS =-Wfatal-errors -Werror -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
OBJS =run.o vector.o vertex.o triangle.o progmesh.o

EXEC =testing

$(EXEC): $(OBJS)
	$(comp) $(OBJS) -o $(EXEC)  

run.o: run.cpp vector.o vertex.o triangle.o
	$(comp) $(CXX_OPTS) run.cpp 

progmesh.o: progmesh.cpp progmesh.h list.cpp list.h vector.o vertex.o
	$(comp) $(CXX_OPTS) progmesh.cpp 

vertex.o: vertex.cpp vertex.h vector.o list.cpp list.h
	$(comp) $(CXX_OPTS) vertex.cpp 

triangle.o: triangle.cpp triangle.h vector.o list.cpp list.h
	$(comp) $(CXX_OPTS) triangle.cpp 

vector.o: vector.cpp vector.h
	$(comp) $(CXX_OPTS) vector.cpp 

clean:
	-rm -rf $(EXEC) *.o
