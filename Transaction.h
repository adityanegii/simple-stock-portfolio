#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>

using namespace std;

class Transaction {
private:
  char date[11];
  string type;
  int quantity;
  float price;
  string ticker;
  char curr[4];

public:
  Transaction() {}

  Transaction(string in_date, string in_type, float in_quantity, float in_price,
              string in_ticker, string in_curr);
  void print() const;

  const char *get_date() { return date; }

  int set_date(string &in_date);

  string get_type() { return type; }

  int set_type(string in_type);

  float get_quantity() { return quantity; }

  int set_quantity(float in_quantity) {
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
