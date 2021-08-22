#include"header.h"

extern char map[][1000];
extern struct Data *head;
extern struct Navigation navigate;
extern struct Navigation navigate2;
extern struct Point box;
extern int score;
extern int score2;
extern int Running_Game;
extern struct DBPoint *db_head;

char handle_usage(char *usage){

    if(str_cmp(usage, "solidblock") == 0 || strcmp(usage, "wall") == 0)
        return 's';
    else if(str_cmp(usage, "deathblock") == 0)
        return 'd';
    else if(str_cmp(usage, "moveblock") == 0)
        return 'm';
    else if(str_cmp(usage, "rpoint") == 0)
        return 'r';
    else if(exist(head, "object") && str_cmp(usage, "target") == 0)
        return 't';
}

struct Result splitter(struct Data *head, int index, char *usage){

    int counter;
    int comma_counter = 0;
    int flag = 0;
    char *value = search_usage(head, usage);
    struct Result result;
    result.type_result.number = 0;
    result.type_result.character = '\0';
    for(counter = 0; value[counter] != '\0'; counter++){
        if(comma_counter == index - 1)
            break;
        if(value[counter] == ',')
            comma_counter++;
    }
    while(value[counter] != '\0' && value[counter] != ','){
        if(value[counter] >= '0' && value[counter] <= '9'){
            result.flag = 1;    //it is an integer
            result.type_result.number = result.type_result.number*10 + value[counter] - '0';
        }
        else{
            result.flag = 0;    //it is a character
            result.type_result.character = value[counter];
            break;
        }
        counter++;
    }
    return result;
}


void exit_game(char *message){
    put_information_in_file(message);
}

void move_block(char the_last_move){

    struct Point place = find_character(map, "character");
    int check_target = handle_object(head);
    char target = splitter(head, 1, "target").type_result.character;

    if(the_last_move == navigate.up){
        if(check_target == 1 && map[place.y - 2][place.x] == target){
            check_who("moveblock");
            return;
        }
        if(map[place.y - 2][place.x] == ' '){
            map[place.y - 2][place.x] = splitter(head, 1, "moveblock").type_result.character;
            map[place.y - 1][place.x] = ' ';
            go_up(map, place, the_last_move);
        }
    }

    else if(the_last_move == navigate.down){
        if(check_target == 1 && map[place.y + 2][place.x] == target){
            check_who("moveblock");
            return;
        }
        if(map[place.y + 2][place.x] == ' '){
            map[place.y + 2][place.x] = splitter(head, 1, "moveblock").type_result.character;
            map[place.y + 1][place.x] = ' ';
            go_down(map, place, the_last_move);
        }
    }

    else if(the_last_move == navigate.left){
        if(check_target == 1 && map[place.y][place.x - 2] == target){
            check_who("moveblock");
            return;
        }
        if(map[place.y][place.x - 2] == ' '){
            map[place.y][place.x - 2] = splitter(head, 1, "moveblock").type_result.character;
            map[place.y][place.x - 1] = ' ';
            go_left(map, place, the_last_move);
        }
    }

    else if(the_last_move == navigate.right){
        if(check_target == 1 && map[place.y][place.x + 2] == target){
            check_who("moveblock");
            return;
        }
        if(map[place.y][place.x + 2] == ' '){
            map[place.y][place.x + 2] = splitter(head, 1, "moveblock").type_result.character;
            map[place.y][place.x + 1] = ' ';
            go_right(map, place, the_last_move);
        }
    }
}

void rpoint(struct Data *head, char map[][1000]){

    int counter = 0;
    int rpcounter = splitter(head, 3, "rpoint").type_result.number;
    int width, height;
    char rp = splitter(head, 1, "rpoint").type_result.character;
    for(width = 0; width < box.x; width++)
        for(height = 0; height < box.y; height++)
            if(map[height][width] == rp)
                counter++;

    while(counter < rpcounter){
        random_rpoint(head, map);
        counter++;
    }
}

void random_rpoint(struct Data *head, char map[][1000]){

    char rpoint_character = search_usage(head, "rpoint")[0];
    int x;
    int y;

    srand(time(NULL));
    do{
        x = rand() % box.x;
        y = rand() % box.y;
    }while(map[y][x] != ' ');
    map[y][x] = rpoint_character;
}

void get_reward(int prize){

    score += prize;

}

void get_reward2(int prize){

    score2 += prize;

}


void check_who(char *who){

    if(str_cmp(who, "opp") == 0)
        put_information_in_file("Lose\n");

    else if(str_cmp(who, "character") == 0)
        put_information_in_file("Won\n");

    else if(str_cmp(who, "character2") == 0)
        put_information_in_file("Won2\n");

    else if(str_cmp(who, "moveblock") == 0);
        put_information_in_file("Won\n");


    return;
}

void toString(char *str, int num){

    int i, rem, len = 0, n;

    if(num == 0){
        str[0] = '0';
        str[1] = '\0';
        return ;
    }
    n = num;
    while(n != 0){
        len++;
        n /= 10;
    }
    for(i = 0;i < len;i++){
        rem = num % 10;
        num = num / 10;
        str[len -(i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void find_struct(struct Data* head, char *usage, char *character){

    while(head != NULL){
        if(strcmp(head->usage, usage) == 0){
            free(head->characters);
            head->characters = character;
            return ;
        }
        head = head->next;
    }

}

void reduce_put(struct Data *head, char *usage){
    struct Result the_char = splitter(head, 3, "put");
    char *number_string = (char *)malloc(15 * sizeof(char));
    char *string = search_usage(head, "put");

    int flag = 0;
    int i, j;

    the_char.type_result.number -= 1;
    toString(number_string, the_char.type_result.number);
    for(i = 0; i < strlen(string); i++){
        if(flag == 2){
            string[i] = '\0';
            break;
        }
        else if(string[i] == ','){
            flag++;
        }
    }
    string = str_cat(string, number_string);
    find_struct(head, "put", string);

}

void raindb_counter(struct DBPoint *db_head, char map[][1000], struct Data *head){

    int counter = 0;
    int dbcounter = splitter(head, 1, "raindb").type_result.number;
    int width, height;
    char db = splitter(head, 1, "deathblock").type_result.character;
    for(width = 0; width < box.x; width++)
        for(height = 0; height < box.y; height++)
            if(map[height][width] == db)
                counter++;

    while(counter < dbcounter){
        raindb(head, map);
        counter++;
    }

}


void raining(struct Data *head, char map[][1000]){

    if(exist(head, "raindb") != 1)
        return ;

    raindb_counter(db_head, map, head);
    struct DBPoint *temp = db_head;

    while(temp != NULL){
        if(map[temp->point.y + 2][temp->point.x] == ' '){
            map[temp->point.y + 2][temp->point.x] = splitter(head, 1, "deathblock").type_result.character;
            map[temp->point.y][temp->point.x] = ' ';
            temp->point.y += 1;
        }
        else if(map[temp->point.y + 2][temp->point.x] == splitter(head, 1, "character").type_result.character){
            put_information_in_file("Dead\n");
            return ;
        }
        else if(map[temp->point.y + 2][temp->point.x] == splitter(head, 1, "wall").type_result.character){
           map[temp->point.y + 1][temp->point.x] = ' ';
           clear_db(db_head, map);
        }
        if(map[temp->point.y][temp->point.x] != splitter(head, 1, "character").type_result.character)
        map[temp->point.y][temp->point.x] = ' ';
        temp = temp->next;
    }
}


void clear_db(struct DBPoint *head, char map[][1000]){

    while(head != NULL){
        map[head->point.y + 1][head->point.x] = ' ';
        head = head->next;
    }
    db_head = NULL;

}

int handle_object(struct Data *head){

    if(exist(head, "object") && exist(head, "target"))
        if(splitter(head, 1, "object").type_result.character == splitter(head, 1, "moveblock").type_result.character)
            return 1;
    return 0;

}

void pause_game(struct Data *head,char map[][1000]){

    if(Running_Game == 1)
        Running_Game = 0;
    else if(Running_Game == 0)
        Running_Game = 1;

}

struct Person *add_persons(struct person* head){

    int name_index = 0;
    int score_index = 0;
    int flag = 0;
    char *name = (char *)malloc(sizeof(char) * 100);
    char *score = (char *)malloc(sizeof(char) * 20);
    int file_data;

    FILE *fp;
    fp = fopen("leaderboard.txt", "r");

    while((file_data = getc(fp)) != EOF){
        if(file_data == '='){
            flag = 1;
        }
        else if(file_data == '\n'){
            name[name_index] = '\0';
            name = (char *)malloc(sizeof(char) * 100);
            score[score_index] = '\0';
            head = insertPerson(head, name, atoi(score));
            flag = 0;
            name_index = 0;
            score_index = 0;
        }
        else if(flag == 0){
            name[name_index++] = file_data;
        }
        else if(flag == 1){
            score[score_index++] = file_data;
        }

    }

    fclose(fp);

    return head;

}

void bubbleSort(struct Person *head){
    int swapped = 1;
    struct Person *temp1;
    struct Person *temp2 = NULL;

    /* Checking for empty list or only one element */
    if (head == NULL || head->next == NULL)
        return;
    while(swapped != 0){
        swapped = 0;
        temp1 = head;
        while (temp1->next != temp2) {
            if (temp1->score < temp1->next->score) {
                swap(temp1, temp1->next);
                swapped = 1;
            }
            temp1 = temp1->next;
        }
        temp2 = temp1;
    }
}

void swap(struct Person *a, struct Person *b){

    struct Person *temp = (struct Person *)malloc(sizeof(struct Person));

    temp->name = a->name;
    temp->score = a->score;

    a->name = b->name;
    a->score = b->score;

    b->name = temp->name;
    b->score = temp->score;
}
