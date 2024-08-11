/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:36:21 by yozainan          #+#    #+#             */
/*   Updated: 2024/08/10 05:51:49 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmd_to_arg(Command *head)
{
	Command	*temp;

	temp = head;
	while (temp)
	{
		temp->av = ft_list_to_char(temp->cmd_lst, ft_lst_size(temp->cmd_lst));
		temp = temp->next;
	}
}

Command	*parse(Token *tokens)
{
	Command	*current;
	t_value	value;
	t_add	*data;

	data = ft_malloc(sizeof(t_add));
	value.flag = 0;
	value.i = 0;
	data->head = NULL;
	data->cmd_head = NULL;
	current = create_command();
	if (!current)
		return (NULL);
	while (tokens[value.i].type != TOKEN_END)
	{
		process_token(tokens, &value, &current, data);
	}
	if (current && (ft_lst_size(current->cmd_lst) > 0 || value.flag > 0))
	{
		add_cmd(&current->cmd_lst, data->cmd_head);
		add_command_to_list(&data->head, current);
	}
	add_cmd_to_arg(data->head);
	return (data->head);
}

int	ft_size(char **argv)
{
	int	i;

	if (argv == NULL)
		return (0);
	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}
