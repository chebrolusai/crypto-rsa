#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <cmath>

using namespace std;

vector<long long int> parseKeyCsvLine(string csv_line)
{

    vector<long long int> result;

    bool commaFlag = false;

    long long int E = 0;
    long long int N = 0;

    for (int i = 0; i < csv_line.size(); i++)
    {
        if (csv_line[i] == ',')
        {
            commaFlag = true;
            continue;
        }

        if (!commaFlag)
        {
            E = E * 10 + (csv_line[i] - '0');
        }
        else
        {
            N = N * 10 + (csv_line[i] - '0');
        }
    }

    result.push_back(E);
    result.push_back(N);

    return result;
}

string getFirstLineFromFile(string &file_name)
{
    ifstream file(file_name);

    string line;

    getline(file, line);

    file.close();

    return line;
}