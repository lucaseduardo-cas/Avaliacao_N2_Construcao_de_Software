#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_TAREFAS 100
#define MAX_TITULO 50
#define MAX_DESCRICAO 100
#define FILENAME "tarefas.txt"

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char descricao[MAX_DESCRICAO];
    char status[20]; // "Pendente", "Em andamento", "Concluído"
    char data_criacao[20];
} Tarefa;

// Função para obter o timestamp atual
void obterDataAtual(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%d %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}

// Função para salvar todas as tarefas no arquivo
void salvarTarefas(Tarefa tarefas[], int total) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para salvar tarefas.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        fprintf(file, "%d|%s|%s|%s|%s\n", tarefas[i].id, tarefas[i].titulo, tarefas[i].descricao, tarefas[i].status, tarefas[i].data_criacao);
    }
    fclose(file);
}

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
