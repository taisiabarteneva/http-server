NAME = run

SRCS = main.cpp Http.cpp

OBJS_DIR = obj

OBJS = $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(SRCS))

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o : %.cpp $(OBJS_DIR)
	$(CXX) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

clean:
	$(RM) -rv $(OBJS) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re
