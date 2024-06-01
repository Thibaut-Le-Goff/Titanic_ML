#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUMBER_RECORDS 1000
#define MAX_LINE_LENGTH 1024

// from https://github.com/portfoliocourses/c-example-code/blob/main/csv_to_struct_array.c

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
} CSV_Passangers;


void missing_value_case(CSV_Passangers *passengers, int *records_index, char *line);
void missing_value_replacement(CSV_Passangers *passengers, int *records_index, int *missing_value_indicator, char *value_assigned);

int main()
{

    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 

    FILE *file = fopen("titanic_csv/train.csv", "r");
    
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    CSV_Passangers passengers[1];
  
    int records_index = 0;
    int records_index_failed = 0;
    char line[MAX_LINE_LENGTH];


    while (fgets(line, sizeof(line), file) != NULL)
    {
        //int result_sscanf = sscanf(line,
          //         "%d, ",
            //       &passengers[records_index].passenger_id, 
        /*
        int result_sscanf = sscanf(line,
                   "%d, %d, %d, %99[^,], %99[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n",
            //       "%d, %d, %49[^,], %49[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n",
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
            
            //missing_value_case(&result_sscanf, line);           
            missing_value_case(passengers, &records_index, line);           
            
            records_index_failed++;
        }
        */
        missing_value_case(passengers, &records_index, line);
        records_index++;
    }

    fclose(file);
  
    //records_index = 4;

    for (int record = 1; record < records_index; record++) {
        printf("%d, %d, %d, %s, %s, %s, %d, %d, %d, %s, %lf, %s, %c\n",
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
void missing_value_case(CSV_Passangers *passengers, int *records_index, char *line) {
    printf("dans la fonction : %s\n", line);


    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 

   char *data_missing_values[] = {"-1", "-1", "-1", 
                                 "<N/A>", "<N/A>", "<N/A>", "-1.0", 
                                 //"<N/A>", "<N/A>", "<N/A>", "float(FLT_MIN)", 
                                 "-1", "-1", "<N/A>", "-1.0", 
                                 "<N/A>", "N"}; 
    
   //char *data_type[] = {"%d, %d, %d, %99[^,], %99[^,], %9[^,], %d, %d, %d, %9[^,], %lf, %9[^,], %c\n"};

    // from https://stackoverflow.com/questions/4917030/move-cursor-x-lines-from-current-position-in-vi-vim
    char *delimiter = ",";
    //char delimiter = ','; // ne fonctione pas avec 
    int delimiter_counter = 0;
    char *separated_data;
       
    //while ((separated_data = strsep(&line, ',')) != NULL) {
    while ((separated_data = strsep(&line, delimiter)) != NULL) {
        if (*separated_data == '\0') {
            printf("the %s is missing, id must be remplaced by %s\n", data_types[delimiter_counter], data_missing_values[delimiter_counter]);

            //missing_value_replacement = 
            missing_value_replacement(passengers, records_index, &delimiter_counter, data_missing_values[delimiter_counter]);
        }
        else {
            printf("the %s is %s\n", data_types[delimiter_counter], separated_data);
            missing_value_replacement(passengers, records_index, &delimiter_counter, separated_data);
        }

        delimiter_counter++;
    }
}



void missing_value_replacement(CSV_Passangers *passengers, int *records_index, int *missing_value_indicator, char *value_assigned) {

   /*     
   char *data_missing_values[] = {"sqrt(-1)\n", "sqrt(-1)\n", "sqrt(-1)\n", 
                                 "<N/A>\n", "<N/A>\n", "<N/A>\n", ", sqrt(-1)\n", 
                                 "sqrt(-1)\n", "sqrt(-1)\n", "<N/A>\n", "sqrt(-1)\n", 
                                 "<N/A>\n", "<N/A>\n"}; 
    */

    char *data_type[] = {"%d", "%d", "%d", "%99[^,]", "%99[^,]", "%9[^,]", "%d", "%d", "%d", "%9[^,]", "%lf", "%9[^,]", "%c\n"};
    int result_sscanf = 0;

    switch(*missing_value_indicator) {
        case 0:
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        &passengers->passenger_id[*records_index]);
            break;
        case 1: 
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        &passengers->survived[*records_index]);
            break;
        case 2:
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        &passengers->pclass[*records_index]);
            break;
        case 3:
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        passengers->surname[*records_index]);
            break;
        case 4:
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        passengers->forename[*records_index]);
            break;
        case 5: //
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        passengers->sex[*records_index]);
            break;
        case 6: //
            result_sscanf = sscanf(value_assigned, 
                                         data_type[*missing_value_indicator], 
                                         &passengers->age[*records_index]);
            break;
        case 7: //
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        &passengers->sibsp[*records_index]);
            break;
        case 8: //
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        &passengers->parch[*records_index]);
            break;
        case 9: //
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        passengers->ticket[*records_index]);
            break;
        case 10: //
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        &passengers->fare[*records_index]);
            break;
        case 11: //
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        passengers->cabin[*records_index]);
            break;
        case 12: //marche pas
            result_sscanf = sscanf(value_assigned, 
                                        data_type[*missing_value_indicator], 
                                        &passengers->embarked[*records_index]);
            break;              
    } 
}
