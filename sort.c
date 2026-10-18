#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Bubble sort contacts alphabetically by name
void sortbyname(AddressBook *addressBook)
{
    int i, j, s;
    Contact temp;

    // Loop through all elements in the contact array
    for (i = 0; i < (addressBook->contactCount) - 1; i++)
    {
        for (j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            // Compare adjacent contact names
            s = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);

            // Swap if the current name comes after the next name alphabetically
            if (s > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

// Bubble sort contacts numerically/alphabetically by phone number
void sortbyphone(AddressBook *addressBook)
{
    int i, j, s;
    Contact temp;

    for (i = 0; i < (addressBook->contactCount) - 1; i++)
    {
        for (j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            // Compare adjacent phone numbers
            s = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);

            // Swap if out of order
            if (s > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

// Bubble sort contacts alphabetically by email address
void sortbyemail(AddressBook *addressBook)
{
    int i, j, s;
    Contact temp;

    for (i = 0; i < (addressBook->contactCount) - 1; i++)
    {
        for (j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            // Compare adjacent email strings
            s = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);

            // Swap if current email should come after the next
            if (s > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}
