############################################################################
################################VARIABLES###################################
############################################################################
NAME 			:= bot_irc

SRCS_DIR 		:= srcs/
INCS_DIR 		:= includes/
COMMAND_DIR		:= commands/
OBJS_DIR		:= .objs/
DOBJS_DIR		:= .dobjs/

FILES 			:= Bot\
				   BotCommand\
				   BotContext\
				   BotContextDispatcher\
				   LineParser\
				   main

COMMAND_FILES	:= PingComman\
				   SendfileCommand

COMMAND_FILE_DIR	:= $(addprefix $(COMMAND_DIR), $(COMMAND_FILES))

SRCS 			:= $(addprefix $(SRCS_DIR), $(addsuffix .cpp, $(FILES)))\
				   $(addprefix $(SRCS_DIR), $(addsuffix .cpp, $(COMMAND_FILE_DIR)))\

OBJS 			:= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))\
				   $(addprefix $(OBJS_DIR), $(addsuffix .o, $(COMMAND_FILE_DIR)))\

DOBJS 			:= $(addprefix $(DOBJS_DIR), $(addsuffix .o, $(FILES)))\
				   $(addprefix $(DOBJS_DIR), $(addsuffix .o, $(COMMAND_FILE_DIR)))\

DEPS 			:= $(addprefix $(OBJS_DIR), $(addsuffix .d, $(FILES)))\
				   $(addprefix $(OBJS_DIR), $(addsuffix .d, $(COMMAND_FILE_DIR)))\

F_ERR			:= -Wall -Wextra -Werror
F_DEP			:= -MMD -MP
F_INC			:= -I$(INCS_DIR)
F_CPP			:= -std=c++98
CXXFLAGS 		:= $(F_ERR) $(F_DEP) $(F_INC) $(F_CPP)
DFLAGS 			:= -g -O0
CXX				:= c++

VALGRIND		?= valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes

############################################################################
##################################RULES#####################################
############################################################################

all: 				$(NAME)

$(NAME):			$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.cpp Makefile
		@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/$(COMMAND_DIR)
		$(CXX) $(CXXFLAGS) -c $< -o $@

debug:				$(DOBJS)
		@mkdir -p $(DOBJS_DIR)
		$(CXX) $(CXXFLAGS) $(DFLAGS) $(SRCS) -o $(NAME)

$(DOBJS_DIR)%.o:	$(SRCS_DIR)%.cpp
		@mkdir -p $(DOBJS_DIR) $(DOBJS_DIR)/$(COMMAND_DIR)
		$(CXX) $(CXXFLAGS) $< -o $@

run:				all
		./$(NAME) 127.0.0.1:6667 irc marc bob

val:				debug
	$(VALGRIND) ./$(NAME) 127.0.0.1:6667 irc marc bob

clean:
		rm -rf $(OBJS_DIR)
		rm -rf $(DOBJS_DIR)

fclean:				clean
		rm $(NAME)

re:					fclean all

re_debug:			fclean debug

.PHONY:				all clean fclean re debug re_debug val run

-include			$(DEPS)