CXX = g++
CXXFLAGS = -std=c++11 -pthread
SRC = fastdeduper.cpp
OUT = fastdeduper
PREFIX = /usr
BINDIR = $(PREFIX)/bin

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

install: $(OUT)
	install -D -m 755 $(OUT) $(DESTDIR)$(BINDIR)/$(OUT)

clean:
	rm -f $(OUT)