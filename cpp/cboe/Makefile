CXX := g++
CXXFLAGS := -std=c++17  -O3
srcfiles := solution.cc
executable := collect_top10

pitcher: $(srcfiles)
	$(CXX) $(CXXFLAGS) $(srcfiles) -o $(executable) 

clean:
	rm -f  $(executable)
