
a.out : client.o dispatcher.o f_control.o view1.o view2.o
	g++ client.o dispatcher.o f_control.o view1.o view2.o

client.o : f_control.hpp client.cpp
	g++ -c client.cpp

dispatcher.o : dispatcher.hpp dispatcher.cpp
	g++ -c dispatcher.cpp

f_control.o : f_control.hpp f_control.cpp
	g++ -c f_control.cpp

view1.o : view1.hpp view1.cpp
	g++ -c view1.cpp

view2.o : view2.hpp view2.cpp
	g++ -c view2.cpp

clean:
	rm *.o a.out
