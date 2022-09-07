NAME = run

VPATH = Http/ Net/ Core/ Parser/ Server/ Cgi/
 
SRCS = main.cpp Http.cpp Request.cpp Response.cpp Net.cpp Core.cpp ConfigFile.cpp Location.cpp Server.cpp Cgi.cpp

OBJS_DIR = obj

OBJS = $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(SRCS))

CFLAGS = -g # -fsanitize=address -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)
	@mkdir -p resources/files

$(OBJS_DIR)/%.o : %.cpp | $(OBJS_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

clean:
	$(RM) -rv $(OBJS) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re
