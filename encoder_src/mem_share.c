/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_share.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 07:54:45 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/15 19:26:47 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	mem_share(t_data *data) //tabela freq e valor comprimido
{
	key_t	key_table;
	key_t	key_compressed;
	key_t	key_size_text;
    int		shmid_table;
	int		shmid_compressed;
	int		shmid_size_text;
    int		*ptr_table;
	char	*ptr_compressed;
	size_t	*ptr_size_text;
	int		i;

	key_table = ftok("./encoder_src/encoder.h", 0);
    key_compressed = ftok("./encoder_src/encoder.h", 1);
	key_size_text = ftok("./encoder_src/encoder.h", 2);
	if (key_table < 0 || key_compressed < 0 || key_size_text < 0)
    {
        ft_printf("Error. Memory is not created.\n"); //crio um exit error?
        return ;
    }
	shmid_table = shmget(key_table, sizeof(int) * 128, SHM_R | SHM_W | IPC_CREAT); //allocar do tamanho de uma struct
	shmid_compressed = shmget(key_compressed, sizeof(char) * (ft_strlen(data->compressed) + 1), SHM_R | SHM_W | IPC_CREAT); // tem o +1?
	shmid_size_text = shmget(key_size_text, sizeof(size_t), SHM_R | SHM_W | IPC_CREAT); //??
	ptr_table = (int *)shmat(shmid_table, NULL, 0);
	ptr_compressed = (char *)shmat(shmid_compressed, NULL, 0);
	ptr_size_text = (size_t *)shmat(shmid_size_text, NULL, 0);

//	atribui table para ptr table
	i = 0;
	while (i < 128)
	{
		ptr_table[i] = data->table[i];
		i++;
	}
//	atribui texto comprimido para ptr comprimido
	size_t j = 0;
	while (j < ft_strlen(data->compressed) + 1)
	{
		ptr_compressed[j] = data->compressed[j];
		j++;
	}
	ptr_compressed[j] = '\0';
//	atribui size para ptr size
	ptr_size_text[0] = ft_strlen(data->text);

/*	//printf p teste
	i = 0;
	while (i < 128)
	{
		ft_printf("Char: %c and Frequency: %d\n", i, ptr[i]);
		i++;
	}*/

//	printf p teste
/*	j = 0;
	while (j < ft_strlen(data->compressed))
	{
		ft_printf("Char: %c\n", ptr_compressed[j]);
		j++;
	}
*/
//	printf p teste
	ft_printf("Tam text: %d\n", ft_strlen(data->text));
	ft_printf("Tam ptr: %d\n", ptr_size_text[0]);


   /* if (shmdt(ptr) < 0)
    {
        ft_printf("Error in free shared memory\n");
        return (1);
    }
	shmget
	shmat*/
}
