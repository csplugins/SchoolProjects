#include <iostream>
#include "Huffman.hpp"

int main() {
  Huffman h;
  Encoded e = h.encode("MISSISSIPPI");

  std::cout << "Input: MISSISSIPPI" << std::endl;
  std::cout << e.encoded_string << std::endl;
  std::cout << e.serialized_tree << std::endl;

  std::cout << "Input: A man a plan, a canal, Panama!" << std::endl;
  Encoded a = h.encode("A man a plan, a canal, Panama!");
  std::cout << a.encoded_string << std::endl;
  std::cout << a.serialized_tree << std::endl;

}
