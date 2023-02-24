#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

//Function Prototypes
void split_csv_lines(char *buffer, char **struct_fields);
node *append(node *head, char **fields);
void printList(node *head);

int main()
{
    FILE *fp = fopen("biostats.csv", "r");

    //If the file pointer is null, exit the program
    if(fp == NULL)
    {
        printf("Can't open file.");
        return -1;
    }

    char buffer[1024];
    /*The linked list struct has 5 variable fields in it
      each field has to be read in every csv line*/
    char *struct_fields[5];
    node *head = NULL;

    /*this fgets will skip the first line of the csv file that only lists the names of the columns*/
    fgets(buffer, 1024, fp);

    while(fgets(buffer, 1024, fp) != NULL)
    {
        split_csv_lines(buffer, struct_fields);   
        head = append(head, struct_fields);
    }
    fclose(fp);
    printList(head);
    return 0;
}

void split_csv_lines(char *buffer, char **struct_fields)
{
    int i = 0;
    //strtok will break up the string (line) at every occurence of ", " and store the token (value)
    char *value = strtok(buffer, ", ");
    //The while loop will loop through the tokens (values) until a NULL value is returned
    while(value != NULL)
    {
        //struct_fields will store each value which will be put in a node
        struct_fields[i] = malloc(strlen(value));
        strcpy(struct_fields[i], value);
        //Grabbing the next value
        value = strtok(NULL, ", ");
        i++;
    }
}

node *append(node *head, char **fields)
{
    node *curr, *tmp;
    tmp = malloc(sizeof(node));

    //Setting the struct fields to the appropriate value from fields (struct_fields from split_csv_lines)
    tmp -> name = *fields;

    tmp -> sex = malloc(strlen(fields[1]));
    strcpy(tmp -> sex, fields[1]);

    tmp -> age = malloc(strlen(fields[2]));
    strcpy(tmp -> age, fields[2]);

    tmp -> height = malloc(strlen(fields[3]));
    strcpy(tmp -> height, fields[3]);

    tmp -> weight = malloc(strlen(fields[4]));
    strcpy(tmp -> weight, fields[4]);

    //If head is NULL then it is set equal to the temp node with the new info (most current node)
    //If head is not NULL then we cycle through to the end of the list and set the temp (most current) node there
    curr = head;
    if(head == NULL)
    {
        head = tmp;
    }
    else
    {
        while(curr -> next != NULL)
        {
            curr = curr -> next;
        }
        curr -> next = tmp;
    }
    return head;
}

void printList(node *head) 
{
   //Prints the linked list from the beginning
    while(head -> next != NULL)
    {
      printf("Name: %s, Sex: %s, Age: %s, Height: %s, Weight: %s\n",head->name, head->sex, head->age, head->height, head->weight);
      head = head->next;
    }
}