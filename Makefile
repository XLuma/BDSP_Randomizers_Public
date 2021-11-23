encounter_src = Randomizers/encounters.c
trainers_src = Randomizers/trainers.c
abilities_src = Randomizers/abilities.c
tm_src = Randomizers/tm.c

encounters = encounters
trainers = trainers
abilities = abilities
tm = tm

LIBFT = 42-libft/libft.a

CC = gcc

all: $(encounters) $(trainers) $(abilities) $(tm)	

$(encounters):
	$(MAKE) -C ./42-libft
	gcc $(encounter_src) $(LIBFT) -o Randomizers/encounters

$(trainers):
	$(MAKE) -C ./42-libft
	gcc $(trainers_src) $(LIBFT) -o Randomizers/trainers

$(abilities):
	$(MAKE) -C ./42-libft
	gcc $(abilities_src) $(LIBFT) -o Randomizers/abilities

$(tm):
	$(MAKE) -C ./42-libft
	gcc $(tm_src) $(LIBFT) -o Randomizers/tm

clean:
	$(MAKE) clean -C ./42-libft

fclean: clean
	rm -f ./Randomizers/encounters
	rm -f ./Randomizers/trainers
	rm -f ./Randomizers/tm
	rm -f ./Randomizers/abilities

re: fclean all

.PHONY: trainers encounters abilities tm all
