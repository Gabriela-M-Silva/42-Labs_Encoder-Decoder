/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:57:45 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/15 17:32:16 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	ft_enc_lstadd_front(t_node **lst, t_node *new)
{
	new->next = *lst;
	*lst = new;
}

void	add_ordenate_list(t_data *data, t_node *new_node)
{
	t_node	*aux;

	aux = data->node;
	if (!data->node)
		data->node = new_node;
	else if (new_node->frequency < aux->frequency)
		ft_enc_lstadd_front(&data->node, new_node);
	else 
	{
		while (aux->next && aux->next->frequency <= new_node->frequency)
			aux = aux->next;
		new_node->next = aux->next;
		aux->next = new_node;
	}
}

t_node	*ft_enc_lstnew(int frequency, int position)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->frequency = frequency;
	new_node->c = (char)position;
	new_node->right = NULL;
	new_node->left = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	create_list(t_data *data)
{
	int		i;
	t_node	*new_node;

	i = 0;
	while (i < 128)
	{
		if (data->table[i] > 0)
		{
			new_node = ft_enc_lstnew(data->table[i], i); //e se o malloc falhar? colocar break ou return  //é o suficiente em caso de erro?
			if (!new_node)
			{
				free_struct(data);
				exit (0);
			}
			add_ordenate_list(data, new_node);
		}
		i++;
	}
}
