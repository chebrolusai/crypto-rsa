#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <cmath>
#include "utility/string_parsing.cpp"
#include "utility/math_functions.cpp"

using namespace std;

bool fileExists(string &file_path)
{
    ifstream file(file_path);
    return file.is_open();
}

int main(int argc, char *argv[])
{

    if (argc != 5)
    {
        std::cerr << "Invalid number of arguments." << std::endl;
        exit(1);
    }

    if (strcmp(argv[1], "-m") != 0 || strcmp(argv[3], "-e") != 0)
    {
        cout << argv[1] << endl
             << argv[3];
        std::cerr << "The format accepted is -m <your message file> -e <your public encryption key>" << std::endl;
        exit(1);
    }

    string message_file = argv[2];
    string public_key_file = argv[4];

    if (!fileExists(message_file))
    {
        std::cerr << "The file [" << message_file << "] does not exist." << std::endl;
        exit(1);
    }

    if (!fileExists(public_key_file))
    {
        std::cerr << "The file [" << public_key_file << "] does not exist." << std::endl;
        exit(1);
    }

    string csv_line = getFirstLineFromFile(public_key_file);
    vector<long long int> keyPair = parseKeyCsvLine(csv_line);

    const long long int E = keyPair[0];
    const long long int N = keyPair[1];

    vector<string> file_lines = readFile(message_file);

    ofstream encrypted_file("encrypted_file.txt");

    if (!encrypted_file.is_open())
    {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    bool newLineFlag = false;

    for (string str : file_lines)
    {
        string temp = "";

        if (newLineFlag)
        {
            encrypted_file << endl;
        }

        for (int i = 0; i < str.size(); i++)
        {

            long long int converted = int(str[i]);

            long long int encryptedNumber = modExp(converted, E, N);

            temp = temp + char(encryptedNumber);
        }

        encrypted_file << temp;
        newLineFlag = true;
    }

    encrypted_file.close();

    return 0;
}