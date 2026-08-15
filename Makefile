############################################################################
################################VARIABLES###################################
############################################################################

NAME 			:= ircserv

SRCS_DIR 		:= srcs/
COMMAND_DIR		:= command/
INCS_DIR 		:= includes/
OBJS_DIR		:= .objs/
DOBJS_DIR		:= .dobjs/
BOT_DIR			:= bot/

COMMAND_FILES	:= CommandDispatcher \
				   CommandContext \
				   ModeTracker \
				   PassCommand \
				   NickCommand \
				   UserCommand \
				   JoinCommand \
				   PartCommand \
				   KickCommand \
				   WhoCommand \
				   ModeCommand \
				   InviteCommand \
				   TopicCommand \
				   PrivMsgCommand \
				   Command

COMMAND_FILE_DIR	:= $(addprefix $(COMMAND_DIR), $(COMMAND_FILES))

FILES 			:= Server \
				   EventLoop \
				   EventHandler \
				   ClientHandler \
				   ServerHandler \
				   Client \
				   Channel \
				   ClientManager \
				   ChannelManager \
				   Message \
				   Replies \
				   Utils \
				   main
				   
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

all:				$(NAME)


$(NAME):			$(OBJS)
		@echo "\nlinking..."
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.cpp Makefile
		@echo "\ncompiling..."
		@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/$(COMMAND_DIR)
		$(CXX) $(CXXFLAGS) -c $< -o $@

debug:				$(DOBJS)
		@echo "\nlinking..."
		$(CXX) $(CXXFLAGS) $(DOBJS) -o $(NAME)

$(DOBJS_DIR)%.o:	$(SRCS_DIR)%.cpp Makefile
		@echo "\ncompiling..."
		@mkdir -p $(DOBJS_DIR) $(DOBJS_DIR)/$(COMMAND_DIR)
		$(CXX) $(CXXFLAGS) $(DFLAGS) -c $< -o $@

run:				all
		./$(NAME) 6667 irc

bonus:
		$(MAKE) --no-print-directory --directory=$(BOT_DIR) all

bonus_re:
		$(MAKE) --no-print-directory --directory=$(BOT_DIR) re

bonus_fclean:
		$(MAKE) --no-print-directory --directory=$(BOT_DIR) fclean

val:				debug
		$(VALGRIND) ./$(NAME) 6667 irc

clean:
		@echo "\nremoving the objects..."
		rm -rf $(OBJS_DIR)
		rm -rf $(DOBJS_DIR)


fclean:				clean
		@echo "\nremoving the executable..."
		rm -rf $(NAME)

re:					fclean all

re_debug:			fclean debug

.PHONY:				all clean fclean re debug re_debug val run bonus bonus_re bonus_fclean

-include 			$(DEPS)
