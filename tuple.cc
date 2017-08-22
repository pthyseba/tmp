#include <iostream>

class iTuple
{
};

template<typename... taArgs>
class Tuple;

template<typename T1, typename...taOthers>
class Tuple<T1, taOthers...> : public Tuple<taOthers...>
{
public:
  Tuple(T1 aHead, taOthers... aOthers) : Tuple<taOthers...>(aOthers...), iHead(aHead) {}
  T1& Head() {return iHead;}
private:
  T1 iHead;
  typedef Tuple<taOthers...> TSuper;
};

template<typename taOnly>
class Tuple<taOnly> : public iTuple
{
public:
  Tuple(taOnly aHead) : iHead(aHead) {}
  taOnly& Head() {return iHead;}
private:
  taOnly iHead;
};

template<unsigned int k, typename T1, typename... taOthers>
struct ElementType
{
  typedef typename ElementType<k-1, taOthers...>::TResult TResult;
};

template<typename T1, typename... taOthers>
struct ElementType<0, T1, taOthers...>
{
  typedef T1 TResult;
};

template<unsigned int k, typename T1, typename... taOthers>
struct Accessor
{
  static typename ElementType<k, T1, taOthers...>::TResult Get(Tuple<T1, taOthers...>& aTuple)
  {
    return Accessor<k-1, taOthers...>::Get(static_cast<Tuple<taOthers...>& >(aTuple));
  }
};

template<typename T1>
struct Accessor<0, T1>
{
  static T1 Get(Tuple<T1>& aTuple)
  {
    return aTuple.Head();
  }
};

template<unsigned int k, typename T1, typename... taOthers>
typename std::enable_if<k != 0,  typename ElementType<k, T1, taOthers...>::TResult>::type GetElement(Tuple<T1, taOthers...>& aTuple)
{
  return GetElement<k-1, taOthers...>(static_cast<Tuple<taOthers...>& >(aTuple));
}

template<unsigned int k, typename... taOthers>
typename std::enable_if<k == 0, typename ElementType<0, taOthers...>::TResult>::type GetElement(Tuple<taOthers...>& aTuple)
{
  return aTuple.Head();
}

template<typename T1, typename T2>
struct EqualTypes
{
  static const bool TResult = false; 
};

template<typename T1>
struct EqualTypes<T1, T1>
{
  const static bool TResult = true;
};

template<typename taWanted, typename T1, typename... taOthers>
typename std::enable_if<EqualTypes<taWanted, T1>::TResult, taWanted>::type  ExtractElement(Tuple<T1, taOthers...>& aTuple)
{
  return aTuple.Head();
}

template<typename taWanted, typename T1, typename... taOthers>
typename std::enable_if<!EqualTypes<taWanted, T1>::TResult, taWanted>::type  ExtractElement(Tuple<T1, taOthers...>& aTuple)
{
  return ExtractElement<taWanted, taOthers...>(static_cast<Tuple<taOthers...>& >(aTuple));
}

template<typename taWanted, typename T1>
typename std::enable_if<!EqualTypes<taWanted, T1>::TResult, taWanted>::type  ExtractElement(Tuple<T1>& aTuple)
{
  return taWanted();
}

class A {};

int main(int argc, char** argv)
{
  Tuple<int, double> t(1,2.0);
 
  ElementType<1, int, double>::TResult d;

  std::cout << Accessor<1, int, double>::Get(t) << std::endl;

  std::cout<< GetElement<1>(t) << std::endl;

  A a = ExtractElement<A>(t);

  //std::cout << result << std::endl;
  return 0;
}
