#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

typedef struct diagoinfo // pour memoriser les coordonee les obstacles
{
    int x;
    int y;
    int derection;
} diagoinfo;

typedef struct ballposition // pour suivre la ball
{
    int x;
    int y;
} ballposition;

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error %s \n", SDL_GetError());
        return 0;
    }
    printf("SDL init \n");
    SDL_Window *window = SDL_CreateWindow("jeu memoire", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    srand(time(NULL)); // Initialisez la graine pour la génération aléatoire

    int N, i, j, k;
    scanf("%d", &N); // la taille de la grille (matrice)
    int grille[N][N];

    grille[0][0] = grille[N - 1][0] = grille[0][N - 1] = grille[N - 1][N - 1] = -3; // cote

    k = 1;
    i = 0;
    for (j = 1; j < (N - 1); j++) // for line up
    {
        grille[i][j] = k;
        k++;
    }

    j = N - 1;

    for (i = 1; i < (N - 1); i++) // for line right
    {
        grille[i][j] = k;
        k++;
    }

    i = N - 1;

    for (j = (N - 2); j > 0; j--) // for line down
    {
        grille[i][j] = k;
        k++;
    }
    j = 0;
    for (i = (N - 2); i > 0; i--) // for line left
    {
        grille[i][j] = k;
        k++;
    }

    // Marquer toutes les cases comme vides (0) pour inisialiser la grille
    for (i = 1; i < (N - 1); i++)
    {
        for (j = 1; j < (N - 1); j++)
        {
            grille[i][j] = 0;
        }
    }

    /* Affichez la grille */
    printf("\t");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", grille[i][j]);
            printf("\t");
        }
        printf("\n\n\t");
    }

    int M;

    scanf("%d", &M); // number of diago (obstacles)

    diagoinfo info[M];

    for (int m = 0; m < M; m++)
    {
        // Génération aléatoire des coordonnées de début de la diagonale
        int X = rand() % (N - 2) + 1;
        int Y = rand() % (N - 2) + 1;
        printf("le X =%d\n", X);
        printf("le Y =%d\n", Y);

        // Génération aléatoire de la direction (1 pour la diagonale slash /, -1 pour antislash \ )
        int direction = (rand() % 2 == 0) ? 1 : -1;

        info[m].x = X;
        info[m].y = Y;
        info[m].derection = direction;

        i = X;
        j = Y;

        // Parcourez la diagonale et marquez les cases
        if (i >= 1 && i < N - 1 && j >= 1 && j < N - 1)
        {
            grille[i][j] = direction; // Marquez la case comme diagonale (obstacles)
        }
    }

    printf("\n\n");

    for (i = 0; i < N; i++) // affichage
    {
        for (j = 0; j < N; j++)
        {
            printf("|\t");
            printf("%d", grille[i][j]);
            if (j == N - 1)
            {
                printf("\t|");
            }
            printf("\t");
        }
        printf("\n\n");
    }

    printf("\n\n");

    for (i = 0; i < M; i++) // afficher le tableau
    {
        printf("diagonal %d: X=%d,  y=%d  direction=%d", i + 1, info[i].x, info[i].y, info[i].derection);
        printf("\n");
    }

    for (i = 0; i < M; i++) // supprimer les diago
    {
        int X = info[i].x;
        int Y = info[i].y;
        grille[X][Y] = 0;
    }

    printf("\n\n");

    for (i = 0; i < N; i++) // affichage apres la supprission
    {
        for (j = 0; j < N; j++)
        {
            printf("|\t");
            printf("%d", grille[i][j]);
            if (j == N - 1)
            {
                printf("\t|");
            }
            printf("\t");
        }
        printf("\n\n");
    }

    int Nn = N * 4 - 8; // le nmbre des point d'entrer

    int a = (rand() % Nn) + 1;
    printf("The starting point  %d", a); // Génération aléatoire de point d'entrer

    int b;
    printf("\n\n Chose the point of arrival");

    scanf(" %d", &b);

    printf("\n\n");

    for (i = 0; i < M; i++) // retourner les obstacles
    {
        int X = info[i].x;
        int Y = info[i].y;
        grille[X][Y] = info[i].derection;
    }

    int c = N - 2; // le nombre de entre dans chaque line
    int line = 1;  // le nombre de la line

    while (c < a) // trouver la line
    {
        line++;
        c = c + (N - 2);
    }

    printf("\n\n la line :%d", line);

    ballposition ball; // chercher les coordonnées de point d'entre

    if (line == 1) // line up
    {
        j = 1;

        while (grille[0][j] != a)
        {
            j++;
        }

        ball.x = 0;
        ball.y = j;
    }

    if (line == 2) // line right
    {
        i = 1;
        while (grille[i][N - 1] != a)
        {
            i++;
        }

        ball.x = i;
        ball.y = N - 1;
    }

    if (line == 3) // line down
    {
        j = 1;
        while (grille[N - 1][j] != a)
        {
            j++;
        }
        ball.x = N - 1;
        ball.y = j;
    }

    if (line == 4)
    {
        i = 1;
        while (grille[i][0] != a)
        {
            i++;
        }
        ball.x = i;
        ball.y = 0;
    }

    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);

    do
    {
        if (line == 1)
        {
            j = ball.y;
            ball.x++;
            printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
        }

        if (line == 2)
        {
            i = ball.x;
            ball.y--;
            printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
        }

        if (line == 3)
        {
            j = ball.y;
            ball.x--;
            printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
        }

        if (line == 4)
        {
            i = ball.x;
            ball.y++;
            printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
        }

        while (grille[ball.x][ball.y] == 1 || grille[ball.x][ball.y] == -1)
        {
            if (grille[ball.x][ball.y] == 1)
            {
                switch (line)
                {
                case 1:
                    ball.y--;
                    line = 2;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                case 2:
                    ball.x++;
                    line = 1;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                case 3:
                    ball.y++;
                    line = 4;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                case 4:
                    ball.x--;
                    line = 3;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                }
            }

            if (grille[ball.x][ball.y] == -1)
            {
                switch (line)
                {
                case 1:
                    ball.y++;
                    line = 4;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                case 2:
                    ball.x--;
                    line = 3;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                case 3:
                    ball.y--;
                    line = 2;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                case 4:
                    ball.x++;
                    line = 1;
                    printf("\n\n la ball :(%d,\t%d)", ball.x, ball.y);
                    break;
                }
            }
        }

    } while (grille[ball.x][ball.y] == 0);

    if (b == grille[ball.x][ball.y])
    {
        printf(" \n\n BINGO YOU WON ");
    }
    else
    {
        printf("\n\n GAME OVER ");
    }

    return 0;
}