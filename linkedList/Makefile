RM=rm -f

WARNING_FLAGS=-Wall -Wextra -Werror

TEST_NAME=linkedListTest
TEST_EXE=$(TEST_NAME).out
TEST_OBJ=$(TEST_NAME).o

all: test

test: $(TEST_OBJ)
	g++ $(WARNING_FLAGS) -o $(TEST_EXE) $(TEST_OBJ) -std=c++11
	./$(TEST_EXE)

clean:
	$(RM) $(TEST_EXE) $(TEST_OBJ)
