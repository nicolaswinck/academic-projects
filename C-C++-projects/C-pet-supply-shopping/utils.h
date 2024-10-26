// Macros for maximum number of products and the serving portion.
#define MAX_PRODUCTS 3
#define NUM_GRAMS 64
#define NUM_POUNDS 2.20462

// Structures.
struct CatFoodInfo
{
    int sku;
    double price;
    int calPerServing;
    double weightPounds;
};


struct ReportData
{
    int sku;
    double price;
    int calPerServing;
    double weightPounds;
    double weightKilos;
    int weightGrams;
    double numTotalServings;
    double costPerServing;
    double costCalPerServing;
};

// Functions.
int getIntPositive(int* positiveNum);

double getDoublePositive(double* positiveNum);

void openingMessage(const int userProductNum);

struct CatFoodInfo getCatFoodInfo(const int productsQtty);

void displayCatFoodHeader(void);

void displayCatFoodData(const int sku, const double* price,
    const int calPerServing, const double* weightPounds);

double convertLbsKg(const double* pounds, double* kgResult);

int convertLbsG(const double* pounds, int* gramsResult);

void convertLbs(const double* pounds, double* kgResult, int* gramsResult);

double calculateServings(const int servSizeGrams, const int totalGrams, double* numOfServs);

double calculateCostPerServing(const double* price, const double* numOfServs, double* costPerServ);

double calculateCostPerCal(const double* price, const double* numOfCals, double* costPerCal);

struct ReportData calculateReportData(struct CatFoodInfo cfInfo);

void displayReportHeader(void);

void displayReportData(const struct ReportData repData, const int cheapestOption);

void displayFinalAnalysis(const struct CatFoodInfo cfInfo);

void start(void);