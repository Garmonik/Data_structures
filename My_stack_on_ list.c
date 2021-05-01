#include <stdio.h>
#include <stdlib.h>

//Структура, ссылающаяся на саму себя
struct stackNode{
    int data;                   //Определить данные с типом nt
    struct stackNode *nextPtr;  //Указатель на структура tackNode
}; //Конец структуры stackNode

typedef struct stackNode StackNode; //Синоним для stackNode
typedef StackNode *StackNodePtr;    //Синоним для StackNode*

//Прототипы
void push(StackNodePtr *topPtr, int info);
int pop(StackNodePtr *topPtr);
int isEmpty(StackNodePtr topPtr);
void printStack(StackNodePtr currentPtr);
void instructions();

//Начало программы
int main() {
    StackNodePtr stackPtr = NULL; //Указатель на вершину стека
    unsigned int choice;          //Пункт меню, выбранный пользователем
    int value;                    //Целое число, введеннное пользователем

    instructions();  //Вывести меню
    printf("%s", "Enter choice ");
    scanf("%u", &choice);

    while(choice != 3){

        switch(choice){
            //Добавить значение в стек
            case 1:
                printf("Enter an integer: ");
                scanf("%d", &value);
                push(&stackPtr, value);
                printStack(stackPtr);
                break;
            //Удалить элемент из стека
            case 2:
                //Если стек не пустой
                if(!isEmpty(stackPtr)){
                    printf("The popped value is %d.\n", pop(&stackPtr));
                }

                printStack(stackPtr);
                break;
            default:
                puts("Invalid choice.\n");
                instructions();
                break;
        }
        printf("Enter choice ");
        scanf("%u", &choice);
    }

    puts("End of run.");
}

//Выводит инструкцию писпользованию программы
void instructions(){
    puts("Enter choice:\n"
         "1 to push a value on the stack\n"
         "2 to pop a value off the stack\n"
         "3 to end program");
}

//Доавляет элемент на вершину стека
void push(StackNodePtr *topPrt, int info){
    StackNodePtr newPtr;            //Указатель на новый элемент

    newPtr = (StackNodePtr) (malloc(sizeof(StackNode)));

    // Вставить элемент на вершину стека
    if(newPtr != NULL){
        newPtr -> data = info;
        newPtr -> nextPtr = *topPrt;
        *topPrt = newPtr;
    }
    else{         //Отступает место в памяти
        printf("%d not inserted. No memory available.\n", info);
    }
}

//Удаляет элемент из стека
int pop(StackNodePtr *topPtr){
    StackNodePtr tempPtr;
    int popValue;

    tempPtr = *topPtr;
    popValue = (*topPtr) -> data;
    *topPtr = (*topPtr) -> nextPtr;
    free(tempPtr);
    return popValue;
}

//Вывод содержимого стека
void printStack(StackNodePtr currentPtr){
    //Если стек пуст
    if(currentPtr == NULL){
        puts("The stack is empty.\n");
    }
    else{
        puts("The stack is:");

        //Пока не достиг конец стека
        while(currentPtr != NULL){
            printf("%d -->", currentPtr -> data);
            currentPtr = currentPtr -> nextPtr;
        }
        puts("NULL\n");
    }
}

//Возвращает 1, если стек пустой, 0 если наоборот
int isEmpty(StackNodePtr topPtr){
    return topPtr == NULL;
}
