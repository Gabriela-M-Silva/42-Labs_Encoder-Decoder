/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:25:50 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 12:53:56 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODER_H
# define ENCODER_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>

# include <sys/ipc.h>
# include <sys/shm.h>
# include <stdio.h>

typedef struct s_node
{
	char			c;
	int				frequency;    //ruim usar separado //arvr tbm precisa do next pq ela vai sendo colocada na lista p ordenar //e dps retorna o nó raiz
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*next;
}	t_node;

typedef struct s_data
{
	char			*text;
	int				table[128];
	struct s_node	*node;
	char			**dictionary;
	char			*code;
	char			*compressed;
}	t_data;

void	read_argv(int argc, char **argv, t_data *data);
void	get_frequency(t_data *data);
void	create_list(t_data *data);
void	add_ordenate_list(t_data *data, t_node *new_node);
void	create_tree(t_data *data);
void	tree_clear(t_node *node);
void	create_dictionary(t_data *data);
void	free_dic(char **dic);
void	compress_code(t_data *data);
void	mem_share(t_data *data);
void	free_struct(t_data *data);

#endif