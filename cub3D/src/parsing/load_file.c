/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 18:08:38 by quill             #+#    #+#             */
/*   Updated: 2026/10/12 00:21:53 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	if (!line)
		return (0);
	if (!is_blank_line(line) && !is_config_line(line))
		return (1);
	return (0);
}

void	split_content(t_framework *fw)
{
	int	start_map;

	start_map = find_map_start(fw);
	if (start_map == -1)
		error_message("No valid map", fw);
	copy_map(fw, start_map);
	copy_config(fw, start_map);
}

void	load_file(char **argv, t_framework *fw)
{
	int	len;
	int	fd;

	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		error_message("Invalid file extension. Expected .cub", fw);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_message("Failed to open file", fw);
	get_content(fd, fw);
	close(fd);
	parse_config(fw);
	parse_map(fw);
}
