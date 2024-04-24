/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:37:51 by flfische          #+#    #+#             */
/*   Updated: 2024/04/24 22:45:32 by flfische         ###   ########.fr       */
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

int	*ft_get_conf(void)
{
	static int	conf;

	return (&conf);
}

int	ft_send_char(pid_t serverid, unsigned char c, struct sigaction sigac)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(100);
		if (c & 1)
			kill(serverid, SIGUSR1);
		else
			kill(serverid, SIGUSR2);
		sigaction(SIGUSR1, &sigac, NULL);
		sigaction(SIGUSR2, &sigac, NULL);
		pause();
		c >>= 1;
		i++;
	}
	return (1);
}

void	ft_sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	i;

	(void)info;
	(void)context;
	if (signum == SIGUSR2)
		i++;
	if (signum == SIGUSR1)
	{
		i++;
		ft_printf("Whole message recieved. Bit count: %d\n", i);
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t				serverid;
	char				*message;
	struct sigaction	sigac;

	if (argc != 3 || !ft_stringall(argv[1], ft_isdigit)
		|| ft_strlen(argv[2]) == 0)
	{
		ft_printf("Error\nUsage: %s [PID] [message]\n", argv[0]);
		return (1);
	}
	serverid = ft_atoi(argv[1]);
	message = argv[2];
	ft_bzero(&sigac, sizeof(sigac));
	sigac.sa_flags = SA_SIGINFO;
	sigac.sa_sigaction = ft_sig_handler;
	while (*message)
	{
		ft_send_char(serverid, *message, sigac);
		message++;
	}
	ft_send_char(serverid, '\0', sigac);
	return (0);
}
