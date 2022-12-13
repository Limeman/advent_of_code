#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ctype.h>

struct lists
{
    lists* parent;
    lists * child;
    std::vector<int> nums;
};

lists* parse_line(const std::string &line)
{
    lists* parsed_line = new lists({nullptr, nullptr, std::vector<int>()});
    for (auto l : line) {
        if (l == ',')
        {
            continue;
        }
        else if (std::isdigit(l))
        {
            parsed_line->nums.push_back(l - '0');
        }
        else if (l == '[')
        {
            parsed_line->child = new lists;
            parsed_line = parsed_line->child;
        }
        else if (l == ']')
        {
            parsed_line = parsed_line->parent;
        }
        else
        {
            // do nothing
        }
        
    }
    return parsed_line;
}

bool is_in_order(lists* first_packet, lists* second_packet)
{
    
}

int main() {
    std::string curr;

    while (std::getline(std::cin, curr))
    {
        if (curr != "\n")
        {
            lists* first_packet = parse_line(curr);
            std::getline(std::cin, curr);
            lists* second_packet = parse_line(curr);
        }
        
    }
    
    return 0;
}