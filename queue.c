#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define clean_screen system("clear");

#define true 1
#define false 0
typedef int bool;

typedef struct{
    char *airplane;
} Airplane;

typedef struct ELEMENT{
    Airplane airplane;
    struct ELEMENT *next;
} Element;

typedef struct{
    Element *start;
    Element *end;
} Queue;

// Inicializa a fila.
void initialize_queue(Queue *queue){
    queue->start = NULL;
    queue->end = NULL;
}

// Retorna a quantidade de elementos na fila.
int queue_lenght(Queue *queue){
    Element *element = queue->start;
    int len = 0;

    while(element != NULL){
        len++;
        element = element->next;
    }

    return len;
}

// Mostra todos os elementos da fila.
void show_queue(Queue *queue){
    Element *element = queue->start;
    int position = 0;

    printf("Fila de decolagem:\n\n");
    while(element != NULL){
        position++;
        printf("[%i]\t[%s]\n", position, element->airplane.airplane);
        element = element->next;
    }
    printf("\n");
}

// Insere um item na fila.
bool insert_in_queue(Queue *queue, Airplane plane){
    Element *element = (Element*)malloc(sizeof(Element));

    if(element == NULL)
        return false;

    element->airplane = plane;
    element->next = NULL;

    if(queue->start == NULL)
        queue->start = element;
    else
        queue->end->next = element;

    queue->end = element;

    return true;
}

// Libera o primeiro item da fila.
bool airplane_launch(Queue *queue){
    if(queue->start == NULL)
        return false;

    Element *launch = queue->start;
    queue->start = queue->start->next;

    printf("Aviao [%s] lancado!", launch->airplane.airplane);
    free(launch);

    return true;
}

// Pausa até que um botão seja pressionado.
void pause(void){
    printf("Pressione uma tecla para continuar...\n");
    getchar();
}

// Main.
void main(void){
    int option;
    Airplane plane;
    Queue *queue = (Queue*)malloc(sizeof(queue));

    initialize_queue(queue);

    while(true){
        clean_screen;
        printf("FILA DE DECOLAGEM:\n");
        printf("[1] Adicionar a fila.\n"
               "[2] Autorizar decolagem.\n"
               "[3] Listar fila de decolagem.\n"
               "[4] Mostrar primeiro aviao na fila.\n"
               "[5] Mostrar quantidade de avioes na fila.\n"
               "[0] Sair.\n");
        scanf("%d", &option);
        getchar();

        switch (option){
        case 1:
            clean_screen;
            plane.airplane = malloc(10);
            printf("Nome do aviao: ");
            scanf("%s", plane.airplane);
            getchar();
            insert_in_queue(queue, plane);
            break;

        case 3:
            clean_screen;
            show_queue(queue);
            pause();
            break;

        case 0:
            return;
        }
    }
}
