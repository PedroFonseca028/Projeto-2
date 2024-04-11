#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK){
        printf("Erro encontrado");
        pos = 0;
        switch (erro){
        case MAX_TAREFA:
            printf("Numero maximo de tarefas atingido\n"); 
            break;
        case SEM_TAREFAS:
            printf("Não há tarefas\n"); 
            break;
        case NAO_ENCONTRADO:
            printf("Tarefas não encontrada\n"); 
            break;
        default:
            break;
        }
    }
     

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        opcao--;
        if(opcao > 2)
            printf("Opcao invalida\n");
        else if(opcao >= 0)
            fs[opcao](tarefas, &pos);
        else
            printf("Sair...\n");

    } while(opcao >= 0);

    fs[3](tarefas, &pos);
}
