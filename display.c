#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void display(AddressBook *addressBook)
{
    // Print table header for contact list
    printf("-----------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------\n");

    int i;

    // Loop through and print each contact details formatted in columns
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    // Print table footer
    printf("-----------------------------------------------------------------\n");
}