#ifndef HOLDING_H
#define HOLDING_H

#include <iostream>
#include <string>

using namespace std;

class Holding {
private:
  float quantity;
  float price;
  string ticker;
  char curr[4];
  string type;

public:
  Holding() {}

  Holding(float in_quantity, float in_price, string in_ticker, string in_curr,
          string in_type);
  void print() const;

  float get_quantity() { return quantity; }

  float set_quantity(float in_quantity) {
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

  int set_type(string in_type) {
    if (in_type != "CASH" && in_type != "STOCK") {
      cerr << "INVALID TYPE FOR HOLDING" << endl;
      return 1;
    }

    type = in_type;
    return 0;
  }

  string get_type() { return type; }
};

#endif
