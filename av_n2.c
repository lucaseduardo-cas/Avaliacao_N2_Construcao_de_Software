#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_TAREFAS 100
#define MAX_TITULO 50
#define MAX_DESCRICAO 100
#define FILENAME "tarefas.txt"

// Estrutura da Tarefa
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

// Função para carregar tarefas do arquivo
int carregarTarefas(Tarefa tarefas[]) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 0; // Arquivo ainda não existe
    }
    int total = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", &tarefas[total].id, tarefas[total].titulo, tarefas[total].descricao, tarefas[total].status, tarefas[total].data_criacao) != EOF) {
        total++;
    }
    fclose(file);
    return total;
}

// Criar uma nova tarefa
void criarTarefa(Tarefa tarefas[], int *total) {
    if (*total >= MAX_TAREFAS) {
        printf("Limite de tarefas alcançado.\n");
        return;
    }
    Tarefa nova;
    nova.id = (*total > 0) ? tarefas[*total - 1].id + 1 : 1;
    printf("Digite o título da tarefa: ");
    getchar(); // Limpar buffer
    fgets(nova.titulo, MAX_TITULO, stdin);
    nova.titulo[strcspn(nova.titulo, "\n")] = '\0'; // Remover quebra de linha

    printf("Digite a descrição da tarefa: ");
    fgets(nova.descricao, MAX_DESCRICAO, stdin);
    nova.descricao[strcspn(nova.descricao, "\n")] = '\0';

    strcpy(nova.status, "Pendente");
    obterDataAtual(nova.data_criacao);

    tarefas[*total] = nova;
    (*total)++;
    salvarTarefas(tarefas, *total);
    printf("Tarefa criada com sucesso!\n");
}

// Listar todas as tarefas
void listarTarefas(Tarefa tarefas[], int total) {
    if (total == 0) {
        printf("Nenhuma tarefa encontrada.\n");
        return;
    }
    printf("\nLista de Tarefas:\n");
    for (int i = 0; i < total; i++) {
        printf("ID: %d\nTítulo: %s\nDescrição: %s\nStatus: %s\nData de criação: %s\n\n",
               tarefas[i].id, tarefas[i].titulo, tarefas[i].descricao, tarefas[i].status, tarefas[i].data_criacao);
    }
}

// Atualizar o status de uma tarefa
void atualizarTarefa(Tarefa tarefas[], int total) {
    int id, encontrado = 0;
    printf("Digite o ID da tarefa para atualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++) {
        if (tarefas[i].id == id) {
            encontrado = 1;
            printf("Digite o novo status (Pendente, Em andamento, Concluído): ");
            getchar();
            fgets(tarefas[i].status, 20, stdin);
            tarefas[i].status[strcspn(tarefas[i].status, "\n")] = '\0';
            salvarTarefas(tarefas, total);
            printf("Tarefa atualizada com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Tarefa não encontrada.\n");
    }
}

// Deletar uma tarefa
void deletarTarefa(Tarefa tarefas[], int *total) {
    int id, encontrado = 0;
    printf("Digite o ID da tarefa para deletar: ");
    scanf("%d", &id);

    for (int i = 0; i < *total; i++) {
        if (tarefas[i].id == id) {
            encontrado = 1;
            for (int j = i; j < *total - 1; j++) {
                tarefas[j] = tarefas[j + 1];
            }
            (*total)--;
            salvarTarefas(tarefas, *total);
            printf("Tarefa deletada com sucesso!\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Tarefa não encontrada.\n");
    }
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
