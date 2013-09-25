EXEC = "Space-Evaders" 
LIBRARIES = /usr/local/lib/libsfml-audio.2.1.dylib /usr/local/lib/libsfml-graphics.2.1.dylib /usr/local/lib/libsfml-network.2.1.dylib /usr/local/lib/libsfml-system.2.1.dylib /usr/local/lib/libsfml-window.2.1.dylib 
INCLUDES = include/
LIBS = /usr/local/lib/
CXXFLAGS = -c -Wall -I$(INCLUDES)
OBJDIR = build/
OUT = bin/

SOURCES = $(shell find . -type f -name '*.cpp')
HEADERS = $(wildcard *.h*)
OBJECTS = $(SOURCES:.cpp=.o)

ifeq ($(mode),release)
	OBJDIR := $(OBJDIR)Release/
	OUT := $(OUT)Release/
else
	mode = debug
	OBJDIR := $(OBJDIR)Debug/
	OUT := $(OUT)Debug/
	CXXFLAGS += -g
endif

build: $(OUT)$(EXEC)

all:
	@make build mode=debug
	@make build mode=release

$(OUT)$(EXEC): $(OBJECTS)
	@mkdir -p $(OUT)
	@echo "<<< Linking >>>"
	g++ -L$(LIBS) -I$(INCLUDES) $(LIBRARIES) $(patsubst %,$(OBJDIR)/%,$(notdir $(OBJECTS))) -o $@

%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	@echo "<<< Compiling >>> "$<
	g++ $(CXXFLAGS) $< -o $(OBJDIR)$(notdir $@)
	@echo ""

clean:
	@echo "<<< Cleaning >>>"
	rm -f $(OUT)$(EXEC) $(patsubst %,$(OBJDIR)/%,$(notdir $(OBJECTS)))

clobber:
	@make clean mode=debug
	@make clean mode=release 
