#include <stdio.h>
#include <unistd.h> // Required for usleep()
#include "file.h"
#include "contact.h"
// funtion for saving contacts
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("Contact.csv", "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    fclose(fp);

    /* Smooth Progress Bar (Total duration ~1 second) */
    for (int i = 1; i <= 100; i++)
    {
        printf("\rSAVING...[");
        for (int j = 1; j <= 50; j++)
        {
            if (j <= i / 2)
                printf("#");
            else
                printf(" ");
        }
        printf("] %d%%", i);
        fflush(stdout);
        usleep(10000); // Delay 10ms per iteration
    }
    printf("\nFinished\n");
}
// fuction forloding contacts from file
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("Contact.csv", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    addressBook->contactCount = 0;

    /* Reads until MAX_CONTACTS or EOF; '\n' at the end consumes line breaks properly */
    while (addressBook->contactCount < MAX_CONTACTS &&
           fscanf(fp, " %49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}