#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "util/print_board.h"
#include "util/scrabble.h"
#define SIZE 15
char game_board[SIZE][SIZE] = {
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};
int calculScor(char string[])
{
    //calcul scor fara bonus pentru un cuvant
    int vec_Puncte[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    //                    A B C D E F G H I J K L M N O P Q  R S T U V W X Y Z
    int score = 0;

    for(int i = 0; string[i]!= '\0'; i++)
           score += vec_Puncte[ string[i] - 'A'];

    return score;
}        

int calculBonus(char string[], char ZZ[], int numarBonus, int directie, int x1, int y1)
{
    //calcularea bonusului pentru un cuvant (nu a scorului total)
    int bonus = 1, B;
    if(numarBonus == 1)
       B = 2;
    else
       B = 3;
    char *p = strstr(string,ZZ);
       
    if( (p != NULL && numarBonus == 1) || (p != NULL && strlen(p) == 2 ) ) 
        {
            if(directie == 0)
            {      //D=0
            for(int i = 0; string[i] != '\0'; i++)
                if(bonus_board[y1][x1 + i] == numarBonus)
                    bonus *= B;
            }
            else
            {    //D=1
            for(int i = 0; string[i] != '\0'; i++)
                if(bonus_board[y1 + i][x1] == numarBonus)
                    bonus *= B;
            }
        }    

    return bonus;    
}

void Adaugare_Cuvant(char string[], int x1, int y1, int D)
{
    //adaugarea unui cuvant pe tabbla de joc
    if(D == 0)
        {
            for(int i = 0; string[i] != '\0'; i++ )
               game_board[y1][x1 + i] = string[i];

        }
        else
        {
            for(int i = 0; string[i] != '\0'; i++ )
               game_board[y1 + i][x1] = string[i];
        }

}

int Insereaza_Cuvant(char word[])
{
    //folosita in taskul 4, incearca sa adauge stringul word
    int efectuat = 0, x1, y1;
    int len = strlen(word);

    for(y1 = 0; y1 < SIZE; y1++)
        for(x1 = 0; x1 < SIZE; x1++)
           if(game_board[y1][x1] == word[0] )
           {
               short ok = 1; //ok - se poate pune pe y1 x1

               //se incearca sa se puna pe directia 0 D=0

               if(x1 + len - 1 > SIZE - 1) //cuvantul va iesi din matrice
                  ok = 0;
               else
                  for(int i = 1; i < len; i++)
                     if(game_board[ y1 ][ x1 + i] != '.')
                     {    
                        ok = 0;
                        break;
                     }
               
                if(ok == 1)//are spatiu necesar
                {
                   Adaugare_Cuvant(word, x1, y1, 0);
                   efectuat = 1;
                   return efectuat;
                }
                ok = 1;

                //se incearca sa se puna pe directia 1 D=1

                if(y1 + len - 1 > SIZE - 1) //cuvantul va iesi din matrice
                  ok = 0;
               else
                  for(int i = 1; i < len; i++)
                      if(game_board[ y1 + i ][ x1] != '.')
                      {    
                          ok = 0;
                          break;
                      }

                if (ok == 1)//are spatiul necesar
                {
                   Adaugare_Cuvant(word, x1, y1, 1);
                   efectuat = 1;
                   return efectuat;
                }    
           }
    //printf("\n");       
    return efectuat;

} 

int Insereaza_Cuvant2(char word[], int *scor_maxim, int *x1, int *y1, int *directie, char XX[],char YY[])
{
    int x2, y2, efectuat = 0;
    int len = strlen(word);

    for(y2 = 0; y2 < SIZE; y2++)
        for(x2 = 0; x2 < SIZE; x2++)
           if(game_board[y2][x2] == word[0] )
           {
               short ok = 1; //ok - se poate pune pe y1 x1

               //se incearca sa se puna pe directia 0 D=0

               if(x2 + len - 1 > SIZE - 1) //cuvantul va iesi din matrice
                  ok = 0;
               else
                  for(int i = 1; i < len; i++)
                     if(game_board[ y2 ][ x2 + i] != '.')
                     {    
                        ok = 0;
                        break;
                     }
               
                if(ok == 1)//are spatiu necesar
                {
                   int scor = calculBonus(word, XX, 1, 0, x2, y2)  *  calculBonus(word, YY, 2, 0, x2, y2) * calculScor(word);
                   if( scor > *scor_maxim)
                   {
                       *scor_maxim = scor;
                       *x1 = x2;
                       *y1 = y2;
                       *directie = 0;
                       efectuat = 1;
                   }
                }
                ok = 1;

                //se incearca sa se puna pe directia 1 D=1

                if(y2 + len - 1 > SIZE - 1) //cuvantul va iesi din matrice
                  ok = 0;
               else
                  for(int i = 1; i < len; i++)
                      if(game_board[ y2 + i ][ x2] != '.')
                      {    
                          ok = 0;
                          break;
                      }

                if (ok == 1)//are spatiul necesar
                {
                   int scor = calculBonus(word, XX, 1, 1, x2, y2)  *  calculBonus(word, YY, 2, 1, x2, y2) * calculScor(word);
                   if( scor > *scor_maxim)
                   {
                       *scor_maxim = scor;
                       *x1 = x2;
                       *y1 = y2;
                       *directie = 1;
                       efectuat = 1;
                   }
                }    
           }
    return efectuat;       
}

void task0()
{
    print_board(game_board);

}

void task1()
{
    char sir[25];
    fgets( sir, 5, stdin);
    short N = atoi(sir);

    while(N!=0)
    {
        N--;
        int x1, y1, D;
        fgets( sir, 24, stdin);

        char *string = strtok(sir," ");
        y1 = atoi(string);
        string = strtok(NULL," ");
        x1 = atoi(string);
        string = strtok(NULL," ");
        D = atoi(string);

        string = strtok(NULL,"\n");

        Adaugare_Cuvant(string, x1, y1, D);

    }
    print_board(game_board);
}

void task2()
{
    char sir[25];
    fgets( sir, 5, stdin);
    short N = atoi(sir);


    int player1 = 0, player2 = 0, who = 1; //who - indica daca joaca player 1 sau player 2
    //player1 = punctajul jucatorului 1
    while(N!=0)
    {
        N--;
        fgets( sir, 24, stdin);

        char *string = strtok(sir," ");
        string = strtok(NULL," ");
        string = strtok(NULL," ");
        string = strtok(NULL,"\n");
        

        if(who == 1)
           player1 += calculScor(string);
        else
           player2 += calculScor(string);
        who = -who;      
    }
    printf("Player 1: %d Points\n",player1);
    printf("Player 2: %d Points\n",player2);

}

void task3()
{
    char sir[25], XX[5], YY[5];
    int player1 = 0, player2 = 0, who = 1;

    fgets( XX, 5, stdin);
    fgets( YY, 5, stdin);
    fgets( sir, 5, stdin);
    short N = atoi(sir);

    XX[2] = '\0';
    YY[2] = '\0';

    while(N!=0)
    {
        N--;
        int x1, y1, D, score = 0;
        fgets( sir, 24, stdin);

        char *string = strtok(sir," ");
        y1 = atoi(string);
        string = strtok(NULL," ");
        x1 = atoi(string);
        string = strtok(NULL," ");
        D = atoi(string);

        string = strtok(NULL,"\n");
        score = calculScor(string);

        score *= calculBonus(string, XX, 1, D, x1, y1) * calculBonus(string, YY, 2, D, x1, y1);

        if(who == 1)
           player1 += score;
        else
           player2 += score;
        who = -who;
    }
    printf("Player 1: %d Points\n",player1);
    printf("Player 2: %d Points\n",player2);
}

void task4()
{
    char sir[25], XX[5], YY[5];
    char used_words[100][25] = {0};

    fgets( XX, 5, stdin);
    fgets( YY, 5, stdin);
    fgets( sir, 5, stdin);
    short N = atoi(sir), i;

    XX[2] = '\0';
    YY[2] = '\0';

    for(i = 1; i <= N; i++)
    {
        
        int x1, y1, D;
        fgets( sir, 24, stdin);

        char *string = strtok(sir," ");
        y1 = atoi(string);
        string = strtok(NULL," ");
        x1 = atoi(string);
        string = strtok(NULL," ");
        D = atoi(string);

        string = strtok(NULL,"\n");
        Adaugare_Cuvant(string, x1, y1, D);

        strcpy(used_words[i], string);  //salveaza cuvintele folosite
    }

    for(i = 0; i <= 100; i++)
    {
        //incerc sa pun cuvantul words[i] daca nu s-a folosit inca
        short repetat = 0, ok;

        for(int j = 1; j <= N; j++)
           if( strcmp( words[i], used_words[j]) == 0 )
              repetat = 1;

        if(repetat == 0)
        {
            ok = Insereaza_Cuvant(words[i]);
        }
        if(ok == 1)
           break; //s-a adaugat cuvantul cu succes
    }
    print_board(game_board);
}

void task5()
{
    char sir[25], XX[5], YY[5];
    char used_words[100][25] = {0};
    int player1 = 0, player2 = 0;

    fgets( XX, 5, stdin);
    fgets( YY, 5, stdin);
    fgets( sir, 5, stdin);
    short N = atoi(sir), i;

    XX[2] = '\0';
    YY[2] = '\0';

    for(i = 1; i <= N; i++)
    {
        
        int x1, y1, D;
        fgets( sir, 24, stdin);

        char *string = strtok(sir," ");
        y1 = atoi(string);
        string = strtok(NULL," ");
        x1 = atoi(string);
        string = strtok(NULL," ");
        D = atoi(string);

        string = strtok(NULL,"\n");
        Adaugare_Cuvant(string, x1, y1, D);

        strcpy(used_words[i], string);  //salveaza cuvintele folosite

        if(i % 2 == 1) //calcularea scorurilor
            player1 += calculBonus(string, XX, 1, D, x1, y1)  *  calculBonus(string, YY, 2, D, x1, y1) * calculScor(string);
        else
            player2 += calculBonus(string, XX, 1, D, x1, y1)  *  calculBonus(string, YY, 2, D, x1, y1) * calculScor(string);
    }
    int scor_maxim = -1, x1 = -1, y1 = -1, D = -1;
    int indice = -1;
    // word[indice] = cuvantul cu scorul maxim pus pe pozitia y1 x1 si directia D 

    for(i = 0; i <= 100; i++)
    {
       short repetat = 0, ok;

        for(int j = 1; j <= N; j++)
           if( strcmp( words[i], used_words[j]) == 0 )
              repetat = 1;

        if(repetat == 0)
        {
            ok = Insereaza_Cuvant2(words[i], &scor_maxim, &x1, &y1, &D, XX, YY);
            if(ok == 1)
               indice = i;
        }
        
    }
    if(scor_maxim >= player1 - player2)
    {
        Adaugare_Cuvant(words[indice], x1, y1, D);
        print_board(game_board);
    }
    else
    {
        printf("Fail!");
    }
}

int main()
{
    char sir[15];
    fgets( sir, 5, stdin);
    int num = sir[0] - '0';

    if(num == 0)
        task0();
    else if(num == 1)
            task1();
         else if(num == 2)
                task2();
               else if(num == 3)
                      task3();
                    else if(num == 4)
                            task4();
                         else
                            task5();
            
    return 0;
}