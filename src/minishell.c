/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyarkovs <dyarkovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:44 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/07 18:08:33 by dyarkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <stdio.h>


void minishell_loop(void) {
    char *input;

    while (1) {
        input = readline(YELLOW "Minishell: " RE);

        if (!input || *input == '\0') {
            // If input is NULL or empty, break out of the loop
            printf("Exiting...\n");
            free(input);  // Freeing if input is NULL is safe
            continue;
        }

        add_history(input);  // Add input to history
        printf("You entered: %s\n", input);
        free(input);  // Free memory allocated by readline
    }
}

int main(int ac, char **av, char **envp) {
    (void)av;
    (void)envp;
    if (ac != 1)
        exit(write(1, RED "No arguments accepted!\n" RE, 32));
    else {
        write(1, GREEN "OK\n" RE, 14);
        minishell_loop();
    }
    return 0;
}
