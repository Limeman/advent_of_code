#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <limits>

struct gardening_map
{
    long long destination_range_start_;
    long long source_range_start_;
    long long range_length_;
};

struct almanac
{
    std::vector<long long> seeds_;
    std::vector<gardening_map> seed_to_soil_;
    std::vector<gardening_map> soil_to_fertilizer_;
    std::vector<gardening_map> fertilizer_to_water_;
    std::vector<gardening_map> water_to_light_;
    std::vector<gardening_map> light_to_temperature_;
    std::vector<gardening_map> temperature_to_humidity_;
    std::vector<gardening_map> humidity_to_location_;
};

std::vector<long long> extract_numbers(std::string str)
{
    std::vector<long long> ret_val;
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
            ret_val.push_back(std::stoll(curr_num));
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
    while (std::getline(std::cin, curr) && curr != "")
    {
        gardening_map tmp;
        std::vector<long long> numbers = extract_numbers(curr);
        tmp.destination_range_start_ = numbers[0];
        tmp.source_range_start_ = numbers[1];
        tmp.range_length_ = numbers[2];
        ret_val.push_back(tmp);
    }
    return ret_val;
}

// std::map<long long, long long> get_mapping(std::vector<gardening_map> arg)
// {
//     std::map<long long, long long> ret_val;
//     for (auto g : arg)
//     {
//         for (int i = 0; i < g.range_length_; i++)
//         {
//             ret_val.insert({g.source_range_start_ + i, g.destination_range_start_ + i});
//         }
//     }
//     return ret_val;
// }

almanac read_almanac()
{
    almanac ret_val;
    std::string curr;
    while (std::getline(std::cin, curr))
    {
        if (curr.rfind("seeds:", 0) == 0)
        {
            ret_val.seeds_ = extract_numbers(curr.substr(curr.find(":")));
        }

        if (curr.rfind("seed-to-soil", 0) == 0)
        {
            ret_val.seed_to_soil_ = read_gardening_maps();
        }

        if (curr.rfind("soil-to-fertilizer", 0) == 0)
        {
            ret_val.soil_to_fertilizer_ = read_gardening_maps();
        }

        if (curr.rfind("fertilizer-to-water", 0) == 0)
        {
            ret_val.fertilizer_to_water_ = read_gardening_maps();
        }

        if (curr.rfind("water-to-light", 0) == 0)
        {
            ret_val.water_to_light_ = read_gardening_maps();
        }

        if (curr.rfind("light-to-temperature", 0) == 0)
        {
            ret_val.light_to_temperature_ = read_gardening_maps();
        }

        if (curr.rfind("temperature-to-humidity", 0) == 0)
        {
            ret_val.temperature_to_humidity_ = read_gardening_maps();
        }

        if (curr.rfind("humidity-to-location", 0) == 0)
        {
            ret_val.humidity_to_location_ = read_gardening_maps();
        }
    }
    return ret_val;
}

long long process_mapping(std::vector<gardening_map> arg, long long val)
{
    for (auto elem : arg)
    {
        if (val >= elem.source_range_start_ && val < elem.source_range_start_ + elem.range_length_)
        {
            long long diff = val - elem.source_range_start_;
            val = elem.destination_range_start_ + diff;
            break;
        }
    }
    return val;
}

long long find_closest_location(almanac arg)
{
    long long closest_location = std::numeric_limits<long long>::max();
    std::vector<long long> seeds;
    long long prev = arg.seeds_[0];
    for (size_t i = 1; i < arg.seeds_.size(); i++)
    {
        if (i % 2 == 0)
        {
            prev = arg.seeds_[i];
        }
        else
        {
            for (size_t j = 0; j < arg.seeds_[i]; j++)
            {
                seeds.push_back(prev + j);
            }
        }
    }

    for (auto s : seeds)
    {
        long long curr = s;
        curr = process_mapping(arg.seed_to_soil_, curr);
        curr = process_mapping(arg.soil_to_fertilizer_, curr);
        curr = process_mapping(arg.fertilizer_to_water_, curr);
        curr = process_mapping(arg.water_to_light_, curr);
        curr = process_mapping(arg.light_to_temperature_, curr);
        curr = process_mapping(arg.temperature_to_humidity_, curr);
        curr = process_mapping(arg.humidity_to_location_, curr);
        if (curr < closest_location)
        {
            closest_location = curr;
        }
    }
    return closest_location;
}

int main()
{
    almanac almanac_ = read_almanac();
    long long answer = find_closest_location(almanac_);
    std::cout << "The answer is " << answer << std::endl;
    return 0;
}