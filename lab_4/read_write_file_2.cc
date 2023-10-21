#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream inputFile("input.txt");
  std::ofstream outputFile("output.txt");

  if (inputFile.is_open() && outputFile.is_open()) {
    std::string line;
    while (getline(inputFile, line)) {
      outputFile << line << std::endl;
    }
    inputFile.close();
    outputFile.close();
  }
  return 0;
}
