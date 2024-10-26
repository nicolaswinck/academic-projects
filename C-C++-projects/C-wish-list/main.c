#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// Macro holding the maximum number of itens.
#define MAX_ITEMS 10

int main(void)
{
    // Unmodifiable constant variables defining minimum and maximum amounts.
    const double INCOME_MIN = 500.00, INCOME_MAX = 400000.00,
        COST_MIN = 100.00;

    // Variables (flag and accumulators included).
    double inputIncome, sumCosts = 0.0f, sumPriority = 0.0f;
    int inputItems, inputOk = 0, i, inputMenu, inputPriority,
        forecastYears, forecastMonths, totalAllItems, displayNote = 0;

    // Declaring and assigning arrays to a safe memory space.
    int priorities[MAX_ITEMS] = { 0 };
    char financed[MAX_ITEMS] = { 0 };
    double cost[MAX_ITEMS] = { 0.0 };

    // Displaying enter message.
    printf("+--------------------------+\n"
        "+  Welcome to Cosmos Wish  |\n"
        "+--------------------------+\n\n");

    // Validating user input for income.
    do {
        printf("What is your net income? $");
        scanf("%lf", &inputIncome);

        if (inputIncome < INCOME_MIN)
        {
            printf("ERROR: The monthly income value must be of at"
                " least $%.2lf\n\n", INCOME_MIN);
        }
        else if (inputIncome > INCOME_MAX)
        {
            printf("ERROR: The value must be no more than $%.2lf\n\n", 
                INCOME_MAX);
        }
        else
        {
            inputOk = 1;
            putchar('\n');
        }

    } while (inputOk == 0);

    // Resetting validation flag.
    inputOk = 0;

    // Validating user input for the quantity of items to be forecasted.
    do {
        printf("Please insert how many items you wish to forecast: ");
        scanf("%d", &inputItems);

        if (inputItems < 1 || inputItems > MAX_ITEMS)
        {
            printf("ERROR: Value must be between 1 and %d items.\n\n",
                MAX_ITEMS);
        }
        else
        {
            inputOk = 1;
            putchar('\n');
        }

    } while (inputOk == 0);

    // Starting loop with details prompting.
    for (i = 0; i < inputItems; i++)
    {
        // Resetting validation flag.
        inputOk = 0;

        printf("Item-%d details:\n", i + 1);

        // Validating user input for item cost.
        do {
            printf("   Item cost: $");
            scanf("%lf", &cost[i]);

            if (cost[i] < COST_MIN)
            {
                printf("      ERROR: The value must be at least $%.2lf\n",
                    COST_MIN);
            }
            else
            {
                inputOk = 1;
            }

        } while (inputOk == 0);

        // Resetting validation flag.
        inputOk = 0;

        // Validating user input for priority.
        do {
            printf("   Please enter the importance of this item to you (1=must have, 2=important,"
                " 3=want): ");
            scanf("%d", &priorities[i]);

            if (priorities[i] < 1 || priorities[i] > 3)
            {
                printf("      ERROR: The value must be between 1 and 3.\n");
            }
            else
            {
                inputOk = 1;
            }

        } while (inputOk == 0);

        // Resetting validation flag.
        inputOk = 0;

        // Validating user input for financing options.
        do {
            printf("   Does this item have financing options? (y/n): ");
            scanf(" %c", &financed[i]);

            if (!(financed[i] == 'n') && !(financed[i] == 'y'))
            {
                printf("      ERROR: The value must be a lowercase 'y' or 'n'\n");
            }
            else
            {
                inputOk = 1;
            }

        } while (inputOk == 0);

        putchar('\n');
    }

    // Displaying the data table:
    // Header.
    printf("Item Priority Financed        Cost\n");
    printf("---- -------- -------- -----------\n");

    // Printing the number of items and the elements for each array.
    for (i = 0; i < inputItems; i++)
    {
        printf("%3d  %5d    %5c    %11.2lf\n", i + 1, priorities[i],
            financed[i], cost[i]);

        // Accumulating costs.
        sumCosts += cost[i];
    }

    printf("---- -------- -------- -----------\n");

    // Displaying the sum of all costs.
    printf("                      $%11.2lf\n\n", sumCosts);

    // Displaying forecasting menu and validating user selection.
    // Validating the input for menu selection.
    do {
        printf("How do you want to filter your wish list?\n"
            " 1. All items (no filter)\n"
            " 2. By priority\n"
            " 0. Quit/Exit\n"
            "Selection: ");
        scanf("%d", &inputMenu);

        putchar('\n');

        if (inputMenu < 0 || inputMenu > 2)
        {
            printf("ERROR: Invalid menu selection.\n\n");
        }

        // Selections 1 and 2.
        else
        {
            switch (inputMenu)
            {
            case 1:

                // Calculations for the forecast months and years for all the items.
                totalAllItems = (((int)(sumCosts + 0.005) / (int)(inputIncome + 0.005)));
                forecastYears = totalAllItems / 12;
                forecastMonths = totalAllItems % 12;

                // Displaying information.
                printf("====================================================\n"
                    "Filter:   All items\n"
                    "Amount:   $%1.2lf\n", sumCosts);

                // Displaying results and adding 1 to month counting (rounding up).
                printf("Forecast: %d years, %d months\n", forecastYears, forecastMonths + 1);

                // Looking for available financing option(s) within the selection.
                for (i = 0; i < inputItems; i++)
                {
                    if (financed[i] == 'y')
                    {
                        displayNote = 1;
                    }
                }

                // Displaying note for available financing option(s).
                if (displayNote != 0)
                {
                    printf("NOTE: Financing options are available on some items.\n"
                        "      You can likely reduce the estimated months.\n");
                }

                printf("====================================================\n\n");

                break;

            case 2:

                // Resetting validation flag.
                inputOk = 0;

                // Validating the input for priority range.
                do {
                    printf("What priority do you want to filter by? [1-3]: ");
                    scanf("%d", &inputPriority);

                    if (inputPriority < 1 || inputPriority > 3)
                    {
                        printf("ERROR: Invalid menu selection.\n\n");
                    }
                    else
                    {
                        inputOk = 1;
                        putchar('\n');
                    }

                } while (inputOk == 0);

                // Displaying information.
                printf("====================================================\n"
                    "Filter:   by priority (%d)\n", inputPriority);

                // Looking for priorities that match with the user input.
                // Looking for available financing option(s) within the selection. 
                for (i = 0; i < inputItems; i++)
                {
                    if (priorities[i] == inputPriority)
                    {
                        sumPriority += cost[i];

                        if (financed[i] == 'y')
                        {
                            displayNote = 1;
                        }
                    }
                }

                // Calculations for the forecast months and years for the filtered option.
                totalAllItems = (((int)(sumPriority + 0.005) / (int)(inputIncome + 0.005)));
                forecastYears = totalAllItems / 12;
                forecastMonths = totalAllItems % 12;

                printf("Amount:   $%1.2lf\n", sumPriority);

                // Displaying results and adding 1 to month counting (rounding up).
                printf("Forecast: %d years, %d months\n", forecastYears, forecastMonths + 1);

                // Displaying note for available financing option(s).
                if (displayNote != 0)
                {
                    printf("NOTE: Financing options are available on some items.\n"
                        "      You can likely reduce the estimated months.\n");
                }
                
                printf("====================================================\n\n");

                break;
            }

            // Resetting variables for new accumulation and the flag for new validation.
            forecastYears = 0;
            forecastMonths = 0;
            sumPriority = 0;
            displayNote = 0;
        }

    } while (inputMenu != 0);

    // Displaying exit message.
    printf("Cosmo Co. hopes you have a wonderful day!\n\n");

    return 0;
}