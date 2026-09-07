#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

// Displays every saved contact in alphabetical order by name.
void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\n+------------------------------------------+\n");
        printf("|          No Contacts Available           |\n");
        printf("+------------------------------------------+\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcmp(addressBook->contacts[j].name,
                       addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("\n");
    printf("===============================================================\n");
    printf("                      CONTACT LIST\n");
    printf("===============================================================\n");

    printf("+------+--------------------+---------------+--------------------------+\n");
    printf("| S.No | Name               | Phone         | Email                    |\n");
    printf("+------+--------------------+---------------+--------------------------+\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-4d | %-18s | %-13s | %-24s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("+------+--------------------+---------------+--------------------------+\n");
}

// Resets the address book and loads any contacts saved on disk.
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Saves the current contacts before ending the program immediately.
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// Checks whether a name contains only the characters accepted by the address book.
int validate_name(char *str)
{
    //loop 0 to str[i]
    for(int i=0;str[i]!=0;i++)
    {
        if( ! ((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') || str[i]==' ' || str[i]=='.')) // not valid
        {
            return 0; // invalid
        }
    }

    return 1; 
}

// Checks whether a phone number contains exactly ten digits.
int validate_phone(char *str)
{   
    for(int i=0;*(str+i)!=0;i++)
    {   
        char ch = *(str+i);
        if(ch<'0' || ch>'9') // not valid
        {
            return 0; // invalid
        }
    }
    if(strlen(str)==10)
    {
        return 1; 
    }
    return 0;

}

// Checks whether an email starts correctly and ends with a valid .com domain.
int validate_email(char *str)
{
    if(*str < 'a' || *str > 'z')
    {
        return 0;
    }
    int i=0;
    int at=-1;
    int dot=-1;

    while(*(str+i)!=0){
        if(*(str+i)=='@'){
            at=i;
        }
        else if (*(str+i)=='.'){
            dot=i;
        }
        i++;
    }
    if(i>=4 && strcmp(str+i-4, ".com")==0)   //check .com
    {
        if(at>0 && dot>=at+2)//between @ and .com check weather something is present or not
        {
            return 1;
        }
    }
    return 0;

}
// Confirms that a phone number is not already assigned to another contact.
int is_unique_phone(AddressBook *addressBook, char *str)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, str) == 0)
        {
            return 0;
        }
    }

    return 1;
}

// Confirms that an email address is not already assigned to another contact.
int is_unique_email(AddressBook *addressBook, char *str)    
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, str) == 0)
        {
            return 0;
        }
    }
        return 1;
}

// Checks whether a phone number is unique while ignoring the contact being edited.
static int is_unique_phone_for_edit(AddressBook *addressBook, char *str, int edited_index)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i != edited_index && strcmp(addressBook->contacts[i].phone, str) == 0)
        {
            return 0;
        }
    }

    return 1;
}

// Checks whether an email is unique while ignoring the contact being edited.
static int is_unique_email_for_edit(AddressBook *addressBook, char *str, int edited_index)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i != edited_index && strcmp(addressBook->contacts[i].email, str) == 0)
        {
            return 0;
        }
    }

    return 1;
}


// Collects validated contact details and adds the new contact to the address book.
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char str1[30], str2[20], str3[30];
    int res;

    printf("\n");
    printf("+------------------------------------------+\n");
    printf("|              CREATE CONTACT              |\n");
    printf("+------------------------------------------+\n");

    do
    {
        printf("Enter the name :");
        scanf(" %[^\n]",str1);

        res = validate_name(str1);
        if(res==0){
            printf("Your entered wrong input. Please provide a valid input.\n");
        }
    }while(res == 0); // 0 means invalid

    do
    {
        printf("Enter the phone :");
        scanf(" %[^\n]",str2);

        res = validate_phone(str2);
        if(res==0)
        {
            printf("Your entered wrong input. Please provide a valid input.\n");
        }
        else if(is_unique_phone(addressBook, str2) == 0)
        {
        printf("Phone number already exists. Please enter a different number.\n");
        res = 0;
        }
    }while(res == 0); // 0 means invalid

    do
    {
        printf("Enter the email id:");
        scanf(" %[^\n]",str3);

        res = validate_email(str3);
        if(res==0)
        {
            printf("Your entered wrong input. Please provide a valid input.\n");
        }
        else if(is_unique_email(addressBook, str3) == 0)
        {
            printf("Email address already exists. Please enter a different email.\n");
            res = 0;
        }
    }while(res == 0); 

    int pos = addressBook->contactCount;
    strcpy(addressBook->contacts[pos].name, str1);
    strcpy(addressBook->contacts[pos].phone, str2);
    strcpy(addressBook->contacts[pos].email, str3);

    addressBook->contactCount++;

    printf("Contact added successfully!\n");

}

// Compares two names without treating uppercase and lowercase letters differently.
static int names_match(const char *first, const char *second)
{
    while (*first != '\0' && *second != '\0')
    {
        if (tolower((unsigned char)*first) != tolower((unsigned char)*second))
        {
            return 0;
        }
        first++;
        second++;
    }

    return *first == '\0' && *second == '\0';
}

// Finds a contact by name and asks the user to choose when names are duplicated.
int search_by_name(AddressBook *addressBook)
{
    char new_name[50];
    int count = 0;
    int index = -1;

    printf("Enter the name to search : ");
    if (scanf(" %49[^\n]", new_name) != 1)
    {
        printf("Invalid name entered.\n");
        return -1;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (names_match(addressBook->contacts[i].name, new_name))
        {
            count++;
        }
    }

    if (count == 0)
    {
        printf("The entered name is not found in the contact\n");
        return -1;
    }
    if (count > 1)
    {
        printf("\nMore than one contact found with this name.\n\n");

        printf("+------+--------------------+---------------+--------------------------+\n");
        printf("| S.No | Name               | Phone         | Email                    |\n");
        printf("+------+--------------------+---------------+--------------------------+\n");

        int serial_number = 1;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (names_match(addressBook->contacts[i].name, new_name))
            {
                printf("| %-4d | %-18s | %-13s | %-24s |\n",
                       serial_number,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                serial_number++;
            }
        }

        printf("+------+--------------------+---------------+--------------------------+\n");

        int choice;

        printf("Enter S.No of the contact: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > count)
        {
            printf("Invalid selection.\n");
            return -1;
        }

        serial_number = 1;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (names_match(addressBook->contacts[i].name, new_name))
            {
                if (serial_number == choice)
                {
                    index = i;
                    break;
                }
                serial_number++;
            }
        }

        printf("\nContact found\n");
        printf("Name  : %s\n", addressBook->contacts[index].name);
        printf("Phone : %s\n", addressBook->contacts[index].phone);
        printf("Email : %s\n", addressBook->contacts[index].email);

        return index;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (names_match(addressBook->contacts[i].name, new_name))
        {
            index = i;
            break;
        }
    }

    printf("\nContact found\n");
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    return index;
}

// Finds and displays the contact that matches the entered phone number.
int search_by_phone(AddressBook *addressBook)
{
    char phone_no[20];
    printf("Enter the phone number to search : ");
    scanf(" %s",phone_no);

    for(int i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].phone,phone_no)==0)
        {
            printf("\nContact found\n");
            printf("Name : %s\n",addressBook->contacts[i].name);
            printf("Phone : %s\n",addressBook->contacts[i].phone);
            printf("Email : %s\n",addressBook->contacts[i].email);
            return i;
        }
    }

    printf("Contact with this phone number is not found\n");
    return -1;
}

// Finds and displays the contact that matches the entered email address.
int search_by_email(AddressBook *addressBook)
{
    char email_id[20];
    printf("Enter the email id to search : ");
    scanf(" %s",email_id);

    int n =addressBook->contactCount;
    for(int i=0;i<n;i++){
        if(strcmp(addressBook->contacts[i].email,email_id)==0)
        {
            printf("\nContact found\n");
            printf("Name : %s\n",addressBook->contacts[i].name);
            printf("Phone : %s\n",addressBook->contacts[i].phone);
            printf("Email : %s\n",addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Contact with this email id is not found\n");
    return -1;
}
// Lets the user choose a field and searches contacts using that field.
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf("Select any one option to search the contact\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
    int choice;

    printf("\n");
    printf("+------------------------------------------+\n");
    printf("|              SEARCH CONTACT              |\n");
    printf("+------------------------------------------+\n");
    printf("|                                          |\n");
    printf("|   1. Search by name                      |\n");
    printf("|   2. Search by phone                     |\n");
    printf("|   3. Search by email                     |\n");
    printf("|                                          |\n");
    printf("+------------------------------------------+\n");
     
    printf("Enter the choice : ");
    scanf("%d",&choice);
    // print promt

    switch(choice)
    {
        case 1:
            search_by_name(addressBook);
            break;
        case 2:
            search_by_phone(addressBook);
            break;
        case 3:
            search_by_email(addressBook);
            break;
        default:
            printf("Invalid choice selected\n");
            break;
    }

}

// Lets the user find a contact and replace one of its details with validated input.
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf("Select any one option to edit the contact\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
    int ind;
    int res;
    int choice;

     printf("\n");
    printf("+------------------------------------------+\n");
    printf("|               EDIT CONTACT               |\n");
    printf("+------------------------------------------+\n");
    printf("|                                          |\n");
    printf("|   1. Edit by name                        |\n");
    printf("|   2. Edit by phone                       |\n");
    printf("|   3. Edit by email                       |\n");
    printf("|                                          |\n");
    printf("+------------------------------------------+\n");

    printf("Enter the choice : ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
        {
            ind = search_by_name(addressBook);
            if(ind==-1)
            {
                return ;
            }

            char edit_name[50];
            do
            {
                printf("Enter the name to edit : ");
                scanf(" %[^\n]",edit_name);

                res=validate_name(edit_name);
                if(res==0)
                {
                    printf("Invalid name, give the proper name\n");
                }
            }
            while(res==0);

            strcpy(addressBook->contacts[ind].name,edit_name);
            printf("The name successfully edited\n");
            break;
        }

        case 2:
        {
            ind=search_by_phone(addressBook);
            if(ind==-1)
            {
                return ;
            }

            char edit_phone[20];
            do
            {
                printf("Enter the phone number to edit : ");
                scanf(" %[^\n]",edit_phone);

                res=validate_phone(edit_phone);
                if(res==0)
                {
                    printf("Invalid phone number, give the proper phone number\n");
                }
                else if (is_unique_phone_for_edit(addressBook, edit_phone, ind) == 0)
                {
                    printf("Phone number already exists. Please enter a different number\n");
                    res = 0;
                }
            }while(res==0);//invalid

            strcpy(addressBook->contacts[ind].phone,edit_phone);
            printf("The phone number successfully edited\n");
            break;
        }

        case 3:
        {
            ind=search_by_email(addressBook);
            if(ind==-1){
                return ;
            }

            char edit_email[50];
            do
            {
                printf("Enter the emailid to edit : ");
                scanf(" %[^\n]",edit_email);

                res=validate_email(edit_email);
                if(res==0)
                {
                    printf("Invalid email id, give the proper email id\n");
                }
                else if (is_unique_email_for_edit(addressBook, edit_email, ind) == 0)
                {
                    printf("Email address already exists. Please enter a different email\n");
                    res = 0;
                }
            }while(res==0);//invalid

            strcpy(addressBook->contacts[ind].email,edit_email);
            printf("The email successfully edited\n");
            break;
        }
        default:
            printf("Invalid choice selected\n");
            break;
    }
}

// Removes the selected contact and shifts the remaining contacts into place.
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("Select any one option to delete the contact\n");
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");

    int ind=-1;
    int choice;

    printf("\n");
    printf("+------------------------------------------+\n");
    printf("|              DELETE CONTACT              |\n");
    printf("+------------------------------------------+\n");
    printf("|                                          |\n");
    printf("|   1. Delete by name                      |\n");
    printf("|   2. Delete by phone                     |\n");
    printf("|   3. Delete by email                     |\n");
    printf("|                                          |\n");
    printf("+------------------------------------------+\n");

    printf("Enter the choice : ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
               ind=search_by_name(addressBook);
               break;
        case 2:
               ind=search_by_phone(addressBook);
               break;
        case 3:
               ind=search_by_email(addressBook);
               break;
        default:
               printf("Invalid choice selected\n");
               return;
    }
    if(ind==-1)
    {
        printf("It is not found in the contact\n");
        return;
    }
    for(int i=ind;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contacts deleted successfully\n");
}