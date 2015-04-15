#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Structs located in this header "Champion.h"
#include "Champion.h"
//Starting Overhead for MySQL Database setup

struct Champion {
    char *champName;
    int   creepScore;
    int   kills;
    int   deaths;
    int   assists;
    double KDA;
};
//Defines methods to create aforementioned "template"
struct Champion *Champion_summon (char *champName, int creepScore, int kills, int deaths, int assists, double KDA) {
    struct Champion *who = malloc(sizeof(struct Champion));
    assert (who != NULL);
    
    who -> champName   = strdup(champName);
    who -> creepScore  = creepScore;
    who -> kills       = kills;
    who -> deaths      = deaths;
    who -> assists     = assists;
    who -> KDA         = (kills + assists)/deaths;
    return who;
}
//Creates methods of deallocation
void Champion_destroy (struct Champion *who) {
    assert (who != NULL);
    
    free (who->champName);
    free (who);
}
//Defines the first true "method"
void Champion_print (struct Champion *who) {
    printf("Name: %s\n",        who->champName);
    printf("\tKills: %d\n",     who->kills);
    printf("\tDeaths: %d\n",    who->deaths);
    printf("\tAssists: %d\n",   who->assists);
    printf("\tCS: %d\n",        who->creepScore);
    printf("\tKDA: %f\n",       who->KDA);
}
int main() {

    //Preps the forced "proper" input loop
    FILE *fp = fopen("/Users/Sichais/Documents/Champion.txt", "a");
    if (fp == NULL) {
        printf("Error opening file");
    }
    bool breakOut = false;
    //Asks for input
    printf("\nSummon another champion? y/n: ");
    //Pre-packages struct parts for modding
    char    championName[16];
    char    summonCheck;
    
    int     championCS      = 0;
    int     championKills   = 0;
    int     championDeaths  = 0;
    int     championAssists = 0;
    double  championKDA     = 0;
    //Forced input loop; requires user to input *something* usable
    do {
        summonCheck = getchar();
        getchar();
        
        switch(summonCheck) {
            case 'y':
            case 'Y': {
                printf("\nEnter a Champion name: ");
                scanf("%15s", championName);
                getchar();
                
                printf("\nEnter %s's CS: ", championName);
                scanf("%10d", &championCS);
                getchar();
                
                printf("\nEnter %s's Kills: ", championName);
                scanf("%10d", &championKills);
                getchar();
                
                printf("\nEnter %s's Deaths: ", championName);
                scanf("%10d", &championDeaths);
                getchar();
                
                printf("\nEnter %s's Assists: ", championName);
                scanf("%10d", &championAssists);
                getchar();
                
                championKDA = (championKills + championAssists) / championDeaths;
                printf("\n%s's KDA is: %f", championName, championKDA);
                ++breakOut;
                break;
            }
            case 'n':
            case 'N': {
                printf("Exitting program");
                
                ++breakOut;
                break;
            }
            default: {
                printf("\nInvalid input\ny/n: ");
                break;
            }
        }
    } while (!breakOut); //Breaks out of the loop if breakOut ISN'T zero, ideally one
    if (summonCheck == 'n') {
        exit(1);
    }
    struct Champion *newSummon = Champion_summon(championName, championCS, championKills, championDeaths, championAssists, championKDA);
    
    Champion_print(newSummon);
    fprintf(fp, "%s,\n \t%d CS,\n \t%d Kills,\n \t%d Deaths,\n \t%d Assists,\n \t%f KDA\n", newSummon->champName, newSummon->creepScore, newSummon->kills, newSummon->deaths, newSummon->assists, newSummon->KDA);
    printf("Champion.txt successfully modified");
    
    
    return 0;
}
