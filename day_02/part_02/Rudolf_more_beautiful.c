
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
// Created by felvmel on 06.12.2024.
//
FILE* ftpr;

const int length_lines = 1000;
const int length_word = 10;
int lines[1000][10];
void init_lines()
{
    for (int outer = 0; outer < length_lines; outer++)
    {
        for (int inner = 0; inner < length_word; inner++)
        {
            lines[outer][inner] = -1;
        }
    }
}
void fill_lines()
{
    init_lines();

    FILE* file = fopen("day_02/input", "r");

    if (file != NULL)
    {
        int index_line = 0;
        int index_word = 0;
        char line[256];
        while (fgets(line, length_lines, file))
        {
            index_word = 0;

            char* pEnd;
            long word = strtol(line, &pEnd, 10);
            while (word)
            {
                lines[index_line][index_word] = word;
                word = strtol(pEnd, &pEnd, 10);
                index_word++;
            }
            index_line++;
        }

        fclose(file);
    }
    else
    {
        fprintf(stderr, "Unable to open file!\n");
    }
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

int* remove_index(const int* line, const int index)
{
    static int new_line[10];
    for (int count = 0; count < length_word; count++)
    {
        new_line[count] = -1;
    }

    int bias = 0;
    for (int count = 0; count < length_word - bias; count++)
    {
        if (index == count)
        {
            bias++;
        }
        new_line[count] = line[count + bias];
    }
    return new_line;
}

int test_line(const int* line, const bool removed)
{
    bool ascending = false;
    for (int i = 0; i < length_word; i++)
    {
        if (line[i + 1] == -1)
        {
            return 1;
        }
        if (i == 0)
        {
            ascending = line[i] < line[i + 1];
        }
        if (!test_pair(line[i], line[i + 1], ascending))
        {
            if (!removed)
            {
                if (i == 1 && test_line(remove_index(line, 0), true))
                {
                    return 1;
                }
                if (test_line(remove_index(line, i), true) == 1)
                {
                    return 1;
                }
                if (test_line(remove_index(line, i + 1), true) == 1)
                {
                    return 1;
                }
            }
            return 0;
        }
    }
    return 1;
}

int main()
{
    int counter = 0;
    fill_lines();

    for (int count = 0; count < length_lines; count++)
    {
        if (test_line(lines[count], false) == 1)
        {
            counter++;
        }
    }

    printf("Count: %d\n", counter);
}
