#include "typelist.h"
#include "arglist.h"
#include <iostream>

using namespace utils;
class dummy {
public:
friend std::ostream& operator << (std::ostream&, const dummy&);
};

std::ostream& operator << (std::ostream& aStream, const dummy& aDummy)
{
  aStream << "dummy";
  return aStream;
}
int main(int argc, char** argv)
{
  TypeList<int, double>  i;
  std::cout << EqualTypes<int, int>::TResult << std::endl;
  std::cout << ContainsType<std::ostream, TypeList<double, char, int> >::TResult << std::endl;
  TypeAtIndex<2, TypeList<int, double, char> >::TResult c;

  std::cout << EqualTypes<int, TypeAtIndex<0, TypeList<int, double, char> >::TResult>::TResult << std::endl;

  ArgList<dummy,int, double, dummy> a(dummy(),17, 2.0, dummy());
  
  auto b = CreateArgList(1,17.0);
  std::cout << a.Head() << std::endl;

  std::cout << IndexOf<double, TypeList<char, double> >::TResult << std::endl;
  
  std::cout << ExtractAtIndex<1>(a) << std::endl;

  std::cout << Extract<dummy>(a) << std::endl;
  std::cout << Extract<double>(b) << std::endl;
  return 0;
}
