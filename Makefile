##
## EPITECH PROJECT, 2022
## ASM
## File description:
## Makefile
##

AS       = nasm
ASFLAGS  = -f elf64 -g

CC       = ld
CFLAGS   = -fPIC -shared

RM       = rm -f
NAME     = libasm.so

SRCS_DIR    = src/
SRCS_FILES  = \
	strlen.asm        \
	strcmp.asm        \
	strncmp.asm       \
	strcasecmp.asm    \
	strchr.asm        \
	strstr.asm        \
	strcspn.asm       \
	strpbrk.asm       \
	strrchr.asm        \
	memset.asm        \
	memcpy.asm        \
	memmove.asm       \
	bonus_memfrob.asm \
	bonus_ffs.asm	 \

SRCS        = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS        = $(SRCS:.asm=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

tests_run: re $(NAME)
	cd tests && gcc main.c tests.c -ldl -Wall -Wextra && ./a.out

.PHONY:	all clean fclean re
