/*
Documentation
------------------------------------------------------------
Name : Abhay P
Student Id : 26018_134
Batch Id : 26018D
Start Date : 11/09/2026
End Date : 19/09/2026

Description :The following functions are implemented in the Address Book project to manage contact information efficiently.
            The project provides options to create, search, edit, delete, sort, display and store contacts.

createcontact() : -> Adds a new contact to the address book by collecting the name, mobile number and email ID entered by the user.
                  -> Validates the entered details and checks their uniqueness before storing the contact in memory.

searchcontact() : -> Searches for contacts based on the name, mobile number or email ID entered by the user.
                  -> Displays the matching records and allows the user to select a contact when multiple contacts are found.

editcontact() : -> Allows the user to modify the name, mobile number or email ID of an existing contact.
                -> Validates the updated information and checks uniqueness before saving the changes.

deletecontact() : -> Removes a selected contact from the address book based on the search criteria entered by the user.
                  -> Shifts the remaining contacts to maintain the proper order and updates the total contact count.

listcontact() : -> Displays all contacts in a formatted tabular view after sorting them according to the selected criteria.
                -> Displays the contact number, name, mobile number, email ID and total number of contacts

savecontactsTofile() : -> Writes all current contact details from memory into the contacts.csv file.
                       -> Preserves the contacts for future program executions by storing them in name, phone and email format.

loadcontactsfromfile() : -> Reads previously saved contact details from the contacts.csv file when the program starts.
                         -> Loads the records into the address book and updates the contact count.

------------------------------------------------------------------------------------------------------------------------

File Used:
------------------------------------------------------------

main.c  : -> Controls the main execution of the Address Book program.
          -> Displays the menu, accepts user choices and calls the required functions.

contact.c : -> Implements the main contact operations such as create, search, edit, delete and list.
            -> Connects contact management with validation, sorting, searching and file handling.

contact.h : -> Defines the Contact and AddressBook structures used to store contact information.
            -> Contains function declarations required by the different modules of the project.

search.c : -> Implements searching of contacts using name, phone number and email ID.
           -> Displays matching contacts and supports partial and case-insensitive searching where applicable.

valid.c  : -> Validates name, phone number and email ID entered by the user.
               -> Checks the uniqueness of contact details to prevent duplicate records.

sort.c : -> Implements sorting of contacts based on name, phone number and email ID.
         -> Uses the Bubble Sort technique to arrange contacts in ascending order.

file.c : -> Handles saving and loading of contact information using the contacts.csv file.
         -> Provides permanent storage so that saved contacts are available when the program restarts.

file.h : -> Contains declarations for the file handling functions.
         -> Provides the AddressBook data type required by the file operations through contact.h.

display.c : -> Implements the visual design of the Address Book including loading animation and contact table.
            -> Displays formatted table headings, contact details, total contact count and other user-interface elements.

------------------------------------------------------------------------------------------------------------------------

Sample Output:
------------------------------------------------------------

================== Address Book Menu ==================
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
=======================================================
Enter your choice: 1

sample output :

Enter the name: yadu
Enter the Phone No: 9865265599
Enter the e-mail ID: yadu@gmail.com

Contact created successfully.
*/
#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

int main(void)
{
    int choice;
    AddressBook addressBook;
    char input[20];

    // Load existing contact data on startup
    initialize(&addressBook);

    do
    {
        // Display main menu options
        printf("\n.....................................................\n");
        printf("                    ADDRESS BOOK\n");
        printf(".....................................................\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        // Read user choice as a string to avoid input loop issues
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput error.\n");
            break;
        }

        /* Ignore empty lines caused by leftover newline characters from scanf */
        if (input[0] == '\n')
        {
            continue;
        }

        /* Validate integer input and range */
        if (sscanf(input, "%d", &choice) != 1 || choice < 1 || choice > 6)
        {
            printf("Invalid choice. Please enter a number from 1 to 6.\n");
            continue;
        }

        // Process menu options
        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;

        case 2:
            searchContact(&addressBook);
            break;

        case 3:
            editContact(&addressBook);
            break;

        case 4:
            deleteContact(&addressBook);
            break;

        case 5:
        {
            int sortChoice;

            // Sub-menu for listing contacts with sorting options
            printf("\nSelect sort criteria:\n");
            printf("1. Sort by name\n");
            printf("2. Sort by phone\n");
            printf("3. Sort by email\n");
            printf("Enter your choice: ");

            if (fgets(input, sizeof(input), stdin) == NULL)
            {
                printf("Input error.\n");
                break;
            }

            // Parse and validate sorting choice
            if (sscanf(input, "%d", &sortChoice) != 1 || sortChoice < 1 || sortChoice > 3)
            {
                printf("Invalid sort choice. Please enter a number from 1 to 3.\n");
                break;
            }

            listContacts(&addressBook, sortChoice);
            break;
        }

        case 6:
            // Save updated contacts and exit program
            saveAndExit(&addressBook);
            break;

        default:
            printf("Invalid choice. Please enter 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}