############################################################################
################################VARIABLES###################################
############################################################################

NAME 			:= ircserv

SRCS_DIR 		:= srcs/
INCS_DIR 		:= includes/
OBJS_DIR		:= .objs/

FILES 			:= Server \
				   EventLoop \
				   EventHandler \
				   ClientHandler \
				   ServerHandler \
				   Client \
				   ClientManager \
				   Message \
				   CommandDispatcher \
				   CommandContext \
				   PassCommand \
				   NickCommand \
				   Command \
				   main

HEADERS 		:= Server \
				   EventLoop \
				   EventHandler \
				   ClientHandler \
				   ServerHandler \
				   Client \
				   ClientManager \
				   Message \
				   CommandDispatcher \
				   CommandContext \
				   PassCommand \
				   NickCommand \
				   Command 

SRCS 			:= $(addprefix $(SRCS_DIR), $(addsuffix .cpp, $(FILES)))
INCS 			:= $(addprefix $(INCS_DIR), $(addsuffix .hpp, $(HEADERS)))
OBJS 			:= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
DEPS 			:= $(addprefix $(OBJS_DIR), $(addsuffix .d, $(FILES)))

F_ERR			:= -Wall -Wextra -Werror
F_DEP			:= -MMD -MP
F_INC			:= -I$(INCS_DIR)
F_CPP			:= -std=c++98
CXXFLAGS 		:= $(F_ERR) $(F_DEP) $(F_INC) $(F_CPP)
CXX				:= c++

############################################################################
##################################RULES#####################################
############################################################################

all:				$(NAME)


$(NAME):			$(OBJS)
		@echo "\nlinking..."
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)


$(OBJS_DIR)%.o:		$(SRCS_DIR)%.cpp
		@echo "\ncompiling..."
		@mkdir -p $(OBJS_DIR)
		$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
		@echo "\nremoving the objects..."
		rm -rf $(OBJS_DIR)


fclean:				clean
		@echo "\nremoving the executable..."
		rm -rf $(NAME)

re:					fclean all

.PHONY:				all clean fclean re

-include 			$(DEPS)
