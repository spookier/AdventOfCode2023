NAME = day04
MAKEFLAGS += --no-print-directory

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra

FILES = main.cpp

OBJ_FILES = $(FILES:.cpp=.o)



%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

ex:
	@make -s all
	@./$(NAME)

.PHONY: all clean fclean re
