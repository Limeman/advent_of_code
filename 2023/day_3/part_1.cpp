#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

struct pos
{
    int x;
    int y;
};

struct number
{
    bool is_partnumber{false};
    int value;
    std::vector<pos> idxs;
};

bool is_partnumber(std::vector<std::vector<char>> schematic, pos p)
{
    bool ret_val{false};
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (p.x + i >= 0 && p.x + i < schematic.size() && p.y + j >= 0 && p.y + j < schematic[0].size())
            {
                if (!isdigit(schematic[p.x + i][p.y + j]) && schematic[p.x + i][p.y + j] != '.')
                {
                    ret_val = true;
                }
            }
        }
    }
    return ret_val;
}

std::vector<number> get_numbers(std::vector<std::vector<char>> schematic)
{
    std::vector<number> ret_val;
    for (int i = 0; i < schematic.size(); ++i)
    {
        number tmp;
        bool number_hit{false};
        for (int j = 0; j < schematic[0].size(); ++j)
        {
            pos curr_pos{i, j};
            if (!number_hit && isdigit(schematic[i][j]))
            {
                number_hit = true;
            }

            if (isdigit(schematic[i][j]))
            {
                tmp.idxs.push_back(curr_pos);
            }

            if ((number_hit && !isdigit(schematic[i][j])) || (number_hit && j == schematic[0].size() - 1))
            {
                std::string s;
                for (auto i : tmp.idxs)
                {
                    tmp.is_partnumber = tmp.is_partnumber | is_partnumber(schematic, i);
                    s.push_back(schematic[i.x][i.y]);
                }
                tmp.value = std::stoi(s);
                ret_val.push_back(tmp);

                tmp = {};
                number_hit = false;
            }
        }
    }
    return ret_val;
}

int main()
{
    std::string curr;
    int sum = 0;

    std::vector<std::vector<char>> schematic;
    while (std::getline(std::cin, curr))
    {
        std::vector<char> tmp;
        for (auto c : curr)
        {
            tmp.push_back(c);
        }
        schematic.push_back(tmp);
    }

    std::vector<number> numbers = get_numbers(schematic);

    for (auto elem : numbers)
    {
        if (elem.is_partnumber)
        {
            std::cout << elem.value << std::endl;
            sum += elem.value;
        }
    }

    std::cout << "The answer is " << sum << std::endl;
    return 0;
}