#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Sorter.hpp"

// creating a type for sorting function pointers
typedef std::vector<int> (*Sort)(const std::vector<int>&);

// creating a vector of sorting functions from Sorter
const std::vector<Sort> sorts = { Sorter::bubblesort, Sorter::insertionsort, Sorter::radixsort, Sorter::mergesort, Sorter::quicksort };

// creating a vector of sort names
const std::vector<std::string> names = { "bubblesort", "insertionsort", "radixsort", "mergesort", "quicksort" };

// display the contents of a vector of ints
void display(const std::vector<int>&);

// run the set of tests for a specific sort
void run_test(const int&, const std::vector<Sort>&, const std::vector<std::string>&);

// used to check the order of the vectors
bool check_order(const std::vector<int>&);

int main() {

  srand(10);

  // run the tests for all sorts
  for (int i = 0; i < sorts.size(); ++i) 
    run_test(i, sorts, names);

}

void display(const std::vector<int>& v) {
  
  for (int i = 0; i < v.size(); ++i) 
    std::cout << "[" << v[i] << "]";
  std::cout << std::endl;

}

void run_test(const int& test, const std::vector<Sort>& sorts, const std::vector<std::string>& names) {

  int top_limit = 9999;
  int count = 10;

  std::vector<int> empty;
  std::vector<int> numbers;
  std::vector<int> random;

  for (int i = 0; i < count; ++i) {
    numbers.push_back(count - i); 
    random.push_back(rand() % top_limit);
  }

  std::cout << "\nTesting " << names[test] << std::endl;
  std::cout << " - empty vector: ";
  std::vector<int> result = sorts[test](empty);
  bool temp = check_order(result);
  std::cout << (temp ? "passed." : "failed.") << std::endl;
  
  std::cout << " - reverse vector: ";
  result = sorts[test](numbers);
  temp = check_order(result);
  std::cout << (temp ? "passed." : "failed.") << std::endl;
  
  if (!temp) {
    std::cout << "    Original Vector: ";
    display(numbers);
    std::cout << "    Sorted Vector: ";
    display(result);
  }

  std::cout << " - random vector: ";
  result = sorts[test](random);
  temp = check_order(result);
  std::cout << (temp ? "passed." : "failed.") << std::endl;
  
  if (!temp) {
    std::cout << "    Original Vector: ";
    display(random);
    std::cout << "    Sorted Vector: ";
    display(result);
  }
}

bool check_order(const std::vector<int>& vec) {
  if (vec.size() < 1)
    return true;

  int prev = vec[0];
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i] < prev)
      return false;
    else
      prev = vec[i];
  }
  return true;
}
