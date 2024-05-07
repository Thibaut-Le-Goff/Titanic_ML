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


void missing_value_case(char *line);
static char *strtok_fixed(char *str, char const *delims);

int main()
{

    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 

    /*char *data_missing_values[] = {", -1\n", ", -1\n", ", -1\n", 
                                   ", NA\n", ", NA\n", ", NA\n", ", -1\n", 
                                   ", -1\n", ", -1\n", ", NA\n", ", -1.1\n", 
                                   ", NA\n", ", NA\n"}; 
    */

    FILE *file = fopen("titanic_csv/train.csv", "r+");
    
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
        //int result_sscanf = sscanf(line,
          //         "%d, ",
            //       &passengers[records].passenger_id, 
        int result_sscanf = sscanf(line,
                   "%d, %d, %d, %49[^,], %49[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n",
            //       "%d, %d, %49[^,], %49[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n",
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
            
            missing_value_case(line);           
            /*
            strcat(line, data_missing_values[result_sscanf]);
            fseek(file, -1, SEEK_CUR);
            fputs(line, file);
            */
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


//Passanger *missing_value_case(char *line) {
void missing_value_case(char *line) {
    printf("%s\n", line);


    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 

    /*char *data_missing_values[] = {", -1\n", ", -1\n", ", -1\n", 
                                   ", NA\n", ", NA\n", ", NA\n", ", -1\n", 
                                   ", -1\n", ", -1\n", ", NA\n", ", -1.1\n", 
                                   ", NA\n", ", NA\n"}; 
    */


    char delimiter = ',';
    int delimiter_counter = 0;

    for (int array_iterator = 1; line[array_iterator] != '\0'; array_iterator++) {

        
        if (line[array_iterator - 1] == delimiter) {
            delimiter_counter++;
        }

        if (line[array_iterator - 1] == delimiter && line[array_iterator] == delimiter) {
            printf("missing value !\n");
            printf("The %s is missing !\n", data_types[delimiter_counter]);
            // un choix doit être fait en fonction de delimiter_counter 
            // qui determine quel donnée manque
        }
        
        //printf("%c ", line[array_iterator]);
    }

    char *token = strtok(line, ",");
    //char *token = strtok_fixed(line, ",");
    
    //for (int nb_datas = 0; nb_datas < 13; nb_datas++) {
    while (token != NULL) {
        //printf("%s\n", line);
        //if (strlen(token) == 0) 
        if (token == "NULL") 
        {
            printf("NULL\n");
        } 
        else 
        {
             printf("%s\n", token);
        }

        token = strtok(NULL, ",");
    }
    
    /*
    //for (string_index = 0; string_index > strlen(line); string_index++) {
    for (int array_iterator = 1; *(line + array_iterator) != '\0'; ++array_iterator) {        
        
        printf("%s\n", *(line + array_iterator));

        if (*(line + array_iterator) == ',') {
        //if (*(line + array_iterator) == ',' && *(line + array_iterator - 1) == ',') {
            printf("missing value !");
        }
        //sum_xor_ascii_characters += *(table + array_iterator - 1) ^ *(table + array_iterator);
    }
    */
}    

//https://stackoverflow.com/questions/30294129/i-need-a-mix-of-strtok-and-strtok-single/30295426#30295426
static char *strtok_fixed(char *line, char const *delimiter) {

    static char  *src = NULL;
    char  *p,  *ret = 0;
    //char *ret = 0;

    
    if (line != NULL) {
        src = line;
    }
    

    if (src == NULL || *src == '\0') {
    //if (line == NULL || *line == '\0') {
        return NULL;
    }

    ret = src;

    // if there is no
    //char *p = strpbrk(src, delimiter);
    
    //if (p != NULL)
    if ((p = strpbrk(src, delimiter)) != NULL)
    {
        *p  = 0;
        src = ++p;
    }
    else 
    {
        src += strlen(src);
    }

    return ret;
}
