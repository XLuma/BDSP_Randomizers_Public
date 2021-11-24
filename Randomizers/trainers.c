#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include "../42-libft/libft.h"
#include "../Resources/pokemon.h"

int new_mon;

/* 
* Picks a random Pokemon.
*/
int	pick_mon()
{
	int min = 1;
	int max = 493;
	return rand() % ((max + 1) - min) + min;
}

/* 
* Picks a random move.
*/
int pick_move(int min, int max)
{
    return rand() % ((max + 1) - min) + min;
}

/* 
* Converts the input to a line.
*/
char *convertToLine(int n, char **input)
{
	int size = 0;

	// Computes the needed size.
	for (int i = 0; i != n; ++i)
	size += strlen(input[i]) + 1;
	
	char * string = (char*)malloc(size); // sizeof(char) is 1 by definition.
	char * p = string;

	// Copies the strings.
	for (int i = 0; i != n; ++i) 
	{
		strcpy(p, input[i]);
		p += strlen(p);
		*p++ = ' ';
	}

	p[-1] = 0;

	return string;
}

/* 
* Returns a mon number if in the monsno line.
*/
char *is_monsno(char *line)
{
	int i = 0;
	int j = 0;

	char *tmp, **tab;
	tab = ft_split(line, ' ');

	while (tab[i])
	{
        // Analyzes whether we are in a monsno line.
		if (ft_strncmp(tab[i], "MonsNo", ft_strlen("MonsNo")) == 0)
		{
			// Checks if the value associated is NOT 0, which guarantees no write to unwanted lines.
			if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
			{
                int num = pick_mon();
                new_mon = num;
				tab[i + 2] = ft_itoa(num);

                // Gets the tab size.
				while(tab[j]) j++;

				return ft_strjoin("     ", convertToLine(j, tab));
			}
		}

		i++;
	}

	return line;
}

/* 
* Fixes alternate forms' numbers.
*/
char *fix_formno(char *line)
{
	int i = 0;
	int j = 0;

	char *tmp, **tab;
	tab = ft_split(line, ' ');

	while (tab[i])
	{
	    // Analyze whether we are in a formno line.
		if (ft_strnstr(tab[i], "FormNo", ft_strlen(tab[i])) != NULL)
		{
			// Checks if the value associated is NOT 0, which guarantees no write to unwanted lines.
			if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
			{
				int num = 0;
				tab[i + 2] = ft_itoa(num);
				
                // Gets the tab size.
				while(tab[j]) j++;

				return ft_strjoin("     ", convertToLine(j, tab));
			}
		}

		i++;
	}

	return line;   
}

/* 
* Finds a mon by name.
*/
char *find_mon(char **names)
{
    return (names[new_mon]);
}

/* 
* Resolves a move's ID by its number.
*/
int resolve_move(int move, char **moveList, char *line)
{
    int i = 0;
    char **tab = ft_split(line, '@');

    while (moveList[i])
    {
        if (strcmp(ft_strjoin(moveList[i], " "), tab[0]) == 0) return i;
        i++;
    }

    return 0;
}

/* 
* Returns a new move.
*/
char *new_move(char *line, char **learnset, char **names, char **movelist)
{
    int i = 0;
    int j = 0;
    int len = 0;
    int move_index;

    char **tab = ft_split(line, ' ');
    char *mon;

    while (tab[i])
    {
        if (ft_strnstr(tab[i], "Waza", ft_strlen(tab[i])) != NULL)
        {
            // Checks if the move isn't empty.
            if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
            {
                mon = find_mon(names);

                while (learnset[j])
                {
                    if (ft_strnstr(learnset[j], mon, ft_strlen(learnset[j])) != NULL)
                    {
                        int current = j;
                        int max = 0;
                        int move;

                        while (ft_strnstr(learnset[current], "end", ft_strlen(learnset[current])) == NULL)
                        {
                            current++;
                            max++;
                        }

                        // Picks a random move.
                        move = pick_move(1, max);
                        move_index = resolve_move(move, movelist, learnset[j + move]);

                        tab[i + 2] = ft_itoa(move_index);
                        while(tab[len]) len++;

			        	return (ft_strjoin("     ", convertToLine(len, tab)));
                    }

                    j++;
                }
            }
        }

        i++;
    }

    return line;
}

int main(int argc, char **argv)
{
    /* -------- VARIABLES DEFINITION -------- */


    char const* const fileName = argv[1];

    char const *movepoolFile = "Resources/learnsets.txt";
    char const *monName = "Resources/pokemon.txt";
    char const *moveName = "Resources/movelist.txt";
    char const *newfile = ft_strjoin(argv[1], "_randomised");

    FILE* file;
    FILE *movepool, *new, *monFile, *moveFile;

	char *buffer;
	char **trTab = NULL;
	char **movepoolTab, **monTab, **moveTab;
	
	int i = 0;
    int j = 1;

    long lSize, trSize, monSize, moveSize;
    

    /* ------------ FILE READING ------------ */


    new_mon = 0; // Resets the mon number.
	srand((unsigned int)time(NULL)); // Sets a random seed.

    // Opens all the needed files.
	file = fopen(fileName, "rb");
    monFile = fopen(monName, "rb");
    movepool = fopen(movepoolFile, "rb");
    moveFile = fopen(moveName, "rb");
	new = fopen(newfile, "w");

    // Gets the sizes of all relevant files.
	fseek(movepool, 0L, SEEK_END);
    fseek(file, 0L, SEEK_END);
    fseek(monFile, 0L, SEEK_END);
    fseek(moveFile, 0L, SEEK_END);
	lSize = ftell(movepool);
    trSize = ftell(file);
    monSize = ftell(monFile);
    moveSize = ftell(moveFile);
	rewind(movepool);
    rewind(file);
    rewind(monFile);
    rewind(moveFile);

	// Allocates the memory.
	printf("Allocating mem for movepool...\n"); // TODO: debug, remove.
    trTab = (char **)malloc((trSize * sizeof(char*)) + 1);

    // This is for the movepool file.
	buffer = malloc(lSize + 1);
	if(!buffer) fclose(file), fputs("memory alloc fails", stderr), exit(1);

	printf("Reading moveset table\n"); // TODO: debug, remove.
	if(1 != fread(buffer, lSize, 1, movepool)) fclose(file), free(buffer), fputs("entire read fails",stderr), exit(1);

    // Splits the buffer into multiple lines, for better parsing.
    movepoolTab = ft_split(buffer, '\n');
    free (buffer);

    // This is for the Pokemon file.
    buffer = malloc(monSize + 1);
    printf("Reading Pokemon table\n"); // TODO: debug, remove.
	if(1 != fread(buffer, monSize, 1, monFile)) fclose(file), free(buffer), fputs("entire read fails", stderr), exit(1);
    
    monTab = ft_split(buffer, '\n');
    free(buffer);

    // This is for the movelist file.
    buffer = malloc(moveSize + 1);
    printf("Reading movelist table\n"); // TODO: debug, remove.
	if(1 != fread(buffer, moveSize, 1, moveFile)) fclose(file), free(buffer), fputs("entire read fails", stderr), exit(1);
    
    moveTab = ft_split(buffer, '\n');
    free(buffer);

    // This is for the trainer file.
    char *line = NULL;
    long lenght;
    printf("Reading trainer table\n");
    while (!feof(file))
    {
        getline(&line, &lenght, file);
        trTab[i] = ft_strdup(line);
        i++;
    }

    
    /* ------------- RANDOMISING ------------ */


    printf("Randomising...\n"); // TODO: debug, remove.

    char *temp = NULL;
    i = 0;

    while (trTab[i])
    {
        if (ft_strnstr(trTab[i], "MonsNo", ft_strlen(trTab[i])) != NULL) // MonsNo line.
        {
            temp = is_monsno(trTab[i]);

            fputs(temp, new);
            if (ft_strnstr(temp, "\n", ft_strlen(temp)) == NULL) fputc('\n', new);

            i++;
        }
        else if (ft_strnstr(trTab[i], "FormNo", ft_strlen(trTab[i])) != NULL) // FormsNo line.
        {
            temp = fix_formno(trTab[i]);

            fputs(temp, new);
            if (ft_strnstr(temp, "\n", ft_strlen(temp)) == NULL) fputc('\n', new);

            i++;
        }
        else if (ft_strnstr(trTab[i], "Waza", ft_strlen(trTab[i])) != NULL) // Waza line.
        {
            
            char **tab_waza = calloc(5, sizeof(char *));

            int counter = 0;
            int current = i;

            while (ft_strnstr(trTab[current], "Waza", ft_strlen(trTab[current])) != NULL && counter < 4)
            {
                tab_waza[counter] = ft_strdup(trTab[current]);
                counter++;
                current++;
            }

            counter = 0;

            while (tab_waza[counter] && counter < 4)
            {
                tab_waza[counter] = new_move(tab_waza[counter], movepoolTab, monTab, moveTab);
                counter++;
            }

            counter = 0;

            while (tab_waza[counter] && counter < 4)
            {
                fputs(tab_waza[counter], new);
                if (ft_strnstr(tab_waza[counter], "\n", ft_strlen(tab_waza[counter])) == NULL) fputc('\n', new);
                counter++;
            }

            free(tab_waza);

            while (ft_strnstr(trTab[i], "Waza", ft_strlen(trTab[i])) != NULL) i++;
        }
		else // Other lines.
        {
            fputs(ft_strdup(trTab[i]), new);
            i++;
        }
    }

    // Closes all the files.
    fclose (file);
    fclose (movepool);
    fclose (new);
    fclose (moveFile);
    fclose (monFile);

    return 0;
}

