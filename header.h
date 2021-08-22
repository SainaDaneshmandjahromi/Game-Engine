#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>

struct Data{
    char *usage;
    char *characters;
    struct Data *next;
};

struct Point{
    int x;
    int y;
};

struct DBPoint{

    struct Point point;
    struct DBPoint *next;

};

struct Navigation{
    char up;
    char down;
    char left;
    char right;
};

struct Arrows{
    int up;
    int down;
    int left;
    int right;
};

struct Person{

    char *name;
    int score;
    struct Person *next;

};

struct Result {

    union ResultType {
        int number;
        char character;
    }type_result;
    int flag;
};

int read_map(char *filename, char map[][1000]);
void print_map(char map[][1000], int height);
struct Data* insertData(struct Data *head, char *usage, char *characters);
int read_game(char *filename);
void get_move(void);
void last_move(char move[]);
void process_move(char the_last_move, char up, char down ,char left, char right, char up2, char down2 ,char left2, char right2);
char* search_usage(struct Data *head, char *usage);
char* search_character(struct Data *head, char character);
struct Point find_character(char map[][1000], char *usage);
void go_up(char map[][1000], struct Point place, char the_last_move);
void go_up2(char map[][1000], struct Point place, char the_last_move);
void go_down(char map[][1000], struct Point place, char the_last_move);
void go_down2(char map[][1000], struct Point place, char the_last_move);
void go_left(char map[][1000], struct Point place, char the_last_move);
void go_left2(char map[][1000], struct Point place, char the_last_move);
void go_right(char map[][1000], struct Point place, char the_last_move);
void go_right2(char map[][1000], struct Point place, char the_last_move);
void build_navigation(void);
struct Result splitter(struct Data *head, int index, char *usage);
void put_information_in_file(char *message);
void exit_game(char *message);
void move_block(char the_last_move);
void random_rpoint(struct Data *head, char map[][1000]);
void get_reward(int prize);
void get_reward2(int prize);
int exist(struct Data *head, char *usage);
void check_who(char *who);
char find_move(char move[]);
void toString(char *str, int num);
void find_struct(struct Data* head, char *usage, char *character);
void reduce_put(struct Data *head, char *usage);
void raindb(struct Data *head, char map[][1000]);
struct DBPoint* insertCoordinates(struct DBPoint *head, int x, int y);
int insert_function(struct Data *head, void (*func[])(struct Data *head, char map[][1000]));
int read_information(void);
void rpoint(struct Data *head, char map[][1000]);
void attack(char map[][1000], struct Data* head, int pressed);
void clean(char map[][1000]);
void call_print_map(struct Data *head, char map[][1000]);
void call_get_move(struct Data* head,char map[][1000]);
void move_opp(struct Data *head, char map[][1000]);
void run_console(void);
void call_last_move(struct Data* head,char map[][1000]);
char *str_cat (char *a, char *b);
void opp_up(struct Data *head, char map[][1000], struct Point place);
void opp_down(struct Data *head, char map[][1000], struct Point place);
void opp_right(struct Data *head, char map[][1000], struct Point place);
void opp_left(struct Data *head, char map[][1000], struct Point place);
int str_cmp(char *a, char *b);
void Clean_info(void);
int get_time(struct Data* head);
void reduce_time(void);
struct Point find_char(char map[][1000], char character);
int handle_object(struct Data *head);
void raining(struct Data *head, char map[][1000]);
void clear_db(struct DBPoint *head, char map[][1000]);
void menu(void);
void end_game(int what_happend);
void play_bg(void);
int get_char(void);
void options(void);
void get_game(void);
void guid_line(void);
void play_win(void);
void play_lost(void);
void play_dead(void);
void play_exit(void);
void pause_game(struct Data *head,char map[][1000]);
void put_score(int score, char *name);
void print_leader_board(void);
char *get_name(void);
void build_ch2_navigation(void);
void bubbleSort(struct Person *head);
void swap(struct Person *a, struct Person *b);
