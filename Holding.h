#ifndef HOLDING_H
#define HOLDING_H

#include <iostream>
#include <string>

using namespace std;

class Holding {
private:
  int quantity;
  float price;
  string ticker;
  char curr[4];

public:
  Holding() {}

  Holding(int in_quantity, float in_price, string in_ticker, string in_curr);
  void print() const;

  int get_quantity() { return quantity; }

  int set_quantity(int in_quantity) {
    quantity = in_quantity;
    return 0;
  }

  float get_price() { return price; }

  int set_price(float in_price) {
    price = in_price;
    return 0;
  }

  string get_ticker() { return ticker; }

  int set_ticker(string in_ticker);

  const char *get_curr() { return curr; }

  int set_curr(string &in_curr);
};

#endif
