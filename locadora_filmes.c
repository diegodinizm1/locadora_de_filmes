#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// funções usadas

void menu();

void adicionar_filme(char *nome, char *genero, int ano, float preço);

void cadastrar_filme();

void imprimir_nome(char *nome);

void imprimir_genero(char *genero);

void imprimir_ano(int ano);

void imprimir();

void buscar_filme();

void remover_filme();

void atualizar_filme();

void adicionar_filmes_exemplos();

// ------------------------------------------------------------------------------------------ //
typedef struct no{
    char *nome; //Nome do filme
    char *genero; //Genero do filme
    int ano; //Ano de lançamento do filme
    float preço; // Preço do filme
    struct no *prox; // Ponteiro pro próximo
    struct no *ant; // Ponteiro pro anterior
}filmes; //nome do nó


filmes *inicio = NULL;
filmes *fim = NULL;
int tam = 0;

void menu(){ //menu de opções para o usuário
    int op;
    printf("\nLocadora Netflixo.\n");
    printf("O que deseja fazer:\n");
    printf("1 - Adicionar um filme ao catálogo.\n");
    printf("2 - Procurar por um filme.\n");
    printf("3 - Remover um filme.\n");
    printf("4 - Atualizar um filme.\n");
    printf("5 - Sair.\n");
    scanf("%d", &op);
    getchar(); // limpa o buffer
    if(op == 1){
        cadastrar_filme();
    }else if(op == 2){
        printf("\nComo você deseja buscar o filme?\n");
        buscar_filme();
    }else if(op == 3){
        remover_filme();
    }else if(op == 4){
        atualizar_filme();
    }else if (op == 5){
        return;
    }else{
        printf("Opção inválida.\n");
        menu(); // se digitar uma opção errada, volta para o menu.
    }
    
}

void buscar_filme(){ //buscar o filme na lista
    int op;
    printf("1 - Nome.\n");
    printf("2 - Gênero.\n");
    printf("3 - Ano de lançamento.\n");
    printf("4 - Listar todos.\n");
    printf("5 - Voltar.\n");
    scanf("%d", &op);
    getchar();
    if (op == 1){
        char nome[100];
        printf("Qual o nome do filme que deseja procurar?\n");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';
        imprimir_nome(nome);
    }else if(op == 2){
        char genero[100];
        printf("Qual o gênero do filme que deseja procurar?\n");
        fgets(genero, sizeof(genero), stdin);
        genero[strcspn(genero, "\n")] = '\0';
        imprimir_genero(genero);
    }else if(op == 3){
        int ano;
        printf("Qual o ano de lançamento do filme que deseja procurar?\n");
        scanf("%d", &ano);
        getchar();
    }else if(op == 4){
        printf("\nTodos os filmes disponíveis:\n");
        imprimir();
    }else if(op == 5){
        menu(); // se digitar uma opção errada, volta para o menu. 
    }
}

void cadastrar_filme(){
    char nome[100];
    char genero[100];
    int ano;
    float preço;
    
    printf("\nQual o nome do filme que deseja cadastrar?\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    printf("Qual o gênero do filme?\n");
    fgets(genero, sizeof(genero), stdin);
    genero[strcspn(genero, "\n")] = '\0';
    
    printf("Qual o ano de lançamento?\n");
    scanf("%d", &ano);
    getchar();
    
    printf("Por fim, qual o preço do filme?\n");
    scanf("%f", &preço);
    getchar();
    
     if (ano < 1900 || ano > 2100) {
        printf("Ano inválido. Deve estar entre 1900 e 2100.\n"); // checo a validade do ano.
        menu();
    }

    if (preço < 0) {
        printf("Preço inválido. Deve ser um valor positivo.\n");
        menu();
    }
    
    adicionar_filme(nome, genero, ano, preço);
    menu();
    
}

void adicionar_filme(char *nome, char *genero, int ano, float preço){
    filmes *novo = malloc(sizeof(filmes)); //aloco memória pro nó do filme.
    novo->nome = strdup(nome); // duplico o nome do filme para não causar problema de memória.
    novo->genero = strdup(genero); // o mesmo com o genero.
    novo->ano = ano; 
    novo->preço = preço;
    novo->prox = NULL;
    novo->ant = NULL;

    if(inicio == NULL){ //quando a lista estiver vazia.
        inicio = novo;
        fim = novo;
        tam++;
    }else if(ano>inicio->ano){ // adicionar no ínicio.
        novo->prox = inicio;
        inicio->ant = novo;
        inicio = novo;
    }else if(ano<fim->ano){ // adicionar no fim.
        fim->prox = novo;
        novo->ant = fim;
        fim = novo;
    }else{ // adicionar no meio.
        filmes *aux = inicio;
        while (aux != NULL && aux->ano > ano){
            aux = aux->prox;
        }
        novo->prox = aux;
        aux->ant->prox = novo;
        novo->ant = aux->ant;
        aux->ant = novo;
    }
    tam++;
}

void atualizar_filme(){
    char nome[100];
    filmes *aux = inicio;
    while(aux != NULL){
        printf("\n%s | Genero : %s | Lançamento : %d | Preço : R$%.2f\n", aux->nome, aux->genero, aux->ano, aux->preço);
        aux = aux->prox;
    } // imprimo todos os filmes para o usuário saber qual filme procurar.
    
    aux = inicio; //volto o ponteiro aux para o ínicio.
    
    printf("\n\nQual o nome do filme que deseja atualizar?\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    

    
    while(aux != NULL) { // se existir o nó
        if(strcmp(aux->nome, nome) == 0) { 
            printf("\nFilme encontrado!\n");
            printf("Nome atual: %s\n", aux->nome);
            printf("Genero atual: %s\n", aux->genero);
            printf("Ano de lançamento atual: %d\n", aux->ano);
            printf("Preço atual: R$%.2f\n", aux->preço);

            printf("\nDigite o novo nome do filme (ou pressione ENTER para manter o atual):\n");
            char novo_nome[100];
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = '\0';
            if (strlen(novo_nome) > 0) {
                free(aux->nome);
                aux->nome = strdup(novo_nome);
            }

            printf("Digite o novo gênero do filme (ou pressione ENTER para manter o atual):\n");
            char novo_genero[100];
            fgets(novo_genero, sizeof(novo_genero), stdin);
            novo_genero[strcspn(novo_genero, "\n")] = '\0';
            if (strlen(novo_genero) > 0) {
                free(aux->genero);
                aux->genero = strdup(novo_genero);
            }

            printf("Digite o novo ano de lançamento (ou pressione 0 para manter o atual):\n");
            int novo_ano;
            scanf("%d", &novo_ano);
            getchar();
            if (novo_ano != 0) {
                if (novo_ano >= 1900 && novo_ano <= 2100) {
                    aux->ano = novo_ano;
                } else {
                    printf("Ano inválido. Mantendo o ano atual.\n");
                }
            }

            printf("Digite o novo preço (ou pressione -1 para manter o atual):\n");
            float novo_preco;
            scanf("%f", &novo_preco);
            getchar();
            if (novo_preco >= 0) {
                aux->preço = novo_preco;
            }

            printf("\nFilme atualizado com sucesso!\n");
            menu();
        }
        aux = aux->prox; // passo o aux pro próx.
    }
    
    printf("\nFilme não encontrado.\n"); 
    menu(); // se o filme não for encontrado retorna pro menu.
}


void imprimir() { //imprimir todos os filmes da lista.
    int op = -1;
    filmes *aux = inicio;
    while (aux != NULL) {
        printf("\n%s | Genero : %s | Lançamento : %d | Preço : R$%.2f\n", aux->nome, aux->genero, aux->ano, aux->preço);
        aux = aux->prox;
    }
    if(inicio == NULL){
        printf("Não há nenhum filme disponível.\n");
        menu();
    }
    printf("\nPara sair, digite qualquer número.\n");
    scanf("%d", &op);
    if (op != -1){
        menu();
    }
}

void imprimir_nome(char *nome) { // imprimir o filme por nome.
    int op = -1;
    filmes *aux = inicio;
    while(aux != NULL) {
        if(strcmp(aux->nome, nome) == 0) {
            printf("\n%s | Genero : %s | Lançamento : %d | Preço : R$%.2f\n", aux->nome, aux->genero, aux->ano, aux->preço);
            return;
        }
        aux = aux->prox;
    }
    printf("Filme não encontrado.\n");
    menu();
    
    printf("\nPara sair digite qualquer número\n");
    scanf("%d", &op);
    if (op != -1){
        menu();
    }
}

void imprimir_genero(char *genero) { // imprimir os filmes por genero.
    int encontrado = 0;
    filmes *aux = inicio;
    while(aux != NULL) {
        if(strcmp(aux->genero, genero) == 0) {
            printf("\n%s | Genero : %s | Lançamento : %d | Preço : R$%.2f\n", aux->nome, aux->genero, aux->ano, aux->preço);
            encontrado = 1;
        }
        aux = aux->prox;
    }
    if (!encontrado) {
        printf("Nenhum filme encontrado no gênero %s.\n", genero);
        menu();
    }
    
    printf("\nPara sair digite qualquer número\n");
    int op;
    scanf("%d", &op);
    if (op != -1){
        menu();
    }
}
void imprimir_ano(int ano) { // imprimir o filme pelo ano de lançamento.
    int encontrado = 0;
    filmes *aux = inicio;
    while(aux != NULL) {
        if(aux->ano == ano) {
            printf("\n%s | Genero : %s | Lançamento : %d | Preço : R$%.2f\n", aux->nome, aux->genero, aux->ano, aux->preço);
            encontrado = 1;
        }
        aux = aux->prox;
    }
    if (!encontrado) {
        printf("Nenhum filme encontrado do ano %d.\n", ano);
        menu();
    }
    
    printf("\nPara sair digite qualquer número\n");
    int op;
    scanf("%d", &op);
    if (op != -1){
        menu();
    }
}

void remover_filme(char *nome) {
    filmes *aux = inicio;

    if (aux == NULL) {
        printf("Não há filmes disponíveis para remover.\n");
        menu();
        return;
    }

    printf("\nLista de filmes disponíveis:\n");
    while (aux != NULL) {
        printf("%s | Genero : %s | Lançamento : %d | Preço : R$%.2f\n", aux->nome, aux->genero, aux->ano, aux->preço);
        aux = aux->prox;
    }

    printf("\nQual o nome do filme que deseja remover?\n");
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    filmes *lixo = inicio;
    while (lixo != NULL && strcmp(lixo->nome, nome) != 0) {
        lixo = lixo->prox;
    }

    if (lixo == NULL) {
        printf("Filme não encontrado.\n");
        menu();
        return;
    }

    if (lixo == inicio) {
        inicio = lixo->prox;
        if (inicio != NULL) {
            inicio->ant = NULL;
        }
    } else {
        lixo->ant->prox = lixo->prox;
    }

    if (lixo == fim) {
        fim = lixo->ant;
        if (fim != NULL) {
            fim->prox = NULL;
        }
    } else {
        if (lixo->prox != NULL) {
            lixo->prox->ant = lixo->ant;
        }
    }

    printf("\nFilme removido: %s.\n", lixo->nome);
    free(lixo->nome);
    free(lixo->genero);
    free(lixo);

    tam--;
    menu();
}

void adicionar_filmes_exemplos(){ //adiciono filmes de exemplo na lista.
    adicionar_filme("Vingadores: Ultimato", "Ação", 2019, 22.0);
    adicionar_filme("Corra!", "Suspense", 2017, 8.0);
    adicionar_filme("Interestelar", "Ficção Científica", 2014, 14.0);
    adicionar_filme("Pulp Fiction", "Crime", 1994, 11.0);
    adicionar_filme("O Iluminado", "Terror", 1980, 9.0);
}

int main(){
    adicionar_filmes_exemplos();
    menu();
    return 0;
}