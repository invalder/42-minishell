/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:17:37 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/07 14:47:17 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_sh.h"

t_main_meta	g_meta;

// size_t gpt_strspn(const char *str, const char *accept)
// {
// 	size_t count = 0;

// 	while (*str)
// 	{
// 		// printf("check: %c\n", *str);
// 		if (!ft_strchr(accept, *str))
// 			break ;
// 		// if (ft_strchr(SYMBOLS, *str))
// 		// 	break ;
// 		str++;
// 		count++;
// 	}

// 	return count;
// }

// size_t gpt_strcspn(const char *str, const char *reject)
// {
// 	size_t	count;

// 	count = 0;
// 	while (*str)
// 	{
// 		if (!ft_strncmp(str, "\"", 1))
// 		{
// 			str++;
// 			count++;
// 			while (ft_strncmp(str, "\"", 1))
// 			{
// 				str++;
// 				count++;
// 			}
// 			str++;
// 			count++;
// 		}
// 		if (!ft_strncmp(str, "\'", 1))
// 		{
// 			str++;
// 			count++;
// 			while (ft_strncmp(str, "\'", 1))
// 			{
// 				str++;
// 				count++;
// 			}
// 			str++;
// 			count++;
// 		}
// 		if (!ft_strncmp(str, "(", 1))
// 		{
// 			str++;
// 			count++;
// 			while (ft_strncmp(str, ")", 1))
// 			{
// 				str++;
// 				count++;
// 			}
// 			str++;
// 			count++;
// 		}
// 		if (ft_strchr(reject, *str))
// 			break ;
// 		str++;
// 		count++;
// 	}
// 	return count;
// }

// char *gpt_strtok(char *str, const char *delim)
// {
// 	static char	*last_str = NULL;
// 	char		*end;

// 	end = NULL;
// 	if (str == NULL)
// 	{
// 		str = last_str;
// 		if (str == NULL)
// 			return NULL;
// 	}
// 	str += gpt_strspn(str, delim);
// 	if (*str == '\0')
// 	{
// 		last_str = NULL;
// 		return NULL;
// 	}
// 	end = str + gpt_strcspn(str, delim);
// 	if (*end == '\0')
// 		last_str = NULL;
// 	else
// 	{
// 		*end = '\0';
// 		last_str = end + 1;
// 	}
// 	return str;
// }

// char	**ft_split_input_line(char *input)
// {
// 	int		buf_size;
// 	int		pos;
// 	char	*token;
// 	char	**tokens;

// 	pos = 0;
// 	token = NULL;
// 	buf_size = TOKENBUF;
// 	tokens = malloc(sizeof(char *) * buf_size);
// 	if (!tokens)
// 		exit_err("Allocation Error\n", EXIT_FAILURE);
// 	token = gpt_strtok(input, DLM);
// 	while (token)
// 	{
// 		tokens[pos++] = token;
// 		if (pos >= buf_size)
// 		{
// 			buf_size += TOKENBUF;
// 			tokens = ft_realloc(tokens, sizeof(char *) * buf_size);
// 			if (!tokens)
// 				exit_err("Allocation Error\n", EXIT_FAILURE);
// 		}
// 		token = gpt_strtok(NULL, DLM);
// 	}
// 	tokens[pos] = NULL;
// 	return (tokens);
// }
// void	get_prev_token_shift(char **es, char **input, char **tokens, int *pos)
// {

// }

void	get_prev_token(char **es, char **input, char **tokens, int *pos)
{
	char	*tmp;

	tmp = NULL;
	if (*input < *es)
	{
		tmp = malloc(sizeof(char *) * (*es - *input + 1));
		if (!tmp)
			exit_err("Allocation Error\n", EXIT_FAILURE);
		ft_strlcpy(tmp, *input, *es - *input + 1);
		tokens[*pos] = tmp;
		*pos += 1;
		*input = *es;
		tmp = NULL;
	}
	*es += 1;
}

void	get_prev_token_shift(char **es, char **input, char **tokens, int *pos)
{
	char	*tmp;

	tmp = NULL;
	if (*input < *es)
	{
		tmp = malloc(sizeof(char *) * (*es - *input + 1));
		if (!tmp)
			exit_err("Allocation Error\n", EXIT_FAILURE);
		ft_strlcpy(tmp, *input, *es - *input + 1);
		tokens[*pos] = tmp;
		*pos += 1;
		*input = *es + 1;
		tmp = NULL;
	}
}

void	until_next_dquote(char **es, char **input, char **tokens, int *pos)
{
	char	*tmp;

	while (ft_strncmp(*es, "\"", 1) && **es)
		*es += 1;
	// if (!ft_strncmp(*es + 1, " ", 1) || !ft_strncmp(*es + 1, "|", 1) || !ft_strncmp(*es + 1, ">", 1) || !ft_strncmp(*es + 1, "<", 1))
	// {
	printf("es: %s\n", *es);
	tmp = malloc(sizeof(char *) * (*es - *input + 2));
	if (!tmp)
		exit_err("Allocation Error\n", EXIT_FAILURE);
	ft_strlcpy(tmp, *input, *es - *input + 2);
	tokens[*pos] = tmp;
	*pos += 1;
	*input = *es + 1;
	*es += 1;
	tmp = NULL;
	// }
	// else
	// 	until_next_dquote(es, input, tokens, pos);
}

void	until_next_quote(char **es, char **input, char **tokens, int *pos)
{
	char	*tmp;

	while (ft_strncmp(*es, "\'", 1) && **es)
		*es += 1;
	tmp = malloc(sizeof(char *) * (*es - *input + 2));
	if (!tmp)
		exit_err("Allocation Error\n", EXIT_FAILURE);
	ft_strlcpy(tmp, *input, *es - *input + 2);
	tokens[*pos] = tmp;
	*pos += 1;
	*input = *es + 1;
	*es += 1;
	tmp = NULL;
}

char	**ft_split_input(char *input)
{
	char	**tokens;
	char	*tmp;
	char	*es;
	int		buf_size;
	int		pos;

	pos = 0;
	tmp = NULL;
	buf_size = TOKENBUF;
	tokens = malloc(sizeof(char *) * buf_size);
	if (!tokens)
		exit_err("Allocation Error\n", EXIT_FAILURE);
	es = input;
	while (*es)
	{
		if (pos + 1 >= buf_size)
		{
			buf_size *= 2;
			tokens = ft_realloc_tokens(tokens, sizeof(char *) * buf_size);
			if (!tokens)
				exit_err("Allocation Error\n", EXIT_FAILURE);
		}
		if (!ft_strncmp(es, "\"", 1))
		{
			get_prev_token(&es, &input, tokens, &pos);
			if (ft_strchr(es, '\"'))
			{
				until_next_dquote(&es, &input, tokens, &pos);
				continue ;
			}
		}
		if (!ft_strncmp(es, "\'", 1))
		{
			get_prev_token(&es, &input, tokens, &pos);
			if (ft_strchr(es, '\''))
			{
				until_next_quote(&es, &input, tokens, &pos);
				continue ;
			}
		}
		if (!ft_strncmp(es, "|", 1))
		{
			get_prev_token_shift(&es, &input, tokens, &pos);
			if (*(es + 1) == '|')
			{
				tmp = malloc(sizeof(char *) * (3));
				if (!tmp)
					exit_err("Allocation Error\n", EXIT_FAILURE);
				ft_strlcpy(tmp, "||", 3);
				tokens[pos++] = tmp;
				input = es + 2;
				es += 2;
				tmp = NULL;
			}
			else
			{
				tmp = malloc(sizeof(char *) * (2));
				if (!tmp)
					exit_err("Allocation Error\n", EXIT_FAILURE);
				ft_strlcpy(tmp, "|", 2);
				tokens[pos++] = tmp;
				input = es + 1;
				es += 1;
				tmp = NULL;
			}
			continue ;
		}
		if (!ft_strncmp(es, "<", 1))
		{
			get_prev_token_shift(&es, &input, tokens, &pos);
			if (*(es + 1) == '<')
			{
				tmp = malloc(sizeof(char *) * (3));
				if (!tmp)
					exit_err("Allocation Error\n", EXIT_FAILURE);
				ft_strlcpy(tmp, "<<", 3);
				tokens[pos++] = tmp;
				input = es + 2;
				es += 2;
				tmp = NULL;
			}
			else
			{
				tmp = malloc(sizeof(char *) * (2));
				if (!tmp)
					exit_err("Allocation Error\n", EXIT_FAILURE);
				ft_strlcpy(tmp, "<", 2);
				tokens[pos++] = tmp;
				input = es + 1;
				es += 1;
				tmp = NULL;
			}
			continue ;
		}
		if (!ft_strncmp(es, ">", 1))
		{
			get_prev_token_shift(&es, &input, tokens, &pos);
			if (*(es + 1) == '>')
			{
				tmp = malloc(sizeof(char *) * (3));
				if (!tmp)
					exit_err("Allocation Error\n", EXIT_FAILURE);
				ft_strlcpy(tmp, ">>", 3);
				tokens[pos++] = tmp;
				input = es + 2;
				es += 2;
				tmp = NULL;
			}
			else
			{
				tmp = malloc(sizeof(char *) * (2));
				if (!tmp)
					exit_err("Allocation Error\n", EXIT_FAILURE);
				ft_strlcpy(tmp, ">", 2);
				tokens[pos++] = tmp;
				input = es + 1;
				es += 1;
				tmp = NULL;
			}
			continue ;
		}
		if (!ft_strncmp(es, " ", 1))
		{
			get_prev_token_shift(&es, &input, tokens, &pos);
			if (input >= es)
			{
				while (*es == ' ' && *es)
					es++;
				input = es;
			}
			continue ;
		}
		es++;
	}
	tmp = malloc(sizeof(char *) * (es - input + 2));
	if (!tmp)
		exit_err("Allocation Error\n", EXIT_FAILURE);
	ft_strlcpy(tmp, input, es - input + 2);
	tokens[pos++] = tmp;
	tokens[pos] = NULL;
	return (tokens);
}

int	cmd_loop(t_main_meta *meta, char **envp)
{
	char	**tokens;
	char	**ptokens;

	(void) envp;
	tokens = NULL;
	while (1)
	{
		while (ft_read_line(&meta->line, meta->pmt))
		{
			if (is_comment_line(meta->line))
				break ;
			if (!is_heredoc(&meta->line, &meta->input))
				break ;
			else
				ft_multiline_cmd(meta);
		}
		if (!meta->input || !ft_strncmp(meta->input, "exit\0", 5))
			exit_eof(meta);
		add_history(meta->input);
		meta->tinput = ft_strtrim(meta->input, WHTSP);
		tokens = ft_split_input(meta->tinput);
		ptokens = tokens;
		while (*ptokens)
		{
			printf("token: %s\n", *ptokens);
			ptokens++;
		}
		meta_dealloc_input(meta);
		meta->pmt = PROMPT;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	g_meta.parent.pid = getpid();
	sa_initialize();
	meta_init(&g_meta);
	cmd_loop(&g_meta, envp);
}
