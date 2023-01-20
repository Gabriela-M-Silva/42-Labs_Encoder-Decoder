# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 18:07:45 by gde-mora          #+#    #+#              #
#    Updated: 2023/01/20 14:27:07 by gde-mora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ENCODER = encoder

SRC_ENCODER = ./encoder_src/encoder.c ./encoder_src/read_argv.c ./encoder_src/get_frequency.c \
		./encoder_src/create_list.c ./encoder_src/create_tree.c ./encoder_src/create_dictionary.c \
		./encoder_src/compress_code.c ./encoder_src/mem_share.c

OBJ_ENCODER = $(SRC_ENCODER:.c=.o)

NAME_DECODER = decoder

SRC_DECODER = ./decoder_src/decoder.c ./decoder_src/rebuild_tree.c ./decoder_src/create_list.c \
		./decoder_src/create_tree.c ./decoder_src/descompress_code.c \

OBJ_DECODER = $(SRC_DECODER:.c=.o)

# MAKEFILE UTILS
LIBFT_A = ./libft/libft.a

HEADER_ENCODER = ./encoder_src/encoder.h

HEADER_DECODER = ./decoder_src/decoder.h

CCFLAGS = -Wall -Wextra -Werror

RM = rm -f

# RULES
all: $(NAME_ENCODER) $(NAME_DECODER)

.c.o:
	cc $(CCFLAGS) -c $< -o $(<:.c=.o) 

# LIBFT COMPILE
$(LIBFT_A):
	make -C libft

# MANDATORY COMPILE
$(NAME_ENCODER): $(OBJ_ENCODER) $(HEADER_ENCODER) $(LIBFT_A)
	cc $(CCFLAGS) -o $(NAME_ENCODER) $(OBJ_ENCODER) $(LIBFT_A)

$(NAME_DECODER): $(OBJ_DECODER) $(HEADER_DECODER) $(LIBFT_A)
	cc $(CCFLAGS) -o $(NAME_DECODER) $(OBJ_DECODER) $(LIBFT_A)

# RULES CLEAN FCLEAN AND RE
clean:
	$(RM) $(OBJ_ENCODER) $(OBJ_DECODER)
	make clean -C libft

fclean: clean
	$(RM) $(NAME_ENCODER) $(NAME_DECODER)
	$(RM) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re