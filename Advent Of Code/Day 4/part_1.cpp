#include <iostream>
#include <string>

int main() {
    std::string curr;
    int sum = 0;

    while (std::getline(std::cin, curr)) {
        int comma_pos = curr.find(',');

        std::string first_pair = curr.substr(0, comma_pos);
        std::string second_pair = curr.substr(comma_pos + 1);
        
        int hyphen_pos = first_pair.find('-');
        int fp1 = std::stoi(first_pair.substr(0, hyphen_pos)), fp2 = std::stoi(first_pair.substr(hyphen_pos + 1));
        hyphen_pos = second_pair.find('-');
        int sp1 = std::stoi(second_pair.substr(0, hyphen_pos)), sp2 = std::stoi(second_pair.substr(hyphen_pos + 1));


        if (fp1 <= sp1 && fp2 >= sp2) {
            ++sum;
        }
        else if (sp1 <= fp1 && sp2 >= fp2) {
            ++sum;
        }
        else {
            //Do nothing
        }
    }

    std::cout << "The total number of overlaps is: " << sum << std::endl;
    return 0;
}