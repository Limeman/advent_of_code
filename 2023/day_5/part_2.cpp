#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <cmath>

struct game
{
    int card_number_;
    int num_copies_{1};
    int num_wins_{0};
    int card_value_{0};
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

    std::vector<game> cards;
    while (std::getline(std::cin, curr))
    {
        cards.push_back(process_row(curr));
        cards[cards.size() - 1].card_value_ = get_card_value(cards[cards.size() - 1]);
        if (cards[cards.size() - 1].card_value_ == 0)
        {
            cards[cards.size() - 1].num_wins_ = 0;
        }
        else
        {
            cards[cards.size() - 1].num_wins_ = log2(cards[cards.size() - 1].card_value_) + 1;
        }
    }

    for (auto c : cards)
    {
        for (size_t j = 0; j < c.num_copies_; j++)
        {
            for (size_t i = 0; i < c.num_wins_; i++)
            {
                cards[c.card_number_ + i].num_copies_ += 1;
            }
        }
    }

    for (auto c : cards)
    {
        sum += c.num_copies_;
    }

    std::cout << "The answer is " << sum << std::endl;
    return 0;
}