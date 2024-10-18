#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>

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

std::vector<std::string> split_string(const std::string &s, char delimiter) {
    std::stringstream ss(s);
    std::vector<std::string> return_vect;
    std::string token;
    while (getline(ss, token, delimiter)) {
        return_vect.push_back(token);
    }
    return return_vect;
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

        // Check if there are any commands entered
        if (commands.empty()) {
            continue;
        }

        std::string command = commands[0];
        std::vector<std::string> Arguments(commands.begin() + 1, commands.end());

        if (command == "exit") {
            break;  // Exit the shell loop
        }

        if (command == "echo") {

            for (int i = 1; i < commands.size() - 1; ++i) {
                std::cout << commands[i] << " ";
            }
            std::cout << commands[commands.size() - 1] << std::endl;
        } else if (command == "type") {
            std::vector<std::string> known_type = {"type", "exit", "echo","pwd","cd"};
            bool is_shell_builtin = false;
            for (auto &it: known_type) {
                if (it == Arguments[0]) {
                    is_shell_builtin = true;
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
        }else if (command == "pwd") {

            std::cout << std::filesystem::current_path().string() << std::endl;
        }else if (command=="cd"){
            if (std::filesystem::exists(Arguments[1])){
                std::filesystem::current_path(Arguments[1]);
            }else{
                std::cout << Arguments[1] << ": No such file or directory" << std::endl;
            }
        }
        else {
            std::string executable_path;
            std::string path_string = getenv("PATH");
            std::vector<std::string> path = split_string(path_string, ':');
            std::string filepath;

            bool command_found = false;
            for (int i = 0; i < path.size(); ++i) {
                filepath = path[i] + '/' + command;

                if (std::filesystem::exists(filepath)) {
                    command_found = true;
                    std::string executable_command = "exec " + filepath + " " + input.substr(command.length() + 1);
                    std::system(executable_command.c_str());
                    break;
                }
            }

            if (!command_found) {
                std::cout << command << ": command not found" << std::endl;
            }
        }
    }

    return 0;  // Program exits after the loop
}
