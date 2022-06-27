dict:
	mkdir -p bin
	g++ -std=c++17 -o bin/freq src/main.cpp src/Utility/*.cpp src/Solution/*.cpp

clean: rm bin/*