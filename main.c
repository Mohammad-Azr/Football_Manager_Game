/*---------------- MOHAMMAD MAHDI AZARBAYEJANI --------------------*/
/*--------------------------40003583-------------------------------*/

/*-----------------Includes-------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>

/*------------------DEFINES-------------------*/
#define shortMAX 100
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/*------------------Structs-------------------*/
struct player
{
    char name[50];
    int id;
    int value;
    int attack_power;
    int defence_power;
    int curr_att_pow;
    int curr_def_pow;
    int last_week_play; // 0 - 1 -> 0=Last week played! | 1=last week not played!
    char team[shortMAX];
    int status;
}player_sorted_list[800];
struct total_player
{
    struct player p_list[800];
    int last_p_loc;
    int last_id;
} all_p = {.last_p_loc = 0, .last_id = 1000};

struct team
{
    char name[shortMAX];
    int id;
    char first_email[shortMAX];
    char email[shortMAX];
    char password[shortMAX];
    int budget;
    int active_player_count;
    int player_count;
    int league_status; // 0 - 1 -> is team in league or not
    int squad_status;  // 0 - 1 -> ready for start_league/play or not
    int squad[5];
    int champ_status; // 0 - 1 -> 0=lost | 1=won
    int champ_count;
    // games
    int team_att_pow;
    int team_def_pow;
    int squad_att_pow;
    int squad_def_pow;
    int played;
    int won;
    int drawn;
    int lost;
    int last_play_gf;
    int last_play_ga;
    int gf;
    int gd;
    int ga;
    int point;
    struct player players[100];
};
struct totall_team
{
    int teams_count;
    int teams_last_used_id;
    struct team teams[100];
} team_database = {.teams_count = 0, .teams_last_used_id = 99};


struct admin
{
    char password[shortMAX];
} admin_database = {.password = "Admin"};

struct league
{
    int week_num;
    int transfer_window_status; // 0 = close | 1 = open
    int league_run_status;      // 0 = No   | 1 = Yes | 2 = mid seaoson
    int end_status;             // 0 = league is running | 1 = league ended
    int plan[24];
    int goals[24];
    int league_team[4];
    int t1_loc;
    int t2_loc;
    int t3_loc;
    int t4_loc;

} league_db = {.league_run_status = 0, .transfer_window_status = 1, .week_num = 0, .plan = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4}};

struct Info
{
    int id;
    char name[100];
    int point;
    int gf;
    int gd;
    int ga;
    int played;
    int won;
    int lost;
    int drawn;
} info_list[4];


/*------------FUNCTIONS DECLARATION-----------*/
void ClearScreen();
void team_location(char *name);
void quit();

//--DATA
void LOADS();
void SAVES();
void team_load_data();
void team_save_data();
void admin_load_data();
void admin_save_data();
void all_players_load();
void all_players_save();
void league_load_data();
void league_save_data();

//--ADMIN
void admin_main_menu();
void team_config();
void add_team();
void add_player();
void show_all_teams();
void show_all_players();
void admin_change_password();
//#league#
void league_menu();
void start_week_menu();
void start_league();
void open_close_transfer();
void end_season();
void show_standing();
//-games
void choose_plan();
void play(int id_1, int att1, int def1, int id_2, int att2, int def2, int id_3, int att3, int def3, int id_4, int att4, int def4);
void update_power(int id_1, int id_2, int id_3, int id_4);
void reset_power(int id_1, int id_2, int id_3, int id_4);

//--COACH
void coach_main_menu();
void buy_playyer();
void sell_playyer();
void select_squad();
void submit_squad();
void league_standing();
void fixtures();
void upcoming_opponent();
//-players_sort
void sort_players_initials();
void sort_players_func();
void sort_plyers_show();
//-standing_sort
void standing_bubble_sort();
void standing_initials();
void standing_sorted_show();

//--SIGN IN
void login_page();
void sign_in_page();
void admin_sign_in();
void coach_sign_in();
void forgot_pass_page();
void change_password();

/*--------------Global Variables--------------*/
char team_num;
int players_num;
char global_password[shortMAX];
char acc_name[shortMAX];
char acc_password[shortMAX];
int team_loc;
char sign_in_inp_name[shortMAX];
int plans[6][24] = {{0,1,2,3 ,0,3,1,2 ,1,3,2,0  ,3,0,2,1 ,1,0,3,2 ,2,0,3,1}  ,
                    {0,1,2,3 ,1,3,2,0 ,0,3,1,2  ,3,0,2,1 ,2,0,3,1 ,1,0,3,2}  ,
                    {1,3,2,0 ,0,3,1,2 ,0,1,2,3  ,2,0,3,1 ,1,0,3,2 ,3,0,2,1}  , 
                    {0,3,1,2 ,0,1,2,3 ,1,3,2,0  ,1,0,3,2 ,3,0,2,1 ,2,0,3,1}  ,
                    {0,3,1,2 ,1,3,2,0 ,0,1,2,3  ,1,0,3,2 ,2,0,3,1 ,3,0,2,1}  ,
                    {1,3,2,0 ,0,1,2,3 ,0,3,1,2  ,2,0,3,1 ,3,0,2,1 ,1,0,3,2}  };

/*------------------------------------------------RUN--------------------------------------------------*/
int main()
{
    ClearScreen();
    LOADS();
    login_page();
    SAVES();
}

/*-----------------FUNCTIONS----------------- */
void ClearScreen()

{
    system("cls");
}
void team_location(char *name)
{
    for (int i = 0; i < team_database.teams_count; i++)
    {
        if (strcmp(name, team_database.teams[i].name) == 0)
        {
            team_loc = i;
        }
    }
}
void quit()
{
    ClearScreen();
    team_save_data();
    admin_save_data();
    all_players_save();
    league_save_data();
    return login_page();
}

//-----ADMIN-----
void admin_main_menu()
{
    ClearScreen();
    printf(BLU"--------- ADMIN PAGE MAIN MENU ----------\n\n"RESET);
    printf(YEL"1>"RESET" ADD TEAM\n"YEL"2>"RESET" ADD PLAYER\n"YEL"3>"RESET" SHOW TEAMS\n"YEL"4>"RESET" SHOW PLAYERS\n"YEL"5>"RESET" LEAGUE MENU\n"YEL"6>"RESET" EXIT\n\n");
    int code;
    printf("---ENTER CODE: ");
    scanf("%d", &code);
    switch (code)
    {
    case 1:
        return add_team();
        break;
    case 2:
        return add_player();
        break;
    case 3:
        return show_all_teams();
        break;
    case 4:
        return show_all_players();
        break;
    case 5:
        return league_menu();
        break;
    case 6:
        return quit();
        break;
    default:
        return admin_main_menu();
        break;
    }
}
void team_config()
{
    int n = team_database.teams_count;
    team_database.teams[n].id = team_database.teams_last_used_id + 1;
    team_database.teams_last_used_id += 1;
    team_database.teams[n].budget = 100;
    team_database.teams[n].player_count = 0;
    team_database.teams[n].active_player_count = 0;
    team_database.teams[n].league_status = 0;
    team_database.teams[n].ga = 0;
    team_database.teams[n].gf = 0;
    team_database.teams[n].gd = 0;
    team_database.teams[n].won = 0;
    team_database.teams[n].lost = 0;
    team_database.teams[n].drawn = 0;
    team_database.teams[n].played = 0;
    team_database.teams[n].champ_count = 0;
    team_database.teams[n].champ_status = 0;
    team_database.teams[n].team_att_pow = 0;
    team_database.teams[n].team_def_pow = 0;
}
void add_team()
{
    ClearScreen();
    printf(BLU"---------- ADD TEAM ----------\n\n"RESET);
    printf("ENTER NAME OF TEAM TO CREATE: ");
    char name[shortMAX];
    scanf("%s", &name);
    // checking team name already taken or not
    for (int i = 0; i < team_database.teams_count; i++)
    {
        if (strcmp(name, team_database.teams[i].name) == 0)
        {
            printf("THIS NAME ALREADY TAKEN!\nCHOOSE ANOTHER ONE!\n");
            sleep(1.3);
            return add_team();
        }
    }
    // get and set email and updates data of teams
    int n = team_database.teams_count;
    strcpy(team_database.teams[n].name, name);
    char email[shortMAX];
    printf("ENTER EMAIL OF COACH TO CRATE: ");
    scanf("%s", &email);
    strcpy(team_database.teams[n].first_email, email);
    strcpy(team_database.teams[n].email, email);
    strcpy(team_database.teams[n].password, email);
    team_config();

    // message of Done:
    ClearScreen();
    printf(BLU"--------------- ADD TEAM --------------\n\n"RESET);
    printf(GRN"NEW TEAM ADDED!:\n"RESET);
    printf("NAME: %s\nEMAIL: %s\nID: %d\n", team_database.teams[team_database.teams_count].name, team_database.teams[team_database.teams_count].email, team_database.teams[team_database.teams_count].id);
    printf("---------------------------------------\n");
    team_database.teams_count += 1;
    int code;
    printf("ENTER ANY KEY TO BACK TO MAIN MENU: ");
    scanf("%d", &code);
    return admin_main_menu();
}
void add_player()
{
    ClearScreen();
    printf(BLU"---------- ADD PLAYER ---------\n\n"RESET);
    char inp_name[shortMAX];
    int inp_value;
    int inp_attack_pow;
    int inp_defence_pow;
    printf("ENTER FILDES: \n");
    printf("---NAME OF PLAYER: ");
    scanf("%s", &inp_name);
    printf("---ATTACK POWER(0-100): ");
    scanf("%d", &inp_attack_pow);
    printf("---DEFENCE POWER(0-100): ");
    scanf("%d", &inp_defence_pow);
    printf("---VALUE(10-20): ");
    scanf("%d", &inp_value);
    strcpy(all_p.p_list[all_p.last_p_loc].name, inp_name);
    all_p.p_list[all_p.last_p_loc].attack_power = inp_attack_pow;
    all_p.p_list[all_p.last_p_loc].defence_power = inp_defence_pow;
    all_p.p_list[all_p.last_p_loc].curr_att_pow = inp_attack_pow;
    all_p.p_list[all_p.last_p_loc].curr_def_pow = inp_defence_pow;
    all_p.p_list[all_p.last_p_loc].value = inp_value;
    strcpy(all_p.p_list[all_p.last_p_loc].team, "FREE_AGENT");
    all_p.p_list[all_p.last_p_loc].id = all_p.last_id + 1;
    all_p.last_p_loc += 1;
    all_p.last_id += 1;
    ClearScreen();
    printf(GRN"----------------\nPLAYER CREATED !\n----------------\n"RESET);
    sleep(1);
    return admin_main_menu();
}
void show_all_teams()
{
    ClearScreen();
    printf(BLU"-------------------------- ALL TEAMS ----------------------------\n\n"RESET);
    printf("%-9s%-20s%-21s%-16s\n", "ID", "TEAM", "EMAIL" ,"CHAMPIONS");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < team_database.teams_count; i++)
    {
        if(i%2==0)
            printf(YEL"%-8d%-23s%-27s%-16d\n"RESET, team_database.teams[i].id, team_database.teams[i].name, team_database.teams[i].email ,team_database.teams[i].champ_count);
        else
            printf(MAG"%-8d%-23s%-27s%-16d\n"RESET, team_database.teams[i].id, team_database.teams[i].name, team_database.teams[i].email ,team_database.teams[i].champ_count);
        // printf("-----------------------------------------------------------\n");
    }
    printf("--------------------------------------------------------------------\n");
    printf("ENTER ID OF EACH TEAM TO SHOW PLAYERS:\n");
    printf("---ENTER CODE (code 0 = exit): ");
    int code;
    scanf("%d", &code);
    if (code==0)
        return admin_main_menu();
    else
    {
        for (int i = 0; i < team_database.teams_count; i++)
        {
            int id = team_database.teams[i].id;
            if(id==code)
            {
                ClearScreen();
                printf(GRN"-----------------------\nTEAM : %s \n-----------------------\n"RESET,team_database.teams[i].name);
                printf(YEL"                                   _____________\n");
                printf("__________________________________| ALL PLAYERS |____________________________________\n\n");
                printf("%-7s%-9s%-15s%-15s%-19s%-18s\n", " ", "ID", "NAME", "ATTACK POWER", "DEFENCE POWER", "VALUE");
                printf("-------------------------------------------------------------------------------------\n"RESET);
                int k = 1;
                for (int j = 0; j < team_database.teams[i].player_count; j++)
                {
                    if(strcmp(team_database.teams[i].players[j].name ,"FREE_AGENT")!=0)
                    {
                        printf("%-6d%-9d%-21s%-15d%-15d%-15d\n", k ,team_database.teams[i].players[j].id ,team_database.teams[i].players[j].name ,team_database.teams[i].players[j].attack_power ,team_database.teams[i].players[j].defence_power ,team_database.teams[i].players[j].value);
                        k++;
                    }
                }
                printf(YEL"-------------------------------------------------------------------------------------\n"RESET);

            }
        }
        printf(YEL"1>"RESET" ENTER ANY NUMBERS FOR BACK\n---ENTER CODE: ");
        int inp_code;
        scanf("%d",&code);
        if("True")
            return show_all_teams();

    }
}
void show_all_players()
{
    ClearScreen();
    printf(BLU"----------------------------------------- ALL PLAYERS -----------------------------------------\n\n"RESET);
    printf("%-7s%-9s%-22s%-14s%-15s%-19s%-18s\n", " ", "ID", "NAME", "TEAM", "ATTACK POWER", "DEFENCE POWER", "VALUE");
    printf("-----------------------------------------------------------------------------------------------\n");
    // int n = all_p.last_p_loc;
    for (int i = 0; i < all_p.last_p_loc; i++)
    {
        if(i%2==0)
            printf(YEL"%-6d%-9d%-21s%-21s%-15d%-15d%-15d\n"RESET, i + 1, all_p.p_list[i].id, all_p.p_list[i].name, all_p.p_list[i].team, all_p.p_list[i].curr_att_pow, all_p.p_list[i].curr_def_pow, all_p.p_list[i].value);
        else
            printf(MAG"%-6d%-9d%-21s%-21s%-15d%-15d%-15d\n"RESET, i + 1, all_p.p_list[i].id, all_p.p_list[i].name, all_p.p_list[i].team, all_p.p_list[i].curr_att_pow, all_p.p_list[i].curr_def_pow, all_p.p_list[i].value);

        // printf("--------------------------------------------------------------------------------------------------\n");
    }
    int code;
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("ENTER ANY NUMBER TO RETURN TO MAIN MENU: ");
    scanf("%d", &code);
    return admin_main_menu();
}

//#LEAGUE#
void league_menu()
{
    ClearScreen();
    printf(BLU"---------------LEAGUE MENU---------------\n\n"RESET);
    printf(YEL"1>"RESET" START LEAGUE\n"YEL"2>"RESET" OPEN/CLOSE TRANSFER WINDOW\n"YEL"3>"RESET" START WEEK i-th GAMES\n"YEL"4>"RESET" End Season and Announce The Champion\n"YEL"5>"RESET" BACK\n\n");
    printf("---ENTER CODE: ");
    int inp_code;
    scanf("%d", &inp_code);
    if (inp_code == 1)
        return start_league();
    else if (inp_code == 2)
        return open_close_transfer();
    else if (inp_code == 3)
        return start_week_menu();
    else if (inp_code == 4)
        return end_season();
    else if (inp_code == 5)
        return admin_main_menu();
    else
    {
        printf(RED"INVALID CODE! try again...\n"RESET);
        sleep(2);
        return league_menu();
    }
}
void start_league()
{
    ClearScreen();
    printf(BLU"-------------------------START LEAGUE-------------------------\n\n"RESET);
    if (league_db.league_run_status != 0)
    {
        printf(RED"------------------------------------------------------------\n");
        printf("ALREADY A LEAGUE STARTED!!!\nYOU CAN NOT START A NEW LEAGUE UNTIL THIS LEAGUE FINISHED!!!\n");
        printf("------------------------------------------------------------\n\n"RESET);
        printf(YEL"1>"RESET" BACK\n");
        int code;
        printf("---ENTER CODE: ");
        scanf("%d", &code);
        if (code == 1)
            return league_menu();
        else
        {
            printf(RED"INVALID CODE!\n"RESET);
            sleep(1.4);
            return start_league();
        }
    }
    else
    {
        int ready_teams_count;
        for (int i = 0; i < team_database.teams_count; i++)
        {
            if (team_database.teams[i].squad_status == 1)
                ready_teams_count += 1;
        }
        printf("------------- READY TEAMS --------------\n\n");
        printf("%-9s%-21s\n", "ID", "TEAM");
        printf("-------------------------------------------------\n");
        for (int i = 0; i < team_database.teams_count; i++)
        {
            if (team_database.teams[i].squad_status == 1)
                printf("%-8d%-20s\n", team_database.teams[i].id, team_database.teams[i].name);
        }
        printf("-------------------------------------------------\n\n");
        if (ready_teams_count < 4)
        {
            printf(RED"---------------------------------------------------\nAT LEAST 4 READY TEAM REQUIRED TO START THE LEAGUE!\nNOW %d TEAMS READY AND SUBMIT THEIR SQUAD!\n---------------------------------------------------\n\n"RESET, ready_teams_count);
            printf(YEL"1>"RESET" BACK\n---ENTER CODE: ");
            int code;
            scanf("%d",&code);
            if (code==1)
                return league_menu();
            else
                return start_league();
        }
        printf("---ENTER ID OF 4 TEAMS TO ADD THEM TO LEAGUE: \n");
        int inp_id;
        int j = 0;
        for (int k = 1; k < 5; k++)
        {
            printf("---TEAM %d ID : ", k);
            scanf("%d", &inp_id);
            for (int i = 0; i < team_database.teams_count; i++)
            {
                if (team_database.teams[i].id == inp_id)
                {
                    
                    team_database.teams[i].squad_status = 0;
                    team_database.teams[i].league_status=1;
                    league_db.league_team[j] = inp_id;
                    
                    for (int n = 0; n < team_database.teams[i].player_count; n++)
                    {
                        if(strcmp(team_database.teams[i].players[n].name ,"FREE_AGENT")!=0)
                            team_database.teams[i].players[n].status = 0;
                    }
                    if(j==0)
                    {
                        league_db.t1_loc = i;
                        j++;
                        break;
                    }
                    else if(j==1)
                    {
                        league_db.t2_loc = i;
                        j++;
                        break;
                    }
                    else if(j==2)
                    {
                        league_db.t3_loc = i;
                        j++;
                        break;
                    }
                    else if(j==3)
                    {
                        league_db.t4_loc = i;
                        j++;
                        break;
                    }
                    
                    
                }
                else
                    continue;
            }
        }
        league_db.league_run_status = 1;
        league_db.end_status = 0;
        league_db.transfer_window_status = 0;
        league_db.week_num = 1;
        //---------------------
        choose_plan();
        //ClearScreen();
        printf(GRN"------------------------------\nWELL DONE! LEAGUE STARTED !\n------------------------------\n"RESET);
        sleep(5);
        return league_menu();
    }
}
void open_close_transfer()
{
    ClearScreen();
    printf(BLU"----------OPEN & CLOSE TRANSFER---------\n\n"RESET);
    printf(YEL"1>"RESET" OPEN TRANSFER WINDOW\n"YEL"2>"RESET" CLOSE TRANSFER WINDOW\n"YEL"3>"RESET" BACK\n\n");
    printf("---ENTER CODE: ");
    int code;
    scanf("%d", &code);
    if (code == 1) //-------OPEN-------
    {
        if (league_db.league_run_status == 1)
        {
            ClearScreen();
            printf(RED"--------------------------------------------------------------------\n");
            printf("NOW YOU CAN NOT OPEN TRANSFER WINDOW!\nTRANSFER WINDOW CAN BE OPEN IN MID-SEASON OR BEFORE STARTING LEAGUE!\n");
            printf("--------------------------------------------------------------------\n\n"RESET);
            sleep(7);
            return open_close_transfer();
        }
        else if (league_db.league_run_status == 2)
        {
            ClearScreen();
            league_db.transfer_window_status = 1;
            printf(GRN"----------------------------------\nWELL DONE! TRANSFER WINDOW OPENED SUCCESSFULLY!\n----------------------------------\n\n"RESET);
            sleep(3);
            return open_close_transfer();
        }
        else if (league_db.league_run_status == 0)
        {
            ClearScreen();
            printf(RED"--------------------------------\nNOW WE DONT HAVE ANY LEAGUE!\nTRANSFER WINDOW IS ALREADY OPEN!\n--------------------------------\n\n"RESET);
            sleep(5);
            return open_close_transfer();
        }
    }
    else if (code == 2) //-------CLOSE------
    {
        if (league_db.league_run_status == 1)
        {
            ClearScreen();
            printf(RED"--------------------------------\nTRANSFER WINDOW IS ALREADY CLOSE!\n--------------------------------\n\n"RESET);
            sleep(5);
            return league_menu();
        }
        else if (league_db.league_run_status == 2)
        {
            ClearScreen();
            league_db.transfer_window_status = 0;
            printf(GRN"----------------------------------\nWELL DONE! TRANSFER WINDOW CLOSED SUCCESSFULLY!\n----------------------------------\n\n"RESET);
            sleep(3);
            return league_menu();
        }
        else if (league_db.league_run_status == 0)
        {
            ClearScreen();
            printf(RED"------------------------------------------------------\n");
            printf("       YOU CAN NOT CLOSE TRANSFER WINDOW!\nSTART A LEAGUE ,AND TRANSFER WINOW CLOSES AUTOMATICLY\n\n");
            printf("------------------------------------------------------\n"RESET);
            sleep(5);
            return league_menu();
        }
    }
    else
    {
        return league_menu();
    }
}
void start_week_menu()
{
    ClearScreen();
    if(league_db.end_status==1)
    {
        printf(RED"-----------------------------------------\n");
        printf("6 WEEK PASSED! NOW YPU SHOULD END SEASON!\n");
        printf("-----------------------------------------\n"RESET);
        sleep(3);
        return league_menu();
    }
    if(league_db.league_run_status==0)
    {
        printf(RED"-------------------------------------\n");
        printf("YOU DONT HAVE AN ACCESS TO THIS PART!\nAT FIRST YOU SHOLD START A LEAGUE\n");
        printf("-------------------------------------\n"RESET);
        sleep(2);
        return league_menu();
    }
    if(league_db.week_num!=7)
        printf(BLU"----------START WEEK i-th----------\n\n"RESET);
    printf(GRN"---------\nweek : %d\n---------\n\n"RESET ,league_db.week_num);
    printf("PLAN OF THIS WEEK: \n\n");
    int num = (league_db.week_num - 1) * 4;
    int id;
    char name[shortMAX];
    int id1 = league_db.league_team[league_db.plan[num]], id2 = league_db.league_team[league_db.plan[num + 1]];
    int id3 = league_db.league_team[league_db.plan[num + 2]], id4 = league_db.league_team[league_db.plan[num + 3]];
    char name1[shortMAX];
    char name2[shortMAX];
    char name3[shortMAX];
    char name4[shortMAX];
    int t1_att, t1_def, t2_att, t2_def, t3_att, t3_def, t4_att, t4_def;
    char ready_status[shortMAX]; // 'Ready'=ok | 'name1' = team1 is not ready | 'name2' = team2 is not ready | ....
    strcpy(ready_status, "Ready");
    for (int i = 0; i < team_database.teams_count; i++)
    {
        id = team_database.teams[i].id;
        strcpy(name, team_database.teams[i].name);
        if (id == id1)
        {
            strcpy(name1, name);
            t1_att = team_database.teams[i].squad_att_pow;
            t1_def = team_database.teams[i].squad_def_pow;
            //printf("att1:%d - def1:%d",team_database.teams[i].squad_att_pow ,team_database.teams[i].squad_def_pow);
            if (team_database.teams[i].squad_status == 0)
            {
                strcpy(ready_status, name1);
                break;
            }
        }
        else if (id == id2)
        {
            strcpy(name2, name);
            t2_att = team_database.teams[i].squad_att_pow;
            t2_def = team_database.teams[i].squad_def_pow;
            //printf("att2:%d - def2:%d",team_database.teams[i].squad_att_pow ,team_database.teams[i].squad_def_pow);
            if (team_database.teams[i].squad_status == 0)
            {
                strcpy(ready_status, name2);
                break;
            }
        }
        else if (id == id3)
        {
            strcpy(name3, name);
            t3_att = team_database.teams[i].squad_att_pow;
            t3_def = team_database.teams[i].squad_def_pow;
            //printf("att3:%d - def3:%d",team_database.teams[i].squad_att_pow ,team_database.teams[i].squad_def_pow);
            if (team_database.teams[i].squad_status == 0)
            {
                strcpy(ready_status, name3);
                break;
            }

        }

        else if (id == id4)
        {
            strcpy(name4, name);
            t4_att = team_database.teams[i].squad_att_pow;
            t4_def = team_database.teams[i].squad_def_pow;
            //printf("att4:%d - def4:%d",team_database.teams[i].squad_att_pow ,team_database.teams[i].squad_def_pow);
            if (team_database.teams[i].squad_status == 0)
            {
                strcpy(ready_status, name4);
                break;
            }

        }
    }

    if (strcmp(ready_status, "Ready") != 0)
    {
        ClearScreen();
        printf(RED"OH! SORRY! SOME TEAMS DIDNT SELECT THEIR SQUAD!\nYOU CAN NOT START WEEK UNTIL THEY SELECT THEIR SQUAD!\n\n"RESET);
        printf("1> BACK\n---ENTER CODE: ");
        int code;
        scanf("%d", &code);
        if (code == 1)
        {
            return league_menu();
        }
        else
            return start_week_menu();
    }
    printf(YEL"%s - %s\n", name1, name2);
    printf("%s - %s\n\n"RESET, name3, name4);
    printf(YEL"1>"RESET" START WEEK %d\n"YEL"2>"RESET" BACK\n---ENTER CODE: " ,league_db.week_num);
    int code;
    scanf("%d", &code);
    if (code == 1) // START WEEK!
    {
        if (league_db.week_num == 4)
        {
            league_db.league_run_status = 1;
        }

        ClearScreen();
        play(id1, t1_att, t1_def,  id2, t2_att, t2_def,  id3, t3_att, t3_def, id4, t4_att, t4_def);

        if (league_db.week_num == 3)
        {
            reset_power(id1, id2, id3, id4);
            league_db.league_run_status = 2;
        }

        else
            update_power(id1, id2, id3, id4);

        ClearScreen();
        printf(GRN"OK! WEEK STARTED!\nYOU CAN SEE RESULTS IN 3 SECOND LATER!!!\n"RESET);
        sleep(1);
        printf(GRN"OK! WEEK STARTED!\nYOU CAN SEE RESULTS IN 2 SECOND LATER!!!\n"RESET);
        sleep(1);
        printf(GRN"OK! WEEK STARTED!\nYOU CAN SEE RESULTS IN 1 SECOND LATER!!!\n"RESET);
        sleep(1);
        ClearScreen();
        team_loc = 101;
        show_standing();
        league_db.week_num += 1;
        if(league_db.week_num==7)
            league_db.end_status=1;
        int id;
        for (int i = 0; i < team_database.teams_count; i++)
        {
            id = team_database.teams[i].id;
            if(id==id1 || id==id2 || id==id3 || id==id4)
            {
                team_database.teams[i].squad_status = 0;
            }
        }
        standing_initials();
        standing_bubble_sort();
        standing_sorted_show();
        printf("---ENTER ANY NUMBER TO BACK TO MENU: ");
        int code;
        scanf("%d" ,&code);
        return admin_main_menu();
    }

    else // BACK TO MENU
        return league_menu();
}
void end_season()
{
    ClearScreen();
    printf("-----------------------END SEASON-----------------------\n\n");

    if(league_db.end_status!=1)
    {
        printf(RED"YOU DONT HAVE ACCESS TO THIS PART UNTIL LEAGUE END!"RESET);
        sleep(1.5);
        return league_menu();
    }
    printf(BLU"---------------------SEAOSON ENDED!-------------------\n"RESET);
    sleep(1.5);
    ClearScreen();
    team_loc = 101;
    standing_sorted_show();
    printf(GRN"=======================\nWINNER: %s \n=======================\n"RESET ,info_list[0].name);
    for (int i = 0; i < team_database.teams_count; i++)
    {
        if(info_list[0].id == team_database.teams[i].id)
            team_database.teams[i].champ_count++;
        team_database.teams[i].ga =0 ; team_database.teams[i].gd = 0;team_database.teams[i].gf = 0;
        team_database.teams[i].lost = 0 ;team_database.teams[i].won = 0; team_database.teams[i].drawn = 0;
        team_database.teams[i].played = 0;
        team_database.teams[i].point = 0; team_database.teams[i].squad_status = 0;
        team_database.teams[i].league_status = 0;
        team_database.teams[i].squad_att_pow = 0; team_database.teams[i].squad_def_pow = 0;
        team_database.teams[i].champ_status = 0;
        for (int j = 0; j < team_database.teams[i].player_count; j++)
        {
            if(strcmp(team_database.teams[i].players[j].name ,"FREE_AGENT")!=0)
            {
                team_database.teams[i].players[j].status=0;
                team_database.teams[i].players[j].curr_att_pow = team_database.teams[i].players[j].attack_power;
                team_database.teams[i].players[j].curr_def_pow = team_database.teams[i].players[j].defence_power;
            }

        }


    }
    league_db.transfer_window_status = 1;
    league_db.league_run_status= 0;
    league_db.end_status = 0;
    for (int i = 0; i < 4; i++)
    {
        league_db.league_team[i] = 0;
    }
    printf(YEL"1>"RESET" BACK\n---ENTER CODE: ");
    int code;
    scanf("%d",&code);
    if ("True")
        return admin_main_menu();
}
void show_standing()
{
    printf(BLU"------------------- LEAGUE STANDING ------------------\n\n\n"RESET);
    printf("----------\nweek : %d\n----------\n",league_db.week_num);
    printf("-------------------------------------------------- STANDING --------------------------------------------------\n\n");
    printf("%-5s%-20s%-12s%-9s%-11s%-11s%-10s%-10s%-9s%-8s\n"," ", "TEAM", "PLAYED","WON","DRAWN","LOST","GF","GA","GD","POINT");
    printf("--------------------------------------------------------------------------------------------------------------\n");
    int j=1;
    for (int i = 0; i < team_database.teams_count; i++)
    {
        if(team_database.teams[i].league_status==1)
        {
            char name[shortMAX];
            strcpy(name ,team_database.teams[i].name);
            int played = team_database.teams[i].played;
            int won = team_database.teams[i].won , drawn = team_database.teams[i].drawn , lost = team_database.teams[i].lost;
            int gf = team_database.teams[i].gf , ga = team_database.teams[i].ga , gd = team_database.teams[i].gd;
            int point = team_database.teams[i].point;
            printf("%-5d%-23s%-10d%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",j ,name ,played ,won ,drawn ,lost ,gf ,ga ,gd ,point);
            j++;
        }
    }
    printf("--------------------------------------------------------------------------------------------------------------\n\n1> BACK\n---ENTER CODE: ");
    return ;
}
//-GAME
void choose_plan()
{
    int plan_num;
    int lower = 0, upper = 5, count = 1;
    srand(time(0));
    for (int i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        plan_num = num;
    }

    //int p[24] = {0, 1, 2, 3, 0, 3, 1, 2, 1, 3, 2, 0, 3, 0, 2, 1, 1, 0, 3, 2, 2, 0, 3, 1};
    for (int i = 0; i < 24; i++)
    {
        league_db.plan[i] = plans[plan_num][i];
    }
}
void play(int id_1, int att1, int def1, int id_2, int att2, int def2, int id_3, int att3, int def3, int id_4, int att4, int def4)
{
    int team1_goals = (att1 - def2) / 100;
    int team2_goals = (att2 - def1) / 100;
    int team3_goals = (att3 - def4) / 100;
    int team4_goals = (att4 - def3) / 100;

    if (team1_goals < 0)
        team1_goals = 0;
    if (team2_goals < 0)
        team2_goals = 0;
    if (team3_goals < 0)
        team3_goals = 0;
    if (team4_goals < 0)
        team4_goals = 0;
    ClearScreen();
    //printf("team1:%d team2:%d team3:%d team4:%d",team1_goals ,team2_goals ,team3_goals ,team4_goals);
    //sleep(6);
    int num = (league_db.week_num - 1) * 4;
    league_db.goals[num] = team1_goals;
    league_db.goals[num + 1] = team2_goals;
    league_db.goals[num + 2] = team3_goals;
    league_db.goals[num + 3] = team4_goals;

    for (int i = 0; i < team_database.teams_count; i++)
    {
        int id = team_database.teams[i].id;
        if (id == id_1)
        {
            team_database.teams[i].last_play_gf = team1_goals;
            team_database.teams[i].last_play_ga = team2_goals;
            team_database.teams[i].played+=1;
            team_database.teams[i].gf+=team_database.teams[i].last_play_gf;
            team_database.teams[i].ga+=team_database.teams[i].last_play_ga;
            team_database.teams[i].gd = (team_database.teams[i].gf - team_database.teams[i].ga);
            if (team1_goals > team2_goals) // win
            {
                team_database.teams[i].point += 3;team_database.teams[i].won+=1;
                team_database.teams[i].budget += 5;
            }
            else if (team1_goals < team2_goals) // lost
            {
                team_database.teams[i].budget += 1;team_database.teams[i].lost+=1;
            }
            else // Drawon
            {
                team_database.teams[i].point += 1;team_database.teams[i].drawn+=1;
                team_database.teams[i].budget += 3;
            }
        }
        else if (id == id_2)
        {
            team_database.teams[i].last_play_gf = team2_goals;
            team_database.teams[i].last_play_ga = team1_goals;
            team_database.teams[i].played+=1;
            team_database.teams[i].gf+=team_database.teams[i].last_play_gf;
            team_database.teams[i].ga+=team_database.teams[i].last_play_ga;
            team_database.teams[i].gd = (team_database.teams[i].gf - team_database.teams[i].ga);
            if (team2_goals > team1_goals) // win
            {
                team_database.teams[i].point += 3;team_database.teams[i].won+=1;
                team_database.teams[i].budget += 5;
            }
            else if (team2_goals < team1_goals) // lost
            {
                team_database.teams[i].budget += 1;team_database.teams[i].lost+=1;
            }
            else // Drawon
            {
                team_database.teams[i].point += 1;team_database.teams[i].drawn+=1;
                team_database.teams[i].budget += 3;
            }
        }
        else if (id == id_3)
        {
            team_database.teams[i].last_play_gf = team3_goals;
            team_database.teams[i].last_play_ga = team4_goals;
            team_database.teams[i].played+=1;
            team_database.teams[i].gf+=team_database.teams[i].last_play_gf;
            team_database.teams[i].ga+=team_database.teams[i].last_play_ga;            
            team_database.teams[i].gd = (team_database.teams[i].gf - team_database.teams[i].ga);
            if (team3_goals > team4_goals) // win
            {
                team_database.teams[i].point += 3;team_database.teams[i].won+=1;
                team_database.teams[i].budget += 5;
            }
            else if (team3_goals < team4_goals) // lost
            {
                team_database.teams[i].budget += 1;team_database.teams[i].lost+=1;
            }
            else // Drawon
            {
                team_database.teams[i].point += 1;team_database.teams[i].drawn+=1;
                team_database.teams[i].budget += 3;
            }
        }
        else if (id == id_4)
        {
            team_database.teams[i].last_play_gf = team4_goals;
            team_database.teams[i].last_play_ga = team3_goals;
            team_database.teams[i].played+=1;
            team_database.teams[i].gf+=team_database.teams[i].last_play_gf;
            team_database.teams[i].ga+=team_database.teams[i].last_play_ga;
            team_database.teams[i].gd = (team_database.teams[i].gf - team_database.teams[i].ga);
            if (team4_goals > team3_goals) // win
            {
                team_database.teams[i].point += 3;team_database.teams[i].won+=1;
                team_database.teams[i].budget += 5;
            }
            else if (team4_goals < team3_goals) // lost
            {
                team_database.teams[i].budget += 1;team_database.teams[i].lost+=1;
            }
            else // Drawon
            {
                team_database.teams[i].point += 1;team_database.teams[i].drawn+=1;
                team_database.teams[i].budget += 3;
            }
        }
    }
    return ;
}
void update_power(int id_1, int id_2, int id_3, int id_4)
{
    for (int i = 0; i < team_database.teams_count; i++)
    {
        int id = team_database.teams[i].id;
        if (id == id_1 || id == id_2 || id == id_3 || id == id_4)
        {
            for (int j = 0; j < team_database.teams[i].player_count; j++)
            {
                if ((strcmp(team_database.teams[i].players[j].name, "FREE_AGENT") != 0) && (team_database.teams[i].players[j].status == 1))
                {
                    team_database.teams[i].players[j].curr_att_pow -= 5;
                    team_database.teams[i].players[j].curr_def_pow -= 5;
                    team_database.teams[i].players[j].status = 0;
                }
                else if ((strcmp(team_database.teams[i].players[j].name, "FREE_AGENT") != 0) && (team_database.teams[i].players[j].status == 0))
                {
                    if ((team_database.teams[i].players[j].curr_att_pow < team_database.teams[i].players[j].attack_power) && (team_database.teams[i].players[j].curr_def_pow < team_database.teams[i].players[j].defence_power))
                        {team_database.teams[i].players[j].curr_att_pow += 5;
                        team_database.teams[i].players[j].curr_def_pow += 5;}
                    team_database.teams[i].players[j].status = 0;
                }
            }
        }
    }
}
void reset_power(int id_1, int id_2, int id_3, int id_4)
{
    for (int i = 0; i < team_database.teams_count; i++)
    {
        int id = team_database.teams[i].id;
        if (id == id_1 || id == id_2 || id == id_3 || id == id_4)
        {
            for (int j = 0; j < team_database.teams[i].player_count; j++)
            {
                if (strcmp(team_database.teams[i].players[j].name, "FREE_AGENT") != 0)
                    team_database.teams[i].players[j].curr_att_pow = team_database.teams[i].players[j].attack_power;
                team_database.teams[i].players[j].curr_def_pow = team_database.teams[i].players[j].defence_power;
                team_database.teams[i].players[j].status = 0;
            }
        }
    }
}

//-----COACH-----
void coach_main_menu()
{
    ClearScreen();
    if (team_database.teams[team_loc].league_status == 1)
    {
        printf(MAG"---------- TEAM PAGE MAIN MENU ----------\n\n"RESET);
        printf("HELLO SIR! WELCOME!\n\n");
        printf("------------------------------------\n ");
        printf("Team: %s    "GRN"Budget: %d \n"RESET, team_database.teams[team_loc].name, team_database.teams[team_loc].budget);
        printf("------------------------------------\n");
        printf("---------------------------------------------------\n");
        printf("TOTAL ATTACK POWER: %d | TOTAL DEFENCE POWER: %d\n", team_database.teams[team_loc].team_att_pow, team_database.teams[team_loc].team_def_pow);
        //printf("SQUAD ATTACK POWER: %d | SQUAD DEFENCE POWER: %d\n", team_database.teams[team_loc].squad_att_pow, team_database.teams[team_loc].squad_def_pow);
        printf("---------------------------------------------------\n");
        printf(YEL"1>"RESET" BUY A PLAYYER\n"YEL"2>"RESET" SELL A PLAYER\n"YEL"3>"RESET" SELECT SQUAD\n"YEL"4>"RESET" LEAGUE STANDING\n"YEL"5>"RESET" FIXTURES\n"YEL"6>"RESET" UPCOMING OPPONENT\n"YEL"7>"RESET" CHANGE PASSWORD\n"YEL"8>"RESET" EXIT\n\n");
        int code;
        printf("---ENTER CODE: ");
        scanf("%d", &code);
        switch (code)
        {
        case 1:
            return buy_playyer();
            break;
        case 2:
            return sell_playyer();
            break;
        case 3:
            return select_squad();
            break;
        case 4:
            return league_standing();
            break;
        case 5:
            return fixtures();
            break;
        case 6:
            return upcoming_opponent();
            break;
        case 7:
            return change_password();
            break;
        case 8:
            return quit();
            break;
        default:
            break;
        }
    }
    else
    {
        printf(MAG"---------- TEAM PAGE MAIN MENU ----------\n\n"RESET);
        printf("HELLO SIR! WELCOME!\n\n");
        printf("------------------------------------\n");
        printf("Team: %s    Budget: %d\n", team_database.teams[team_loc].name, team_database.teams[team_loc].budget);
        printf("------------------------------------\n");
        printf(YEL"1>"RESET" BUY A PLAYYER\n"YEL"2>"RESET" SELL A PLAYER\n"YEL"3>"RESET" SUBMIT SQUAD\n"YEL"4>"RESET" LEAGUE STANDING\n"YEL"5>"RESET" FIXTURES\n"YEL"6>"RESET" UPCOMING OPPONENT\n"YEL"7>"RESET" CHANGE PASSWORD\n"YEL"8>"RESET" EXIT\n\n");
        int code;
        printf("---ENTER CODE: ");
        scanf("%d", &code);
        switch (code)
        {
        case 1:
            return buy_playyer();
            break;
        case 2:
            return sell_playyer();
            break;
        case 3:
            return submit_squad();
            break;
        case 4:
            return league_standing();
            break;
        case 5:
            return fixtures();
            break;
        case 6:
            return upcoming_opponent();
            break;
        case 7:
            return change_password();
            break;
        case 8:
            return quit();
            break;
        default:
            break;
        }
    }
}
void buy_playyer()
{
    ClearScreen();
    printf(MAG"----------------------BUY A PLAYER----------------------\n"RESET);
    if (league_db.transfer_window_status == 0)
    {
        printf(RED"---------------------------------------\nSORRY! TRANSFER WINDOW CLOSED!\n        YOU CAN NOT BUY PLAYER!\n---------------------------------------\n\n"RESET);
        sleep(3);
        return coach_main_menu();
    }
    else if (team_database.teams[team_loc].active_player_count == 8)
    {
        printf(RED"-----------------------------------\nYOU CAN NOT BUY A PLAYER!\nYOU HAVE MAXIMUM NUMBER OF PLAYER(8)\n-----------------------------------\n"RESET);
        sleep(1);
        return coach_main_menu();
    }
    int free_cnt=0;
    for (int i = 0; i < all_p.last_p_loc; i++)
    {
        
        if(strcmp(all_p.p_list[i].team ,"FREE_AGENT")==0)
            free_cnt++;
    }
    if(free_cnt==0)
    {
        printf(RED"------------------------\nNO FREE AGENT TO BUY!\n------------------------\n"RESET);
        sleep(3);
        return coach_main_menu();
    }
    sort_players_initials();
    sort_players_func();
    sort_plyers_show();
    printf("---------------\nYOUR BUDGET: %d$\n--------------\n", team_database.teams[team_loc].budget);
    printf("ENTER ID OF PLAYER YOU WANT TO BUY (code 0 = back to menu): ");
    int code;
    scanf("%d", &code);
    if (code == 0)
        return coach_main_menu();
    for (int i = 0; i < all_p.last_p_loc; i++)
    {
        if (all_p.p_list[i].id == code)
        {
            if ((all_p.p_list[i].value <= team_database.teams[team_loc].budget) && (team_database.teams[team_loc].active_player_count < 8))
            {
                for (int j = 0; j < team_database.teams[team_loc].player_count; j++)
                {
                    if (team_database.teams[team_loc].players[j].id == all_p.p_list[i].id)
                    {
                        team_database.teams[team_loc].players[j] = all_p.p_list[i];
                        strcpy(team_database.teams[team_loc].players[j].team, team_database.teams[team_loc].name);
                        strcpy(all_p.p_list[i].team, team_database.teams[team_loc].name);
                        team_database.teams[team_loc].active_player_count += 1;
                        team_database.teams[team_loc].budget -= all_p.p_list[i].value;
                        ClearScreen();
                        printf("---------- BUY A PLAYER ----------\n\n");
                        printf("-----------------------\n  CONGRATULATION !!!\n  YOU BUY -%s- SUCCESSFULLY!\n-----------------------\n\n", all_p.p_list[i].name);
                        printf("1> BACK TO MAIN MENU\n2> BUY A PLAYER\n\nENTER CODE: ");
                        int input_code;
                        scanf("%d", &input_code);
                        switch (input_code)
                        {
                        case 1:
                            return coach_main_menu();
                            break;
                        case 2:
                            return buy_playyer();
                            break;
                        default:
                            break;
                        }
                    }
                }

                team_database.teams[team_loc].players[team_database.teams[team_loc].player_count] = all_p.p_list[i];
                strcpy(team_database.teams[team_loc].players[team_database.teams[team_loc].player_count].team, team_database.teams[team_loc].name);
                strcpy(all_p.p_list[i].team, team_database.teams[team_loc].name);
                team_database.teams[team_loc].active_player_count += 1;
                team_database.teams[team_loc].player_count += 1;
                team_database.teams[team_loc].budget -= all_p.p_list[i].value;
                team_database.teams[team_loc].team_att_pow += all_p.p_list[i].attack_power;
                team_database.teams[team_loc].team_def_pow += all_p.p_list[i].defence_power;
                ClearScreen();
                printf(MAG"---------- BUY A PLAYER ----------\n\n"RESET);
                printf(GRN"-----------------------\n  CONGRATULATION\n  YOU BUY -%s- SUCCESSFULLY!\n-----------------------\n\n"RESET, all_p.p_list[i].name);
                printf(YEL"1>"RESET" BUY A PLAYER\n"YEL"2>"RESET" BACK TO MAIN MENU\n\nENTER CODE: ");
                int input_code;
                scanf("%d", &input_code);
                switch (input_code)
                {
                case 1:
                    return buy_playyer();
                    break;
                case 2:
                    return coach_main_menu();
                    break;
                default:
                    break;
                }
            }
            printf(RED"SORRY! YOU DONT HAVE ENOUGH MONEY TO BUY THIS PLAYER!\n"RESET);
            printf(YEL"1>"RESET" BACK TO MAIN MENU\n"YEL"2>"RESET" BUY ANOTHER PLAYER\n\n");
            int inp_code;
            scanf("%d", &inp_code);
            if (inp_code == 1)
                return coach_main_menu();
            else if (inp_code == 2)
                return buy_playyer();
            else
                return coach_main_menu();
        }
    }
    ClearScreen();
    printf(RED"--------------\n        INVALID ID !!!\n--------------\n"RESET);
    sleep(2);
    return buy_playyer();
}
void sell_playyer()
{
    ClearScreen();
    if (league_db.transfer_window_status == 0)
    {
        printf(RED"---------------------------------------\nSORRY! TRANSFER WINDOW CLOSED!\n   YOU CAN NOT SELL PLAYER!\n---------------------------------------\n\n"RESET);
        sleep(3);
        return coach_main_menu();
    }
    else if (team_database.teams[team_loc].active_player_count == 0)
    {
        printf(RED"-------------------\nYOU HAVE 0 PLAYER !!!\n-------------------\n"RESET);
        sleep(2.5);
        return coach_main_menu();
    }
    else if (team_database.teams[team_loc].squad_status == 1 && league_db.league_run_status==0)
    {
        printf(RED"--------------------------------\nYOU SUBMITED YOUR SQUAD!\nNOW YOU CAN NOT SELL ANY PLAYER!\n--------------------------------\n"RESET);
        sleep(5);
        return coach_main_menu();
    }
    printf(MAG"---------- SELL A PLAYER ----------\n\n"RESET);
    printf("---------------------------------- ALL PLAYERS ----------------------------------\n");
    printf("%-9s%-18s%-21s%-23s%-21s\n", "ID", "NAME", "ATTACK POWER", "DEFENCE POWER", "VALUE");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < team_database.teams[team_loc].player_count; i++)
    {
        if (strcmp(team_database.teams[team_loc].players[i].name, "FREE_AGENT") != 0)
            printf("%-9d%-21s%-21d%-21d%-21d\n", team_database.teams[team_loc].players[i].id, team_database.teams[team_loc].players[i].name, team_database.teams[team_loc].players[i].attack_power, team_database.teams[team_loc].players[i].defence_power, team_database.teams[team_loc].players[i].value);
    }
    printf("------------------------\n   YOUR BUDGET: %d$\n------------------------\n", team_database.teams[team_loc].budget);
    printf("ENTER ID OF PLAYER YOU WANT TO SELL (code 0 = back to menu): ");
    int code;
    scanf("%d", &code);
    if (code == 0)
        return coach_main_menu();
    for (int i = 0; i < team_database.teams[team_loc].player_count; i++)
    {
        if ((code == team_database.teams[team_loc].players[i].id) && (strcmp(team_database.teams[team_loc].players[i].team, "FREE_AGENT") != 0))
        {
            for (int j = 0; j < all_p.last_p_loc; j++)
            {
                if (team_database.teams[team_loc].players[i].id == all_p.p_list[j].id)
                {
                    strcpy(all_p.p_list[j].team, "FREE_AGENT");
                    strcpy(team_database.teams[team_loc].players[i].name, "FREE_AGENT");
                    ClearScreen();
                    printf(MAG"---------- SELL A PLAYER ----------\n\n"RESET);
                    printf(GRN"-----------------------\n  WELL DONE !!!\n  YOU SELL -%s- SUCCESSFULLY!\n-----------------------\n"RESET, all_p.p_list[j].name);
                    team_database.teams[team_loc].team_att_pow -= all_p.p_list[j].attack_power;
                    team_database.teams[team_loc].team_def_pow -= all_p.p_list[j].defence_power;
                    break;
                }
            }
            team_database.teams[team_loc].active_player_count -= 1;
            team_database.teams[team_loc].budget += team_database.teams[team_loc].players[i].value;

            printf("------------------\n  YOUR BUDGET: %d$\n-----------------\n", team_database.teams[team_loc].budget);
            printf(YEL"1>"RESET" BACK TO MAIN MENU\n"YEL"2>"RESET" SELL A PLAYER\n\nENTER CODE: ");
            int input_code;
            scanf("%d", &input_code);
            if (input_code == 1)
                return coach_main_menu();
            else if (input_code == 2)
                return sell_playyer();
            else
                return coach_main_menu();
        }
    }
    printf(RED"\n----------------\n       INVALID ID !!!\n-----------------\n"RESET);
    sleep(2);
    return sell_playyer();
}
void select_squad()
{
    ClearScreen();
    printf(MAG"---------- SELECT SQUAD ----------\n\n"RESET);
    //---------------players list------------
    printf("---------------------------------- ALL PLAYERS ----------------------------------\n");
    printf("%-9s%-18s%-21s%-23s%-21s\n", "ID", "NAME", "ATTACK POWER", "DEFENCE POWER", "VALUE");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < team_database.teams[team_loc].player_count; i++)
    {
        if (strcmp(team_database.teams[team_loc].players[i].name, "FREE_AGENT") != 0)
            printf("%-9d%-21s%-21d%-21d%-21d\n", team_database.teams[team_loc].players[i].id, team_database.teams[team_loc].players[i].name, team_database.teams[team_loc].players[i].curr_att_pow, team_database.teams[team_loc].players[i].curr_def_pow, team_database.teams[team_loc].players[i].value);
    }
    printf("---------------------------------------------------------------------------------\n");
    //----------------------------------------
    printf(YEL"1>"RESET" SELECT PALYER\n"YEL"2>"RESET" BACK\n---ENTER CODE: ");
    int code;
    scanf("%d",&code);
    if(code==2)
        return coach_main_menu();
    printf("-------------------\n");
    printf("---SELECT 5 PLAYER TO BE IN YOUR MAIN SQUAD:\n---enter 5 player ID seprate with space: \n");
    

    int p_count=0;
    int id;
    int players_id[5] = {};
    int j=0;
    int i=0;
    for (int k = 1; k <= 5; k++)
    {
        printf(YEL"ENTER PLAYER%d ID : "RESET ,k);
        scanf("%d" ,&id);
        while (j<team_database.teams[team_loc].player_count)
        {
            if ((strcmp(team_database.teams[team_loc].players[j].name, "FREE_AGENT") != 0) && (team_database.teams[team_loc].players[j].id == id))
            {
                players_id[i] = id;
                p_count++;
                i++;
                j = 0;
                break;
            }
            j++;
        }
    }
    if(p_count!=5)
    {
        
        printf("SOME PLAYERS ID IS INVALID! PLS ENTER AGAIN...\n");
        sleep(3);
        return select_squad();
    }

    int id1 = players_id[0], id2 = players_id[1], id3 = players_id[2], id4 = players_id[3], id5 = players_id[4];

    j = 0;
    team_database.teams[team_loc].squad_att_pow = 0;
    team_database.teams[team_loc].squad_def_pow = 0;
    printf(GRN"WELL DONE! MAIN SQUAD PLAYERS : \n"RESET);
    for (int i = 0; i < team_database.teams[team_loc].player_count; i++)
    {
        if (strcmp(team_database.teams[team_loc].players[i].name, "FREE_AGENT") != 0)
        {
            int p_id = team_database.teams[team_loc].players[i].id;
            char name[shortMAX];
            strcpy(name, team_database.teams[team_loc].players[i].name);
            if (p_id == id1 || p_id == id2 || p_id == id3 || p_id == id4 || p_id == id5)
            {
                team_database.teams[team_loc].squad[j] = p_id;
                j ++;
                team_database.teams[team_loc].players[i].status = 1;
                team_database.teams[team_loc].squad_att_pow += team_database.teams[team_loc].players[i].curr_att_pow;
                team_database.teams[team_loc].squad_def_pow += team_database.teams[team_loc].players[i].curr_def_pow;

                printf(GRN" << %s >> \n"RESET, name);
            }

            else
            {
                team_database.teams[team_loc].players[i].status = 0;
            }
        }
    }
    team_database.teams[team_loc].squad_status = 1;
    sleep(3);
    return coach_main_menu();
}
void submit_squad()
{
    ClearScreen();
    if (league_db.league_run_status != 0)
    {
        printf("------------------------------------\nNOW YOU DONT HAVE AN ACCESS TO THIS PART!\nPLEASE WAIT UNTILL SEASON END!\n------------------------------------\n");
        sleep(4);
        return coach_main_menu();
    }
    else if (team_database.teams[team_loc].squad_status == 1)
    {
        printf("------------------------\nYOU SUBMITED YOUR SQUAD!\n------------------------\n");
        sleep(2);
        return coach_main_menu();
    }
    printf(MAG"----------------------------------- SUBMIT SQUAD -----------------------------\n\n\n"RESET);
    printf(YEL"------------------------------------YOUR PLAYERS------------------------------\n\n");
    printf("%-7s%-8s%-13s%-19s%-20s%-21s\n", " ", "ID", "NAME", "ATTACK POWER", "DEFENCE POWER", "VALUE");
    printf("------------------------------------------------------------------------------\n"RESET);
    int j = 0;
    for (int i = 0; i < team_database.teams[team_loc].player_count; i++)
    {
        if (strcmp(team_database.teams[team_loc].players[i].name, "FREE_AGENT") != 0)
        {
            j++;
            printf("%-6d%-9d%-17s%-19d%-17d%-21d\n", j, team_database.teams[team_loc].players[i].id, team_database.teams[team_loc].players[i].name, team_database.teams[team_loc].players[i].attack_power, team_database.teams[team_loc].players[i].defence_power, team_database.teams[team_loc].players[i].value);
            // printf("---------------------------------------------------------------------------------\n");
        }
    }
    printf(YEL"------------------------------------------------------------------------------\n\n"RESET);
    if (team_database.teams[team_loc].active_player_count != 8)
    {
        printf(RED"YOU DONT HAVE ENOUGH PLAYERS TO SUBMIT SQUAD!\nYOU SHOULD HAVE 8 PLAYER!\n\n"RESET);
        sleep(6);
        return coach_main_menu();
    }
    printf(YEL"1>"RESET" SUBMIT SQUAD!\n"YEL"2>"RESET" BACK\n");
    printf("---ENTER CODE: ");
    int code;
    scanf("%d", &code);
    if (code == 1)
    {
        team_database.teams[team_loc].squad_status = 1;
        ClearScreen();
        printf(GRN"-------------------------------\nSQUAD SUBMITED SUCCESSFULLY !!!\n-------------------------------\n"RESET);
        sleep(2.5);
        return coach_main_menu();
    }
    else
    {
        return coach_main_menu();
    }
}
void fixtures()
{
    
    ClearScreen();
    printf(MAG"---------- FIXTURES ----------\n\n"RESET);
    if(league_db.league_run_status==0)
    {
        printf(RED"---------------------\nNO ACTIVE LEAGUE NOW!\n---------------------\n"RESET);
        sleep(1.5);
        return coach_main_menu();
    }
    if(team_database.teams[team_loc].league_status==0)
    {
        printf(RED"You have not participated in the league!\n"RESET);
        sleep(3);
        return coach_main_menu();
    }
    int num = (league_db.week_num - 1) * 4;
    int id;
    char name[shortMAX];
    char name1[50];
    char name2[50];
    char name3[50];
    char name4[50];

    int id1 = 0;
    int id2 = 0;
    int id3 = 0;
    int id4 = 0;
    int week = 0;
    for (int i = 0; i < 24; i += 4)
    {
        if (i % 4 == 0)
        {
            week++;
            printf(YEL"\n-------WEEK %d--------\n"RESET, week);
        }

        id1 = league_db.league_team[league_db.plan[i]];
        id2 = league_db.league_team[league_db.plan[i + 1]];
        id3 = league_db.league_team[league_db.plan[i + 2]];
        id4 = league_db.league_team[league_db.plan[i + 3]];
        int num = (week-1)*4 ;
        int team1_goals = league_db.goals[num] ;
        int team2_goals = league_db.goals[num+1] ;
        int team3_goals = league_db.goals[num+2] ;
        int team4_goals = league_db.goals[num+3] ;
        for (int j = 0; j < team_database.teams_count; j++)
        {
            if (team_database.teams[j].id == id1)
            {
                strcpy(name1, team_database.teams[j].name);
            }
            else if (team_database.teams[j].id == id2)
            {
                strcpy(name2, team_database.teams[j].name);
            }
            else if (team_database.teams[j].id == id3)
            {
                strcpy(name3, team_database.teams[j].name);
            }
            else if (team_database.teams[j].id == id4)
            {
                strcpy(name4, team_database.teams[j].name);
            }

        }


        if(league_db.week_num > week)
        {
            printf("%s %d-%d %s\n", name1, team1_goals ,team2_goals ,name2 );
            printf("%s %d-%d %s\n", name3, team3_goals ,team4_goals ,name4 );
        }

        else
        {
            printf("%s - %s\n", name1,name2);
            printf("%s - %s\n", name3,name4);
        }

    }
    printf(YEL"---------------------\n"RESET);
    printf(YEL"1>"RESET" BACK\n");
    printf("---ENTER CODE: ");
    int code;
    scanf("%d", &code);
    if (code == 1)
    {
        return coach_main_menu();
    }
    else
        return fixtures();
}
void upcoming_opponent()
{
    ClearScreen();
    if(league_db.league_run_status==0)
    {
        printf(RED"----------------------\nNO LEAGUE RUNNING NOW!\n----------------------\n"RESET);
        sleep(2);
        return coach_main_menu();
    }
    if(team_database.teams[team_loc].league_status==0)
    {
        printf(RED"You have not participated in the league!\n"RESET);
        sleep(3);
        return coach_main_menu();
    }
    printf(MAG"---------------- UPCOMING OPPONENT ---------------\n\n"RESET);
    int num = (league_db.week_num - 1) * 4;
    int id = team_database.teams[team_loc].id;
    char name[shortMAX];
    char name1[50];
    char name2[50];
    char name3[50];
    char name4[50];
    int id1 = 0;
    int id2 = 0;
    int id3 = 0;
    int id4 = 0;
    int week = 0;
    id1 = league_db.league_team[league_db.plan[num]];
    id2 = league_db.league_team[league_db.plan[num + 1]];
    id3 = league_db.league_team[league_db.plan[num + 2]];
    id4 = league_db.league_team[league_db.plan[num + 3]];
    for (int j = 0; j < team_database.teams_count; j++)
        {
            if (team_database.teams[j].id == id1)
                strcpy(name1, team_database.teams[j].name);
            else if (team_database.teams[j].id == id2)
                strcpy(name2, team_database.teams[j].name);
            else if (team_database.teams[j].id == id3)
                strcpy(name3, team_database.teams[j].name);
            else if (team_database.teams[j].id == id4)
                strcpy(name4, team_database.teams[j].name);
        }
    if (id1==id)
    {
        printf(GRN"==================================\n");
        printf("NEXT OPPONENT:");
        printf("%s\n",name2);
        printf("==================================\n"RESET);
        int att_pow;
        int def_pow;
        for (int j = 0; j < team_database.teams_count; j++)
        {
            if(id2==team_database.teams[j].id)
            {
                att_pow = team_database.teams[j].team_att_pow;
                def_pow = team_database.teams[j].team_def_pow;
                printf("-------------------- ALL PLAYERS --------------------\n");
                printf("%-9s%-18s\n", "ID", "NAME");
                printf("-----------------------------------------------------\n");
                for (int i = 0; i < team_database.teams[j].player_count; i++)
                {
                    if (strcmp(team_database.teams[j].players[i].name, "FREE_AGENT") != 0)
                        printf("%-9d%-21s\n", team_database.teams[j].players[i].id, team_database.teams[j].players[i].name);
                }
                printf("-----------------------------------------------------\n");
                printf(GRN"ATTACK POWER: %d "YEL"|"RESET GRN" DEFENCE POWER: %d"RESET,att_pow,def_pow);
            }
        }
        
    }
    else if(id2==id)
    {
        printf(GRN"==================================\n");
        printf("NEXT OPPONENT:");
        printf("%s\n",name1);
        printf("==================================\n"RESET);
        int att_pow;
        int def_pow;
        for (int j = 0; j < team_database.teams_count; j++)
        {
            if(id1==team_database.teams[j].id)
            {
                att_pow = team_database.teams[j].team_att_pow;
                def_pow = team_database.teams[j].team_def_pow;
                printf("-------------------- ALL PLAYERS --------------------\n");
                printf("%-9s%-18s\n", "ID", "NAME");
                printf("-----------------------------------------------------\n");
                for (int i = 0; i < team_database.teams[j].player_count; i++)
                {
                    if (strcmp(team_database.teams[j].players[i].name, "FREE_AGENT") != 0)
                        printf("%-9d%-21s\n", team_database.teams[j].players[i].id, team_database.teams[j].players[i].name);
                }
                printf("-----------------------------------------------------\n");
                printf(GRN"ATTACK POWER: %d "YEL"|"RESET GRN" DEFENCE POWER: %d"RESET,att_pow,def_pow);
            }
        }
        
    }
    else if(id3==id)
    {
            printf(GRN"==================================\n");
        printf("NEXT OPPONENT:");
        printf("%s\n",name4);
        printf("==================================\n"RESET);
        int att_pow;
        int def_pow;
        for (int j = 0; j < team_database.teams_count; j++)
        {
            if(id4==team_database.teams[j].id)
            {
                att_pow = team_database.teams[j].team_att_pow;
                def_pow = team_database.teams[j].team_def_pow;
                printf("-------------------- ALL PLAYERS --------------------\n");
                printf("%-9s%-18s\n", "ID", "NAME");
                printf("-----------------------------------------------------\n");
                for (int i = 0; i < team_database.teams[j].player_count; i++)
                {
                    if (strcmp(team_database.teams[j].players[i].name, "FREE_AGENT") != 0)
                        printf("%-9d%-21s\n", team_database.teams[j].players[i].id, team_database.teams[j].players[i].name);
                }
                printf("-----------------------------------------------------\n");
                printf(GRN"ATTACK POWER: %d "YEL"|"RESET GRN" DEFENCE POWER: %d"RESET,att_pow,def_pow);
            }
        }
        
    
    }
    else if(id4==id)
    {
            printf(GRN"==================================\n");
        printf("NEXT OPPONENT:");
        printf("%s\n",name3);
        printf("==================================\n"RESET);
        int att_pow;
        int def_pow;
        for (int j = 0; j < team_database.teams_count; j++)
        {
            if(id3==team_database.teams[j].id)
            {
                att_pow = team_database.teams[j].team_att_pow;
                def_pow = team_database.teams[j].team_def_pow;
                printf("-------------------- ALL PLAYERS --------------------\n");
                printf("%-9s%-18s\n", "ID", "NAME");
                printf("-----------------------------------------------------\n");
                for (int i = 0; i < team_database.teams[j].player_count; i++)
                {
                    if (strcmp(team_database.teams[j].players[i].name, "FREE_AGENT") != 0)
                        printf("%-9d%-21s\n", team_database.teams[j].players[i].id, team_database.teams[j].players[i].name);
                }
                printf("-----------------------------------------------------\n");
                printf(GRN"ATTACK POWER: %d "YEL"|"RESET GRN" DEFENCE POWER: %d"RESET,att_pow,def_pow);
            }
        }
    }
    printf(YEL"\n1>"RESET" BACK\n---ENTER CODE: ");
    int code;
    scanf("%d" ,&code);
    if(code==1)
        return coach_main_menu();
    else
        return upcoming_opponent();
    
}
void change_password()
{
    ClearScreen();
    printf(MAG"-------- CHANGE PASSWORD ---------\n\n"RESET);
    char inp_email[shortMAX];
    char inp_password[shortMAX];
    printf("---ENTER YOUR EMAIL: ");
    scanf("%s", &inp_email);
    printf("---ENTER YOUR CURRENT PASSWORD: ");
    scanf("%s", &inp_password);
    if (strcmp(inp_email, team_database.teams[team_loc].email) == 0)
    {
        if (strcmp(inp_password, team_database.teams[team_loc].password) == 0)
        {
            printf("---CORRECT! NOW ENTER YOUR NEW PASSWORD TO SET: ");
            char new_password[shortMAX];
            scanf("%s", &new_password);
            strcpy(team_database.teams[team_loc].password, new_password);
            ClearScreen();
            printf(GRN"\n------------------------------------\n   CHANGING PASSWORD HAVE DONE !!!\n-------------------------------\n"GRN);
            sleep(1.5);
            return coach_main_menu();
        }
        else
        {
            ClearScreen();
            printf(RED"PASSWORD IS NOT CORRECT !!!\n"RESET);
            sleep(2);
            return coach_main_menu();
        }
    }
    else
    {
        ClearScreen();
        printf(RED"EMAIL IS NOT CORRECT !!!\n"RESET);
        sleep(2);
        return coach_main_menu();
    }
}
//sort -layers
void sort_players_initials()
{
    for (int i = 0; i < all_p.last_p_loc ; i++)
    {
        player_sorted_list[i] = all_p.p_list[i];
    }
    return ;
}
void sort_players_func()
{
    int i, j;
    struct player temp_player;
    for (i = 0; i < all_p.last_p_loc; i++)
    {
        for (j = i; j < all_p.last_p_loc; j++)
        {
            if (player_sorted_list[i].value < player_sorted_list[j].value)
            {
                temp_player = player_sorted_list[j];
                player_sorted_list[j] = player_sorted_list[i];
                player_sorted_list[i] = temp_player;
            }
        }
    }
    return ;
}
void sort_plyers_show()
{
    printf("---------------------------------- ALL PLAYERS ------------------------------\n");
    printf("%-9s%-21s%-18s%-21s%-23s%-21s\n", "ID", "NAME", "TEAM", "ATTACK POWER", "DEFENCE POWER", "VALUE");
    printf("--------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < all_p.last_p_loc; i++)
    {
        if (strcmp(player_sorted_list[i].team, "FREE_AGENT") == 0)
        {
            printf("%-9d%-21s%-21s%-21d%-21d%-21d\n", player_sorted_list[i].id, player_sorted_list[i].name, player_sorted_list[i].team, player_sorted_list[i].attack_power, player_sorted_list[i].defence_power, player_sorted_list[i].value);
        }
    }
    printf("--------------------------------------------------------------------------------------------------\n");
    return ;
    //------------------------------------------------------------------------------------
}
//--standing
void league_standing()
{  
    ClearScreen();
    if(league_db.league_run_status==0)
    {
        printf(RED"----------------------\nNO LEAGUE RUNNING NOW!\n----------------------\n"RESET);
        sleep(2);
        return coach_main_menu();
    }
    
    standing_initials();
    standing_bubble_sort();
    standing_sorted_show(); 
    printf(YEL"1>"RESET" BACK\n");
    int code;
    scanf("%d",&code);
    if (code==1)
        return coach_main_menu();
    else
        return league_standing();


}
void standing_initials()
{
    int loc_list[4] = {league_db.t1_loc ,league_db.t2_loc ,league_db.t3_loc ,league_db.t4_loc};
    for (int i = 0; i < 4; i++)
    {
        info_list[i].id = team_database.teams[loc_list[i]].id;
        info_list[i].point = team_database.teams[loc_list[i]].point;
        info_list[i].gf = team_database.teams[loc_list[i]].gf;
        info_list[i].ga = team_database.teams[loc_list[i]].ga;
        info_list[i].gd = team_database.teams[loc_list[i]].gd;
        info_list[i].won = team_database.teams[loc_list[i]].won;
        info_list[i].lost = team_database.teams[loc_list[i]].lost;
        info_list[i].drawn = team_database.teams[loc_list[i]].drawn;
        info_list[i].played = team_database.teams[loc_list[i]].played;
        strcpy(info_list[i].name ,team_database.teams[loc_list[i]].name);
    }
    return ;
}
void standing_bubble_sort()
{
    int i, j;
    struct Info temp_info;
    for (i = 0; i < 4; i++)
    {
        for (j = i; j < 4; j++)
        {
            if (info_list[i].point < info_list[j].point)
            {
                temp_info = info_list[j];
                info_list[j] = info_list[i];
                info_list[i] = temp_info;
            }
            else if (info_list[i].point == info_list[j].point)
            {
                if (info_list[i].gd < info_list[j].gd)
                {
                    temp_info = info_list[j];
                    info_list[j] = info_list[i];
                    info_list[i] = temp_info;
                }
                else if(info_list[i].gd == info_list[j].gd)
                {
                    if (info_list[i].gf < info_list[j].gf)
                    {
                        temp_info = info_list[j];
                        info_list[j] = info_list[i];
                        info_list[i] = temp_info;
                    }
                    else if(info_list[i].gf == info_list[j].gf)
                    {
                        if (info_list[i].ga > info_list[j].ga)
                        {
                            temp_info = info_list[j];
                            info_list[j] = info_list[i];
                            info_list[i] = temp_info;
                        }
                    }
                }
            }
        }
    }
    return ;

}
void standing_sorted_show()
{
    ClearScreen();
    printf(MAG"------------------- LEAGUE STANDING ------------------\n\n\n"RESET);
    printf("----------\nweek : %d\n----------\n",league_db.week_num-1);
    printf(YEL"-------------------------------------------------- STANDING --------------------------------------------------\n\n");
    printf("%-5s%-20s%-12s%-9s%-11s%-11s%-10s%-10s%-9s%-8s\n"," ", "TEAM", "PLAYED","WON","DRAWN","LOST","GF","GA","GD","POINT");
    printf("--------------------------------------------------------------------------------------------------------------\n"RESET);
    //---------------------------------------------------------------------------------------------
    int j=1;
    for (int i = 0; i < 4 ; i++)
    {
        if(team_database.teams[team_loc].id == info_list[i].id)
        {
            char name[shortMAX];
            strcpy(name ,info_list[i].name);
            int played = info_list[i].played;
            int won = info_list[i].won , drawn = info_list[i].drawn , lost = info_list[i].lost;
            int gf = info_list[i].gf , ga = info_list[i].ga , gd = info_list[i].gd;
            int point = info_list[i].point;
            printf(GRN"%-5d%-23s%-10d%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n"RESET,j ,name ,played ,won ,drawn ,lost ,gf ,ga ,gd ,point);
            j++;
        }
        else
        {
            char name[shortMAX];
            strcpy(name ,info_list[i].name);
            int played = info_list[i].played;
            int won = info_list[i].won , drawn = info_list[i].drawn , lost = info_list[i].lost;
            int gf = info_list[i].gf , ga = info_list[i].ga , gd = info_list[i].gd;
            int point = info_list[i].point;
            printf("%-5d%-23s%-10d%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n",j ,name ,played ,won ,drawn ,lost ,gf ,ga ,gd ,point);
            j++;
        }
    }
    printf(YEL"--------------------------------------------------------------------------------------------------------------\n\n"RESET);
    return ;
}

//-----LOGIN-----
void login_page()
{
    ClearScreen();
    printf(MAG"---------- LOGIN PAGE ----------\n\n"RESET YEL"1>"RESET" SIGN IN\n"YEL"2>"RESET" FORGOT PASSWORD\n"YEL"3>"RESET" EXIT\n\n");
    int code;
    printf("ENTER CODE: ");
    scanf("%d", &code);
    if (code != 1 && code != 2 && code != 3)
    {
        printf("INVALID CODE!try again...");
        sleep(1);
        return login_page();
    }
    else if (code == 1)
        return sign_in_page();
    else if (code == 2)
        return forgot_pass_page();
    else if (code == 3)
    {
        ClearScreen();
        printf("---------\nGOOD BYE!\n---------\n");
        sleep(2);
        ClearScreen();
        return;
        // ClearScreen();
        // SAVES();
        // exit(0);
    }
}
void sign_in_page()
{
    ClearScreen();
    char inp_name[shortMAX];
    printf(MAG"--------- SIGN IN ---------\n\n"RESET);
    // printf("HINT: TEAM NAME FOR ADMIN PAGE IS-> 'Admin' \n");
    printf("---ENTER TEAM NAME: ");
    scanf("%s", &sign_in_inp_name);
    // check "admin page" or "team page"
    if (strcmp(sign_in_inp_name, "Admin") == 0)
        return admin_sign_in();
    else
        return coach_sign_in();
}
void admin_sign_in()
{
    char inp_name[shortMAX];
    char inp_pass[shortMAX];
    // ClearScreen();
    //  input password
    printf("---ENTER PASSWORD: ");
    scanf("%s", &inp_pass);
    if (strcmp(inp_pass, admin_database.password) == 0)
    {
        ClearScreen();
        printf(GRN"SIGNING IN ADMIN PAGE SUCCESSFULLY !!!!\n"RESET);
        sleep(1.3);
        ClearScreen();
        return admin_main_menu();
    }
    else
    {
        ClearScreen();
        printf(RED"INVALID PASSWORD !!!ENTER PASSWORD AGAIN...\n"RESET);
        sleep(1.5);
        ClearScreen();
        return admin_sign_in();
    }
}
void coach_sign_in()
{
    char inp_pass[shortMAX];
    for (int i = 0; i <= team_database.teams_count; i++)
    {
        strcpy(acc_name, team_database.teams[i].name);
        if (strcmp(sign_in_inp_name, acc_name) == 0)
        {
            strcpy(acc_password, team_database.teams[i].password);
            printf(GRN"!!! password is= %s !!!\n"RESET, team_database.teams[i].password);
            break;
        }
        else if (i == team_database.teams_count)
        {
            ClearScreen();
            printf(RED"INVALID TEAM NAME !!!\n"RESET);
            sleep(1);
            return login_page();
        }
        else
            continue;
    }
    printf("\n---ENTER PASSWORD: ");
    scanf("%s", &inp_pass);
    if (strcmp(inp_pass, acc_password) == 0)
    {
        ClearScreen();
        printf(GRN"SIGNING IN SUCCESSFULLY !!!\n"RESET);
        sleep(1.5);
        team_location(acc_name);
        return coach_main_menu();
    }
    else
    {
        ClearScreen();
        printf(RED"INVALID PASSWORD !!!"RESET);
        sleep(1.5);
        return login_page();
    }
}
void forgot_pass_page()
{
    ClearScreen();
    printf(MAG"---------- FORGOT PASSWORD ----------\n\n"RESET);
    char input_name[shortMAX];
    char input_email[shortMAX];
    char acc_email[shortMAX];
    printf("---ENTER NAME OF YOUR TEAM: ");
    scanf("%s", &input_name);
    printf("---ENTER YOUR EMAIL: ");
    scanf("%s", &input_email);
    int i = 0;
    for (i; i < team_database.teams_count; i++)
    {
        strcpy(acc_name, team_database.teams[i].name);
        if (strcmp(input_name, acc_name) == 0)
        {
            strcpy(acc_email, team_database.teams[i].email);
            team_loc = i;
            break;
        }
        else if (i == team_database.teams_count)
        {
            // ClearScreen();
            printf(RED"INVALID TEAM NAME !!!\n"RESET);
            sleep(3);
            return login_page();
        }
        else
            continue;
    }
    if (strcmp(input_email, acc_email) == 0)
    {
        // ClearScreen();
        char new_password[shortMAX];
        printf(GRN"WELL DONE!"RESET" NOW ENTER YOUR NEW PASSWORD TO SET: ");
        scanf("%s", &new_password);
        strcpy(team_database.teams[team_loc].password, new_password);
        ClearScreen();
        printf("--------------------------------------------\nCHANGING PASSWORD HAVE DONE SUCCESSFULLY !!!\n--------------------------------------------\n");
        printf(GRN"|||   NEW PASSWORD IS : %s   |||\n"RESET, team_database.teams[team_loc].password);
        sleep(2);
        return coach_main_menu();
    }
    else
    {
        // ClearScreen();
        printf(RED"INVALID EMAIL !!!\n"RESET);
        sleep(3);
        return login_page();
    }
}

//-----SAVE & LOAD DATA-----
void LOADS()
{
    admin_load_data();
    team_load_data();
    all_players_load();
    league_load_data();
    return;
}
void SAVES()
{
    team_save_data();
    admin_save_data();
    all_players_save();
    league_save_data();
}
void team_load_data()
{

    FILE *fptr1 = fopen("teams_database.txt", "rb+");
    if (fptr1 == NULL)
    {
        fclose(fptr1);
        FILE *fptr2 = fopen("teams_database.txt", "wb+");
        fclose(fptr2);
        return ;
    }

    FILE *fptr = fopen("teams_database.txt", "rb+");
    int i = 0;
    fread(&team_database, sizeof(struct totall_team), 1, fptr);
    fclose(fptr);
    return ;
}
void team_save_data()
{
    FILE *fptr = fopen("teams_database.txt", "wb+");
    fwrite(&team_database, sizeof(struct totall_team), 1, fptr);
    fclose(fptr);
    return ;
}
void admin_load_data()
{
    FILE *fptr = fopen("admin_database.txt", "rb+");
    if(fptr==NULL)
    {
        fclose(fptr);
        FILE *fptr = fopen("admin_database.txt", "wb+");
        fclose(fptr);
        return ;
    }
    fread(&admin_database, sizeof(struct admin), 1, fptr);
    fclose(fptr);
    return;
}
void admin_save_data()
{
    FILE *fptr = fopen("admin_database.txt", "wb+");
    fwrite(&admin_database, sizeof(struct admin), 1, fptr);
    fclose(fptr);
    return ;

}
void all_players_load()
{
    FILE *fptr = fopen("allplayers_database.txt", "rb+");
    if (fptr == NULL)
    {
        fclose(fptr);
        FILE *fptr = fopen("allplayers_database.txt", "wb+");
        fclose(fptr);
        return ;
    }
    fread(&all_p, sizeof(struct total_player), 1, fptr);
    fclose(fptr);
    return;
}
void all_players_save()
{
    FILE *fptr = fopen("allplayers_database.txt", "wb+");
    fwrite(&all_p, sizeof(struct total_player), 1, fptr);
    fclose(fptr);
    return ;
}
void league_load_data()
{
    FILE *fptr = fopen("league_database.txt", "rb+");
    if (fptr == NULL)
    {
        fclose(fptr);
        FILE *fptr = fopen("league_database.txt", "wb+");
        fclose(fptr);
        return ;
    }
    fread(&league_db, sizeof(struct league), 1, fptr);
    fclose(fptr);
    return ;
}
void league_save_data()
{
    FILE *fptr = fopen("league_database.txt", "wb+");
    fwrite(&league_db, sizeof(struct league), 1, fptr);
    fclose(fptr);
    return ;
}
