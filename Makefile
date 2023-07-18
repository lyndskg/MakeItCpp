################ MAKEFILE ################

# IMPORTANT NOTES:
#   1. Set EXECUTABLE to the command name.
#   2. To enable automatic creation of unit test rules, your program logic
#      (where main() is) should be in a file named project*.cpp or
#      specified in the PROJFILE variable.
#   3. Files you want to include cannot match the test*.cpp pattern.

NAME := blackscholes

#------------------------------------------------#
#   BUILD VARIABLES                              #
#------------------------------------------------#
# EXE            executable name
#
# SRCS           C++ source files
# OBJS           C++ object files
#
# PROJFILE       project file containing main()
#
# CXX      	 C++ compiler
# CXXFLAGS   	 C++ compiler flags
# LDFLAGS        linker flags
#
# TESTSRCS       test drivers (with main()) for development
# TESTS	         test executables

EXE = bs

# The following line looks for a project's main() in files named project*.cpp,
# executable.cpp (substituted from EXECUTABLE above), or main.cpp
PROJFILE = $(or $(wildcard project*.cpp $(EXE).cpp), main.cpp)
# If main() is in another file delete line above, edit and uncomment below
PROJFILE = Program.cpp


# Designate which C++ compiler to use
CXX          = g++
# If using clang, uncomment below
# CXX = clang

# Test driver source files (with main()) for development
TESTSRCS = $(wildcard test*.cpp)

# Test executables
TESTS       = $(TESTSOURCES:%.cpp=%)

# Define the C++ source files used in the project
SRCS      = $(wildcard *.cpp) # Gets a list of all the C++ source files in a directory
SRCS 	  := $(filter-out $(TESTSRCS), $(SRCS))

# Define the C++ object files used in the project
OBJS     = $(SRCS:%.cpp=%.o)
OBJS	+= $(patsubst %.cpp, %.o, $(SRCS))

# Name of the perf data file, only used by the clean target
PERF_FILE = perf.data*

# Default C++ flags (-std=c++17 is preferred, but MacOS/xCode/Clang don't support)
CXXFLAGS     = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -g -I/opt/homebrew/opt/curl/include
# CAN ALSO USE -std=c++20

#------------------------------------------------#
#   LIBRARIES                                    #
#------------------------------------------------#
# INCLUDE
# LDFLAGS
# LDLIBS

# INCLUDE = -Iusr/local/include
LDFLAGS = -L/opt/homebrew/opt/curl/lib
LIBS = -lcurl -lssl -lcrypto

#------------------------------------------------#
#   SHELL COMMANDS                               #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
#
#RM          := rm -f
#MAKEFLAGS   += --no-print-directory

#------------------------------------------------#
#  BUILD & EXTRA RULES                           #
#------------------------------------------------#
# release
# debug
# profile
# gprof
# all
# alltests
# clean

# Default rule to build the executable
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
	
	
# Rule to compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXE)

    
# make release - will compile "all" with $(CXXFLAGS) and the -O3 flag
#                also defines NDEBUG so that asserts will not check
release: CXXFLAGS += -O3 -DNDEBUG
release: $(EXE)

# make debug - will compile sources with $(CXXFLAGS) and the -g3 flag
#              also defines DEBUG, so "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)_debug

# make profile - will compile "all" with $(CXXFLAGS) and the -g3 and -O3 flags
profile: CXXFLAGS += -g3 -O3
profile:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)_profile
	

# make gprof - will compile "all" with $(CXXFLAGS) and the -pg (for gprof, i.e. GNU profiler)
gprof: CXXFLAGS += -pg
gprof:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)_profile

# Build all executables
all: release debug profile

$(EXE): $(OBJS)
ifeq ($(EXE), exe)
	@echo Edit EXE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJS)
else
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXE)
endif

# Automatically generate any build rules for test*.cpp files
define make_tests
    ifeq ($$(PROJFILE),)
	    @echo Edit PROJFILE variable to .cpp file with main\(\)
	    @exit 1
    endif
    SRCS = $$(filter-out $$(PROJFILE), $$(SRCS))
    OBJS = $$(SRCS:%.cpp=%.o)
    HDRS = $$(wildcard *.h *.hpp)
    $(1): CXXFLAGS += -g3 -DDEBUG
    $(1): $$(OBJS) $$(HDRS) $(1).cpp
	$$(CXX) $$(CXXFLAGS) $$(OBJS) $(1).cpp -o $(1)
endef
$(foreach test, $(TESTS), $(eval $(call make_tests, $(test))))

alltests: $(TESTS)

################ UNIT TESTING SUPPORT ################
    A) Source files for unit testing should be named test*.cpp.  Examples
       include test_input.cpp or test3.cpp.
    B) Automatic build rules are generated to support the following:
           $$ make test_input
           $$ make test3
           $$ make alltests        (this builds all test drivers)
    C) If test drivers need special dependencies, they must be added
       manually.
######################################################


# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp


# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJS) $(EXE) $(EXE)_debug $(EXE)_profile \
      $(TESTS) $(PERF_FILE)
	rm -Rf *.dSYM

#------------------------------------------------#
#   SPECIAL TARGETS                              #
#------------------------------------------------#

.PHONY: all release debug profile gprof clean alltests

# disable built-in rules
.SUFFIXES:


####################################### END_1 ####

default: build

build: clean
	gcc -Wall -o curl main.c util.c -l curl
	
clean:
	rm -rf curl
	
test: build
	./curl https://freegeoip.app/json/
	


#######################
# TODO (begin) #
#######################
# individual dependencies for objects
# Examples:
# "Add a header file dependency"
# project2.o: project2.cpp project2.h
#
# "Add multiple headers and a separate class"
# HEADERS = some.h special.h header.h files.h
# myclass.o: myclass.cpp myclass.h $(HEADERS)
# project5.o: project5.cpp myclass.o $(HEADERS)
#
# SOME EXAMPLES
#
#test_thing: test_thing.cpp class.o functions.o
#class.o: class.cpp class.h
#functions.o: functions.cpp functions.h
#project0.o: project0.cpp class.h functions.h
#
# THE COMPILER CAN GENERATE DEPENDENCIES FROM SOURCE CODE
#
# % g++ -std=c++1z -MM *.cpp
#
# ADD YOUR OWN DEPENDENCIES HERE

######################
# TODO (end) #
######################

