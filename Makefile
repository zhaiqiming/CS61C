CC = gcc
CFLAGS = -g -Wall -std=c99 -c
LDFLAGS = -g -Wall
CUNIT = -L/home/ff/cs61c/cunit/install/lib -I/home/ff/cs61c/cunit/install/include -lcunit
BUILD_DIR = ./build

# A phony target is one that is not really the name of a file;
# rather it is just a name for a recipe to be executed when you make an explicit request.
# You can read more about them here: https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY : all test clean unittest

all : philphix

philphix : philphix.o hashtable.o
	$(CC) $(LDFLAGS) -o philphix $(BUILD_DIR)/philphix.o $(BUILD_DIR)/hashtable.o

philphix.o : src/philphix.c src/philphix.h src/hashtable.h build_dir
	$(CC) $(CFLAGS) src/philphix.c -o $(BUILD_DIR)/philphix.o

hashtable.o : src/hashtable.c src/hashtable.h build_dir
	$(CC) $(CFLAGS) src/hashtable.c -o $(BUILD_DIR)/hashtable.o

build_dir :
	mkdir -p $(BUILD_DIR)

clean :
	rm -f $(BUILD_DIR)/*.o philphix unittest

# Make sure you leave testpassedall as the last thing in this line. You can add your own custom tests before it.
test: test_basic test_alphanumeric test_large_dict test_capitalization test_empty test_tabs_and_spaces test_numbers test_no_newline test_no_newline_longer test_binary test_long_word_input test_long_word_dict testpassedall

test_basic: clean philphix
	touch tests/basic/test_basic.out
	rm tests/basic/test_basic.out
	@echo "================Running Program...================="
	cat tests/basic/test_basic.in | ./philphix tests/basic/test_basic.dict > tests/basic/test_basic.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/basic/test_basic.out tests/basic/test_basic.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_alphanumeric: clean philphix
	touch tests/alphanumeric/test_alphanumeric.out
	rm tests/alphanumeric/test_alphanumeric.out
	@echo "================Running Program...================="
	cat tests/alphanumeric/test_alphanumeric.in | ./philphix tests/alphanumeric/test_alphanumeric.dict > tests/alphanumeric/test_alphanumeric.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/alphanumeric/test_alphanumeric.out tests/alphanumeric/test_alphanumeric.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_large_dict: clean philphix
	touch tests/large_dict/test_large_dict.out
	rm tests/large_dict/test_large_dict.out
	@echo "================Running Program...================="
	cat tests/large_dict/test_large_dict.in | ./philphix tests/large_dict/test_large_dict.dict > tests/large_dict/test_large_dict.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/large_dict/test_large_dict.out tests/large_dict/test_large_dict.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_capitalization: clean philphix
	touch tests/capitalization/test_capitalization.out
	rm tests/capitalization/test_capitalization.out
	@echo "================Running Program...================="
	cat tests/capitalization/test_capitalization.in | ./philphix tests/capitalization/test_capitalization.dict > tests/capitalization/test_capitalization.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/capitalization/test_capitalization.out tests/capitalization/test_capitalization.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_empty: clean philphix
	touch tests/empty/test_empty.out
	rm tests/empty/test_empty.out
	@echo "================Running Program...================="
	cat tests/empty/test_empty.in | ./philphix tests/empty/test_empty.dict > tests/empty/test_empty.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/empty/test_empty.out tests/empty/test_empty.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_tabs_and_spaces: clean philphix
	touch tests/tabs_and_spaces/test_tabs_and_spaces.out
	rm tests/tabs_and_spaces/test_tabs_and_spaces.out
	@echo "================Running Program...================="
	cat tests/tabs_and_spaces/test_tabs_and_spaces.in | ./philphix tests/tabs_and_spaces/test_tabs_and_spaces.dict > tests/tabs_and_spaces/test_tabs_and_spaces.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/tabs_and_spaces/test_tabs_and_spaces.out tests/tabs_and_spaces/test_tabs_and_spaces.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_numbers: clean philphix
	touch tests/numbers/test_numbers.out
	rm tests/numbers/test_numbers.out
	@echo "================Running Program...================="
	cat tests/numbers/test_numbers.in | ./philphix tests/numbers/test_numbers.dict > tests/numbers/test_numbers.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/numbers/test_numbers.out tests/numbers/test_numbers.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_no_newline: clean philphix
	touch tests/no_newline/test_no_newline.out
	rm tests/no_newline/test_no_newline.out
	@echo "================Running Program...================="
	cat tests/no_newline/test_no_newline.in | ./philphix tests/no_newline/test_no_newline.dict > tests/no_newline/test_no_newline.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/no_newline/test_no_newline.out tests/no_newline/test_no_newline.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_no_newline_longer: clean philphix
	touch tests/no_newline_longer/test_no_newline_longer.out
	rm tests/no_newline_longer/test_no_newline_longer.out
	@echo "================Running Program...================="
	cat tests/no_newline_longer/test_no_newline_longer.in | ./philphix tests/no_newline_longer/test_no_newline_longer.dict > tests/no_newline_longer/test_no_newline_longer.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/no_newline_longer/test_no_newline_longer.out tests/no_newline_longer/test_no_newline_longer.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_binary: clean philphix
	touch tests/binary/test_binary.out
	rm tests/binary/test_binary.out
	@echo "================Running Program...================="
	cat tests/binary/test_binary.in | ./philphix tests/binary/test_binary.dict > tests/binary/test_binary.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/binary/test_binary.out tests/binary/test_binary.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_long_word_input: clean philphix
	touch tests/long_word_input/test_long_word_input.out
	rm tests/long_word_input/test_long_word_input.out
	@echo "================Running Program...================="
	cat tests/long_word_input/test_long_word_input.in | ./philphix tests/long_word_input/test_long_word_input.dict > tests/long_word_input/test_long_word_input.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/long_word_input/test_long_word_input.out tests/long_word_input/test_long_word_input.ref
	@echo "-----------------------None!-----------------------"
	@echo

test_long_word_dict: clean philphix
	touch tests/long_word_dict/test_long_word_dict.out
	rm tests/long_word_dict/test_long_word_dict.out
	@echo "================Running Program...================="
	cat tests/long_word_dict/test_long_word_dict.in | ./philphix tests/long_word_dict/test_long_word_dict.dict > tests/long_word_dict/test_long_word_dict.out
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/long_word_dict/test_long_word_dict.out tests/long_word_dict/test_long_word_dict.ref
	@echo "-----------------------None!-----------------------"
	@echo

testpassedall:
	@echo "You have passed all of the tests!"

unittest: 
	$(CC) $(LDFLAGS) -D _PHILPHIX_UNITTEST ./tests/phil_test.c ./src/philphix.c ./src/hashtable.c -o unittest $(CUNIT)
	./unittest
