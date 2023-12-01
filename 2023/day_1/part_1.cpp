#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>

int main()
{
    std::string curr;
    int sum = 0;
    while (std::getline(std::cin, curr))
    {
        auto first_num = std::find_if(std::begin(curr), std::end(curr), [](char i)
                                      { return isdigit(i); });
        std::string rev_curr(curr);
        std::reverse(rev_curr.begin(), rev_curr.end());
        auto last_num = std::find_if(std::begin(rev_curr), std::end(rev_curr), [](char i)
                                     { return isdigit(i); });
        std::string comb_num{*first_num, *last_num};
        sum += std::stoi(comb_num);
    }
    std::cout << "The answer is " << sum << std::endl;
    return 0;
}