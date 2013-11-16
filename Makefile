comp = g++
CXXFLAGS = -stdlib=libc++ -ldl -Wall -Werror -g -O0

CXX_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow

EXEC = testing

.PHONY: clean

$(EXEC): run.cpp vec3.o vertex.o triangle.o
	$(comp) -o $@ $^

vertex.o: vertex.cpp vertex.h vec3.o
	$(comp) $(CXX_OPTS) $<

vec3.o: vec3.cpp vec3.h
	$(comp) $(CXX_OPTS) $<

triangle.o: triangle.cpp triangle.h
	$(comp) $(CXX_OPTS) $<

clean:
	-rm -rf $(EXEC) *.o