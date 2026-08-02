#include "utils.h"
#include <stdlib.h>

/*----------------------------------------------------------
                    Mathematical Functions
----------------------------------------------------------*/

double reciprocal(double n) {
    return 1.0 / n;
}

double logarithm(double n) {
    return log2(n);
}

double fractionalPolynomial(double n) {
    return pow(n, 0.51);
}

double sqrt12(double n) {
    return 12.0 * sqrt(n);
}

double sqrt50(double n) {
    return 50.0 * sqrt(n);
}

double nLogN(double n) {
    return n * log2(n);
}

double quadratic1(double n) {
    return n * n - 324.0;
}

double quadratic2(double n) {
    return 100.0 * n * n + 6.0 * n;
}

double cubic(double n) {
    return 2.0 * pow(n, 3);
}

double linearHuge(double n) {
    return 4294967296.0 * n;       // 2^32 × n
}

double superPolynomial(double n) {
    return pow(n, log2(n));
}

double exponential(double n) {
    return pow(3.0, n);
}


/*----------------------------------------------------------
                    Function Array
----------------------------------------------------------*/

Function functions[FUNCTION_COUNT] =
{
    {"1 / n",             "Reciprocal",              reciprocal},
    {"log2(n)",           "Logarithmic",             logarithm},
    {"n^0.51",            "Fractional Polynomial",   fractionalPolynomial},
    {"12*sqrt(n)",        "Square Root",             sqrt12},
    {"50*sqrt(n)",        "Square Root",             sqrt50},
    {"n*log2(n)",         "Linearithmic",            nLogN},
    {"2^32 * n",          "Linear",                  linearHuge},
    {"n^2 - 324",         "Quadratic",               quadratic1},
    {"100n^2 + 6n",       "Quadratic",               quadratic2},
    {"2n^3",              "Cubic",                   cubic},
    {"n^(log2 n)",        "Super Polynomial",        superPolynomial},
    {"3^n",               "Exponential",             exponential}
};


/*----------------------------------------------------------
                    Console Functions
----------------------------------------------------------*/

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader()
{
    printf("===============================================================\n");
    printf("          ORDER OF GROWTH ANALYZER (DAA LAB)\n");
    printf("===============================================================\n\n");
}

void printGrowthTable()
{
    printf("Functions arranged in increasing order of growth:\n\n");

    printf("%-5s %-25s %-25s\n",
           "No", "Function", "Growth Type");

    printf("---------------------------------------------------------------\n");

    for(int i = 0; i < FUNCTION_COUNT; i++)
    {
        printf("%-5d %-25s %-25s\n",
               i + 1,
               functions[i].name,
               functions[i].growth);
    }

    printf("---------------------------------------------------------------\n");
}

void printMenu()
{
    printf("\n");
    printf("0  -> Plot Combined Graph\n");

    for(int i = 0; i < FUNCTION_COUNT; i++)
    {
        printf("%2d -> Plot %-20s\n",
               i + 1,
               functions[i].name);
    }

    printf("13 -> About\n");
    printf("14 -> Exit\n");
}

void printAbout()
{
    printf("\n====================================\n");
    printf("Order of Growth Analyzer\n");
    printf("Language : C\n");
    printf("Graph    : GNUPlot\n");
    printf("Compiler : GCC\n");
    printf("====================================\n");
}


/*----------------------------------------------------------
                    Data Generation
----------------------------------------------------------*/

void generateCombinedData()
{
    FILE *fp = fopen("output/functions.dat", "w");

    if(fp == NULL)
    {
        printf("Cannot create output file.\n");
        return;
    }

    for(int n = START_N; n <= END_N; n++)
    {
        fprintf(fp,"%d",n);

        for(int i = 0; i < FUNCTION_COUNT; i++)
        {
            fprintf(fp," %lf",functions[i].func((double)n));
        }

        fprintf(fp,"\n");
    }

    fclose(fp);
}

void generateSingleData(int index)
{
    FILE *fp = fopen("output/single.dat", "w");

    if(fp == NULL)
    {
        printf("Cannot create output file.\n");
        return;
    }

    for(int n = START_N; n <= END_N; n++)
    {
        fprintf(fp,
                "%d %lf\n",
                n,
                functions[index].func((double)n));
    }

    fclose(fp);

    printf("\nSelected Function : %s\n",
           functions[index].name);
}


/*----------------------------------------------------------
                    GNUPlot
----------------------------------------------------------*/

void plotCombinedGraph()
{
    system("gnuplot scripts/combined.gnu");
}

void plotSingleGraph()
{
    system("gnuplot scripts/single.gnu");
}