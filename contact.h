#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

/*MAIN FUNCTIONS*/
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

/*SORTING FUNCTIONS*/
void sortbyname(AddressBook *addressBook);
void sortbyemail(AddressBook *addressBook);
void sortbyphone(AddressBook *addressBook);

/*VALIDATING FUNCTIONS*/

int validate_name(Contact *check);
int validate_phone(Contact *check);
int validate_email(Contact *check);

int unique_name(Contact *check,AddressBook *addressBook);
int unique_phone(Contact *check,AddressBook *addressBook);
int unique_email(Contact *check,AddressBook *addressBook);

/*DISPLAYING FUNCTION*/
void display(AddressBook *addressBook);


/*SEARCH  FUNCTIONS*/
int searchbyname(AddressBook *addressBook,Contact *check);
int searchbyphone(AddressBook *addressBook,Contact *check);
int searchbyemail(AddressBook *addressBook,Contact *check);
#endif
