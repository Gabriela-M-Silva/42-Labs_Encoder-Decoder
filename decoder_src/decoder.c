/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:18:41 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 15:29:58 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void	set_struct(t_data *data)
{
	data->node = NULL;
	data->descompressed = NULL;
	data->compressed = NULL;
}

void	free_struct(t_data *data)
{
	if (data->node)
		tree_clear(data->node);
	if (data->descompressed)
		free(data->descompressed);
	if (data->compressed)
		free(data->compressed);
}

void	get_encoder_dates(t_data *data)
{
	key_t	key_table;
	key_t	key_compressed; //t_memory?
	key_t	key_size_text;
	int		shmid_table;
	int		shmid_compressed;
	int		shmid_size_text;
    int		*ptr_table;
	char	*ptr_compressed;
	size_t	*ptr_size_text;
	int 	i;

	key_table = ftok("./encoder_src/encoder.h", 0);
    key_compressed = ftok("./encoder_src/encoder.h", 1);
	key_size_text = ftok("./encoder_src/encoder.h", 2);
    shmid_table = shmget(key_table, 0, 0);
	shmid_compressed = shmget(key_compressed, 0, 0);
	shmid_size_text = shmget(key_size_text, 0, 0);

	if (shmid_table < 0 || shmid_compressed < 0 || shmid_size_text < 0)
	{
		ft_printf("Error\nNo data\n");
		exit (0);
	}
    ptr_table = (int *)shmat(shmid_table, NULL, 0);
	ptr_compressed = (char *)shmat(shmid_compressed, NULL, 0);
	ptr_size_text = (size_t *)shmat(shmid_size_text, NULL, 0);
//	atribui table
	i = 0;
	while (i < 128)
	{
		data->table[i] = ptr_table[i];
		i++;
	}
	rebuild_tree(data);
//	atribui texto comprimido
	data->compressed = malloc(sizeof(char) * (ft_strlen(ptr_compressed) + 1)); //criar testes e erros p esses malloc
	size_t j = 0;
	while (j < ft_strlen(ptr_compressed))
	{
		data->compressed[j] = ptr_compressed[j];
		j++;
	}	
	data->compressed[j] = '\0';
//atribui size_text
	data->size_text = ptr_size_text[0];
//libera mem_shared
	shmdt(ptr_table); 
	shmdt(ptr_compressed); 
	shmdt(ptr_size_text);
	shmctl(shmid_table, IPC_RMID, NULL);
	shmctl(shmid_compressed, IPC_RMID, NULL);
	shmctl(shmid_size_text, IPC_RMID, NULL);
}

void	send_info_to_encoder(t_data *data)
{
	key_t	key_descompressed;
	key_t	key_bytes_to;
	key_t	key_bytes_co;
	key_t	key_time;
	int		shmid_descompressed;
	int		shmid_bytes_to;
	int		shmid_bytes_co;
	int		shmid_time;
	char	*ptr_descompressed;
    size_t	*ptr_bytes_to;
	size_t	*ptr_bytes_co;
	double	*ptr_time;

	key_descompressed = ftok("./decoder_src/decoder.h", 0);
    key_bytes_to = ftok("./decoder_src/decoder.h", 1);
	key_bytes_co = ftok("./decoder_src/decoder.h", 2);
	key_time = ftok("./decoder_src/decoder.h", 3);
	//dado descomprimido
	shmid_descompressed = shmget(key_descompressed, sizeof(char) * (ft_strlen(data->descompressed) + 1), SHM_R | SHM_W | IPC_CREAT);
	//bytes totais
	shmid_bytes_to = shmget(key_bytes_to, sizeof(size_t), SHM_R | SHM_W | IPC_CREAT);
	//bytes comprimidos
	shmid_bytes_co = shmget(key_bytes_co, sizeof(size_t), SHM_R | SHM_W | IPC_CREAT);
	//tempo
	shmid_time = shmget(key_time, sizeof(double), SHM_R | SHM_W | IPC_CREAT);

	ptr_descompressed = (char *)shmat(shmid_descompressed, NULL, 0);
	ptr_bytes_to = (size_t *)shmat(shmid_bytes_to, NULL, 0);
	ptr_bytes_co = (size_t *)shmat(shmid_bytes_co, NULL, 0);
	ptr_time = (double *)shmat(shmid_time, NULL, 0);

	//atribui descompressed
	size_t i = 0;
	while (i < ft_strlen(data->descompressed) + 1)
	{
		ptr_descompressed[i] = data->descompressed[i];
		i++;
	}
	ptr_descompressed[i] = '\0';
	//atribui size_t values
	ptr_bytes_to[0] = data->size_text;
	ptr_bytes_co[0] = ft_strlen(data->compressed);
	//atribui time
	ptr_time[0] = data->time_spent;
}

int main(void)
{
	t_data	data;

	set_struct(&data);
	get_encoder_dates(&data);
	descompress_code(&data);
//	ft_printf("teste: %s\n", data.descompressed); //ta perdendo os ultimos bytes em textos grandes  //print p teste
	send_info_to_encoder(&data);
	free_struct(&data);
	return (0);
}
