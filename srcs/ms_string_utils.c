/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:22:45 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/04 11:26:25 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int	is_string_numeric(char *num_str)
{
	while (ft_isspace(*num_str))
		num_str++;
	if (*num_str == '-' || *num_str == '+')
		num_str++;
	while (*num_str >= '0' && *num_str <= '9')
		num_str++;
	if (*num_str)
		return (1);
	return (0);
}
