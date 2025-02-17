/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:52:24 by diana             #+#    #+#             */
/*   Updated: 2025/02/17 09:44:17 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void received_messaged(int sig)
{
	if (sig)
		write(1, "message received by server!", 27);
	
}
void	str_to_bin(char *str, int pid)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(1000);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	//struct sigaction	s_action;
	int					server_pid;

	//ft_memset(&s_action, 0, sizeof(s_action));
	//s_action.sa_sigaction = received_messaged;
	signal(SIGUSR1, received_messaged);

	if (argc != 3)
	{
		write(1, "invalid args", 12);
		return (0);
	}
	server_pid = atoi(argv[1]);
	str_to_bin(argv[2], server_pid);
	return (0);
}


/*
void	send_signals(int pid, char *message)
{
	int				character;
	int				i;

	character = 0;
	while (message[character])
	{
		i = -1;
		while (++i < 8)
		{
			if (((unsigned char)(message[character] >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((unsigned char)(message[character] >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(50);
		}
		character++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	char				*message;
	int					server_id;

	if (argc == 3)
	{
		server_id = ft_atoi(argv[1]);
		if (!server_id)
		{
			ft_printf("ERROR");
			return (0);
		}
		message = argv[2];
		if (message[0] == 0)
		{
			ft_printf("You did not send anything. Send something\n");
			return (0);
		}
		send_signals(server_id, message);
	}
	else
		ft_printf("ERROR. Follow this order: ./client <PID> <MESSAGE>\n");
	return (0);
}
*/