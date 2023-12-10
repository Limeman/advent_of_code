#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

std::vector<int> parse_line(std::string str)
{
    std::vector<int> ret_val;

    std::string curr_num_str;
    bool number_hit{false};

    for (auto s : str)
    {
        if (!number_hit && isdigit(s))
        {
            number_hit = true;
        }

        if (isdigit(s))
        {
            curr_num_str.push_back(s);
        }

        if (!isdigit(s) && number_hit)
        {
            ret_val.push_back(std::stoi(curr_num_str));
            curr_num_str.clear();
            number_hit = false;
        }
    }

    return ret_val;
}

int main()
{
    std::string curr;
    std::vector<std::vector<int>> oasis_stability;
    while (std::getline(std::cin, curr))
    {
        oasis_stability.push_back(parse_line(curr));
        while (!std::all_of(oasis_stability[oasis_stability.size() - 1].begin(), oasis_stability[oasis_stability.size() - 1].end(), [](int i)
                            { return i == 0; }))
        {
            std::vector<int> tmp;
            for (size_t i = 0; i < oasis_stability[oasis_stability.size() - 1].size() - 1; i++)
            {
                tmp.push_back(oasis_stability[oasis_stability.size() - 1][i + 1] - oasis_stability[oasis_stability.size() - 1][i]);
            }
            oasis_stability.push_back(tmp);
        }
    }

    return 0;
}