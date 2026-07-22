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

void bookSeat(int m, int t) {
    char name[50];
    char rowChar;
    int col, discountChoice, groupSize;
    int totalPrice = 0, totalDiscount = 0;
    char bookedSeats[200] = "";

    viewSeatMap(m, t);

    printf("\nENTER YOUR FULL NAME (First and last): ");
    scanf(" %[^\n]", name);

    printf("BOOKING GROUP SIZE (Number of tickets): ");
    scanf("%d", &groupSize);

    for (int g = 0; g < groupSize; g++) {
        viewSeatMap(m, t);

        printf("\n");
        printf("--------------------------------\n");
        printf("== SELECT SEAT FOR TICKET %d  ==\n", g+1);
        printf("--------------------------------\n");
        printf("ENTER ROW (A-E): ");
        scanf(" %c", &rowChar);
        printf("ENTER SEAT NUMBER (1-10): ");
        scanf("%d", &col);

        int row = rowChar - 'A';
        col--;

        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("[X] INVALID SEAT SELECTION! [X]\n");
            g--;
            continue;
        }
        if (showtimes[m][t].seats[row][col].booked) {
            printf("[X] SEAT ALREADY BOOKED! [X]\n");
            g--;
            continue;
        }

        int basePrice = getBasePrice(row);
        int price = basePrice;
        int seatDiscount = 0;

        printf("\n");
        printf("----------------------------------------------\n");
        printf("==== SELECT DISCOUNT TYPE FOR THIS TICKET ====\n");
        printf("----------------------------------------------\n");
        printf("1. NONE\n");
        printf("2. STUDENT (Age under 18 years)\n");
        printf("3. SENIOR (18+)\n");
        printf("----------------------------------------------\n");
        printf("Choice: ");
        scanf("%d", &discountChoice);

        if (discountChoice == 2) { seatDiscount += basePrice * 0.1; }
        else if (discountChoice == 3) { seatDiscount += basePrice * 0.2; }

        if (groupSize >= 4) { seatDiscount += basePrice * 0.1; }

        price = basePrice - seatDiscount;

        showtimes[m][t].seats[row][col].booked = 1;
        showtimes[m][t].seats[row][col].pricePaid = price;
        strcpy(showtimes[m][t].seats[row][col].customerName, name);

        totalPrice += price;
        totalDiscount += seatDiscount;

        char seatStr[10];
        sprintf(seatStr, "%c%d ", 'A' + row, col+1);
        strcat(bookedSeats, seatStr);
    }

    clearScreen();
    printf("----------------------------------------------------\n");
    printf("===========  [||] KDTIG MOVIE LAND [||]  ===========\n");
    printf("----------------------------------------------------\n");
    printf("   Movie           : %s\n", showtimes[m][t].movieName);
    printf("   Showtime        : %s\n", showtimes[m][t].showtime);
    printf("   Customer        : %s\n", name);
    printf("   Number of Seats : %d\n", groupSize);
    printf("   Seats Booked    : %s\n", bookedSeats);
    printf("----------------------------------------------------\n");
    printf("   Total Discount  : Rs. %d\n", totalDiscount);
    printf("   Final Price Paid: Rs. %d\n", totalPrice);
    printf("----------------------------------------------------\n");
    printf("           THANK YOU FOR BOOKING WITH US!           \n");
    printf("     VISIT OUR SITE : https://kdtigmovieland.com    \n");
    printf("----------------------------------------------------\n");
}

void cancelBooking(int m, int t) {
    char rowChar;
    int col;
    printf("\nENTER ROW (A-E): ");
    scanf(" %c", &rowChar);
    printf("ENTER SEAT NUMBER (1-10): ");
    scanf("%d", &col);

    int row = rowChar - 'A';
    col--;

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("[X] INVALID SEAT SELECTION! [X]\n");
        return;
    }
    if (!showtimes[m][t].seats[row][col].booked) {
        printf("[X] CANNOT CANCEL — SEAT NOT BOOKED! [X]\n");
        return;
    }

    showtimes[m][t].seats[row][col].booked = 0;
    showtimes[m][t].seats[row][col].pricePaid = 0;
    strcpy(showtimes[m][t].seats[row][col].customerName, "");
    printf(" BOOKING CANCELLED SUCCESSFULLY!\n");
}

void searchBooking(int m, int t) {
    char name[50];
    printf("\nENTER CUSTOMER NAME: ");
    scanf(" %[^\n]", name);

    int found = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (showtimes[m][t].seats[i][j].booked &&
                strcmp(showtimes[m][t].seats[i][j].customerName, name) == 0) {
                printf("BOOKING FOUND: Seat %c%d, Price Rs. %d\n",
                       'A' + i, j+1, showtimes[m][t].seats[i][j].pricePaid);
                found = 1;
            }
        }
    }
    if (!found) printf("[X] NO BOOKING FOUND FOR %s [X]\n", name);
}

void revenueReport(int m, int t)
{
    int totalRevenue = 0, ticketsSold = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (showtimes[m][t].seats[i][j].booked)
            {
                ticketsSold++;
                totalRevenue += showtimes[m][t].seats[i][j].pricePaid;
            }
        }
    }
    printf("\n=====  REVENUE REPORT FOR %s (%s)  =====\n",
           showtimes[m][t].movieName, showtimes[m][t].showtime);
    printf(" Tickets Sold: %d\n Total Revenue: Rs. %d\n",
           ticketsSold, totalRevenue);
}

int main()
{
    initData();
    int choice, m, t;
    while (1)
    {
        clearScreen();
        printf("--------------------------------\n");
        printf("======  KDTIG MOVIE LAND  ======\n");
        printf("--------------------------------\n");
        printf("1. View Movies\n");
        printf("2. View Showtimes\n");
        printf("3. View Seat Map\n");
        printf("4. Book a Seat\n");
        printf("5. Cancel a Booking\n");
        printf("6. Search Booking\n");
        printf("7. View Revenue Report\n");
        printf("8. Exit\n");
        printf("--------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            viewMovies();
            break;
        case 2:
            viewMovies();
            printf("SELECT MOVIE (1-3): ");
            scanf("%d", &m);
            m--;
            viewShowtimes(m);
            break;
        case 3:
            viewMovies();
            printf("SELECT MOVIE (1-3): ");
            scanf("%d", &m);
            m--;
            viewShowtimes(m);
            printf("SELECT SHOWTIME (1-2): ");
            scanf("%d", &t);
            t--;
            viewSeatMap(m, t);
            break;
        case 4:
            viewMovies();
            printf("SELECT MOVIE (1-3): ");
            scanf("%d", &m);
            m--;
            viewShowtimes(m);
            printf("SELECT SHOWTIME (1-2): ");
            scanf("%d", &t);
            t--;
            bookSeat(m, t);
            break;
        case 5:
            viewMovies();
            printf("SELECT MOVIE (1-3): ");
            scanf("%d", &m);
            m--;
            viewShowtimes(m);
            printf("SELECT SHOWTIME (1-2): ");
            scanf("%d", &t);
            t--;
            cancelBooking(m, t);
            break;
        case 6:
            viewMovies();
            printf("SELECT MOVIE (1-3): ");
            scanf("%d", &m);
            m--;
            viewShowtimes(m);
            printf("SELECT SHOWTIME (1-2): ");
            scanf("%d", &t);
            t--;
            searchBooking(m, t);
            break;
        case 7:
            viewMovies();
            printf("SELECT MOVIE (1-3): ");
            scanf("%d", &m);
            m--;
            viewShowtimes(m);
            printf("SELECT SHOWTIME (1-2): ");
            scanf("%d", &t);
            t--;
            revenueReport(m, t);
            break;
        case 8:
            printf("\n Thank you for visiting KDTIG MOVIELAND!\n");
                   return 0;
               default:
                       printf("[X] INVALID CHOICE! [X]\n");
                       break;
            }

        printf("\nPRESS ENTER TO CONTINUE...");
        getchar();
        getchar();
    }
    return 0;
}

