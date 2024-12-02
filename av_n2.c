#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define FILENAME "tarefas.txt"

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char descricao[MAX_DESCRICAO];
    char status[20]; // "Pendente", "Em andamento", "Concluído"
    char data_criacao[20];
} Tarefa;

int main() {
    setlocale (LC_ALL, "Portuguese");
    Tarefa tarefas[MAX_TAREFAS];
    int total = carregarTarefas(tarefas);
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Criar Tarefa\n");
        printf("2. Listar Tarefas\n");
        printf("3. Atualizar Tarefa\n");
        printf("4. Deletar Tarefa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            criarTarefa(tarefas, &total);
            break;
        case 2:
            listarTarefas(tarefas, total);
            break;
        case 3:
            atualizarTarefa(tarefas, total);
            break;
        case 4:
            deletarTarefa(tarefas, &total);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
