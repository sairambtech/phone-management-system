#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define FILE_NAME "phonebook.dat"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Contact;

int addContact(Contact* contacts, int numContacts) {
    if (numContacts >= 100) { // Adjust the limit as needed
        printf("Phonebook is full!\n");
        return numContacts;
    }

    printf("Enter contact name: ");
    fgets(contacts[numContacts].name, MAX_NAME_LENGTH, stdin);
strtok(contacts[numContacts].phone, "\n"); // Remove newline character

    return numContacts + 1;
}

void listContacts(Contact* contacts, int numContacts) {
    if (numContacts == 0) {
        printf("Phonebook is empty!\n");
        return;
    }
printf("\n%-30s %-15s\n", "Name", "Phone Number");
    printf("---------------------------------------------\n");
    for (int i = 0; i < numContacts; i++) {
        printf("%-30s %-15s\n", contacts[i].name, contacts[i].phone);
    }
}

int searchContact(Contact* contacts, int numContacts, char* name) {
    for (int i = 0; i < numContacts; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Contact not found
}

int deleteContact(Contact* contacts, int numContacts, char* name) {
    int index = searchContact(contacts, numContacts, name);
    if (index == -1) {
        printf("Contact not found!\n")
return numContacts;
    }

// Shift contacts to remove the deleted one
    for (int i = index; i < numContacts - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    return numContacts - 1;
}

void saveContacts(Contact* contacts, int numContacts) {
    FILE* file = fopen(FILE_NAME, "wb"); // Open for writing in binary mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

fwrite(contacts, sizeof(Contact), numContacts, file); // Write contacts to file
    fclose(file);
    printf("Phonebook saved successfully!\n");
}

int loadContacts(Contact* contacts) {
    FILE* file = fopen(FILE_NAME, "rb"); // Open for reading in binary mode
    if (file == NULL) {
        return 0; // No existing phonebook file
    }

    int numContacts = fread(contacts, sizeof(Contact), 100, file); // Read up to 100 contacts
    fclose(file);
    return numContacts;
}

int main() {
    Contact contacts[100];
    int numContacts = loadContacts(contacts);

    int choice;
    char name[MAX_NAME_LENGTH];

    while (1) {
        printf("\nPhonebook Management System\n");
        printf("1. Add Contact\n");
        printf("2. List Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save Phonebook\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                numContacts = addContact(contacts, numContacts);
                break;
            case 2:
                listContacts(contacts, numContacts);
                break;
            case 3:
                getchar(); // Consume the newline character left in the buffer
                printf("Enter contact name to search: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
           strtok(name, "\n"); // Remove newline character
                int index = searchContact(contacts, numContacts, name);
                if (index != -1) {
                    printf("Contact found!\n");
                    printf("Name: %s\n", contacts[index].name);
                    printf("Phone: %s\n", contacts[index].phone);
                } else {
                    printf("Contact not found!\n");
                }
                break;
            case 4:
                getchar(); // Consume the newline character left in the buffer
                printf("Enter contact name to delete: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                strtok(name, "\n"); // Remove newline character
                numContacts = deleteContact(contacts, numContacts, name);
                break;
            case 5:
                saveContacts(contacts, numContacts);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }

return 0;
} 
