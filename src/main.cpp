#include <iostream>
#include <map>

int main() {
  // Flush after every std::cout / std:cerr
    while (true){
        std::map<std::string, int> mp;
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin,input);
        if (input=="exit 0"){
            exit(0);
        }
        std::cout<<input<<": command not found"<<std::endl;

    }

}
