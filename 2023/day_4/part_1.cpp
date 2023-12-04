#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

struct game
{
    int card_number_;
    std::vector<int> numbers_;
    std::vector<int> winning_numbers_;
};

std::vector<std::string> extract_numbers(std::string str)
{
    std::vector<std::string> ret_val;
    bool number_hit{false};
    std::string curr_num;
    for (auto s : str)
    {
        if (!number_hit && std::isdigit(s))
        {
            number_hit = true;
        }

        if (std::isdigit(s))
        {
            curr_num.push_back(s);
        }

        if (!std::isdigit(s) && number_hit)
        {
            ret_val.push_back(curr_num);
            curr_num.clear();
            number_hit = false;
        }
    }

    if (!curr_num.empty())
    {
        ret_val.push_back(curr_num);
    }

    return ret_val;
}

game process_row(std::string row)
{
    game ret_val;
    std::vector<std::string> winning_numbers_str = extract_numbers(row.substr(row.find(":") + 2, row.find(" |") - row.find(":") - 2));
    for (auto w : winning_numbers_str)
    {
        ret_val.winning_numbers_.push_back(std::stoi(w));
    }

    std::vector<std::string> numbers_str = extract_numbers(row.substr(row.find("|") + 2));
    for (auto n : numbers_str)
    {
        ret_val.numbers_.push_back(std::stoi(n));
    }

    std::string card_number_str = row.substr(row.find(" ") + 1, row.find(":") - row.find(" "));
    ret_val.card_number_ = std::stoi(card_number_str);

    return ret_val;
}

int get_card_value(game card)
{
    int ret_val{0};
    for (auto w : card.winning_numbers_)
    {
        for (auto n : card.numbers_)
        {
            if (n == w)
            {
                if (ret_val == 0)
                {
                    ret_val = 1;
                }
                else
                {
                    ret_val *= 2;
                }

                break;
            }
        }
    }
    return ret_val;
}

int main()
{
    std::string curr;
    int sum = 0;

    while (std::getline(std::cin, curr))
    {
        game curr_card = process_row(curr);
        sum += get_card_value(curr_card);
    }

    std::cout << "The answer is " << sum << std::endl;
    return 0;
}