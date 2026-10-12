/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 00:18:36 by quill             #+#    #+#             */
/*   Updated: 2026/10/12 00:21:41 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_line(t_framework *fw, char *line)
{
	if (fw->map_started && is_blank_line(line))
	{
		free(line);
		error_message("Empty line in map", fw);
	}
	if (is_map_line(line))
		fw->map_started = 1;
}

char	*append_line(char *content, char *line, t_framework *fw)
{
	char	*temp;

	temp = ft_strjoin(content, line);
	free(content);
	free(line);
	if (!temp)
		error_message("Malloc failed", fw);
	return (temp);
}

void	get_content(int fd, t_framework *fw)
{
	char	*line;
	char	*l_line;

	l_line = ft_strdup("");
	if (!l_line)
		error_message("Malloc failed", fw);
	line = get_next_line(fd);
	while (line)
	{
		check_line(fw, line);
		l_line = append_line(l_line, line, fw);
		line = get_next_line(fd);
	}
	fw->content = ft_split(l_line, '\n');
	free(l_line);
	if (!fw->content)
		error_message("Split failed", fw);
	split_content(fw);
}
