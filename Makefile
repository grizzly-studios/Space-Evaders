# Define the following machine dependent settings in Makefile.config:
# COMPILE - SFML inlcude dir flag (& C++11 flag for Windows & Linux)
# LINK - SFML library dir flag & libraries to link against
-include Makefile.config

EXEC = SpaceEvaders
CXXFLAGS = -c -Wall $(COMPILE)
OBJDIR = build/
OUT = bin/

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

ifndef CXX
    CXX = g++
endif

ifeq ($(mode),release)
	OBJDIR := $(OBJDIR)Release/
	OUT := $(OUT)Release/
else
	mode = debug
	OBJDIR := $(OBJDIR)Debug/
	OUT := $(OUT)Debug/
	CXXFLAGS += -g
endif

SOURCES := $(call rwildcard,src/,*.cpp)
HEADERS := $(call rwildcard,src/,*.h*)
OBJECTS := $(patsubst src/main/%,$(OBJDIR)%,$(SOURCES:.cpp=.o))

build: $(OUT)$(EXEC)

all:
	@make build mode=debug
	@make build mode=release
	
$(OUT)$(EXEC): $(OBJECTS)
	@mkdir -p $(OUT)
	@echo "<<< Linking >>>"
	$(CXX) $(OBJECTS) -o $@ $(LINK)

$(OBJDIR)%.o: src/main/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "<<< Compiling >>> "$<
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo ""
	
clean:
	@echo "<<< Cleaning >>>"
	rm -rf $(OBJDIR)
	rm -rf $(OUT)

clobber:
	@echo "<<< Clobbering >>>"
	rm -rf build/
	rm -rf bin/
