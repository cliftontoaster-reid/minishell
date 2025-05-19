/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:09:52 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/05/19 17:17:51 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <criterion/criterion.h>

Test(utils, is_builtin_null)
{
	cr_assert_not(is_builtin(NULL), "is_builtin(NULL) should return (false)");
}

Test(utils, is_builtin)
{
	t_command	cmd;

	cmd.flags = FLAG_BUILTIN;
	cr_assert(is_builtin(&cmd),
		"is_builtin should return (true) when FLAG_BUILTIN is set");
}

Test(utils, is_builtin_zero)
{
	t_command	cmd;

	cmd.flags = 0;
	cr_assert_not(is_builtin(&cmd),
		"is_builtin should return (false) when FLAG_BUILTIN is not set");
}

Test(utils, has_input_redirect_null)
{
	cr_assert_not(has_input_redirect(NULL),
		"has_input_redirect(NULL) should return (false)");
}

Test(utils, has_input_redirect)
{
	t_command	cmd;

	cmd.flags = FLAG_INPUT_REDIRECT;
	cr_assert(has_input_redirect(&cmd),
		"has_input_redirect should return (true) when FLAG_INPUT_REDIRECT is set");
}

Test(utils, has_input_redirect_zero)
{
	t_command	cmd;

	cmd.flags = 0;
	cr_assert_not(has_input_redirect(&cmd),
		"has_input_redirect should return (false) when FLAG_INPUT_REDIRECT is not set");
}

Test(utils, has_output_redirect_null)
{
	cr_assert_not(has_output_redirect(NULL),
		"has_output_redirect(NULL) should return (false)");
}

Test(utils, has_output_redirect)
{
	t_command	cmd;

	cmd.flags = FLAG_OUTPUT_REDIRECT;
	cr_assert(has_output_redirect(&cmd),
		"has_output_redirect should return (true) when FLAG_OUTPUT_REDIRECT is set");
}

Test(utils, has_output_redirect_zero)
{
	t_command	cmd;

	cmd.flags = 0;
	cr_assert_not(has_output_redirect(&cmd),
		"has_output_redirect should return (false) when FLAG_OUTPUT_REDIRECT is not set");
}

Test(utils, has_error_redirect_null)
{
	cr_assert_not(has_error_redirect(NULL),
		"has_error_redirect(NULL) should return (false)");
}

Test(utils, has_error_redirect)
{
	t_command	cmd;

	cmd.flags = FLAG_ERROR_REDIRECT;
	cr_assert(has_error_redirect(&cmd),
		"has_error_redirect should return (true) when FLAG_ERROR_REDIRECT is set");
}

Test(utils, has_error_redirect_zero)
{
	t_command	cmd;

	cmd.flags = 0;
	cr_assert_not(has_error_redirect(&cmd),
		"has_error_redirect should return (false) when FLAG_ERROR_REDIRECT is not set");
}

Test(utils, has_pipe_in_null)
{
	cr_assert_not(has_pipe_in(NULL), "has_pipe_in(NULL) should return (false)");
}

Test(utils, has_pipe_in)
{
	t_command	cmd;

	cmd.flags = FLAG_PIPE_IN;
	cr_assert(has_pipe_in(&cmd),
		"has_pipe_in should return (true) when FLAG_PIPE_IN is set");
}

Test(utils, has_pipe_in_zero)
{
	t_command	cmd;

	cmd.flags = 0;
	cr_assert_not(has_pipe_in(&cmd),
		"has_pipe_in should return (false) when FLAG_PIPE_IN is not set");
}

Test(utils, has_pipe_out_null)
{
	cr_assert_not(has_pipe_out(NULL),
		"has_pipe_out(NULL) should return (false)");
}

Test(utils, has_pipe_out)
{
	t_command	cmd;

	cmd.flags = FLAG_PIPE_OUT;
	cr_assert(has_pipe_out(&cmd),
		"has_pipe_out should return (true) when FLAG_PIPE_OUT is set");
}

Test(utils, has_pipe_out_zero)
{
	t_command	cmd;

	cmd.flags = 0;
	cr_assert_not(has_pipe_out(&cmd),
		"has_pipe_out should return (false) when FLAG_PIPE_OUT is not set");
}

Test(utils, has_soft_redirect_null)
{
	cr_assert_not(has_soft_redirect(NULL),
		"has_soft_redirect(NULL) should return (false)");
}

Test(utils, has_soft_redirect)
{
	t_command	cmd;

	cmd.flags = FLAG_SOFT_REDIRECT;
	cr_assert(has_soft_redirect(&cmd),
		"has_soft_redirect should return (true) when FLAG_SOFT_REDIRECT is set");
}

Test(utils, has_soft_redirect_zero)
{
	t_command	cmd;

	cmd.flags = 0;
	cr_assert_not(has_soft_redirect(&cmd),
		"has_soft_redirect should return (false) when FLAG_SOFT_REDIRECT is not set");
}
