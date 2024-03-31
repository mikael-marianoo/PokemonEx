/*************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and 
applying the concepts learned. I have constructed the functions and their respective algorithms 
and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I 
further certify that I have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons.
 
 <Mariano, Jean Mikael V.>, DLSU ID# <12193291>
*************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>


struct game_state
{
    int PLAYER_GEM;         //Shows current amount of the player
    int StrikeOwn;          //Shows the current Owned of STRIKE Synch Pairs
    int TechOwn;            //Shows the current Owned of TECH Synch Pairs
    int SupportOwn;         //Shows the current Owned of SUPPORT Synch Pairs
    int EnemyHealth;        //Shows the current Health of the Enemy
    int STKhealth;          //Shows the current Health of your Strike Synch Pairs
    int TEChealth;          //Shows the current Health of your Tech Synch Pairs
    int SUPhealth;          //Shows the current Health of your Support Synch Pairs
    int Floor;              //Shows the current Floor
    int SynchPair;          //Choice For Synch Pair Who Will Attack
    int BossHealthOne;      //Shows the current health of Boss Type 1
    int BossHealthTwo;      //Shows the current health of Boss Type 2
    int BossHealthThree;    //Shows the current health of Boss Type 3
};


//Displays the lines 
void Lines()
{
    printf("\n\n----------------------------------------------------------------------------\n\n");
}


//Displays introduction
void Introduction()
{
    printf("%40s", "WELCOME TO POKEMON EXTRAORDINARY \n");  
    printf("\n\n%36s", "Press Any Key to Continue...");
}


//Displays the enemy image *optional
void Image()
{
                printf("\t\t-------------------\n");
                printf("\t\t|     _      _    |\n");
                printf("\t\t|    |_|    |_|   |\n");
                printf("\t\t|    | |____| |   |\n");
                printf("\t\t|   |' 0    0 '|  |\n");
                printf("\t\t|   '.O______O.'  |\n");
                printf("\t\t|     | |  | |    |\n");
                printf("\t\t------ ENEMY ------\n");
}


//Heals randomise from 8 to 15
int RandHeal()
{
   return rand() % (8 + 1) + 7;
}


//Deals a randomised 10 to 20 DAMAGE on an opposing sync pair.
int RandStrike()
{
   return rand() % (10+ 1) + 10;
}


//Has a 20% chance of making an opposing sync pair FLINCH, This generates random number from 1 - 5 therefore it is 20% chance
int RandFlinch()
{
    return  (rand() % 5) + 1;
}


//Shows the Current Amount of Synch Pairs
int Inventory(struct game_state *pgs)
{
    printf("\n\t\t      Inventory\n");
    printf("-------------------------------------------------------\n\n");
    printf("+-----------------------------------------------------+\n");
    printf("|\t\t [SYNCH PAIRS]\t\t\t      |\n"); 
    printf("| This Shows Your Current Amount of your Synch Pairs. |\n");
    printf("+-----------------------------------------------------+\n");
    printf("| [STRIKE]\t[TECH]\t    [SUPPORT] \t\t      |\n");
    printf("|    %d      \t  %d\t\t%d\t\t      |\n", pgs->StrikeOwn, pgs->TechOwn, pgs->SupportOwn);
    printf("+-----------------------------------------------------+\n\n");
    printf("[GEMS]: %d\n\n", pgs->PLAYER_GEM);
    getch();
}


//You can Buy Synch Pairs Here
int Shop(struct game_state *pgs)
{
    int nBuy = 0;
    do
    {
        do
        {   
        printf("\n\t\t\t\tWelcome To The Shop\n");
        printf("\nChoose One Type of Synch Pairs to Buy!!");
        printf("\n\t\t\t[SYNCH PAIRS]\n\n");
        printf("\t+--------------------------+\n");
        printf("\t| ITEM\t\t| PRICE\t   |\n");
        printf("\t+--------------------------+\n");
        printf("[1]\t| STRIKE\t|  200 \t   |\n");
        printf("[2]\t| TECH\t\t|  200 \t   |\n");
        printf("[3]\t| SUPPORT\t|  200\t   |\n");
        printf("\t+--------------------------+\n");
        printf("[0]\t  Exit");
        printf("\n\n[GEMS]: %d\n", pgs->PLAYER_GEM);
        if (nBuy > 3 || nBuy < 0)
            {
                printf("[SYSTEM MESSAGE] PLEASE INPUT A VALID NUMBER!!!\n");
            }
        printf("[INPUT]: ");
        scanf("%d", &nBuy);
        }

        while (nBuy > 3 || nBuy < 0);

            switch(nBuy)
            {
                case 1:
                if (pgs->PLAYER_GEM >= 200)
                {
                    pgs->PLAYER_GEM -= 200;
                    pgs->StrikeOwn += 1;
                    printf("You Succesfully bought STRIKE Type Synch Pairs.\n\n");
                    getch();
                }
                else
                {
                    printf("[SYSTEM MESSAGE]: Not enough coins.\n");
                    getch();
                }
                break;

                case 2:
                if (pgs->PLAYER_GEM >= 200)
                {
                    pgs->PLAYER_GEM -= 200;
                    pgs->TechOwn += 1;
                    printf("You Succesfully bought TECH Type Synch Pairs.");
                    getch();
                }
                else
                {
                    printf("[SYSTEM MESSAGE]: Not enough coins.\n");
                    getch();
                }
                break;

                case 3:
                if (pgs->PLAYER_GEM >= 200)
                {
                    pgs->PLAYER_GEM -= 200;
                    pgs->SupportOwn += 1;
                    printf("You Succesfully bought SUPPORT Type Synch Pairs.");
                    getch();
                }
                else
                {
                    printf("[SYSTEM MESSAGE]: Not enough coins.\n");
                    getch();
                }
                break;
            }
    } while (nBuy != 0);
}


//Function to see the Floor Level, Enemy Health and What attack will player do
int BattleUI(struct game_state *pgs)
{
    do
    {
        printf("FLOOR %d\n\n", pgs->Floor);
        Image();
        printf("\n\t\t    Health: %d\n\n", pgs->EnemyHealth);
        printf("       [1]                   [2]                    [3]                 [4]              [0]\n");
        printf("  STRIKE HEALTH           TEC HEALTH           SUPPORT HEALTH           SKIP          SURRENDER\n");
        printf("        %d                  %d                    %d\n\n",pgs->STKhealth,pgs->TEChealth,pgs->SUPhealth);
        printf("[INPUT A SYNCH PAIR]: ");
        scanf("%d", &pgs->SynchPair);
        if (pgs->SynchPair > 4 || pgs->SynchPair < 0)
        {
            printf("\n\n[SYSTEM ERROR] PLEASE INPUT A VALID NUMBER!!!\n\n\n");
        }
        
    }
    while (pgs->SynchPair > 4 || pgs->SynchPair < 0);
}


//BattleUI for Type One Boss
int BattleOneUI(struct game_state *pgs)
{
    do
    {
        printf("FLOOR %d\n\n", pgs->Floor);
        Image();
        printf("\n\t\t    Health: %d\n\n", pgs->BossHealthOne);
        printf("       [1]                   [2]                    [3]                 [4]              [0]\n");
        printf("  STRIKE HEALTH           TEC HEALTH           SUPPORT HEALTH           SKIP          SURRENDER\n");
        printf("        %d                  %d                    %d\n\n",pgs->STKhealth,pgs->TEChealth,pgs->SUPhealth);
        printf("[INPUT A SYNCH PAIR]: ");
        scanf("%d", &pgs->SynchPair);
        if (pgs->SynchPair > 4 || pgs->SynchPair < 0)
        {
            printf("\n\n[SYSTEM ERROR] PLEASE INPUT A VALID NUMBER!!!\n\n\n");
        }
        
    }
    while (pgs->SynchPair > 4 || pgs->SynchPair < 0);
}


////BattleUI for Type Two Boss
int BattleTwoUI(struct game_state *pgs)
{
    do
    {
        printf("FLOOR %d\n\n", pgs->Floor);
        Image();
        printf("\n\t\t    Health: %d\n\n", pgs->BossHealthTwo);
        printf("       [1]                   [2]                    [3]                 [4]              [0]\n");
        printf("  STRIKE HEALTH           TEC HEALTH           SUPPORT HEALTH           SKIP          SURRENDER\n");
        printf("        %d                  %d                    %d\n\n",pgs->STKhealth,pgs->TEChealth,pgs->SUPhealth);
        printf("[INPUT A SYNCH PAIR]: ");
        scanf("%d", &pgs->SynchPair);
        if (pgs->SynchPair > 4 || pgs->SynchPair < 0)
        {
            printf("\n\n[SYSTEM ERROR] PLEASE INPUT A VALID NUMBER!!!\n\n\n");
        }
        
    }
    while (pgs->SynchPair > 4 || pgs->SynchPair < 0);
}


////BattleUI for Type Three Boss
int BattleThreeUI(struct game_state *pgs)
{
    do
    {
        printf("FLOOR %d\n\n", pgs->Floor);
        Image();
        printf("\n\t\t    Health: %d\n\n", pgs->BossHealthThree);
        printf("       [1]                   [2]                    [3]                 [4]              [0]\n");
        printf("  STRIKE HEALTH           TEC HEALTH           SUPPORT HEALTH           SKIP          SURRENDER\n");
        printf("        %d                  %d                    %d\n\n",pgs->STKhealth,pgs->TEChealth,pgs->SUPhealth);
        printf("[INPUT A SYNCH PAIR]: ");
        scanf("%d", &pgs->SynchPair);
        if (pgs->SynchPair > 4 || pgs->SynchPair < 0)
        {
            printf("\n\n[SYSTEM ERROR] PLEASE INPUT A VALID NUMBER!!!\n\n\n");
        }
        
    }
    while (pgs->SynchPair > 4 || pgs->SynchPair < 0);
}

//Function for GameOver
int GameOver(struct game_state *pgs)
{
if (pgs->StrikeOwn <= 0 && pgs->TechOwn <= 0 && pgs->SupportOwn <= 0)
    {
        printf("\tGAMEOVER");
        printf("You Lose.");
        return 0;
        _Exit(0);
    }    
    return 1;
}


//Functions for Random if Enemy will attack or heal or flinch
int nonBossBattleUI(struct game_state *pgs)
{
    int random;
    int Random = Random = (rand() % (3 - 1 + 1)) + 1;

    switch(Random)
    {
        case 1:
        switch(pgs->SynchPair)
        {
            case 1:
            case 4:
                if (pgs->STKhealth >= 1)
                    {
                        pgs->STKhealth -= RandStrike();
                        printf("The Enemy Attacked Your Strike Pair.\n");
                        getch();
                        if (pgs->STKhealth <= 0)
                        {
                            pgs->StrikeOwn -= 1;
                            printf("You lost 1 Strike Pair.\n");
                            pgs->STKhealth -= pgs->STKhealth;
                            pgs->STKhealth += 100;
                            getch();
                        }
                    }
                break;
            case 2:
                if (pgs->TEChealth >= 1)
                {
                    pgs->TEChealth -= RandStrike();
                    printf("The Enemy Attacked Your Tech Pair.\n");
                    getch();
                    if (pgs->TEChealth <= 0)
                    {
                        pgs->TechOwn -= 1;
                        printf("You lost 1 Tech Pair.\n");
                        pgs->TechOwn -= pgs->TechOwn;
                        pgs->TEChealth += 100;
                        getch();
                    }
                }   
                break;
            case 3:
                if(pgs->SUPhealth >= 1)
                {
                    pgs->SUPhealth -= RandStrike();
                    printf("The Enemy Attacked Your Support Pair.\n");
                    getch();
                    if (pgs->SUPhealth <= 0)
                    {
                        pgs->SupportOwn -= 1;
                        printf("You lost 1 Support Pair.\n");
                        pgs->SupportOwn -= pgs->SupportOwn;
                        pgs->SUPhealth += 100;
                        getch();
                    }
                }
                break;
        }
        break;
        case 2:
        printf("Enemy uses TEC to ATTACK and Your Synch Pair ");
        random = RandFlinch();
        if (random == 1)
            {
                printf("Flinched.\n");
            }
            else if (random != 1)
            {
                printf("does not Flinch.\n");
            }
        break;
        case 3:
        if (pgs->EnemyHealth <= 100)
        pgs->EnemyHealth += RandHeal();
        printf("Enemy HEALS its own HP\n");
        break;
    }
}


//Functions for non Boss Battle
int nonBossBattle(struct game_state *pgs)
{
    getch();
    printf("\nIt is the Enemy Turn.\n");
    getch();
    nonBossBattleUI(pgs);
    
    GameOver(pgs);
}


int PlayGame(); //Called PlayGame() So I can call the function even na nasa baba siya ng function Battle()
int BossBattle(); //Called BossBattle() So I can call the function even na nasa baba siya ng function Battle()
//Player Battle Menu
int Battle(struct game_state *pgs)
{
    int random;
    char cChoice;
    BattleUI(pgs);
    switch(pgs->SynchPair)
        {
        case 1:
            pgs->EnemyHealth -= RandStrike()    /*rand()%(150-100+1)+100*/;
            printf("STK ATTACKED Enemy Synch Pair");
            break;

        case 2:
            printf("TEC ATTACK and The Enemy ");
            random = RandFlinch();
            if (random == 1)
                {
                    printf("Flinch.\n");
                }
                else if (random != 1)
                {
                    printf("does not Flinch.\n");
                }
            break;

        case 3:
            if (pgs->STKhealth <= 100)
            pgs->STKhealth += RandHeal();
            if (pgs->TEChealth <= 100)
            pgs->TEChealth += RandHeal();
            printf("SUP HEALS HP in your STRIKE and TECH Pairs\n");
            break;

        case 4:
            printf("You skipped a turn.\n");
            break;

        case 0:
            printf("You Surrender!!!\n");
            printf("Would you like to play again?\n");
            printf("[If yes press Y and N if No]: ");
            scanf(" %c", &cChoice);
            switch(cChoice)
                {
                    case 'y':
                    case 'Y':
                    system("pause");
                    return PlayGame();
                    break;
                    case 'n':
                    case 'N':
                    printf("\n\nThank You For Playing!!!!");
                    _Exit(0);
                    return 0;
                    break; 
                }
            break;
        }

        if (pgs->Floor <= 20 && pgs->Floor != (pgs->Floor %5 == 0))
        {
            nonBossBattle(pgs);
        }

        else if (pgs->Floor %5 == 0 && pgs->Floor <= 20)
        {
            BossBattle(pgs);
        }
}


//Function For Boss Battle Type One UI
int BossBattleTypeOne(struct game_state *pgs)
{
    int random;
    int Random = Random = (rand() % (3 - 1 + 1)) + 1;
    char cChoice;

    BattleOneUI(pgs);

    switch(pgs->SynchPair)
        {
        case 1:
            pgs->BossHealthOne -= RandStrike();
            printf("STK ATTACKED The Elite Four's Synch Pair.\n");
            break;

        case 2:
            printf("TEC ATTACK and The Elite Four's Synch Pair ");
            random = RandFlinch();
            if (random == 1)
                {
                    printf("Flinch.\n");
                }
                else if (random != 1)
                {
                    printf("does not Flinch.\n");
                }
            break;

        case 3:
            if (pgs->STKhealth <= 100)
            pgs->STKhealth += RandHeal();
            if (pgs->TEChealth <= 100)
            pgs->TEChealth += RandHeal();
            printf("SUP HEALS HP in your STRIKE and TECH Pairs\n");
            break;

        case 4:
            printf("You skipped a turn.\n");
            break;

        case 0:
            printf("You Surrender!!!\n");
            printf("Would you like to play again?\n");
            printf("[If yes press Y and N if No]: ");
            scanf(" %c", &cChoice);
            switch(cChoice)
                {
                    case 'y':
                    case 'Y':
                    system("pause");
                    return PlayGame();
                    break;
                    case 'n':
                    case 'N':
                    printf("\n\nThank You For Playing!!!!");
                    _Exit(0);
                    return 0;
                    break; 
                }
            break;
        }

        printf("It is The Elite Four's Synch Pair Turn.\n");
        getch();

    switch(Random)
    {
        case 1:
        switch(pgs->SynchPair)
        {
            case 1:
            case 4:
                if (pgs->STKhealth >= 1)
                    {
                        pgs->STKhealth -= rand()%(30-15+1)+15;
                        printf("The Elite Four's Synch Pair Attacked Your Strike Pair.\n");
                        getch();
                        if (pgs->STKhealth <= 0)
                        {
                            pgs->StrikeOwn -= 1;
                            printf("You lost 1 Strike Pair.\n");
                            pgs->STKhealth -= pgs->STKhealth;
                            pgs->STKhealth += 100;
                            getch();
                        }
                    }
                break;

            case 2:
                if (pgs->TEChealth >= 1)
                {
                    pgs->TEChealth -= rand()%(30-15+1)+15;
                    printf("The Elite Four's Synch Pair Attacked Your Tech Pair.\n");
                    getch();
                    if (pgs->TEChealth <= 0)
                    {
                        pgs->TechOwn -= 1;
                        printf("You lost 1 Tech Pair.\n");
                        pgs->TechOwn -= pgs->TechOwn;
                        pgs->TEChealth += 100;
                        getch();
                    }
                }   
                break;

            case 3:
                if(pgs->SUPhealth >= 1)
                {
                    pgs->SUPhealth -= rand()%(30-15+1)+15;
                    printf("The Elite Four's Synch Pair Attacked Your Support Pair.\n");
                    getch();
                    if (pgs->SUPhealth <= 0)
                    {
                        pgs->SupportOwn -= 1;
                        printf("You lost 1 Support Pair.\n");
                        pgs->SupportOwn -= pgs->SupportOwn;
                        pgs->SUPhealth += 100;
                        getch();
                    }
                }
                break;

        }
        break;

        case 2:
        printf("The Elite Four's Synch Pair uses TEC to ATTACK and Your Synch Pair ");
        random = rand()%(7-1+1)+1;
        if (random == 1)
            {
                printf("Flinched.\n");
            }
            else if (random != 1)
            {
                printf("does not Flinch.\n");
            }
        break;

        case 3:
        if (pgs->BossHealthOne <= 100)
        pgs->BossHealthOne += RandHeal();
        printf("The Elite Four's Synch Pair HEALS its own HP\n");
        break;
    }
}


//Function For Boss Battle Type Two UI
int BossBattleTypeTwo(struct game_state *pgs)
{
    int random;
    int Random = Random = (rand() % (3 - 1 + 1)) + 1;
    char cChoice;

    BattleTwoUI(pgs);

    switch(pgs->SynchPair)
        {
        case 1:
            pgs->BossHealthTwo -= RandStrike();
            printf("STK ATTACKED Enemy Synch Pair.\n");
            break;

        case 2:
            printf("TEC ATTACK and The Elite Four's Synch Pair ");
            random = RandFlinch();
            if (random == 1)
                {
                    printf("Flinch.\n");
                }
                else if (random != 1)
                {
                    printf("does not Flinch.\n");
                }
            break;

        case 3:
            if (pgs->STKhealth <= 100)
            pgs->STKhealth += RandHeal();
            if (pgs->TEChealth <= 100)
            pgs->TEChealth += RandHeal();
            printf("SUP HEALS HP in your STRIKE and TECH Pairs\n");
            break;

        case 4:
            printf("You skipped a turn.\n");
            break;

        case 0:
            printf("You Surrender!!!\n");
            printf("Would you like to play again?\n");
            printf("[If yes press Y and N if No]: ");
            scanf(" %c", &cChoice);
            switch(cChoice)
                {
                    case 'y':
                    case 'Y':
                    system("pause");
                    return PlayGame();
                    break;
                    case 'n':
                    case 'N':
                    printf("\n\nThank You For Playing!!!!");
                    _Exit(0);
                    return 0;
                    break; 
                }
            break;
        }
        getch();
        printf("It is Elite Four's Synch Pair Turn.\n");
        getch();

    switch(Random)
    {
        case 1:
        switch(pgs->SynchPair)
        {
            case 1:
            case 4:
                if (pgs->STKhealth >= 1)
                    {
                        pgs->STKhealth -= rand()%(25-15+1)+15;
                        printf("The Elite Four's Synch Pair Attacked Your Strike Pair.\n");
                        getch();
                        if (pgs->STKhealth <= 0)
                        {
                            pgs->StrikeOwn -= 1;
                            printf("You lost 1 Strike Pair.\n");
                            pgs->STKhealth -= pgs->STKhealth;
                            pgs->STKhealth += 100;
                            getch();
                        }
                    }
                break;

            case 2:
                if (pgs->TEChealth >= 1)
                {
                    pgs->TEChealth -= rand()%(30-15+1)+15;
                    printf("The Elite Four's Synch Pair Attacked Your Tech Pair.\n");
                    getch();
                    if (pgs->TEChealth <= 0)
                    {
                        pgs->TechOwn -= 1;
                        printf("You lost 1 Tech Pair.\n");
                        pgs->TechOwn -= pgs->TechOwn;
                        pgs->TEChealth += 100;
                        getch();
                    }
                }   
                break;

            case 3:
                if(pgs->SUPhealth >= 1)
                {
                    pgs->SUPhealth -= rand()%(30-15+1)+15;
                    printf("The Elite Four's Synch Pair Attacked Your Support Pair.\n");
                    getch();
                    if (pgs->SUPhealth <= 0)
                    {
                        pgs->SupportOwn -= 1;
                        printf("You lost 1 Support Pair.\n");
                        pgs->SupportOwn -= pgs->SupportOwn;
                        pgs->SUPhealth += 100;
                        getch();
                    }
                }
                break;

        }
        break;

        case 2:
        printf("Enemy uses TEC to ATTACK and Your Synch Pair ");
        random = rand()%(3-1+1)+1;
        if (random == 1)
            {
                printf("Flinched.\n");
            }
            else if (random != 1)
            {
                printf("does not Flinch.\n");
            }
        break;

        case 3:
        if (pgs->BossHealthTwo <= 100)
        pgs->BossHealthTwo += RandHeal();
        printf("The Elite Four's Synch Pair HEALS its own HP\n");
        break;
    }
}


//Function For Boss Battle Type Three UI
int BossBattleTypeThree(struct game_state *pgs)
{
    int random;
    int Random = Random = (rand() % (3 - 1 + 1)) + 1;
    char cChoice;

    BattleThreeUI(pgs);

    switch(pgs->SynchPair)
        {
        case 1:
            pgs->BossHealthThree -= RandStrike();
            printf("STK ATTACKED Elite Four's Synch Pair\n");
            break;

        case 2:
            printf("TEC ATTACK and The Elite Four's Synch Pair ");
            random = RandFlinch();
            if (random == 1)
                {
                    printf("Flinch.\n");
                }
                else if (random != 1)
                {
                    printf("does not Flinch.\n");
                }
            break;

        case 3:
            if (pgs->STKhealth <= 100)
            pgs->STKhealth += RandHeal();
            if (pgs->TEChealth <= 100)
            pgs->TEChealth += RandHeal();
            printf("SUP HEALS HP in your STRIKE and TECH Pairs\n");
            break;

        case 4:
            printf("You skipped a turn.\n");
            break;

        case 0:
            printf("You Surrender!!!\n");
            printf("Would you like to play again?\n");
            printf("[If yes press Y and N if No]: ");
            scanf(" %c", &cChoice);
            switch(cChoice)
                {
                    case 'y':
                    case 'Y':
                    system("pause");
                    return PlayGame();
                    break;
                    case 'n':
                    case 'N':
                    printf("\n\nThank You For Playing!!!!");
                    _Exit(0);
                    return 0;
                    break; 
                }
            break;
        }

        printf("It is Elite Four's Turn.\n");
        getch();

    switch(Random)
    {
        case 1:
        switch(pgs->SynchPair)
        {
            case 1:
            case 4:
                if (pgs->STKhealth >= 1)
                    {
                        pgs->STKhealth -= rand()%(20-10+1)+10;
                        printf("The Elite Four's Synch Pair Attacked Your Strike Pair.\n");
                        getch();
                        if (pgs->STKhealth <= 0)
                        {
                            pgs->StrikeOwn -= 1;
                            printf("You lost 1 Strike Pair.\n");
                            pgs->STKhealth -= pgs->STKhealth;
                            pgs->STKhealth += 100;
                            getch();
                        }
                    }
                break;

            case 2:
                if (pgs->TEChealth >= 1)
                {
                    pgs->TEChealth -= rand()%(20-10+1)+10;
                    printf("The Elite Four's Synch Pair Attacked Your Tech Pair.\n");
                    getch();
                    if (pgs->TEChealth <= 0)
                    {
                        pgs->TechOwn -= 1;
                        printf("You lost 1 Tech Pair.\n");
                        pgs->TechOwn -= pgs->TechOwn;
                        pgs->TEChealth += 100;
                        getch();
                    }
                }   
                break;

            case 3:
                if(pgs->SUPhealth >= 1)
                {
                    pgs->SUPhealth -= rand()%(20-10+1)+10;
                    printf("The Elite Four's Synch Pair Attacked Your Support Pair.\n");
                    getch();
                    if (pgs->SUPhealth <= 0)
                    {
                        pgs->SupportOwn -= 1;
                        printf("You lost 1 Support Pair.\n");
                        pgs->SupportOwn -= pgs->SupportOwn;
                        pgs->SUPhealth += 100;
                        getch();
                    }
                }
                break;

        }
        break;

        case 2:
        printf("The Elite Four's Synch Pair uses TEC to ATTACK and Your Synch Pair ");
        random = rand()%(5-1+1)+1;
        if (random == 1)
            {
                printf("Flinched.\n");
            }
            else if (random != 1)
            {
                printf("does not Flinch.\n");
            }
        break;

        case 3:
        if (pgs->BossHealthThree <= 100)
        pgs->BossHealthThree += RandHeal();
        printf("The Elite Four's Synch Pair HEALS its own HP\n");
        break;
    }
}


//Boss Battle Menu
int BossBattle(struct game_state *pgs)
{

    int BossSelect;
    printf("Please Select One Elite Four That You Want To Challenge.\n\n");
    switch(pgs->Floor)
    {
        case 5:
        printf("   WILL             Karen\n");
        printf("   [1]               [2]\n");
        scanf("%d", &BossSelect);
        switch(BossSelect)
        {
            case 1:
            BossBattleTypeTwo(pgs);
            getch();
            GameOver(pgs);
            break;
            case 2:
            BossBattleTypeTwo(pgs);
            getch();
            GameOver(pgs);
            break;
        }
    break;
    
    case 10:
        printf("   GLACIA            FLINT\n");
        printf("    [1]               [2]\n");
        scanf("%d", &BossSelect);
        switch(BossSelect)
        {
            case 1:
            BossBattleTypeThree(pgs);
            getch();
            GameOver(pgs);
            break;
            case 2:
            BossBattleTypeOne(pgs);
            getch();
            GameOver(pgs);
            break;
        }
    break;

    case 15:
        printf("   GRIMSLEY         SHAUNTAL\n");
        printf("     [1]              [2]\n");
        scanf("%d", &BossSelect);
        switch(BossSelect)
        {
            case 1:
            BossBattleTypeTwo(pgs);
            getch();
            GameOver(pgs);
            break;
            case 2:
            BossBattleTypeThree(pgs);
            getch();
            GameOver(pgs);
            break;
        }
    break;

    case 20:
        printf("   ACEROLA           SIEBOLD\n");
        printf("     [1]              [2]\n");
        scanf("%d", &BossSelect);
        switch(BossSelect)
        {
            case 1:
            BossBattleTypeThree(pgs);
            getch();
            GameOver(pgs);
            break;
            case 2:
            BossBattleTypeOne(pgs);
            getch();
            GameOver(pgs);
            break;
        }
    break;
    }
}


//Function to play the actual game. Battle Normal enemies and boss battles
int BattleVilla(struct game_state *pgs)
{
    printf("Welcome To Battle Villa!!!\n");
    printf("Press any key to continue...");
    getch();
    system ("cls");
    if (pgs->Floor %5 == 0 && pgs->Floor <= 20)
        {
            system("cls");
            printf("FLOOR %d\n\n", pgs->Floor);
            printf("Boss Battle\n\n");
            BossBattle(pgs);
        }
    else if (pgs->Floor <= 20 && pgs->Floor != (pgs->Floor %5 == 0))
        {
            system("cls");
            Battle(pgs);
        }
}


//Will Get A Boss Rewards Based on The Players Input
int EliteFloorRewards(struct game_state *pgs)
{
    int Rewards;
    int RandGems = rand() % (100 + 1) + 900;;
    if (pgs->Floor %5 == 0 && pgs->Floor <= 20)
    {
        {
            printf("\nPlease Select Your Rewards!\n\n");
            printf("  FULL HEAL        500 GEMS         RANDOM GEMS\n");
            printf("     [1]             [2]                 [3]\n\n");
            printf("Input: ");
            scanf("%d", &Rewards);
            switch(Rewards)
            {
                case 1:
                pgs->STKhealth -= pgs->STKhealth;
                pgs->STKhealth += 100;
                pgs->TEChealth -= pgs->TEChealth;
                pgs->TEChealth += 100;
                pgs->SUPhealth -= pgs->SUPhealth;
                pgs->SUPhealth += 100;
                printf("Full heal restores the health of all sync pairs.\n");
                break;
                case 2:
                pgs->PLAYER_GEM += 500;
                printf("500 Gems Has Been Added To Your Gems.\n");
                break;
                case 3:
                pgs->PLAYER_GEM += RandGems;
                printf("%d Has Been Added To Your Gems.\n", RandGems);
                break;
            }
        }
        pgs->Floor++;
    }
}


//Will move the floor to next level and will get reward
int MoveToFloorAndGetReward(struct game_state *pgs)
{
        pgs->Floor++;
        pgs->EnemyHealth = 0;
        pgs->EnemyHealth +=100;
        printf("\n\nYou advanced to next floor.");
        if (pgs->Floor <= 10)
        {
            pgs->PLAYER_GEM +=50;
            printf("\nYou've been rewarded with 50 GEMS.\n");
        }
        else if (pgs->Floor <= 15 && pgs->Floor >= 11)
        {
            pgs->PLAYER_GEM +=80;
            printf("\nYou've been rewarded with 80 GEMS.\n");
        }
        else if (pgs->Floor >=16 && pgs->Floor <=19)
        {
            pgs->PLAYER_GEM +=100;
            printf("\nYou've been rewarded with 100 GEMS.\n");
        }
        else if (pgs->Floor == 20)
        {
            EliteFloorRewards(pgs);
            pgs->PLAYER_GEM +=500;
            printf("\nYou've been rewarded with 500 GEMS.\n");
        }
        getch();
}


//Displays the Main Menu and if the player wants to play or not
int PlayGame()
{
    int nChoice = 0;
    struct game_state gs =
    {
        .PLAYER_GEM = 200,
        .StrikeOwn = 1,
        .TechOwn = 1,
        .SupportOwn = 1,
        .EnemyHealth = 100,
        .STKhealth = 100,
        .TEChealth = 100,
        .SUPhealth = 100,
        .Floor = 1,
        .SynchPair = 0,
        .BossHealthOne = 100,
        .BossHealthTwo = 150,
        .BossHealthThree = 200,
    };

    do
    {
        do
        {
            system("cls");
            printf("\t\t\t\tMAIN MENU\n");
            printf("-----------------------------------------------------------------------\n\n");
            printf("\t[1] Inventory\n");
            printf("\t[2] Battle Villa\n");
            printf("\t[3] Shop\n\n");
            printf("\t[0] Exit\n\n");
            printf("  [GEMS]: %d\n", gs.PLAYER_GEM);
            if (nChoice > 3 || nChoice < 0)
                {
                    printf("[SYSTEM MESSAGE] PLEASE INPUT A VALID NUMBER!!!\n");
                }
            printf("  [INPUT]: ");
            scanf("%d", &nChoice); 
    }

    while (nChoice > 3 || nChoice < 0);

        switch(nChoice)
        {
            case 1:
                Inventory(&gs);
            break;
        
            case 2:
                printf("\nBattle Villa\n");
                BattleVilla(&gs);
                if (gs.EnemyHealth <= 0 || gs.BossHealthOne <=0 || gs.BossHealthTwo <= 0 || gs.BossHealthThree <=0)
                {
                    EliteFloorRewards(&gs);
                    MoveToFloorAndGetReward(&gs);
                }
    
                getch();
            break;

            case 3:
            Shop(&gs);
            break;

            case 0:
            printf("\nThank You for Playing!!!");
            _Exit(0);
            break;
        }
    }
    while (nChoice != 0);
}


int main()
{
    int nInput;
    srand (time(0)); // Initialize random seed

    Lines();
    Introduction();
    Lines();
    getch();
    
    system("cls");

    PlayGame(nInput);
    getch();
    system ("cls");
    return 0;
}