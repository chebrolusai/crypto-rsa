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

    if (strcmp(argv[1], "-ef") != 0 || strcmp(argv[3], "-d") != 0)
    {
        cout << argv[1] << endl
             << argv[3];
        std::cerr << "The format accepted is -ef <your encrypted file> -d <your private encryption key>" << std::endl;
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

    const long long int D = keyPair[0];
    const long long int N = keyPair[1];

    vector<string> file_lines = readFile(message_file);

    bool newLineFlag = false;

    for (string str : file_lines)
    {

        if (newLineFlag)
        {
            cout << endl;
        }

        vector<long long int> encrypted_numbers = parseEncryptedLine(str);

        for (auto it : encrypted_numbers)
        {
            long long int decrypted_number = modExp(it, D, N);
            cout << char(decrypted_number);
        }

        newLineFlag = true;
    }

    return 0;
}