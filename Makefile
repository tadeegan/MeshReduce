comp = clang++
CXXFLAGS = -stdlib=libc++ -ldl -Wall -Werror -g -O0

CXX_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow

EXEC = testing

$(EXEC): run.cpp vector.o vertex.o triangle.o list.o progmesh.o
	$(comp) -o $@ $^

progmesh.o: progmesh.cpp list.o vector.o vertex.o
	$(comp) $(CXX_OPTS) $<

vertex.o: vertex.cpp vertex.h vector.o
	$(comp) $(CXX_OPTS) $<

triangle.o: triangle.cpp triangle.h
	$(comp) $(CXX_OPTS) $<

list.o: list.cpp list.h
	$(comp) $(CXX_OPTS) $<

vector.o: vector.cpp vector.h
	$(comp) $(CXX_OPTS) $<

clean:
	-rm -rf $(EXEC) *.o