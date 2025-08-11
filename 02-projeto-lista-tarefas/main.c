#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct tarefa {
    char descricao[100];
    int concluida;
    struct tarefa *proxima;
};

void adicionar_tarefa(struct tarefa **cabeca, const char *descricao);
void destruir_lista(struct tarefa **cabeca);
void listar_tarefas(struct tarefa *cabeca);

int main() {
    struct tarefa *lista_de_tarefas = NULL;

    printf("Bem-vindo ao Gerenciador de Tarefas!\n");

    adicionar_tarefa(&lista_de_tarefas, "Estudar listas encadeadas em C");
    adicionar_tarefa(&lista_de_tarefas, "Comprar pão");

    listar_tarefas(lista_de_tarefas);

    destruir_lista(&lista_de_tarefas);

    return 0;
}

void adicionar_tarefa(struct tarefa **cabeca, const char *descricao) {
    struct tarefa *nova_tarefa;
    if(!(nova_tarefa = malloc(sizeof(struct tarefa)))){
        printf("Falha ao alocar nova tarefa.\n");
        return;
    }

    nova_tarefa->concluida = 0;
    strncpy(nova_tarefa->descricao, descricao, sizeof(nova_tarefa->descricao) - 1);
    nova_tarefa->descricao[sizeof(nova_tarefa->descricao) - 1] = '\0';
    nova_tarefa->proxima = *cabeca;
    *cabeca = nova_tarefa;

    return;
}

void listar_tarefas(struct tarefa *cabeca){
    struct tarefa *atual = cabeca;

    while(atual){
        printf("Tarefa atual: %s\n", atual->descricao);
        atual = atual->proxima;
    }

    return;
}

void destruir_lista(struct tarefa **cabeca){
    struct tarefa *atual = *cabeca;
    struct tarefa *temp;

    while(atual){
        temp = atual;
        atual = atual->proxima;
        free(temp);
    }

    (*cabeca) = NULL;
    return;
}