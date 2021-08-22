#include "header.h"

struct Point opps[100];
extern struct Point box;
struct Data* head;
void (*movements[4])(struct Data *head, char map[][1000], struct Point place) = {opp_up, opp_down, opp_right, opp_left};

void find_opps(char map[][1000]){

    int col, row, index = 0;
    char opp = splitter(head, 1, "opp").type_result.character;
    for(col = 0;col < box.y;col++){
        for(row = 0;row < box.x;row++){
            if(map[col][row] == opp){
                struct Point new_point;
                new_point.x = row;
                new_point.y = col;
                opps[index++] = new_point;
            }
        }
    }

    struct Point new_point;
    new_point.x = -1;
    new_point.y = -1;
    opps[index++] = new_point;

}

void move_opp(struct Data *head, char map[][1000]){

    struct Point opp_place;
    char the_target = splitter(head, 2, "opp").type_result.character;
    struct Point target_place = find_char(map, the_target);

    if(target_place.x == -1 && target_place.y == -1)
        return ;

    int x_distance;
    int y_distance;
    int index = 0;

    find_opps(map);

    while(opps[index].x != -1 && opps[index].y != -1){

        opp_place = opps[index++];

        x_distance = target_place.x - opp_place.x;
        y_distance = target_place.y - opp_place.y;

        if(x_distance >= 0 && y_distance >= 0){
            if(x_distance >= y_distance)
                opp_right(head, map, opp_place);
            else
                opp_down(head, map, opp_place);
        }

        else if(x_distance >= 0 && y_distance <= 0){
            if(x_distance >= abs(y_distance))
                opp_right(head, map, opp_place);

            else
                opp_up(head, map, opp_place);
        }

        else if(x_distance <= 0 && y_distance >= 0){
            if(abs(x_distance) >= y_distance)
                opp_left(head, map, opp_place);
            else
                opp_down(head, map, opp_place);
        }
        else if(x_distance <= 0 && y_distance <= 0){
            if(abs(x_distance) >= abs(y_distance))
                opp_left(head, map, opp_place);
            else
                opp_up(head, map, opp_place);
        }

    }

}

void opp_up(struct Data *head, char map[][1000], struct Point place){


    char check = map[place.y - 1][place.x];
    char opp_char =  splitter(head, 1, "opp").type_result.character;
    char target_char = splitter(head, 2, "opp").type_result.character;
    if(check == target_char){
        check_who("opp");
        return ;
    }

    else if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y - 1][place.x] = opp_char;
    }

    else{
        movements[rand() % 4](head, map, place);
    }

    return ;
}


void opp_down(struct Data *head, char map[][1000], struct Point place){

    char check = map[place.y + 1][place.x];
    char opp_char =  splitter(head, 1, "opp").type_result.character;
    char target_char = splitter(head, 2, "opp").type_result.character;
    if(check == target_char){
        check_who("opp");
        return ;
    }

    else if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y + 1][place.x] = opp_char;
    }

    else{
        movements[rand() % 4](head, map, place);
    }
}

void opp_right(struct Data *head, char map[][1000], struct Point place){

    char check = map[place.y][place.x + 1];
    char opp_char =  splitter(head, 1, "opp").type_result.character;
    char target_char = splitter(head, 2, "opp").type_result.character;
    if(check == target_char){
        check_who("opp");
        return ;
    }

    else if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y][place.x + 1] = opp_char;
    }

    else{
        movements[rand() % 4](head, map, place);
    }

}

void opp_left(struct Data *head, char map[][1000], struct Point place){

    char check = map[place.y][place.x - 1];
    char opp_char =  splitter(head, 1, "opp").type_result.character;
    char target_char = splitter(head, 2, "opp").type_result.character;
    if(check == target_char){
        check_who("opp");
        return ;
    }

    else if(check == ' '){
        map[place.y][place.x] = ' ';
        map[place.y][place.x - 1] = opp_char;
    }

    else{
        movements[rand() % 4](head, map, place);
    }

}
