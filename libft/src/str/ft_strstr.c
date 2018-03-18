/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:48 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/08 13:54:08 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int i_to_find;

	i = 0;
	i_to_find = 0;
	if (*to_find == '\0')
		return ((char*)str);
	while (str[i])
	{
		if (to_find[i_to_find] == str[i])
		{
			while (to_find[i_to_find] == str[i + i_to_find])
			{
				i_to_find++;
				if (to_find[i_to_find] == '\0')
					return ((char*)(str + i));
			}
			i_to_find = 0;
		}
		i++;
	}
	return (0);
}
