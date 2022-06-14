#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Item Element;
typedef struct LinkedList Lista;

struct Item{
    int value;
    Element* next;
    Element* prev;
};

struct LinkedList{
    int lenght;
    Element* head;
    
};

Lista* createList(){
    Lista* list = malloc (sizeof(Lista));
    list -> head = NULL;
    list -> lenght = 0;
    return list;
}

void startList (Lista* list, int value){
    Element* element = malloc (sizeof(Element));
    element -> value = value;
    element -> next = element;
    element -> prev = element;
    list -> head = element;
    list -> lenght = 1;   
}

bool isFull (Lista* lista){
    if(lista -> lenght != 0){
        return true;
    }
    else{
        return false;
    }
}

void addAfterList (Lista* list, int value){
    if(isFull(list)){
        Element* element = malloc(sizeof(Element));
        element -> value = value;
        element -> prev = list -> head -> prev;
        element -> next = list -> head;
        list -> head -> prev -> next = element;
        list -> head -> prev = element;
        list -> lenght++;
    }
    else{
        startList(list, value);
    }
}

void removeElemnt (Lista* list, int index){


    Element* temp = list -> head;
    if(index >= list -> lenght){
        printf("lista juz pusta \n");
    }
    else if(index == 0){

        //Element* temp = list -> head;
        
        temp -> next -> prev = temp -> prev;
        temp -> prev -> next = temp -> next;
        list -> head = temp -> next;
        list -> lenght--;
        

    }
    else if (index < list -> lenght/2){
        //Element* temp = list -> head;
        for(int i = 1; i <= index; i++){
            temp = temp -> next;
        }
    }
    else{
        //Element* temp = list -> head;
        int end = list -> lenght -1;
        for(int i = end; i >= index; i--){
            temp = temp -> prev;
        }
    }

    temp -> next -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    list -> lenght--;
    free(temp);
    return;
}  

bool check (Lista* list, int value) {
    
    Element* temp = list -> head;
    int end = list -> lenght;

    for (int i = 0; i < end; i++) {
        
        if (temp -> value ==  value) {
            return true;
        } else {
            
            temp = temp -> next;
        }
    }
    return false;
}

int find (Lista* list, int index) {
    
    if (index >= list -> lenght) {
        return -1;
    }

    Element* temp = list -> head;

    if (index < list -> lenght / 2) {
        for (int i = 1; i <= index; i++) {
            temp = temp -> next;
        }
    } else {
        
        int start = list -> lenght - 1;

        for (int i = start; i >= index; i--) {
            temp = temp -> prev;
        }
    }

    return temp -> value;
}

void displayList (Lista* list){

    if(isFull(list)){
        Element* temp = list -> head;
        int end = list -> lenght;

        printf ("(Head) ");

        for (int i = 0; i < end; i++) {
            printf ("%d -> ", temp -> value);
            temp = temp -> next;
        }

    printf ("%d (Head)\n", (list -> head -> value));
    }
    else{
        printf ("lista juz pusta\n");

    }
    
}

Lista* merge (Lista* list1, Lista* list2) {
    Lista* merged = createList ();

    Element* temp = list1 -> head;
    int end = list1 -> lenght;

    for (int i = 0; i < end; i++) {
        addAfterList (merged, temp -> value);
        temp = temp -> next;
    }


    temp = list2 -> head;
    end = list2 -> lenght;

    for (int i = 0; i < end; i++) {
        addAfterList (merged, temp -> value);
        temp = temp -> next;
    }

    free(temp);
    return merged;
}

int main(){

    printf("dupa1\n");
    Lista* list1 = createList();
    printf("dupa2\n");
    addAfterList (list1, 8);
    printf("dupa3\n");
    displayList (list1);
    printf("dupa4\n");
    addAfterList (list1, 17);
    printf("dupa5\n");
    displayList (list1);
    printf("dupa6\n");
    addAfterList (list1, 19);
    printf("dupa7\n");
    displayList (list1);
    printf("dupa8\n");
    printf ("%d\n", check(list1, 17));
    printf("dupa9\n");
    printf ("%d\n", find(list1, 0));
    printf("dupa10\n");
    removeElemnt(list1, 0);
    printf("dupa11\n");
    displayList (list1);
    printf("dupa12\n");

    Lista* list2 = createList();
    printf("dupa13\n");
    addAfterList (list2, 22);
    printf("dupa14\n");
    addAfterList (list2, 55);
    printf("dupa15\n");
    addAfterList (list2, 89);
    printf("dupa16\n");

    Lista* merged = merge (list1, list2);
    printf("dupa17\n");
    displayList (merged);
    printf("dupa18\n");

    free(list1);
    free(list2);
    free(merged);

    int value;
    int index;
    double executionTime;
    clock_t beginTime;
    clock_t endTime;

    Lista* czasy = createList();

    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {
        value = rand() % 2137;
        addAfterList (czasy, value);
    }

    index = rand() % czasy -> lenght - 1; //wybieram jeden losowy element tablicy
    int rozmiar = 10000;

    beginTime = clock();

    for(int i = 0; i < rozmiar; i++){
        find (czasy, index);
    }

    endTime = clock(); //koniec pomiaru czasu dostepu do losowego (caly czas tego samego) elementu 10000 razy

    executionTime = (double) (endTime - beginTime) / (CLOCKS_PER_SEC * rozmiar);
    printf ("Sprawdzanie danego elementu %d 10000 razy trwa srednio na raz: %2.15f \n", index, executionTime);


    int* random_index = malloc (rozmiar * sizeof(int));

    beginTime = clock();
    for(int i = 0; i < rozmiar; i++){
        find(czasy, random_index[i]);
    }
    endTime = clock();

    executionTime = (double) (endTime - beginTime) / (CLOCKS_PER_SEC * rozmiar);
    printf("Sprawdzanie dostepu do losowych elementow trwa srednio        : %2.15f \n", executionTime);

    free(random_index);

    free(czasy);
    
    return 0;
}






