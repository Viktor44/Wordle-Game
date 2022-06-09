#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <processenv.h>

//veklost jedneho slova
#define SIZE 5
//pocet slova
#define NUMBER_OF_WORDS 30


//kolko krat vyskúsal hrace jeden slovo
int tries = 0;
//slová z ktorého vybere program jeden náhodne (30 slovo)
char word_pool[NUMBER_OF_WORDS][SIZE+1] = { "abort", "mouth", "share", "sound","hotel","force","month","point","radio","image","plant","entry","woman",
                                            "earth","study","thing","money","court","power","judge","nurse","anger","unity","reply","adult","track",
                                            "brain","train","break","plane" };
//vsteky tie slova ktoré hrác uz vyskúsal
char word_tries[6][SIZE];
//slovo čo vybral program náhodne z word_pool
char word[SIZE + 1];



//funkcia ktorá vygeneruje jedno císlo od 0 do 29
int generator() {
    time_t t1;
    srand((unsigned)time(&t1));
    int r = rand(); // assign the rand() function to random variable.
    r = r % 30;
    return r;
}

void reset() {
    printf("\033[0m");
}


void green() {
    printf("\033[32m");
}

void yellow() {
    printf("\033[33m");
}

// funkcia ktorý vykresly stav hry, keď hráč vyhral hru tak funkcia vráti 1 (return 1;)
int draw() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int letters = 0;
    int win = 0;
    printf("*********************\n");
    for (int i = 0; i < 6; i++) {
        if (i >= tries) {
            printf("|   |   |   |   |   |\n");
            printf("*********************\n");
        }
        else {  //ked hrac uz vyskusal nejaké slova tak najprv ich vypíšem na plochu
            printf("|");
            for (int l = 0; l < SIZE; l++) {
                if (word_tries[i][l] == word[l]) {
                    SetConsoleTextAttribute(h, 1);                             // ked písmeno je na dobrom mieste tak pismeno bude zelený
                    letters++;
                    printf(" %c ", word_tries[i][l]);
                    SetConsoleTextAttribute(h, 7);
                    printf("|");
                    continue;
                }
                for (int k = 0; k < SIZE; k++) {
                    if (word_tries[i][l] == word[k]) {
                        SetConsoleTextAttribute(h, 6);             // ked pismeno nie je na dobrom mieste ale je v slove na inom misete
                        break;                // tak bude zltý
                    }
                }
                printf(" %c ", word_tries[i][l]);
                SetConsoleTextAttribute(h, 7);
                printf("|");

            }
            printf("\n");
            printf("*********************\n");

        }
        if (letters == 5)
            win = 1;
        else
            letters = 0;
    }
    if (win == 1)
        return 1;

    return 0;
}

int game(){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


    for (int i = 0; i < 6; i++) {
        word_tries[i][0] = '0';
    }
    //na zaciatku program vypíše pravidlá hry
    printf("Try and guess the word in 6 moves, this word has 5 letters\n\n");

    SetConsoleTextAttribute(h, 1);
    printf("Blue");
    SetConsoleTextAttribute(h, 7);

    printf(" -  right letter in right place\n");

    SetConsoleTextAttribute(h, 6);
    printf("Yellow");
    SetConsoleTextAttribute(h, 7);

    printf(" - right letter in wrong place\n");

    printf("White - there is no letter like this in the word\n\n");

    draw();

    strcpy(word, word_pool[generator()]);             //tuto vyberem jedno slovo náhodne
    word[5] = '\0';


    int n = 0;
    int game;
    while (1 > 0) {
        char str[10];
        //hrac zada jedno slovo kore ma 5 pisem
        if (tries > 0) {
            printf("Try again: ");
            scanf("%s", str);
            printf("\n");
            tries++;
        }
        else {
            printf("Write a word with 5 letter: ");
            scanf("%s", str);
            printf("\n");
            tries++;
        }
        //ked slovo ma menej alebo viac pisem ako 5 tak hrac musi zadat slovo este raz
        if (strlen(str) != 5) {
            printf("The word must have 5 letters !!!\n");
            tries--;
            continue;
        }
        // pridam slovo str do word_tries
        for (int i = 0; i < 5; i++) {
            word_tries[n][i] = str[i];
        }

        n++;
        game = draw();
        if (game == 1) {           //ked funcia draw vraty 1 tak hra sa skonci a hrac vyhral
            printf("GOOD JOB, YOU WON !!!\n");

            printf("The word was: %s\n", word);
            return 0;
        }


        if (tries == 6) {         //ked harc uz isiel 6 krat tak hra sa skonci a hrac prehral
            printf("GAME OVER !!!\n");

            printf("The word was: %s\n", word);
            return 1;
        }


    }
    return 0;
}

int main() {
    char c;
    while(1>0){

       game();
       printf("\nDo you want to play again?\n");
       printf("Type 'y' for yes or 'n' for no: ");
       getchar();
       scanf("%c",&c);
       if (c == 'y' || c == 'Y'){
           tries = 0;
           for (int i = 0;i<6;i++){
               memset(word_tries[i],NULL,SIZE);
           }
           memset(word,NULL,SIZE);
           continue;
       }

       if (c == 'n' || c == 'N')
           break;
   }
    return 0;
}
