/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:37:51 by flfische          #+#    #+#             */
/*   Updated: 2024/04/24 11:58:15 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_stringall(char *str, int (*f)(int))
{
	while (*str)
	{
		if (!f(*str))
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t	serverid;
	char	*message;

	if (argc != 3 || !ft_stringall(argv[1], ft_isdigit))
	{
		ft_printf("Error\nUsage: %s [PID] [message]\n", argv[0]);
		return (1);
	}
	serverid = ft_atoi(argv[1]);
	message = argv[2];
	return (0);
}
