/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:18:30 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/20 15:37:59 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

void	set_struct(t_data *data)
{
	data->text = NULL;
	data->node = NULL;
	data->dictionary = NULL;
	data->code = NULL;
	data->compressed = NULL;
}

void	free_struct(t_data *data)
{
	if (data->text)
		free(data->text);
	if (data->node)
		tree_clear(data->node);
	if (data->dictionary)
		free_dic(data->dictionary);
	if (data->code)
		free(data->code);
	if (data->compressed)
		free(data->compressed);
}

void	huffman_code(t_data *data) //recebe texto e dicionário
{
	int	i;

	i = 0;
	while (data->text[i])
	{
		data->code = ft_strjoin_gnl(data->code, data->dictionary[(int)data->text[i]]);
		i++;
	}
	compress_code(data);
}

void	get_and_print_decoder_datas(void)
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

//	ptr_descompressed = NULL;
//	ptr_bytes_to = NULL;
//	ptr_bytes_co = NULL;
//	ptr_time = NULL;
	key_descompressed = ftok("./decoder_src/decoder.h", 0);
    key_bytes_to = ftok("./decoder_src/decoder.h", 1);
	key_bytes_co = ftok("./decoder_src/decoder.h", 2);
	key_time = ftok("./decoder_src/decoder.h", 3);
	//dado descomprimido
	shmid_descompressed = shmget(key_descompressed, 0, 0);
	//bytes totais
	shmid_bytes_to = shmget(key_bytes_to, 0, 0);
	//bytes comprimidos
	shmid_bytes_co = shmget(key_bytes_co, 0, 0);
	//tempo
	shmid_time = shmget(key_time, 0, 0);

	if (shmid_descompressed < 0 || shmid_bytes_to < 0 || shmid_bytes_co < 0 || shmid_time < 0)
	{
		ft_printf("Error\nNo data\n");
		exit (0);
	}
	ptr_descompressed = (char *)shmat(shmid_descompressed, NULL, 0);
	ptr_bytes_to = (size_t *)shmat(shmid_bytes_to, NULL, 0);
	ptr_bytes_co = (size_t *)shmat(shmid_bytes_co, NULL, 0);
	ptr_time = (double *)shmat(shmid_time, NULL, 0);

	ft_printf("Descompressed text: %s\n", ptr_descompressed);
	ft_printf("Total bytes: %u\n", *ptr_bytes_to);
	ft_printf("Compressed bytes: %u\n", *ptr_bytes_co);
	printf("Decompression time: %lf\n", *ptr_time);
	shmdt(ptr_descompressed); 
	shmdt(ptr_bytes_to); 
	shmdt(ptr_bytes_co);
	shmdt(ptr_time);
	shmctl(shmid_descompressed, IPC_RMID, NULL);
	shmctl(shmid_bytes_to, IPC_RMID, NULL);
	shmctl(shmid_bytes_co, IPC_RMID, NULL);
	shmctl(shmid_time, IPC_RMID, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		get_and_print_decoder_datas();
	set_struct(&data);
	read_argv(argc, argv, &data);
	get_frequency(&data);
	create_list(&data);
	create_tree(&data);
	create_dictionary(&data);
	huffman_code(&data);
	mem_share(&data); //  ---mudar nome func
//	ft_printf("%s\n", data.text); //p teste
	free_struct(&data);
	return (0);
}
