#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <ctype.h>

struct instruction
{
    int amount, from, to;
};


std::vector<std::deque<char>> read_piles(const int &n) {
    std::string curr;
    std::vector<std::deque<char>> piles(n, std::deque<char>());

    while (true) {
        std::getline(std::cin, curr);
        for (int i = 0; i < n; ++i) {
            char c = curr[1 + i * 4];
            if (isdigit(c)) {
                return piles;
            }
            else {
                if (c != ' ') {
                    piles[i].push_back(c);
                }
            }
        }
    }
}

std::vector<instruction> read_instrucions() {
    std::string curr;
    std::vector<instruction> instructions;
    while (std::getline(std::cin, curr)) {
        instruction instr;
        
        std::string curr_num(curr.begin() + 5, curr.begin() + curr.find(" fr"));
        instr.amount = std::stoi(curr_num);

        curr_num = std::string(curr.begin() + (curr.find("om ") + 3), curr.begin() + curr.find(" to"));
        instr.from = std::stoi(curr_num);

        curr_num = curr.substr(curr.find("to ") + 3);
        instr.to = std::stoi(curr_num);

        instructions.push_back(instr);
    }
    return instructions;
}

std::string rearangement_procedure(std::vector<std::deque<char>> &piles, const std::vector<instruction> & instructions) {
    
    std::string tops = "";

    for (auto i : instructions) {
        std::string curr = "";
        for (int j = 0; j < i.amount; ++j) {
            curr += piles[i.from - 1].front();
            piles[i.from - 1].pop_front();
        }

        for (int j = curr.length() - 1; j >= 0; --j) {
            piles[i.to - 1].push_front(curr[j]);
        }
    }

    for (auto p : piles) {
        tops += p.front();
    }

    return tops;
}


int main() {
    int n = 9;
    std::string curr;
    
    std::vector<std::deque<char>> piles = read_piles(n);

    std::getline(std::cin, curr);

    std::vector<instruction> instructions = read_instrucions();

    std::string rearanged_tops = rearangement_procedure(piles, instructions);

    std::cout << "The rearanged tops are: " << rearanged_tops << std::endl;

    return 0;
}