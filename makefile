.PHONY: all clean pdf

# compiler settings
CC=g++
CFLAGS=-c -g -Wall -std=c++11
LATEXCC=pdflatex
LATEXFLAGS=-quiet

# files
SOURCES=Math.cpp Tree.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Mat
TEX_FILES=tree.tex
PDF_FILES=$(TEX_FILES:.tex=.pdf)

all: $(SOURCES) $(EXECUTABLE) pdf

pdf: $(PDF_FILES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

%.tex:
	ifdef OS
		ifeq ($(OS), Windows_NT)
			$(EXECUTABLE)
		else
			./$(EXECUTABLE)
		endif
	else
		ifeq($(shell uname), Linux)
			./$(EXECUTABLE)
		else
			$(EXECUTABLE)
		endif
	endif

%.pdf: %.tex
	$(LATEXCC) $(LATEXFLAGS) $<

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(TEX_FILES) $(PDF_FILES)