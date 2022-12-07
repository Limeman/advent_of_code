#include <iostream>
#include <string>
#include <cctype>


int main() {
    std::string curr;
    int sum = 0;

    while (std::getline(std::cin, curr)) {
        std::string compartment_1 = curr.substr(0, curr.length() / 2);
        std::string compartment_2 = curr.substr(curr.length() / 2);

        bool done = false;
        for (auto c1 : compartment_1) {
            for (auto c2 : compartment_2) {
                if (c1 == c2) {
                    if (std::islower(c1)) {
                        sum += int(c1) - int('a') + 1;
                    }
                    else {
                        sum += int(c1) - int('A') + 27;
                    }
                    done = true;
                    break;
                }
            }
            if (done) {
                break;
            }
        }
    }
    std::cout << "The sum of priorities is: " << sum << std::endl;
    return 0;
}