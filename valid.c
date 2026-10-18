#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// NAME VALIDATION
int validate_name(Contact *check)
{
    int i = 0;

    // Name length check
    if (strlen(check->name) < 4)
    {
        printf("Name must contain at least 4 characters!\n");
        return 0;
    }

    // Ensure name contains only alphabets and spaces
    while (check->name[i] != '\0')
    {
        if (check->name[i] == ' ')
        {
            i++;
            continue;
        }
        if (isalpha((unsigned char)check->name[i]) == 0)
        {
            printf("Name should contain alphabets and spaces only!\n");
            return 0;
        }
        i++;
    }
    return 1;
}

// PHONE VALIDATION
int validate_phone(Contact *check)
{
    int i = 0;

    // Digits check
    while (check->phone[i] != '\0')
    {
        if (isdigit((unsigned char)check->phone[i]) == 0)
        {
            printf("Number should contain digits 0-9 only!\n");
            return 0;
        }
        i++;
    }

    // Exact length check
    if (strlen(check->phone) != 10)
    {
        printf("Phone number must contain exactly 10 digits!\n");
        return 0;
    }

    // Mobile prefix rule check
    if (check->phone[0] < '6' || check->phone[0] > '9')
    {
        printf("Phone number must start with a digit from 6 to 9!\n");
        return 0;
    }
    return 1;
}

// EMAIL VALIDATION
int validate_email(Contact *check)
{
    int at_count = 0, dot_count = 0, i = 0;
    int pos_at = -1, pos_dot = -1;

    // Scan email structure
    while (check->email[i] != '\0')
    {
        if (check->email[i] == '@')
        {
            if (at_count > 0)
            {
                printf("Only one '@' character is allowed!\n");
                return 0;
            }
            at_count++;
            pos_at = i;
        }
        if (check->email[i] == '.')
        {
            if (dot_count > 0)
            {
                printf("Only one '.' character is allowed!\n");
                return 0;
            }
            dot_count++;
            pos_dot = i;
        }
        i++;
    }

    // Presence checks
    if (at_count == 0)
    {
        printf("Error Message: Missing @\n");
        return 0;
    }
    if (dot_count == 0)
    {
        printf("Error Message: Missing .\n");
        return 0;
    }

    // Positional checks
    if (pos_at == 0)
    {
        printf("Email username cannot be empty before '@'!\n");
        return 0;
    }
    if (pos_dot < pos_at)
    {
        printf("Dot '.' must appear after '@'!\n");
        return 0;
    }
    if (pos_dot - pos_at - 1 == 0)
    {
        printf("There must be at least one character between '@' and '.'!\n");
        return 0;
    }

        // Strict .com domain suffix validation
    if (strcmp(&check->email[pos_dot + 1], "com") != 0)
    {
        printf("Error Message: Extra characters after the domain\n");
        return 0;
    }

    // Strict lowercase letters and digits check only
    for (i = 0; i < pos_at; i++)
    {
        char c = check->email[i];
        if (!isalnum((unsigned char)c) || isupper((unsigned char)c))
        {
            printf("Error Message: Email ID contain only lowercase and Digits\n");
            return 0;
        }
    }

    return 1;
}