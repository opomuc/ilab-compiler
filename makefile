.PHONY: all clean

# compiler settings
CC=g++
CFLAGS=-c -g -Wall -std=c++11
LATEXCC=pdflatex
LATEXFLAGS=

# files
SOURCES=Math.cpp Tree.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Mat
TEX_FILES=tree.tex
PDF_FILES=tree.pdf

all: $(SOURCES) $(EXECUTABLE) tree.pdf

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

%.tex:
	./$(EXECUTABLE)

%.pdf: %.tex
	$(LATEXCC) $(LATEXFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(TEX_FILES) $(PDF_FILES)
