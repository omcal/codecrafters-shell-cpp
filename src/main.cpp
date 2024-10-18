#include <iostream>
#include <map>

int main() {
  // Flush after every std::cout / std:cerr
  std::map<std::string, int> mp;
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::cout << "$ ";
  std::string input;
  std::getline(std::cin,input);
  std::map<std::string, int>::iterator it = mp.begin();
  while (it != mp.end()) {
        if (it->first== input){
            // Do stuff
        }
  }
  std::cout<<input<<": command not found"<<std::endl;



}
