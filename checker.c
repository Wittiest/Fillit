/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:40:17 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/01 12:39:09 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

t_info	*solveinfo;

int		numofgrids(char	*buf)
{
	int	i;

	i = 1;
	while (*buf)
	{
		if (*buf == '\n' && *(buf + 1) == '\n')
			i++;
		buf++;
	}
	return (i);
}

int		stage_three(int n, int delta, int row_delta, int col_delta)
{
	if (((((delta + n) % 5) - n % 5) == row_delta) && ((((delta + n) / 5) - (n / 5)) == col_delta))
		return (1);
	return (0);
}

int	struct_add(int j)
{
	int i;

	i = 0;
	while (grids[i].i)
		i++;
	grids[i].i = j;
	return (1);
}

int	stage_two(int n, int *delta)
{
	if (stage_three(n, delta[0], 1, 0))
	{
		if ((stage_three(n, delta[1], 2, 0)))
		{
			if (stage_three(n, delta[2], 3, 0))
				return(struct_add(2));
			if (stage_three(n, delta[2], 0, 1))
				return(struct_add(8));
			if (stage_three(n, delta[2], 2, 1))
				return(struct_add(12));
			if (stage_three(n, delta[2], 1, 1))
				return(struct_add(16));
		}
		if (stage_three(n, delta[1], 0, 1))
		{
			if (stage_three(n, delta[2], 1, 1))
				return(struct_add(1));
			if (stage_three(n, delta[2], 0, 2))
				return(struct_add(13));
		}
		if (stage_three(n, delta[1], 1, 1))
		{
			if (stage_three(n, delta[2], 2, 1))
				return(struct_add(6));
			if (stage_three(n, delta[2], 1, 2))
				return(struct_add(11));
		}
		if (stage_three(n, delta[1], -1, 1) && stage_three(n, delta[2], 0, 1))
				return(struct_add(4));
	}
	if (stage_three(n, delta[0], 0, 1))
	{
		if(stage_three(n, delta[1], 0, 2))
		{
			if (stage_three(n, delta[2], 0, 3))
				return(struct_add(3));
			if (stage_three(n, delta[2], 1, 2))
				return(struct_add(9));
		}
		if (stage_three(n, delta[1], 1, 1))
		{
			if (stage_three(n, delta[2], 1, 2))
				return(struct_add(5));
			if (stage_three(n, delta[2], 2, 1))
				return(struct_add(14));
			if (stage_three(n, delta[2], 0, 2))
				return(struct_add(17));
		}
		if (stage_three(n, delta[1], -1, 2) && stage_three(n ,delta[2], 0, 2))
			return(struct_add(15));
	}
	if (stage_three(n, delta[0], -1, -1) && stage_three(n, delta[1], 0, 1))
	{
		if (stage_three(n, delta[2], -1, 2))
			return(struct_add(7));
		if (stage_three(n, delta[2], 1, 1))
			return(struct_add(18));
		if (stage_three(n, delta[2], 0, 2))
			return(struct_add(19));
	}
	if (stage_three(n, delta[0], -2, -1) && stage_three(n, delta[1],-1,-1) && stage_three(n, delta[2], 0, 1))
		return(struct_add(10));
	return (0);
}

void	stage_one(int n, char *buf)
{
	int delta[3];
	int i;
	int j;

	i = 1;
	j = 0;
	while (buf[i])
	{
		if (buf[i] == '#' && j < 3)
		{
			delta[j] = i;
			j++;
		}
		i++;
	}
	if (!(stage_two(n, delta)))
	{
		ft_putstr("error stage_two\n"); 
		exit(3);		
	}
}

int		error_check(char c, int i, int hash)
{
	if ((c != '\n') && (c != '.') && (c != '#'))
		return (0);
	if (i == 0 && c != '.' && c != '#')
		return (0);
	if (i != 20 && (!(i + 1 % 5)) && i != 0)
		return (0);
	if (hash > 4)
		return (0);
	if (i == 20 && (c != '\n' || hash < 4))
		return (0);
	return (1);
}

int		convert_buf(char *buf)
{
	int i;
	int hash;

	i = 0;
	hash = 0;
	while (*buf)
	{
		if (!(error_check(*buf, i, hash)))
			return (0);
		if (i == 20)
		{
			i = -1;
			hash = 0;
		}
		if (*buf == '#')
		{
			hash++;
			if (hash == 1)
				stage_one(i + 1, buf);
		}
		i++;
		buf++;
	}
	return (1);
}

void		perform_check(char *buf)
{
	int small_grids;

	small_grids = numofgrids(buf);
	solveinfo = (t_info *)ft_memalloc(sizeof(solveinfo));
	grids = (t_grid *)ft_memalloc((small_grids * 5 / 8) + 2);
	if (!grids)
	{
		ft_putstr("Error in allocating small grids!");
		exit(2);
	}
	minimumset(small_grids);
	if (!(convert_buf(buf)))
	{
		ft_putstr("error\n");
		exit(3);
	}
	printf("Solve resp: %d\n", solve());
	printf("We malloc'd %d grids for a size of %lu bytes\n", small_grids, small_grids * sizeof(struct s_grid *));	
}
