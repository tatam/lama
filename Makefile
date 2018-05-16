##
## Makefile
## 
## Made by Tatam
## Login   <tatam@protonmail.com>
## 
## Started on  Wed Sep 28 08:37:33 2016 Tatam
## Last update Wed May 16 21:16:51 2018 Tatam
##
CC =	gcc
NAME =	lama
MAN =	man/lama.man
SRC =	src/main.c \
	src/lama_builtin.c \
	src/lama_arg.c \
	src/lama_file.c \
	src/lama_permutation.c \
	src/lama_print.c \
	src/lama_calculator.c \
	src/lama_count.c \
	src/lama_len.c \
	src/lama_convert.c \
	src/lama_alter.c \
	src/lama_split.c \
	src/lama_init_array.c

BIN_D	= /usr/bin
MAN_D	= /usr/share/man/man1
OBJ	= $(SRC:%.c=%.o)
BAK     = *~
CFLAGS	= -W -Wall -Werror
ECHO	= /bin/echo
MKDIR	= /bin/mkdir
RM	= /bin/rm -f
CP	= /bin/cp
USER	= `whoami`

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
		$(RM) $(OBJ)
		$(RM) $(BAK)
		$(RM) */$(BAK)

fclean:		clean
		$(RM) $(NAME)

install:	
		@if [ $(USER) != "root" ]; then	\
			$(ECHO) "Make install need to be root." 1>&2; \
			exit 1; \
		fi
		$(CP) $(NAME) $(BIN_D)
		$(CP) $(MAN) $(MAN_D)/$(NAME).1
		@if ! [ -d /etc/$(NAME) ]; then \
			$(MKDIR) /etc/$(NAME); \
			$(CP) cfg/* /etc/$(NAME); \
		fi

uninstall:
		@if [ $(USER) != "root" ]; then	\
			$(ECHO) "Make uninstall need to be root." 1>&2; \
			exit 1; \
		fi
		$(RM) $(BIN_D)/$(NAME)
		$(RM) $(MAN_D)/$(NAME).1
		$(RM) -R /etc/$(NAME)

re:		uninstall fclean all

all:		$(NAME) install
