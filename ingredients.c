#include "header.h"

extern struct Data* head;
extern struct Point box;
struct Navigation navigate;
struct Navigation navigate2;
struct Arrows ArrowKeys;
extern struct DBPoint *db_head;
extern float the_time;

struct Data* insertData(struct Data *head, char *usage, char *characters){

    struct Data *new_data = (struct Data*)malloc(sizeof(struct Data));
    new_data->usage = usage;
    new_data->characters = characters;
    new_data->next = NULL;
    struct Data *temp = head;

    if(head == NULL)
        return new_data;

    while(head->next != NULL)
        head = head->next;
    head->next = new_data;

    return temp;
}

struct DBPoint* insertCoordinates(struct DBPoint *head, int x, int y){

    struct DBPoint *new_point = (struct DBPoint *)malloc(sizeof(struct DBPoint));
    new_point->point.x = x;
    new_point->point.y = y;
    new_point->next = head;

    return new_point;

}

char* search_usage(struct Data *head, char *usage){

    if(head == NULL)
        return " ";
    while(head != NULL){
        if(strcmp(head->usage, usage) == 0)
            return head->characters;
        head = head->next;
    }
    return " ";
}

char* search_character(struct Data *head, char character){

    if(head == NULL)
        return " ";

    while(head != NULL){
        if(head->characters[0] == character)
            return head->usage;
        head = head->next;
    }

    return " ";
}


struct Point find_character(char map[][1000], char *usage){

    char *the_character = (char *)malloc(2 * sizeof(char));
    char character;
    struct Point place;
    place.x = -1;
    place.y = -1;
    int flag = 0;
    the_character = search_usage(head, usage);
    if(the_character != NULL){
        character = the_character[0];
        flag = 1;
    }
    int i, j;
    for(i = 0;flag == 1 && i < box.y;i++)
        for(j = 0;j < box.x;j++)
            if(map[i][j] == character){
                place.x = j;    //place based on width
                place.y = i;    //place based on height
            }

    return place;
}

struct Point find_char(char map[][1000], char character){

    struct Point place;
    int i, j;

    place.x = -1;
    place.y = -1;

    for(i = 0;i <= box.y;i++)
        for(j = 0;j <= box.x;j++)
            if(map[i][j] == character){
                place.x = j;    //place based on width
                place.y = i;    //place based on height
            }

    return place;

}

int exist(struct Data *head, char *usage){
    if(search_usage(head, usage) == " ")
        return 0;
    return 1;

}

void build_navigation(void){

    navigate.up = splitter(head, 1, "up").type_result.character;
    navigate.down = splitter(head, 1, "down").type_result.character;
    navigate.left = splitter(head, 1, "left").type_result.character;
    navigate.right = splitter(head, 1, "right").type_result.character;

}

void build_ch2_navigation(void){

    navigate2.up = splitter(head, 1, "up1").type_result.character;
    navigate2.down = splitter(head, 1, "down1").type_result.character;
    navigate2.left = splitter(head, 1, "left1").type_result.character;
    navigate2.right = splitter(head, 1, "right1").type_result.character;

}

void build_arrowkeys(void){

    ArrowKeys.up = 72;
    ArrowKeys.down = 80;
    ArrowKeys.left = 75;
    ArrowKeys.right = 77;

}

char find_move(char move[]){
    int i;
    char moving_character = ' ';
    for(i = 0; i < strlen(move); i++)
        if(move[i] == navigate.down || move[i] == navigate.left || move[i] == navigate.right || move[i] == navigate.up)
            moving_character = move[i];

    return moving_character;

}

void put_death(struct Data *head, char map[][1000], char previous_move){

    if(exist(head, "put") != 1)
        return ;

    struct Point place = find_character(map, "character");
    int i = place.x;
    int j = place.y;
    char the_character = splitter(head, 2, "put").type_result.character;

    if(splitter(head, 3, "put").type_result.number == 0)
        return ;

    if(previous_move == navigate.up){
        if(map[j + 1][i] == ' ')
            map[j + 1][i] = the_character;
        else{
            go_up(map, place, previous_move);
            place = find_character(map, "character");
            map[place.y + 1][place.x] = the_character;
        }
    }
    else if(previous_move == navigate.down){
        if(map[j - 1][i] == ' ')
            map[j - 1][i] = the_character;
        else{
            go_down(map, place, previous_move);
            place = find_character(map, "character");
            map[place.y - 1][place.x] = the_character;
        }
    }
    else if(previous_move == navigate.left){
        if(map[j][i + 1] == ' ')
            map[j][i + 1] = the_character;
        else{
            go_left(map, place, previous_move);
            place = find_character(map, "character");
            map[place.y][place.x - 1] = the_character;
        }
    }
    else if(previous_move == navigate.right){
        if(map[j][i - 1] == ' ')
            map[j][i - 1] = the_character;
        else{
            go_right(map, place, previous_move);
            place = find_character(map, "character");
            map[place.y][place.x + 1] = the_character;
        }
    }
    reduce_put(head, "put");
}

void raindb(struct Data *head, char map[][1000]){

    if(exist(head, "raindb") != 1)
        return ;

    struct Point place;
    place.y = 2;
    do{
        place.x = rand() % box.x;
    }while(map[place.y][place.x] != ' ');

    map[place.y][place.x] = search_usage(head, "deathblock")[0];
    db_head = insertCoordinates(db_head, place.x, place.y);
}

int insert_function(struct Data *head, void (*func[])(struct Data *head, char map[][1000])){

    int index = 0;
    func[index++] = call_print_map;
    while(head != NULL){
        if(strcmp(head->usage, "rpoint") == 0)
            func[index++] = rpoint;

        if(strcmp(head->usage, "opp") == 0)
            func[index++] = move_opp;

        if(strcmp(head->usage, "raindb") == 0)
            func[index++] = raining;

        head = head->next;
    }
    func[index++] = call_get_move;
    return index;
}

void attack(char map[][1000], struct Data* head, int pressed){

    if(exist(head, "attack") != 1)
        return ;

    int range = splitter(head, 1, "attack").type_result.number;
    struct Point place = find_character(map ,"character");
    int counter = 0;
    char wall = splitter(head, 1, "wall").type_result.character;

    if(pressed == ArrowKeys.up){
        for(counter = 1; counter <= range ; counter++){
            if(map[place.y - counter][place.x] != wall)
                map[place.y - counter][place.x] = '`';
        }
    }
    else if(pressed == ArrowKeys.down){
        for(counter = 1; counter <= range ; counter++){
            if(map[place.y + counter][place.x] != wall)
                map[place.y + counter][place.x] = '`';
        }
    }
    else if(pressed == ArrowKeys.left){
        for(counter = 1; counter <= range ; counter++){
            if(map[place.y][place.x - counter] != wall)
                map[place.y][place.x - counter] = '`';
        }
    }
    else if(pressed == ArrowKeys.right){
        for(counter = 1; counter <= range ; counter++){
            if(map[place.y][place.x + counter] != wall)
                map[place.y][place.x + counter] = '`';
        }
    }
    system("cls");
    print_map(map, box.y);
    Sleep(100);
    clean(map);

}

char *str_cat (char *a, char *b){

    char *result = (char*)malloc(sizeof(char) * (strlen(a) + strlen(b)));
    int i, j;
    for(i = 0; i < strlen(a); i++)
        result[i] = a[i];

    for(j = 0; j < strlen(b); j++, i++)
        result[i] = b[j];

    return result;
}

char *str_cpy(char *b, char *a){

    int index;

    for(index = 0; a[index] != '\0'; index++)
        b[index] = a[index];

    b[index] = '\0';

    return b;
}

struct Person* insertPerson(struct Person *head,char *name , int score){

    struct Person *new_person = (struct Person *)malloc(sizeof(struct Person));
    new_person->name = name;
    new_person->score = score;
    new_person->next = head;
    return new_person;

}

void clean(char map[][1000]){

    int width;
    int height;
    for(width = 0;width < box.x;width++)
        for(height = 0;height < box.y;height++)
            if(map[height][width] == '`')
                map[height][width] = ' ';
}

int str_cmp(char *a, char *b){

    int i = 0;
    if(strlen(a) != strlen(b))
        return -1;
    while(a[i] != '\0' && b[i] != '\0')
        if(a[i] != b[i++])
            return -1;

    return 0;
}

int get_time(struct Data* head){

    if(exist(head, "time")){
        the_time = splitter(head, 1, "time").type_result.number;
        return 1;
    }
    return 0;

}

void reduce_time(void){

    if(the_time != 0)
        the_time -= 0.2;

}

void play_bg(void){

    system("MissionImpossibleRingtone.mp3 &");

}

void play_win(void){

    system("hallelujah_ringtone.mp3 &");

}

void play_lost(void){

    system("TheGodfather.mp3 &");

}

void play_dead(void){

    system("start titanic.mp3");

}

void play_exit(void){

    system("thuglife.mp3 &");

}

char *get_name(void){

    int c;
    char *name = (char *)malloc(sizeof(char) * 100);
    printf("\n\tPlease Enter your name : ");
    scanf("%s", name);
    return name;
}
