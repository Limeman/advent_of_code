#include <iostream>
#include <string>


int main() {
    std::string elf_1, elf_2, elf_3;
    int sum = 0;

    while(std::cin >> elf_1 >> elf_2 >> elf_3) {
        bool done = false;
        for (auto e1 : elf_1) {
            for (auto e2 : elf_2) {
                for (auto e3 : elf_3) {
                    if (e1 == e2 && e2 == e3) {
                         if (std::islower(e1)) {
                            sum += int(e1) - int('a') + 1;
                        }
                        else {
                            sum += int(e1) - int('A') + 27;
                        }
                        done = true;
                        break;
                    }
                }
                if (done) {
                    break;
                }
            }
            if (done) {
                break;
            }
        }
    }
    std::cout << "The sum is: " << sum << std::endl;
    return 0;
}