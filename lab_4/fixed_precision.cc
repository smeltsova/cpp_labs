#include <fstream>
#include <iomanip>
#include <iostream>

int main() {
  std::ifstream file("input.txt");
  if (file.is_open()) {
    while (!file.eof()) {
      double number;
      file >> number;
      std::cout << std::fixed << std::setprecision(3) << number << "\n";
    }
  }
}