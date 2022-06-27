dict:
	mkdir -p bin
	g++ -std=c++17 -O3 -march=native -flto -o bin/freq src/main.cpp src/Utility/*.cpp src/Solution/*.cpp

clean: rm bin/*