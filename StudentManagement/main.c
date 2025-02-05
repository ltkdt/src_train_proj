#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 100

typedef struct StudentStruct{
    char name[100];
    unsigned int id;
    float score_maths;
    float score_physics;
    float score_informatics;
} Student;

// Store the students' info into a list and return the number of students
int fetch_student_list(char* filename, Student* student_list_ref){  
    //Student* student_list_ref = malloc(MAX_STUDENT * sizeof(Student));

    FILE* open_db;
    open_db = fopen(filename, "r");

    char content[100];
    char* terminate = "END";
    
    int i = 0, index = 0;
    // Read the content and store it inside myString
    while(fgets(content, 100, open_db)){
        content[strcspn(content, "\n")] = 0;
        
        if(strcmp(content, terminate) == 0){
            break;
        }
    
        switch (i % 6)
        {
        case 0:
            strcpy(student_list_ref[index].name, content);
            //student_list_ref[index].name = content;
            break;
        case 1:
            student_list_ref[index].id = atoi(content);
            break;
        case 2:
            student_list_ref[index].score_maths = atof(content);
            break;
        case 3:
            student_list_ref[index].score_physics = atof(content);
            break;
        case 4:
            student_list_ref[index++].score_informatics = atof(content);
            break;
        default:
            break;
        }
        i++;
    };

    return index;
}

void writeDB(char* filename, int len, Student* student_list){
    FILE* db;
    db = fopen(filename, "w");
    fclose(db);

    // Open a file in append mode
    db = fopen(filename, "a");
    int i = 0;
    while(i < len){
        fprintf(db, "%s\n", student_list[i].name);
        fprintf(db, "%d\n" ,student_list[i].id);
        fprintf(db, "%.1f\n", student_list[i].score_maths);
        fprintf(db, "%.1f\n", student_list[i].score_physics);
        if(i == len - 1){
            fprintf(db, "%.1f\n", student_list[i++].score_informatics);
        }
        else{
            fprintf(db, "%.1f\n\n", student_list[i++].score_informatics);
        }
    }
    fprintf(db, "%s", "END");
    fclose(db);
}

void updateStudentScore(int search_id, int option, int replace, Student* student_list){
    int index;
    for(int i = 0; i < MAX_STUDENT; i++){
        if(student_list[i].id == search_id){
            index = i;
            break;
        }
    }
    if(index == -1){
        printf("NO STUDENT WITH THIS ID FOUND \n");
    }
    else{
        switch (option)
        {
        case 1:
            student_list[index].score_maths = replace; 
            break;
        case 2:
            student_list[index].score_physics = replace;
            break;
        case 3:
            student_list[index].score_informatics = replace;
        default:
            break;
        }
    }
}

void add_student_to_list(Student* student_list, int *len_ptr, char name[100], int id, float score_maths, float score_physics, float score_informatics){
    if( ++*len_ptr == 101 ){
        printf("STUDENT LIMIT EXCEEDED. NO CHANGE\n");
        *len_ptr--;
    }
    else{
        strcpy(student_list[*len_ptr - 1].name, name);
        student_list[*len_ptr - 1].id = id;
        student_list[*len_ptr - 1].score_maths = score_maths;
        student_list[*len_ptr - 1].score_physics = score_physics;
        student_list[*len_ptr - 1].score_informatics = score_informatics;
        printf("NEW STUDENT ADDED\n");
    }
}

void delete_student(Student* student_list, int search_id, int *len_ptr){
    int index = -1;
    for(int i = 0; i < MAX_STUDENT; i++){
        if(student_list[i].id == search_id){
            index = i;
            break;
        }
    }
    if(index == -1){
        printf("NO STUDENT WITH THIS ID FOUND\n");
    }
    else{
        printf("%d \n", *len_ptr);
        for(int i = index; i < *len_ptr - 1; i++){
            strcpy(student_list[i].name, student_list[i+1].name);
            student_list[i].id = student_list[i+1].id;
            student_list[i].score_maths = student_list[i+1].score_maths;
            student_list[i].score_physics = student_list[i+1].score_physics;
            student_list[i].score_informatics = student_list[i+1].score_informatics;
        }
        *len_ptr -= 1;
        printf("%d \n", *len_ptr);
        printf("DELETED\n");
    }
}

void display_info_single(Student* student_list, int search_id){
    int index = -1;
    for(int i = 0; i < MAX_STUDENT; i++){
        if(student_list[i].id == search_id){
            index = i;
            break;
        }
    }
    if(index == -1){
        printf("NO STUDENT WITH THIS ID FOUND\n");
    }
    else{
        printf("STUDENT NAME: %s \n", student_list[index].name);
        printf("STUDENT_ID: %d \n", student_list[index].id);
        printf("MATHS SCORE: %.1f \n", student_list[index].score_maths);
        printf("PHYSICS SCORE: %.1f \n", student_list[index].score_physics);
        printf("INFORMATICS SCORE: %.1f \n", student_list[index].score_informatics);
    }
    
}

void display_info(Student* student_list, int len){
    printf("-----------------------------------------------------------------\n");
    for(int i = 0; i < len; i++){
        printf("STUDENT NAME: %s \n", student_list[i].name);
        printf("STUDENT_ID: %d \n", student_list[i].id);
        printf("MATHS SCORE: %.1f \n", student_list[i].score_maths);
        printf("PHYSICS SCORE: %.1f \n", student_list[i].score_physics);
        printf("INFORMATICS SCORE: %.1f \n", student_list[i].score_informatics);
        printf("\n                                          *\n");
    }
    printf("TOTAL NUMBER OF STUDENT: %d\n", len);
    printf("-----------------------------------------------------------------\n\n\n");
} 


int main(){
    Student* student_list = malloc(MAX_STUDENT * sizeof(Student));
    
    int number_of_students = fetch_student_list("database.txt", student_list);
    
    printf("STUDENT MANAGEMENT SYSTEM \n");

    while(1){
        printf("SELECT OPTIONS \n");
        printf("1. GET INFO \n");
        printf("2. GET STUDENT INFO BASED ON ID \n");
        printf("3. UPDATE A STUDENT'S INFO BASED ON ID \n");
        printf("4. ADD A STUDENT\n");
        printf("5. DELTE STUDENT BASED ON ID\n");
        printf("6. SAVE \n");
        printf("7. CLOSE \n");

        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            display_info(student_list,number_of_students);
            break;
        case 2:
            printf("TYPE THE ID OF THE STUDENT YOU WANT TO FIND: \n");
            int id_2;
            scanf("%d", &id_2);
            display_info_single(student_list, id_2);
            break;
        case 3:
            printf("TYPE OF ID OF THE STUDENT YOU WANT TO CHANGE\n");
            int id, option;
            float replace;
            scanf("%d", &id);
            printf("1. MATHS 2. PHYSICS 3. INFORMATICS | CHOOSE AN OPTION THEN TYPE THE NEW VALUE\n");
            scanf("%d", &option);
            scanf("%f", &replace);
            updateStudentScore(id, option, replace, student_list);
            break;
        case 4:
            char newname[100];
            int new_id;
            float score_maths, score_physics, score_informatics;
            printf("NEW NAME: \n");
            scanf("%s", newname);
            printf("ID: \n");
            scanf("%d", &new_id);
            printf("SCORE MATHS:\n" );
            scanf("%f", &score_maths);
            printf("SCORE PHYSICS:\n");
            scanf("%f", &score_physics);
            printf("SCORE INFORMATICS:\n");
            scanf("%f", &score_informatics);
            add_student_to_list(student_list, &number_of_students, newname, new_id, score_maths, score_physics, score_informatics);
            break;
        case 5:
            printf("TYPE OF ID OF THE STUDENT YOU WANT TO CHANGE\n");
            int id_find;
            scanf("%d", &id_find);
            delete_student(student_list, id_find, &number_of_students);
            break;
        case 6:
            writeDB("database.txt", number_of_students, student_list);
            break;
        case 7:
            goto exit_program;
            break;
        default:
            printf("UNDEFINED OPTION. CLOSE BY DEFAULT\n");
            goto exit_program;
            break;
        }
    }

    exit_program: printf("Exiting the program.\n");


    free(student_list);
}

