/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:42:59 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 12:53:30 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
# define DECODER_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>

# include <sys/ipc.h>
# include <sys/shm.h>
# include <time.h>
# include <stdio.h>

typedef struct s_node
{
	char			c;
	int				frequency;
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*next;
}	t_node;

typedef struct s_data
{
	int				table[128];
	struct s_node	*node;
	char			*compressed;
	char			*descompressed;
	size_t			size_text;
	double			time_spent;
}	t_data;

void	rebuild_tree(t_data *data);
void	create_list(t_data *data);
void	add_ordenate_list(t_data *data, t_node *new_node);
void	create_tree(t_data *data);
void	create_dictionary(t_data *data);
void	tree_clear(t_node *node);
void	free_dic(char **dic);
void	descompress_code(t_data *data);

#endif