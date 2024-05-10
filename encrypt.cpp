#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <cmath>
#include "utility/string_parsing.cpp"

using namespace std;

long long modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

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

    if (strcmp(argv[1], "-m") != 0 || strcmp(argv[3], "-p") != 0)
    {
        cout << argv[1] << endl
             << argv[3];
        std::cerr << "The format accepted is -m <your message file> -p <your public key>" << std::endl;
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

    FILE *encrypted_file = fopen("encrypted_file.txt", "wt");

    for (string str : file_lines)
    {
        string temp = "";

        for (int i = 0; i < str.size(); i++)
        {

            long long int converted = int(str[i]);

            long long int encryptedNumber = modExp(converted, E, N);

            temp = temp + char(encryptedNumber);
        }

        fprintf(encrypted_file, "%s\n", temp.c_str());
    }

    fclose(encrypted_file);

    return 0;
}