#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
    // Setting variables for quantities, shopping cart, and flags for escaping loops.
    int qtyApples, qtyBananas, qtyPeaches, qtyTomatoes, qtyCabbages,
        pickedProducts, continueShopping, cart = 0, shoppingAgain;

    // Adding items to shopping list.
    do {
        printf("Welcome to grocery shopping!\n"
            "===============================\n");

        do {
            printf("How many apples do you need? ");
            scanf("%d", &qtyApples);

            if (qtyApples < 0)
            {
                printf("ERROR: Enter a value greater or equal to 0.\n");
            }

        } while (qtyApples < 0);

        putchar('\n');

        do {
            printf("How many bananas do you need? ");
            scanf("%d", &qtyBananas);

            if (qtyBananas < 0)
            {
                printf("ERROR: Enter a value greater or equal to 0.\n");
            }

        } while (qtyBananas < 0);

        putchar('\n');

        do {
            printf("How many peaches do you need? ");
            scanf("%d", &qtyPeaches);

            if (qtyPeaches < 0)
            {
                printf("ERROR: Enter a value greater or equal to 0.\n");
            }

        } while (qtyPeaches < 0);

        putchar('\n');

        do {
            printf("How many tomatoes do you need? ");
            scanf("%d", &qtyTomatoes);

            if (qtyTomatoes < 0)
            {
                printf("ERROR: Enter a value greater or equal to 0.\n");
            }

        } while (qtyTomatoes < 0);

        putchar('\n');

        do {
            printf("How many cabbages do you need? ");
            scanf("%d", &qtyCabbages);

            if (qtyCabbages < 0)
            {
                printf("ERROR: Enter a value greater or equal to 0.\n");
            }

        } while (qtyCabbages < 0);

        putchar('\n');

        // Shopping for the products.
        printf("-----------------------------\n"
            "Time to do your shopping!\n"
            "-----------------------------\n\n");

        // The next loops check if the user picked as many items as needed.
        if (qtyApples > 0)
        {
            continueShopping = 0;

            do {
                printf("How many apples did you pick? ");
                scanf("%d", &pickedProducts);

                if (pickedProducts < 1)
                {
                    printf("ERROR: You must pick at least 1!\n");

                }

                else if (pickedProducts > 0)
                {
                    if (pickedProducts > qtyApples - cart)
                    {
                        printf("You picked too many. Only %d more apple(s) needed.\n",
                            qtyApples - cart);
                    }

                    else
                    {
                        cart += pickedProducts;

                        if (qtyApples - cart != 0)
                        {
                            printf("We still need some apples.\n");

                        }

                        else
                        {
                            printf("You're done with apples.\n\n");
                            cart = 0;
                            pickedProducts = 0;
                            continueShopping = 1;
                        }
                    }
                }

            } while (continueShopping == 0);
        }

        if (qtyBananas > 0)
        {
            continueShopping = 0;

            do {
                printf("How many bananas did you pick? ");
                scanf("%d", &pickedProducts);

                if (pickedProducts < 1)
                {
                    printf("ERROR: You must pick at least 1!\n");

                }

                else if (pickedProducts > 0)
                {
                    if (pickedProducts > qtyBananas - cart)
                    {
                        printf("You picked too many. Only %d more banana(s) needed.\n",
                            qtyBananas - cart);
                    }

                    else
                    {
                        cart += pickedProducts;

                        if (qtyBananas - cart != 0)
                        {
                            printf("We still need some bananas.\n");

                        }

                        else
                        {
                            printf("You're done with bananas.\n\n");
                            cart = 0;
                            pickedProducts = 0;
                            continueShopping = 1;
                        }
                    }
                }

            } while (continueShopping == 0);
        }

        if (qtyPeaches > 0)
        {
            continueShopping = 0;

            do {
                printf("How many peaches did you pick? ");
                scanf("%d", &pickedProducts);

                if (pickedProducts < 1)
                {
                    printf("ERROR: You must pick at least 1!\n");

                }

                else if (pickedProducts > 0)
                {
                    if (pickedProducts > qtyPeaches - cart)
                    {
                        printf("You picked too many. Only %d more peach(es) needed.\n",
                            qtyPeaches - cart);
                    }

                    else
                    {
                        cart += pickedProducts;

                        if (qtyPeaches - cart != 0)
                        {
                            printf("We still need some peaches.\n");

                        }

                        else
                        {
                            printf("You're done with peaches.\n\n");
                            cart = 0;
                            pickedProducts = 0;
                            continueShopping = 1;
                        }
                    }
                }

            } while (continueShopping == 0);
        }

        if (qtyTomatoes > 0)
        {
            continueShopping = 0;

            do {
                printf("How many tomatoes did you pick? ");
                scanf("%d", &pickedProducts);

                if (pickedProducts < 1)
                {
                    printf("ERROR: You must pick at least 1!\n");

                }

                else if (pickedProducts > 0)
                {
                    if (pickedProducts > qtyTomatoes - cart)
                    {
                        printf("You picked too many. Only %d more tomato(es) needed.\n",
                            qtyTomatoes - cart);
                    }

                    else
                    {
                        cart += pickedProducts;

                        if (qtyTomatoes - cart != 0)
                        {
                            printf("We still need some tomatoes.\n");

                        }

                        else
                        {
                            printf("You're done with tomatoes.\n\n");
                            cart = 0;
                            pickedProducts = 0;
                            continueShopping = 1;
                        }
                    }
                }

            } while (continueShopping == 0);
        }

        if (qtyCabbages > 0)
        {
            continueShopping = 0;

            do {
                printf("How many cabbages did you pick? ");
                scanf("%d", &pickedProducts);

                if (pickedProducts < 1)
                {
                    printf("ERROR: You must pick at least 1!\n");

                }

                else if (pickedProducts > 0)
                {
                    if (pickedProducts > qtyCabbages - cart)
                    {
                        printf("You picked too many. Only %d more cabbage(s) needed.\n",
                            qtyCabbages - cart);
                    }

                    else
                    {
                        cart += pickedProducts;

                        if (qtyCabbages - cart != 0)
                        {
                            printf("We still need some cabbages.\n");

                        }

                        else
                        {
                            printf("You're done with cabbages.\n\n");
                            cart = 0;
                            pickedProducts = 0;
                            continueShopping = 1;
                        }
                    }
                }

            } while (continueShopping == 0);
        }

        // Wrapping up and prompting for another shopping.
        printf("You've finished picking your items.\n\n");
        printf("Shopping again? (0=NO): ");
        scanf("%d", &shoppingAgain);

        putchar('\n');

    } while (shoppingAgain != 0);

    printf("You're done with your shopping list for today!\n");
    
    return 0;
}