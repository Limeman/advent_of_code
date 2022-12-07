#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <limits>

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

void get_dir_to_delete(directory* node, int &del_size, const int &needed_space) {
    node->visited = true;
    for (auto c : node->children) {
        if (c->visited == false)
        {
            if (c->size < del_size && c->size >= needed_space) {
                del_size = c->size;
            }
            get_dir_to_delete(c, del_size, needed_space);
        }
        
    }
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
    root = get_root(root);
    reset_states(root);

    root = get_root(root);
    int free_space = 70000000 - root->size;
    int needed_spae = 30000000 - free_space;

    int dir_to_delete = 70000000;
    get_dir_to_delete(root, dir_to_delete, needed_spae);
    
    std::cout << "I will delete: " << dir_to_delete << std::endl;
    return 0;
}