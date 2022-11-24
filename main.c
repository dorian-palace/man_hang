#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define MAXNUMWORDS 2000
#define MAXLENGTHWORDS 60

int main()
{   
    //Lecture du fichier contenant les mots.
    char guessWords[MAXNUMWORDS][MAXLENGTHWORDS];
    int reading = 0;
    
    FILE *ptr;
    char * filename = "words.txt";
    
    ptr = fopen(filename,"r");

    char input[60];
    int nbReading;

    while(fgets(input, 60, ptr)){
        sscanf(input,"%s", guessWords[reading]);
        reading++;
    }

    nbReading = reading;

    fclose(ptr);

    //Mot aléatoire.
    srand(time(NULL));

    int randomIndex = rand() % 6;

    int numLives = 5;
    int numCorrect = 0;
    int oldCorrect = 0;

    int lengthOfWord = strlen(guessWords[randomIndex]);


    int letterGuessed[10] = { 0,0,0,0,0,0,0,0,0,0};

    int quit = 0;

    int loopIndex = 0;

    char guess[nbReading];
    char letterEntered;

    char * newWord;
    int choiceToCreateWord = 0;
    newWord = malloc(sizeof(char *));

    // printf débug
    // printf("GuessWord:%s randomIndex:%d LengthOfWord: %d\n\n", 
    // guessWords[randomIndex], 
    // randomIndex,
    // lengthOfWord
    // );
   
    //Game boucle
    while (numCorrect < lengthOfWord){

        printf("\n");
        for (loopIndex = 0; loopIndex < lengthOfWord; loopIndex++){

            if(letterGuessed[loopIndex] == 1){
                printf("%c",guessWords[randomIndex][loopIndex]);
            } else {
                printf("-");
            }
        }
        printf("\n");

        printf("Nombre correct jusqu'à présent: %d\n",numCorrect);
        printf("Entrer une lettre a trouver\n");
        fgets(guess, nbReading, stdin);

        if(strncmp(guess, "quit", 4) == 0){
            quit = 1;
            break;
        }

        letterEntered = guess[0];
        printf("letterGuessed: %c",letterEntered);

        oldCorrect = numCorrect;

        for (loopIndex = 0; loopIndex < lengthOfWord; loopIndex++){

            if(letterGuessed[loopIndex] == 1){
                continue;
            }

            if (letterEntered == guessWords[randomIndex][loopIndex]){
                letterGuessed[loopIndex] = 1;
                numCorrect++;
            }
        }

        if (oldCorrect == numCorrect){
            numLives--;
            printf("Désoler mauvaise réponse\n");

            if (numLives == 0){
                break;
            }

        } else {
            printf("\nBonne réponse");
        }

    }

    if (quit == 1){
        printf("Le joueur a quitté\n");
    } else if ( numLives == 0){
        printf("\nVous avez perdu le mot est : %s\n", guessWords[randomIndex]);
    } else {
        printf("\nFelicitation vous avez gagner :) !");
    }
    
    // Àjout de nouveaux mots au jeu du pendu ou bien fin de partie.
    printf("\n---------------------------------\n");
    printf("Désirez-vous ajouter de nouveaux mots au jeu ? si oui tapez 1 sinon 0\n");
    scanf("%d", &choiceToCreateWord);

    if (choiceToCreateWord == 1){
        printf("Taper le mot que vous désirez ajouter au pendu ! :)\n");
        scanf("%s", newWord);

        ptr = fopen(filename, "a+");

        if (ptr){
            fprintf(ptr, "\n%s", newWord);
            printf("%s a été ajouter au jeu !\n", newWord);
            fclose(ptr);
        }

        printf("Votre nouveaux mot est : %s", newWord);
    } else if (choiceToCreateWord == 0){
        printf("À bientot ! \n");
        quit = 1;
    }
    
    return 0;
}