/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:33:48 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include "lexer.h"
# include "shared.h"
# include <criterion/criterion.h>
# include <errno.h>

// Common test utility functions for lexer
void		free_tok(void *token);
void		print_tokenlist(t_list *token_list);
t_token		*get_n_token(t_list *token_list, int n);
const char	*get_token_name(t_token_type type);
void		token_test(t_token *token, t_token_type type, char *value,
				char *name);

// Lexer-specific utility functions
void		print_tok(t_token *token);
void		print_tok_type(t_token_type type);

// Environment utility functions (shared across environment tests)
t_env		*find_env_var(t_list *env_list, const char *key);
void		free_env_data(void *content);

#endif
