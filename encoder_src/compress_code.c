/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 06:30:42 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 15:30:10 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	compress_code(t_data *data)
{
	int		i;
	int		j;
	char	mask;
	char	byte;
	char	*aux;

	i = 0;
	j = 7;
	byte = 0; // 0000 0000
	while (data->code[i])
	{
		mask = 1; //tem q estar dentro do while pq é alterada no if   // 0000 0001
		if (data->code[i] == '1')
		{
			mask = mask << j;
			byte = byte | mask;
		}
		j--;
		if (j < 0)
		{	
			aux = malloc(2);
			aux[0] = byte;
			aux[1] = '\0';
			data->compressed = ft_strjoin_gnl(data->compressed, aux);
			free(aux);
			byte = 0;
			j = 7;
		}
		i++;
	}
	if (j != 7)
	{
		aux = malloc(2);
		aux[0] = byte;
		aux[1] = '\0';
		data->compressed = ft_strjoin_gnl(data->compressed, aux);
		free(aux);
	}
	ft_printf("veio ate aq \n"); //no caso de yyyyyyyy
	if (!data->compressed)
	{
		free_struct(data);
		exit (0);
	}
}
