/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:26:46 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/15 19:27:13 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	check_valid_text(char *text)
{
	int	i;

	i = 0;
	if (!text) //????precisa?
		exit (0);
	while (text[i])
	{
		if (text[i] < 0)
		{
			ft_printf("Error. Invalid char in the message or file.\n");
			free (text);
			exit (0);
		}
		i++;
	}
}

static char	*read_file(int fd)
{
	char	*text;
	char	*line;

	text = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		text = ft_strjoin_gnl(text, line);
		free(line);
	}
	if (!text)
	{
		ft_printf("Error\nEmpty file.\n");
		exit(0);
	}
	return (text);
}

static void	join_text(t_data *data, char *str, int fd)
{
	char	*aux;

	if (fd < 0)
		data->text = ft_strjoin_gnl(data->text, str); //e se str vazia?
	else
	{
		aux = read_file(fd);
		data->text = ft_strjoin_gnl(data->text, aux);
		free(aux);
	}
}

void	read_argv(int argc, char **argv, t_data *data)
{
	int	fd;
	int	i;

	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		join_text(data, argv[i], fd);
		i++;
	}
	check_valid_text(data->text);
}
