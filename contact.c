#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria

    // Bubble sort

    Loop from 0 to addressBook->contactCount-1;

     pf("%s, %s, %s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char *str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if( ! (str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] == ' ') && !(str[i] == '.'))
        {
            return 0;
        }
    }

    return 1;
}
int validate_phone(char *str, AddressBook *addressBook)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(!(str[i]>= '0' && str[i] <= '9'))
        {
            return 0;
        }
        if(strlen(str) != 10)
        {
            return 0;
        }
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone, str) == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}
int validate_email(char *str, AddressBook *addressBook)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(!(str[i]>= '0' && str[i] <= '9'))
        {
            return 0;
        }
        if(strlen(str) != 10)
        {
            return 0;
        }
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].email, str) == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}

void createContact(AddressBook *addressBook)
{

    char str1[30], str2[20], str3[30];

    do
    {
        printf("Enter the name: ");
        scanf("%[^\n]", str1);

        int res = validate_name(str1);
        if(res == 0)
        {
            printf("Invalid name. Please enter a valid name.\n");
        }
    }while(res == 0)

    do
    {
        printf("Enter the phone number: ");
        scanf("%[^\n]", str2);

        int res = validate_phone(str2,addressBook);
        if(res == 0)
        {
            printf("Invalid phone number. Please enter a valid phone number.\n");
        }
    }while(res == 0)

    do
    {
        printf("Enter the email: ");
        scanf("%[^\n]", str3);

        int res = validate_email(str3,addressBook);
        if(res == 0)
        {
            printf("Invalid email. Please enter a valid email.\n");
        }
    }while(res == 0)







    int ind = addressBook->contactCount;
    strcpy(addressBook->contacts[ind].name, str1);
    strcpy(addressBook->contacts[ind].phone, str2);
    strcpy(addressBook->contacts[ind].email, str3);

    addressBook->contactCount++;

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    int choise;

    // print promt

    scanF("%d", &choise);

    switch(choise)
    {
        case 1:
            search_by_name(addressBook);
            break;
        case 2:
            search_by_phone(addressBook);
            break;
    }

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
