#include <stdio.h>
#include "file.h"

// Writes the contact count and all contact details to the CSV file.
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.csv","w");
    if(fptr == NULL)
    {
        printf("The file is not opened.\n");
        return;
    }
    printf("The file is opened successfully\n");
    fprintf (fptr,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

// Reads the contact count and contact details from the CSV file into memory.
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv","r");
    if(fptr == NULL)
    {
        printf("The file is not opened.\n");
        return;
    }
    fscanf(fptr,"#%d\n",&addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}