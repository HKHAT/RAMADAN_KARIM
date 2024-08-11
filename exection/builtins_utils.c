/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:06 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/10 20:16:52 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_is_builtin(t_data data)
{
	char *builtins_str = "exit env pwd cd export unset echo";
	char **builtins;
	int i;

	if (data.cmd == NULL || data.cmd->av == NULL || data.cmd->av[0] == NULL)
		return 0;
	builtins = ft_split(builtins_str, ' ');
	if (!builtins)
		return 0;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(data.cmd->av[0], builtins[i]) == 0)
			return 1;
		i++;
	}
	return 0;
}

int execute_builtin(t_data *data)
{
	if (!ft_strcmp(data->cmd->av[0], "exit"))
		build_exit(data->cmd->av);
	else if (!ft_strcmp(data->cmd->av[0], "env"))
		build_env(data);
	else if (!ft_strcmp(data->cmd->av[0], "pwd"))
		build_pwd(data);
	else if (!ft_strcmp(data->cmd->av[0], "cd"))
		build_cd(data);
	else if (!ft_strcmp(data->cmd->av[0], "export"))
		build_export(data);
	else if (!ft_strcmp(data->cmd->av[0], "unset"))
		build_unset(data);
	else if (!ft_strcmp(data->cmd->av[0], "echo"))
		build_echo(data);
	return (data->exit_status);
}

void run_builtin(t_data *data, int *status)
{
	if (check_is_builtin(*data) == 1)
	{
		*status = execute_builtin(data);
	}
	else
		*status = 1;
	data->exit_status = *status;
}
