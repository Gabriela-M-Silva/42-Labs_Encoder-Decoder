/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dictionary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:59:28 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 15:38:24 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	free_dic(char **dic)
{
	int	i;

	i = 0;
	if (!dic && !*dic) //manter? testar na main com NULL --- ver sobre o *dic (sus)
		return ;
	while (i < 128) //mudar valor p TAM dps
	{
		if (dic[i])
			free(dic[i]);
		i++;
	}
	free(dic);
	dic = NULL;
}

int		tree_size(t_node *node)
{
	int	left;
	int	right;
	int	size;

	if (!node)
		return (-1);
	left = tree_size(node->left) + 1;
	right = tree_size(node->right) + 1;
	if (left > right)
		size = left;
	else
		size = right;
	return (size);
}

void	set_dictionary_values(char **dic, t_node *node, char *path, int columns)
{
	char	left[columns];
	char	right[columns];
	
	if (!node)
		return ;
	if (!node->left && !node->right)
		strcpy(dic[(int)node->c], path); //  ---e se path = NULL? -- aí seria arvore vazia...(?
	else
	{
		strcpy(left, path);
		strcpy(right, path);
		strcat(left, "0"); 		//cada vez q esquerda,  + "0"
		strcat(right, "1");		//cada vez q direita,   + "1"
		set_dictionary_values(dic, node->left, left, columns);
		set_dictionary_values(dic, node->right, right, columns);
	}
}

void	create_dictionary(t_data *data) //n tem como passar pra mem compartilhada pq altura da arvore varia //a n ser q tenha 
{
	int	columns; //usar size_t?
	int	i;

	columns = tree_size(data->node) + 1; //altura + \0     ----criar macro pra esse 128, posso alterar dps //cuidado p n esquecer de alterar algum lugar
	data->dictionary = malloc(sizeof(char *) * 128); //vetor com 128 posições (0 a 127) que guardam ponteiro p string
	//if (!data->dictionary)  ...
	i = 0;
	while (i < 128) //alterar TAM
	{
		data->dictionary[i] = calloc(columns, sizeof(char)); //ja malloca e zera  --- tbm posso usar malloc e bzero com size_t column(?)
		if (!data->dictionary[i])
		{
			free_dic(data->dictionary); //certo?
			return ; //trocar td pra exit (0)? cuidado pra n deixar de liberar as coisas --> func de erro
		}
		//e se der erro no calloc??
		i++;
	}
//	if (!node->left && !node->right) //add esse if e else
//		strcpy(dic[(int)node->c], "0"); //ele n pode ser 0    --------n, vou criar a árvore ja pronta pro set
//	else
	set_dictionary_values(data->dictionary, data->node, "", columns); //isso ja tava
}
