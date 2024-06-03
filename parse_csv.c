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
    int lines_number;
    char *columns_names;
    char *columns_data_type;
    
    float *float_values_to_change;
    float *float_values_of_replacement;

    char *char_values_to_change_in_int;
    float *char_to_int_values_of_replacement;

} CSV_info


typedef struct
{
    char *column_name;
    char **column_data;

    Float_column_node *next_float_node;
    Char_column_node *next_char_node;

} Char_column_node


typedef struct
{
    char *column_name;
    float *column_data;

    Float_column_node *next_float_node;
    Char_column_node *next_char_node;

} Float_column_node


Char_column_node *csv_to_linked_list_char(CSV_info *csv_raw_info, FILE* csv_raw) {
    

}

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
} CSV_Passangers;


int read_line(CSV_Passangers *passengers, int *records_index, char *line);
int value_assignation(CSV_Passangers *passengers, int *records_index, int *missing_value_indicator, char *value_assigned);

int main()
{

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


    if (fgets(line, sizeof(line), file) != NULL) {}


    while (fgets(line, sizeof(line), file) != NULL)
    {
        int read_line_result = read_line(passengers, &records_index, line);

        if (read_line_result == 1) {
            //return 1;
            records_index_failed++;
        }   
        records_index++;
    }

    fclose(file);
  
    for (int record = 0; record < records_index; record++) {
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


//Passanger *read_line(char *line) {
int read_line(CSV_Passangers *passengers, int *records_index, char *line) {
    printf("dans la fonction : %s\n", line);


    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 

   char *data_missing_values[] = {"-1", "-1", "-1", 
                                 "<N/A>", "<N/A>", "<N/A>", "-1.0", 
                                 "-1", "-1", "<N/A>", "-1.0", 
                                 "<N/A>", "N"}; 
    

    // from https://stackoverflow.com/questions/4917030/move-cursor-x-lines-from-current-position-in-vi-vim
    char *delimiter = ",";
    //char delimiter = ','; // ne fonctione pas avec 
    int delimiter_counter = 0;
    char *separated_data;
       
    //while ((separated_data = strsep(&line, ',')) != NULL) {
    while ((separated_data = strsep(&line, delimiter)) != NULL) {
        if (*separated_data == '\0') {
            printf("the %s is missing, id must be remplaced by %s\n", data_types[delimiter_counter], data_missing_values[delimiter_counter]);

            //value_assignation = 
            int result_assignation = value_assignation(passengers, records_index, &delimiter_counter, data_missing_values[delimiter_counter]);

            if (result_assignation == 0) {
                return 1;
            }
        }
        else {
            printf("the %s is %s\n", data_types[delimiter_counter], separated_data);
            int result_assignation = value_assignation(passengers, records_index, &delimiter_counter, separated_data);
            
            if (result_assignation == 0) {
                return 1;
            }
        }

        delimiter_counter++;
    }

    return 0;
}



int value_assignation(CSV_Passangers *passengers, int *records_index, int *missing_value_indicator, char *value_assigned) {

    char *data_type[] = {"%d", "%d", "%d", "%99[^,]", "%99[^,]", "%9[^,]", "%d", "%d", "%d", "%9[^,]", "%lf", "%9[^,]", "%c\n"};
    int result_sscanf;

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

        return result_sscanf;            
}
