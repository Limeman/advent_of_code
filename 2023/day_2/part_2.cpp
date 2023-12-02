#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

struct cube_pull
{
    int reds;
    int greens;
    int blues;
};

std::vector<std::string> tokenizer(std::string str, std::string delimiter)
{
    std::vector<std::string> ret_val;
    std::size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        ret_val.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    ret_val.push_back(str);

    return ret_val;
}

cube_pull count_cube_pull(std::string pull)
{
    cube_pull ret_val{0, 0, 0};
    std::vector<std::string> counts = tokenizer(pull, ",");
    for (auto elem : counts)
    {
        elem = elem.substr(1);
        std::string color_count_str = elem.substr(0, elem.find(" "));
        int color_count = std::stoi(color_count_str);
        std::string color = elem.substr(elem.find(" ") + 1);
        if (color == "red")
        {
            ret_val.reds += color_count;
        }
        else if (color == "green")
        {
            ret_val.greens += color_count;
        }
        else
        {
            ret_val.blues += color_count;
        }
    }
    return ret_val;
}

std::vector<cube_pull> parse_line(std::string line)
{
    std::vector<cube_pull> ret_val;
    std::vector<std::string> pulls = tokenizer(line, ";");
    for (auto elem : pulls)
    {
        cube_pull count = count_cube_pull(elem);
        ret_val.push_back(count);
    }
    return ret_val;
}

int main()
{
    std::string curr;
    int sum = 0;

    while (std::getline(std::cin, curr))
    {
        std::string game_num_str = curr.substr(5, curr.find(":") - 5);
        int game_num = std::stoi(game_num_str);
        std::vector<cube_pull> game = parse_line(curr.substr(curr.find(":") + 1));

        cube_pull min_possible{-1, -1, -1};
        for (auto elem : game)
        {

            if (elem.blues > min_possible.blues)
            {
                min_possible.blues = elem.blues;
            }
            if (elem.greens > min_possible.greens)
            {
                min_possible.greens = elem.greens;
            }
            if (elem.reds > min_possible.reds)
            {
                min_possible.reds = elem.reds;
            }
        }
        sum += min_possible.blues * min_possible.greens * min_possible.reds;
    }
    std::cout << "The answer is " << sum << std::endl;
    return 0;
}