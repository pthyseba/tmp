#include <iostream>
#include " utils/typelist.h"

using namespace utils;

template<typename T1, typename T2>
struct EqualTypes
{
  const static bool TResult = false;
};

template<typename T1>
struct EqualTypes<T1, T1>
{
  const static bool TResult = true;
};

/*
template<typename Head, typename... Rest>
struct TypeList2;

template<typename Head>
struct TypeList2<Head>
{
  typedef Head THead;
  typedef void TTail;
};

template<typename Head, typename... Rest>
struct TypeList2
{
  typedef Head THead;
  typedef TypeList2<Rest...> TTail;
};
  
template<typename Head, typename Tail = void>
struct TypeList
{
  typedef Head THead;
  typedef Tail TTail;
};


template<typename SearchType, typename List>
struct ContainsType;

template<typename SearchType, typename Head, typename... Tail>
struct ContainsType<SearchType, TypeList2<Head, Tail...> >
{
  const static bool TResult = EqualTypes<SearchType, Head>::TResult ? true : ContainsType<SearchType, TypeList2<Tail...> >::TResult;
};

template<typename SearchType, typename Head>
struct ContainsType<SearchType, TypeList2<Head> >
{
  const static bool TResult = EqualTypes<SearchType, Head>::TResult;
};

template<typename SearchType, typename Head, typename Tail>
struct ContainsType<SearchType, TypeList<Head, Tail> >
{
  const static bool TResult = EqualTypes<SearchType, Head>::TResult ? true : ContainsType<SearchType, Tail>::TResult;
};

template<typename SearchType>
struct ContainsType<SearchType, void>
{
  const static bool TResult = false;
};

*/


class BaseLayer
{
public:
  class Ring
  {
  public:
    template<typename TopRing>
    class Inner
    {
    typedef typename TopRing::template Inner<TopRing> TTop;
    public:
      void Do() { static_cast<TTop&>(*this).Use(); }
      void Use() { std::cout << "Base Use()" << std::endl; }
    protected:
      Inner() {}
    };
    template<typename TopRing>
    class Shared
    {
    typedef typename TopRing::template Shared<TopRing> TTop;
    public:
      
    };
  };
};

class Layer1 
{
public:
  template<typename SuperRing>
  class Ring : public SuperRing
  {
  public:
    template<typename TopRing>
    class Inner : public SuperRing::template Inner<TopRing>
    {
    typedef typename TopRing::template Inner<TopRing> TTop;
    typedef typename SuperRing::template Inner<TopRing> TSuper;
    public:
      void Use() 
      {
        TSuper::Use();
        std::cout << "Layer1 Use()" << std::endl; 
      }
    };
  };
};

class Layer2
{
public:
  template<typename SuperRing>
  class Ring : public SuperRing
  {
  public:
    template<typename TopRing>
    class Inner : public SuperRing::template Inner<TopRing>
    {
    typedef typename TopRing::template Inner<TopRing> TTop;
    typedef typename SuperRing::template Inner<TopRing> TSuper;
    public:
      void Use() 
      {
        TSuper::Use();
        std::cout << "Layer2 Use()" << std::endl; 
	std::cout << ContainsType<char, TypeList<double, TypeList<int> > >::TResult << std::endl;
        std::cout << ContainsType<char, TypeList2<double, char> >::TResult << std::endl;
      }
    };
  };
};

// Assembly<Layer1>
template<typename Top, typename... Rest>
struct Assembly
{
  typedef typename Top::template Ring<typename Assembly<Rest...>::TRing> TRing;
  typedef typename TRing::template Inner<TRing> TInner; 
};

template<typename Top>
struct Assembly<Top>
{
  typedef typename Top::template Ring<BaseLayer::Ring> TRing;
  typedef typename TRing::template Inner<TRing> TInner;
};

int main(int argc, char** argv)
{ 
  Assembly<Layer2,Layer1>::TInner a;

  a.Do();

  return 0;
}
