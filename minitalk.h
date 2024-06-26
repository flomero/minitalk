/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:35:28 by flfische          #+#    #+#             */
/*   Updated: 2024/04/24 21:52:42 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>
# include <unistd.h>

# define BUFFER 1000

typedef struct s_message
{
	char	*str;
	size_t	i;
	size_t	len;
	pid_t	clientid;
}			t_message;

#endif
