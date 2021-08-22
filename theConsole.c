#include "header.h"

extern struct Navigation navigate;
extern struct Navigation navigate2;
void (*func[10])(struct Data* head, char map[][1000]);
extern struct Data* head;
extern char map[][1000];
extern float the_time;
extern int Running_Game;

void run_console(void){

    int have_time = get_time(head);
    int what_happend = 0;
    int index = insert_function(head, func);
    int count = 0;
    int flag = 1;
    int c;
    char pause = '\0';
    if(exist(head, "pause"))
        pause = splitter(head, 1, "pause").type_result.character;

    if(exist(head, "character2"))
        build_ch2_navigation();

    system("COLOR 07");
    build_arrowkeys();
    build_navigation();

    for(;flag;){

        if(Running_Game){
            system("cls");
            printf("GAME IS PAUSED...");
            c = getch();
            if(c == pause)
                pause_game(head, map);
            continue;
        }

        for(count = 0;count < index;count++){
            func[count](head, map);
        }
        what_happend = read_information();
        if (what_happend == 1 || what_happend == 2 || what_happend == 3 || what_happend == 4 || what_happend == 6){
            flag = 0;
            Sleep(200);
        }
        if(have_time == 1){
            if(the_time < 0){
                flag = 0;
                what_happend = 5;
                Sleep(200);
            }
        }
        system("cls");
    }

    end_game(what_happend);
    print_leader_board();
    Clean_info();
}
