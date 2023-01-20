/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descompress_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:26:20 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 15:38:55 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

int	is_active_bit(char byte, int j)
{
	char	mask;

	mask = (1 << j);
	return (byte & mask);
}

void	descompress_code(t_data *data)
{
	char	byte;
	size_t	i;
	size_t	size;
	int		j;
	t_node	*aux;
	char	*aux_str;

	data->time_spent = 0.0;
	clock_t begin = clock();
	i = 0;
	aux = data->node;
	size = 0;
//	data->descompressed = NULL; //fazer func init p isso e resto da struct
	while (i < ft_strlen(data->compressed) + 1)
	{
		byte = data->compressed[i];
		j = 7;
		while (j >= 0)
		{
			if (is_active_bit(byte, j))
				aux = aux->right;
			else
				aux = aux->left;
			if (!aux->left && !aux->right && size < data->size_text)
			{
				aux_str = malloc(2);
				aux_str[0] = aux->c;
				aux_str[1] = '\0';
				data->descompressed = ft_strjoin_gnl(data->descompressed, aux_str);
				free(aux_str);
				if (data->node)
					aux = data->node;
				size++;
			}
			if (size >= data->size_text)
				break ;
			j--;
		}
		if (size >= data->size_text)
			break ;
		i++;
	}
	clock_t	end = clock();
	data->time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
}
