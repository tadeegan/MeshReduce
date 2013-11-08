CXX = clang++
CXXFLAGS = -stdlib=libc++ -lcxxrt -ldl -Wall -Werror -g -O0 -pthread

EXE = testing

.PHONY: clean

$(EXE): main.cpp $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $(EXE) main.cpp

clean:
	-rm -rf $(EXE) *.o
