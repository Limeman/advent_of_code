#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string curr;
    int most_calories = 0;
    int curr_sum = 0;
    std::vector<int> cals;
    while (std::getline(std::cin, curr))
    {
        if (curr == "")
        {
            cals.push_back(curr_sum);
            curr_sum = 0;
        }
        else
        {
            curr_sum += std::stoi(curr);
        }
        
    }
    
    cals.push_back(curr_sum);

    std::sort(cals.begin(), cals.end(), std::greater<int>());

    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += cals[i];
    } 
    std::cout << sum << std::endl;
    return 0;
}