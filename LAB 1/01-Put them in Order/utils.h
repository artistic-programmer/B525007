#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <math.h>

#define FUNCTION_COUNT 12
#define START_N 2
#define END_N 30

// Structure representing one mathematical function
typedef struct
{
    const char *name;
    const char *growth;
    double (*func)(double);

} Function;


/*----------------------------------------------------------
                    Mathematical Functions
----------------------------------------------------------*/

double reciprocal(double n);
double logarithm(double n);
double fractionalPolynomial(double n);
double sqrt12(double n);
double sqrt50(double n);
double nLogN(double n);
double quadratic1(double n);
double quadratic2(double n);
double cubic(double n);
double linearHuge(double n);
double superPolynomial(double n);
double exponential(double n);


/*----------------------------------------------------------
                    Console Functions
----------------------------------------------------------*/

void clearScreen();
void printHeader();
void printGrowthTable();
void printMenu();
void printAbout();


/*----------------------------------------------------------
                    Graph Functions
----------------------------------------------------------*/

void generateCombinedData();
void generateSingleData(int index);

void plotCombinedGraph();
void plotSingleGraph();


/*----------------------------------------------------------
                    Global Function Array
----------------------------------------------------------*/

extern Function functions[FUNCTION_COUNT];

#endif