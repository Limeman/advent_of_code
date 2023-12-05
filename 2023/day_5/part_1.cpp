#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <map>

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

    std::vector<std::map<long long, long long>> global_map_;
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

std::map<long long, long long> get_mapping(std::vector<gardening_map> arg)
{
    std::map<long long, long long> ret_val;
    for (auto g : arg)
    {
        for (int i = 0; i < g.range_length_; i++)
        {
            ret_val.insert({g.source_range_start_ + i, g.destination_range_start_ + i});
        }
    }
    return ret_val;
}

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
            ret_val.global_map_.push_back(get_mapping(ret_val.seed_to_soil_));
        }

        if (curr.rfind("soil-to-fertilizer", 0) == 0)
        {
            ret_val.soil_to_fertilizer_ = read_gardening_maps();
            ret_val.global_map_.push_back(get_mapping(ret_val.soil_to_fertilizer_));
        }

        if (curr.rfind("fertilizer-to-water", 0) == 0)
        {
            ret_val.fertilizer_to_water_ = read_gardening_maps();
            ret_val.global_map_.push_back(get_mapping(ret_val.fertilizer_to_water_));
        }

        if (curr.rfind("water-to-light", 0) == 0)
        {
            ret_val.water_to_light_ = read_gardening_maps();
            ret_val.global_map_.push_back(get_mapping(ret_val.water_to_light_));
        }

        if (curr.rfind("light-to-temperature", 0) == 0)
        {
            ret_val.light_to_temperature_ = read_gardening_maps();
            ret_val.global_map_.push_back(get_mapping(ret_val.light_to_temperature_));
        }

        if (curr.rfind("temperature-to-humidity", 0) == 0)
        {
            ret_val.temperature_to_humidity_ = read_gardening_maps();
            ret_val.global_map_.push_back(get_mapping(ret_val.temperature_to_humidity_));
        }

        if (curr.rfind("humidity-to-location", 0) == 0)
        {
            ret_val.humidity_to_location_ = read_gardening_maps();
            ret_val.global_map_.push_back(get_mapping(ret_val.humidity_to_location_));
        }
    }
    return ret_val;
}

long long find_closest_location(almanac arg)
{
    long long closest_location = 0xFFFFFF;
    for (auto s : arg.seeds_)
    {
        long long curr = s;
        for (auto g : arg.global_map_)
        {
            if (g.find(curr) != g.end())
            {
                curr = g[curr];
            }
        }
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
    std::cout << "The answer is " << find_closest_location(almanac_) << std::endl;
    return 0;
}