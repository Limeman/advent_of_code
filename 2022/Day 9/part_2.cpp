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

void update_map(std::vector<std::vector<cell>> &map, std::vector<std::pair<int, int>> &tail, std::pair<int, int> new_pos) {
    
    map[new_pos.first][new_pos.second] = {'H', map[new_pos.first][new_pos.second].visited};


    std::pair<int, int> tmp = tail[0];
    tail[0] = new_pos;
    
    for (size_t i = 1; i < 10; i++)
    {
        std::pair<int, int> prev = tail[i - 1];
        std::pair<int, int> curr = tail[i];

        if (calc_dist(prev, curr) >= 2)
        {
            map[prev.first][prev.second].value = std::to_string(i)[0];
            map[curr.first][curr.second].value = '.';
            curr = tmp;
        }
        else
        {
            map[prev.first][prev.second].value = '.';
        }
        tmp = tail[i];
        tail[i] = prev;
    }
    
}

void run_instruction(std::vector<std::vector<cell>> &map, char instruction, int steps, std::vector<std::pair<int, int>> &tail) {
    for (int i = 0; i < steps; ++i) {
        if (instruction == 'R')
        {
            if (tail[0].second + 1 > map[0].size() - 1)
            {
                for (size_t i = 0; i < map.size(); i++)
                {
                    map[i].push_back({'.', false});
                }
            }
            
            update_map(map, tail, std::make_pair(tail[0].first, tail[0].second + 1));
        }
        else if (instruction == 'L')
        {
            std::pair<int, int> new_pos;
            if (tail[0].second - 1 < 0)
            {
                for (size_t i = 0; i < map.size(); i++)
                {
                    map[i].insert(map[i].begin(), {'.', false});
                }
                for (size_t i = 0; i < 10; i++)
                {
                    tail[i] = std::make_pair(tail[i].first, tail[i].second + 1);
                }
                
                new_pos = std::make_pair(tail[0].first, 0);
            }
            else
            {
                new_pos = std::make_pair(tail[0].first, tail[0].second - 1);
            }
            
            update_map(map, tail, new_pos);
        }
        else if (instruction == 'U')
        {
            std::pair<int, int> new_pos;
            if (tail[0].first - 1 < 0)
            {
                map.insert(map.begin(), std::vector<cell>(map[0].size(), {'.', false}));
                new_pos = std::make_pair(0, tail[0].second);
                for (size_t i = 0; i < 10; i++)
                {
                    tail[i] = std::make_pair(tail[i].first + 1, tail[i].second);
                }
                new_pos = std::make_pair(0, tail[0].second);
            }
            else
            {
                new_pos = std::make_pair(tail[0].first - 1, tail[0].second);
            }
            
            update_map(map, tail, new_pos);
        }
        else
        {
            // 'D'
            if (tail[0].first + 1 > map.size() - 1)
            {
                map.push_back(std::vector<cell>(map[0].size(), {'.', false}));
            }
            update_map(map, tail, std::make_pair(tail[0].first + 1, tail[0].second));
        }
        for (auto e : map) {
            for (auto c : e) {
                std::cout << c.value << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";   
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
    std::pair<int, int> head_pos = {map.size() - 1, 0};
    std::vector<std::pair<int, int>> tail(10, {map.size() - 1, 0});
    while (std::cin >> instruction >> curr)
    {
        int steps = std::stoi(curr);

        std::cout << instruction << " " << steps << std::endl; 

        run_instruction(map, instruction, steps, tail);
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