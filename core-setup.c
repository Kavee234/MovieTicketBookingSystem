#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 10

typedef struct {
    char customerName[50];
    int pricePaid;
    int booked;
} Seat;

typedef struct {
    char movieName[50];
    char showtime[20];
    Seat seats[ROWS][COLS];
} Showtime;

Showtime showtimes[3][2];

int getBasePrice(int row) {
    if (row < 2) return 500;
    else if (row < 4) return 750;
    else return 1000;
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void initData() {
    char movies[3][50] = {"The Odyssey", "Interstellar", "The Spider-Man : Brand New Day"};
    char times[2][20] = {"5:00 PM", "8:00 PM"};

    for (int m = 0; m < 3; m++) {
        for (int t = 0; t < 2; t++) {
            strcpy(showtimes[m][t].movieName, movies[m]);
            strcpy(showtimes[m][t].showtime, times[t]);
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    showtimes[m][t].seats[i][j].booked = 0;
                    showtimes[m][t].seats[i][j].pricePaid = 0;
                    strcpy(showtimes[m][t].seats[i][j].customerName, "");
                }
            }
        }
    }
}
void viewMovies()
{
    printf("\n");
    printf("--------------------------------------\n");
    printf("=======    AVAILABLE MOVIES    =======\n");
    printf("--------------------------------------\n");
    for (int m = 0; m < 3; m++)
    {
        printf("    %d. %s\n", m+1, showtimes[m][0].movieName);
    }
    printf("--------------------------------------\n");
}
void viewShowtimes(int m)
{
    printf("\n");
    printf("\n");
    printf("----------------------------------------------\n");
    printf(" SHOWTIMES FOR %s\n", showtimes[m][0].movieName);
    printf("----------------------------------------------\n");
    for (int t = 0; t < 2; t++)
    {
        printf("    %d. %s\n", t+1, showtimes[m][t].showtime);
    }
    printf("----------------------------------------------\n");
}
void viewSeatMap(int m, int t)
{
    printf("\n");
    printf("\n");
    printf("--------------------------------------------------------------------\n");
    printf("====== SEAT MAP FOR %s (%s) ======\n",
           showtimes[m][t].movieName, showtimes[m][t].showtime);
    printf("--------------------------------------------------------------------\n");
    printf("\n");
    for (int i = 0; i < ROWS; i++)
    {
        printf("           ROW %c: ", 'A' + i);
        for (int j = 0; j < COLS; j++)
        {
            if (showtimes[m][t].seats[i][j].booked)
                printf("X ");
            else
                printf(". ");
        }
        printf("\n");
        printf("\n");
    }
    printf("--------------------------------------------------------------------\n");
    printf("\n");
    printf("------------------------------\n");
    printf("=====     PRICE LIST     =====\n");
    printf("------------------------------\n");
    printf(" ROWS A-B (Regular): Rs. 500\n");
    printf(" ROWS C-D (Premium): Rs. 750\n");
    printf(" ROW E (VIP)       : Rs. 1000\n");
    printf("------------------------------\n");
    printf("\n");
}
