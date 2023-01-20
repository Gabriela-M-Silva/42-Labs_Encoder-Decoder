/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:16:00 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/15 19:29:43 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void	rebuild_tree(t_data *data)
{
	create_list(data);
	create_tree(data);
//	create_dictionary(data);
}
