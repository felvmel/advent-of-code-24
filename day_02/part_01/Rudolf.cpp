//
// Created by micro on 05.12.2024.
//

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

set<vector<int>> get_lines(const string& path)
{
    set<vector<int>> lines = {};
    ifstream file(path);
    string line;
    while (getline(file, line))
    {
        stringstream line_stream(line);
        string word;

        vector<int> word_vector;

        while (getline(line_stream, word, ' '))
        {
            word_vector.push_back(stoi(word));
        }
        lines.insert(word_vector);
    }

    return lines;
}


bool test_gradient(const int x, const int y, const bool ascending) { return ascending && x < y || !ascending && x > y; }

bool test_diff_asc(const int x, const int y) { return x - y > -4; }

bool test_diff_desc(const int x, const int y) { return x - y < 4; }

bool test_diff(const int x, const int y, const bool ascending)
{
    return ascending ? test_diff_asc(x, y) : test_diff_desc(x, y);
}

bool test_pair(const int x, const int y, const bool ascending)
{
    return test_gradient(x, y, ascending) && test_diff(x, y, ascending);
}

int test_line(const vector<int>& line)
{
    bool ascending = false;
    for (int i = 0; i < line.size() - 1; i++)
    {
        if (i == 0)
        {
            ascending = line[i] < line[i + 1];
        }
        if (!test_pair(line[i], line[i + 1], ascending))
        {
            return 0;
        }
    }

    return 1;
}

set<vector<int>> lines = get_lines("day_02/part_01/input");
int main(int argc, char* argv[])
{
    int count = 0;
    for (const auto& line : lines)
    {
        if (test_line(line) == 1)
        {
            for (const auto word : line)
            {
                cout << word << " ";
            }
            cout << endl;
            count++;
        }
    }

    printf("Count: %d\n", count);
}
