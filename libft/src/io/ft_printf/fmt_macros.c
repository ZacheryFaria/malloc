/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_macros.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:02:41 by zfaria            #+#    #+#             */
/*   Updated: 2020/01/19 13:05:46 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	is_inf(char *str)
{
	return (ft_strstr(str, "inf") || ft_strstr(str, "INF"));
}

int	has_sign(char *str)
{
	return (str[0] == '+' || str[0] == '-');
}