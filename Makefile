#*******************************  VARIABLES  **********************************#

NAME			=	2048

# --------------- FILES --------------- #

include src.mk

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_INCLUDES 	=	\
					$(DIR_INCLUDE)

# ------------- SHORTCUTS ------------- #

OBJ				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEP				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
SRC				=	$(addprefix $(DIR_SRC),$(LIST_SRC))
INCLUDES		=	$(addprefix -I , $(DIR_INCLUDES))

# ------------ COMPILATION ------------ #

CFLAGS			=	-Wall -Wextra -Werror
DEBUG_CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3

DEP_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p
OS				=	$(shell uname -s)


#***********************************  RULES  **********************************#

.PHONY: all
all:			$(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -lncurses

# ---------- COMPILED RULES ----------- #

-include $(DEP)

$(DIR_BUILD)%.o: %.c
				mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) $(DEP_FLAGS) $(INCLUDES) -c $< -o $@

.PHONY: run
run:	all
				./$(NAME)

.PHONY: clean
clean:
				$(RM) $(DIR_BUILD)

.PHONY: fclean
fclean: clean
				$(RM) $(NAME)

.PHONY: re
re:				fclean
				$(MAKE) all

.PHONY: debug
debug:	fclean
				$(MAKE) all CFLAGS="$(DEBUG_CFLAGS)"

.PHONY: check-format
check-format:
				clang-format -style=file $(SRC) -n --Werror

.PHONY: format
format:
				clang-format -style=file $(SRC) -i
