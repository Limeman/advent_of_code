#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <vector>

class game
{
public:
    struct hand
    {
        std::vector<int> cards;
        int bid;
    };
    std::vector<hand> hands;

    int get_card_value(char c)
    {
        if (isdigit(c))
        {
            return c - '0';
        }

        int ret_val;
        switch (c)
        {
        case 'A':
            ret_val = 14;
            break;
        case 'K':
            ret_val = 13;
            break;
        case 'Q':
            ret_val = 12;
            break;
        case 'J':
            ret_val = 11;
            break;
        case 'T':
            ret_val = 10;
        default:
            break;
        }
        return ret_val;
    }

    bool is_five_of_a_kind(std::vector<int> arg)
    {
        return is_x_of_a_kind(arg, 5);
    }

    bool is_x_of_a_kind(std::vector<int> arg, int x)
    {
        for (size_t i = 0; i < arg.size(); i++)
        {
            int matches = 0;
            for (size_t j = 0; j < arg.size(); j++)
            {
                if (arg[i] == arg[j] || arg[j] == 11)
                {
                    matches += 1;
                }
            }
            if (matches == x)
            {
                return true;
            }
        }
        return false;
    }

    bool is_x_of_a_kind(std::vector<int> arg, int x, int y)
    {
        for (size_t i = 0; i < arg.size(); i++)
        {
            int matches = 0;
            for (size_t j = 0; j < arg.size(); j++)
            {
                if ((arg[i] == arg[j] && arg[i] != y) || (arg[i] != y && arg[j] == 11))
                {
                    matches += 1;
                }
            }
            if (matches == x)
            {
                return true;
            }
        }
        return false;
    }

    bool is_full_house(std::vector<int> arg)
    {
        if (is_x_of_a_kind(arg, 3))
        {
            int first_match = 0;
            bool j_used{false};
            for (size_t i = 0; i < arg.size(); i++)
            {
                int matches = 0;
                for (size_t j = 0; j < arg.size(); j++)
                {
                    if (arg[i] == arg[j] || arg[j] == 11)
                    {
                        if (arg[j] == 11)
                        {
                            j_used = true;
                        }

                        matches += 1;
                    }
                }
                if (matches == 3)
                {
                    first_match = arg[i];
                }
            }
            if (j_used)
            {
                return is_x_of_a_kind_no_j(arg, 2, first_match);
            }
            return is_x_of_a_kind(arg, 2, first_match);
        }
        return false;
    }

    bool is_x_of_a_kind_no_j(std::vector<int> arg, int x)
    {
        for (size_t i = 0; i < arg.size(); i++)
        {
            int matches = 0;
            for (size_t j = 0; j < arg.size(); j++)
            {
                if (arg[i] == arg[j])
                {
                    matches += 1;
                }
            }
            if (matches == x)
            {
                return true;
            }
        }
        return false;
    }

    bool is_x_of_a_kind_no_j(std::vector<int> arg, int x, int y)
    {
        for (size_t i = 0; i < arg.size(); i++)
        {
            int matches = 0;
            for (size_t j = 0; j < arg.size(); j++)
            {
                if (arg[i] == arg[j] && arg[i] != y)
                {
                    matches += 1;
                }
            }
            if (matches == x)
            {
                return true;
            }
        }
        return false;
    }

    bool is_two_pair(std::vector<int> arg)
    {
        if (is_x_of_a_kind(arg, 2))
        {
            int first_match = 0;
            bool j_used{false};
            for (size_t i = 0; i < arg.size(); i++)
            {
                int matches = 0;
                for (size_t j = 0; j < arg.size(); j++)
                {
                    if (arg[i] == arg[j] || arg[j] == 11)
                    {
                        if (arg[j] == 11)
                        {
                            j_used = true;
                        }

                        matches += 1;
                    }
                }
                if (matches == 2)
                {
                    first_match = arg[i];
                }
            }
            if (j_used)
            {
                return is_x_of_a_kind_no_j(arg, 2, first_match);
            }
            return is_x_of_a_kind(arg, 2, first_match);
        }
        return false;
    }

    bool is_high_card(std::vector<int> arg)
    {
        std::sort(arg.begin(), arg.end());
        return std::unique(arg.begin(), arg.end()) == arg.end();
    }

    int get_hand_rank(std::vector<int> arg)
    {
        if (is_five_of_a_kind(arg))
        {
            return 7;
        }

        if (is_x_of_a_kind(arg, 4))
        {
            return 6;
        }

        if (is_full_house(arg))
        {
            return 5;
        }

        if (is_x_of_a_kind(arg, 3))
        {
            return 4;
        }

        if (is_two_pair(arg))
        {
            return 3;
        }

        if (is_x_of_a_kind(arg, 2))
        {
            return 2;
        }

        if (is_high_card(arg))
        {
            return 1;
        }

        return 0;
    }
};

int main()
{
    std::string cards, bid;

    game g;

    while (std::cin >> cards >> bid)
    {
        std::vector<int> tmp;
        for (auto c : cards)
        {
            tmp.push_back(g.get_card_value(c));
        }

        int bid_ = std::stoi(bid);

        g.hands.push_back({tmp, bid_});
    }

    auto comp = [&g](game::hand lhs, game::hand rhs)
    {
        int lhs_rank = g.get_hand_rank(lhs.cards);
        int rhs_rank = g.get_hand_rank(rhs.cards);
        if (lhs_rank == rhs_rank)
        {
            for (size_t i = 0; i < lhs.cards.size(); i++)
            {
                if (lhs.cards[i] < rhs.cards[i])
                {
                    return true;
                }

                if (lhs.cards[i] > rhs.cards[i])
                {
                    return false;
                }
            }
            return false;
        }
        return lhs_rank < rhs_rank;
    };

    std::sort(g.hands.begin(), g.hands.end(), comp);

    int count = 1;
    int sum = 0;
    for (auto h : g.hands)
    {
        // for (auto c : h.cards)
        // {
        //     std::cout << c << " ";
        // }
        // std::cout << "\n";
        sum += h.bid * count;
        ++count;
    }
    std::cout << "The answer is " << sum << std::endl;
    return 0;
}