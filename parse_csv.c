#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUMBER_RECORDS 1000
#define MAX_LINE_LENGTH 1024

#define LENGTH_SHORT_CHAR 10
#define LENGTH_LONG_CHAR 100


// from https://github.com/portfoliocourses/c-example-code/blob/main/csv_to_struct_array.c



typedef struct 
{
    int lines_number;
    int columns_number;

    char **columns_names;
    char **columns_data_type;
    
} CSV_info;


typedef struct Column_node Column_node;

struct Column_node
{
    char *column_name;
    
    char **char_column_data;
    float *float_column_data;

    Column_node *next_column_node;
};



Column_node *csv_to_linked_list(CSV_info *csv_raw_info);
//Column_node *csv_to_linked_list(CSV_info *csv_raw_info, FILE *csv_raw);
//Column_node *create_column_node();
Column_node *create_column_node(CSV_info *csv_raw_info, int *iterator_linked_list);
//int free_csv_linked_list(CSV_info *csv_raw_inf, Column_node *scv_linked_list);
int free_csv_linked_list(Column_node *scv_linked_list);
char **malloc_column_char();


Column_node *csv_to_linked_list(CSV_info *csv_raw_info) {
//Column_node *csv_to_linked_list(CSV_info *csv_raw_info, FILE *csv_raw) {

    // to get the number of column
    //int size_array_data_type = sizeof(csv_raw_info->columns_data_type)/sizeof(csv_raw_info->columns_data_type[0]);
    //int size_array_data_type = sizeof(csv_raw_info->columns_data_type)/sizeof(**(csv_raw_info->columns_data_type));
    //printf("the number of column is of %d\n", size_array_data_type);
    int iterator_data_type = 0;
    Column_node *scv_linked_list = create_column_node(csv_raw_info, &iterator_data_type);
    iterator_data_type++;
    // the iterator must start at because the first column has already
    // been created
    Column_node *tmp_column_node = scv_linked_list;

    //for (int iterator_data_type = 1; iterator_data_type < size_array_data_type; iterator_data_type++) {
for (iterator_data_type = 1; iterator_data_type < csv_raw_info->columns_number; iterator_data_type++) {

        //tmp_column_node->next_column_node = create_column_node();
        tmp_column_node->next_column_node = create_column_node(csv_raw_info, &iterator_data_type);

        tmp_column_node = tmp_column_node->next_column_node;
    }

    return scv_linked_list;
}



Column_node *create_column_node(CSV_info *csv_raw_info, int *iterator_data_type) {
//Column_node *create_column_node() {

    Column_node *new_column_node = malloc(sizeof(Column_node));

    new_column_node->column_name = csv_raw_info->columns_names[*iterator_data_type];


    char *column_data_type = csv_raw_info->columns_data_type[*iterator_data_type];
    int nb_lines = csv_raw_info->lines_number;

    if (strcmp(column_data_type, "%f") == 0) {
        float *float_column = malloc(sizeof(float) * nb_lines);
        //float float_column[csv_raw_info->lines_number];

        new_column_node->float_column_data = float_column;
        new_column_node->char_column_data = NULL;
    }
    else if (strcmp(column_data_type, "%99[^,]") == 0) { 
        //char *char_column[csv_raw_info->lines_number][LENGTH_LONG_CHAR];
        char **char_column = malloc_column_char(&nb_lines);
        
        new_column_node->float_column_data = NULL;   
        new_column_node->char_column_data = &char_column;
    }
    else if (strcmp(column_data_type, "%9[^,]") == 0) {
        //char *char_column[csv_raw_info->lines_number][LENGTH_SHORT_CHAR];
        char **char_column = malloc_column_char(&nb_lines);
        
        new_column_node->float_column_data = NULL;   
        new_column_node->char_column_data = char_column;
    }


    new_column_node->next_column_node = NULL;

    return new_column_node;
}


char **char_column = malloc_column_char(int *nb_lines) {
    column_char = (**char)malloc(sizeof(*char) * *nb_lines);
}


int free_csv_linked_list(Column_node *scv_linked_list) {
//int free_csv_linked_list(CSV_info *csv_raw_info, Column_node *scv_linked_list) {
    
    // to get the number of column
    //int size_array_data_type = sizeof(csv_raw_info->columns_data_type)/sizeof(**(csv_raw_info->columns_data_type));


    // we free the linked list from the start
    Column_node *tmp_column_node = scv_linked_list;
    Column_node *node_to_free;

    while (tmp_column_node != NULL) {
    //for (int iterator_linked_list = 0; iterator_linked_list < size_array_data_type; iterator_linked_list++) {
        // we want to free tmp
        node_to_free = tmp_column_node;
        // but we need to keep the linked list
        // if we don't want to lose it 
        tmp_column_node = node_to_free->next_column_node;

        free(node_to_free);
    }



    if (scv_linked_list == NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

typedef struct 
{
    float passenger_id[NUMBER_RECORDS];
    float survived[NUMBER_RECORDS];
    float pclass[NUMBER_RECORDS];
    char surname[NUMBER_RECORDS][100];
    char forename[NUMBER_RECORDS][100];
    char sex[NUMBER_RECORDS][10]; // should be an int
    float age[NUMBER_RECORDS];
    float sibsp[NUMBER_RECORDS];
    float parch[NUMBER_RECORDS];
    char ticket[NUMBER_RECORDS][10]; // should be an int
    float fare[NUMBER_RECORDS];
    char cabin[NUMBER_RECORDS][10]; // should be an int
    char embarked[NUMBER_RECORDS][10]; //should be an int
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



    char *columns_names[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 
    char *data_types[] = {"%f", "%f", "%f", "%99[^,]", "%99[^,]", "%9[^,]", "%f", "%f", "%f", "%9[^,]", "%f", "%9[^,]", "%9[^,]"};

    CSV_info *csv_raw_info = malloc(sizeof(CSV_info));
    csv_raw_info->lines_number = 891;
    csv_raw_info->columns_number = 13;
    csv_raw_info->columns_names = columns_names;
    csv_raw_info->columns_data_type = data_types;

    Column_node *scv_linked_list = csv_to_linked_list(csv_raw_info);


    int free_status = free_csv_linked_list(scv_linked_list);
    //int free_status = free_csv_linked_list(csv_raw_info, scv_linked_list);
    free(csv_raw_info);


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
  
    for (int record = 890; record < records_index; record++) {
        printf("%f, %f, %f, %s, %s, %s, %f, %f, %f, %s, %f, %s, %s",
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
    
    if (free_status == 0) {
        return 0;
    } 
    else 
    {
        return 1;
    }
}


//Passanger *read_line(char *line) {
int read_line(CSV_Passangers *passengers, int *records_index, char *line) {
    //printf("dans la fonction : %s\n", line);

    /*
    char *data_types[] = {"passenger_id", "survived", "pclass", 
                          "surname", "forename", "sex", "age", 
                          "sibsp", "parch", "ticket", "fare", 
                          "cabin", "embarked"}; 
    */
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
            //printf("the %s is missing, id must be remplaced by %s\n", data_types[delimiter_counter], data_missing_values[delimiter_counter]);

            //value_assignation = 
            int result_assignation = value_assignation(passengers, records_index, &delimiter_counter, data_missing_values[delimiter_counter]);

            if (result_assignation == 0) {
                return 1;
            }
        }
        else {
            //printf("the %s is %s\n", data_types[delimiter_counter], separated_data);
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

    char *data_type[] = {"%f", "%f", "%f", "%99[^,]", "%99[^,]", "%9[^,]", "%f", "%f", "%f", "%9[^,]", "%f", "%9[^,]", "%9[^,]"};
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
