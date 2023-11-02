
#
#	Compilation and linking options
#

CC							= g++
CXXFLAGS					= -I ./include -Wall -Werror -Wextra -std=c++17 -pedantic -g
LDFLAGS						= $(shell pkg-config --cflags --libs gtest) -lgtest_main
GCFLAGS						= -fprofile-arcs -ftest-coverage -fPIC
VGFLAGS						= --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

#
#	Extensions
#

CPP							= .cc
TPP							= .tpp
HEADERS						= .h
OBJ							= .o

#
#	Connecting source file directories
#

VPATH						:= $(shell find . -type d)
vpath %$(CPP) $(VPATH)
vpath %$(HEADERS) $(VPATH)

#
#	Directories of source and object files
#

SRC_GRAPH_DIR				= sources/graph/
SRC_GRAPH_ALGS_DIR			= sources/algorithms/
SRC_CLI_DIR					= sources/cli/
SRC_TESTS_DIR				= tests/
OBJ_GRAPH_DIR				= ../obj/graph/
OBJ_GRAPH_ALGS_DIR			= ../obj/algorithms/
OBJ_TESTS_DIR				= ../obj/tests/
OBJ_DIR						= ../obj/

#
#	Subdirectories of source files
#

SRC_GRAPH_DIRS				:= $(shell find $(SRC_GRAPH_DIR) -type d)
SRC_GRAPH_ALGS_DIRS			:= $(shell find $(SRC_GRAPH_ALGS_DIR) -type d)

#
#	Name of libraries
#

GRAPH_LIBRARY				= s21_graph.a
GRAPH_ALGS_LIBRARY			= s21_graph_algorithms.a

#
#	Creating folders for object files
#

OBJ_GRAPH_FOLDER			:= $(shell mkdir -p $(OBJ_GRAPH_DIR))
OBJ_GRAPH_ALGS_FOLDER		:= $(shell mkdir -p $(OBJ_GRAPH_ALGS_DIR))
OBJ_TESTS_FOLDER			:= $(shell mkdir -p $(OBJ_TESTS_DIR))

#
#	Parsing of source files from directories and subdirectories
#

SRC_GRAPH					:= $(foreach dir, $(SRC_GRAPH_DIRS), $(wildcard $(dir)/*$(CPP)))
SRC_GRAPH_ALGS				:= $(foreach dir, $(SRC_GRAPH_ALGS_DIRS), $(wildcard $(dir)/*$(CPP)))
SRC_TESTS					:= $(foreach dir, $(SRC_TESTS_DIR), $(wildcard $(dir)/*$(CPP)))

#
#	Creating object files
#

OBJ_GRAPH					:= $(patsubst %$(CPP), $(OBJ_GRAPH_DIR)%$(OBJ), $(notdir $(SRC_GRAPH)))
OBJ_GRAPH_ALGS				:= $(patsubst %$(CPP), $(OBJ_GRAPH_ALGS_DIR)%$(OBJ), $(notdir $(SRC_GRAPH_ALGS)))
OBJ_TESTS					:= $(patsubst %$(CPP), $(OBJ_TESTS_DIR)%$(OBJ), $(notdir $(SRC_TESTS)))

#
#	TARGETS
#

all: $(GRAPH_LIBRARY) $(GRAPH_ALGS_LIBRARY) test

$(GRAPH_LIBRARY): $(OBJ_GRAPH)
	ar rc $(GRAPH_LIBRARY) $(OBJ_GRAPH)
	ranlib $(GRAPH_LIBRARY)

$(GRAPH_ALGS_LIBRARY): $(OBJ_GRAPH_ALGS)
	ar rc $(GRAPH_ALGS_LIBRARY) $(OBJ_GRAPH_ALGS)
	ranlib $(GRAPH_ALGS_LIBRARY)

test: $(GRAPH_LIBRARY) $(GRAPH_ALGS_LIBRARY) $(OBJ_TESTS)
	$(CC) $(CXXFLAGS) $(OBJ_TESTS) -o test $(GRAPH_LIBRARY) $(GRAPH_ALGS_LIBRARY) $(LDFLAGS)
	./test

coverage: $(GRAPH_LIBRARY) $(GRAPH_ALGS_LIBRARY) $(OBJ_TESTS)
	$(CC) $(CXXFLAGS) $(GCFLAGS) -o test $(OBJ_TESTS) --coverage $(SRC_GRAPH) $(SRC_GRAPH_ALGS) $(LDFLAGS)
	./test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info

open_coverage_report:
	open report/index.html

run: $(GRAPH_LIBRARY) $(GRAPH_ALGS_LIBRARY)
	$(CC) $(CXXFLAGS) $(SRC_CLI_DIR)*$(CPP) -o CLI $(GRAPH_LIBRARY) $(GRAPH_ALGS_LIBRARY)
	./CLI

valgrind: test
	valgrind $(VGFLAGS) ./test
	! grep -n "ERROR SUMMARY" valgrind.txt | grep -v "0 errors"

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(GRAPH_LIBRARY)
	rm -rf $(GRAPH_ALGS_LIBRARY)
	rm -rf test
	rm -rf CLI
	rm -rf valgrind.txt
	rm -rf report
	rm -rf *.info
	rm -rf *.gc*

$(OBJ_GRAPH_DIR)%$(OBJ): %$(CPP)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJ_GRAPH_ALGS_DIR)%$(OBJ): %$(CPP)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJ_TESTS_DIR)%$(OBJ): %$(CPP)
	$(CC) $(CXXFLAGS) -c $< -o $@

format_set:
	find . -iname "*$(CPP)" -o -iname "*$(HEADERS)" -o -iname "*$(TPP)" | xargs clang-format --style=google -i

format_check:
	find . -iname "*$(CPP)" -o -iname "*$(HEADERS)" -o -iname "*$(TPP)" | xargs clang-format --style=google -n

.PHONY: all test clean valgrind format_set format_check