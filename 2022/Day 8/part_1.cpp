#include <iostream>
#include <string>
#include <vector>
#include <utility>

std::vector<std::vector<int>> read_forest() {
    std::string curr;
    std::vector<std::vector<int>> forest;
    while (std::getline(std::cin, curr))
    {
        std::vector<int> tmp = {};
        for (auto c : curr) {
            tmp.push_back(int(c));
        }
        forest.push_back(tmp);
    }
    return forest;
}

struct steps
{
    int shift_up;
    int shift_down;
    int shift_right;
    int shift_left;
};


bool hidden_above(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    for (int i = 0; i < p.first; ++i) {
        if (forest[i][p.second] >= val)
        {
            return true;
        }
    }
    return false;
}

bool hidden_below(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    for (int i = p.first + 1; i < forest.size(); ++i) {
        if (forest[i][p.second] >= val)
        {
            return true;
        }
    }
    return false;
}

bool hidden_left(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    for (int i = 0; i < p.second; ++i) {
        if (forest[p.first][i] >= val)
        {
            return true;
        }
    }
    return false;
}

bool hidden_right(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    for (int i = p.second + 1; i < forest[0].size(); ++i) {
        if (forest[p.first][i] >= val)
        {
            return true;
        }
    }
    return false;
}

bool is_hidden(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    return hidden_above(forest, p) &&
           hidden_below(forest, p) &&
           hidden_left(forest, p)  &&
           hidden_right(forest, p);
}

int count_visible_trees(const std::vector<std::vector<int>> &forest) {
    int sum = 2 * (forest.size() + forest[0].size()) - 4;
    for (size_t i = 1; i < forest.size() - 1; i++)
    {
        for (size_t j = 1; j < forest[0].size() - 1; j++)
        {
            if (!is_hidden(forest, std::make_pair(i, j)))
            {
                ++sum;
            }
        }
        
    }
    return sum;
}

int main() {
    std::vector<std::vector<int>> forest = read_forest();
    std::cout << "The number of visible trees is: " << count_visible_trees(forest) << std::endl;
    return 0;
}