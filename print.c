#include "header.h"

extern char map[][1000];
extern struct Point box;
extern float the_time;
extern int score;
extern int score2;
extern struct Data* head;

void print_map(char map[][1000], int height){

    int i = 0;
    for(i = 0;i < height;i++)
        printf("%s", map[i]);
    if(the_time != -1){
        printf("\nRemaining Time : %.1f\n", the_time);
        reduce_time();
    }
    printf("\nPlayer Score : %d\n", score);
    if(exist(head, "character2"))
        printf("Player2 Score : %d\n", score2);

}

void call_print_map(struct Data *head, char map[][1000]){

    print_map(map, box.y);

}

void options(void){

    int answer;

    printf("\n\tDo you need Music during your game?\n\t");
    printf("\n\tEnter y for yes or n for No\n\t");
    printf("\n\ty/n ");
    do{
        answer = getchar();
    }while(answer == '\n');

    if(answer == 'y' || answer == 'Y')
        play_bg();
    system("cls");

    printf("\n\tDo you want to add a new Game?");
    printf("\n\tEnter y for yes or n for No\n\t");
    printf("\n\ty/n ");
    do{
        answer = getchar();
    }while(answer == '\n');


    if(answer == 'y' || answer == 'Y')
        get_game();

    else{
        printf("\n\tWelcome to the MAZE.\n");
        printf("\tPress any Key to Continue...");
        read_game("game-(maze).txt");
        read_map("map-(maze).txt", map);
        getch();
    }

    system("cls");

}

void get_game(void){

    char *map_filename = (char *)malloc(30*sizeof(char));
    char *game_filename = (char *)malloc(30*sizeof(char));
    int ans_map;
    int ans_game;

    do{
        system("cls");
        system("COLOR F2");
        printf("\tEnter game's FileName: \n\t");
        scanf("%s", game_filename);
        ans_game = read_game(game_filename);
    }while(ans_game != 1);

    do{
        system("cls");
        system("COLOR F2");
        printf("\tEnter map's FileName: \n\t");
        scanf("%s", map_filename);
        ans_map = read_map(map_filename, map);
    }while(ans_map != 1);

}

void menu(void){

    system("COLOR F2");


    int answer;
    char *name = (char *)malloc(50 *sizeof(char));

    printf("\tWelcome To The Console.\n\n");
    printf("\tMade By Ee 2 to bacho (Saina && Aida).\n\tOK Dude...LEt's get Started!\n\n");
    printf("\tPress any Key to Continue...");
    getch();
    system("cls");

    options();
    system("cls");
    guid_line();
    system("cls");

    printf("\n\tHere we Go.Get Ready for the Game :))))))))\n\t");
    getch();
    system("cls");
    run_console();
}

void guid_line(void){

    struct Data *temp = head;

    while(temp != NULL){
        printf("\n\t%s => %s", temp->usage, temp->characters);
        temp = temp->next;
    }

    printf("\n\tPress and Key to continue ...");
    getch();
}

void end_game(int what_happend){

    if(what_happend == 1){
        system("COLOR C3");
        play_lost();
        if(exist(head, "character2")){
            if(score > score2)
                printf("Player1 has won the game");
            else if(score == score2)
                printf("You guys did the same");
            else
                printf("Player2 has won the game");
        }
        else
            printf("\n\tYou Lost the Battle.\n");
    }

    else if(what_happend == 2){
        system("COLOR A0");
        play_win();
        if(exist(head, "character2"))
            printf("Player1 has won the game");
        else
            printf("\n\tYou Won the Battle.\n");
    }

    else if(what_happend == 3){
        system("COLOR F0");
        play_exit();
        printf("\n\tYou Exited the Battle.\n");
    }

    else if(what_happend == 4){
        system("COLOR 04");
        play_dead();
        if(exist(head, "character2")){
            if(score > score2)
                printf("Player1 has won the game");
            else if(score == score2)
                printf("You guys did the same");
            else
                printf("Player2 has won the game");
        }
        else {
        printf("\n\tYou're Dead.\n");
        }
    }

    else if(what_happend == 5){
        system("COLOR C3");
        play_lost();
        printf("\n\tYou Lost the Battle.\n\t(Ran Out of Time)\n\t");
    }

    else if(what_happend == 6){
        system("COLOR A0");
        play_win();
        if(exist(head, "character2"))
            printf("Player2 has won the game");
    }

    Clean_info();

}


void print_leader_board(void){

    FILE *fp;

    int file_data;

    char *name = get_name();
    put_score(score, name);

    struct Person *head = NULL;
    head = add_persons(head);
    bubbleSort(head);

    system("cls");
    printf("\t Leader Board  :\n");
    while(head != NULL){
        printf("\t \t %s => %d \n", head->name, head->score);
        head = head->next;
    }


}
