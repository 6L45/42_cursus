/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:52:47 by mberengu          #+#    #+#             */
/*   Updated: 2021/04/01 11:52:49 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// string size
size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

// \n checker
int	got_new_line(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

// lecture du fichier
// dans une loop lire jusqu'à EOF ou \n
// (norme 42 : on ne peut pas assigner de variable dans loops ou conditions)
// strjoin custom -> join strings buf, tmp, et free tmp.
int	file_reader(int fd, char **line)
{
	char	*buf;
	char	*tmp;
	int		res;
	res = 1;
	buf = NULL;
	tmp = NULL;
	while (res > 0)
	{
		tmp = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		res = read(fd, tmp, BUFFER_SIZE);
		tmp[res] = '\0';
		if (got_new_line(tmp))
		{
			buf = ft_strjoin(&buf, &tmp);
			break ;
		}
		buf = ft_strjoin(&buf, &tmp);
	}
	*line = buf;
	if (res != 0)
		res = 1;
	return (res);
}

// backup = static
// lecture de ce que contient la static si \n dans la static
void	backup_reader(char **backup, char **line)
{
	char	*str;
	char	*ptrbu;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ptrbu = *backup;
	while (ptrbu[++i])
	{
		if (ptrbu[i] == '\n')
			break ;
	}
	str = (char *)ft_calloc((i + 1), sizeof(char));
	while (++j < i)
		str[j] = ptrbu[j];
	str[j] = '\0';
	*line = str;
	ft_strcpy(*backup, &ptrbu[i + 1]);
}

// comme la taille du buffer pour le read est décidé à la compilation
// et qu on ne peux pas remonter dans le fichier lut (fonction interdite)
// dans une variable static, on stock les caractères qui serait après un \n
// A chaque rappel de la fonction, on vérifie qu'un \n 
// ne soit pas dans la static avant de read à nouveaux
// si y'a un \n on prend la partie jusqu'au \n et la static garde uniquement ce qu il y a apres
// sinon on concat le resultat du read a ce que contient la static et on stock a nouveaux tout ce qu il y a apres le \n ...etc
// la ligne est envoyé dans le char **line
// et la fonction renvoie 0 pour EOF, -1 en cas d'erreur, sinon 1
int	get_next_line(int fd, char **line)
{
	static char	backup[BUFFER_SIZE + 1] = "";
	char		*transit;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL
		|| read(fd, backup, 0) < 0 || fd >= 256 || fd == 1 || fd == 2)
		return (-1);
	transit = backup;
	if (got_new_line(backup))
	{
		backup_reader(&transit, line);
		ft_strcpy(backup, transit);
		return (1);
	}
	i = file_reader(fd, line);
	ft_strchr(line, (int) '\n', &transit);
	ft_strcpy(backup, transit);
	return (i);
}
