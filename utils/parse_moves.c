#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "42-libft/libft.h"

char	*remove_comma(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
		{
			line[i] = '\0';
		}
		i++;
	}
	return (line);
}

int main(void)
{
	char const *filename = "moves.txt";
	char const *newfile = "moves_parsed.txt";
	FILE *sym;
	FILE *txt;
	char	*buffer;
	char **sym_array;
	char **move_array;
	char **line;
	char	*current_line;
	long lSize;
	int	i;
	int j;

	i = 0;
	//stolen from stack overflow
	sym = fopen(filename, "rb");
	txt = fopen(newfile, "w");
	fseek( sym , 0L , SEEK_END);
	lSize = ftell(sym);
	rewind(sym);

	if (txt == NULL)
		return (1);
	printf("Allocating mem\n");
	buffer = calloc( 1, lSize+1 );
	if( !buffer ) fclose(sym),fputs("memory alloc fails",stderr),exit(1);

	/* copy the file into the buffer */
	printf("Reading file into mem\n");
	if( 1!=fread( buffer , lSize, 1 , sym) )
  		fclose(sym),free(buffer),fputs("entire read fails",stderr),exit(1);

	//printf("%s\n", buffer);
	//Split string into multiple substrings. Long time to process, cant make it quicker im already using syscalls
	sym_array = ft_split(buffer, '\n');
	free(buffer); //dont need it anymore
	printf("We're in boys\n");
	j = 0;
	/*
		Multiple solutions here. I think the best one is to get counter J, increment each time we find a num value so we get a good array.
		We now have an array of the size of every move.
		Rewind the file, reset J counter 
	*/
	while (sym_array[i])
	{
		if (ft_strnstr(sym_array[i], "num", ft_strlen(sym_array[i])) != NULL) //only if the array contains MapWarps, we take the address and output to a txt file
		{
			j++;
		}
		i++;
	}
	printf("Got whole array size: %d\n", j);
	sleep(1);
	i = 0;
	move_array = (char **)malloc(j * sizeof(char*));
	j = 0;
	j++;
	//Now, each time we find a num, we find the name associated together, check if the space array is not empty, and copy the name
	printf("Finding names for array\n");
	while(sym_array[i])
	{
		if (ft_strnstr(sym_array[i], "num", ft_strlen(sym_array[i])) != NULL) //only if the array contains num, we continue
		{
			//split line, convert number to int
			line = ft_split(sym_array[i], ' ');
			int index = ft_atoi(remove_comma(line[1]));
			int	limit = i;
			while (limit < (i + 20))
			{
				//try to find the next name field, split, remove comma, assign to correct index
				if (ft_strnstr(sym_array[limit], "name", ft_strlen(sym_array[limit])) != NULL)
				{
					if (ft_strchr(sym_array[limit], '"') != NULL)
					{
						printf("Got a name!\n");
						line = ft_split(sym_array[limit], '"');
						move_array[index] = ft_strdup(remove_comma(line[1]));
						printf("%d %s\n", index, move_array[index]);
						limit += 20;
					}
				}
				limit++;
			}
		}
		i++;
	}
	printf("Parsed all names, outputting\n");
	free(line);
	i = 0;
	while (move_array[i])
	{
		printf("%s\n", move_array[i]);
		fputs(move_array[i], txt);
		fputs("\n", txt);
		i++;
	}
	//free all the mem
	i = 0;
	free(move_array);
	free(sym_array);
	fclose(sym);
	fclose(txt);
	return (0);
}