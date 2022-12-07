#include <iostream>
#include <string>
#include <vector>

bool is_starter(const std::vector<char> &packet) {
    for (int i = 0; i < packet.size(); ++i) {
        for (int j = i + 1; j < packet.size(); ++j) {
            if (packet[i] == packet[j]) {
                return false;
            }
        }
    }
    return true;
}

void next(std::vector<char> &packet, const char &c) {
    for (int i = 0; i < 13; ++i) {
        packet[i] = packet[i + 1];
    }
    packet[13] = c;
}

int main() {
    std::string curr;
    std::vector<char> start_packet(14, ' ');
    int curr_pos = 0, sum = 0;
    while (std::getline(std::cin, curr)) {
        int curr_sum = 1;
        for (auto c : curr) {
            next(start_packet, c);
            if (curr_sum > 13 && is_starter(start_packet)) {
                break;
            }
            ++curr_sum;
        }
        sum += curr_sum;
    }
    std::cout << "The sum of characters is " << sum << std::endl;
    return 0;
}