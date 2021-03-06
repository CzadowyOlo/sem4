#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Item Element;
typedef struct FIFO Kolejka;

struct Item{
    int value;
    Element* next;
};

struct FIFO{
    Element* head; //head to zmienna adresowa, ktora przechowuje adres pewnej zmiennej typu Element
    Element* tail;
    int size;
};
Kolejka* createFIfo(){
    Kolejka* kolejka = malloc(sizeof(Kolejka));
    kolejka->head = NULL;
    kolejka->tail = NULL;
    kolejka->size = 0;
    return kolejka;
}

bool isFull (Kolejka* kolejka){
    if(kolejka -> size != 0){
        return true;
    }
    else{
        return false;
    }
}

void startFifo(Kolejka* kolejka, int value){
    Element* element = malloc(sizeof(Element));
    element -> value = value;
    element -> next = NULL;
    kolejka -> head = element;
    kolejka -> tail = element;
    kolejka -> size = 1;

}

void addElement (Kolejka* kolejka, int value){

    if(isFull(kolejka)){
        Element* element = malloc(sizeof(Element));
        element -> value = value;
        element -> next = NULL;

        kolejka -> tail -> next = element;
        kolejka -> tail = element;
        kolejka -> size++;

    }

    else{
        startFifo(kolejka, value);
    }

    printf("Dodano element: %d \n", value);
}

void removeElement(Kolejka* kolejka){
    if(isFull(kolejka)){
        Element* temporary = kolejka -> head -> next;
        printf("usuniento element: %d \n", kolejka -> head -> value);
        free(kolejka -> head);
        kolejka -> head = temporary;
        kolejka -> size--;
    }
    else{
        printf("kolejka juz pusta \n");
    }
    
}

void displayFifo (Kolejka* kolejka){
    if(isFull(kolejka)){
        Element* temporary;
        temporary = kolejka -> head;
        while (temporary != NULL){
            printf("%d -> ", temporary -> value);
            temporary = temporary -> next;
        }
        printf("NULL \n");
    }    
    else{
        printf("kolejka juz pusta \n");
    }   
     
}

int main(){
    Kolejka* kolejka = createFIfo();
    /*
    addElement (kolejka, 1);
    addElement (kolejka, 2);
    addElement (kolejka, 3);
    addElement (kolejka, 4);
    displayFifo(kolejka);
    removeElement(kolejka);
    displayFifo(kolejka);
    removeElement(kolejka);
    displayFifo(kolejka);
    removeElement(kolejka);
    displayFifo(kolejka);
    removeElement(kolejka);
    displayFifo(kolejka);
    removeElement(kolejka);
    addElement(kolejka, 5);
    displayFifo(kolejka);
    */

    int i = 0;
    int r;
    srand(time(NULL));
    while (i < 100){

        r = rand() % 200;
        addElement(kolejka, r);
        i++;
    }
    displayFifo(kolejka);
    i = 0;
    while (i < 101){ // usuwam element i = 100, wtedy kolejka jest pusta i jest  na to zabezpieczenie ez


        removeElement(kolejka);
        i++;
    }
    displayFifo(kolejka);


}







