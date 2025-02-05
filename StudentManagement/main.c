#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 100

typedef struct StudentStruct{
    char *name;
    unsigned int id;
    float score_maths;
    float score_physics;
    float score_informatics;
} Student;

int fetch_student_list(char* filename, Student* student_list){
    //Student* student_list = malloc(MAX_STUDENT * sizeof(Student));

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
            //printf("%s ", content);
            student_list[index].name = content;
            printf("%s ", student_list[index].name);
            /*
            if(strcmp(student_list[index].name, content) == 0){
                printf("%s ", student_list[index].name);
            }
            else{
                
                printf("false ");
            }
            */
            break;
        case 1:
            student_list[index].id = atoi(content);
            //printf("%d - index - %s \n", i, content);
            break;
        case 2:
            student_list[index].score_maths = atof(content);
            //printf("%d - index - %s \n", i, content);
            break;
        case 3:
            student_list[index].score_physics = atof(content);
            //printf("%d - index - %s \n", i, content);
            break;
        case 4:
            student_list[index++].score_informatics = atof(content);
            //printf("%d - index - %s \n", i, content);
            break;
        default:
            break;
        }
        i++;
    };

    fclose(open_db);

    return index+1;
}

void updateStudentScore(int search_id, int option, int replace, Student* student_list){
    int index;
    for(int i = 0; i < MAX_STUDENT; i++){
        if(student_list[i].id == search_id){
            index = search_id;
            break;
        }
    }
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

void writeDB(char * filename, int len, Student* student_list){
    FILE* db;
    db = fopen(filename, "w");
    fclose(db);

    // Open a file in append mode
    db = fopen("filename.txt", "a");
    int i = 0;
    while(i < len){
        fprintf(db, "%s\n", student_list[i].name);
        fprintf(db, "%d\n" ,student_list[i].id);
        fprintf(db, "%e\n", student_list[i].score_maths);
        fprintf(db, "%e\n", student_list[i].score_physics);
        fprintf(db, "%e\n", student_list[i++].score_informatics);
    }
    fclose(db);
}

void interface_loop(){
    printf("STUDENT MANAGEMENT SYSTEM \n");

    while(1){
        printf("SELECT OPTIONS \n");
        printf("1. GET INFO \n");
        printf("2. GET STUDENT INFO BASED ON ID \n");
        printf("3. UPDATE A STUDENT'S INFO BASED ON ID \n");
        printf("4. SAVE AND CLOSE \n");

        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 4:
            goto exit_program;
            break;
        
        default:
            printf("UNDEFINED OPTION. CLOSE BY DEFAULT");
            goto exit_program;
            break;
        }
    }

    exit_program: printf("Exiting the program.\n");
}

int main(){
    Student* student_list = malloc(MAX_STUDENT * sizeof(Student));
    int number_of_students = fetch_student_list("database.txt", student_list);
    printf("\n");
    printf("%s ", student_list[0].name);
    printf("\n");
    printf("%d", strcmp(student_list[0].name, "John Doe"));
    printf("\n");
    printf("%.1f", student_list[0].score_informatics);
    printf("\n");
}

