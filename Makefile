NAME = clox

HEADER = ./headers/

AUTHOR = nkanaan

CC = gcc

CFLAGS = -g #-fsanitize=address

SRCS = main chunk mem debug value vm 

SRC = $(addprefix src/, $(addsuffix .c, $(SRCS)))

OBJS = $(addprefix objs/, $(addsuffix .o, $(SRCS)))

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
OK_COLOR        = \033[0;32m
_END            =       \e[0m
_GREEN          =       \e[32m
_WHITE          =       \e[37m
_MUP            =       \e[1A
_ERASE          =       \e[K

all: $(NAME)

objs/%.o:	src/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "\033[?25l"
	@printf "$(_ERASE)\r"
	@printf "$<$(_END)\n"
	@for i in $$(seq 1 $(CNT)); \
	do \
		printf "$(OK_COLOR)*"; \
	done
	$(eval CNT=$(shell echo $$(($(CNT) + 1))))
	@printf "\r$(_MUP)"


$(NAME):	$(OBJS) $(HEADER)
	@$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)
	@printf "%-53b%b" "$(COM_COLOR)Project Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"


clean:
			rm -rf $(OBJS) ./objs
			@printf "%-53b%b" "$(COM_COLOR)OBJECT FILES DELETED:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"


fclean:		clean
				rm $(NAME)
				@printf "%-53b%b" "$(COM_COLOR)ALL CLEAN:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY: 	all clean fclean re

.SILENT: 	clean fclean re all
