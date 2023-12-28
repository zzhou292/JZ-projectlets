CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

a.out: main.cpp
	g++ $(CFLAGS) -o t02.out *.cpp $(LDFLAGS)

.PHONY: test clean

test: t02.out
	./t02.out

clean:
	rm -f t02.out