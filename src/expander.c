/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 20:47:15 by mpedraza          #+#    #+#             */
/*   Updated: 2026/03/20 20:52:01 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Expander
// - expand $VAR
// - expand $?
// do not expand inside single quotes - leave as is
// do expand inside double quotes - replace as needed
// always remove quote characters from the final result
// process:
// iterate over args in commands and expand
// iterate over targets in redirs and expand
// if a variable does not exist it is replaced with "" empty string
// FIGURE OUT: $? - how do I get the exit code and how to I store it?
// tip: Use state machine for tracking quotes (like so_long)