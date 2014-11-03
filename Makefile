# Define the following machine dependent settings in Makefile.config:
# COMPILE_MAIN - SFML inlcude dir flag (& C++11 flag for Windows & Linux)
# COMPILE_TEST - Google Test & Google Mock include directories (use system includes)
# LINK_MAIN - SFML library dir flag & libraries to link against
# LINK_TEST - Google Test & Google Mock library dir flag and library to link against
include Makefile.config

EXEC_MAIN = SpaceEvaders
EXEC_TEST = SpaceEvadersTest
CXXFLAGS = -c -Wall $(COMPILE_MAIN) $(COMPILE_TEST)
OBJDIR_MAIN = build/main/
OBJDIR_TEST = build/test/
OUT = bin/
BUILD_CONFIG_FILE = src/main/BuildConfig.hpp

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

ifndef CXX
    CXX = g++
endif

ifeq ($(mode),release)
	OBJDIR_MAIN := $(OBJDIR_MAIN)Release/
	OUT := $(OUT)Release/
else
	mode = debug
	OBJDIR_MAIN := $(OBJDIR_MAIN)Debug/
	OUT := $(OUT)Debug/
	CXXFLAGS += -g
endif

SOURCES_MAIN := $(call rwildcard,src/main/,*.cpp)
SOURCES_TEST := $(call rwildcard,src/test/,*.cpp)
HEADERS := $(call rwildcard,src/,*.h*)
OBJECTS_MAIN := $(patsubst src/main/%,$(OBJDIR_MAIN)%,$(SOURCES_MAIN:.cpp=.o))
OBJECTS_TEST := $(patsubst src/test/%,$(OBJDIR_TEST)%,$(SOURCES_TEST:.cpp=.o))

build: $(OUT)$(EXEC_MAIN)

test: $(OUT)$(EXEC_TEST)
	@echo "<<< Running tests >>>"
	$(OUT)$(EXEC_TEST)

all:
	@make build mode=debug
	@make build mode=release

set-test-flag:
	@echo '#define RUN_TESTS' >> $(BUILD_CONFIG_FILE)

$(OUT)$(EXEC_MAIN): $(OBJECTS_MAIN)
	@mkdir -p $(OUT)
	@echo "<<< Linking main >>>"
	$(CXX) $(OBJECTS_MAIN) -o $@ $(LINK_MAIN)

$(OUT)$(EXEC_TEST): set-test-flag $(OBJECTS_MAIN) $(OBJECTS_TEST)
	@mkdir -p $(OUT)
	@echo "<<< Linking tests >>>"
	$(CXX) $(OBJECTS_MAIN) $(OBJECTS_TEST) -o $@ $(LINK_MAIN) $(LINK_TEST)

$(OBJDIR_MAIN)%.o: src/main/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "<<< Compiling main >>> "$<
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo ""

$(OBJDIR_TEST)%.o: src/test/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@echo "<<< Compiling tests >>> "$<
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo ""

clean:
	@echo "<<< Cleaning >>>"
	rm -rf $(OBJDIR_MAIN)
	rm -rf $(OBJDIR_TEST)
	rm -rf $(OUT)
# Clear flags from build config
	sed -i '/#/d' $(BUILD_CONFIG_FILE)
# Ensure config is still writable (sed on Windows seems to make read only?)
	chmod 6 $(BUILD_CONFIG_FILE)

clobber:
	@echo "<<< Clobbering >>>"
	rm -rf build/
	rm -rf bin/
