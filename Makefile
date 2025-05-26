##
## EPITECH PROJECT, 2025
## raytracer
## File description:
## Makefile
##

SRCDIR_serveur = src/serveur
SRCDIR_client = src/client
SRCDIR_ai = src/ai

SRC_serv = $(shell find $(SRCDIR_serveur) -name '*.c')
SRC_client = $(shell find $(SRCDIR_client) -name '*.cpp')
SRC_ai = $(shell find $(SRCDIR_ai) -name '*.cpp')


OBJ_serv = $(SRC_serv:$(SRCDIR_server)/%.c=obj/%.o)
OBJ_client = $(SRC_client:$(SRCDIR_client)/%.cpp=obj/%.o)
OBJ_ai = $(SRC_ai:$(SRCDIR_ai)/%.cpp=obj/%.o)

BINARY_serv = zappy_server
BINARY_client = zappy_gui
BINARY_ai = zappy_ai

DEBUG_FLAGS += -Wall -Wextra -pedantic -g


all: $(BINARY_serv) $(BINARY_client)

$(BINARY_serv): $(OBJ_serv)
	gcc -o $@ $^  $(DEBUG_FLAGS)

$(BINARY_client): $(OBJ_client)
	gcc -o $@ $^  $(DEBUG_FLAGS)

obj/%.o: $(SRCDIR_server)/%.c
	mkdir -p $(dir $@)
	gcc -c $< -o $@  $(DEBUG_FLAGS)

obj/%.o: $(SRCDIR_client)/%.cpp
	mkdir -p $(dir $@)
	g++ -c $< -o $@  $(DEBUG_FLAGS)

clean:
	rm -rf obj

fclean: clean
	rm -f $(BINARY_serv) $(BINARY_client) $(BINARY_ai)

re: fclean all

.PHONY: all clean fclean re
