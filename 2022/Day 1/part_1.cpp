#include <iostream>
#include <string>

int main() {
    std::string curr;
    int most_calories = 0, curr_calories = 1;
    int curr_sum = 0, largest_sum = -1;
    while (std::getline(std::cin, curr))
    {
        if (curr == "")
        {
            std::cout << curr_sum << std::endl;
            if (curr_sum > largest_sum)
            {
                largest_sum = curr_sum;
                most_calories = curr_calories;
            }
            curr_sum = 0;
            curr_calories++;
        }
        else
        {
            curr_sum += std::stoi(curr);
        }
        
    }
    if (curr_sum > largest_sum)
    {
        std::cout << curr_sum << std::endl;
        largest_sum = curr_sum;
        most_calories = curr_calories;
    }

    std::cout << "Elf numeber " << most_calories  << " is carying " << largest_sum << " calories." << std::endl;
    
    return 0;
}