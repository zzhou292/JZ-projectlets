CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

a.out: main.cpp
	g++ $(CFLAGS) -o t01.out *.cpp $(LDFLAGS)

.PHONY: test clean

test: t01.out
	./t01.out

clean:
	rm -f t01.out