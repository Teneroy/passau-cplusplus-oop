all: Student.o Course.o Grade.o main.o
	$(CXX) --std=c++17 -g -o main main.o Student.o Course.o Grade.o

main.o:
	$(CXX) --std=c++17 -g -c main.cpp -o main.o
Student.o:
	$(CXX) --std=c++17 -g -c Student.cpp -o Student.o
Course.o:
	$(CXX) --std=c++17 -g -c Course.cpp -o Course.o
Grade.o:
	$(CXX) --std=c++17 -g -c Grade.cpp -o Grade.o
clean:
	rm *.o main
