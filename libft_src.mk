

LIBFT_MANDATORY_SRC = $(LIBFT_DIR)/ft_isalpha.c\
				$(LIBFT_DIR)/ft_isdigit.c\
				$(LIBFT_DIR)/ft_isalnum.c\
				$(LIBFT_DIR)/ft_isascii.c\
				$(LIBFT_DIR)/ft_isprint.c\
				$(LIBFT_DIR)/ft_strlen.c\
				$(LIBFT_DIR)/ft_memset.c\
				$(LIBFT_DIR)/ft_bzero.c\
				$(LIBFT_DIR)/ft_memcpy.c\
				$(LIBFT_DIR)/ft_memmove.c\
				$(LIBFT_DIR)/ft_strlcpy.c\
				$(LIBFT_DIR)/ft_strlcat.c\
				$(LIBFT_DIR)/ft_toupper.c\
				$(LIBFT_DIR)/ft_tolower.c\
				$(LIBFT_DIR)/ft_strchr.c\
				$(LIBFT_DIR)/ft_strrchr.c\
				$(LIBFT_DIR)/ft_strncmp.c\
				$(LIBFT_DIR)/ft_memchr.c\
				$(LIBFT_DIR)/ft_memcmp.c\
				$(LIBFT_DIR)/ft_strnstr.c\
				$(LIBFT_DIR)/ft_atoi.c\
				$(LIBFT_DIR)/ft_calloc.c\
				$(LIBFT_DIR)/ft_strdup.c\
				$(LIBFT_DIR)/ft_substr.c\
				$(LIBFT_DIR)/ft_strjoin.c\
				$(LIBFT_DIR)/ft_strtrim.c\
				$(LIBFT_DIR)/ft_split.c\
				$(LIBFT_DIR)/ft_strcmp.c \
				$(LIBFT_DIR)/ft_itoa.c\
				$(LIBFT_DIR)/ft_strmapi.c\
				$(LIBFT_DIR)/ft_striteri.c\
				$(LIBFT_DIR)/ft_putchar_fd.c\
				$(LIBFT_DIR)/ft_putstr_fd.c\
				$(LIBFT_DIR)/ft_putendl_fd.c\
				$(LIBFT_DIR)/ft_putnbr_fd.c\
				$(LIBFT_DIR)/get_next_line.c\
				$(LIBFT_DIR)/get_next_line_utils.c\
				$(LIBFT_DIR)/ft_printf.c \
				$(LIBFT_DIR)/ft_decimal_to_hex.c \
				$(LIBFT_DIR)/ft_puthex.c \
				$(LIBFT_DIR)/ft_putnbr.c \
				$(LIBFT_DIR)/ft_putubr.c \
				$(LIBFT_DIR)/ft_safe_write.c \
				$(LIBFT_DIR)/handle_char.c \
				$(LIBFT_DIR)/handle_format.c \
				$(LIBFT_DIR)/handle_hex.c \
				$(LIBFT_DIR)/handle_integer.c \
				$(LIBFT_DIR)/handle_percent.c \
				$(LIBFT_DIR)/handle_pointer.c \
				$(LIBFT_DIR)/handle_string.c \
				$(LIBFT_DIR)/handle_unsigned.c 
				

LIBFT_OFILES = $(LIBFT_MANDATORY_SRC:.c=.o)