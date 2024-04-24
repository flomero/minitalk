/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:37:33 by flfische          #+#    #+#             */
/*   Updated: 2024/04/24 14:49:07 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

void	ft_realloc_str(char **str, size_t len)
{
	char	*new;

	new = malloc(sizeof(char) * len);
	if (!new)
		ft_error("Failed to allocate memory");
	ft_bzero(new, len);
	ft_memcpy(new, *str, len - BUFFER);
	free(*str);
	*str = new;
}

void	ft_sig_handler(int signum)
{
	static int			i;
	static char			c;
	static t_message	message = {NULL, 0, 0};

	if (signum == SIGUSR1)
		c |= 1 << i;
	i++;
	if (i == 8)
	{
		if (!message.str)
		{
			message.str = malloc(BUFFER_SIZE);
			if (!message.str)
				ft_error("Failed to allocate memory");
			message.len = BUFFER_SIZE;
			message.i = 0;
		}
		if (message.i == message.len - 1)
		{
			message.len += BUFFER_SIZE;
			ft_realloc_str(&message.str, message.len);
		}
		message.str[message.i++] = c;
		if (c == '\0')
		{
			message.str[message.i] = '\0';
			ft_printf("%s\n", message.str);
			free(message.str);
			message.str = NULL;
		}
		c = 0;
		i = 0;
	}
}

int	main(void)
{
	pid_t	serverid;

	serverid = getpid();
	if (serverid < 0)
		ft_error("Failed to get server PID");
	ft_printf("Server PID: %d\n", serverid);
	signal(SIGUSR1, ft_sig_handler);
	signal(SIGUSR2, ft_sig_handler);
	while (1)
	{
		pause();
	}
	return (0);
}
