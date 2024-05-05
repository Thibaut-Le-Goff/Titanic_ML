#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_RECORDS 1000
#define MAX_LINE_LENGTH 1024

typedef struct 
{
    int passenger_id;
    int survived;
    int pclass;
    char surname[50];
    char forename[50];
    char sex[10]; // should be an int
    int age;
    int sibsp;
    int parch;
    char ticket[10]; // should be an int
    double fare;
    char cabin[10]; // should be an int
    char embarked; //should be an int
} Passenger;

int main()
{

    char *data_types[] = {"passenger_id", "survived", "pclass", "surname", "forename", "sex", "age", "sibsp", "parch", "ticket", "fare", "cabin", "embarked"}; 

    FILE *file = fopen("titanic_csv/train.csv", "r");
    
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    Passenger passengers[NUMBER_RECORDS];
  
    int records = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int result_sscanf = sscanf(line,
                   "%d, %d, %d, %49[^,], %49[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n",
                   &passengers[records].passenger_id, 
                   &passengers[records].survived, 
                   &passengers[records].pclass,
                   passengers[records].surname,
                   passengers[records].forename,
                   passengers[records].sex, 
                   &passengers[records].age, 
                   &passengers[records].sibsp, 
                   &passengers[records].parch, 
                   passengers[records].ticket,
                   &passengers[records].fare,
                   passengers[records].cabin,
                   &passengers[records].embarked); 
                
        if (result_sscanf == 13)
        {
            records++;
        }
        else
        {
            printf("Error reading line: %s, the %s is missing\n", line, data_types[result_sscanf]);
        }
    }

    fclose(file);
  
    printf("\n%d records read.\n\n", records);
  
    for (int record = 0; record < records; record++) {
        printf("%d, %d, %d, %s, %s, %s, %d, %d, %d, %s, %lf, %s, %c\n",
                passengers[record].passenger_id, 
                passengers[record].survived, 
                passengers[record].pclass,
                passengers[records].surname,
                passengers[records].forename,
                passengers[record].sex, 
                passengers[record].age, 
                passengers[record].sibsp, 
                passengers[record].parch, 
                passengers[record].ticket,
                passengers[record].fare,
                passengers[record].cabin,
                passengers[record].embarked
                );
        printf("\n");
    }

    return 0;
}

