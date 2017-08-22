#include <iostream>

template<typename MostDerived>
class Base
{
public:
  const MostDerived& Top() const { return static_cast<const MostDerived&>(*this); }
  MostDerived& Top() { return static_cast<MostDerived&>(*this); }
  void Useful() 
  {
    std::cout << "Base Useful()" << std::endl;
  }
  void Do() 
  { 
    std::cout << "Base Do()" << std::endl;
    this->Top().Useful(); 
  }
};

template<typename MostDerived>
class DerivedBase : public Base<MostDerived> 
{
public:
  typedef Base<MostDerived> TSuper;
  void Useful() 
  { 
    std::cout << "DerivedBase Useful()" << std::endl;
    TSuper::Useful();
  }
  void DoMore() {}
};

class A : public DerivedBase<A> 
{
public:
  typedef DerivedBase<A> TSuper;
  void Useful() 
  {
    std::cout << "A Useful()" << std::endl;
    TSuper::Useful();
  }
};

class SimpleBase {};

template<template<class> class Top, typename... Rest>
struct Assemble
{
  typedef Top<typename Assemble<Rest...>::TResult> TResult;
};

template<template<class> class Top>
struct Assemble<Top>
{
  typedef Top<SimpleBase> TResult;
};
//
//  Assemble<A,B,C>::type = A<B<C<Base> > >
//

int main(int argc, char** argv)
{

  A a;
  a.Do();
  a.DoMore();

  Assemble<E,D>::TResult obj;
  return 0;
}


