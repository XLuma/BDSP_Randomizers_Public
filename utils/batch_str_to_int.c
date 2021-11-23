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
	FILE *old;
	FILE *new;
	char *buffer;
	char **old_array;
	char *line;
	long lSize;
	int i;
	int j;

	old = fopen(filename, "rb");
	new = fopen(newfile, "w");
	fseek(old, 0L, SEEK_END);
	lSize = ftell(old);
	rewind(old);

	if (new == NULL)
		return 1;
	printf("Allocating mem\n");
	buffer = calloc(1, lSize+1);

	if( !buffer ) fclose(old),fputs("memory alloc fails",stderr),exit(1);

	/* copy the file into the buffer */
	printf("Reading file into mem\n");
	if( 1!=fread( buffer , lSize, 1 , old) )
  		fclose(old),free(buffer),fputs("entire read fails",stderr),exit(1);
	
	old_array = ft_split(buffer, '\n');
	free(buffer);
	printf("We're in boys\n");

	i = 0;
	while (old_array[i])
	{
		int num = atoi(old_array[i]);
		line = ft_itoa(num);
		printf("%s\n", line);
		fputs(line, new);
		fputs("\n", new);
		i++;
	}
	free(old_array);
	fclose(new);
	fclose(old);
	return 0;
}