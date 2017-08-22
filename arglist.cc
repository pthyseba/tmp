#include <iostream>
using namespace std;

template<typename U, typename V>
struct EqualTypes
{
  const static bool TResult = false;
};

template<typename U>
struct EqualTypes<U, U>
{
  const static bool TResult = true;
};

class Empty {};

static const Empty __empty = Empty();

template<typename taHead, typename... taTail>
class List;

template<typename taHead>
class List<taHead>
{
public:
  List(taHead aHead) : iHead(aHead), iTail(Empty()) {}
  const taHead& Head() const {return iHead;}
  const Empty& Tail() const {return iTail;}
private:
  taHead iHead;
  Empty  iTail;
};

template<typename taHead, typename... taTail>
class List
{
public:
  List(taHead aHead, taTail... aTail) : iHead(aHead), iTail(List<taTail...>(aTail...)) {}
  const taHead& Head() const {return iHead;}
  const List<taTail...>& Tail() const {return iTail;}
private:
  taHead iHead;
  List<taTail...> iTail;
};

template<typename taSearch, typename taHead, typename... taTail>
struct InList;

template<typename taSearch, typename... taTail>
struct InList<taSearch, taSearch, taTail...>
{
  const static bool TResult = true;
};

template<typename taSearch, typename taOther>
struct InList<taSearch, taOther>
{
  const static bool TResult = EqualTypes<taSearch, taOther>::TResult;
};

template<typename taSearch, typename taHead, typename... taTail>
struct InList
{
  const static bool TResult = InList<taSearch, taTail...>::TResult;
};

template<typename taWanted, typename taHead, typename... taTail>
const taWanted Extract(const List<taHead, taTail...>& aList)
{
  if (EqualTypes<taWanted, taHead>::TResult)
  {
    return aList.Head();
  }
  else
  {
    return Extract<taWanted, taTail...>(aList.Tail());
  } 
}

template<typename taWanted, typename taOther>
const taWanted Extract(const List<taOther>& aList)
{
  if (EqualTypes<taWanted, taOther>::TResult)
  {
    return aList.Head();
  } 
  else
  {
    return taWanted();
  }
}
 

template<typename taHead, typename... taTail>
struct DeriveFrom; 

template<typename taBase>
struct DeriveFrom<taBase> : public taBase
{
};

template<typename taHead, typename... taTail>
struct DeriveFrom : public taHead, public DeriveFrom<taTail...>
{
};

enum class Product
{
  EDesktop = 0,
  EEmbedded
};


class A {};
class B {};
class C {};

template<enum Product>
struct Assembly;


template<>
struct Assembly<Product::EDesktop>
{
  typedef DeriveFrom<A,B> TResult;
};

template<>
struct Assembly<Product::EEmbedded>
{
  typedef DeriveFrom<A,C> TResult;
}; 


template<int n, typename taHead, typename... taTail>
struct TypeOf
{
  typedef typename TypeOf<n-1, taTail...>::TResult TResult;
}; 

template<typename taHead, typename... taTail>
struct TypeOf<0, taHead, taTail...>
{
  typedef taHead TResult;
};

template<int n, typename taHead, typename... taTail>
typename std::enable_if<n != 0, typename TypeOf<n, taHead, taTail...>::TResult>::type GetElement(const List<taHead, taTail...>& aList)
{
  return GetElement<n-1, taTail...>(aList.Tail());
}

template<int n, typename taHead>
typename std::enable_if<n == 0, taHead>::type GetElement(const List<taHead>& aList)
{
  return aList.Head();
}

int main(int argc, char** argv)
{
  List<int, double> l(1, 2.0);

  cout << InList<float, int, double>::TResult << endl;

  int i = Extract<int, int, double>(l);

  Assembly<Product::EDesktop>::TResult product;

  
  cout << i << endl;

  const auto a = GetElement<1, int, double>(l);

  cout << a << endl;
  return 0;
}
