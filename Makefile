pwd := $(CURDIR)
pathvar := ${PATH}
seqtest := 1

pmt:
	g++ src/main.cpp -o pmt -std=c++14 -O3
add-to-paths: 
	export PATH=$(pathvar):$(pwd)/bin/

## TODO: Add tests here