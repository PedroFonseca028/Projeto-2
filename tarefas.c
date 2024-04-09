#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    // Lopping para verificar se o numero da prioridade colocada pelo usuario é maior que 0 e menor que 11
    do{
        //Solicita a prioridade para o usuario
        printf("Entre com a prioridade:(Min: 1  Max: 10): ");
        scanf("%d", &tarefas[*pos].prioridade);
        clearBuffer();
        
        //Mostra ao usuario que o numero a ser digitado tem que maior que 0 e menor que 11
        if (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10){
        printf("O valor escrito deve ser entre 1 a 10\n");
        }
    } while (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10); 
      //Realiza o looping até a prioridade estar entre 1 e 10
    
    
    
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin);
    //Utilizado o 'Strtok' para remover o \n
    strtok(tarefas[*pos].categoria, "\n");

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);
    //Utilizado o 'Strtok' para remover o \n
    strtok(tarefas[*pos].descricao, "\n");

    *pos = *pos + 1;

    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    for(int i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
