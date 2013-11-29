#include <iostream>
#include <map>
 
using namespace std;
 
class Variavel;
 
class Polinomio {
 
public:
  Polinomio(int n) {
    termo[0] = n;
  }
  Polinomio(const Variavel& x, int n = 1) {
    termo[n] = 1;
  }
 
  Polinomio operator()(int n) const {
    Polinomio ret(*this);
    
    for (int i=1; i<n; i++) {
      ret = ret.produto(*this);
    }
    
    return ret;
  }
 
  Polinomio soma(const Polinomio& b) const {
    Polinomio ret(*this);
 
    for (auto iter = b.termo.begin(); iter != b.termo.end(); iter++) {
      ret.termo[iter->first] += iter->second;
    
      if (ret.termo[iter->first] == 0) {
        ret.termo.erase(iter->first);
      }
    }
 
      return ret;
    }
 
    Polinomio subtracao(const Polinomio& b) const {
      Polinomio ret(*this);
 
      for (auto iter = b.termo.begin(); iter != b.termo.end(); iter++) {
        ret.termo[iter->first] -= iter->second;
      
        if (ret.termo[iter->first] == 0) {
          ret.termo.erase(iter->first);
        }
      }
 
      return ret;
    }
 
    Polinomio produto(const Polinomio& b) const{
      Polinomio ret(0);
 
      for (auto iter = b.termo.begin(); iter != b.termo.end(); iter++) {
        for (auto iter2 = termo.begin(); iter2 != termo.end(); iter2++) {
          ret.termo[iter->first + iter2->first] += iter->second * iter2->second;
        
          if (ret.termo[iter->first + iter2->first] == 0) {
            ret.termo.erase(iter->first + iter2->first);
          }
        }
      }
 
      return ret;
    }
 
    ostream& print(ostream& o) const {
      for (auto iter = termo.crbegin(); iter != termo.crend(); iter++) {
 
        if (iter == termo.crbegin() && iter->second == -1) {
          o << "-";
        }else if (iter == termo.crbegin() && iter->second < 0) {
          o << iter->second;
        }else if ((iter->second != 0 && abs(iter->second) != 1) || iter->first == 0) {
          o << abs(iter->second); 
        }

        if (iter->first != 0) {
          if (iter->second > 1 || iter->second < -1) {
            o << "*";
          }
          
          o << "x";
          
          if (iter->first > 1) {
            o << "(" << iter->first << ")";
          }
        }
 
        if (next(iter) != termo.crend() && next(iter)->second > 0) {
          cout << " + ";
        }else if (next(iter) != termo.crend() && next(iter)->second < 0) {
          cout << " - ";
        }
 
      }
 
      return o;
    }
 
 
 
private:
  map<int, int> termo;
};
 
Polinomio operator + (const Polinomio& a, const Polinomio& b) {
  return a.soma(b);
}
 
Polinomio operator - (const Polinomio& a, const Polinomio& b) {
  return a.subtracao(b);
}
 
Polinomio operator * (const Polinomio& a, const Polinomio& b) {
  return a.produto(b);
}
 
Polinomio power(const Polinomio& a, int n) {
  return a(n);
}
 
ostream& operator << (ostream& o, const Polinomio& a) {
  return a.print(o);
}
 
class Variavel{
public:
  Polinomio operator () (int n) {
    return Polinomio(*this, n);
  }
};
 
int main(int argc, const char** argv) {
  Variavel x;
 
  Polinomio a = x(2) + x(3);
  Polinomio b = x + 2*x(3);
    
  cout << a + b << endl;
  
  return 0;
}