#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

struct gardening_map
{
    int destination_range_start_;
    int source_range_start_;
    int range_length_;
};

struct almanac
{
    std::vector<int> seeds_;
    std::vector<gardening_map> seed_to_soil_;
    std::vector<gardening_map> soil_to_fertilizer_;
    std::vector<gardening_map> fertilizer_to_water_;
    std::vector<gardening_map> water_to_light_;
    std::vector<gardening_map> light_to_temperature_;
    std::vector<gardening_map> temperature_to_humidity_;
    std::vector<gardening_map> humidity_to_location_;
};

std::vector<int> extract_numbers(std::string str)
{
    std::vector<int> ret_val;
    std::string curr_num;
    bool hit_number{false};
    for (auto c : str)
    {
        if (!hit_number && isdigit(c))
        {
            hit_number = true;
        }

        if (isdigit(c))
        {
            curr_num += c;
        }

        if (hit_number && !isdigit(c))
        {
            std::cout << curr_num << std::endl;
            ret_val.push_back(std::stoi(curr_num));
            curr_num.clear();
            hit_number = false;
        }
    }

    if (!curr_num.empty())
    {
        ret_val.push_back(std::stoi(curr_num));
    }
    return ret_val;
}

std::vector<gardening_map> read_gardening_maps()
{
    std::vector<gardening_map> ret_val;
    std::string curr;
    while (std::getline(std::cin, curr) && curr != "\n")
    {
        std::cout << curr << std::endl;
        gardening_map tmp;
        std::vector<int> numbers = extract_numbers(curr);
        tmp.destination_range_start_ = numbers[0];
        tmp.source_range_start_ = numbers[1];
        tmp.range_length_ = numbers[2];
    }
    return ret_val;
}

int main()
{
    std::string curr;
    int sum = 0;
    almanac almanac_;
    while (std::getline(std::cin, curr))
    {
        if (curr.rfind("seeds:", 0) == 0)
        {
            almanac_.seeds_ = extract_numbers(curr.substr(curr.find(":")));
        }

        if (curr.rfind("seed-to-soil", 0) == 0)
        {
            almanac_.seed_to_soil_ = read_gardening_maps();
        }
    }

    for (auto elem : almanac_.seed_to_soil_)
    {
        std::cout << elem.destination_range_start_ << " " << elem.source_range_start_ << " " << elem.range_length_ << " ";
    }
    std::cout << "\n";

    std::cout << "The answer is " << sum << std::endl;
    return 0;
}