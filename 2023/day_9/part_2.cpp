#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <map>
#include <numeric>

struct node
{
    std::string connected_left_;
    std::string connected_right_;
};

bool is_solved(std::vector<std::string> positions)
{
    for (int i = 0; i < positions.size(); ++i)
    {
        if (positions[i][positions[i].size() - 1] != 'Z')
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::string instrunctions;
    std::map<std::string, node> map;

    std::getline(std::cin, instrunctions);

    std::string curr;
    std::vector<std::string> positions;
    std::getline(std::cin, curr);
    while (std::getline(std::cin, curr))
    {
        node tmp;

        std::string name = curr.substr(0, curr.find(" "));
        tmp.connected_left_ = curr.substr(curr.find("(") + 1, curr.find(",") - curr.find("(") - 1);
        tmp.connected_right_ = curr.substr(curr.find(",") + 2, curr.find(")") - curr.find(",") - 2);

        map.insert({name, tmp});
        if (name[name.size() - 1] == 'A')
        {
            positions.push_back(name);
        }
    }

    std::vector<int> loop_counts;
    for (auto p : positions)
    {
        int count = 0;
        curr = p;
        while (curr[curr.size() - 1] != 'Z')
        {
            char move = instrunctions[count % instrunctions.size()];
            if (move == 'R')
            {
                curr = map[curr].connected_right_;
            }
            else
            {
                curr = map[curr].connected_left_;
            }

            ++count;
        }

        loop_counts.push_back(count);
    }
    for (auto l : loop_counts)
    {
        std::cout << l << " ";
    }
    std::cout << "\n";
    long long answer = std::lcm(loop_counts[0], loop_counts[1]);
    std::cout << answer << std::endl;
    for (int i = 2; i < loop_counts.size(); ++i)
    {
        answer = std::lcm(answer, loop_counts[i]);
        std::cout << answer << std::endl;
    }

    std::cout << "The answer is " << answer << std::endl;

    return 0;
}