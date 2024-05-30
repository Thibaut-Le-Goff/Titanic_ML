#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUMBER_RECORDS 1000
#define MAX_LINE_LENGTH 1024

// from https://github.com/portfoliocourses/c-example-code/blob/main/csv_to_struct_array.c
/*
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
*/

typedef struct 
{
    int passenger_id[NUMBER_RECORDS];
    int survived[NUMBER_RECORDS];
    int pclass[NUMBER_RECORDS];
    char surname[NUMBER_RECORDS][100];
    char forename[NUMBER_RECORDS][100];
    char sex[NUMBER_RECORDS][10]; // should be an int
    int age[NUMBER_RECORDS];
    int sibsp[NUMBER_RECORDS];
    int parch[NUMBER_RECORDS];
    char ticket[NUMBER_RECORDS][10]; // should be an int
    double fare[NUMBER_RECORDS];
    char cabin[NUMBER_RECORDS][10]; // should be an int
    char embarked[NUMBER_RECORDS]; //should be an int
} Passenger;


//void missing_value_case(int *record, char *line);


void missing_value_case(int *record, char *line);

int main()
{

    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 

    /*char *data_missing_values[] = {", sqrt(-1)\n", ", sqrt(-1)\n", ", sqrt(-1)\n", 
                                   ", NA\n", ", NA\n", ", NA\n", ", sqrt(-1)\n", 
                                   ", sqrt(-1)\n", ", sqrt(-1)\n", ", NA\n", ", sqrt(-1).1\n", 
                                   ", NA\n", ", NA\n"}; 
    */

    FILE *file = fopen("titanic_csv/train.csv", "r");
    
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    //Passenger passengers[NUMBER_RECORDS];
    Passenger passengers[1];
  
    int records_index = 0;
    int records_index_failed = 0;
    char line[MAX_LINE_LENGTH];


    while (fgets(line, sizeof(line), file) != NULL)
    {
        //int result_sscanf = sscanf(line,
          //         "%d, ",
            //       &passengers[records_index].passenger_id, 
        int result_sscanf = sscanf(line,
                   "%d, %d, %d, %99[^,], %99[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n",
            //       "%d, %d, %49[^,], %49[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n",
                   /*
                   &passengers[records_index].passenger_id, 
                   &passengers[records_index].survived, 
                   &passengers[records_index].pclass,
                   passengers[records_index].surname,
                   passengers[records_index].forename,
                   passengers[records_index].sex, 
                   &passengers[records_index].age, 
                   &passengers[records_index].sibsp, 
                   &passengers[records_index].parch, 
                   passengers[records_index].ticket,
                   &passengers[records_index].fare,
                   passengers[records_index].cabin,
                   &passengers[records_index].embarked); 
                   */

                   &passengers->passenger_id[records_index], 
                   &passengers->survived[records_index], 
                   &passengers->pclass[records_index],
                   passengers->surname[records_index],
                   passengers->forename[records_index],
                   passengers->sex[records_index], 
                   &passengers->age[records_index], 
                   &passengers->sibsp[records_index], 
                   &passengers->parch[records_index], 
                   passengers->ticket[records_index],
                   &passengers->fare[records_index],
                   passengers->cabin[records_index],
                   &passengers->embarked[records_index]); 
                
        if (result_sscanf == 13)
        {
            records_index++;
        }
        else
        {
            printf("Error reading line: %s, the %s is missing\n", line, data_types[result_sscanf]);
            
            missing_value_case(result_sscanf, line);           
            
            records_index_failed++;
        }
    }

    fclose(file);
  
    for (int record = 0; record < records_index; record++) {
        printf("%d, %d, %d, %s, %s, %s, %d, %d, %d, %s, %lf, %s, %c\n",
                /*
                passengers[record].passenger_id, 
                passengers[record].survived, 
                passengers[record].pclass,
                passengers[record].surname,
                passengers[record].forename,
                passengers[record].sex, 
                passengers[record].age, 
                passengers[record].sibsp, 
                passengers[record].parch, 
                passengers[record].ticket,
                passengers[record].fare,
                passengers[record].cabin,
                passengers[record].embarked
                );
                */
                passengers->passenger_id[record], 
                passengers->survived[record], 
                passengers->pclass[record],
                passengers->surname[record],
                passengers->forename[record],
                passengers->sex[record], 
                passengers->age[record], 
                passengers->sibsp[record], 
                passengers->parch[record], 
                passengers->ticket[record],
                passengers->fare[record],
                passengers->cabin[record],
                passengers->embarked[record] 
                ); 
        printf("\n");
    }

    printf("\n%d records_index read.\n\n", records_index);
    printf("\n%d records_index failed.\n\n", records_index_failed);
    return 0;
}


//Passanger *missing_value_case(char *line) {
void missing_value_case(int *record, char *line) {
    printf("dans la fonction : %s\n", line);


    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 

    /*char *data_missing_values[] = {", sqrt(-1)\n", ", sqrt(-1)\n", ", sqrt(-1)\n", 
                                   ", NA\n", ", NA\n", ", NA\n", ", sqrt(-1)\n", 
                                   ", sqrt(-1)\n", ", sqrt(-1)\n", ", NA\n", ", sqrt(-1).1\n", 
                                   ", NA\n", ", NA\n"}; 
    */

    // from https://stackoverflow.com/questions/4917030/move-cursor-x-lines-from-current-position-in-vi-vim
    char delimiter = ",";
    //char delimiter = ','; // ne fonctione pas avec 
    int delimiter_counter = 0;
    char *separated_data;
       
    //while ((separated_data = strsep(&line, ',')) != NULL) {
    while ((separated_data = strsep(&line, &delimiter)) != NULL) {
        if (*separated_data == '\0') {
            printf("the %s is missing\n", data_types[delimiter_counter]);
        }
        else {
            printf("the %s is %s\n", data_types[delimiter_counter], separated_data);
        }

        delimiter_counter++;
    }

}
