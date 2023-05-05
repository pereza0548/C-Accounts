/*Name: Alexandra Perez
Date: 4/27/2023
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

// Define a struct to represent a row in the CSV file
typedef struct Row
{
    int id;
    char name[100];
    float balance;
} Row;
void topFive (struct Row r[], int n);

void main(int argc, char *argv[])
{
    // first argument is the name of the program
    // second argument is the name of the file to open
    char filename[] = "accounts.csv";
    FILE *fp = fopen(filename, "r");

    
    if (fp == NULL)
    {
        printf("Failed to open file: %s\n", filename);  
    }
    
    // Read the header row
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, fp);

    // Initialize an array to store the rows
    Row rows[1000];
    int num_rows = 0;
    float total_bal=0;

    // Read each row and store it in the array
    while (fgets(line, MAX_LINE_SIZE, fp))
    {
        char *token;
        token = strtok(line, ",");
        rows[num_rows].id = atoi(token);

        token = strtok(NULL, ",");
        strncpy(rows[num_rows].name, token, sizeof(rows[num_rows].name));

        token = strtok(NULL, ",");
        // remove first character ($)
        token++;
        rows[num_rows].balance = atof(token);
        total_bal += rows[num_rows].balance;

        num_rows++;
    }
    printf("Total accounts: %d\n", num_rows);
    printf("Total balance: $%.2f\n\n", total_bal); 
    printf("Top 5 accounts: \n");
 
 //call function to find reorder with the highest balance to lowest
    topFive(rows, num_rows);
//loop for the 5 accounts with the highest balance
    for(int i=0; i<5;i++)
    {
        printf("%s: $%.2f\n", rows[i].name, rows[i].balance);
    }

    fclose(fp);

} 

//create function
void topFive (struct Row r[], int n)
{
    int i, j;
    struct Row temp;
    //create for loop to compare array postions with each other
    for(i=0; i<n-1;i++)
    {
        for(j=i+1; j<n;j++) // compare array postion i with the postion 1 more than it
        {
            if(r[i].balance<r[j].balance) // compare the balances
            {
                temp = r[i]; // save what is originally in r[i] spot
                r[i]=r[j]; // move position j to position i if j's integer is less than i
                r[j]=temp; // move postion i's integer to postion j
            }
        }
    }
    
}