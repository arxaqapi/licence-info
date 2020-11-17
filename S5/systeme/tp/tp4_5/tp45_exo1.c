#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <semaphore.h>

#define MAX_PROC 5
#define NB_TOURS 1

typedef struct msg
{
    pid_t emmeteur;
    const int value;
    int acc;
} msg_;

void proc(int mon_num, int ** tubes)
{   
    msg_ msg;
    // TODO Close unused pipe/write end
    // my pipe = tubes[0]
    close(tubes[mon_num][1]);
    read(tubes[mon_num][0], &msg, sizeof(msg_));
    // afficher info
    // int num = 0;
    printf("Processus de pid %d, n°%d dans l'anneau: j'envoie au n°%d l'info [ - - ]", getpid(), mon_num, mon_num + 1);
    // modifier info
    // pass message to next
    // attendre info

}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s Nombre de processus\n", argv[0]);
        exit(1);
    }
    int n_processes = atoi(argv[1]);
    // limit the numeber of process creation
    if (n_processes > MAX_PROC)
    {
        n_processes = MAX_PROC;
    }
    //init
    pid_t *processes = calloc(n_processes, sizeof(pid_t));
    
    // Create pipes
    int ** tubes = calloc(n_processes, sizeof(int *));
    for (int i = 0; i < n_processes; i++)
    {
        tubes[i] = calloc(2, sizeof(int));
        if (pipe(tubes[i]) == -1)
        {
            perror("Erreur création des pipes");
            exit(EXIT_FAILURE);
        }
    }
    // Activate pipes

    for (int i = 0; i < n_processes; i++)
    {
        switch (processes[i] = fork())
        {
            // child process
        case 0:
            proc(i, tubes);
            break;
        case -1:
            perror("Echec fork");
            exit(EXIT_FAILURE);
            break;
        }
    }

    // attendre la fin des processus fils
    while (wait(NULL) != -1)
        ;

    return 0;
}
