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

char *convertToLine(int n, char **input) {
  /* compute the needed size,
     of course can also use malloc then realloc to avoid that */
  int size = 0;
  int i;

  for (i = 0; i != n; ++i)
    size += strlen(input[i]) + 1;

  /* copy the strings */
  char * string = (char*)malloc(size); /* sizeof(char) is 1 by definition */
  char * p = string;

  for (i = 0; i != n; ++i) 
  {
	  strcpy(p, input[i]);
	  p += strlen(p);
	  *p++ = ' ';
  }
  p[-1] = 0;

  return string;
}

int	check_index(char **index, int move)
{
	int	i;
	int tmp;

	tmp = 0;
	i = 0;
	while (index[i])
	{
		tmp = ft_atoi(index[i]);
		if (tmp == move)
			return 0;
		i++;
	}
	return (1);
}

int pick_move(int min, int max, char **index)
{
	int move;
	int i;
	i = 0;
    move = rand()%((max+1)-min) + min;
	while (check_index(index, move) != 0)
	{
		move = rand()%((max+1)-min) + min;
	}
	return (move);
}

char *new_move(char *line, char **index, long index_size)
{
	int	i;
	int	j;
	int move;
	char *tmp;
	char **tab;

	tab = ft_split(line, ' ');
	i = 0;
	j = 0;
	move = 0;

	while (tab[i])
	{
		if (ft_strnstr(tab[i], "wazaNo", ft_strlen(tab[i])) != NULL)
		{
			if (ft_strnstr(tab[i + 2], "0", ft_strlen(tab[i+2])) == NULL)
			{
				move = pick_move(1, index_size, index);
				tab[i + 2] = ft_itoa(move);
				while (tab[j])
					j++;
				tmp = convertToLine(j, tab);
				tmp = ft_strjoin("     ", tmp);
				return (tmp);
			}
		}
		i++;
	}
	return (line);
}

int	main(int argc, char **argv)
{
	char const *filename = argv[1];
	char const *bdsp_index_file = "Resources/bdsp_move_index.txt";
	char const *newfile = ft_strjoin(argv[1], "randomised_");

	FILE *file;
	FILE *bdsp_index;
	FILE *new;

	char *buffer;

	char **indexTab;
	char **itemTab;

	long fileSize;
	long indexSize;

	int i;
	int j;

	srand((unsigned int)time(NULL)); //set random seed

	file = fopen(filename, "rb");
	bdsp_index = fopen(bdsp_index_file, "rb");
	new = fopen(newfile, "w");
	fseek(file, 0L, SEEK_END);
	fseek(bdsp_index, 0L, SEEK_END);
	fileSize = ftell(file);
	indexSize = ftell(bdsp_index);
	rewind(file);
	rewind(bdsp_index);

	printf("Reading BDSP used move indexes\n");
	buffer = malloc(indexSize + 1);
	if( !buffer ) fclose(bdsp_index),fputs("memory alloc fails",stderr),exit(1);
	if( 1!=fread( buffer , indexSize, 1, bdsp_index) )
  		fclose(bdsp_index),free(buffer),fputs("entire read fails",stderr),exit(1);

	indexTab = ft_split(buffer, '\n');
	free(buffer);

	printf("Reading Item table\n");
	unsigned long lenght;
	i = 0;
	itemTab = (char **)malloc((fileSize * sizeof(char*)) + 1); //also allocating for trtab
	buffer = NULL;
	while (!feof(file))
    {
        getline(&buffer, &lenght, file);
        itemTab[i] = ft_strdup(buffer);
        i++;
    }

	printf("Randomizing TM's\n");
	char *temp = NULL;
	i = 0;
	while (itemTab[i])
	{
		if (ft_strnstr(itemTab[i], "wazaNo", ft_strlen(itemTab[i])) != NULL)
		{
			temp = new_move(itemTab[i], indexTab, indexSize);
			fputs(temp, new);
			if (ft_strnstr(temp, "\n", ft_strlen(temp)) == NULL)
                fputc('\n', new);
			i++;
		}
		else
		{
			temp = ft_strdup(itemTab[i]);
            fputs(temp, new);
			i++;
		}
	}
	fclose(file);
	fclose(new);
	fclose(bdsp_index);
	free(itemTab);
	free(indexTab);
	return 0;
}