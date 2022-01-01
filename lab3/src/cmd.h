#pragma once
#include "Sorting.h"
#include "Data.h"
//the definition of functions in "cmd.cpp"
bool isInteger(string str);
bool fileIsExist(string file);
int *fileToArray(string filename, int &input_size);
void arrayToFile(int *a, int n, string filename);
bool checkAlgorithm(string alg, int a[], int n, string fileInput, string output_parameters);
chrono::duration<double, milli> algorithmSwitch(int a[], int n, string algorithm, long long &count_cmp);
bool sortAllArrangement(string alg, int amount, string output_parameters);
void runCompare(string first_algorithm, string second_algorithm, int *a, int n);
int *createData(string data_order, int data_size);
bool runAlgorithm(string input_order, int input_size, string algorithm, string output_param);
bool commandLineProcess(int argc, const char *argv[]);
