#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// Year macros.
#define MIN_YEAR 2014
#define MAX_YEAR 2024

// Log days macro.
#define LOG_DAYS 3


int main(void)
{
    // Month constants, constant for 1st day and variables (flag included).
    const int JAN = 1, DEC = 12, firstDay = 1;
    int inputYear, inputMonth, i, inputOk;
    double ratingMorning, ratingEvening, totalMorning = 0.0f,
        totalEvening = 0.0f;

    printf("Hello! Welcome to the Cosmos Well-being System 1.0\n"
        "====================================================\n");

    do {
        printf("Set the year and month for the log in the format YYYY MM: ");
        scanf("%d %d", &inputYear, &inputMonth);

        // Validation flag (assigning to 0).
        inputOk = 0;

        // Validating year and month user inputs.
        if (inputYear < MIN_YEAR || inputYear > MAX_YEAR)
        {
            printf("   ERROR: The year must be between %d and %d inclusive.\n",
                MIN_YEAR, MAX_YEAR);
        }

        if (inputMonth < JAN || inputMonth > DEC)
        {
            printf("   ERROR: Jan.(%d) - Dec.(%d)\n", JAN, DEC);
        }

        else if (!(inputYear < MIN_YEAR || inputYear > MAX_YEAR) &&
            !(inputMonth < JAN || inputMonth > DEC))
        {
            inputOk = 1;
        }

    } while (inputOk == 0);

    putchar('\n');

    printf("...............The date is set...............\n\n");

    for (i = 0; i < LOG_DAYS; i++)
    {
        printf("%d-", inputYear);

        // Selecting month output (MMM).
        switch (inputMonth)
        {
        case 1:
            printf("JAN");
            break;

        case 2:
            printf("FEB");
            break;

        case 3:
            printf("MAR");
            break;

        case 4:
            printf("APR");
            break;

        case 5:
            printf("MAY");
            break;

        case 6:
            printf("JUN");
            break;

        case 7:
            printf("JUL");
            break;

        case 8:
            printf("AUG");
            break;

        case 9:
            printf("SEP");
            break;

        case 10:
            printf("OCT");
            break;

        case 11:
            printf("NOV");
            break;

        case 12:
            printf("DEC");
            break;
        };

        // Adding the log's 1st day display at the beginning (and incrementing).
        printf("-%02d\n", firstDay + i);

        // Starting user input validation for morning and evening ratings.
        // Resetting validation flag.
        inputOk = 0;

        do {
            printf("   Rate your morning from 0.0 to 5.0: ");
            scanf("%lf", &ratingMorning);

            if (ratingMorning < 0.0 || ratingMorning > 5.0)
            {
                printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive.\n");
            }

            else
            {
                inputOk = 1;
            }

        } while (inputOk == 0);

        // Resetting validation flag.
        inputOk = 0;

        do {
            printf("   Rate your evening from 0.0 to 5.0: ");
            scanf("%lf", &ratingEvening);

            if (ratingEvening < 0.0 || ratingEvening > 5.0)
            {
                printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive.\n");
            }

            else
            {
                inputOk = 1;
            }

        } while (inputOk == 0);

        putchar('\n');

        // Accumulating rating points for morning and evening.
        totalMorning += ratingMorning;
        totalEvening += ratingEvening;

    }
    printf("...............The date is set...............\n\n");

    // Displaying summary information with calculations.
    printf("===================SUMMARY===================\n\n");

    printf("MORNING rating: %6.3lf\n", totalMorning);
    printf("EVENING rating: %6.3lf\n", totalEvening);
    printf("============================\n");
    printf("OVERALL rating: %.3lf\n\n", totalMorning + totalEvening);

    printf("Average MORNING rating: %4.1lf\n", totalMorning / LOG_DAYS);
    printf("Average EVENING rating: %4.1lf\n", totalEvening / LOG_DAYS);
    printf("============================\n");

    // Calculating the average with precision.
    printf("Average overall rating: %4.1lf\n\n", 
        (totalMorning + totalEvening) / (LOG_DAYS * 2.0));

    return 0;
}