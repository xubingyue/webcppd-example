PRO=../../build/$(shell basename `realpath .`).so


APPSRC=$(wildcard $(shell find . -type f | grep -E '*.cpp$$'))
APPOBJ=$(patsubst %.cpp,%.o,$(APPSRC))


CXXFLAGS+=-O3 -std=c++11 -fPIC `pkg-config --cflags opencv`
LIBS+=-lPocoJSON -lPocoNet -lPocoCrypto -lPocoUtil -lPocoFoundation
LIBS+=`pkg-config --libs opencv`
LIBS+=-lqrencode
LDFLAGS+=-shared

all:$(PRO)

$(PRO):$(APPOBJ)
	g++ $(CXXFLAGS) $(LIBS) $(LDFLAGS) -o $@ $^

clean:
	rm -f  $(APPOBJ) $(PRO)

