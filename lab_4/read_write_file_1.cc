#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream file("input.txt");
  if (file.is_open()) {
    while (!file.eof()) {
      std::string line;
      while (getline(file, line)) {
        std::cout << line << std::endl;
      }
      file.close();
    }
  }
}