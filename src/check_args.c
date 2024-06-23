/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:18:46 by ssoeno            #+#    #+#             */
/*   Updated: 2024/06/23 23:25:28 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// 0xFFFFFFFFFFFFFFFF
static long	ft_atol(const char *str)
{
	long	i;
	long	number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9') //overflowを考慮していない! LONG_MAX+2が1に変換されてしまっている。
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

static int	ft_duplicate(int num, char **argv, int i)
{
	i++;
	while (argv[i])
	{
		if (ft_atol(argv[i]) == num)
			return (1);
		i++;
	}
	return (0);
}

//"+"は許容しても良いのでは？
bool	ft_isnum(char *num) //少なくとも1つは数字が含まれているかどうかを確認すべき！"-"だけの場合はfalseにする。
{
	size_t	i;

	i = 0;
	if (num[0] == '-')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (false);
		i++;
	}
	return (true);
}

//duplicateは、まずnlognのソートをしてから、隣に同じ数字があるかどうかを確認した方が効率が良い
bool	ft_check_args(int argc, char **argv)
{
	int		i;
	long	tmp;
	char	**args;

	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv;
	while (args[++i])
	{
		tmp = ft_atol(args[i]);
		if (!ft_isnum(args[i]) || ft_duplicate(tmp, args, i)
			|| tmp < INT_MIN || tmp > INT_MAX)
		{
			ft_putstr_fd("Error\n", 2);
			if (argc == 2)
				ft_free(args);
			return (false);
		}
	}
	if (argc == 2)
		ft_free(args);
	return (true);
}
