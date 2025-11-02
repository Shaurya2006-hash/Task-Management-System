#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Size 50

struct node {
    int id;
    char task[100];
    struct node* next;
};

struct node* head = NULL;

struct node* createNodeLinkedList(int id, char name[]) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->id = id;
    strcpy(newNode->task, name);
    newNode->next = NULL;
    return newNode;
}

void insertTask(int id, char name[]) {
    struct node* newNode = createNodeLinkedList(id, name);
    if (head == NULL) {
        head = newNode;
    } else {
        struct node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Task %d '%s' added.\n", id, name);
}

void deleteTask(int id) {
    struct node* temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Task with ID %d not found.\n", id);
        return;
    }
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Task %d deleted.\n", id);
}

void updateTask(int id, char newName[]) {
    struct node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            strcpy(temp->task, newName);
            printf("Task %d updated to '%s'.\n", id, newName);
            return;
        }
        temp = temp->next;
    }
    printf("Task with ID %d not found.\n", id);
}

void displayTasks() {
    struct node* temp = head;
    if (temp == NULL) {
        printf("No tasks to display.\n");
        return;
    }
    while (temp != NULL) {
        printf("Task ID: %d, Task: %s\n", temp->id, temp->task);
        temp = temp->next;
    }
}

struct queue {
    int front, rear;
    struct node tasks[Size];
};

void initializeQueue(struct queue* q) {
    q->front = q->rear = -1;
}

int isFull(struct queue* q) {
    return (q->rear == Size - 1);
}

int isEmpty(struct queue* q) {
    return (q->front == -1);
}

void enqueue(struct queue* q, int id, char name[]) {
    if (isFull(q)) {
        printf("Queue is full.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->tasks[q->rear].id = id;
    strcpy(q->tasks[q->rear].task, name);
    printf("Task %d added to queue.\n", id);
}

void dequeue(struct queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Executing Task %d: %s\n", q->tasks[q->front].id, q->tasks[q->front].task);
    for (int i = q->front; i < q->rear; i++) {
        q->tasks[i] = q->tasks[i + 1];
    }
    q->rear--;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
}

void displayQueue(struct queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        printf("Task ID: %d, Task: %s\n", q->tasks[i].id, q->tasks[i].task);
    }
}

struct Array {
    int id;
    char task[100];
};

struct Array taskStore[Size];
int taskCount = 0;

void storeTask(int id, char name[]) {
    if (taskCount < Size) {
        taskStore[taskCount].id = id;
        strcpy(taskStore[taskCount].task, name);
        taskCount++;
        printf("Task %d stored.\n", id);
    } else {
        printf("Task storage is full.\n");
    }
}

void displayStoredTasks() {
    if (taskCount == 0) {
        printf("No tasks stored.\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        printf("Task ID: %d, Task: %s\n", taskStore[i].id, taskStore[i].task);
    }
}

struct stack {
    struct node tasks[Size];
    int top;
};

void initializeStack(struct stack* s) {
    s->top = -1;
}

int isStackFull(struct stack* s) {
    return (s->top == Size - 1);
}

int isStackEmpty(struct stack* s) {
    return (s->top == -1);
}

void push(struct stack* s, struct node task) {
    if (isStackFull(s)) {
        printf("Undo stack is full.\n");
        return;
    }
    s->tasks[++(s->top)] = task;
    printf("Task pushed to undo stack.\n");
}

void pop(struct stack* s) {
    if (isStackEmpty(s)) {
        printf("No tasks to undo.\n");
        return;
    }
    struct node task = s->tasks[s->top--];
    printf("Undo Task %d: %s\n", task.id, task.task);
}

struct treeNode {
    int id;
    char task[100];
    char category[50];
    struct treeNode* left;
    struct treeNode* right;
};

struct treeNode* createNodeBinaryTree(int id, char task[], char category[]) {
    struct treeNode* newNode = (struct treeNode*)malloc(sizeof(struct treeNode));
    newNode->id = id;
    strcpy(newNode->task, task);
    strcpy(newNode->category, category);
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct treeNode* insertCategory(struct treeNode* root, int id, char task[], char category[]) {
    if (root == NULL) {
        return createNodeBinaryTree(id, task, category);
    }
    if (strcmp(category, root->category) < 0)
        root->left = insertCategory(root->left, id, task, category);
    else
        root->right = insertCategory(root->right, id, task, category);
    return root;
}

void displayCategories(struct treeNode* root) {
    if (root != NULL) {
        displayCategories(root->left);
        printf("Task ID: %d, Task: %s, Category: %s\n", root->id, root->task, root->category);
        displayCategories(root->right);
    }
}

struct treeNode* searchCategory(struct treeNode* root, int id) {
    if (root == NULL)
        return NULL;
    if (root->id == id)
        return root;
    struct treeNode* leftSearch = searchCategory(root->left, id);
    if (leftSearch != NULL)
        return leftSearch;
    return searchCategory(root->right, id);
}

int main() {
    struct queue q;
    struct stack s;
    struct treeNode* categoryRoot = NULL;
    initializeQueue(&q);
    initializeStack(&s);
    int choice, id;
    char taskName[100], newName[100], category[50];
    while (1) {
        printf("\n1. Add Task\n2. Delete Task\n3. Update Task\n4. Display Tasks\n5. Add Task to Queue\n6. Execute Task\n7. Undo Task\n8. Categorize Task\n9. Display Task Categories\n10. Search Task in Categories\n11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        struct node tempTask;
        switch (choice) {
        case 1:
            printf("Enter Task ID: ");
            scanf("%d", &id);
            printf("Enter Task Name: ");
            scanf("%s", taskName);
            insertTask(id, taskName);
            storeTask(id, taskName);
            tempTask.id = id;
            strcpy(tempTask.task, taskName);
            push(&s, tempTask);
            break;
        case 2:
            printf("Enter Task ID to delete: ");
            scanf("%d", &id);
            deleteTask(id);
            break;
        case 3:
            printf("Enter Task ID to update: ");
            scanf("%d", &id);
            printf("Enter new Task Name: ");
            scanf("%s", newName);
            updateTask(id, newName);
            break;
        case 4:
            displayTasks();
            break;
        case 5:
            printf("Enter Task ID: ");
            scanf("%d", &id);
            printf("Enter Task Name: ");
            scanf("%s", taskName);
            enqueue(&q, id, taskName);
            break;
        case 6:
            dequeue(&q);
            break;
        case 7:
            pop(&s);
            break;
        case 8:
            printf("Enter Task ID: ");
            scanf("%d", &id);
            printf("Enter Task Name: ");
            scanf("%s", taskName);
            printf("Enter Category: ");
            scanf("%s", category);
            categoryRoot = insertCategory(categoryRoot, id, taskName, category);
            break;
        case 9:
            displayCategories(categoryRoot);
            break;
        case 10:
            printf("Enter Task ID to search: ");
            scanf("%d", &id);
            struct treeNode* foundTask = searchCategory(categoryRoot, id);
            if (foundTask != NULL) {
                printf("Found Task ID: %d, Name: %s, Category: %s\n", foundTask->id, foundTask->task, foundTask->category);
            } else {
                printf("Task with ID %d not found in categories.\n", id);
            }
            break;
        case 11:
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

