#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
} Bus;

typedef struct
{
    char name[50];
    int age;
    int seatNumber;
    int busNumber;
} Passenger;

typedef struct
{
    char username[50];
    char password[50];
} User;

void displayMainMenu();
void displayUserMenu();
int loginUser(User users[], int numUsers, char username[], char password[]);
void bookTicket(Bus buses[], int numBuses, Passenger passengers[], int *numPassengers);
void cancelTicket(Bus buses[], int numBuses, Passenger passengers[], int *numPassengers);
void checkBusStatus(Bus buses[], int numBuses);

int main()
{
    clock_t start = clock();
    // Code start.

    User users[5] = {
        {"user1", "password1"},
        {"user2", "password2"},
        {"user3", "password3"},
        {"user4", "password4"},
        {"user5", "password5"}};
    int numUsers = sizeof(users) / sizeof(users[0]);

    Bus buses[3] = {
        {101, "City A", "City B", 50, 50, 25.0},
        {102, "City C", "City D", 40, 40, 20.0},
        {103, "City E", "City F", 30, 30, 15.0}};
    int numBuses = sizeof(buses) / sizeof(buses[0]);

    Passenger passengers[500];
    int numPassengers = 0;
    int loggedInUserId = -1;

    while (1)
    {
        if (loggedInUserId == -1)
        {
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1)
            {
                char username[50];
                char password[50];

                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                loggedInUserId = loginUser(users, numUsers, username, password);
                if (loggedInUserId == -1)
                {
                    printf("Login failed. Please check your username and password.\n");
                }
                else
                {
                    printf("Login successful. Welcome, %s!\n", username);
                }
            }
            else if (choice == 2)
            {
                printf("Exiting the program.\n");
                break;
            }
            else
            {
                printf("Invalid choice. Please try again.\n");
            }
        }
        else
        {
            displayUserMenu();
            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice)
            {
            case 1:
                bookTicket(buses, numBuses, passengers, &numPassengers);
                break;
            case 2:
                cancelTicket(buses, numBuses, passengers, &numPassengers);
                break;
            case 3:
                checkBusStatus(buses, numBuses);
                break;
            case 4:
                printf("Logging out.\n");
                loggedInUserId = -1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }

    // Code end.
    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %.2f seconds\n", execution_time);

    printf("\nPress any key to close...");
    _getch();
    return 0;
}

void displayMainMenu()
{
    printf("\n=== Bus Reservation System ===\n");
    printf("1. Login\n");
    printf("2. Exit\n");
}

void displayUserMenu()
{
    printf("\n=== User Menu ===\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. Logout\n");
}

int loginUser(User users[], int numUsers, char username[], char password[])
{
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void bookTicket(Bus buses[], int numBuses, Passenger passengers[], int *numPassengers)
{
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++)
    {
        if (buses[i].busNumber == busNumber)
        {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1)
    {
        printf("Bus with the %d number not found.\n", busNumber);
    }
    else if (buses[busIndex].availableSeats == 0)
    {
        printf("Sorry, the bus is fully booked.\n");
    }
    else
    {
        printf("Enter Passenger Name: ");
        scanf("%s", passengers[*numPassengers].name);

        printf("Enter Passenger Age: ");
        scanf("%d", &passengers[*numPassengers].age);

        passengers[*numPassengers].busNumber = busNumber;
        passengers[*numPassengers].seatNumber = buses[busIndex].totalSeats - buses[busIndex].availableSeats + 1;

        buses[busIndex].availableSeats--;
        (*numPassengers)++;

        printf("Bus booked successfully!\n");
    }
}

void cancelTicket(Bus buses[], int numBuses, Passenger passengers[], int *numPassengers)
{
    printf("\nEnter the bus number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int busFound = 0;

    for (int i = 0; i < numBuses; i++)
    {
        if (buses[i].busNumber == busNumber)
        {
            busFound = 1;
            break;
        }
    }

    if (busFound == 0)
    {
        printf("Bus with the number %d not found.\n", busNumber);
        return;
    }

    printf("\nEnter passenger name: ");
    char name[50];
    scanf("%s", name);

    int found = 0;

    for (int i = 0; i < *numPassengers; i++)
    {
        if (passengers[i].busNumber == busNumber && strcmp(passengers[i].name, name) == 0)
        {
            int busIndex = -1;
            for (int j = 0; j < numBuses; j++)
            {
                if (buses[j].busNumber == busNumber)
                {
                    busIndex = j;
                    break;
                }
            }

            if (busIndex != -1)
            {
                buses[busIndex].availableSeats++;

                for (int j = i; j < (*numPassengers) - 1; j++)
                {
                    passengers[j] = passengers[j + 1];
                }
                (*numPassengers)--;

                found = 1;
                printf("Ticket cancelled successfully.\n");
                break;
            }
        }
    }

    if (!found)
    {
        printf("Passenger with name \"%s\" not found on bus number %d.\n", name, busNumber);
    }
}
void checkBusStatus(Bus buses[], int numBuses)
{
    for (int i = 0; i < numBuses; i++)
    {
        printf("\nBus Number: %d\n", buses[i].busNumber);
        printf("Source : %s\n", buses[i].source);
        printf("Destination : %s\n", buses[i].destination);
        printf("Total Seats : %d\n", buses[i].totalSeats);
        printf("Available Seats : %d\n", buses[i].availableSeats);
        printf("Fare : %.2f\n", buses[i].fare);
    }
}
