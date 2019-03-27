FLAG = -Wall -Wextra -Werror
NAME = libftprintf.a

SRC_PF = create_pr_data.c float_flags.c ft_cast_va_list.c ft_flags.c            \
            ft_flags_manipulation.c ft_format.c ft_pr_data_num.c ft_precision.c \
            ft_printf.c ft_start_parse.c ft_str_vector.c ftoa.c                 \
            impressiv_data_macker.c itoa_base.c long_arithmetic.c starbax.c

SRC_LFT = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c \
            ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lstpushback.c ft_lstrev.c ft_makestr.c \
            ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c       \
            ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c          \
            ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c        \
            ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c     \
            ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c   \
            ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_vstrdel.c ft_vstrpb.c

OBJET_PF = $(SRC_PF:.c=.o)
OBJET_LFT = $(SRC_LFT:.c=.o)

LIBFT_PATH = libft
LIB = $(addprefix $(LIBFT_PATH)/, $(OBJET_LFT))

all: $(NAME)
$(NAME): $(OBJET_PF) $(SRC_PF) $(LIB)
	@make -C $(LIBFT_PATH)
	@echo Compiling $(NAME)
	@gcc -Wall -Wextra -Werror -c $(SRC_PF)
	@ar rc  $(NAME) $(OBJET_PF) $(LIB)
	@echo ======[Done]======

%.o : %.c
	@echo "$(NAME) >>> Add/Update $^"

clean:
	@make -C $(LIBFT_PATH) clean
	@echo Clean objects $(NAME)
	@rm -rf $(OBJET_PF)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@echo Clean $(NAME)
	@rm -rf $(NAME)
	@echo ======[Clean]======
re: fclean all
