#include "Holding.h"

using namespace std;

Holding::Holding(float in_quantity, float in_price, string in_ticker,
                 string in_curr, string in_type) {
  set_quantity(in_quantity);
  set_price(in_price);
  set_ticker(in_ticker);
  set_curr(in_curr);
  set_type(in_type);
}

void Holding::print() const {
  cout << "Holding:" << "\n\tQuantity: " << quantity << "\n\tPrice: " << price
       << "\n\tTicker: " << ticker << "\n\tPurchasing currency: " << curr
       << "\n\tType: " << type << endl;
}

int Holding::set_ticker(string in_ticker) {
  if (in_ticker.size() != 3 && in_ticker.size() != 4) {
    cerr << "Invalid ticker: " << in_ticker << endl;
    return 1;
  }
  ticker = in_ticker;
  return 0;
}

int Holding::set_curr(string &in_curr) {
  if (in_curr.size() != 3) {
    cerr << "Invalid currency: " << in_curr << endl;
    return 1;
  }
  strncpy(curr, in_curr.c_str(), sizeof(curr));
  curr[3] = '\0';
  return 0;
}

// int main() {
//   Holding t = Holding(10, 24.56, "NVDA", "USD");
//
//   t.print();
//
//   Holding t1 = Holding(10, 24.56, "NVDA", "USDDS");
//
//   return 0;
// }
