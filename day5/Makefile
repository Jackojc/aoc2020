all:
	@mkdir -p build
	$(CXX) main.cpp $(CXXFLAGS) -funroll-all-loops -std=c++17 -I.. -I../tinge -I../nanobench/src/include -ltbb -O3 -march=native -Wall -o build/out
