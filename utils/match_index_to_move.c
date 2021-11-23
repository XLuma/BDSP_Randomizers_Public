#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "../42-libft/libft.h"

int main(int argc, char **argv)
{
	char const *filename = argv[1];
	char const *newfile = ft_strjoin(argv[1], "_convert.txt");
	FILE *move;
	FILE *new;
	char *buffer;
	char *buffer2;
	char **move_array;
	char **tmp_array = NULL;
	char *line;
	long lSize;
	long lSize2;
	int i;
	int j;

	new = fopen(newfile, "w");
	move = fopen(filename, "rb");

	fseek(move, 0L, SEEK_END);
	lSize2 = ftell(move);
	rewind(move);


	if (new == NULL)
		return 1;
	printf("Allocating mem\n");
	buffer2 = calloc(1, lSize2+1);

	if( !buffer2 ) fclose(move),fputs("memory alloc fails2",stderr),exit(1);

	/* copy the file into the buffer */
	printf("Reading file into mem\n");

	if( 1!=fread( buffer2 , lSize2, 1 , move) )
  		fclose(move),free(buffer2),fputs("entire read fails2",stderr),exit(1);
	move_array = ft_split(buffer2, '\n');
	free(buffer2);
	printf("We're in boys\n");

	i = 0;
	j = 0;
	//old array is move list in string, move_array is index
	//please dont look here, so dirty
	char *tmp = NULL;
	while (move_array[i])
	{
		int num = 0;
		//if line contains data, take the number and write it to a new file
		if (ft_strnstr(move_array[i], "data", ft_strlen(move_array[i])) != NULL)
		{
			tmp_array = ft_split(move_array[i], ' ');
			printf("hi\n");
			num = atoi(tmp_array[4]);
			printf("%d\n", num);
			tmp = ft_itoa(num);
			printf("%s\n", tmp);
			fputs(tmp, new);
			fputs("\n", new);
		}
		i++;		
	}
	free(move_array);
	fclose(move);
	fclose(new);
	return 0;
}