#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
    // Setting HST.
    const double TAX = 0.13;
    // Setting variables to hold customer's and product info: shirt size, prices...
    const char firstCustomerSize = 'S', secondCustomerSize = 'M', thirdCustomerSize = 'L';
    double priceSmall, priceMedium, priceLarge,
        subTotal, taxes, total, average;
    int firstCustomerQty, secondCustomerQty, thirdCustomerQty, 
        firstCustomerSubTotal, firstCustomerTaxes, firstCustomerTotal,
        secondCustomerSubTotal, secondCustomerTaxes, secondCustomerTotal,
        thirdCustomerSubTotal, thirdCustomerTaxes, thirdCustomerTotal,
        coins, balance;

    // Getting input information for prices and quantity.
    printf("Set Shirt Prices\n"
        "================\n");

    printf("Enter the price for a SMALL shirt: $");
    scanf("%lf", &priceSmall);
    printf("Enter the price for a MEDIUM shirt: $");
    scanf("%lf", &priceMedium);
    printf("Enter the price for a LARGE shirt: $");
    scanf("%lf", &priceLarge);

    putchar('\n');

    printf("Price list for shirts\n"
        "======================\n");
    printf("SMALL  : $%.2lf\n", priceSmall);
    printf("MEDIUM : $%.2lf\n", priceMedium);
    printf("LARGE  : $%.2lf\n", priceLarge);

    putchar('\n');

    printf("First customer's shirt size is '%c'\n", firstCustomerSize);
    printf("Number of shirts first customer is buying: ");
    scanf("%d", &firstCustomerQty);

    putchar('\n');

    printf("Second customer's shirt size is '%c'\n", secondCustomerSize);
    printf("Number of shirts second customer is buying: ");
    scanf("%d", &secondCustomerQty);

    putchar('\n');

    printf("Third customer's shirt size is '%c'\n", thirdCustomerSize);
    printf("Number of shirts third customer is buying: ");
    scanf("%d", &thirdCustomerQty);

    putchar('\n');

    // Calculating subtotal (before taxes), taxes and total for each customer.
    firstCustomerSubTotal = ((priceSmall * firstCustomerQty) + 0.005) * 100;
    firstCustomerTaxes = (firstCustomerSubTotal * TAX) + 0.5;
    firstCustomerTotal = firstCustomerSubTotal + firstCustomerTaxes;

    secondCustomerSubTotal = ((priceMedium * secondCustomerQty) + 0.005) * 100;
    secondCustomerTaxes = (secondCustomerSubTotal * TAX) + 0.5;
    secondCustomerTotal = secondCustomerSubTotal + secondCustomerTaxes;

    thirdCustomerSubTotal = ((priceLarge * thirdCustomerQty) + 0.005) * 100;
    thirdCustomerTaxes = (thirdCustomerSubTotal * TAX) + 0.5;
    thirdCustomerTotal = thirdCustomerSubTotal + thirdCustomerTaxes;

    // Wrapping up to avoid miscalculation.
    subTotal = ((double)firstCustomerSubTotal / 100) + ((double)secondCustomerSubTotal / 100) + ((double)thirdCustomerSubTotal / 100);
    taxes = ((double)firstCustomerTaxes / 100) + ((double)secondCustomerTaxes / 100) + ((double)thirdCustomerTaxes / 100);
    total = ((double)firstCustomerTotal / 100) + ((double)secondCustomerTotal / 100) + ((double)thirdCustomerTotal / 100);

    // Printing out general results (receipt-like information).
    printf("Customer Size Price Qty Sub-Total       Tax     Total\n");
    printf("-------- ---- ----- --- --------- --------- ---------\n");
    printf("First    %-4c %5.2lf %3d %9.4lf %9.4lf %9.4lf\n", firstCustomerSize, priceSmall, firstCustomerQty,
        ((double)firstCustomerSubTotal / 100), ((double)firstCustomerTaxes / 100), ((double)firstCustomerTotal / 100));
    printf("Second   %-4c %5.2lf %3d %9.4lf %9.4lf %9.4lf\n", secondCustomerSize, priceMedium, secondCustomerQty,
        ((double)secondCustomerSubTotal / 100), ((double)secondCustomerTaxes / 100), ((double)secondCustomerTotal / 100));
    printf("Third    %-4c %5.2lf %3d %9.4lf %9.4lf %9.4lf\n", thirdCustomerSize, priceLarge, thirdCustomerQty,
        ((double)thirdCustomerSubTotal / 100), ((double)thirdCustomerTaxes / 100), ((double)thirdCustomerTotal / 100));
    printf("-------- ---- ----- --- --------- --------- ---------\n");
    printf("%33.4lf %9.4lf %9.4lf\n\n", subTotal, taxes, total);

    // Printing out coin-based results, to showcase calculation precision.
    printf("Daily commercial revenue represented by coins\n"
        "===============================================\n\n");

    printf("Sales BEFORE tax\n"
        "Coin     Qty   Balance\n"
        "-------- --- ---------\n");
    printf("%22.4lf\n", subTotal);

    balance = (int)((subTotal + 0.005) * 100);

    coins = balance / 200;
    balance = balance % 200;

    printf("Toonies  %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 100;
    balance = balance % 100;

    printf("Loonies  %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 25;
    balance = balance % 25;

    printf("Quarters %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 10;
    balance = balance % 10;

    printf("Dimes    %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 5;
    balance = balance % 5;

    printf("Nickels  %3d %9.4lf\n", coins, (double)(balance / 100.0));
    
    coins = balance / 1;
    balance = balance % 1;

    printf("Pennies  %3d %9.4lf\n\n", coins, (double)(balance / 100.0));

    average = subTotal / (firstCustomerQty + secondCustomerQty + thirdCustomerQty);

    printf("Average cost/shirt: $%.4lf\n\n", average);

    printf("Sales AFTER tax\n"
        "Coin     Qty   Balance\n"
        "-------- --- ---------\n");
    printf("%22.4lf\n", total);

    balance = (int)((total + 0.005) * 100);

    coins = balance / 200;
    balance = balance % 200;

    printf("Toonies  %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 100;
    balance = balance % 100;

    printf("Loonies  %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 25;
    balance = balance % 25;

    printf("Quarters %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 10;
    balance = balance % 10;

    printf("Dimes    %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 5;
    balance = balance % 5;

    printf("Nickels  %3d %9.4lf\n", coins, (double)(balance / 100.0));

    coins = balance / 1;
    balance = balance % 1;

    printf("Pennies  %3d %9.4lf\n\n", coins, (double)(balance / 100.0));

    average = total / (firstCustomerQty + secondCustomerQty + thirdCustomerQty);

    printf("Average cost/shirt: $%.4lf\n", average);

    return 0;
}