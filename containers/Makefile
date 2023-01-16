# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 12:59:32 by mel-amma          #+#    #+#              #
#    Updated: 2023/01/16 16:54:29 by mel-amma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Vec

NAME2 = Set

NAME3 = Map

NAME4 = Stack

SRCS = mains/vector_main.cpp
SRCS_SET = mains/set_main.cpp
SRCS_MAP = mains/map_main.cpp
SRCS_STACK = mains/stack_main.cpp
HEADERS = trees/avl_tree.hpp utils/compare.hpp utils/enable_if.hpp utils/is_integral.hpp utils/iterator_traits.hpp iterators/map_iterator.hpp\
			containers/map.hpp utils/pair.hpp  trees/red_black.hpp iterators/reverse_iterator_.hpp iterators/set_iterator.hpp\
			containers/set.hpp containers/stack.hpp iterators/vector_iterators.hpp containers/vector.hpp

OBJS = ${SRCS:.cpp=.o}
OBJS_SET = ${SRCS_SET:.cpp=.o}
OBJS_MAP = ${SRCS_MAP:.cpp=.o}
OBJS_STACK = ${SRCS_STACK:.cpp=.o}

CC = c++

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98

SANITIZE = -fsanitize=address


all: vector


vector: Vec 

Vec : $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SANITIZE) $(SRCS) -o $(NAME)

set: Set

Set : $(SRCS_SET) $(HEADERS)
	$(CC) $(CFLAGS) $(SANITIZE) $(SRCS_SET) -o $(NAME2)


stack: Stack

Stack : $(SRCS_STACK) $(HEADERS)
	$(CC) $(CFLAGS) $(SANITIZE) $(SRCS_STACK) -o $(NAME4)

map: Map
	
Map : $(SRCS_MAP) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS_MAP) -o $(NAME3)


clean:
	$(RM) $(NAME) $(NAME2) $(NAME3) $(NAME4)

fclean: clean
	$(RM) $(NAME) $(NAME2) $(NAME3) $(NAME4)

re: fclean all

.PHONY: all vector set map stack clean fclean re
