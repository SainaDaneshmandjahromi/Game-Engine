#include "header.h"

extern struct Data* head;
struct Point box;

int read_map(char *filename,char map[][1000]){

    FILE *fptr;
    fptr = fopen(filename, "r");

    if(!fptr){
        system("COLOR BC");
        printf("\tNo File Named %s in relative Folder\n\t", filename);
        getch();
        return 0;
    }
    char ch;
    int flag = 0;
    int width = 0;
    int height = 0;

    char wall = splitter(head, 1, "wall").type_result.character;
    while((ch = fgetc(fptr))!= wall){
        if(flag == 1 && ch != 'x')
            if(ch >= '0' && ch <= '9'){
                width = width * 10 + ch - '0';
            }
        if(ch == 'x')
            flag = 1;
        if(flag == 0 && ch != wall){
            if(ch >= '0' && ch <= '9')
                height = height * 10 + ch - '0';
        }

    }


    box.x = width;
    box.y = height;

    int row = 0, col = 0;
    map[row][col++] = ch;
    while((ch = fgetc(fptr)) != EOF){
        if(ch == '\n'){
            map[row][col++] = ch;
            map[row++][col] = '\0';
            col = 0;
        }
        else
            map[row][col++] = ch;
    }
    fclose(fptr);
    return 1;
}

int read_game(char *filename){

    FILE *fptr;
    fptr = fopen(filename, "r");
    if(!fptr){
        system("COLOR BC");
        printf("\tNo File Named %s in relative Folder\n\t", filename);
        getch();
        return 0;
    }

    int counter = 0;
    char ch;
    int flag = 0;

    char *usage = (char *)malloc(15 * sizeof(char));
    char *characters = (char *)malloc(10 * sizeof(char));
    while((ch = fgetc(fptr)) != EOF){
        if(flag == 0 && ch != '=')
            usage[counter++] = ch;
        else if(ch == '='){
            flag = 1;
            usage[counter] = '\0';
            counter = 0;
        }
        else if(flag == 1 && ch != '\n')
            characters[counter++] = ch;
        else; if(ch == '\n'){
            characters[counter] = '\0';
            head = insertData(head, usage, characters);
            usage = (char *)malloc(15 * sizeof(char));
            characters = (char *)malloc(10 * sizeof(char));counter = 0;
            flag = 0;
        }

    }
    characters[counter] = '\0';
    head = insertData(head, usage, characters);
    fclose(fptr);
    return 1;
}

void put_information_in_file(char *message){

    FILE *fptr;
    fptr = fopen("what's_going_on.txt", "a");
    fprintf(fptr, message);

    fclose(fptr);
}

int read_information(void){

    FILE *fptr;
    fptr = fopen("what's_going_on.txt", "r");
    int file_data;
    int index = 0;
    int counter = 0;
    char **line = (char **)malloc(100 * sizeof(char*));
    line[index] = (char *)malloc(sizeof(char) * 100);
    while((file_data = getc(fptr)) != EOF ){
        if(file_data == '\n'){
            line[index][counter++] = '\n';
            line[index][counter] = '\0';
            counter = 0;
            line[++index] = (char *)malloc(sizeof(char) * 100);
        }
        else{
            line[index][counter++] = file_data;
        }
    }
    line[index][counter++] = '\n';
    line[index][counter] = '\0';

    counter = 0;
    while(counter <= index){
        if(str_cmp(line[counter], "Lose\n") == 0)
            return 1;
        if(str_cmp(line[counter], "Won\n") == 0)
            return 2;
        if(str_cmp(line[counter], "Exit\n") == 0)
            return 3;
        if(str_cmp(line[counter], "Dead\n") == 0)
            return 4;
        else
            counter++;
    }

    fclose(fptr);
    return 0;
}

void put_score(int score, char *name){

    FILE *fp;
    fp = fopen("leaderboard.txt", "a");

    int name_len = strlen(name);
    char * DataToAppend = (char*)malloc((10 + name_len)* sizeof(char));
    char * score_str = (char*)malloc((10)* sizeof(char));
    toString(score_str, score);

    fputs(name, fp);
    fputs("=", fp);
    fputs(score_str, fp);
    fputs("\n", fp);

    fclose(fp);
}

void Clean_info(void){

    FILE *fptr;
    fptr = fopen("what's_going_on.txt", "w");
    fprintf(fptr, "");
    fclose(fptr);

}
