#include <iostream>
#include <string>
#include <sstream>


int main() {
    int total_score = 0;
    char opponent, me;

    while (std::cin >> opponent >> me)
    {

        switch (me)
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
        if (opponent == 'A' && me == 'X' ||
            opponent == 'B' && me == 'Y' ||
            opponent == 'C' && me == 'Z')
        {
            total_score += 3;
        }
        else if (opponent == 'A' && me == 'Y' ||
                 opponent == 'B' && me == 'Z' ||
                 opponent == 'C' && me == 'X')
        {
            total_score += 6;
        }
                
    }

    std::cout << "The total score is: " << total_score << std::endl;
    
    return 0;
}