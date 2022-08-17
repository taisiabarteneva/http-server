NAME = run

VPATH = Http/ Net/ Core/ Parser/ Server/
 
SRCS = main.cpp Http.cpp Request.cpp Response.cpp Net.cpp Core.cpp config_file.cpp location.cpp Server.cpp

OBJS_DIR = obj

OBJS = $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(SRCS))

CFLAGS = -g #-fsanitize=address -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o : %.cpp $(OBJS_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

clean:
	$(RM) -rv $(OBJS) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re
