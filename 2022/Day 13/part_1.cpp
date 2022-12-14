#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ctype.h>

struct lists
{
    int val;
    lists* parent;
    std::vector<lists*>* nums = nullptr;
};

lists* parse_line(const std::string &line)
{
    lists* ret_val = new lists({0, nullptr, new std::vector<lists*>()});
    lists* parent = nullptr;
    for (auto l : line.substr(1)) {
        if (l == ',')
        {
            // do nothing
        }
        else if (std::isdigit(l))
        {
            ret_val->nums->push_back(new lists({l - '0', parent}));
        }
        else if (l == '[')
        {
            lists* child = new lists({0, ret_val, new std::vector<lists*>()});
            ret_val = child;
        }
        else if (l == ']')
        {
            if (ret_val->parent != nullptr)
            {
                ret_val = ret_val->parent;
            }
            
        }
        else
        {
            // do nothing
        }
    }
    return ret_val;
}

int compare_ints(const int &a, const int &b)
{
    if (a < b)
    {
        return 2;
    }
    else if (a == b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int compare_lists(std::vector<lists*>* first, std::vector<lists*>* second)
{
    int i = 0;
    while (i < first->size() && i < second->size())
    {
        if (first->at(i)->nums != nullptr && second->at(i)->nums != nullptr)
        {
            compare_lists(first->at(i)->nums, second->at(i)->nums);
        }
        else if (first->at(i)->nums == nullptr && second->at(i)->nums != nullptr)
        {
            compare_lists(new std::vector<lists*>(1, new lists({first->at(i)->val, nullptr, nullptr})), second->at(i)->nums);
        }
        else if (first->at(i)->nums != nullptr && second->at(i)->nums == nullptr)
        {
            compare_lists(first->at(i)->nums, new std::vector<lists*>(1, new lists({first->at(i)->val, nullptr, nullptr})));
        }
        else
        {
            int ret = compare_ints(first->at(i)->val, second->at(i)->val);
            if (ret == 2)
            {
                return 2;
            }
            else if (ret == 1)
            {
                continue;;
            }
            else
            {
                return 0;
            }
        }
        ++i;
    }
    if (first->size() < second->size())
    {
        return 2;
    }
    else if (first->size() == second->size())
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

int compare(lists* first, lists* second) {
    return compare_lists(first->nums, second->nums);
}

int main() {
    std::string curr;
    int sum = 0, index = 1;
    while (std::getline(std::cin, curr))
    {
        if (curr != "\n")
        {
            lists* first_packet = parse_line(curr);
            std::getline(std::cin, curr);
            lists* second_packet = parse_line(curr);
            if (compare(first_packet, second_packet) == 2)
            {
                sum += index;
            }
        }
        ++index;
    }
    std::cout << "Thes sum of indicies of packets in the right order is: " << sum << std::endl;
    return 0;
}