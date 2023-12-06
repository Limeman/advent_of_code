#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

struct record
{
    int time;
    int distance;
};

struct document
{
    std::vector<record> records;
};

std::vector<int> extract_numbers(std::string str)
{
    std::vector<int> ret_val;
    bool number_hit{false};
    std::string curr_num_str;
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

        if (number_hit && !isdigit(s))
        {
            ret_val.push_back(std::stoi(curr_num_str));
            curr_num_str.clear();
            number_hit = false;
        }
    }
    if (!curr_num_str.empty())
    {
        ret_val.push_back(std::stoi(curr_num_str));
    }
    return ret_val;
}

int main()
{
    int sum = 1;
    std::string curr;
    document document_;

    std::getline(std::cin, curr);
    std::vector<int> times = extract_numbers(curr);

    std::getline(std::cin, curr);
    std::vector<int> distances = extract_numbers(curr);

    if (times.size() == distances.size())
    {
        for (size_t i = 0; i < times.size(); i++)
        {
            document_.records.push_back({times[i], distances[i]});
        }
    }

    for (auto r : document_.records)
    {
        int multiplier = 0;
        for (size_t i = 0; i <= r.time; i++)
        {
            if (i * (r.time - i) > r.distance)
            {
                multiplier += 1;
            }
        }
        sum *= multiplier;
    }

    std::cout << "The answer is " << sum << std::endl;
    return 0;
}