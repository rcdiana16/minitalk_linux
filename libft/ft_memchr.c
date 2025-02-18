/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diramire <diramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:00:42 by diana             #+#    #+#             */
/*   Updated: 2025/02/18 11:04:44 by diramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*temp;
	size_t				i;

	temp = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (temp[i] == (unsigned char)c)
		{
			return ((void *)&temp[i]);
		}
		i++;
	}
	return (NULL);
}
