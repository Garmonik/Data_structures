#include <stdio.h>
#include <stdlib.h>

// Структура, ссылающаяся на саму себя
struct listNode{
    char data;                  // Символ структуры
    struct listNode *nextPtr;   // Указатель на следующий элемент
};

typedef struct listNode ListNode;      // Символ для struct listNode
typedef ListNode *ListNodePtr;         // Синоним для ListNode*

// Прототипы функций
void insert(ListNodePtr *sPtr, char value);
char delete_value(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr *sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);

int main(void) {
    ListNodePtr startPtr = NULL;      // Инициализация списка нулями
    unsigned int choice;              // Выбор пользователя
    char item;                        // Символ, введенный пользователем

    instructions();                   // Вывести меню
    printf("Enter your choice: ");
    scanf("%u", &choice);

    // Цикл, пока не выберут choice == 3 (Завершение работы программы)
    while(choice != 3){

        switch(choice){
            case 1:                     // Добавить элемент
                printf("Enter a character: ");
                scanf("\n%c", &item);

                insert(&startPtr, item); // Вставить элемент в список
                printList(startPtr);
                break;

            case 2:                     // Удалить элемент
                // Проверка на пустоту списка
                if(!isEmpty(&startPtr)) {
                    printf("Enter character to be deleted: ");
                    scanf("\n%c", &item);

                    // Если символ найден, удалить его из списка
                    if (delete_value(&startPtr, item)) {   // Удалить элемент
                        printf("%c delete.\n", item);
                        printList(startPtr);
                    }
                    else
                        printf("%c not found.\n\n", item);
                }
                else
                    puts("List is empty");

                break;
            default:
                puts("Invalid choice.\n");
                instructions();
                break;
        }
        printf("Enter a character: ");
        scanf("%u", &choice);
    }
    puts("End of run.");
}

// Инструкция по работе с прогрмаммой
void instructions(void) {
    puts("Enter your choice:\n"
         "1 to insert an element into the list.\n"
         "2 to delete an element from the list.\n"
         "3 tp end.");
}

// Добавляет значение в список
void insert(ListNodePtr *sPtr, char value){
    ListNodePtr newPtr;                 // Указатель на новый элемент
    ListNodePtr previousPtr;            // Указатель на предыдущий элемент
    ListNodePtr currentPtr;             // Указатель на текущий элемент

    newPtr = (ListNodePtr)(malloc(sizeof(ListNode)));   // Выделяем память на элемент

    if(newPtr != NULL){                                 // Если память выделена
        newPtr -> data = value;                         // Запись числа в память
        newPtr -> nextPtr = NULL;                       // Узел не связан с другим узлом

        previousPtr = NULL;
        currentPtr = *sPtr;

        // Найти место в списке и вставить его туда
        while(currentPtr != NULL && value > currentPtr -> data){
            previousPtr = currentPtr;           // Перейти к ...
            currentPtr = currentPtr -> nextPtr; // ... следующему элементу
        }

        // Вставка нового узла в начало списка
        if(previousPtr == NULL){
            newPtr -> nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else{ // Вставить новый элемент между previousPtr и currentPtr
            previousPtr -> nextPtr = newPtr;
            newPtr -> nextPtr = currentPtr;
        }
    }
    else
        printf("%c not inserted. No memory available.\n", value);
}

// Удаляет элемент списка
char delete_value(ListNodePtr *sPtr, char value){
    ListNodePtr previousPtr; // Указатель на предыдущий элемент
    ListNodePtr currentPtr;  // Указатель на текущий элемент
    ListNodePtr tempPtr;     // Временный указатель на элемент

    // Удалить первый элемент
    if(value == (*sPtr) -> data){
        tempPtr = *sPtr;                // Сохранить указатель на удаляемый элемент
        *sPtr = (*sPtr) -> nextPtr;     // Исключить элемент из списка
        free(tempPtr);// Освободить память, занимаемую исключенным элементом
        return value;
    }
    else{
        previousPtr = *sPtr;
        currentPtr = (*sPtr) -> nextPtr;

        // Найти элемент списка с указанным символом
        while(currentPtr != NULL && currentPtr -> data != value){
            previousPtr = currentPtr;                   // перейти к ...
            currentPtr = currentPtr -> nextPtr;         // ... следующему элементу
        }

        // Удалить элемент
        if(currentPtr != NULL){
            tempPtr = currentPtr;
            previousPtr -> nextPtr = currentPtr -> nextPtr;
            free(tempPtr);
            return value;
        }
    }

    return '\0';
}

// Возвращает 1, если список пуст, 0 если список не пуст
int isEmpty(ListNodePtr *sPtr){
    return sPtr == NULL;
}

// Вывод списка
void printList(ListNodePtr currentPtr){
    //если список пуст
    if(isEmpty(&currentPtr))
        puts("List is empty.\n");
    else{
        puts("The list is: ");

        // Пока не достиг конца списка
        while(currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
            puts("NULL\n");
    }
}
