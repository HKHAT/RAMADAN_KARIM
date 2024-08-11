/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elchakir <elchakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:20:21 by elchakir          #+#    #+#             */
/*   Updated: 2024/08/11 02:51:58 by elchakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int init_buffer(t_expand *ex) 
{
    ex->result_size = 256;
    ex->temp_result = calloc(ex->result_size, sizeof(char));
    if (ex->temp_result == NULL) 
	{
        perror("calloc");
        return -1;
    }
    return 0;
}

int resize_buffer(char **buffer, size_t *current_size, size_t used_size) {
    char *new_buffer;

	*current_size *= 2;
	new_buffer = calloc(*current_size, sizeof(char));
    if (new_buffer == NULL) {
        perror("calloc");
        return -1;
    }
    memcpy(new_buffer, *buffer, used_size);
    free(*buffer);
    *buffer = new_buffer;
    return 0;
}

int safe_strncpy(char **dest, t_expand *ex, const char *src) 
{
    if (ex->used_size + ex->len >= ex->result_size) 
	{
        if (resize_buffer(dest, &ex->result_size, ex->used_size) != 0)
            return -1;
    }
    memcpy(*dest + (size_t)(ex->used_size), src, ex->len);
    ex->used_size += ex->len;
    return 0;
}

int handle_dollar_variable(t_expand *ex, char **p, t_data *data) {
    char *tmp = ft_itoa(data->pid);
    if (tmp == NULL) {
        return -1; // Handle memory allocation failure
    }
    ex->len = strlen(tmp);
    if (safe_strncpy(&ex->temp_result, ex, tmp) != 0) {
        free(tmp);
        return -1;
    }
    free(tmp);
    (*p)++;
    return 0;
}


int handle_variable_expansion(t_expand *ex, char **p, const char *start, t_data *data) 
{
    char *expanded;
	expanded = expand_variable(start, *p - start, data->env_list);
    if (expanded == NULL) {
        return -1; // Handle memory allocation failure
    }
    ex->len = strlen(expanded);
    if (safe_strncpy(&ex->temp_result, ex, expanded) != 0) {
        free(expanded);
        return -1;
    }
    free(expanded);
    return 0;
}

int expand_variable_in_strr(t_expand *ex, char **p, t_data *data) {
    const char *start;
	start = *p;
    if (**p == '$') {
        return handle_dollar_variable(ex, p, data);
    } else {
        while (isalnum(**p) || **p == '_') {
            (*p)++;
        }
        return handle_variable_expansion(ex, p, start, data);
    }
}


int process_segment(char *str, t_expand *ex, t_data *data) 
{
    char *p;
	p = ft_strrch_finder(str, '$');
    if (p == NULL) {
        ex->len = strlen(str);
        return safe_strncpy(&ex->temp_result, ex, str);
    }
    ex->len = p - str;
    if (safe_strncpy(&ex->temp_result, ex, str) != 0) {
        return -1;
    }
    p++;
    if (expand_variable_in_strr(ex, &p, data) != 0) {
        return -1;
    }
    return process_segment(p, ex, data);
}

void find_when_start(char *str, t_data *data, char **result)
{
    t_expand ex;
    int status;
	ex.result_size = 0;
	ex.used_size = 0;
	ex.len = 0;
	ex.temp_result = NULL;
    if (init_buffer(&ex) != 0) {
        return;
    }
    status = process_segment(str, &ex, data);
    if (status != 0) {
        free(ex.temp_result);
        return;
    }
    *result = ex.temp_result;
}


void	check_limit_her_doc(Redirection *redir)
{
	Redirection	*tmp_redir;
	int			counter;

	tmp_redir = redir;
	counter = 0;
	while (tmp_redir)
	{
		if (tmp_redir->type == TOKEN_HERE_DOC
			|| tmp_redir->type == TOKEN_HERE_DOC_NO)
			counter++;
		tmp_redir = tmp_redir->next;
	}
	if (counter > 16)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n",
			STDERR_FILENO);
		exit(2);
	}
}
