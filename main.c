#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lab2.h"

int main(){
    adventureGame ag={

        .room = 0,
        //process look variables
        .lookArray = {// Put the description for the look in each room here.
                "You are in a main hall. There is a storeroom to the south, and a kitchen lies to the east.",//room1
                "You are in the kitchen. There is a graveyard to the east, and the main hall lies to the west.",//room2
                "You are in the graveyard. There is a clinic to the east, kitchen lies to the west and keyroom lies to the south",//room3
                "You are in the clinic. There is a graveyard to the west, the elixir room lies to the south and the backyard lies to the east",//room4
                "You are in the backyard. There is a sewage to the south, and the clinic lies to the west.",//room5
                "You are in the storeroom. The main hall lies to the north.",//room6
                "You are in the frozen room. There is a key room to the east, and the meat room lies to the south.",//room7
                "You are in the key room. There is a graveyard to the north, an elixir room to the east, a training room to the south and a frozen room to the west.",//room8
                "You are in the elixir room. There is a clinic to the north, and the key room lies to the west.",//room9
                "You are in the sewage. There is a backyard to the north.",//room10
                "You are in the meat room. There is a frozen room to the north, and the training room lies to the east.",//room11
                "You are in the training room. There is a meat room to the west, the key room lies to the north and the mysterious room lies to the east.",//room12
                "You are in the mysterious room. There is a training room to the east.",//room13
            },
            .roomArray = {// Put the description for the look in each room here.
                "Main hall",//room1
                "Kitchen",//room2
                "Graveyard",//room3
                "Clinic",//room4
                "Backyard",//room5
                "Storeroom",//room6
                "Frozen room",//room7
                "Key room",//room8
                "Elixir room",//room9
                "Sewage",//room10
                "Meat room",//room11
                "Training room",//room12
                "Mysterious room",//room13
            },

            //processMovement variable
            .moveArray={
            {"You cannot go north","You go south to the storeroom ","You go east to the kitchen","You cannot go west"},//room1
            {"You cannot go north","You cannot go south","You go east to the graveyard","You go west to the main hall"},//room2
            {"You cannot go north","You go south to the keyroom","You go east to the clinic","You go west to the kitchen"},//room3
            {"You cannot go north","You go south to the elixir room","You go east to the backyard","You go west to the graveyard"},//room4
            {"You cannot go north","You go south to the sewage","You cannot go east","You go west to the clinic"},//room5
            {"You go north to the main hall","You cannot go south","You cannot go east","You cannot go west"},//room6
            {"You cannot go north","You go south to the meat room","You go east key room","You cannot go west"},//room7
            {"You go north to the graveyard","You go south to the training room","You go east to the elixir room","You go west to the frozen room"},//room8
            {"You go north to the clinic","You cannot go south","You cannot go east","You go west to the keyroom"},//room9
            {"You go north to the backyard","You cannot go south","You cannot go east","You cannot go west"},//room10
            {"You go north to the frozen room","You cannot go south","You go east to the training room","You cannot go west"},//room11
            {"You go north to the keyroom","You cannot go south","You go east to the mysterious room","You go west to the meat room"},//room12
            {"You cannot go north","You cannot go south","You cannot go east","You go west to the training room"},//room13
            },

            .moveToArray={// North, South, East, West
                {-1,5,1,-1}, //room1
                {-1,-1,2,0},//room2
                {-1,7,3,1},//room3
                {-1,8,4,2},//room4
                {-1,9,-1,3}, //room5
                {0,-1,-1,-1},//room6
                {-1,10,7,-1},//room7
                {2,11,8,6},//room8
                {3,-1,-1,7}, //room9
                {4,-1,-1,-1},//room10
                {6,-1,11,-1},//room11
                {7,-1,12,10},//room12
                {-1,-1,-1,11},//room13
            },

        //killMonster Variable
        .monsterArray = {"","","Zombie","","Werewolf","Monster","Dracula","","","Lizard-man","Bride-of-Dracula","","Dragon",},
        .monsterStatusArray = {-1,-1,5,-1,12,4,12,-1,-1,5,7,-1,12},//-1 means no enemy
        .size_monsterarray=13,
        .swordeff={0,0,-1,0,0,-1,-2,0,0,-1,-2,0,-1},//0 means it will not cause extra dmg, -3 means it will while -4 means it cause less dmg
        .diamondcrosseff={0,0,0,0,0,0,-1,0,0,0,-1,0,0},
        .silverspeareff={0,0,0,0,-1,0,0,0,0,0,0,0},


        //ProcessGet variable
        .N_artifact = 13,
        .artifact = {"","Food","","Medpack","","Sword","Copper Key","Bronze Key","Elixir","Diamond Cross","","Silver Spear", "Golden Chalice"},
        .artifactcpy = {-2,1,-2,3,-2,5,6,7,8,9,-2,11,12},
        .artifactLoc = {-2,1,-2,3,-2,5,6,7,8,9,-2,11,12},// if taken, assign it as -1 while if doesn't exist, assign as -2
        .max_inventory=3,
        .cannotget={0,0,0,0,0,0,-1,0,0,-1,0,0,-1},//-1 means cannot get unless kill enemy

        //processHeal
        .HP=12,
        .previouscommand="",

        //exp
        .xp=0,//initialize to 0

        //processunlock
        .doorcondition={1,1,1,1,-2,1,1,1,1,1,1,-1,1},//-1 means locked, 0 means no lock, 1 means it's not locked at all
        .cannotunlock={0,0,0,0,-1,0,0,0,0,0,0,0,0},//-1 means cannot use unlock door unless the enemy is killed


    };

    printf("________________________________________________________________________________________________________________________\n");
    printf("                                            Welcome to the adventure game!\n");
    printf("________________________________________________________________________________________________________________________\n");
    printf("\n");
    processHelp(&ag);
    processLook(&ag);
    while (fgets(ag.command,1000,stdin)){
        if(processCommand(&ag)==0){
            break;
        }
    }
}
