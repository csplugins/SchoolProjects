#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "AVL.hpp"

void print_serialized(const std::vector<std::string>& v) {
  for (int i = 0; i < v.size(); ++i)
    std::cout << "[" << v[i] << "]";
  std::cout << std::endl;
}

std::vector<std::string> fill_vector(const std::string& s) {
  std::vector<std::string> out;
  int start = 0, end = 0;
  while(end < s.length() - 1) {
    start = s.find_first_of("[", end);
    end = s.find_first_of("]", end + 1);
    out.push_back(s.substr(start + 1, end - start - 1)); 
  }
  return out;
}



bool test_vector_equal(const std::vector<std::string>& a, const std::vector<std::string>& b) {
  if (a.size() != b.size())
    return false;

  for (int i = 0; i < a.size(); ++i)
    if (a[i] != b[i])
      return false;

  return true;
}

int main() {
    
  // Test 1 inserting, no rotation, serialize
  std::cout << "Test 1" << std::endl;
  std::cout << "  Basic Insertion - insert 30, 10, 50, 48, 20" << std::endl;
  AVL<int>* a1 = new AVL<int>();
  a1->insert(30);
  a1->insert(10);
  a1->insert(50);
  a1->insert(48);
  a1->insert(20);
  std::vector<std::string> a1s = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s);
  std::cout << "    Mine : ";
  std::vector<std::string> t1 = fill_vector("[30][10][/][20][/][/][50][48][/][/][/]");
  print_serialized(t1);
  assert(test_vector_equal(a1s, t1));
  std::cout << "  OK." << std::endl;
  std::cout << "Test 1 Passed." << std::endl;

  // Test 2 rotations
  std::cout << "\nTest 2" << std::endl;
  std::cout << "  Right Rotation - insert 40" << std::endl;
  a1->insert(40);
  std::vector<std::string> a1s2 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s2);
  std::cout << "    Mine : ";
  std::vector<std::string> t21 = fill_vector("[30][10][/][20][/][/][48][40][/][/][50][/][/]");
  print_serialized(t21);
  assert(test_vector_equal(a1s2, t21));
  std::cout << "  OK." << std::endl;

  std::cout << "  Left Rotation - insert 25" << std::endl;
  a1->insert(25);
  std::vector<std::string> a1s3 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s3);
  std::cout << "    Mine : ";
  std::vector<std::string> t22 = fill_vector("[30][20][10][/][/][25][/][/][48][40][/][/][50][/][/]");
  print_serialized(t22);
  assert(test_vector_equal(a1s3, t22));
  std::cout << "  OK." << std::endl;
  
  std::cout << "  Double Right Rotation - insert 42, 35, 44" << std::endl;
  a1->insert(42);
  a1->insert(35);
  a1->insert(44);
  std::vector<std::string> a1s4 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s4);
  std::cout << "    Mine : ";
  std::vector<std::string> t23 = fill_vector("[30][20][10][/][/][25][/][/][42][40][35][/][/][/][48][44][/][/][50][/][/]");
  print_serialized(t23);
  assert(test_vector_equal(a1s4, t23));
  std::cout << "  OK." << std::endl;

  std::cout << "  Double Left Rotation - insert 41, 33" << std::endl;
  a1->insert(41);
  a1->insert(33);
  std::vector<std::string> a1s5 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s5);
  std::cout << "    Mine : ";
  std::vector<std::string> t24 = fill_vector("[40][30][20][10][/][/][25][/][/][35][33][/][/][/][42][41][/][/][48][44][/][/][50][/][/]");
  print_serialized(t24);
  assert(test_vector_equal(a1s5, t24));
  std::cout << "  OK." << std::endl;

  std::cout << "Test 2 Passed." << std::endl;
  

  // Test 3 deletions
  std::cout << "\nTest 3" << std::endl;
  std::cout << "  Delete Leaf, delete 25" << std::endl;
  a1->remove(25);
  std::vector<std::string> a1s6 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s6);
  std::cout << "    Mine : ";
  std::vector<std::string> t31 = fill_vector("[40][30][20][10][/][/][/][35][33][/][/][/][42][41][/][/][48][44][/][/][50][/][/]");
  print_serialized(t31);
  assert(test_vector_equal(a1s6, t31));
  std::cout << "  OK." << std::endl;

  std::cout << "  Delete With Single Child, delete 35" << std::endl;
  a1->remove(35);
  std::vector<std::string> a1s7 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s7);
  std::cout << "    Mine : ";
  std::vector<std::string> t32 = fill_vector("[40][30][20][10][/][/][/][33][/][/][42][41][/][/][48][44][/][/][50][/][/]");
  print_serialized(t32);
  assert(test_vector_equal(a1s7, t32));
  std::cout << "  OK." << std::endl;

  std::cout << "  Delete With Two Children, delete 48" << std::endl;
  a1->remove(48);
  std::vector<std::string> a1s8 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s8);
  std::cout << "    Mine : ";
  std::vector<std::string> t33 = fill_vector("[40][30][20][10][/][/][/][33][/][/][42][41][/][/][44][/][50][/][/]");
  print_serialized(t33);
  assert(test_vector_equal(a1s8, t33));
  std::cout << "  OK." << std::endl;

  std::cout << "  Delete With Two Children, Causes Rotation, delete 40" << std::endl;
  a1->remove(40);
  std::vector<std::string> a1s9 = a1->serialize();
  std::cout << "    Yours: ";
  print_serialized(a1s9);
  std::cout << "    Mine : ";
  std::vector<std::string> t34 = fill_vector("[33][20][10][/][/][30][/][/][42][41][/][/][44][/][50][/][/]");
  print_serialized(t34);
  assert(test_vector_equal(a1s9, t34));
  delete a1;
  std::cout << "  OK." << std::endl;
  std::cout << "Test 3 Passed." << std::endl;

  // Test 4 ALl of the above with std::strings
  std::cout << "\nTest 4" << std::endl;
  std::cout << "  Insert and Delete with std::strings" << std::endl;
  AVL<std::string>* avls = new AVL<std::string>();
  avls->insert("Deeter");

  avls->insert("is");
  avls->insert("the");
  avls->insert("best");
  avls->insert("teacher");
  avls->insert("I");
  avls->insert("have");
  avls->insert("ever");
  avls->insert("had!");
  avls->insert("rules!!");
  avls->remove("the");
  avls->remove("best");
  avls->remove("teacher");
  avls->remove("I");
  avls->remove("have");
  avls->remove("ever");
  avls->remove("had!");
  avls->remove("is");

  std::vector<std::string> avlsv = avls->serialize();
  std::cout << "    Yours: ";
  print_serialized(avlsv);
  std::cout << "    Mine : ";
  std::vector<std::string> t41 = fill_vector("[Deeter][/][rules!!][/][/]");
  print_serialized(t41);
  assert(test_vector_equal(avlsv, t41));
  delete avls;
  std::cout << "Test 4 Passed." << std::endl;
  std::cout << "\nAll Tests Passed." << std::endl;
}
