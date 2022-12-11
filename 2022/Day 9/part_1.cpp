#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

struct cell
{
    char value;
    bool visited;
    bool is_start_pos = false;
};


float calc_dist(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

void update_map(std::vector<std::vector<cell>> &map, std::pair<int, int> &head_pos, std::pair<int, int> &tail_pos, std::pair<int, int> new_pos) {
    
    map[new_pos.first][new_pos.second] = {'H', map[new_pos.first][new_pos.second].visited};
    

    if (calc_dist(new_pos, tail_pos) >= sqrt(2))
    {
        map[head_pos.first][head_pos.second].value = 'T';
        map[head_pos.first][head_pos.second].visited = true;
        map[tail_pos.first][tail_pos.second].value = '.';

        tail_pos = head_pos;
    }
    else
    {
        map[head_pos.first][head_pos.second].value = '.';
    }
    
    head_pos = new_pos;

}

void run_instruction(std::vector<std::vector<cell>> &map, char instruction, int steps, std::pair<int, int> &head_pos, std::pair<int, int> &tail_pos) {
    for (int i = 0; i < steps; ++i) {
        if (instruction == 'R')
        {
            if (head_pos.second + 1 > map[0].size() - 1)
            {
                for (size_t i = 0; i < map.size(); i++)
                {
                    map[i].push_back({'.', false});
                }
            }
            
            update_map(map, head_pos, tail_pos, std::make_pair(head_pos.first, head_pos.second + 1));
        }
        else if (instruction == 'L')
        {
            std::pair<int, int> new_pos;
            if (head_pos.second - 1 < 0)
            {
                for (size_t i = 0; i < map.size(); i++)
                {
                    map[i].insert(map[i].begin(), {'.', false});
                }
                head_pos = std::make_pair(head_pos.first, head_pos.second + 1);
                tail_pos = std::make_pair(tail_pos.first, tail_pos.second + 1);
                new_pos = std::make_pair(head_pos.first, 0);
            }
            else
            {
                new_pos = std::make_pair(head_pos.first, head_pos.second - 1);
            }
            
            update_map(map, head_pos, tail_pos, new_pos);
        }
        else if (instruction == 'U')
        {
            std::pair<int, int> new_pos;
            if (head_pos.first - 1 < 0)
            {
                map.insert(map.begin(), std::vector<cell>(map[0].size(), {'.', false}));
                new_pos = std::make_pair(0, head_pos.second);
                head_pos = std::make_pair(head_pos.first + 1, head_pos.second);
                tail_pos = std::make_pair(tail_pos.first + 1, tail_pos.second);
            }
            else
            {
                new_pos = std::make_pair(head_pos.first - 1, head_pos.second);
            }
            
            update_map(map, head_pos, tail_pos, new_pos);
        }
        else
        {
            // 'D'
            if (head_pos.first + 1 > map.size() - 1)
            {
                map.push_back(std::vector<cell>(map[0].size(), {'.', false}));
            }
            update_map(map, head_pos, tail_pos, std::make_pair(head_pos.first + 1, head_pos.second));
        }
        // for (auto e : map) {
        //     for (auto c : e) {
        //         std::cout << c.value << " ";
        //     }
        //     std::cout << "\n";
        // }
        // std::cout << "\n";   
    }
}

int count_visited(const std::vector<std::vector<cell>> &m) {
    int sum = 0;
    for (auto i : m) {
        for (auto j : i) {
            if (j.visited || j.is_start_pos)
            {
                ++sum;
            }
            
        }
    }
    return sum;
}

int main() {
    std::vector<std::vector<cell>> map = std::vector(2, std::vector<cell>(2, {'.', false}));
    map[map.size() - 1][0] = {'s', false, true};
    
    std::string curr;
    char instruction;
    std::pair<int, int> head_pos = {map.size() - 1, 0}, tail_pos = {map.size() - 1, 0};
    while (std::cin >> instruction >> curr)
    {
        int steps = std::stoi(curr);

        std::cout << instruction << " " << steps << std::endl; 

        run_instruction(map, instruction, steps, head_pos, tail_pos);
    }
    

    for (auto e : map) {
        for (auto c : e) {
            if (c.visited) {
                std::cout << "# ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "The number of positions that the tail has visited is: " << count_visited(map) << std::endl;
    return 0;
}