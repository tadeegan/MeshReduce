comp =clang++

CXX_OPTS =-c -g -O0  $(WARNINGS)
WARNINGS =-Wfatal-errors -Werror -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
OBJS =run.o vector.o vertex.o triangle.o list.o progmesh.o

EXEC =testing

$(EXEC): $(OBJS)
	$(comp) $(OBJS) -o $(EXEC)  

run.o: run.cpp vector.h vertex.h triangle.h
	$(comp) $(CXX_OPTS) run.cpp 

progmesh.o: progmesh.cpp list.cpp list.h vector.h vertex.h
	$(comp) $(CXX_OPTS) progmesh.cpp 

vertex.o: vertex.cpp vector.h list.cpp list.h
	$(comp) $(CXX_OPTS) vertex.cpp 

triangle.o: triangle.cpp vector.cpp list.cpp list.h
	$(comp) $(CXX_OPTS) triangle.cpp 

list.o: list.cpp list.h
	$(comp) $(CXX_OPTS) list.cpp 

vector.o: vector.cpp vector.h
	$(comp) $(CXX_OPTS) vector.cpp 

clean:
	-rm -rf $(EXEC) *.o
