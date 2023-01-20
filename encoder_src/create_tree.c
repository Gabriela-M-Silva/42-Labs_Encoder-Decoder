/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:53:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 15:11:50 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	tree_clear(t_node *node)
{
	t_node	*left;
	t_node	*right;

	if (!node)
		return ;
	if (!node->left && !node->right)
	{
		free(node);
		return ;
	}
	left = node->left;
	right = node->right;
	free(node);
	tree_clear(left);
	tree_clear(right);
}

t_node	*remove_node(t_node *node)
{
	t_node	*aux;

	aux = NULL;
	if (node)
		aux = node;
		//node = node->next; //n ta avançando aq   ---- estranho  ---ponteiro?
		//aux->next = NULL; //desconetar dos proximos?   //n funcionava
	return (aux);
}

int	ft_enc_lstsize(t_node *lst)
{
	t_node	*aux_lst;
	int		len;

	aux_lst = lst;
	len = 0;
	while (aux_lst)
	{
		aux_lst = aux_lst->next;
		len++;
	}
	return (len);
}

void	create_tree(t_data *data)
{
	t_node	*new_node;
	int		len;

	len = ft_enc_lstsize(data->node);
	while (len > 1)
	{
		new_node = malloc(sizeof(t_node));
		if (!new_node)
		{
			free_struct(data);
			exit (0);
		}
		new_node->left = remove_node(data->node);
		data->node = data->node->next;
		new_node->right = remove_node(data->node);
		data->node = data->node->next;
		new_node->c = '+';
		new_node->frequency = new_node->left->frequency + new_node->right->frequency;
		new_node->next = NULL;
		add_ordenate_list(data, new_node);
		len--;
	}
	if (!data->node) //trata argv vazio
	{
		free(data->text);
		exit (0);
	}
}
