/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:37:33 by flfische          #+#    #+#             */
/*   Updated: 2024/04/24 11:55:11 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	pid_t	serverid;

	serverid = getpid();
	if (serverid < 0)
	{
		ft_printf("Error\nFailed to get server PID\n");
		return (1);
	}
	ft_printf("Server PID: %d\n", serverid);
	return (0);
}
