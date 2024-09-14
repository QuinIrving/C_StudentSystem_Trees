// Assignment N3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define FLUSH stdin=freopen(NULL,"r",stdin)
#define FLUSH freopen(NULL,"r",stdin)
#define MAX_LEN 50

typedef struct node {
    char *name;
    float gpa;
    size_t id;
    struct node *next;
} student_t;

// You must use the prototypes below. Do NOT declare any other functions!
// You must fix the prototypes below: Make sure you use the correct parameter(s)

student_t* createNode(char* name, float gpa, size_t id); // function to create the node
student_t* createList(); // function to create the list
void displayList(student_t* listHead);         // function to display the list
void insertNode(student_t* newNode, student_t** headNode);  // function to insert node into the sorted list.
void removeList(student_t** listHead);  // function to delete the linked list


int main() {
    printf("\nCreating List of students:\n");

    student_t* head = createList();

    displayList(head);

    removeList(&head);

    return 0;
}

// Your code goes below!!
// Declare the functions according to prototypes.
student_t* createNode(char* name, float gpa, size_t id) {

    student_t* newNode = (student_t*) calloc(1, sizeof(student_t));

    newNode->name = (char*) calloc(strlen(name)+1, sizeof(char));
    strcpy(newNode->name, name);

    newNode->gpa = gpa;

    newNode->id = id;

    newNode->next = NULL;

    return newNode;
}

// Got some of my code from slides on fgets and strcspn, memory allocation and the like
student_t* createList() {

    size_t id = 1000;
    student_t* head = NULL;

    // allocate memory for input string of name
    char* name = (char*) calloc(MAX_LEN, sizeof(char));
    if (name == NULL) {
        perror("Error: Failed to allocate heap memory");
        exit(1);
    }

    // allocate memory for input string of gpa
    char* gpaString = (char*) calloc(MAX_LEN, sizeof(char));
    if (gpaString == NULL) {
        perror("Error: Failed to allocate heap memory");
        exit(1);
    }

    do {

        // ask for name input
        printf("\nInsert student's name (id=%zu): ", id);
        FLUSH;

        // get name input from user
        fgets(name, MAX_LEN, stdin);
        name[strcspn(name, "\r\n")] = '\0';

        // if name entered was blank (go straight to check, so we can exit loop)
        if(strlen(name) < 1) {
            continue;
        }

        // ask for gpa input
        printf("Insert student's GPA (0-100): ");

        // get gpa input from user
        fgets(gpaString, sizeof(gpaString), stdin);
        gpaString[strcspn(gpaString, "\r\n")] = '\0';

        // if gpa entered was blank (go straight to check to skip creating a node)
        if(strlen(gpaString) < 1) {
            printf("Incorrect value of GPA! Ignore student input!\n");
            continue;
        }

        // convert string to float for gpa
        float gpa = strtof(gpaString, NULL);

        // check if gpa is within valid range, if not then skip creating node
        if (gpa < 0.0 || gpa > 100.0) {
            printf("Incorrect value of GPA! Ignore student input!\n\n");
            continue;
        }

        /*
         * insert the node that is created, and send in head node so that if the new node becomes the head node
         * we can update the head node to point to it.
         */
        insertNode(createNode(name, gpa, id), &head);

        // increment id as we have successfully added a new node
        id++;

    } while(strlen(name) > 1);

    free(name);
    free(gpaString);

    return head;
}

void displayList(student_t* listHead) {
    printf("\n============== List of Students: ==============\n");
    printf("  No      GPA     ID        Name\n");
    printf("-----------------------------------------------\n");
    size_t number = 1;
    while(listHead != NULL) {
        printf("  %zu.     %6.2f   %zu   %s\n", number, listHead->gpa, listHead->id, listHead->name);
        number++;
        listHead = listHead->next;
    }
}

void insertNode(student_t* newNode, student_t** head) {

    //if the head is null, then new node should be head, and that is our insert
    if(*head == NULL) {
        *head = newNode;
        return;
    }

    //if node is greater than head, then node should be the new head (as we are sorting from top gpa to lowest)
    if (newNode->gpa > (*head)->gpa) {

        // just make newNode next point to old head node and set head equal to newNode.
        newNode->next = *head;
        *head = newNode;
        return;
    }

    student_t* current = *head;

    //check for place to insert
    while (current != NULL) {

        // if the next node is null then we have reached the end and should insert and return
        if (current->next == NULL) {

            // don't need to update newNode->next as it is already null
            current->next = newNode;
            return;
        }

        // if new node gpa is greater than the node next to new node then we insert right after current node
        if (newNode->gpa > current->next->gpa) {

            newNode->next = current->next;
            current->next = newNode;
            return;
        }

        current = current->next;
    }

}

void removeList(student_t** listHead) {

    student_t* temp = NULL;

    while (*listHead != NULL) {

        temp = (*listHead)->next;
        free((*listHead)->name);
        free((*listHead));
        *listHead = temp;
    }
    //free(listHead);
}
