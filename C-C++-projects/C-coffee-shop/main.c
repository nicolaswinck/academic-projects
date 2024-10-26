#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
    // Constant for converting grams into pounds.
    const double GRAMS_IN_LBS = 453.5924;

    // Setting variables for preferences and specs.
    char coffeeType1, coffeeType2, coffeeType3,
        useCream1, useCream2, useCream3,
        strength, orderWithCream;
    int weightBag1, weightBag2, weightBag3, dailyServings;

    // Getting info for the coffee specs (input).
    printf("***** Cosmos Coffee Shop *****\n"
        "================================\n\n"
        "Please, enter the following coffee product information:\n\n");

    printf("Coffee 1........................\n");
    printf("L = light, M = medium, R = rich: ");
    scanf(" %c", &coffeeType1);
    printf("Bag weight (g): ");
    scanf("%d", &weightBag1);
    printf("Is this coffee best served with cream? (Y = yes/ N = no): ");
    scanf(" %c", &useCream1);

    putchar('\n');

    printf("Coffee 2........................\n");
    printf("L = light, M = medium, R = rich: ");
    scanf(" %c", &coffeeType2);
    printf("Bag weight (g): ");
    scanf("%d", &weightBag2);
    printf("Is this coffee best served with cream? (Y = yes/ N = no): ");
    scanf(" %c", &useCream2);

    putchar('\n');

    printf("Coffee 3........................\n");
    printf("L = light, M = medium, R = rich: ");
    scanf(" %c", &coffeeType3);
    printf("Bag weight (g): ");
    scanf("%d", &weightBag3);
    printf("Is this coffee best served with cream? (Y = yes/ N = no): ");
    scanf(" %c", &useCream3);

    putchar('\n');

    // Table displaying the specs accordingly.
    printf("---+------------------------+---------------+-------+\n");
    printf("   |    Coffee              |   Package     | Ideal |\n");
    printf("   |    Style               |  Weight (bag) | Served|\n");
    printf("   +------------------------+---------------+ With  |\n");
    printf("ID | Light | Medium | Rich  |  (G) | Lbs    | Cream |\n");
    printf("---+------------------------+---------------+-------|\n");
    printf(" 1 |   %d   |   %d    |   %d   | %4d | %6.3lf |   %d   |\n",
        (coffeeType1 == 'l' || coffeeType1 == 'L'), (coffeeType1 == 'm' || coffeeType1 == 'M'),
        (coffeeType1 == 'r' || coffeeType1 == 'R'), weightBag1,
        weightBag1 / GRAMS_IN_LBS, (useCream1 == 'y' || useCream1 == 'Y'));
    printf(" 2 |   %d   |   %d    |   %d   | %4d | %6.3lf |   %d   |\n",
        (coffeeType2 == 'l' || coffeeType2 == 'L'), (coffeeType2 == 'm' || coffeeType2 == 'M'),
        (coffeeType2 == 'r' || coffeeType2 == 'R'), weightBag2,
        weightBag2 / GRAMS_IN_LBS, (useCream2 == 'y' || useCream2 == 'Y'));
    printf(" 3 |   %d   |   %d    |   %d   | %4d | %6.3lf |   %d   |\n\n",
        (coffeeType3 == 'l' || coffeeType3 == 'L'), (coffeeType3 == 'm' || coffeeType3 == 'M'),
        (coffeeType3 == 'r' || coffeeType3 == 'R'), weightBag3,
        weightBag3 / GRAMS_IN_LBS, (useCream3 == 'y' || useCream3 == 'Y'));

    // Getting info for the customer preferences.
    printf("How do you like your coffee?\n\n");

    printf("Coffee strength (L = light, M = medium, R = rich): ");
    scanf(" %c", &strength);
    printf("Do you like your coffee with cream? (Y = yes/ N = no): ");
    scanf(" %c", &orderWithCream);
    printf("How many daily servings? ");
    scanf("%d", &dailyServings);

    putchar('\n');

    // Displaying preferences and availability.
    printf("Aligning your preferences to the options available........................ \n\n");

    printf("--+------------------+--------------+-------+\n");
    printf("  |    Coffee        |   Package    | With  |\n");
    printf("ID|    Style         | Weight (bag) | Cream |\n");
    printf("--+------------------+--------------+-------+\n");
    printf(" 1|       %d          |      %d       |   %d   |\n",
        ((coffeeType1 == 'l' || coffeeType1 == 'L') && (strength == 'l' || strength == 'L')),

        ((dailyServings > 0 && dailyServings < 5) && weightBag1 == 250),

        ((useCream1 == 'y' || useCream1 == 'Y') && (orderWithCream == 'y' || orderWithCream == 'Y')) ||
        ((useCream1 == 'n' || useCream1 == 'N') && (orderWithCream == 'n' || orderWithCream == 'N')));

    printf(" 2|       %d          |      %d       |   %d   |\n",
        ((coffeeType2 == 'r' || coffeeType2 == 'R') && (strength == 'r' || strength == 'R')),

        ((dailyServings > 4 && dailyServings < 10) && weightBag2 == 500),

        ((useCream2 == 'y' || useCream2 == 'Y') && (orderWithCream == 'y' || orderWithCream == 'Y')) ||
        ((useCream2 == 'n' || useCream2 == 'N') && (orderWithCream == 'n' || orderWithCream == 'N')));

    printf(" 3|       %d          |      %d       |   %d   |\n\n",
        ((coffeeType3 == 'm' || coffeeType3 == 'M') && (strength == 'm' || strength == 'M')),

        ((dailyServings > 9) && weightBag3 == 1000),

        ((useCream3 == 'y' || useCream3 == 'Y') && (orderWithCream == 'y' || orderWithCream == 'Y')) ||
        ((useCream3 == 'n' || useCream3 == 'N') && (orderWithCream == 'n' || orderWithCream == 'N')));

    printf("How do you like your coffee?\n\n");

    printf("Coffee strength (L = light, M = medium, R = rich): ");
    scanf(" %c", &strength);
    printf("Do you like your coffee with cream? (Y = yes/ N = no): ");
    scanf(" %c", &orderWithCream);
    printf("How many daily servings? ");
    scanf("%d", &dailyServings);

    putchar('\n');

    printf("Aligning your preferences to the options available........................ \n\n");

    printf("--+------------------+--------------+-------+\n");
    printf("  |    Coffee        |   Package    | With  |\n");
    printf("ID|    Style         | Weight (bag) | Cream |\n");
    printf("--+------------------+--------------+-------+\n");
    printf(" 1|       %d          |      %d       |   %d   |\n",
        ((coffeeType1 == 'l' || coffeeType1 == 'L') && (strength == 'l' || strength == 'L')),

        ((dailyServings > 0 && dailyServings < 5) && weightBag1 == 250),

        ((useCream1 == 'y' || useCream1 == 'Y') && (orderWithCream == 'y' || orderWithCream == 'Y')) ||
        ((useCream1 == 'n' || useCream1 == 'N') && (orderWithCream == 'n' || orderWithCream == 'N')));

    printf(" 2|       %d          |      %d       |   %d   |\n",
        ((coffeeType2 == 'r' || coffeeType2 == 'R') && (strength == 'r' || strength == 'R')),

        ((dailyServings > 4 && dailyServings < 10) && weightBag2 == 500),

        ((useCream2 == 'y' || useCream2 == 'Y') && (orderWithCream == 'y' || orderWithCream == 'Y')) ||
        ((useCream2 == 'n' || useCream2 == 'N') && (orderWithCream == 'n' || orderWithCream == 'N')));

    printf(" 3|       %d          |      %d       |   %d   |\n\n",
        ((coffeeType3 == 'm' || coffeeType3 == 'M') && (strength == 'm' || strength == 'M')),

        ((dailyServings > 9) && weightBag3 == 1000),

        ((useCream3 == 'y' || useCream3 == 'Y') && (orderWithCream == 'y' || orderWithCream == 'Y')) ||
        ((useCream3 == 'n' || useCream3 == 'N') && (orderWithCream == 'n' || orderWithCream == 'N')));

    printf("Thank you for shopping with Cosmos!\n");

    return 0;
}