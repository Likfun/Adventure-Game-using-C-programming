#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lab2.h"
#include<time.h>

//each function is explained in lab2.h file
void replaceNewLine(adventureGame *ag)
{
    for (int i=0;ag->command[i]!='\0'; i++)
        {// Iterate over every char in the command
            if (ag->command[i]=='\n')
            { // Search for newline characters
                ag->command[i]='\0'; // replace them with end-of-string char.
                return; // We return after first newline character is found
            }
        }
}

int processCommand(adventureGame *ag){
    replaceNewLine(ag);//check any new line character
    previouscommand(ag);// check if got new line character, replace it with previous command

    //Rules command
    if(strcasecmp(ag->command,"Rules")==0){processrules(ag);return(1);}//tell u the rules

    //exit command
    if (strcasecmp(ag->command,"exit")==0)
    {printf("You exit the game.\n");
    printf("Your XP is %d\n",ag->xp);
    return(0);}//is a build-in function that terminates the program entirely

    //look command
    if((strcasecmp(ag->command,"look")==0)||(strcasecmp(ag->command,"l")==0)){processLook(ag);//tell u want is inside the room(enemy n artifacts, and the moveable room from current room
        return(1);}

    //kill enemy(monster) command
    if ((strcasecmp(ag->command,"killmonster")==0)||(strcasecmp(ag->command,"km")==0)){//to kill enemy
        processKillMonster(ag);
        return(1);}

    //unlock door command
    if (strcasecmp(ag->command,"unlock door")==0){//to unlock locked door, even the door no lock be4, it will still print the message"u can now enter the room"
        processunlock(ag);return(1);}

    //alternate kill command
    if ((strncasecmp(ag->command,"kill ",4)==0))//if lets say u type kill dragon n the room u currently in got dragon,
    //it will call processKillMonster() function
    {processAlternate(ag);return(1);}

    //move command
    if(processMovement(ag)){return(1);}// to move to 'e','w','s','n'


    //help command
    if(strcasecmp(ag->command, "help")==0)//to print out the commands
    {processHelp(ag);return(1);}

    //get command
    if (strncasecmp(ag->command,"get ",4)==0) {//to get artifact
            processGet(ag);return(1);}

    //inventory command
    if((strcasecmp(ag->command,"inventory")==0)||(strcasecmp(ag->command,"i")==0))//to see what's gotten(artifacts)
    {printInventory(ag);return(1);}


    //drop command
    if (strncasecmp(ag->command,"drop ",5)==0) {//to drop artifacts
            processDrop(ag);return(1);}

    //health command
    if((strcasecmp(ag->command,"eat food")==0)||(strcasecmp(ag->command,"drink elixir")==0)||(strcasecmp(ag->command,"use medpack")==0))//to regain HP
    {processHealth(ag);return(1);}

    if(strcasecmp(ag->command,"info")==0){processInfo(ag);return(1);}// To see the current status if player

    //if invalid command, print unknown command
    printf("Unknown command: %s\n", ag->command);
    return(1);
}

void previouscommand(adventureGame *ag){
  if (strlen(ag->command)==0) {strcpy(ag->command, ag->previouscommand);} // If "Enter" pressed, execute the previous command
  else {strcpy(ag->previouscommand, ag->command);}// Store the current command as previous command
}

int processLook(adventureGame *ag){
    printf("%s\n", ag->lookArray[ag->room]);//print out the lookarray, giving out room name and move condition
    printf("You are in Room: %d\n",ag->room);//print out the room number

    if(ag->monsterStatusArray[ag->room]>0){
        printf("There is a %s with HP of %d here\n", ag->monsterArray[ag->room],ag->monsterStatusArray[ag->room]);//print out enemy in current room with its HP
    }
    else if(ag->monsterStatusArray[ag->room]==0){
        printf("There is a dead %s here\n", ag->monsterArray[ag->room]);//if enemy HP==0, print it is dead
    }

    for(int i=0;i<ag->N_artifact;i++){
        if(ag->artifactLoc[i]==ag->room){
            printf("You see %s here\n", ag->artifact[i]);//print out any artifacts seen here
        }
    }
    return(1);
}

int processunlock(adventureGame *ag) {
    int i=0;
    if (ag->monsterStatusArray[ag->room]==0&&ag->doorcondition[ag->room]<-1)//if the enemy in current room is dead, and if doorcondition array is less than -1, add 1
    {ag->doorcondition[ag->room]++;}
    for (i=0;i<ag->N_artifact;i++)//iterate i over less than N_artifact
    { // iterate over each number of artifact,13 in the list
            if(ag->artifactLoc[i]==-1&&strcasecmp(ag->artifact[i],"Bronze Key")==0&&ag->room==4){//if artifact is taken and artifact's name is bronze key and current room is 4
                if(ag->doorcondition[ag->room]==-1)//if doorcondition is -1, means it's lock
                    ag->doorcondition[ag->room]++;//unlock it
                else{printf("You have to kill the %s first\n",ag->monsterArray[ag->room]);}// if not say u have to kill enemy first, as it's not -1 for doorcondition
            }

             if(ag->artifactLoc[i]==-1&&strcasecmp(ag->artifact[i],"Copper Key")==0&&ag->room==11){//if artifact is taken and artifact's name is copper key and current room is 4
                if(ag->doorcondition[ag->room]==-1)//if doorcondition is -1, means it's lock
                    ag->doorcondition[ag->room]++;//unlock it
            }
    }
    if(ag->doorcondition[ag->room]==0){printf("You can now enter the room\n");}//if doorcondition is 0
    else if(ag->doorcondition[ag->room]==1){printf("No lock is applied on the room\n");}//if door condition is 1
    else{printf("The room is locked\n");}//print this
    return(1);
}

int processMovement(adventureGame *ag){
    replaceNewLine(ag);//replace any \n to \0
    if ((ag->doorcondition[ag->room]<0)&&(ag->room==4)&&((strcasecmp(ag->command,"s"))==0||strcasecmp(ag->command,"south")==0))//if towards south, the doorcondition is not 0,
    {       printf("The room is locked\n");//print this
            printf("You need bronze key and defeat the werewolf\n");//n this
            return(1);
    }
    if ((ag->doorcondition[ag->room]<0)&&(ag->room==11)&&((strcasecmp(ag->command,"e"))==0||strcasecmp(ag->command,"east")==0))//same theory as above
    {       printf("The room is locked\n");
            printf("You need copper key\n");
            return(1);
    }

    else
    {
    if((strcasecmp(ag->command,"north")==0) || (strcasecmp(ag->command,"n")==0)){
        if(ag->moveToArray[ag->room][0] != -1){
            printf("%s\n", ag->moveArray[ag->room][0]);
            ag->room = ag->moveToArray[ag->room][0];
            processLook(ag);
        }
        else{printf("Unable to move north.\n");}
        return(1);
    }

    else if((strcasecmp(ag->command,"south")==0) || (strcasecmp(ag->command,"s")==0)){
        if(ag->moveToArray[ag->room][1] != -1){
            printf("%s\n", ag->moveArray[ag->room][1]);
            ag->room = ag->moveToArray[ag->room][1];
            processLook(ag);
        }
        else{printf("Unable to move south.\n");}
        return(1);
    }

    else if((strcasecmp(ag->command,"east")==0) || (strcasecmp(ag->command,"e")==0)){
        if(ag->moveToArray[ag->room][2] != -1){
            printf("%s\n", ag->moveArray[ag->room][2]);
            ag->room = ag->moveToArray[ag->room][2];
            processLook(ag);
        }
        else{printf("Unable to move east.\n");}
        return(1);
    }

    else if((strcasecmp(ag->command,"west")==0) || (strcasecmp(ag->command,"w")==0)){
        if(ag->moveToArray[ag->room][3] != -1){
            printf("%s\n", ag->moveArray[ag->room][3]);
            ag->room = ag->moveToArray[ag->room][3];
            processLook(ag);
            processWin(ag);
        }
        else{printf("Unable to move west.\n");}
        return(1);
    }

    else{return(0);}
    }
}

int processKillMonster(adventureGame *ag)
{   //if monster is dead
    if(ag->monsterStatusArray[ag->room] == 0){
        printf("The %s is already dead\n", ag->monsterArray[ag->room]);
    }
    //if monster doesn't exist
    if (ag->monsterStatusArray[ag->room] == -1){
        printf("There's no enemy here\n");
    }
    if(ag->monsterStatusArray[ag->room] >= 1){//if monster is alive
        processKilleffectiveness(ag);
        if(ag->HP<0){ag->HP=0;}//reassign it as 0 if less than 0
        printf("________________________________________________________________________________________________________________________\n");
        printf("                                            The remaining HP of %s is %d\n", ag->monsterArray[ag->room], ag->monsterStatusArray[ag->room]);
        printf("________________________________________________________________________________________________________________________\n");
        printf("                                             Your remaining HP is %d\n",ag->HP);
        printf("                                                    Your XP is %d\n",ag->xp);
        printf("________________________________________________________________________________________________________________________\n");
        if (ag->HP==0){//if player's HP is 0
        printf("You died\n");//print this
        printf("Your XP score:%d",ag->xp);
        exit(0);}//exit the game
        if (ag->monsterStatusArray[ag->room]==0){printf("You have slayed the %s\n",ag->monsterArray[ag->room]);//if enemy HP==0, print that:
        ag->cannotget[ag->room]=0;}//if the enemy is dead, then update cannotget[room no. currently] as zero, indicates can take
        return(1);
    }
    if(ag->monsterStatusArray[4]==0){//if HP of werewolf is zero
        ag->doorcondition[5]++;//door condition +1
    }
    return(1);
}

int processKilleffectiveness(adventureGame *ag)
{
    int swordcondition=0;
    int diamondcrosscondition=0;
    int silverspearcondition=0;
    srand(time(NULL));//creating random number
    int y;
    y=1+rand()%2;//y ranges from 1 to 2
    for(int i=0;i<ag->N_artifact;i++)//check whether i have sword/diamond cross/silver spear in my inventory
    {   if(strcasecmp(ag->artifact[i],"Diamond Cross")==0&&(ag->artifactLoc[i]==-1))
        {diamondcrosscondition=1;}//stop the loop once if condition is acheived
        if(strcasecmp(ag->artifact[i],"Sword")==0&&(ag->artifactLoc[i]==-1))
        {swordcondition=1;}//if yes, change the global variable to 1
        if(strcasecmp(ag->artifact[i],"Silver Spear")==0&&(ag->artifactLoc[i]==-1))
        {silverspearcondition=1;}
    }
    if(swordcondition!=0&&ag->swordeff[ag->room]==-1)//if got sword
    {gethit(ag);return(1);}//-1, means can deal super eff dmg to the specific enemy

    else if(swordcondition!=0&&ag->swordeff[ag->room]==-2&&diamondcrosscondition==0)//if -2, that means deal less dmg to the enemy
    {   ag->monsterStatusArray[ag->room]--;//super ineffective, 1 dmg
        ag->HP-=y;//but still -player HP range 1-2.
        if(ag->monsterStatusArray[ag->room]<0){ag->monsterStatusArray[ag->room]=0;}
        printf("You hit the %s by 1 as you are holding sword\n", ag->monsterArray[ag->room]);
        printf("The %s hit you by %d\n",ag->monsterArray[ag->room],y);
        return(1);
    }
    if(silverspearcondition!=0&&ag->silverspeareff[ag->room]==-1)//if got silverspear
    {gethit(ag);return(1);}

    else if(diamondcrosscondition!=0&&ag->diamondcrosseff[ag->room]==-1)//if got diamondcross
    {gethit(ag);return(1);}
    else//if everything u dont have
    {   if (ag->monsterStatusArray[ag->room]==1){ag->xp++;}//if dmg u hot to enemy is more than current enemy HP, add XP==enemy current HP
        else {ag->xp+=2;}//else add 2 as u deal 2 dmg to enemy
        ag->monsterStatusArray[ag->room]-=2;
        ag->HP-=y;//enemy deal 1-2 dmg to player
        printf("You hit the %s by 2\n", ag->monsterArray[ag->room]);
        printf("The %s hit you by %d\n",ag->monsterArray[ag->room],y);
        if(ag->monsterStatusArray[ag->room]<0){ag->monsterStatusArray[ag->room]=0;}//if enemy HP is less than 0, update to 0
        return(1);
    }
}

int gethit(adventureGame *ag)
{   srand(time(NULL));//seed the random no. generator to current time, so it will not seed only at the time u enter the game, it is always -2 in my case
    int x;
    x=2+rand()% 3;//x range from 2 to 4
    int y;
    y=1+rand()%2;//y ranges from 1 to 2
    if (x>ag->monsterStatusArray[ag->room])
            {ag->xp+=ag->monsterStatusArray[ag->room];}// if lets says hp of monster is 2, but u hit 3, xp will plus 2 instead of 3
    else {ag->xp+=x;}
    ag->monsterStatusArray[ag->room]-=x;//super effective
    ag->HP-=y;//you is hit by enemy from 1-2 dmg
    if(ag->monsterStatusArray[ag->room]<0){ag->monsterStatusArray[ag->room]=0;}//if HP of monster is less than 0, assign to 0.
    printf("You hit the %s by %d\n", ag->monsterArray[ag->room],x);
    printf("The %s hit you by %d\n",ag->monsterArray[ag->room],y);
    return(1);
}

int processAlternate(adventureGame *ag)
{
    char *monster_name=&ag->command[5];//create a pointer pointing to fifth element of command
    int i=0;
    int j=0;//create a counter

    for(i;i<ag->size_monsterarray;i++)//if i is less than total room
    {
        if (strcasecmp(monster_name,ag->monsterArray[i])==0){//if the enemy u type is valid
            j=1;//change j to 1
            if(i==ag->room){//and it is in the current room
                if(ag->monsterStatusArray[i]==0){printf("The %s is dead\n",monster_name);}//check if the enemy is dead or not, if yes print this
                else{processKillMonster(ag);//if no call this function
                return(1);}
            }
        }
    }
    if(j==0){printf("Unknown enemy: %s\n",monster_name);return(1);}//if the j value didnt change, indicates it did not enter the first if statement, thus it means that the enemy is unknown
    else{printf("You cannot use %s here\n",ag->command);return(1);}//if j is not 0, indicating it does enters the first if statement, but didn't enter the second one
}

int processGet(adventureGame *ag) {
    int i=0;
    int j=0;
    char *item = &ag->command[4]; // The fifth character of the line is where the name of the item begins.
    for(i;i<ag->N_artifact;i++){
        if (ag->artifactLoc[i]==-1){j++;}
    }//this for loop is to check if taken artifact is more than max_inventory

    for (i=0;i<ag->N_artifact;i++){ // iterate over each artifact in the list
        if (strcasecmp(item,ag->artifact[i])==0) { // the object being gotten is in the list of objects
            if (ag->artifactLoc[i]==ag->room) {// The artifact is in the current room.
                if (ag->cannotget[ag->room]!=-1){//if no specific enemy is in the room that prevents u picking up artifacts
                        if(j>=ag->max_inventory)//if more than 3 which is defined as max_inventory, it will go back to processCommand and not go into for loop
                        {printf("You reach the maximum amount of carried items, kindly remove items before adding\n");
                            return(1);//return the message above
                        }
                    printf("You pick up the %s\n",item);
                    ag->artifactLoc[i]=-1; // -1 indicates the object is in the player’s inventory.
                    if (ag->artifactcpy[i]!=-2){ag->xp++;ag->artifactcpy[i]=-2;}//check if the player gotten the artifact be4, if yes, xp wont increase
                    printf("Your XP is %d\n",ag->xp);//print out the xp value
                    return(1);
                }
                else {printf("There is %s here, you cannot get %s\n",ag->monsterArray[ag->room],ag->artifact[ag->room]);//if got enemy, print this:
                        return(1);
                }
            }

            else if(ag->artifactLoc[i]!=ag->room) {//if the artifact is not in current room, print this:
                printf("You cannot see any %s here\n",item);
                return(1);}

        }
    }
    printf("Invalid item\n");//if the item name is not in ag->artifact, print this:
    return(1);
}


void printInventory(adventureGame *ag) {
    int i=0,j=0;
    printf("You are carrying:\n");
    for (i=0,j=0;i<ag->N_artifact;i++) { // iterate over each artifact in the list
        if (ag->artifactLoc[i]==-1) {printf("%2d. %s\n",j+=1,ag->artifact[i]);}
    }
    if (j==0) printf("Nothing\n");
}

int processDrop(adventureGame *ag) {
    char *item = &ag->command[5]; // The fifth character of the line is where the name of the item begins.
    for (int i=0;i<ag->N_artifact;i++) { // iterate over each artifact in the list
        if (strcasecmp(item,ag->artifact[i])==0) { // the object being gotten is in the list of objects
            if (ag->artifactLoc[i]==-1) { // if the artifact is being gotten
                    if(ag->cannotget[ag->room]==0){
                        printf("You drop the %s\n",item);
                        ag->artifactLoc[i]=ag->room; // change artifactLoc[] to player's current room
                        return(1);//return above messgaes and lines
                    }
                    else{printf("You cannot drop %s here as have %s in this room\n",item,ag->monsterArray[ag->room]);
                        return(1);}//return the above message
            }
            else {
                printf("You don't have %s to drop\n",item);//if the artifact is not being gotten
                return(1);//return the above message
            }
        }
    }
    printf("Invalid artifact name\n");//if artifact name is not valid
    return(1);//return the above messgae
}

void processHelp(adventureGame *ag){//print put commands
        printf("________________________________________________________________________________________________________________________\n");
        printf("Command                                                     Example(s)\n");
        printf("________________________________________________________________________________________________________________________\n");
        printf("Movement commands                                           north, n, south, s, east, e, west, w\n");
        printf("Look command                                                look,l\n");
        printf("Fight commands                                              killMonster,killmonster,km\n");
        printf("Alternate                                                   kill zombie, kill werewolf, kill dragon\n");
        printf("Get commands                                                get diamond cross, get sword, get Sword, get elixir\n");
        printf("Drop commands                                               drop copper key, drop food, drop golden chalice.\n");
        printf("Inventory command                                           inventory, i: list what the player is carrying\n");
        printf("Healing commands                                            eat food, drink elixir, use medpack\n");
        printf("Unlocking door                                              unlock door\n");
        printf("Your status(HP, XP, Location)                               info\n");
        printf("Rules of the game                                           rules\n");
        printf("Exit game                                                   exit\n");
        printf("________________________________________________________________________________________________________________________\n");
}

int processHealth(adventureGame*ag)
{int afterused=0;//create a variable named afterused
    for(int i=0;i<ag->N_artifact;i++){
        if(ag->artifactLoc[i]==-1){
            if((strcasecmp(ag->command,"eat food")==0)&&(strcasecmp(ag->artifact[i],"Food")==0)){
               ag->HP+=5;
               printf("You've consume %s, you obtained +5 HP\n",ag->artifact[i]);
               if(ag->HP<12){printf("Your HP now is %d\n",ag->HP);}
               ag->artifactLoc[i]=-2;//reassign the artifact status to be -2 in artifactLoc, meaning it's invalid
               afterused=1;//reassign afterused=1
               }
            if((strcasecmp(ag->command,"drink elixir")==0)&&(strcasecmp(ag->artifact[i],"Elixir")==0)){
               ag->HP+=10;
               printf("You've consume %s, you obtained +10 HP\n",ag->artifact[i]);
               if(ag->HP<12){printf("Your HP now is %d\n",ag->HP);}
               ag->artifactLoc[i]=-2;//assign it to be invalid as used before
               afterused=1;
                }
            if((strcasecmp(ag->command,"use medpack")==0)&&(strcasecmp(ag->artifact[i],"Medpack")==0)){
               ag->HP+=10;
               printf("You've used %s, you obtained +10 HP\n",ag->artifact[i]);
               if(ag->HP<12){printf("Your HP now is %d\n",ag->HP);}
               ag->artifactLoc[i]=-2;//assign it to be invalid as used before
               afterused=1;
               }
            if (ag->HP>=12)
            {ag->HP=12;printf("Your HP reached maximum,%d HP\n",ag->HP);break;}//if player HP is more than 12, reassign to 12, break is used to print the message once
        }
    }
    if (afterused==0){processNotGet(ag);}//if did not go into either if statement above, call the function
    return(1);
}

// if the items called is not in inventory, eg: drink elixir or unlock door, it will prompt out you dont have items
int processNotGet(adventureGame *ag)
{
    int found=0;
    for (int i=0;i<ag->N_artifact;i++)
        {if (ag->artifactLoc[i]==-1)
            {found=1;}//if the artifact is in inventory, assign found as 1
        }
    if (found==0){printf("You cannot use %s as you don't have the item\n",ag->command);return(1);}//if cannot find, print this
}

//process info let's you know player's condition
void processInfo(adventureGame *ag)
{
    printf("You are in room no.%d, %s.\n",ag->room,ag->roomArray[ag->room]);
    printf("Your HP is %d\n",ag->HP);
    printf("Your XP is %d\n",ag->xp);
    int deadMonsters=0; // Counter to keep track of dead monsters

    for (int i=0;i<ag->size_monsterarray;i++)//iterate size_monsterarray times
        {if (ag->monsterStatusArray[i]==0) {
            if (deadMonsters==0) {printf("Below are the dead monsters:\n");}//if the monster is dead, print
            printf("%d. %s\n",deadMonsters+=1,ag->monsterArray[i]);}//reassign dead monster to be 1
        }
    if (deadMonsters==0) {printf("You have not killed any enemies\n");}// if did not go into the if statement above, print this:
}

void processXP(adventureGame *ag)
{   printf("________________________________________________________________________________________________________________________\n");
    printf("                                                 You are in: ");
    if(ag->xp<25){printf("Failure grade, play again\n");}//print out the range
    if(ag->xp<=30&&ag->xp>=25){printf("Grade 3\n");}
    if(ag->xp<=50&&ag->xp>30){printf("Grade 2\n");}
    if(ag->xp<=60&&ag->xp>50){printf("Grade 1\n");}
    if(ag->xp==60){printf("Highest Score!!\n");}
    printf("________________________________________________________________________________________________________________________\n");
}

int processWin(adventureGame *ag) {
    replaceNewLine(ag);//remove any \n
    for (int i=0;i<ag->N_artifact;i++)
    if ((strcasecmp(ag->artifact[i],"Golden Chalice")==0)&&(ag->room==0)&&(ag->artifactLoc[i]==-1)) {//if golden chalice is taken n player is in room 0
            printf("________________________________________________________________________________________________________________________\n");
            printf("                                       Congratulations! You have won the game!\n");//print this
            printf("________________________________________________________________________________________________________________________\n");
            processInfo(ag);//tell u the score
            processXP(ag);//tell u the range u r in
            exit(0); // exit 0 to signal the game has been won
    }
}

void processrules(adventureGame *ag)
{
    printf("________________________________________________________________________________________________________________________\n");
    printf("                                               RULES of ADVENTURE GAME\n");
    printf("________________________________________________________________________________________________________________________\n");
    printf("You are assigned with 12 HP, once reaches 0, you lose\n");
    printf("Highest XP score obtainable is 60, get items +1 while kill enemy +XP=Enemy HP\n");
    printf("To win, bring Golden Chalice to the main hall \n");
    printf("Sword is super effective to Zombie, Monster, Lizard-man and Dragon,\n");
    printf("while is less effective to Bride-of-Dracula and Dracula\n");
    printf("Silver spear is super effective to werewolf\n");
    printf("Diamond cross is super effective to Bride-of-Dracula and Dracula\n");
    printf("If you have both sword and diamond cross in inventory, you will deal more dmg\n");
    printf("________________________________________________________________________________________________________________________\n");
}







