#include <iostream>
#include <string>
#include <sstream>
#include <vector>


int calc_score(const std::vector<std::pair<char, char>> &moves) {
    char opponent, my_move;
    int total_score;

    for (auto elem : moves) {
        opponent = elem.first;
        my_move = elem.second;

        switch (my_move)
        {
        case 'X':
            total_score++;
            break;
        case 'Y':
            total_score += 2;
            break;
        case 'Z':
            total_score += 3;
            break;
        default:
            break;
        }
        if (opponent == 'A' && my_move == 'X' ||
            opponent == 'B' && my_move == 'Y' ||
            opponent == 'C' && my_move == 'Z')
        {
            total_score += 3;
        }
        else if (opponent == 'A' && my_move == 'Y' ||
                 opponent == 'B' && my_move == 'Z' ||
                 opponent == 'C' && my_move == 'X')
        {
            total_score += 6;
        }
    }
    return total_score;
}

int main() {
    int total_score = 0;
    char opponent, my_move;
    std::vector<std::pair<char, char>> moves;

    while (std::cin >> opponent >> my_move)
    {
        std::pair<char, char> curr;
        
        curr.first = opponent;

        if (my_move == 'X')
        {
            switch (opponent)
            {
            case 'A':
                curr.second = 'Z';
                break;
            case 'B':
                curr.second = 'X';
                break;
            case 'C':
                curr.second = 'Y';
                break;
            default:
                break;
            }
        }
        else if (my_move == 'Y')
        {
            switch (opponent)
            {
            case 'A':
                curr.second = 'X';
                break;
            case 'B':
                curr.second = 'Y';
                break;
            case 'C':
                curr.second = 'Z';
                break;
            default:
                break;
            }
        }
        else
        {
            switch (opponent)
            {
            case 'A':
                curr.second = 'Y';
                break;
            case 'B':
                curr.second = 'Z';
                break;
            case 'C':
                curr.second = 'X';
                break;
            default:
                break;
            }
        }

        moves.push_back(curr);
        
    }

    std::cout << "The total score is: " << calc_score(moves) << std::endl;
    
    return 0;
}