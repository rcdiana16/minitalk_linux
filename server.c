/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:52:28 by diana             #+#    #+#             */
/*   Updated: 2025/02/17 09:31:23 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char	c;
	static int	bit_pos;
	pid_t		sender_pid;

	(void)(context);
	(void)(info);
	sender_pid = info->si_pid;
	c |= (sig == SIGUSR2) << (7 - bit_pos);
	bit_pos++;
	if (bit_pos == 8)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(sender_pid, SIGUSR1);
		}
			
		else
			write(1, &c, 1);
		c = 0;
		bit_pos = 0;
	}
	
}

int	main(void)
{
	struct sigaction	s_action;

	ft_memset(&s_action, 0, sizeof(s_action));
	printf("server running with pid: %d\n", getpid());
	printf("-----------------\n");
	s_action.sa_sigaction = handle_signal;
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, 0);
	sigaction(SIGUSR2, &s_action, 0);
	while (1)
	{
		pause();
	}
	return (0);
}

/*
int	calculate_power(int nb, int power)
{
	int	res;

	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else
	{
		res = nb * calculate_power(nb, power - 1);
		return (res);
	}
}

char	*character_to_str(char const *s1, char const character)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	tab = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	tab[j++] = character;
	tab[j] = 0;
	free ((void *)(s1));
	return (tab);
}

void	signal_handler(int signum)
{
	static int	counter = 0;
	static int	result = 0;
	static char	*final;

	if (!final)
		final = ft_strdup("");
	if (signum == SIGUSR1)
		result = result + 0;
	else if (signum == SIGUSR2)
		result = result + (1 * calculate_power(2, 7 - counter));
	counter++;
	if (counter == 8)
	{
		final = character_to_str(final, result);
		if (result == '\0')
		{
			ft_printf("%s\n", final);
			final = NULL;
		}
		counter = 0;
		result = 0;
	}
}

int	main(void)
{
	struct sigaction	signal_received;

	ft_memset(&signal_received, 0, sizeof(signal_received));
	//pid_t pid = 0;
	//ft_memset(&signal_received, 0, sizeof(struct sigaction));
	//sigemptyset(&signal_received.sa_mask);
	//pid = getpid();

	ft_printf("Server's PID: %d\n", getpid());
	signal_received.sa_sigaction = signal_handler;
	signal_received.sa_flags = SA_SIGINFO;

	//sigemptyset(&signal_received.sa_mask);
	
	sigaction(SIGUSR1, &signal_received, 0);
	sigaction(SIGUSR2, &signal_received, 0);
	
	while (1)
		usleep(100);
}
*/