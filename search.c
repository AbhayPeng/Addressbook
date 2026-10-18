#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

typedef struct
{
    char name[50];
} lower;

int searchbyname(AddressBook *addressBook, Contact *check)
{
    int i, found = 0, j = 0;
    lower check1[MAX_CONTACTS];

    // Copy contact names into temporary array
    for (i = 0; i < addressBook->contactCount; i++)
    {
        strcpy(check1[i].name, addressBook->contacts[i].name);
    }

    // Convert all names to lowercase
    for (i = 0; i < addressBook->contactCount; i++)
    {
        j = 0;

        while (check1[i].name[j] != '\0')
        {
            check1[i].name[j] = tolower(check1[i].name[j]);
            j++;
        }
    }

    // Convert search name to lowercase
    j = 0;

    while (check->name[j] != '\0')
    {
        check->name[j] = tolower(check->name[j]);
        j++;
    }

    // Search the name
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(check1[i].name, check->name) != NULL)
        {
            // Print heading only when first result is found
            if (found == 0)
            {
                printf("RESULT FOUND ARE:\n");

                printf("---------------------------------------------------------\n");
                printf("%-5s %-20s %-15s %-30s\n",
                       "No.", "Name", "Phone", "Email");
                printf("---------------------------------------------------------\n");
            }

            printf("%-5d %-20s %-15s %-30s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            found = 1;
        }
    }

    // No matching contact
    if (found == 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Contact not found\n");
        printf("---------------------------------------------------------\n");

        return 0;
    }

    printf("---------------------------------------------------------\n");

    return 1;
}

int searchbyphone(AddressBook *addressBook, Contact *check)
{
    int i, found = 0;

    // Search through all phone numbers
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].phone, check->phone) != NULL)
        {
            // Print heading for the first result
            if (found == 0)
            {
                printf("\nRESULT FOUND ARE:\n");

                printf("---------------------------------------------------------\n");
                printf("%-5s %-20s %-15s %-30s\n",
                       "No.", "Name", "Phone", "Email");
                printf("---------------------------------------------------------\n");
            }

            printf("%-5d %-20s %-15s %-30s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            found = 1;
        }
    }

    // No matching contact
    if (found == 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Contact not found\n");
        printf("---------------------------------------------------------\n");

        return 0;
    }

    printf("---------------------------------------------------------\n");

    return 1;
}

int searchbyemail(AddressBook *addressBook, Contact *check)
{
    int i = 0, found = 0;

    // Convert search email to lowercase
    while (check->email[i] != '\0')
    {
        check->email[i] = tolower(check->email[i]);
        i++;
    }

    // Search through all email addresses
    for (i = 0; i < addressBook->contactCount; i++)
    {
        char email[50];
        int j = 0;

        // Copy email to temporary array
        strcpy(email, addressBook->contacts[i].email);

        // Convert temporary email to lowercase
        while (email[j] != '\0')
        {
            email[j] = tolower(email[j]);
            j++;
        }

        // Search the email
        if (strstr(email, check->email) != NULL)
        {
            // Print heading for the first result
            if (found == 0)
            {
                printf("RESULT FOUND ARE:\n");

                printf("---------------------------------------------------------\n");
                printf("%-5s %-20s %-15s %-30s\n",
                       "No.", "Name", "Phone", "Email");
                printf("---------------------------------------------------------\n");
            }

            printf("%-5d %-20s %-15s %-30s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            found = 1;
        }
    }

    // No matching contact
    if (found == 0)
    {
        printf("---------------------------------------------------------\n");
        printf("Contact not found\n");
        printf("---------------------------------------------------------\n");

        return 0;
    }

    printf("---------------------------------------------------------\n");

    return 1;
}