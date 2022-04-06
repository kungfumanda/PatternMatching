pmt:
	g++ src/main.cpp -o $(CURDIR)/bin/pmt -std=c++14 -O3
add-to-paths: 
	export PATH=${PATH}:$(CURDIR)/bin/
