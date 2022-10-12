#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAM 256



// ----------------- Parte 1 Linked List ----------------------
// ----------------- Parte 1 Lista encadeada ----------------------

// Node data
typedef struct no{
    unsigned char caracter;
    int frequencia;
    struct no *dir, *esq, *prox;
 }No;

// List data
 typedef struct lista{
    No *inicio;
    int tam;

 }Lista;

//Make list
 void criar_lista(Lista *lista){
    lista->inicio=NULL;
    lista->tam=0;
 }

//Insert node ordered
 void inserir_ordenado(Lista *lista,No *no){
     No *aux;
        // Is List empty?
    if(lista->inicio==NULL){
        lista->inicio=no;

    // Implementation Details //O no que queremos inserir tem frequencia menor que inicio da lista
    }else if(no->frequencia < lista->inicio->frequencia){// noh(freq 2) eh menor que  noh (freq 3)
        no->prox=lista->inicio;// noh(freq 2) prox->  noh (freq 3)
        lista->inicio=no; // lista inicio = noh
    }else{
        aux=lista->inicio;
        while(aux->prox &&aux->prox->frequencia <= no->frequencia){
            aux=aux->prox;
        }no->prox=aux->prox;
        aux->prox=no;
    }
    lista->tam++;
 }


//Filled in list
void preencher_lista(unsigned int tab[],Lista *lista){
    int i;
    No *novo;
    for (i=0;i<TAM;i++){
        if(tab[i]>0){
            novo=malloc(sizeof(No));
            if(novo){
                    novo->caracter=i;
                    novo->frequencia=tab[i];
                    novo->dir=NULL;
                    novo->esq=NULL;
                    novo->prox=NULL;

                    inserir_ordenado(lista,novo);

            }else{
                printf("Erro ao alocar memoria em preencher_lista\n");
                break;
            }
        }
    }
}

// Print list
void imprimir_lista(Lista *lista){
    No *aux=lista->inicio;

    printf("\n\tLista Ordenada: Tamanho: %d\n",lista->tam);
    while(aux){
        printf("Caracter: %c  Frequencia: %d\n",aux->caracter,aux->frequencia);
        aux=aux->prox;
    }



}

// Part 1 frequency list
// ----------------- Parte 1 Tabela de Frequencia ----------------------
void inicializa_tabela_com_zero(unsigned int tab[]){
    int i;
    for(i=0;i<TAM;i++){
        tab[i]=0;
    }

}

void preenche_tab_frequencia(unsigned char texto[],unsigned int tab[]){
    int i=0;
    // printf("\nPreenchimento da tabela com a frequencia\n"); discoment this libe to show fill in table
    while(texto[i]!='\0'){
        tab[texto[i]]++;
        i++;
        }
}
 void imprime_tab(unsigned int tab[]){
    int i;
   printf("\tTABELA DE FREQUENCIA\n");
    for(i=0;i<TAM;i++){
  	  if(tab[i]>0){
        	printf("\t%d-%c = %u\n",i,i,tab[i]);
          }
    }

 }

// Part 3 Huffman Tree
 // ----------------- Parte 3 Arvore de Huffman ----------------------
No* remove_no_inicio(Lista *lista){
    No *aux=NULL;
    if(lista->inicio){
      aux=lista->inicio;
      lista->inicio=aux->prox;
      aux->prox=NULL;
      lista->tam--;


    }
    return aux;
}

No* montar_arvore(Lista *lista){
    No *primeiro,*segundo, *novo;
    while(lista->tam >1){
        primeiro=remove_no_inicio(lista);
        segundo=remove_no_inicio(lista);

        novo=malloc(sizeof(No));

        if (novo){
            novo->caracter='+';
            novo->frequencia=primeiro->frequencia+segundo->frequencia;
            novo->esq=primeiro;
            novo->dir=segundo;
            novo->prox=NULL;

            inserir_ordenado(lista,novo);

        }else{
            printf("\nErro ao alocar memoria em montar_arvore!\n");
            break;
        }

    }return lista->inicio;


}

void imprimir_arvore(No *raiz,int tam){
        if(raiz->dir == NULL && raiz->esq== NULL){
            printf("Folha: %c\tAltura: %d\n",raiz->caracter,tam);

       }else{
            imprimir_arvore(raiz->esq,tam+1);
            imprimir_arvore(raiz->dir,tam+1);
       }

}


// Part 4 Dictionary
// ----------------- Parte 4 Dicionario ----------------------
int altura_arvore(No *raiz){
    int esq,dir;
    if(raiz==NULL){

        return -1;
    }else{
        esq=altura_arvore(raiz->esq)+1;
        dir=altura_arvore(raiz->dir)+1;

        if(esq>dir){

            return esq;
        }else{
            return dir;
        }
    }
}
//criacao de uma matriz de strings ou texto (um vetor inicial de ponteiros e contendo ponteiros para as strings
char** aloca_dicionario(int colunas){
    char** dicionario;
    int i;
    dicionario=malloc(sizeof(char*)*TAM);//Aloca memoria para o vetor inicial/vertical da matriz

    for(i=0;i<TAM;i++){
        dicionario[i]=calloc(colunas,sizeof(char));

    }return dicionario;
}
//Funcao para gerar o docionario ou tabela de codigos
void gerar_dicionario(char **dicionario,No *raiz,char *caminho,int colunas){
    char esquerda[colunas],direita[colunas];

    if(raiz->esq==NULL && raiz->dir==NULL){
        strcpy(dicionario[raiz->caracter],caminho); //copia a string caminho na posicao raiz->caracter da matriz

    }else{
        strcpy(esquerda,caminho);
        strcpy(direita,caminho);

        strcat(esquerda,"0"); //Com base no conceito da arvore de Huffman
        strcat(direita,"1");

        gerar_dicionario(dicionario,raiz->esq,esquerda,colunas);
        gerar_dicionario(dicionario,raiz->dir,direita,colunas);
    }
}
void imprime_dicionario(char **dicionario){
    int i;
    printf("\t\nDicionario:\n");
    for(i=0;i<TAM;i++){
        if(strlen(dicionario[i])>0){
        printf("\t%3d: %s\n",i,dicionario[i]);

        }

    }

}

// Part 5 Codification
// ----------------- Parte 5 Codificar----------------------

int calcula_tamanho_string(char **dicionario,unsigned char *texto){
    int i=0, tam=0;
    while(texto[i]!='\0'){
        tam=tam+strlen(dicionario[texto[i]]);
        i++;
    }return tam +1;//+1 devido ao caracter fim de string '\0'
}

char* codificar(char **dicionario,unsigned char *texto){
        int i=0,tam=calcula_tamanho_string(dicionario,texto);
        char *codigo=calloc(tam,sizeof(char));
         while(texto[i]!='\0'){
            strcat(codigo,dicionario[texto[i]]);
            i++;
         }return codigo;
}

// Part 6 Decodification
// ----------------- Parte 6 Decodificar----------------------
char* decodificar(unsigned char texto[],No *raiz){
    int i=0;
    No *aux=raiz;
    char temp[2];
    char *decodificado=calloc(strlen(texto),sizeof(char));

    while(texto[i]!='\0'){
        if(texto[i]=='0'){
            aux=aux->esq;
        }else{
            aux=aux->dir;
        }if (aux->esq==NULL && aux->dir==NULL){
            temp[0]=aux->caracter;
            temp[1]='\0';

            strcat(decodificado,temp);
            aux=raiz;
            /*char texto_temp=aux->caracter'\0';
            strcat(decodificado,"'aux->caracter''\0'");
            */
        }
        i++;
    }return decodificado;
}

// Part 7 Compactification
// ----------------- Parte 7 Compactar----------------------
void compactar(unsigned char str[]){
//Vai criar um arquivo binario para armazenar as informacoes codificadas
    FILE *arquivo =fopen("compressed_file.bin","wb");
    int i=0,j=7; // j=7 devido ao numero da posicao dos bits do byte 00000000
    unsigned char mascara, byte=0; //        00000000 em binario
    //vai pegar o 00000001 e descolar 7vezes 10000000  1<<7
    // vai usar o operador ou| e o resultado 10000000 na variavel byte
    if (arquivo){
            while(str[i]!='\0'){
             mascara=1;// 00000001
             if(str[i]=='1'){
                mascara=mascara<<j;//operador binario << desloca a esquerda
                byte=byte|mascara; //  00000000 | 10000000 = 10000000
             }j--;

             if(j<0){//tem um byte formado
                fwrite(&byte,sizeof(unsigned char),1,arquivo);
                byte=0;
                j=7;
             }
             i++;


            }
            if(j!=7){// 10101000
                fwrite(&byte,sizeof(unsigned char),1,arquivo);

            }
            fclose(arquivo);
    }else{
        printf("\nErro ao abrir/criar o arquivo em compactar\n");
    }

}

// Part 8 Descompactification
// ----------------- Parte 8 Descompactar----------------------
unsigned int eh_bit_um(unsigned char byte,int i){
    unsigned char mascara=(1<<i);// 0000001 com a operacao binaria se i for 7 desloca para esquerda 7 posicoes fica 10000000

    return byte&mascara; /* operacao binaria & se tiver um nos dois bits form iguais a 1  retorna 1,
     se byte 10000000 e mascara 10000000*/

}

void descompactar(No *raiz){
    FILE *arquivo=fopen("compressed_file.bin","rb");
    No *aux=raiz;
    unsigned char byte;//10111101
    int i;

    if(arquivo){
        while(fread(&byte,sizeof(unsigned char),1,arquivo)){//fread irah retornar zero quando nao conseguir ler mais nada
            for(i=7;i>=0;i--){
                if(eh_bit_um(byte,i)){
                        aux=aux->dir;

                }else{
                        aux=aux->esq;
                }if(aux->esq==NULL && aux->dir==NULL){
                    printf("%c",aux->caracter);
                    aux=raiz;
                }


            }

        }
        fclose(arquivo);
    }else{
        printf("\n\nErro ao abrir o arquivo em descompactar\n");
    }


}

int descobrir_tamanho(){
    FILE *arq=fopen("file.txt","r");
    //Queremos contar caracteres dentro de um arquivo
    int tam=0;
    if(arq){
            while(fgetc(arq)!=-1){//retorna caracter lido ou -1 quando nao acha
            tam++;
            }fclose(arq);

    }else{
        printf("\nErro ao abrir arquivo em descobrir_tamanho\n");
    }
    return tam;

}

void ler_texto(unsigned char *texto){
    FILE *arq=fopen("file.txt","r");
    char letra;
    int i=0;
    if(arq){
            while(!feof(arq)){//quando chegar no fim a feof retorn true mas como precisamos rodar o while agente nega ate o fim
                letra=fgetc(arq);
                if(letra!=-1){
                    texto[i]=letra;
                    i++;
                }
            }
            fclose(arq);

            }else{
        printf("\nErro ao abrir arquivo em descobrir_tamanho\n");
    }
}

int main()
{
setlocale(LC_ALL,"Portuguese");

// Part 1 Frequency table
// ----------------- Parte 1 Tabela de Frequencia ----------------------


unsigned char *texto;
unsigned int tabela_frequencia[TAM];
Lista lista;
No *arvore; //Precisa liberar memoria criando um procedimento liberando noh por noh
int colunas,tam;
char **dicionario;//Precisa liberar memoria criando um procedimento primeiro as listas depois o vetor coluna
char *codificado, *decodificado;

//Agora se torna necessario alocar memoria de forma dinamica
tam=descobrir_tamanho();
printf("\nNumber of characters including spaces: %d\n",tam);

texto=calloc(tam+2,sizeof(unsigned char));/*Agora temos memoria suficiente para ler todo o conteudo do arquivo texto.txt
e salvar nesta regiao*/
ler_texto(texto);
//printf("\nTexto: \n%s",texto);//aqui discoment this line to see the text that you type in the file


//Inicialza a tabela de frequancia com zeros
inicializa_tabela_com_zero(tabela_frequencia);
//printf("\n\nImpressao da string: %s",texto);//aqui discoment this line to see the text that you type in the file//
preenche_tab_frequencia(texto,tabela_frequencia);
// imprime_tab(tabela_frequencia); discoment this line to show linked list



// Part 2 Linked List
// ----------------- Parte 2 Lista encadeada ----------------------
        criar_lista(&lista);
        preencher_lista(tabela_frequencia,&lista);
        // imprimir_lista(&lista); discoment this line to show linked list

// Part 3 Huffman Tree
// ----------------- Parte 3 Arvore de Huffman ----------------------
arvore=montar_arvore(&lista);
//printf("\n\tArvore de Huffman:\n"); discomment this line to display Huffman tree
//imprimir_arvore(arvore,0); discomment this line to display Huffman tree

// Part 4 Dictionary
// ----------------- Parte 4 Dicionario ----------------------
colunas=altura_arvore(arvore)+1;// o +1 eh devido ao caracter fim de string '\0'
dicionario=aloca_dicionario(colunas);
gerar_dicionario(dicionario,arvore,"",colunas);//Como estamos na raiz devemos passar no caminho uma string vazia
// imprime_dicionario(dicionario); discomment this line to display dictionary

// Part 5 Codification
// ----------------- Parte 5 Codificar----------------------
codificado=codificar(dicionario,texto);
printf("\n\tBinary Encoded Text: %s\n",codificado);

// Part 6 Decodifocation
// ----------------- Parte 6 Decodificar----------------------
decodificado=decodificar(codificado,arvore);
//printf("\n\tTexto decodificado: %s\n",decodificado);

// Part 7 Compactification
// ----------------- Parte 7 Compactar-------------------------
compactar(codificado);

// Part 8 Descompactification
// ----------------- Parte 8 Descompactar----------------------
printf("\nUNPACKED FILE:\n");

descompactar(arvore);

printf("\n\n");

free(texto);//Para liberar a memoria que nao esta usando mais, Isso eh chamado na programacao de vazemento de memoria
free(codificado);
free(decodificado);
    return 0;
}
