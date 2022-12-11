#include <bits/stdc++.h>
using namespace std;

template<class InputStream, class OutputStream> class IO {
  private:
    InputStream *is;
    OutputStream *os;

  public:
    IO(InputStream &_is, OutputStream &_os) : is(&_is), os(&_os) {}
    template<class T> IO& operator<<(const T var) { *os << var; return *this; }
    template<class T> IO& operator>>(T& var) { *is >> var; return *this; }
    void print() { *os << '\n'; }
    template<class T> void print(const T var) { *os << var << '\n'; }
    template<class T, class ...P> void print(const T var, P ...t) { *os << var << ' '; print(t...); }
    template<class T> void read(T& var) { *is >> var; }
    template<class T, class ...P> void read(T& var, P& ...t) { *is >> var; read(t...); }
    template<class T> T get() { return is->get(); }
    string getline() { string s; getline(*is, s); return s; }
    void optimize() { is->tie(0), os->tie(0), ios_base::sync_with_stdio(0); }
    bool eof() { return is->eof(); }
};

template<class IOStream> class Solver {
  private:
    IOStream io;

  public:
    Solver(IOStream _io) : io(_io) {
      int a, b, c;
      io.read(a, b, c);
      io.print(a, b, c);
    }
};


#ifndef TEST

using IOStream = IO<istream, ostream>;
int main() { Solver<IOStream>(IOStream(cin, cout)); }

#endif
