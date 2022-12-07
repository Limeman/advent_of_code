#include <iostream>
#include <string>
#include <vector>
#include <stack>


struct directory
{
    directory* parent;
    std::string name;
    int size;
    std::vector<directory*> children;
    bool visited = false;
};

directory* get_root(directory* &standing) {
    directory* walker = standing;
    while (walker->parent != nullptr)
    {
        walker = walker->parent;
    }
    return walker;
}

void run_cd(directory* &standing, std::string &jump_to) {
    if (jump_to == "/") {
        standing = get_root(standing);
    }
    else if (jump_to == "..") {
        standing = standing->parent;
    }
    else {
        for (auto c : standing->children) {
            if (c->name == jump_to) {
                standing = c;
                return;
            }
        }
    }
}

void run_command(const std::string &command, directory* &standing) {
    std::string cmd = command.substr(2, 2);
    if (cmd == "cd") {
        std::string jump_to = command.substr(command.find("cd ") + 3);
        run_cd(standing, jump_to);
    }
    else if (cmd == "ls") {
        std::string curr;
        while (std::getline(std::cin, curr))
        {
            if (curr[0] == '$')
            {
                run_command(curr, standing);
            }
            else {
                // std::cout << curr << std::endl;
                std::string first = curr.substr(0, curr.find(" "));
                std::string second = curr.substr(curr.find(" ") + 1);

                //std::cout << first << " " << second << std::endl;

                if (first == "dir") {
                    standing->children.push_back(new directory({standing, second, 0, {}}));
                }
                else {
                    standing->size += std::stoi(first);
                }
            }
        }
        
    }
    else {
        // do nothing
    }
}

int compute_sizes(directory* node) {
    node->visited = true;
    for (auto c : node->children) {
        if (c->visited == false)
        {
            node->size = compute_sizes(c) + node->size;
        }
    }
    return node->size;
}

void reset_states(directory* node) {
    node->visited = false;
    for (auto c : node->children) {
        if (c->visited)
        {
            reset_states(c);
        }  
    }
}

int sum_of_sub100k(directory* node) {
    node->visited = true;
    int sum = 0;
    for (auto c : node->children) {
        if (c->visited == false)
        {
            if (c->size <= 100000)
            {
                sum += sum_of_sub100k(c) + c->size;
            }
            else {
                sum += sum_of_sub100k(c);
            }
        }
    }
    return sum;
}

int main() {
    std::string curr;
    directory* root = new directory({nullptr, "/", 0, {}});
    std::getline(std::cin, curr);
    while (std::getline(std::cin, curr))
    {
        std::cout << curr << std::endl;
        run_command(curr, root);
    }
    
    
    root = get_root(root);
    compute_sizes(root);

    for (auto r : root->children[0]->children) {
        std::cout << r->name << " " << r->size << std::endl;
    }

    root = get_root(root);
    reset_states(root);

    root = get_root(root);
    int sum = sum_of_sub100k(root);

    std::cout << "The sum of sub 100k directories is " << sum << std::endl;

    return 0;
}