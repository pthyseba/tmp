class Empty
{
};

template<typename THead, typename... TTail>
class List
{
public:
  List(THead aHead, TTail... aTail)
    : iHead(aHead), iTail(List<TTail...>(aTail...)) {} 

  THead& Head() {return iHead;}
private:
  THead iHead;
  List<TTail...> iTail;
};

template<typename THead>
class List<THead>
{
public:
  List(THead aHead) : iHead(aHead), iTail(Empty()) {}
  THead& Head() {return iHead;}
private:
  THead iHead;
  Empty iTail;
};

int main(int argc, char** argv)
{
  int i = 1;
  double d = 2.0;
  List<int, double> l(i, d);
  int a = l.Head();
  return 0;
}
