#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "DataGenerator.h"
#include "Sort.h"

using namespace std;

void chooseAlgorithm(const string& algorithm, int* data, int dataSize, long long& comparisions) {
    if (algorithm == "selection-sort") {
        SelectionSort(data, dataSize, comparisions);
    } else if (algorithm == "insertion-sort") {
        InsertionSort(data, dataSize, comparisions);
    } else if (algorithm == "bubble-sort") {
        BubbleSort(data, dataSize, comparisions);
    } else if (algorithm == "heap-sort") {
        HeapSort(data, dataSize, comparisions);
    } else if (algorithm == "merge-sort") {
        MergeSort(data, 0, dataSize - 1, comparisions);
    } else if (algorithm == "quick-sort") {
        QuickSort(data, 0, dataSize - 1, comparisions);
    } else if (algorithm == "radix-sort") {
        RadixSort(data, dataSize, comparisions);
    } else {
        cout << "Unknown sorting algorithm!" << endl;
        delete[] data;
        exit(1);
    }
}

// [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]
//     0             1     2            3                4
void Command1(int argc, char *argv[])
{
    string algorithm = argv[2], fileName = argv[3];
    fstream fin;
    fin.open(fileName);
    if (!fin.is_open())
    {
        cout << "Error Opening File: " << fileName;
        exit(1);
    }

    ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open())
    {
        cout << "Error Opening File: ";
        exit(1);
    }

    string Input;
    getline(fin, Input);
    int dataSize = stoi(Input);

    int* data = new int[dataSize];

    fout << dataSize << endl;

    getline(fin, Input);
    stringstream ss(Input);
    string temp;
    for(int i = 0; i < dataSize; i++){
        ss >> temp;
        data[i] = stoi(temp);
    }

    long long comparisions = 0;
    clock_t begin = clock();
    chooseAlgorithm(algorithm, data, dataSize, comparisions);
    clock_t end = clock();
    double timeRun = (double)(end-begin)/CLOCKS_PER_SEC;

    cout << "ALGORITHM MODE\n";
    cout << algorithm << '\n';
    cout << "Input file: " << fileName << '\n';
    cout << "Input Size: " << dataSize << '\n';
    cout << "- - - - - - - - - - - - - - - - \n";
    string parameter = argv[4];
    if (parameter == "-both")
    {
        cout << "Running time: " << timeRun * 1000 << " ms\n";
        cout << "Comparisons: "  << comparisions << "\n";
    }
    else if (parameter == "-time")
    {
        cout << "Running time: " << timeRun * 1000 << " ms\n";
    }
    else if (parameter == "-comp")
    {
        cout << "Comparisons: " << comparisions << "\n";
    }

    for (int i = 0; i < dataSize; i++){
        fout << data[i] << " ";
    }

    fin.close();
    fout.close();
    delete[] data;
}

// [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
void Command2(int argc, char *argv[])
{
    string algorithm = argv[2];
    int dataSize = atoi(argv[3]);

    string inputOrder = argv[4];
    int *data = new int[dataSize];

    if(inputOrder == "-rand"){
        GenerateRandomData(data, dataSize);
    }else if(inputOrder == "-nsorted"){
        GenerateNearlySortedData(data, dataSize);
    }else if(inputOrder == "-sorted"){
        GenerateSortedData(data, dataSize);
    }else if(inputOrder == "-rev"){
        GenerateReverseData(data, dataSize);
    }else{
        cout << "Wrong input order!" << endl;
        exit(1);
    }
    
    long long comparisions = 0;

    //Ghi file đầu vào
    ofstream fin;
    fin.open("input.txt");
    if (!fin.is_open())
    {
        cout << "Error Opening File: ";
        exit(1);
    }
    fin << dataSize << endl;
    for (int i = 0; i < dataSize; i++){
        fin << data[i] << " ";
    }
    fin.close();

    clock_t begin = clock();
    chooseAlgorithm(algorithm, data, dataSize, comparisions);
    clock_t end = clock();
    double timeRun = (double)(end-begin)/CLOCKS_PER_SEC;

    cout << "ALGORITHM MODE\n";
    cout << algorithm << '\n';
    cout << "Input Size: " << dataSize << '\n';
    cout << "Input Order: " << inputOrder << '\n';
    cout << " - - - - - - - - - - - - - - - - \n";

    string parameter = argv[5];
    if (parameter == "-both")
    {
        cout << "Running time: " << timeRun * 1000 << " ms\n";
        cout << "Comparisons: " << comparisions << "\n";
    }
    else if (parameter == "-time")
    {
        cout << "Running time: " << timeRun * 1000 << " ms\n";
    }
    else if (parameter == "-comp")
    {
        cout << "Comparisons: " << comparisions << "\n";
    }

    //Ghi file đầu ra
    ofstream fout;
    fout.open("output.txt");
    if (!fout.is_open())
    {
        cout << "Error Opening File: ";
        exit(1);
    }
    fout << dataSize << endl;
    for (int i = 0; i < dataSize; i++){
        fout << data[i] << " ";
    }
    fout.close();

    delete[] data;
}

void Command3(int argc, char *argv[])
{
    string algorithm = argv[2];
    string parameter = argv[4];
    int dataSize = atoi(argv[3]);

    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << algorithm << '\n';
    cout << "Input size: " << dataSize << '\n' << '\n';

    vector<string>  dataArrangement = {"Randomrize" , "Nearly Sorted" , "Sorted", "Reversed"};
    int **data = new int* [4];
    long long comparisions = 0;

    for(int i = 0; i < 4; ++i){

        data[i] = new int[dataSize];
        GenerateData(data[i], dataSize, i);
        comparisions = 0;

        //Ghi file đầu vào
        stringstream ss;
        ss << "input_" << i + 1 << ".txt";
        string fileName = ss.str();
        ofstream fin;
        fin.open(fileName);
        if (!fin.is_open())
        {
            cout << "Error Opening File: ";
            exit(1);
        }
        fin << dataSize << endl;
        for (int j = 0; j < dataSize; j++){
            fin << data[i][j] << " ";
        }
        fin.close();

        clock_t begin = clock();

        chooseAlgorithm(algorithm, data[i], dataSize, comparisions);

        clock_t end = clock();
        double timeRun = (double)(end-begin)/CLOCKS_PER_SEC;

        cout << "Input Order: " << dataArrangement[i] << '\n';
        cout << "--------------------------------------\n";
        
        if (parameter == "-both")
        {
            cout << "Running time: " << timeRun * 1000 << " ms\n";
            cout << "Comparisons: "  << comparisions << "\n";
        }
        else if (parameter == "-time")
        {
            cout << "Running time: " << timeRun * 1000 << " ms\n";
        }
        else if (parameter == "-comp")
        {
            cout << "Comparisons:" << comparisions  <<"\n";
        }
        cout << "\n";
    }
    
    for(int i = 0; i < 4; i++)
        delete data[i];
    delete []data;
}

void runSortingAlgorithm(int argc, char *argv[])
{
    int inputType = atoi(argv[3]);
    //cout << inputType << endl << endl;
    if (argc == 5 && inputType == 0)
        Command1(argc, argv);
    else if (argc == 5 && inputType != 0)
        Command3(argc, argv);
    else if (argc == 6)
        Command2(argc, argv);
    else
        return;
}

void Command4(int agrc, char *agrv[])
{
    // Add your implementation for Command4 if needed
    string algorithm1 = agrv[2];  
    string algorithm2 = agrv[3]; 
    string fileName   = agrv[4];

    fstream reader(fileName);

    if (!reader.is_open())
    {
        cout << "Error Opening File: " << fileName;
        exit(1);
    }

    string Input;
    getline(reader, Input);
    int dataSize = stoi(Input);

    int* data = new int[dataSize];
    int* dataTemp = new int[dataSize];

    getline(reader, Input);
    stringstream ss(Input);
    string temp;
    for(int i = 0; i < dataSize; i++){
        ss >> temp;
        data[i] = stoi(temp);
        dataTemp[i] = data[i];
    }


    //algorithm1
    clock_t begin1 = clock();
    long long comparisions1 = 0;
    chooseAlgorithm(algorithm1, data, dataSize, comparisions1);
    clock_t end1 = clock();
    float timeRun1 = (float)(end1-begin1)/CLOCKS_PER_SEC;

   //algorithm2
   for(int i = 0; i < dataSize; i++){
        data[i] = dataTemp[i];
    }
    clock_t begin2 = clock();
    long long comparisions2 = 0;
    chooseAlgorithm(algorithm2, data, dataSize, comparisions2);
    clock_t end2 = clock();
    float timeRun2 = (float)(end2-begin2)/CLOCKS_PER_SEC;

    //Console output:
    cout <<"COMPARE MODE" << endl
        << "Algorithm: " << algorithm1 << " | " << algorithm2 << endl
        << "Input file: " << fileName << endl
        << "Input size: " << dataSize << endl
        << "---------------------------" << endl;
    
    cout << "Running time: " << timeRun1 * 1000 << "ms | " << timeRun2 * 1000 << "ms"<< endl
         << "comparision: " << comparisions1 << " | " << comparisions2 << endl;

    //system("pause");
    delete[] data;
    delete[] dataTemp;
}

//       0          1     2              3            4            5
//[Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
void Command5(int agrc, char *agrv[])
{
    string algorithm1 = agrv[2];  
    string algorithm2 = agrv[3];
    int dataSize = stoi(agrv[4]);
    string inputOrder = agrv[5];

    int* a = new int[dataSize];

    if(inputOrder == "-rand"){
        GenerateRandomData(a, dataSize);
    }else if(inputOrder == "-nsorted"){
        GenerateNearlySortedData(a, dataSize);
    }else if(inputOrder == "-sorted"){
        GenerateSortedData(a, dataSize);
    }else if(inputOrder == "-rev"){
        GenerateReverseData(a, dataSize);
    }else{
        cout << "Wrong input order!" << endl;
        exit(1);
    }

    int* data = new int[dataSize];
    for(int i = 0; i < dataSize; i++){
        data[i] = a[i];
    }

    //Ghi file đầu vào
    ofstream fin;
    fin.open("input.txt");
    if (!fin.is_open())
    {
        cout << "Error Opening File: ";
        exit(1);
    }
    fin << dataSize << endl;
    for (int i = 0; i < dataSize; i++){
        fin << data[i] << " ";
    }
    fin.close();
   
    //algorithm1
    clock_t begin1 = clock();
    long long comparisions1 = 0;

    chooseAlgorithm(algorithm1, data, dataSize, comparisions1);
    clock_t end1 = clock();
    float timeRun1 = (float)(end1-begin1)/CLOCKS_PER_SEC;

    //algorithm2
    //reset lai mang data
    for(int i = 0; i < dataSize; i++){
        data[i] = a[i];
    }
   
    clock_t begin2 = clock();
    long long comparisions2 = 0;

    chooseAlgorithm(algorithm2, data, dataSize, comparisions2);
    clock_t end2 = clock();
    float timeRun2 = (float)(end2-begin2)/CLOCKS_PER_SEC;

    //Console output:
    cout <<"COMPARE MODE" << endl
        << "Algorithm: " << algorithm1 << " | " << algorithm2 << endl
        << "Input size: " << dataSize << endl
        << "input order: " << inputOrder << endl
        << "---------------------------" << endl;
    
    cout << "Running time: " << timeRun1 * 1000 << "ms | " << timeRun2 * 1000 << "ms" << endl
         << "comparision: " << comparisions1 << " | " << comparisions2 << endl;

    delete[]a;
    delete[]data;

}

void compareSortingAlgorithms(int argc, char *argv[])
{
    if(argc == 5){
        Command4(argc, argv);
    }
    else if(argc == 6){
        Command5(argc, argv);
    }else cout << "Unknown mode!" << endl;
}

int main(int argc, char *argv[])
{   
    string mode = argv[1];
    if (mode == "-a")
    {
        runSortingAlgorithm(argc, argv);
    }
    else if (mode == "-c")
    {
        compareSortingAlgorithms(argc, argv);
    }
    else
    {
        cout << "Unknown mode!" << endl;
        return 1;
    }

    system("pause");
    return 0;
}