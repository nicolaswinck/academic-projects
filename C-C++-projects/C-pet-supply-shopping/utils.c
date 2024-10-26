#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "utils.h"

// ============ FUNCTIONS ============
int getIntPositive(int* positiveNum)
{
	// Local variable to pass the value.
	int userNum;

	// User input validation for positive integer number.
	do {
		scanf("%d", &userNum);

		if (userNum < 1)
		{
			printf("ERROR: Enter a positive value: ");
		}

	} while (userNum < 1);

	// Return 1: assigning the value to the pointer argument.
	if (positiveNum != NULL)
	{
		*positiveNum = userNum;
	}

	// Return 2: returning the value.
	return userNum;
}

double getDoublePositive(double* positiveNum)
{
	// Local variable to pass the value.
	double userNum;

	// User input validation for positive double number.
	do {
		scanf("%lf", &userNum);

		if (userNum <= 0)
		{
			printf("ERROR: Enter a positive value: ");
		}

	} while (userNum <= 0);

	// Return 1: assigning the value to the pointer argument.
	if (positiveNum != NULL)
	{
		*positiveNum = userNum;
	}

	// Return 2: returning the value.
	return userNum;
}


void openingMessage(const int userProductNum)
{
	// Displaying the opening message to the screen.
	printf("Cat Food Cost Analysis\n"
		"======================\n\n");
	printf("Enter the details for %d dry food bags of product "
		"data for analysis.\n", MAX_PRODUCTS);
	printf("NOTE: A 'serving' is %dg\n\n", NUM_GRAMS);
}


struct CatFoodInfo getCatFoodInfo(const int productsQtty)
{
	// Defining object and allocating memory.
	struct CatFoodInfo cfInfo = { 0 };

	// Displaying input indications for each item (+ 1, since it's zero-based).
	printf("Cat Food Product #%d\n", productsQtty + 1);
	printf("--------------------\n");

	printf("SKU           : ");
	getIntPositive(&cfInfo.sku);

	printf("PRICE         : $");
	getDoublePositive(&cfInfo.price);

	printf("WEIGHT (LBS)  : ");
	getDoublePositive(&cfInfo.weightPounds);

	printf("CALORIES/SERV.: ");
	getIntPositive(&cfInfo.calPerServing);

	putchar('\n');

	return cfInfo;
}


void displayCatFoodHeader(void)
{
	printf("SKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
}


void displayCatFoodData(const int sku, const double* price,
	const int calPerServing, const double* weightPounds)
{
	// Displaying information for each user input record.

	printf("%07d %10.2lf %10.1lf %8d\n",
		sku, *price, *weightPounds, calPerServing);
}


double convertLbsKg(const double* pounds, double* kgResult)
{
	// Making the calculation through the local variable.
	double userNum = *pounds / NUM_POUNDS;

	// Return 1: assigning the value to the pointer argument.
	if (kgResult != NULL)
	{
		*kgResult = userNum;
	}

	// Return 2: returning the value.
	return userNum;
}


int convertLbsG(const double* pounds, int* gramsResult)
{
	// Making the calculation through the local variable.
	// Applying modularity using previous function.
	int userNum = convertLbsKg(pounds, NULL) * 1000;

	// Return 1: assigning the value to the pointer argument.
	if (gramsResult != NULL)
	{
		*gramsResult = userNum;
	}

	// Return 2: returning the value.
	return userNum;
}

void convertLbs(const double* pounds, double* kgResult, int* gramsResult)
{
	// Making the calculation through local variables.
	// Applying modularity using previous functions.
	double lbsToKilos = convertLbsKg(pounds, NULL);
	int lbsToGrams = convertLbsG(pounds, NULL);

	// Assigning values via address.
	*kgResult = lbsToKilos;
	*gramsResult = lbsToGrams;
}


double calculateServings(const int servSizeGrams, const int totalGrams,
	double* numOfServs)
{
	// Making the calculation through local variables.
	double userNum = (double)totalGrams / servSizeGrams;

	// Return 1: assigning the value to the pointer argument.
	if (numOfServs != NULL)
	{
		*numOfServs = userNum;
	}

	// Return 2: returning the value.
	return userNum;
}


double calculateCostPerServing(const double* price, const double* numOfServs,
	double* costPerServ)
{
	// Making the calculation through local variables.
	double userNum = *price / *numOfServs;

	// Return 1: assigning the value to the pointer argument.
	if (costPerServ != NULL)
	{
		*costPerServ = userNum;
	}

	// Return 2: returning the value.
	return userNum;
}


double calculateCostPerCal(const double* price, const double* numOfCals,
	double* costPerCal)
{
	// Making the calculation through local variables.
	double userNum = *price / *numOfCals;

	// Return 1: assigning the value to the pointer argument.
	if (costPerCal != NULL)
	{
		*costPerCal = userNum;
	}

	// Return 2: returning the value.
	return userNum;
}


struct ReportData calculateReportData(struct CatFoodInfo cfInfo)
{
	// Initializing the structure to a safe empty space (assigning to zero).
	// Local variable for calculating the total of calories.
	struct ReportData repData = { 0 };
	double totalCals;

	// Directly assigning the first 4 members using the other structure.
	repData.sku = cfInfo.sku;
	repData.price = cfInfo.price;
	repData.weightPounds = cfInfo.weightPounds;
	repData.calPerServing = cfInfo.calPerServing;

	// Calculating the other members using the calculation functions.
	repData.weightKilos =
		convertLbsKg(&repData.weightPounds, &repData.weightKilos);
	repData.weightGrams =
		convertLbsG(&repData.weightPounds, &repData.weightGrams);
	repData.numTotalServings =
		calculateServings(NUM_GRAMS, repData.weightGrams, &repData.numTotalServings);

	// Calculating the total of calories and assigning.
	totalCals = repData.calPerServing * repData.numTotalServings;

	repData.costPerServing = calculateCostPerServing(&repData.price,
		&repData.numTotalServings, &repData.costPerServing);
	repData.costCalPerServing = calculateCostPerCal(&repData.price,
		&totalCals, &repData.costCalPerServing);

	// Returning the structure.
	return repData;
}


void displayReportHeader(void)
{
	printf("Analysis Report (Note: Serving = %dg)\n", NUM_GRAMS);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}


void displayReportData(const struct ReportData repData, const int cheapestOption)
{
	// Displaying the formatted values in the given order.
	printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf",
		repData.sku,
		repData.price,
		repData.weightPounds,
		repData.weightKilos,
		repData.weightGrams,
		repData.calPerServing,
		repData.numTotalServings,
		repData.costPerServing,
		repData.costCalPerServing);
}


void displayFinalAnalysis(const struct CatFoodInfo cfInfo)
{
	// Displaying opening message.
	printf("Final Analysis\n"
		"--------------\n"
		"Based on the comparison data, the PURRR-fect economical option is:\n");

	// Accessing data details.
	printf("SKU:%07d Price: $%5.2lf\n\n", cfInfo.sku, cfInfo.price);

	// Closing message.
	printf("Happy shopping!\n");
}


// ============ STARTING POINT ============
void start(void)
{
	// Initializing arrays to a safe empty state.
	struct CatFoodInfo cfInfo[MAX_PRODUCTS] = { {0} };
	struct ReportData repData[MAX_PRODUCTS] = { {0} };

	// Declaring variables.
	int i, cheapIdx = 0;
	double cheapest;

	// Displaying opening message.
	openingMessage(MAX_PRODUCTS);

	// Getting user inputs up to the maximum number established.
	// Assigning array's elements within the structure's members.
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		cfInfo[i] = getCatFoodInfo(i);
		repData[i] = calculateReportData(cfInfo[i]);
	}

	// Displaying the table heather.
	displayCatFoodHeader();

	// Printing parallel arrays to organize information.
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		displayCatFoodData(cfInfo[i].sku, &cfInfo[i].price,
			cfInfo[i].calPerServing, &cfInfo[i].weightPounds);
	}

	// Fetching the best deal for the user (cheapest product).
	cheapest = repData[0].costPerServing;

	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		if (repData[i].costPerServing <= cheapest)
		{
			cheapest = repData[i].costPerServing;

			// Storing the index of the cheapest option.
			cheapIdx = i;
		}
	}

	putchar('\n');

	// Displaying the table heather.
	displayReportHeader();

	// Displaying and organizing data.
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		displayReportData(repData[i], cheapIdx);

		// Finding and pointing the best option for the user.
		if (cheapIdx == i)
		{
			printf(" ***\n");
		}
		else
		{
			putchar('\n');
		}
	}

	putchar('\n');

	// Displaying data and finishing the application.
	for (i = 0; i < MAX_PRODUCTS; i++)
	{
		if (i == cheapIdx)
		{
			displayFinalAnalysis(cfInfo[i]);
		}
	}
}