#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <cmath>

using namespace std;

vector<long long int> parseKeyCsvLine(string csv_line)
{
    /**
     * This function parses a csv line with 2 comma separated values.
     * This function is very specific for the private and public key file
     */

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
    /**
     * This function returns the first line from a file
     */

    ifstream file(file_name);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file '" << file_name << "'" << std::endl;
        return "";
    }

    string line;

    getline(file, line);

    file.close();

    return line;
}

vector<string> readFile(string &file_name)
{

    /**
     * This function reads an entire file and
     * returns its content in  vector of type string
     */

    vector<string> result;

    ifstream file(file_name);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file '" << file_name << "'" << std::endl;
        return result;
    }

    string line;
    while (std::getline(file, line))
    {
        result.push_back(line);
    }

    file.close();
    return result;
}

vector<long long int> parseEncryptedLine(string str)
{
    /**
     * This function parses a string using '?' as the delimiter
     * and returns a vector of type long long int.
     * This is a specific function only for parsing the encrypted file
     * created by this program
     */

    vector<long long int> result;

    long long int encryptedNumber = 0;

    for (int i = 0; i < str.size(); i++)
    {

        if (str[i] == '?')
        {
            result.push_back(encryptedNumber);
            encryptedNumber = 0;
            continue;
        }

        encryptedNumber = encryptedNumber * 10 + (str[i] - '0');
    }

    return result;
}