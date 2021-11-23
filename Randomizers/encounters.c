#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include "../42-libft/libft.h"

/* 
* Removes new lines from the text.
*/
char *strip_nl(char *line)
{
	int i = 0;
	int len = ft_strlen(line);
	char *ret;

	while (i < len)
	{
		if (line[i] == '\n') return "1";
		i++;
	}

	return line;
}

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
* Converts the input to a line.
*/
char *convert_to_line(int n, char **input)
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
char *is_monsno(char *line, char **encount, int index)
{
	int i = 0;
	int j = 0;

	char *tmp, *space, **tab;
	tab = ft_split(line, ' ');

	while (tab[i])
	{
		// Analyzes whether we are in a monsno line.
		if (ft_strncmp(tab[i], "monsNo", ft_strlen("monsNo")) == 0)
		{
			// Checks if the value associated is NOT 0, which guarantees no write to unwanted lines.
			if (ft_strncmp(tab[i + 2], "0", ft_strlen("0")) != 0)
			{
				int num = pick_mon();
				tab[i + 2] = ft_itoa(num);
				printf("%d\n", num); // TODO: debug, remove.

				// Gets the tab's size.
				while(tab[j]) j++;

				space = ft_strnstr(encount[index - 1], "Sheetlegendpoke", ft_strlen(encount[index - 1])) != NULL ? "     " : "         ";

				return ft_strjoin(space, convert_to_line(j, tab));
			}
		}

		i++;
	}

	return line;
}

/* 
** Main code.
*/
int main(int argc, char* argv[])
{
	/* -------- VARIABLES DEFINITION -------- */


    char const* const fileName = argv[1];
	char const *newfile = ft_strjoin(argv[1], "_randomised");

	FILE* file;
	FILE *new;

	char *buffer;
	char *temp;

	char **tab = NULL;
	char **encount_tables;

    char line[256];

	int i = 0;
	long lSize;


	/* ---------------- CODE ---------------- */


	srand((unsigned int)time(NULL)); // Sets a random seed.

	// Opens both needed files.
	file = fopen(fileName, "rb");
	new = fopen(newfile, "w");

	// Gets the file size.
	fseek(file, 0L, SEEK_END);
	lSize = ftell(file);
	rewind(file);

	// Allocates the memory.
	printf("Allocating mem...\n"); // TODO: debug, remove.
	buffer = calloc(1, lSize +1);
	if(!buffer) fclose(file), fputs("memory alloc fails", stderr), exit(1);

	// Copies the file into the buffer.
	printf("Reading encounter table...\n");
	if(1 != fread(buffer , lSize, 1 , file)) fclose(file), free(buffer), fputs("entire read fails", stderr), exit(1);

	//Splits the buffer into multiple lines, for better parsing.
	encount_tables = ft_split(buffer, '\n');

	printf("We're in boys\n"); // TODO: debug, remove.
	
    while (encount_tables[i])
	{
		// Regular encounters use 'monsNo', whilst safari encounters use 'MonsNo'.
		if (ft_strnstr(encount_tables[i], "monsNo", ft_strlen(encount_tables[i])) != NULL || ft_strnstr(encount_tables[i], "MonsNo", ft_strlen(encount_tables[i])) != NULL)
			temp = is_monsno(encount_tables[i], encount_tables, i);
		else
			temp = ft_strdup(encount_tables[i]);

		printf("%s\n", temp); // TODO: debug, remove.
		
		fputs(temp, new);
		fputs("\n", new);
		free(temp);

		i++;
	}

	i = 0;
	free(encount_tables);
  fclose(file);
	fclose(new);

    return 0;
}