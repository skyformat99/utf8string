#include <iostream>
#include "utf8string.hpp"
#include <vector>

int main(int argc, char **argv){
  char *p;
  int pos = strtol(argv[2], &p, 10);
  int len = strtol(argv[3], &p, 10);

  UTF8String str = "a,あ,b,い\0";
  //std::cout << str.substr(2,3).substr(1,1).toString().c_str() << '\n';
  UTF8String str2 = str;

  std::vector<UTF8String> v = str2.split(",");
  std::cout << "size=" << v.size() << '\n';

  for(std::vector<UTF8String>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << it->toString() << '\n';

  }

  std::vector<UTF8String> v2 = str2.split("");
  std::cout << "size=" << v2.size() << '\n';

  for(std::vector<UTF8String>::iterator it = v2.begin(); it != v2.end(); ++it) {
    std::cout << it->toString() << '\n';

  }


}
