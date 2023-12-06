#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

struct record
{
    long long time;
    long long distance;
};

struct document
{
    record record;
};

long long extract_number(std::string str)
{
    long long ret_val;
    bool number_hit{false};
    std::string num_str;
    for (auto s : str)
    {
        if (isdigit(s))
        {
            num_str.push_back(s);
        }
    }
    if (!num_str.empty())
    {
        ret_val = std::stoll(num_str);
    }
    return ret_val;
}

int main()
{
    long long sum = 0;
    std::string curr;
    document document_;

    std::getline(std::cin, curr);
    document_.record.time = extract_number(curr);

    std::getline(std::cin, curr);
    document_.record.distance = extract_number(curr);

    for (long long i = 0; i <= document_.record.time; i++)
    {
        if (i * (document_.record.time - i) > document_.record.distance)
        {
            sum += 1;
        }
    }

    std::cout << "The answer is " << sum << std::endl;
    return 0;
}