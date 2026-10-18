#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Check for duplicate name (skipIndex avoids self-match when editing)
int unique_name(Contact *check, AddressBook *addressBook, int skipIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == skipIndex)
            continue;

        if (strcmp(check->name, addressBook->contacts[i].name) == 0)
            return 0;
    }
    return 1;
}

// Check for duplicate phone number
int unique_phone(Contact *check, AddressBook *addressBook, int skipIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == skipIndex)
            continue;

        if (strcmp(check->phone, addressBook->contacts[i].phone) == 0)
            return 0;
    }
    return 1;
}

// Check for duplicate email
int unique_email(Contact *check, AddressBook *addressBook, int skipIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == skipIndex)
            continue;

        if (strcmp(check->email, addressBook->contacts[i].email) == 0)
            return 0;
    }
    return 1;
}