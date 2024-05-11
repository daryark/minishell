/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:44 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/11 19:12:30 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <stdio.h>

static void minishell_loop(t_mshell *mshell) {
    char *input;

    while (1) {
        input = readline(YELLOW "Minishell>" RE);

        if (!input || *input == '\0') {
            printf("Exiting...\n");
            // free(input);
            continue;
        }
        add_history(input);
        if (input[0] == '1' && !input[1])   //*temporary exit
        {
            printf("%sexit%s\n", YELLOW, RE);
            free(input);
            exit(0);
        }                                  //*
        parse_input(input, mshell);
        free(input);
    }
}

int main(int ac, char **av, char **envp)
{
    t_mshell    mshell;

    (void)av;
    if (ac != 1)
        exit(write(1, RED "No arguments accepted!\n" RE, 32));
    else {
        write(1, GREEN "OK\n" RE, 14);
        init_mshell(&mshell, envp);
        minishell_loop(&mshell);
    }
    return 0;
}
