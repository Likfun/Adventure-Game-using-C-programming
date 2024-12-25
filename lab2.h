typedef struct adventureGame {
    char command[1000]; // Command typed by the user
    int size_monsterarray;      // how many monster existed
    int room;         // The room the user is in. Initialized to start in room#0

    const char *lookArray[13];   //Get memory for an array of 4 char*'s
    const char* roomArray[13];


    const char *moveArray[13][4];    //Get memory for an array of 4x4 char*'s
    const int moveToArray[13][4];    //Memory for destination rooms

    const char *monsterArray[13];
    int monsterStatusArray[13];
    int swordeff[13];
    int diamondcrosseff[13];
    int silverspeareff[13];

    const int N_artifact;
    const char *artifact[13];
    int artifactcpy[13];
    int artifactLoc[13];
    const int max_inventory;
    int cannotget[13];

    //processHeal
    int HP;

    //exp
    int xp;
    //when click enter go to previous code
    char previouscommand[1000];

    int doorcondition[13];
    int cannotunlock[13];


} adventureGame;

int processCommand(adventureGame *ag);// to pass on the commands typed from player to the computer
int processLook(adventureGame *ag);// to see what are inside(artifacts, enemy) a specific room the player is in
int processMovement(adventureGame *ag);// to move from one room to another if the direction is valid
int processKillMonster(adventureGame *ag);//to process the situation of the enemy(eg the monster is dead or alive) and the HP status of player(No HP, player dead, then terminate)
int processKilleffectiveness(adventureGame *ag);//to process whether got effectiveness or not towards a specific enemy
void processHelp(adventureGame *ag);//to print out the command that are available
int processAlternate(adventureGame *ag);// to process kill ..., eg: kill dragon, but the dash in between is important, eg:bride-of-dracula
int processHealth(adventureGame*ag);//to process to heal how much HP to player, if reach 12, will not add anymore
int processGet(adventureGame *ag);//to get artifacts
void printInventory(adventureGame *ag);//to print what's inside artifact
int processDrop(adventureGame *ag);//to drop artifact to the room player's currently in
int processNotGet(adventureGame *ag);//if artifact is not in the room the player is currently in, then it will process tp say, u dont have...
void processInfo(adventureGame *ag);// to check the status of player
void previouscommand(adventureGame *ag);//to recall the previous command by hitting enter key
int processunlock(adventureGame *ag);// to unlock locked door with specific key
void processXP(adventureGame *ag);//to check the xp player got, and print out the category of grades based on the XP player got
int processWin(adventureGame *ag);// to process if golden chalice is detected in room 0, will ask u whether want to quit the game or not
int gethit(adventureGame *ag);// to randomize the dmg hit by enemy to player and dmg hit to enemy by player if player are holding specific artifact
void processrules(adventureGame *ag);// to print out the rules of the game
