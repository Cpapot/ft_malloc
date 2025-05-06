#				______ _ _
#				|  ____(_) |
#				| |__   _| | ___  ___
#				|  __| | | |/ _ \/ __|
#				| |    | | |  __/\__ \.
#				|_|    |_|_|\___||___/

HEADERS		=	malloc.h				\
				str_utils.h

SRCS		=	free.c					\
				malloc.c				\
				realloc.c				\
				malloc_block_utils.c	\
				malloc_utils.c			\
				show_alloc_mem.c		\
				str_utils.c				\
				malloc_debug.c			\
				show_alloc_mem_ex.c		\

#					Directories

UTILSDIR		=	./srcs/utils/

HEADERSDIR		=	./inc/

SRCSDIR			=	./srcs/

LIBFTDIR		=	./libft/

OBJSDIR			=	./.objs/

#					Full Path

HEAD		=	$(addprefix $(HEADERSDIR),$(HEADERS))

SRCSPATH	=	$(addprefix $(SRCSDIR),$(SRCS))

LIBFT		=	$(addprefix $(LIBFTDIR),$(LIBFTSRC))

OBJS		=	$(addprefix $(OBJSDIR), $(SRCSPATH:.c=.o))

#			 __      __        _       _     _
#			 \ \    / /       (_)     | |   | |
#			  \ \  / /_ _ _ __ _  __ _| |__ | | ___  ___
#			   \ \/ / _` | '__| |/ _` | '_ \| |/ _ \/ __|
#			    \  / (_| | |  | | (_| | |_) | |  __/\__ \.
#			     \/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/

define HEADER
"\e[2J\e[H
\033[1;36m
___  ___      _ _
|  \\/  |     | | |
| .  . | __ _| | | ___   ___
| |\\/| |\\/ _ | | |/ _ \\ / __|
| |  | | (_| | | | (_) | (__
\\_|  |_/\\__,_|_|_|\\___/ \\___|
\033[0m
endef
export HEADER

RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
DEFAULT		=	\033[0m
SUPPR		=	\r\033[2K

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so
TEST_NAME	=	malloc_tests
LINK_NAME	=	libft_malloc.so

AR			=	ar rc

CFLAGS		=	-Wall -Wextra -Werror -fPIC -g

CC			=	cc

RM			=	rm -rf

MKDIR		=	mkdir -p

MUTE		:=	1

#				  _____       _
#				 |  __ \     | |
#				 | |__) |   _| | ___  ___
#				 |  _  / | | | |/ _ \/ __|
#				 | | \ \ |_| | |  __/\__ \.
#				 |_|  \_\__,_|_|\___||___/

all : header ${NAME} ${LINK_NAME}

${NAME}: $(OBJS)
ifeq ($(MUTE),1)
	@${CC} -shared ${OBJS} -o ${NAME} -lm
	@echo -n "${SUPPR} ${GREEN}	${NAME} : 🆗${DEFAULT}\n"
else
	${CC} -shared ${OBJS} -o ${NAME} -lm
endif

${LINK_NAME}: ${NAME}
ifeq ($(MUTE),1)
	@ln -sf ${NAME} ${LINK_NAME}
	@echo -n "${SUPPR} ${GREEN}	${LINK_NAME} : 🆗${DEFAULT}\n"
else
	ln -sf ${NAME} ${LINK_NAME}
endif

$(OBJSDIR)%.o: %.c ${HEAD}
	@$(MKDIR) .objs
	@$(MKDIR) $(dir $@)
ifeq ($(MUTE),1)
	@echo -n "${YELLOW}${SUPPR}	⌛ Creating ft_malloc objects : $@"
	@$(CC) ${CFLAGS} -c $< -o $@ -I$(HEADERSDIR)
else
	$(CC) ${CFLAGS} -c $< -o $@ -I$(HEADERSDIR)
endif

clean:
	@${RM} ${OBJS}

fclean:
	@echo "${RED}🗑  ${NAME} cleanded"
	@${RM} ${OBJS}
	@${RM} ${OBJSDIR}
	@${RM} ${NAME}
	@${RM} ${LINK_NAME}
	@${RM} ${TEST_NAME}

reobj:
	rm -rf $(OBJSDIR)
	@${MAKE} --no-print-directory all

header:
	@echo "$$HEADER"

re:
	@${MAKE} --no-print-directory fclean
	@${MAKE} --no-print-directory all

test: all
	@${CC} -g -o ${TEST_NAME} ./test/main.c -L. -lft_malloc -Wl,-rpath=$(PWD)
	@echo "	${GREEN}${TEST_NAME} : 🆗${DEFAULT}"

.PHONY : re all clean fclean printf lib header reobj
