#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <filesystem>

std::string get_paths(std::string command) {
    std::string path_env = std::getenv("PATH");
    std::stringstream ss(path_env);

    std::string path;
    while (!ss.eof()) {
        getline(ss, path, ':');
        std::string abs_path = path + "/" + command;

        if (std::filesystem::exists(abs_path)) {

            return abs_path;
        }

    }
    return "";
}

int main() {
    // Flush after every std::cout / std:cerr
    while (true) {
        std::map<std::string, int> mp;
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;
        std::cout << "$ ";
        std::string input;
        std::vector<std::string> commands;
        std::string word;

        std::getline(std::cin, input);
        std::stringstream ss(input);
        while (ss >> word) {
            commands.push_back(word);
        }
        if (input == "exit 0") {
            exit(0);
        }
        std::string command = commands[0];
        std::vector<std::string> Arguments(commands.begin() + 1, commands.end());
        if (command == "echo") {

            for (int i = 1; i < commands.size() - 1; ++i) {
                std::cout << commands[i] << " ";
            }
            std::cout << commands[commands.size() - 1] << std::endl;
        } else if (command == "type") {
            std::vector<std::string> known_type = {"type", "exit", "echo"};
            bool is_shell_builtin = false;
            for (auto &it: known_type) {
                if (it == Arguments[0]) {
                    is_shell_builtin = true;
                    break;
                }
            }
            if (is_shell_builtin) {
                std::cout << Arguments[0] << " is a shell builtin" << std::endl;
            } else {
                std::string path = get_paths(Arguments[0]);
                if (path.empty()) {
                    std::cout << Arguments[0] << ": not found\n";
                } else {
                    std::cout << input.substr(5) << " is " << path << std::endl;
                }
            }
        } else {
            std::cout << input << ": command not found" << std::endl;
        }
    }

}
