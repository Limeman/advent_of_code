#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <map>

struct node
{
    std::string connected_left_;
    std::string connected_right_;
};

int main()
{
    std::string instrunctions;
    std::map<std::string, node> map;

    std::getline(std::cin, instrunctions);

    std::string curr;
    std::getline(std::cin, curr);
    while (std::getline(std::cin, curr))
    {
        node tmp;

        std::string name = curr.substr(0, curr.find(" "));
        tmp.connected_left_ = curr.substr(curr.find("(") + 1, curr.find(",") - curr.find("(") - 1);
        tmp.connected_right_ = curr.substr(curr.find(",") + 2, curr.find(")") - curr.find(",") - 2);

        map.insert({name, tmp});
    }

    curr = map.begin()->first;
    int i = 0;
    while (curr != "ZZZ")
    {
        char move = instrunctions[i % instrunctions.size()];
        if (move == 'R')
        {
            curr = map[curr].connected_right_;
        }
        else
        {
            curr = map[curr].connected_left_;
        }

        ++i;
    }

    std::cout << "The answer is " << i << std::endl;

    return 0;
}