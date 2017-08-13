#include <iostream>
#include "utf8string.hpp"
#include <vector>

int main(int argc, char **argv){
  // original string 1 - std::string
  std::string str1 = "abcあいうdeえお";
  // original string 2 - C string
  char str2[50];
  strcpy(str2, str1.c_str());

  // initialize from std::string
  UTF8String ustr1 = str1;
  // initialize from C string
  UTF8String ustr2 = str2;
  
  // get substring and convert to std::string
  std::cout << ustr1.substr(2,5).toString() << '\n';

  // split string and generate vector
  std::string csv = "a,あ,b,c,い,う";
  std::string delimiter = ",";
  UTF8String ustr3 = csv;
  
  std::vector<UTF8String> v = ustr3.split(delimiter);

  for(std::vector<UTF8String>::iterator it = v.begin(); it != v.end(); it++){
    std::cout << it->toString() << '\n';
  }


  std::string a = "abcあ";
  std::string b = "defい";
  UTF8String ua = a;
  UTF8String ub = b;

  UTF8String concat = a + b;
  std::cout << concat.toString() << '\n';
}
