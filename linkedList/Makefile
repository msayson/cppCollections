RM=rm -f

WARNING_FLAGS=-Wall -Wextra -Werror

TEST=linkedListTest
TEST_OBJ=$(TEST).o

all: test

test: $(TEST_OBJ)
	g++ $(WARNING_FLAGS) -o $(TEST) $(TEST_OBJ) -std=c++11
	./$(TEST)

clean:
	$(RM) $(TEST) $(TEST_OBJ)
