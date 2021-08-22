#include "header.h"

extern struct Data* head;
extern char map[][1000];
extern struct Navigation navigate;
extern struct Navigation navigate2;
extern struct Arrows ArrowKeys;
char move[10];

//Get Move from user
void get_move(void){

    int index = 0;
    int kb;
    clock_t this_time = clock();
    clock_t end_time = this_time + 200;
    move[index++] = find_move(move);
    while(clock() < end_time)
        if(kbhit()){
            kb = getch();
            if(kb == 0xE0)
                kb = getch();
            move[index++] = kb;
        }

    move[index] = '\0';
    last_move(move);

}

void call_get_move(struct Data* head,char map[][1000]){

    get_move();

}

//check the last move
void last_move(char move[]){

    int index;
    char the_last_move = ' ';
    char put = splitter(head, 1, "put").type_result.character;
    char exit = splitter(head, 1, "Exit").type_result.character;
    char pause = '\0';
    if(exist(head, "pause") == 1)
        pause = splitter(head, 1, "pause").type_result.character;

    for(index = 0; move[index] != '\0'; index++){
        if(move[index] == navigate.up || move[index] == navigate.down || move[index] == navigate.left || move[index] == navigate.right)
            the_last_move = move[index];
        else if(move[index] == navigate2.up || move[index] == navigate2.down || move[index] == navigate2.left || move[index] == navigate2.right)
            the_last_move = move[index];
        else if(move[index] == ArrowKeys.up || move[index] == ArrowKeys.down || move[index] == ArrowKeys.left || move[index] == ArrowKeys.right)
            attack(map, head, move[index]);
        else if(move[index] == put)
            put_death(head, map, move[0]);
        else if(move[index] == pause)
            pause_game(head, map);
        else if(move[index] == exit)
            exit_game("Exit\n");
    }
    if(the_last_move == ' ')
        return ;
    process_move(the_last_move, navigate.up, navigate.down, navigate.left, navigate.right,
                 navigate2.up, navigate2.down, navigate2.left, navigate2.right);
}

//check the navigation
void process_move(char the_last_move, char up, char down ,char left, char right, char up2, char down2 ,char left2, char right2){

    struct Point place = find_character(map, "character");
    if(the_last_move == up)
        go_up(map, place, the_last_move);
    else if(the_last_move == down)
        go_down(map, place, the_last_move);
    else if(the_last_move == left)
        go_left(map, place, the_last_move);
    else if(the_last_move == right)
        go_right(map, place, the_last_move);

    else if(exist(head, "character2")){
        struct Point place = find_character(map, "character2");
        if(the_last_move == up2)
            go_up2(map, place, the_last_move);
        else if(the_last_move == down2)
            go_down2(map, place, the_last_move);
        else if(the_last_move == left2)
            go_left2(map, place, the_last_move);
        else if(the_last_move == right2)
            go_right2(map, place, the_last_move);
    }

    return;
}

void go_up(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    struct Result prize;
    char character = ' ';
    char check = map[place.y - 1][place.x];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y - 1][place.x] = the_char;
        return ;
    }
    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage);
        get_reward(prize.type_result.number);
        map[place.y][place.x] = ' ';
        map[place.y - 1][place.x] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}

void go_up2(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character2").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    struct Result prize;
    char character = ' ';
    char check = map[place.y - 1][place.x];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y - 1][place.x] = the_char;
        return ;
    }
    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage);
        get_reward2(prize.type_result.number);
        map[place.y][place.x] = ' ';
        map[place.y - 1][place.x] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}

void go_down(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    int prize;
    char character;
    char check = map[place.y + 1][place.x];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y + 1][place.x] = the_char;
        return ;
    }
    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage).type_result.number;
        get_reward(prize);
        map[place.y][place.x] = ' ';
        map[place.y + 1][place.x] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}


void go_down2(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character2").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    int prize;
    char character;
    char check = map[place.y + 1][place.x];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y + 1][place.x] = the_char;
        return ;
    }
    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage).type_result.number;
        get_reward2(prize);
        map[place.y][place.x] = ' ';
        map[place.y + 1][place.x] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}


void go_left(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    struct Result prize;
    char character;
    char check = map[place.y][place.x - 1];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y][place.x - 1] = the_char;
        return ;
    }
    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage);
        get_reward(prize.type_result.number);
        map[place.y][place.x] = ' ';
        map[place.y][place.x - 1] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}


void go_left2(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character2").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    struct Result prize;
    char character;
    char check = map[place.y][place.x - 1];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y][place.x - 1] = the_char;
        return ;
    }
    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage);
        get_reward2(prize.type_result.number);
        map[place.y][place.x] = ' ';
        map[place.y][place.x - 1] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}

void go_right(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    struct Result prize;
    char character;
    char check = map[place.y][place.x + 1];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y][place.x + 1] = the_char;
        return ;
    }

    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage);
        get_reward(prize.type_result.number);
        map[place.y][place.x] = ' ';
        map[place.y][place.x + 1] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}



void go_right2(char map[][1000], struct Point place, char the_last_move){

    char the_char = splitter(head, 1, "character2").type_result.character;
    char *usage = (char *)malloc(15 * sizeof(char));
    char *who = (char *)malloc(15 * sizeof(char));
    struct Result prize;
    char character;
    char check = map[place.y][place.x + 1];
    if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y][place.x + 1] = the_char;
        return ;
    }

    usage = search_character(head, check);
    character = handle_usage(usage);

    switch(character){
    case 's':
        break;

    case 'd':
        exit_game("Dead\n");     //Fired
        break;

    case 'm':
        move_block(the_last_move);
        break;

    case 'r':
        prize = splitter(head, 2, usage);
        get_reward2(prize.type_result.number);
        map[place.y][place.x] = ' ';
        map[place.y][place.x + 1] = the_char;
        break;

    case 't':
        who = search_character(head, map[place.y][place.x]);
        check_who(who);
        break;

    default:
        break;
    }
}
