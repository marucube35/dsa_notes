#include "cmd.h"

//Check if a string can convert to integer or not
bool isInteger(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}
//Check if a file exists or not
bool fileIsExist(string file)
{
    fstream f(file, ios::in);
    if (f.is_open())
    {
        f.close();
        return true;
    }
    cout << "File does not exist" << endl;
    f.close();
    return false;
}
//Get data from file to array
int *fileToArray(string filename, int &input_size)
{
    fstream f(filename, ios::in);

    string size;
    f >> size;
    input_size = stoi(size);
    int *arr = new int[input_size];

    for (int i = 0; i < input_size; i++)
    {
        string num;
        f >> num;
        if (num != " ")
        {
            arr[i] = stoi(num);
        }
    }

    f.close();
    return arr;
}
//write element in array to file
void arrayToFile(int *a, int n, string filename)
{
    fstream f(filename, ios::out);
    if (!f.is_open())
        return;

    f << n << endl;
    for (int i = 0; i < n; i++)
    {
        f << a[i] << " ";
    }

    f.close();
}
//Function to call the Command 1
bool checkAlgorithm(string alg, int a[], int n, string fileInput, string output_parameters)
{
    long long count_cmp = 0;
    chrono::duration<double, milli> runtime;
    runtime = algorithmSwitch(a, n, alg, count_cmp); //calculate the running time and count the comparisons of input algorithm
    arrayToFile(a,n,"output.txt");
    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << alg << endl;
    cout << "Input: " << fileInput << endl;
    cout << "Input size: " << n << endl;
    cout << "--------------------------------" << endl;
    //there kinds of output
    if (output_parameters == "-time")
    {
        cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
    }
    else if (output_parameters == "-comp")
    {
        cout << "Comparisions: " << count_cmp << endl;
    }
    else if (output_parameters == "-both")
    {
        cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
        cout << "Comparisions: " << count_cmp << endl;
    }
    else
    {
        cout << "Output parameter is undefined" << endl;
        return false;
    }
    return true;
}
//collection to calculate the running time and comparisons of all 11 algorithms
chrono::duration<double, milli> algorithmSwitch(int a[], int n, string algorithm, long long &count_cmp)
{
    if (algorithm == "selection-sort")
    {
        auto start = high_resolution_clock::now();
        selectionSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "insertion-sort")
    {
        auto start = high_resolution_clock::now();
        insertionSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "bubble-sort")
    {
        auto start = high_resolution_clock::now();
        bubbleSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "shaker-sort")
    {
        auto start = high_resolution_clock::now();
        shakerSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "shell-sort")
    {
        auto start = high_resolution_clock::now();
        shellSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "heap-sort")
    {
        auto start = high_resolution_clock::now();
        heapSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "merge-sort")
    {
        auto start = high_resolution_clock::now();
        mergeSortExperiment(a, 0, n - 1, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "quick-sort")
    {
        auto start = high_resolution_clock::now();
        quickSortExperiment(a, 0, n - 1, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "counting-sort")
    {
        auto start = high_resolution_clock::now();
        countingSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "radix-sort")
    {
        auto start = high_resolution_clock::now();
        radixSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    else if (algorithm == "flash-sort")
    {
        auto start = high_resolution_clock::now();
        flashSortExperiment(a, n, count_cmp);
        auto stop = high_resolution_clock::now();
        auto runtime = stop - start;
        return runtime;
    }
    cout << "The algorithm is undefined!" << endl;
}

bool sortAllArrangement(string alg, int amount, string output_parameters)
{
    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << alg << endl;
    cout << "Input size: " << amount << endl;
    for (int i = 0; i < 4; i++)
    {
        long long count_cmp = 0;
        int *a = new int[amount];
        cout << "Input order: ";
        if (i == 0)
        {
            cout << "Randomize" << endl;
            cout << "--------------------------------" << endl;
            GenerateRandomData(a, amount);
            auto runtime = algorithmSwitch(a, amount, alg, count_cmp);
            arrayToFile(a,amount,"input_1.txt");
            if (output_parameters == "-time")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
            }
            else if (output_parameters == "-comp")
            {
                cout << "Comparisions: " << count_cmp << endl;
            }
            else if (output_parameters == "-both")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
                cout << "Comparisions: " << count_cmp << endl;
            }
            else
            {
                cout << "Output parameter is undefined" << endl;
                return false;
            }
        }
        else if (i == 1)
        {
            cout << "Nearly Sorted" << endl;
            cout << "--------------------------------" << endl;
            GenerateNearlySortedData(a, amount);
            auto runtime = algorithmSwitch(a, amount, alg, count_cmp);
            arrayToFile(a,amount,"input_2.txt");
            if (output_parameters == "-time")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
            }
            else if (output_parameters == "-comp")
            {
                cout << "Comparisions: " << count_cmp << endl;
            }
            else if (output_parameters == "-both")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
                cout << "Comparisions: " << count_cmp << endl;
            }
            else
            {
                cout << "Output parameter is undefined" << endl;
                return false;
            }
        }
        else if (i == 2)
        {
            cout << "Sorted" << endl;
            cout << "--------------------------------" << endl;
            GenerateSortedData(a, amount);
            auto runtime = algorithmSwitch(a, amount, alg, count_cmp);
            arrayToFile(a,amount,"input_3.txt");
            if (output_parameters == "-time")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
            }
            else if (output_parameters == "-comp")
            {
                cout << "Comparisions: " << count_cmp << endl;
            }
            else if (output_parameters == "-both")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
                cout << "Comparisions: " << count_cmp << endl;
            }
            else
            {
                cout << "Output parameter is undefined" << endl;
                return false;
            }
        }
        else if (i == 3)
        {
            cout << "Reversed" << endl;
            cout << "--------------------------------" << endl;
            GenerateReverseData(a, amount);
            auto runtime = algorithmSwitch(a, amount, alg, count_cmp);
            arrayToFile(a,amount,"input_4.txt");
            if (output_parameters == "-time")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
            }
            else if (output_parameters == "-comp")
            {
                cout << "Comparisions: " << count_cmp << endl;
            }
            else if (output_parameters == "-both")
            {
                cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
                cout << "Comparisions: " << count_cmp << endl;
            }
            else
            {
                cout << "Output parameter is undefined" << endl;
                return false;
            }
        }
    }
    return true;
}
//compare time and number of comparisons of two algorithms
void runCompare(string first_algorithm, string second_algorithm, int *a, int n)
{
    long long first_count_compare = 0;
    auto first_runtime = algorithmSwitch(a, n, first_algorithm, first_count_compare);
    long long second_count_compare = 0;
    auto second_runtime = algorithmSwitch(a, n, second_algorithm, second_count_compare);
    cout << "Running time: ";
    cout << chrono::duration<double, milli>(first_runtime).count() << " (ms)";
    cout << " | ";
    cout << chrono::duration<double, milli>(second_runtime).count() << " (ms)";
    cout << endl;
    cout << "Comparisions: ";
    cout << first_count_compare;
    cout << " | ";
    cout << second_count_compare;
    cout << endl;
}

int *createData(string data_order, int data_size)
{
    int *arr = new int[data_size];
    string file = "input.txt";
    if (data_order == "-rand")
    {
        GenerateRandomData(arr, data_size);
        arrayToFile(arr, data_size, file);
    }
    else if (data_order == "-nsorted")
    {
        GenerateNearlySortedData(arr, data_size);
        arrayToFile(arr, data_size, file);
    }
    else if (data_order == "-sorted")
    {
        GenerateSortedData(arr, data_size);
        arrayToFile(arr, data_size, file);
    }
    else if (data_order == "-rev")
    {
        GenerateReverseData(arr, data_size);
        arrayToFile(arr, data_size, file);
    }
    else
    {
        cout << "Data order is invalid! " << endl;
        return NULL;
    }
    return arr;
}

bool runAlgorithm(string input_order, int input_size, string algorithm, string output_param)
{
    int *data = createData(input_order, input_size);
    long long count_comparison = 0;
    auto runtime = algorithmSwitch(data, input_size, algorithm, count_comparison);
    arrayToFile(data,input_size,"output.txt");
    if (output_param == "-time")
    {
        cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
    }
    else if (output_param == "-comp")
    {
        cout << "Comparisions: " << count_comparison << endl;
    }
    else if (output_param == "-both")
    {
        cout << "Running time: " << chrono::duration<double, milli>(runtime).count() << " (ms)" << endl;
        cout << "Comparisions: " << count_comparison << endl;
    }
    else
    {
        cout << "Output parameter is undefined" << endl;
        return false;
    }
    return true;
}
// The main process of command line
bool commandLineProcess(int argc, const char *argv[])
{
    //number of arguments is either 5 or 6
    if (argc != 5 && argc != 6)
    {
        cout << "Cannot find option with these arguments" << endl;
        return false;
    }
    else
    {
        //program need 5 arguments
        if (argc == 5)
        {
            string mode = argv[1];
            if (mode == "-a")
            {
                string algorithms = argv[2];
                string input = argv[3];
                string output_mode = argv[4];
                //Command 1
                if (!isInteger(input))
                {
                    if (fileIsExist(input))
                    {
                        int input_size = 0;
                        int *array = fileToArray(input, input_size); //get data from file stored as array
                        //running the single sort option
                        checkAlgorithm(algorithms, array, input_size, input, output_mode);
                    }
                }
                //Command 3
                else
                {
                    //running all sort algorithms with 4 kind of Order
                    sortAllArrangement(algorithms, stoi(input), output_mode);
                }
            }
            //Command 4
            else if (mode == "-c")
            {
                cout << "COMPARE MODE: " << endl;
                string first_algo = argv[2];
                string second_algo = argv[3];
                string input_file = argv[4];
                if (fileIsExist(input_file))
                {
                    int size;
                    int *a = fileToArray(input_file, size);
                    cout << "Algorithm: " << first_algo << " | " << second_algo << endl;
                    cout << "Input file: " << input_file << endl;
                    cout << "Input size: " << size << endl;
                    runCompare(first_algo, second_algo, a, size);
                }
            }
            else
            {
                cout << "Wrong argument: " << mode << endl;
            }
        }
        else
        {
            string mode = argv[1];
            //Command 2
            if (mode == "-a")
            {
                cout << "ALGORITHM MODE: " << endl;
                string algorithm = argv[2];
                string input_size = argv[3];
                string input_order = argv[4];
                string output_param = argv[5];
                cout << "Algorithms: " << algorithm << endl;
                cout << "Input size: " << input_size << endl;
                cout << "Input order: " << input_order << endl;
                cout << "--------------------------------" << endl;
                runAlgorithm(input_order, stoi(input_size), algorithm, output_param);
            }
            //Command 5
            else if (mode == "-c")
            {
                string first_algo = argv[2];
                string second_algo = argv[3];
                int input_size = stoi(argv[4]);
                string input_order = argv[5];
                int *a = createData(input_order, input_size);

                cout << "COMPARE MODE" << endl;
                cout << "Algorithm: " << first_algo << " | " << second_algo << endl;
                cout << "Input size: " << input_size << endl;
                cout << "Input order: " << input_order << endl;
                cout << "-----------------" << endl;

                runCompare(first_algo, second_algo, a, input_size);
            }
            else
            {
                cout << "Wrong argument: " << mode << endl;
            }
        }
    }
    return true;
}
