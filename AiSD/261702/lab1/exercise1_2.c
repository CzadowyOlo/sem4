#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Item Element;
typedef struct LIFO Stos;

struct Item{
    int value;
    Element* prev;
};

struct LIFO{
    Element* head; //head to zmienna adresowa, ktora przechowuje adres pewnej zmiennej typu Element
    Element* tail;
    int size;
};
Stos* createLIFO(){
    Stos* stos = malloc(sizeof(Stos));
    stos->head = NULL;
    stos->tail = NULL;
    stos->size = 0;
    return stos;
}

bool isFull (Stos* stos){
    if(stos -> size != 0){
        return true;
    }
    else{
        return false;
    }
}

void startFifo(Stos* stos, int value){
    Element* element = malloc(sizeof(Element));
    element -> value = value;
    element -> prev = NULL;
    stos -> head = element;
    stos -> tail = element;
    stos -> size = 1;

}

void addElement (Stos* stos, int value){

    if(isFull(stos)){
        Element* element = malloc(sizeof(Element));
        element -> value = value;
        element -> prev = NULL;

        element -> prev = stos -> tail; //przed nowy element dopinam stos
        stos -> tail = element; //to moj nowy stos
        stos -> size++;

    }

    else{
        startFifo(stos, value);
    }

    printf("Dodano element: %d \n", value);
}

void removeElement(Stos* stos){
    if(isFull(stos)){
        Element* temporary = stos -> tail; //w zmiennej temp przechowuje adres starego stosu
        printf("usuniento element: %d \n", stos -> tail -> value);
        stos -> tail = stos -> tail -> prev;
        free(temporary); //usuwam stary stos
        stos -> size--;
    }
    else{
        printf("stos juz pusty \n");
    }
    
}



int main(){
    Stos* stos = createLIFO();
    /*
    addElement (stos, 1);
    addElement (stos, 2);
    addElement (stos, 3);
    addElement (stos, 4);
    
    removeElement(stos);
    
    removeElement(stos);
    
    removeElement(stos);
    
    removeElement(stos);
    
    removeElement(stos);
    addElement(stos, 5);
    */
    

    
    int i = 0;
    int r;
    srand(time(NULL));
    while (i < 100){

        r = rand() % 200;
        addElement(stos, r);
        i++;
    }
    
    i = 0;
    while (i < 101){


        removeElement(stos);
        i++;
    }
    
    


}
