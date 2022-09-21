NAME1 = ft_prog
NAME2 = std_prog

TIME_PROG1 = ft_time
TIME_PROG2 = std_time

SRCS =	tests/main_test.cpp

INC = ""

CXX = c++

CXXFLAGS = -std=c++98 -Wall -Werror -Wextra -g

STD_FLAG = STD

MAIN_INTRA = main_intra.cpp

all:
	@$(MAKE)  $(NAME2) $(NAME1)

$(NAME1):
	${CXX} $(CXXFLAGS) ${SRCS} -o $(NAME1) 
	@echo "\033[0;32m=> $(NAME1) created ! <=\033[0m"
$(NAME2):
	${CXX} $(CXXFLAGS) ${SRCS} -D ${STD_FLAG}  -o $(NAME2) 
	@echo "\033[0;32m=> $(NAME2) created ! <=\033[0m"

clean:

fclean:
	@rm -rf $(NAME1) $(NAME2) $(TIME_PROG1) $(TIME_PROG2)
	@echo "\033[0;31m=> $(NAME1) deleted <=\033[0m"
	@echo "\033[0;31m=> $(NAME2) deleted <=\033[0m"

re: fclean all

compile_time_prog:
	${CXX} ${MAIN_INTRA} -o $(TIME_PROG1)
	${CXX} ${MAIN_INTRA} -D ${STD_FLAG} -o $(TIME_PROG2)

.PHONY: all, clean, fclean, re