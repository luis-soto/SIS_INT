CFLAGS = -I../remoteApi -I../include -DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255 -DDO_NOT_USE_SHARED_MEMORY

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	CFLAGS += -D__linux
else
	CFLAGS += -D__APPLE__
endif

all: 
	@rm -f bin/*.*
	@rm -f *.o 
	g++ $(CFLAGS) -c DuckieTownClient.cpp -o DuckieTownClient.o
	gcc $(CFLAGS) -c ../remoteApi/extApi.c -o extApi.o
	gcc $(CFLAGS) -c ../remoteApi/extApiPlatform.c -o extApiPlatform.o
	g++ $(CFLAGS) -c fuzzy_control.cpp -o fuzzy_control.o
	g++ $(CFLAGS) -c fuzzyset.cpp -o fuzzyset.o
	g++ $(CFLAGS) -c lingvar.cpp -o lingvar.o
	g++ $(CFLAGS) -c rule.cpp -o rule.o
	g++ $(CFLAGS) -c flie.cpp -o flie.o
	@mkdir -p bin
	g++ extApi.o extApiPlatform.o DuckieTownClient.o fuzzy_control.o fuzzyset.o lingvar.o rule.o flie.o -o ../../DuckieTownClient -lpthread
