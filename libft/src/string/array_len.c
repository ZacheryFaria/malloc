/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:22:06 by zfaria            #+#    #+#             */
/*   Updated: 2019/02/27 20:39:55 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	array_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i] && arr[i][0])
		i++;
	return (i);
}
