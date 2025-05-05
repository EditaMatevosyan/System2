#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define NB_ARGUMENTS_MAX 10

int decouperCommande(char *commande, char *arguments[]) {
    int nbArguments = 0;
    int i = 0;
    while (commande[i] != '\0') {
        if (commande[i] == ' ') {
            commande[i] = '\0';
        } else if (
            (i == 0 || commande[i - 1] == '\0') &&
            commande[i] != '\0' &&
            nbArguments < NB_ARGUMENTS_MAX
        ) {
            arguments[nbArguments] = &commande[i];
            nbArguments++;
        }
        i++;
    }
    arguments[nbArguments] = NULL;
    return nbArguments;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s \"cmd1\" \"cmd2\" ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    int success_count = 0, failure_count = 0;

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return EXIT_FAILURE;
        }

        if (pid == 0) {
            // CHILD PROCESS
            char *args[NB_ARGUMENTS_MAX + 1];
            char cmd_copy[100];
            strncpy(cmd_copy, argv[i], sizeof(cmd_copy) - 1);
            cmd_copy[sizeof(cmd_copy) - 1] = '\0';

            int nbArgs = decouperCommande(cmd_copy, args);

            printf("Enfant %d [PID=%d] lance : %s\n", i, getpid(), args[0]);

            execvp(args[0], args);
            // If execvp fails:
            perror("execvp");
            exit(EXIT_FAILURE);
        }

        // PARENT PROCESS
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Parent : enfant PID=%d termine avec code %d\n", pid, exit_code);
            if (exit_code == EXIT_SUCCESS) success_count++;
            else failure_count++;
        }
    }

    printf("Bilan : %d succès, %d échecs\n", success_count, failure_count);
    return EXIT_SUCCESS;
}
