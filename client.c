/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:37:51 by flfische          #+#    #+#             */
/*   Updated: 2024/04/24 14:01:26 by flfische         ###   ########.fr       */
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

int	ft_send_char(pid_t serverid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 1)
			kill(serverid, SIGUSR1);
		else
			kill(serverid, SIGUSR2);
		c >>= 1;
		i++;
		usleep(100);
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
	while (*message)
	{
		ft_send_char(serverid, *message);
		message++;
	}
	ft_send_char(serverid, '\0');
	return (0);
}
