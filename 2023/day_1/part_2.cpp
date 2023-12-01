#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <vector>
#include <ctype.h>

std::pair<int, int> find_spelled_num_reverse(std::string arg)
{
    std::reverse(arg.begin(), arg.end());
    std::vector<std::string> spelled_nums{"eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};
    std::pair<int, int> ret_val{std::numeric_limits<int>::max(), 1};
    int counter = 1;
    for (auto elem : spelled_nums)
    {
        int index = arg.find(elem);
        if (index != std::string::npos && index < first)
        {
            ret_val.first = index;
            ret_val.second = counter;
        }
        counter++;
    }
    return ret_val;
}

std::pair<int, int> find_spelled_num(std::string arg)
{
    std::vector<std::string> spelled_nums{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::pair<int, int> ret_val{std::numeric_limits<int>::max(), 1};
    int counter = 1;
    for (auto elem : spelled_nums)
    {
        int index = arg.find(elem);
        if (index != std::string::npos && index < first)
        {
            ret_val.first = index;
            ret_val.second = counter;
        }
        counter++;
    }
    return ret_val;
}

int main()
{
    std::string curr;
    int sum = 0;
    while (std::getline(std::cin, curr))
    {
        auto first_digit = std::find_if(std::begin(curr), std::end(curr), [](char i)
                                        { return isdigit(i); });
        std::string rev_curr(curr);
        std::reverse(rev_curr.begin(), rev_curr.end());
        auto last_digit = std::find_if(std::begin(rev_curr), std::end(rev_curr), [](char i)
                                       { return isdigit(i); });

        std::pair<int, int> first_index{std::distance(curr.begin(), first_digit), *first_digit - '0'};
        std::pair<int, int> last_index{std::distance(rev_curr.begin(), last_digit), *last_digit - '0'};

        std::pair<int, int> first_spelled = find_spelled_num(curr);
        std::pair<int, int> last_spelled = find_spelled_num_reverse(curr);
    }
    std::cout << "The answer is " << sum << std::endl;
    return 0;
}