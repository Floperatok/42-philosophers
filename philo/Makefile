####################################################################
#                            CONFIG                                #
####################################################################

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra -pthread -g
NAME			=	philo

####################################################################
#                            FILES                                 #
####################################################################

SRC				=	main.c \
					errors.c \
					utils.c \
					init.c \
					execution.c \
					tasks.c \
					time.c

OBJ				=	$(SRC:.c=.o)

####################################################################
#                            PATHS                                 #
####################################################################

OBJ_PATH		=	obj/
OBJS			=	$(addprefix $(OBJ_PATH), $(OBJ))

####################################################################
#                            RULES                                 #
####################################################################

all:	$(NAME)

$(OBJ_PATH)%.o:	%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	@echo -n "$(COM_COLOR)compiling $(NAME)...     $(NO_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(COM_COLOR)done: $(OK_COLOR)[✓]$(NO_COLOR)"


clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(COM_COLOR)clean:                       $(OK_COLOR)[✓]$(NO_COLOR)"

fclean:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@echo "$(COM_COLOR)fclean:                      $(OK_COLOR)[✓]$(NO_COLOR)"

re: fclean all

####################################################################
#                            COLORS                                #
####################################################################

COM_COLOR   = \033[0;34m
OK_COLOR    = \033[0;32m
NO_COLOR    = \033[m