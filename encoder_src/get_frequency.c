/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_frequency.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:19:29 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/15 19:25:17 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	get_frequency(t_data *data)
{
	int	i;

	i = 0;
	while (i < 128)
	{
		data->table[i] = 0;
		i++;
	}
	i = 0;
	while (data->text[i])
	{
		data->table[(int)data->text[i]]++;
		i++;
	}
}
