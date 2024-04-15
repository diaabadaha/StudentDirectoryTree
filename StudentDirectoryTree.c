#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50  // Size of student and city name
#define MAX_DATE_SIZE 20 // Size of enrollment date

// Tree node struct
typedef struct T_node{
    int id;
    char name[MAX_SIZE];
    char city[MAX_SIZE];
    int classId;
    char enrollmentDate[MAX_DATE_SIZE];
    struct T_node* left;
    struct T_node* right;

} Tnode;

// List node struct
typedef struct list_node {
    Tnode* student;
    struct list_node* next;
} Lnode;

// Function to create node for a list
Lnode* createListNode(Tnode* student) {
    Lnode* temp = (Lnode*)malloc(sizeof(struct list_node));

    temp->student = student;
    temp->next = NULL;

    return temp;
}

// Function to free all list nodes from memory
void deleteList(Lnode* head) {
    Lnode* P;
    Lnode* temp;
    P = head->next;
    head->next = NULL;

    while (P != NULL) {
        temp = P->next;
        free(P);
        P = temp;
    }
}

// Function to make an empty list, it also makes a list empty (if it has content)
Lnode* makeEmptyList(Lnode* head){
    if(head != NULL)
        deleteList(head);

    head = (Lnode*)malloc(sizeof(struct list_node));
    if(head == NULL)
        printf("Out of memory!\n");

    head->next = NULL;
    return head;
}

// Function to insert a new node to list
Lnode* insertListNode(Lnode* head, Lnode* newNode) {
    Lnode* p = head;

    while(p->next != NULL) {
        p = p->next;
    }

    newNode->next = NULL;
    p->next = newNode;

    return head;
}

// Function to insert a tree node to list
Lnode* insertListNodeFromTree(Tnode* student, Lnode* head) {
    Lnode* temp = createListNode(student); // Create list node from the tree node
    insertListNode(head, temp);

    return head;
}

// Function to swap the contents of two list nodes
void swapContent(Lnode* node1, Lnode* node2) {
    int tempId, tempClassId;
    char tempName[MAX_SIZE], tempDate[MAX_DATE_SIZE], tempCity[MAX_SIZE];

    // Storing the contents of second node in temporary variables
    tempId = node2->student->id;
    strcpy(tempName, node2->student->name);
    tempClassId = node2->student->classId;
    strcpy(tempCity, node2->student->city);
    strcpy(tempDate, node2->student->enrollmentDate);

    // Storing the contents of first node in second node
    node2->student->id = node1->student->id;
    strcpy(node2->student->name, node1->student->name);
    node2->student->classId = node1->student->classId;
    strcpy(node2->student->city, node1->student->city);
    strcpy(node2->student->enrollmentDate, node1->student->enrollmentDate);

    // Storing the contents of second node (temporary variables) in first node
    node1->student->id = tempId;
    strcpy(node1->student->name, tempName);
    node1->student->classId = tempClassId;
    strcpy(node1->student->city, tempCity);
    strcpy(node1->student->enrollmentDate, tempDate);
}

// Function to find the node with the least value in a list depending on students names
Lnode* findMinListName(Lnode* head) {
    Lnode* min = head;
    Lnode* p;


    if(head->next != NULL) // The list is not empty
        p = head->next;
    else // The list is empty
        p = NULL;

    while(p != NULL) {
        if(strcmp(p->student->name, min->student->name) < 0 || min == NULL) // Name in (p) is smaller than name in (min) OR min is the head pointer
            min = p;
        p = p->next;
    }
    return min;
}


// Function to sort(selection sort) list depending on students names
void sortList(Lnode* head) {
    Lnode* p = head->next;

    while(p->next != NULL) {
        Lnode* min = findMinListName(p);
        swapContent(p, min);
        p = p->next;
    }
}

// Function to create a new student node
Tnode* createTreeNode(int id, char name[], char city[], int classId, char enrollmentDate[]) {
    Tnode* temp = (Tnode*)malloc(sizeof(struct T_node));

    if(temp == NULL) {
        printf("\nOut of memory!\n");
        return NULL;
    }

    temp->id = id;
    strcpy(temp->name, name);
    strcpy(temp->city, city);
    temp->classId = classId;
    strcpy(temp->enrollmentDate, enrollmentDate);
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

// Function to check if a tree is empty
int isEmptyTree(Tnode* root) {
    return root == NULL;
}

// Function to make an empty tree, it also makes a tree empty (if it has content)
void makeEmptyTree(Tnode* root){
    if(root != NULL){
        makeEmptyTree(root->left);
        makeEmptyTree(root->right);
        free(root);
    }
}

// Recursive Function to insert new node to tree
Tnode* insertTreeNode(Tnode* root, Tnode* newStudent) {
    if(root == NULL) { // Base case
        root = createTreeNode(newStudent->id, newStudent->name, newStudent->city, newStudent->classId, newStudent->enrollmentDate);
        return root;
    }

    // Recursively, insert on rigth or left
    if(root->id < newStudent->id)
        root->right = insertTreeNode(root->right, newStudent);
    else if(root->id > newStudent->id)
        root->left = insertTreeNode(root->left, newStudent);

    return root;
}

// Recursive function to find student by his id
Tnode* findStudent(int id, Tnode* root) {
    if(root != NULL) {
        if(root->id == id) { // Base case
            return root;
          // Recursively, search in left or right
        } else if(root->id < id) {
            return findStudent(id, root->right);
        } else if(root->id > id)
            return findStudent(id, root->left);

    } else { // Student is not found
        printf("There is no student with that id!\n");
        return NULL;
    }
}

// Function to print information of students
void printInfo(Tnode* student) {
    printf("\nName: %s\t\tID: %d\t\tClass' ID: %d\t\tLocation(city): %s\t\tEnrollment date: %s\n", student->name, student->id, student->classId, student->city, student->enrollmentDate);
}

// Recursive function to free a tree
void freeTree(Tnode* root) {
    if (root == NULL) {
        return;
    }

    // Recursively, free left subtree
    freeTree(root->left);

    // Recursively, free right subtree
    freeTree(root->right);

    // Free the current node
    free(root);
}

// Recursive function to traverse tree by in-order
void inOrderTraversal(Tnode* root) {
    if(root == NULL)
        return;

    inOrderTraversal(root->left);
    printInfo(root);
    inOrderTraversal(root->right);
}

// Recursive function to copy tree content to a list
void treeToList(Lnode* head, Tnode* root) {
    if (root == NULL)
        return;

    Tnode* temp = NULL;
    temp = createTreeNode(root->id, root->name, root->city, root->classId, root->enrollmentDate);
    head = insertListNodeFromTree(temp, head); // Insert root node

    // Recursively, traverse left and right subtrees
    treeToList(head, root->left);
    treeToList(head, root->right);
}

// Function to print the content of students list
void printList(Lnode* head) {
    Lnode* temp = head->next;

    while (temp != NULL) {
        printInfo(temp->student); // Print each student information
        temp = temp->next;
    }
    printf("\n");
}

// Function to print the content of students list in a file
void inOrderTraversalToFile(Tnode* root, FILE* fptr) {
    if(root == NULL)
        return;

    inOrderTraversalToFile(root->left, fptr);
    fprintf(fptr, "%s\t\t%d\t\t%d\t\t%s\t\t%s\n", root->name, root->id, root->classId, root->city, root->enrollmentDate); // Print each student information
    inOrderTraversalToFile(root->right, fptr);
}

// Function to print the content of students list depending on their cities
void printCityList(Lnode* head, char city[]) {
    Lnode* temp = head->next;

    while (temp != NULL) {
        if(strcmp(temp->student->city, city) == 0) // Student city is the same as desired city
            printInfo(temp->student);

        temp = temp->next;
    }
    printf("\n");
}

// Function to print the content of students list depending on their classes
void printClassList(Lnode* head, int classId) {
    Lnode* temp = head->next;

    while (temp != NULL) {
        if(temp->student->classId == classId) // Student class is the same as desired class
            printInfo(temp->student);

        temp = temp->next;
    }
    printf("\n");
}

// Function to find the node with minimum id in a tree
Tnode* findMin(Tnode* root) {
    Tnode* p = root;

    if(p != NULL) {
        while(p->left != NULL) { // Stops at most left leaf node
            p = p->left;
        }
    }
    return p;
}

int deleteFlag = 1; // Global variable to check if the student to delete is found or not

// Function to delete node(student) from a tree recursively
Tnode* deleteStudent(Tnode* root, int id) {
    Tnode* temp;

    if(root == NULL) {
        printf("\nStudent with an id of %d is not found!", id);
        deleteFlag = 0;
    } else if(id < root->id) {
        root->left = deleteStudent(root->left, id); // Recursively, find node in left subtree
    } else if(id > root->id) {
        root->right = deleteStudent(root->right, id); // Recursively, find node in right subtree
    } else { // Node to be deleted is found
        if(root->left != NULL && root->right != NULL) { // The node to be deleted has two children
            temp = findMin(root->right); // Replace the node to be deleted with smallest node(id) in right subtree
            root->id = temp->id;
            strcpy(root->name, temp->name);
            root->classId = temp->classId;
            strcpy(root->city, temp->city);
            strcpy(root->enrollmentDate, temp->enrollmentDate);

            root->right = deleteStudent(root->right, root->id);
        } else { // One or zero children
            temp = root;
            if(root->left == NULL) {
                root = root->right;
            } else if(root->right == NULL) {
                root = root->left;
            }

            free(temp);
        }
    }

    return root;
}

// Function to print menu to the user
void printMenu() {
    printf("\n\nPlease Choose one from these options:\n");
    printf("1. Insert a student.\n");
    printf("2. Find a student and update his information.\n");
    printf("3. List all students in lexicographic order of their names.\n");
    printf("4. Search for a city and list all students from that city.\n");
    printf("5. List all students from a specified class.\n");
    printf("6. Delete a student.\n");
    printf("7. Save changes to file.\n");
    printf("8. Exit.\n");
}

// Main function
int main()
{
    printf("\nWelcome to the school management system...\n\n");

    Tnode* school = NULL; // Main tree which stores all students
    Lnode* studentsList; // List used to order students depending on their names

    // Temporary variables used in insertion and updating operations
    int id;
    char name[MAX_SIZE];
    char city[MAX_SIZE];
    int classId;
    char enrollmentDate[MAX_DATE_SIZE];

    FILE* fPtr = fopen("students.data.txt", "r"); // Input file

    if(fPtr == NULL) {
        printf("\nFile cannot open!\n");
    } else {
        // Reading data from input file (if any)
        while(fscanf(fPtr, "%s %d %d %s %s", name, &id, &classId, city, enrollmentDate) != EOF) {
            // Insert student with read data to the tree
            Tnode* temp = createTreeNode(id, name, city, classId, enrollmentDate);
            school = insertTreeNode(school, temp);
        }
    }

    int option; // Menu option
    do {
        printMenu();
        scanf("%d", &option);

        if(option == 1) { // Insert student
            // Reading student data from user
            printf("\n\nPlease enter the information below:\n");
            printf("Enter the student's id: ");
            scanf("%d", &id);

            printf("Enter the student's name: ");
            scanf("%s", name);

            printf("Enter the student city's name: ");
            scanf("%s", city);

            printf("Enter the student class' id: ");
            scanf("%d", &classId);

            printf("Enter enrollment date: ");
            scanf("%s", enrollmentDate);

            // Insert student with read data to the tree
            Tnode *temp = createTreeNode(id, name, city, classId, enrollmentDate);
            school = insertTreeNode(school, temp);

            printf("\nStudent has been added successfully...\n");

        } else if(option == 2) { // Find a student by his/her student ID, and support updating of the student info if found.
            if (isEmptyTree(school)) {
                printf("\nThere are no students in the system!\n");
            }

            printf("\nPlease enter an ID to search for: ");
            scanf("%d", &id);

            Tnode *student = findStudent(id, school);
            if (student != NULL) { // Student is found
                int choiceToUptade;
                do { // Keep editing information until user chooses nothing to update
                    printf("\nChoose one to update:\n1- ID.\n2- Name.\n3- Class ID.\n4- City name.\n5- Enrollment date.\n6- Nothing.\n");
                    scanf("%d", &choiceToUptade);

                    switch (choiceToUptade) {
                        // Updating id
                        case 1:
                            printf("\nEnter the new id: ");
                            scanf("%d", &id);
                            student->id = id;
                            break;

                        // Updating name
                        case 2:
                            printf("\nEnter the new name: ");
                            scanf("%s", student->name);
                            break;

                        // Updating class id
                        case 3:
                            printf("\nEnter the new id for class: ");
                            scanf("%d", &classId);
                            student->classId = classId;
                            break;

                        // Updating city
                        case 4:
                            printf("\nEnter the new name of city: ");
                            scanf("%s", student->city);
                            break;

                        // Updating enrollment date
                        case 5:
                            printf("\nEnter the new name of city: ");
                            scanf("%s", student->enrollmentDate);
                            break;

                        // Update nothing
                        case 6:
                            break;

                        default:
                            printf("\nUnavailable Option!");
                            break;
                    }
                } while (choiceToUptade != 6);
            }

        } else if(option == 3) { // List all students in lexicographic order of their names.
            // Creating a students list from tree
            studentsList = makeEmptyList(studentsList);
            treeToList(studentsList, school);

            // Sorting the list depending on lexicographic order of students' names
            sortList(studentsList);

            // Printing the list
            printList(studentsList);

        } else if(option == 4) { // Search for a city and list all students from that city in lexicographic order of their names.
            Lnode* tempList = NULL;
            char cityToSearch[MAX_SIZE];

            tempList = makeEmptyList(tempList);

            // Reading city name from user
            printf("\nPlease enter a name of city to search for: ");
            scanf("%s", cityToSearch);

            // Creating temporary students list from tree & sorting it
            treeToList(tempList, school);
            sortList(tempList);

            if(isEmptyTree(school)) {
                printf("\nThere's no students in the system!\n");
            } else {
                Lnode* p1 = tempList->next;
                int cityFlag = 0;

                // Checking if there are students from the specified city
                while(p1->next != NULL) {
                    if(strcmp(p1->student->city, cityToSearch) == 0) {
                        cityFlag = 1;
                        break;
                    } else {
                        p1 = p1->next;
                    }
                }

                if(cityFlag == 0) { // There are NO students from the specified city
                    printf("\nThere are no students from %s!\n", cityToSearch);

                } else { // There exist students from the specified city
                    printf("\nStudents from %s are:\n", cityToSearch);
                    printCityList(tempList, cityToSearch);
                }
            }

            // Free temp list from memory
            deleteList(tempList);
            free(tempList);

        } else if(option == 5) { // List all students by their class in lexicographic order of their names.
            Lnode* tempList = NULL;
            int classIdToSearch;

            tempList = makeEmptyList(tempList);

            // Reading class id from user
            printf("\nPlease enter an ID of a class: ");
            scanf("%d", &classIdToSearch);

            // Creating temporary students list from tree & sorting it
            treeToList(tempList, school);
            sortList(tempList);

            if(isEmptyTree(school)) {
                printf("\nThere's no students in the system!\n");
            } else {
                Lnode* p1 = tempList->next;
                int classFlag = 0;

                // Checking if there is a class with the specified id
                while(p1->next != NULL) {
                    if(p1->student->classId == classIdToSearch) {
                        classFlag = 1;
                        break;
                    } else {
                        p1 = p1->next;
                    }
                }

                if(classFlag == 0) { // There is NO class with the specified id
                    printf("\nThere is no class with an ID of %d", classIdToSearch);

                } else { // There exists a class with the specified id
                    printf("\nStudents enrolled in class %d are:\n", classIdToSearch);
                    printClassList(tempList, classIdToSearch);
                }
            }

            // Free temp list from memory
            deleteList(tempList);
            free(tempList);

        } else if (option == 6) { // Delete a student given his/her student ID.

            // Reading id from user
            int idToDelete;
            printf("\nPlease enter an ID to delete: ");
            scanf("%d", &idToDelete);

            deleteFlag = 1; // Assigning delete flag to equal 1

            // Deleting student
            deleteStudent(school, idToDelete);
            if(deleteFlag)
            printf("\nThe student with an id of %d has been deleted successfully..\n", idToDelete);

        } else if(option == 7) { // Save all students in file students.data.

            fPtr = fopen("students.data.txt", "w"); // Opening file
            if(fPtr == NULL) {
                printf("\nFile cannot open!\n");
                break;
            }
            inOrderTraversalToFile(school, fPtr);

            printf("\nData have been saved in -students.data- file successfully\n");

        } else if(option == 8) { // Exit.
            printf("\nThank you for using this program...\n\n\n");

        } else {
            printf("\nInvalid Option!!\n");
        }

    } while(option != 8);

    // Free tree and list from memory
    freeTree(school);
    deleteList(studentsList);
    free(studentsList);

    return 0;
}