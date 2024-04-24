/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:37:33 by flfische          #+#    #+#             */
/*   Updated: 2024/04/24 21:22:39 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_exit(char *str, int status)
{
	if (str && status)
		ft_printf("Error: %s\n", str);
	if (str && !status)
		ft_printf("%s\n", str);
	exit(status);
}

int	ft_handle_message(char c, t_message *message, siginfo_t *info)
{
	if (!message->str)
	{
		message->str = malloc(BUFFER_SIZE);
		if (!message->str)
			ft_exit("Failed to allocate memory", 1);
		message->len = BUFFER_SIZE;
		message->i = 0;
	}
	if (message->i == message->len - 1)
	{
		ft_realloc_str(&message->str, message->len, message->len * 2);
		message->len *= 2;
	}
	message->str[message->i++] = c;
	if (c == '\0')
	{
		message->str[message->i] = '\0';
		ft_printf("%s\n", message->str);
		free(message->str);
		message->str = NULL;
		usleep(100);
		kill(info->si_pid, SIGUSR1);
		return (1);
	}
	return (0);
}

pid_t	ft_clientid_check(siginfo_t *info, t_message *message, int *i, char *c)
{
	static pid_t	clientid;

	if (clientid != info->si_pid)
	{
		ft_bzero(message, sizeof(*message));
		clientid = info->si_pid;
		*i = 0;
		*c = 0;
	}
	return (clientid);
}

void	ft_sig_handler(int signum, siginfo_t *info, void *context)
{
	static int			i;
	static char			c;
	static t_message	message = {NULL, 0, 0};
	static pid_t		clientid;

	(void)context;
	clientid = ft_clientid_check(info, &message, &i, &c);
	if (signum == SIGINT)
	{
		if (message.str)
			free(message.str);
		ft_exit("Server terminated", 0);
	}
	if (signum == SIGUSR1)
		c |= 1 << i;
	if (++i == 8)
	{
		ft_handle_message(c, &message, info);
		c = 0;
		i = 0;
	}
	usleep(100);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sigac;
	pid_t				serverid;

	serverid = getpid();
	ft_printf("Server PID: %d\n", serverid);
	ft_bzero(&sigac, sizeof(sigac));
	sigac.sa_sigaction = ft_sig_handler;
	sigac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sigac, NULL) < 0 || sigaction(SIGUSR2, &sigac,
			NULL) < 0 || sigaction(SIGINT, &sigac, NULL) < 0)
		ft_exit("Failed to set signal handler", 1);
	while (1)
		pause();
	return (0);
}
