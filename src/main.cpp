#include <iostream>
#include <map>
#include <sstream>
#include <vector>

int main() {
  // Flush after every std::cout / std:cerr
    while (true){
        std::map<std::string, int> mp;
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;
        std::cout << "$ ";
        std::string input;
        std::vector<std::string> commands;
        std::string  word;

        std::getline(std::cin,input);
        std::stringstream ss(input);

         while (ss>>word){
            commands.push_back(word);
        }
        if (input=="exit 0"){
            exit(0);
        }

        if (commands[0]=="echo"){

            for (int i = 1; i <commands.size()-1 ; ++i) {
                std::cout<<commands[i]<<" ";
            }
            std::cout<<commands[commands.size()-1]<<std::endl;
        }else{
            std::cout<<input<<": command not found"<<std::endl;
        }
    }

}
