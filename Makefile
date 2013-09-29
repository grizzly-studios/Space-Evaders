# Define the following in Makefile.config:
# SFML_DIR - SFML installation directory
# LIBRARIES - libraries to link against
include Makefile.config

EXEC = SpaceEvaders
INCLUDES = $(SFML_DIR)/include/
LIBS = $(SFML_DIR)/lib/
CXXFLAGS = -c -Wall -I$(INCLUDES)
OBJDIR = build/
OUT = bin/

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))


SOURCES := $(call rwildcard,src/,*.cpp)
HEADERS := $(call rwildcard,src/,*.h*)
OBJECTS := $(patsubst %,$(OBJDIR)%,$(notdir $(SOURCES:.cpp=.o)))
	

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
	g++ $(patsubst %,$(OBJDIR)%,$(notdir $(OBJECTS))) -o $@ -L$(LIBS) $(LIBRARIES)

$(OBJECTS): $(SOURCES) $(HEADERS)
	@mkdir -p $(OBJDIR)
	@echo "<<< Compiling >>> "$<
	g++ $(CXXFLAGS) $< -o $@
	@echo ""

clean:
	@echo "<<< Cleaning >>>"
	rm -r build
	rm -r bin

clobber:
	@make clean mode=debug
	@make clean mode=release 
