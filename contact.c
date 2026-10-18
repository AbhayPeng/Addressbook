#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Sort contacts based on the chosen criteria
    int i;
    switch (sortCriteria)
    {
    case 1:
        sortbyname(addressBook);
        display(addressBook);

        break;

    case 2:
        sortbyphone(addressBook);
        display(addressBook);

        break;

    case 3:
        sortbyemail(addressBook);
        display(addressBook);

        break;

    default:
        printf("\n**********Enter valid option!!!******\n\n");
    }
}

void initialize(AddressBook *addressBook)
{

    // Load contacts from file during initialization (After files)

    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    Contact check = {0};
    int proceed;

    // Check if address book has reached max capacity
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("BOOK is FULL!!\n");
        return;
    }

    printf("    ADD TO CONTACTS\n   ");

    // Get name input and clear buffer
    printf("NAME:");
    scanf(" %49[^\n]", check.name);
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    // Check for duplicates before validating format
    if (unique_name(&check, addressBook, -1) == 0)
    {
        printf("Duplicate name found");
        return;
    }
    proceed = validate_name(&check);
    if (proceed)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name, check.name);
    }
    else
    {
        printf("ABORTED!!");
        return;
    }

    // Get phone input and check uniqueness
    printf("PHONE:");
    scanf(" %19[^\n]", check.phone);
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    if (unique_phone(&check, addressBook, -1) == 0)
    {
        printf("Duplicate phone found");
        return;
    }
    proceed = validate_phone(&check);
    if (proceed)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].phone, check.phone);
    }
    else
    {
        printf("ABORTED!!");
        return;
    }

    // Get email input and check uniqueness
    printf("EMAIL ID:");
    scanf(" %49[^\n]", check.email);
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    if (unique_email(&check, addressBook, -1) == 0)
    {
        printf("Duplicate email found");
        return;
    }
    proceed = validate_email(&check);
    if (proceed)
    {
        strcpy(addressBook->contacts[addressBook->contactCount].email, check.email);
    }
    else
    {
        printf("ABORTED!!");
        return;
    }

    // Increment count after all fields are saved successfully
    addressBook->contactCount++;

}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    Contact check = {0};
    printf("Select search method:\n");
    printf("1. search  by name\n");
    printf("2. search by phone\n");
    printf("3. search by email\n");
    printf("4. Exit to Main Menu\n");
    printf("Enter your choice: ");
    int searchChoice;

    // Read user choice and clean input buffer
    if (scanf("%d", &searchChoice) == 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Clear trailing characters & newline
    }

    // Call search function based on selected field
    switch (searchChoice)
    {
    case 1:
        printf("Enter name keyword:");
        scanf(" %49[^\n]", check.name);
        searchbyname(addressBook, &check);

        break;

    case 2:
        printf("Enter phone keyword:");
        scanf(" %19[^\n]", check.phone);
        searchbyphone(addressBook, &check);

        break;

    case 3:
        printf("Enter email keyword:");
        scanf(" %49[^\n]", check.email);
        searchbyemail(addressBook, &check);

        break;
    case 4:
        return;
    default:
        printf("\n**********Enter valid option!!!******\n\n");
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    Contact check = {0};
    int index, i, proceed;
    printf("Select search method:\n");
    printf("1. search  by name\n");
    printf("2. search by phone\n");
    printf("3. search by email\n");
    printf("Enter your choice: ");
    int searchChoice, editchoice;
    scanf("%d", &searchChoice);

    // First locate the contact to edit
    switch (searchChoice)
    {
    case 1:
        printf("Enter name keyword:");
        scanf(" %49[^\n]", check.name);
        if (!searchbyname(addressBook, &check))
        {
            while (getchar() != '\n')
                ;
            return;
        }

        break;

    case 2:
        printf("Enter phone keyword:");
        scanf(" %19[^\n]", check.phone);
        if (!searchbyphone(addressBook, &check))
        {
            while (getchar() != '\n')
                ;
            return;
        }
        break;

    case 3:
        printf("Enter email keyword:");
        scanf(" %49[^\n]", check.email);
        if (!searchbyemail(addressBook, &check))
        {
            while (getchar() != '\n')
                ;
            return;
        }

        break;

    default:
        printf("\n**********Enter valid option!!!******\n\n");
        return;
    }

    // Pick specific contact index from search results
    printf("\nSelect the contact to be edited:");
    scanf("%d", &index);
    if (index <= 0 || index > addressBook->contactCount)
    {
        printf("Select a valid contact");
        return;
    }

    // Display chosen contact details
    printf("\nCurrent contact details:\n");
    printf("------------------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
    printf("------------------------------------------------------------------------\n");
    printf("%-5d %-20s %-15s %-30s\n", index, addressBook->contacts[index - 1].name, addressBook->contacts[index - 1].phone, addressBook->contacts[index - 1].email);
    printf("------------------------------------------------------------------------\n");

    printf("Select What to edit?:");
    printf("\n1. Edit name\n");
    printf("2. Edit phone\n");
    printf("3. Edit email\n");
    printf("Exit back to main menu");
    printf("Enter your choice: ");
    scanf("%d", &editchoice);

    // Apply changes based on user selection
    switch (editchoice)
    {

    case 1:
        printf("Enter new name:");
        scanf(" %49[^\n]", check.name);
        proceed = validate_name(&check);
        if (proceed)
        {
            // Ignore current index during duplicate check
            if (unique_name(&check, addressBook, index - 1) == 0)
            {
                printf("Duplicate name found");
                return;
            }
            strcpy(addressBook->contacts[index - 1].name, check.name);
        }
        else
        {
            printf("ABORTED!!");
            return;
        }

        break;

    case 2:
        printf("Enter new phone:");
        scanf(" %19[^\n]", check.phone);
        proceed = validate_phone(&check);
        if (proceed)
        {
            // Pass (index - 1) as the skipIndex parameter so unique_phone ignores self-comparison
            if (unique_phone(&check, addressBook, index - 1) == 0)
            {
                printf("Duplicate phone found\n");
                return;
            }
            strcpy(addressBook->contacts[index - 1].phone, check.phone);
        }
        else
        {
            printf("ABORTED!!");
            return;
        }

        break;

    case 3:
        printf("Enter new email:");
        scanf(" %49[^\n]", check.email);

        proceed = validate_email(&check);
        if (proceed)
        {
            if (unique_email(&check, addressBook, index - 1) == 0)
            {
                printf("Duplicate email found");
                return;
            }
            strcpy(addressBook->contacts[index - 1].email, check.email);
        }
        else
        {
            printf("ABORTED!!");
            return;
        }

        break;
    case 4:
        return;
    default:
        printf("Enter a valid option");
    }

    printf("Contact edited");
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    char c;

    int index, i;
    Contact check = {0};

    // Make sure there are contacts to delete
    if (addressBook->contactCount == 0)
    {
        printf("NO CONTACTS IN ADDRESS BOOK!");
        return;
    }

    // Search for contact to delete
    printf("Select search method:\n");
    printf("1. search  by name\n");
    printf("2. search by phone\n");
    printf("3. search by email\n");
    printf("4. Exit back to main menu\n");
    printf("Enter your choice: ");
    int searchChoice;
    if (scanf("%d", &searchChoice) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Invalid choice\n");
        return;
    }
    while (getchar() != '\n')
        ;

    switch (searchChoice)
    {

    case 1:
        printf("Enter name keyword: ");
        scanf(" %49[^\n]", check.name);

        if (!searchbyname(addressBook, &check))
        {
            while (getchar() != '\n')
                ;
            return;
        }

        break;

    case 2:
        printf("Enter phone keyword:");
        scanf(" %19[^\n]", check.phone);
        if (!searchbyphone(addressBook, &check))
        {
            while (getchar() != '\n')
                ;
            return;
        }

        break;

    case 3:
        printf("Enter email keyword:");
        scanf(" %49[^\n]", check.email);
        if (!searchbyemail(addressBook, &check))
        {
            while (getchar() != '\n')
                ;
            return;
        }

        break;
    case 4:
        return;
    default:
        printf("\n**********Enter valid option!!!******\n\n");
        return;
    }

    printf("\nSelect the contact to be deleted: ");
    scanf("%d", &index);

    if (index <= 0 || index > addressBook->contactCount)
    {
        printf("Select a valid contact\n");
        return;
    }

    // Confirm deletion
    printf("Are you sure you want to delete? Press y/n: ");
    scanf(" %c", &c);

    if (c == 'y' || c == 'Y')
    {
        // Shift remaining array elements left to overwrite deleted contact
        for (i = index - 1; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("Contact deleted successfully!!\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("Deletion cancelled.\n");
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return;
}