.PHONY: all clean tex pdf

# compiler settings
CC=g++
CFLAGS=-c -g -Wall
LATEXCC=
LATEXFLAGS=

# files
SOURCES=Math.cpp Tree.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Mat
TEX_FILE=

all: $(SOURCES) $(EXECUTABLE) pdf

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

tex:
#$(EXECUTABLE) > $(TEX_FILE)
	@echo $@ -- Not implemented

pdf: tex
#$(LATEXCC) $(LATEXFLAGS) $(TEX_FILE)
	@echo $@ -- Not implemented

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(TEX_FILE)