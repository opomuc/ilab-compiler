.PHONY: all clean pdf

# get OS information
OSFLAG :=
	ifeq ($(OS),Windows_NT)
		OSFLAG += -D WIN32
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			OSFLAG += -D AMD64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			OSFLAG += -D IA32
		endif
	else
		UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S),Linux)
			OSFLAG += -D LINUX
		endif
		ifeq ($(UNAME_S),Darwin)
			OSFLAG += -D OSX
		endif
			UNAME_P := $(shell uname -p)
		ifeq ($(UNAME_P),x86_64)
			OSFLAG += -D AMD64
		endif
			ifneq ($(filter %86,$(UNAME_P)),)
		OSFLAG += -D IA32
			endif
		ifneq ($(filter arm%,$(UNAME_P)),)
			OSFLAG += -D ARM
		endif
	endif

# compiler settings
CC=g++
CFLAGS=-c -g -Wall -std=c++11
LATEXCC=pdflatex
LATEXFLAGS=-quiet

# files
SOURCES=Math.cpp Tree.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TEX_FILES=tree.tex
PDF_FILES=$(TEX_FILES:.tex=.pdf)

# executable
ifeq (WIN32,$(findstring WIN32,$(OSFLAG)))
EXECUTABLE=Mat.exe
else
EXECUTABLE=Mat
endif

all: $(SOURCES) $(EXECUTABLE) pdf

pdf: $(PDF_FILES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

ifeq (WIN32,$(findstring WIN32,$(OSFLAG)))
%.tex:
	$(EXECUTABLE)
else
%.tex:
	./$(EXECUTABLE)
endif

%.pdf: %.tex
	$(LATEXCC) $(LATEXFLAGS) $<

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(TEX_FILES) $(PDF_FILES)