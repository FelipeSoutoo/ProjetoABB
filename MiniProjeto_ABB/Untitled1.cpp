#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct aluno{
    int rgm;
    char nome[100];
}t_aluno;

typedef struct no{
    t_aluno aluno;
    struct no *esquerda;
    struct no *direita;
}t_no;

t_no* criarNo(t_aluno aluno){
    t_no* novoNo = (t_no*)malloc(sizeof(t_no));
    novoNo->aluno = aluno;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

t_no* inserirNo(t_no* raiz, t_aluno aluno){
    if (raiz == NULL)
        return criarNo(aluno);
    
    if (aluno.rgm < raiz->aluno.rgm)
        raiz->esquerda = inserirNo(raiz->esquerda,aluno);
    else if (aluno.rgm > raiz->aluno.rgm)
        raiz->direita = inserirNo(raiz->direita,aluno);
    return raiz;
}

t_no* menorNo(t_no* no){
    t_no* atual = no;
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

t_no* removerNo(t_no* raiz, int rgm){
    if (raiz == NULL)
        return raiz;

    if (rgm < raiz->aluno.rgm) // Procura o n�
        raiz->esquerda = removerNo(raiz->esquerda,rgm);
    else if (rgm > raiz->aluno.rgm)
        raiz->direita = removerNo(raiz->direita,rgm);
        
    else { //Encontrou o n�
    
        if (raiz->esquerda == NULL && raiz->direita == NULL){ // N� Folha
            free(raiz);
            return NULL;
        }

        if (raiz->esquerda == NULL){ // N� com apenas 1 filho (direita)
            t_no* aux = raiz->direita;
            free(raiz);
            return aux;
        } else if (raiz->direita == NULL){ // N� com apenas 1 filho (esquerda)
            t_no* aux = raiz->esquerda;
            free(raiz);
            return aux;
        }
		// N� com 2 filhos
        t_no* aux = menorNo(raiz->direita); // Encontra o n� sucessor (menor n� da sub-�rvore direita)
        raiz->aluno = aux->aluno; // Copia os dados para o n� auxiliar (atual)
        raiz->direita = removerNo(raiz->direita,aux->aluno.rgm); // Remove o n� sucessor
    }
    return raiz;
}

t_no* pesquisarNo(t_no* raiz, int rgm){
    if (raiz == NULL || raiz->aluno.rgm == rgm)
        return raiz;
    if (raiz->aluno.rgm < rgm)
        return pesquisarNo(raiz->direita,rgm);
    return pesquisarNo(raiz->esquerda,rgm);
}

void exibirPreOrdem(t_no* raiz){
    if (raiz != NULL){
        printf("%d %s\n",raiz->aluno.rgm,raiz->aluno.nome);
        exibirPreOrdem(raiz->esquerda);
        exibirPreOrdem(raiz->direita);
    }
}

void exibirInOrdem(t_no* raiz){
    if (raiz != NULL){
        exibirInOrdem(raiz->esquerda);
        printf("%d %s\n",raiz->aluno.rgm,raiz->aluno.nome);
        exibirInOrdem(raiz->direita);
    }
}

void exibirPosOrdem(t_no* raiz){
    if (raiz != NULL){
        exibirPosOrdem(raiz->esquerda);
        exibirPosOrdem(raiz->direita);
        printf("%d %s\n",raiz->aluno.rgm,raiz->aluno.nome);
    }
}

void esvaziarArvore(t_no* raiz){
    if (raiz != NULL){
        esvaziarArvore(raiz->esquerda);
        esvaziarArvore(raiz->direita);
        free(raiz);
    }
}

t_no* carregarArquivo(t_no* raiz, const char* nomeArquivo){
	t_aluno aluno;
    FILE* arquivo = fopen(nomeArquivo,"r");
    if (arquivo == NULL){
        printf("Arquivo alunos.txt n�o existe. Por favor, crie manualmente\n");
        exit(0);
    }
    while (fscanf(arquivo, "%d %[^\n]",&aluno.rgm,aluno.nome) != EOF){
        raiz = inserirNo(raiz,aluno);
    }
    fclose(arquivo);
    return raiz;
}

int main(){
    setlocale(LC_ALL,"Portuguese");
    int op;
    t_no* raiz = NULL;
    const char* nomeArquivo = "alunos.txt";
    raiz = carregarArquivo(raiz,nomeArquivo);

    do{
        printf("\nGrupo:\tARTHUR XAVIER CAVALCANTE\n\tFELIPE SOUTO MAIOR MENDES\n\tJULLIANE DI PAULA XAVIER\n\tMATTEUS MAIA RESENDE GUIMAR�ES\n");
        printf("DISCIPLINA: ESTRUTURA DE DADOS I\n");
        printf("PROFESSOR: WALACE BONFIM\n\n");
        printf("EDITOR DE �RVORE\n");
        printf("1 � INSERIR � fornecer RGM e Nome\n");
        printf("2 � REMOVER UM N� � fornecer o RGM a remover\n");
        printf("3 � PESQUISAR � fornecer o RGM a pesquisar\n");
        printf("4 � ESVAZIAR A �RVORE\n");
        printf("5 � EXIBIR A �RVORE � tr�s op��es: PR�, IN ou P�S\n");
        printf("0 � SAIR\n\n");
        printf("ESCOLHA UMA OP��O: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                int rgm;
                char nome[100];
                printf("Digite o RGM: ");
                scanf("%d",&rgm);
                printf("Digite o Nome: ");
                scanf(" %[^\n]",nome);
                t_aluno aluno = {rgm,""};
                strcpy(aluno.nome,nome);
                raiz = inserirNo(raiz,aluno);
                break;
            }
            case 2: {
                int rgm;
                printf("Digite o RGM: ");
                scanf("%d", &rgm);
                t_no* resultado = pesquisarNo(raiz,rgm);
                if (resultado != NULL) {
                    printf("Aluno Removido\nNome: %s\nRGM: %d\n",resultado->aluno.nome,resultado->aluno.rgm);
                    raiz = removerNo(raiz,rgm);
                } else {
                    printf("Aluno n�o encontrado!\n");
                }
                break;
            }
            case 3: {
                int rgm;
                printf("Digite o RGM: ");
                scanf("%d", &rgm);
                t_no* resultado = pesquisarNo(raiz,rgm);
                if (resultado != NULL)
                    printf("Aluno Encontrado\nNome: %s\nRGM: %d\n",resultado->aluno.nome,resultado->aluno.rgm);
                else
                    printf("Aluno n�o encontrado!\n");
                break;
            }
            case 4:
                esvaziarArvore(raiz);
                raiz = NULL;
                printf("�rvore esvaziada!\n");
                break;
            case 5: {
                int opExibicao;
                printf("\n1 - Pr�-ordem\n");
                printf("2 - In-ordem\n");
                printf("3 - P�s-ordem\n");
                printf("\n--> ");
                scanf("%d",&opExibicao);
                printf("\n");
                if (raiz == NULL){
                    printf("�rvore Vazia!\n");
                }else{
                    if (opExibicao == 1)
                        exibirPreOrdem(raiz);
                    else if (opExibicao == 2)
                        exibirInOrdem(raiz);
                    else if (opExibicao == 3)
                        exibirPosOrdem(raiz);
                    else
                        printf("Op��o inv�lida!\n");
                }
                break;
            }
            case 0:
            	printf("\nPrograma Finalizado!");
                exit(0);
            default:
                printf("Op��o inv�lida!\n");
                break;
        }
    }while (op != 0);
    return 0;
}
