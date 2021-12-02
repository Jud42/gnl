/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:54:41 by rmamison          #+#    #+#             */
/*   Updated: 2021/12/02 20:09:12 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(const char *s)
{
  int i = 0;
  while (s[i] != '\0')
    i++;
  return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len_s1;
	size_t	len_all;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_all = len_s1 + ft_strlen(s2);
	p = malloc (sizeof(char) * len_all + 1);
	if (!p)
		return (NULL);
	strlcpy(p, s1, len_s1);
	strlcat(p, s2, len_all + 1);
	return (p);
}

char  *ft_strchr(const char *s, int c)
{
  if (!s)
    return (0);
  while (*s != (char) c)
  {
    if (*s++ == '\0')
      return (NULL);
  }
  return ((char *)s);
}

char  *ft_lineLeft(char *str)
{
  int i;
  int j;
  char  *p;

  i = 0;
  while (str[i] && str[i] != '\n')
    i++;
  if (str[i] == '\n')
    p = malloc(sizeof(char) * i + 2);
  else
    p = malloc(sizeof(char) * i + 1);
  if (!p)
    return (NULL);
  i = 0;
  j = 0;
  while(str[i] && str[i] != '\n')
    p[j++] = str[i++];
  if (str[i] == '\n')
    p[j++] = str[i++];
  p[j] = '\0';
  return (p);
}

char  *ft_lineRight(char *str)
{
  char  *p;
  int i;
  int j;
  
  i = 0;
  while (str[i] && str[i] != '\n')
    i++;
  p = malloc(sizeof(char) * (strlen(str) - i + 1));
  if (!p)
    return (NULL);
  j = 0;
  while (str[i])
    p[j++] = str[++i];
  p[j] = '\0';
  return (p);
}

char  *pre_get_next_line(int fd, char *str)
{
  char *buf;
  int   ret;

  buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
  if (!buf)
    return (NULL);
  ret = 1;
  while (!ft_strchr(str, '\n') && ret != 0)
  {
    ret = read(fd, buf, BUFFER_SIZE);
    if (ret == -1)
    {
      free(buf);
      return (NULL);
    }
    buf[ret] = '\0';
    str = ft_strjoin(str ,buf); //concatenation
  }
 // free(buf);
  return (str);
}