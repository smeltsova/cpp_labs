#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

int main() {
  int MAX = 50;
  for (int i = 0; i <= MAX; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "\r[" << '\0';
    std::cout << std::setw(i) << std::setfill('#') << "";
    std::cout << std::setw(MAX - i) << std::setfill('.') << "";
    std::cout << "] " << i * 100.0 / MAX << "%" << std::flush;
  }
  std::cout << "\n";
}