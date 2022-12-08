#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>

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

int top_score(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    int score = 1;
    for (int i = p.first - 1; i >= 0; --i) {
        if (forest[i][p.second] >= val)
        {
            return score;
        }
        ++score;
    }
    return score - 1;
}

int bottom_score(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    int score = 1;
    for (int i = p.first + 1; i < forest.size(); ++i) {
        if (forest[i][p.second] >= val)
        {
            return score;
        }
        ++score;
    }
    return score - 1;
}

int left_score(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    int score = 1;
    for (int i = p.second - 1; i >= 0; --i) {
        if (forest[p.first][i] >= val)
        {
            return score;
        }
        ++score;
    }
    return score - 1;
}

int right_score(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    int val = forest[p.first][p.second];
    int score = 1;
    for (int i = p.second + 1; i < forest[0].size(); ++i) {
        if (forest[p.first][i] >= val)
        {
            return score;
        }
        ++score;
    }
    return score - 1;
}

int calc_score(const std::vector<std::vector<int>> &forest, std::pair<int, int> p) {
    return top_score(forest, p) * bottom_score(forest, p) * left_score(forest, p) * right_score(forest, p);
}

int get_best_tree(const std::vector<std::vector<int>> &forest) {
    int highest_score = -1;

    for (size_t i = 0; i < forest.size(); i++)
    {
        for (size_t j = 0; j < forest[0].size(); j++)
        {
            int score = calc_score(forest, std::make_pair(i, j));
            if (score > highest_score)
            {
                highest_score = score;
            }
            
        }
        
    }
    return highest_score;
}

int main() {
    std::vector<std::vector<int>> forest = read_forest();
    int best_tree = get_best_tree(forest);
    std::cout << "The highest score is: " << best_tree << std::endl;
    return 0;
}