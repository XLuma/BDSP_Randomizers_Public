#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include "../42-libft/libft.h"
#include "../Resources/abilities.h"

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

int pick_ability(void)
{
	int	min = 1;
	int max = 267;
	int	pick = 0;

    pick = rand()%((max+1)-min) + min;
	while (pick==ABILITY_AS_ONE_1 || pick==ABILITY_AS_ONE_2 || pick==ABILITY_BATTLE_BOND || pick==ABILITY_DISGUISE
	 || pick==ABILITY_GULP_MISSILE || pick==ABILITY_HUNGER_SWITCH || pick==ABILITY_ICE_FACE || pick==ABILITY_POWER_CONSTRUCT || pick==ABILITY_RKS_SYSTEM || pick==ABILITY_STANCE_CHANGE || pick==ABILITY_WONDER_GUARD)
	 {
		pick = rand()%((max+1)-min) + min;
	 }
	 return (pick);
}

t_abilities init_abilities(void)
{
	t_abilities ret;

	ret.ability1 = 0;
	ret.ability2 = 0;
	ret.ability3 = 0;
	return (ret);
}

void find_old_ability(t_abilities *abilities, char **tab_abilities)
{
	int	i;
	char **tmp;
	char **tmp2;
	char **tmp3;

	tmp = ft_split(tab_abilities[0], ' ');
	tmp2 = ft_split(tab_abilities[1], ' ');
	tmp3 = ft_split(tab_abilities[2], ' ');

	abilities->ability1 = ft_atoi(tmp[5]);
	abilities->ability2 = ft_atoi(tmp2[5]);
	abilities->ability3 = ft_atoi(tmp3[5]);
}

char *new_ability(char *ability)
{
	char **tab;
	char *tmp;
	int	i;
	int j;
	int	ability1;

	tab = ft_split(ability, ' ');
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (ft_strnstr(tab[i], "tokusei", ft_strlen(tab[i])) != NULL)
		{
			ability1 = pick_ability();
			tab[i + 2] = ft_itoa(ability1);
			while (tab[j])
				j++;
			tmp = convertToLine(j, tab);
			tmp = ft_strjoin("     ", tmp);
			return (tmp);
		}
		i++;
	}
	return (ability);
}

int main(int argc, char **argv)
{
	char const *filename = argv[1];
	char const *newfile = ft_strjoin(argv[1], "_randomised");
	FILE *file;
	FILE *new;
	char *line;
	char **personalTab;
	long fileSize;
	unsigned long lenght;
	int i;
	int j;
	t_abilities abilities;

	srand((unsigned int)time(NULL)); //set random seed
	file = fopen(filename, "rb");
	new = fopen(newfile, "w");
	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file);
	rewind(file);

	printf("Reading personal data file\n");
	personalTab = (char **)malloc((fileSize *sizeof(char*)) + 1);
	i = 0;
	while (!feof(file))
    {
        getline(&line, &lenght, file);
        personalTab[i] = ft_strdup(line);
        i++;
    }

	printf("Randomizing abilities\n");
	char *temp = NULL;
	i = 0;
	while (personalTab[i])
	{
		if (ft_strnstr(personalTab[i], "tokusei", ft_strlen(personalTab[i])) != NULL)
		{
			j = 0;
			int counter = 0;
			char **tab_ability;
			int	current = i;
			tab_ability = malloc(4);
			while (ft_strnstr(personalTab[current], "tokusei", ft_strlen(personalTab[current])) != NULL && counter < 3)
			{
				tab_ability[counter] = ft_strdup(personalTab[current]);
				counter++;
				current++;
			}
			counter = 0;
			while (tab_ability[counter] && counter < 3)
			{
				tab_ability[counter] = new_ability(tab_ability[counter]);
				counter++;
			}
			counter = 0;
			while (tab_ability[counter] && counter < 3)
			{
				fputs(tab_ability[counter], new);
				if (ft_strnstr(tab_ability[counter], "\n", ft_strlen(tab_ability[counter])) == NULL)
                    fputc('\n', new);
				counter++;
			}
			free(tab_ability);
			while (ft_strnstr(personalTab[i], "tokusei", ft_strlen(personalTab[i])) != NULL)
            {
                i++;
            }
		}
		else
		{
			temp = ft_strdup(personalTab[i]);
			fputs(temp, new);
			i++;
		}
	}
	fclose(file);
	fclose(new);
	free(personalTab);
	return 0;
}
