############################################################################
################################VARIABLES###################################
############################################################################

NAME 			:= ircserv

SRCS_DIR 		:= srcs/
INCS_DIR 		:= includes/
OBJS_DIR		:= .objs/
DOBJS_DIR		:= .dobjs/

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
				   CommandDispatcher \
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
				   Command \
				   Replies \
				   Utils \
				   main

HEADERS 		:= Server \
				   EventLoop \
				   EventHandler \
				   ClientHandler \
				   ServerHandler \
				   Client \
				   Channel \
				   ClientManager \
				   ChannelManager \
				   Message \
				   CommandDispatcher \
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
				   Replies \
				   Status \
				   RegRule \
				   Utils \
				   Command
				   

SRCS 			:= $(addprefix $(SRCS_DIR), $(addsuffix .cpp, $(FILES)))
INCS 			:= $(addprefix $(INCS_DIR), $(addsuffix .hpp, $(HEADERS)))
OBJS 			:= $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
DOBJS 			:= $(addprefix $(DOBJS_DIR), $(addsuffix .o, $(FILES)))
DEPS 			:= $(addprefix $(OBJS_DIR), $(addsuffix .d, $(FILES)))

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
		@mkdir -p $(OBJS_DIR)
		$(CXX) $(CXXFLAGS) -c $< -o $@

debug:				$(DOBJS)
		@echo "\nlinking..."
		$(CXX) $(CXXFLAGS) $(DOBJS) -o $(NAME)

$(DOBJS_DIR)%.o:	$(SRCS_DIR)%.cpp Makefile
		@echo "\ncompiling..."
		@mkdir -p $(DOBJS_DIR)
		$(CXX) $(CXXFLAGS) $(DFLAGS) -c $< -o $@

run:				all
		./$(NAME) 6667 irc

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

.PHONY:				all clean fclean re debug re_debug val run

-include 			$(DEPS)
