#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Holding.h"
#include "Transaction.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Portfolio {
private:
  string name;
  vector<class Transaction> transactions;        // All transactions
  unordered_map<string, class Holding> holdings; // Current holdings
  float transaction_fee;
  float dividend_tax;
  vector<int> value_yoy;

public:
  Portfolio() {}

  Portfolio(string in_name, float in_transaction_fee, float in_dividend_tax);

  string get_name() { return name; }
  int set_name(string in_name) {
    name = in_name;
    return 0;
  }

  int add_transaction(string in_date, string in_type, int in_quantity,
                      float in_price, string in_ticker, string in_curr);
  int add_transaction(Transaction t);

  int update_holding(Transaction t);

  // Helper functions for update_holding
  int handle_cash_update(Transaction t);
  int handle_stock_or_convert_update(Transaction t);

  void add_holding(string ticker, Holding h) { holdings.insert({ticker, h}); }

  int calculate_value(string year);

  int export_portfolio(const string &filename);

  int import_portfolio(const string &filename);

  void print_holdings() const {
    cout << "PRINTING HOLDINGS" << endl;
    for (auto it = holdings.begin(); it != holdings.end(); it++) {
      it->second.print();
    }
  }

  void print_transactions() const {
    cout << "PRINTING TRANSACTIONS" << endl;
    for (int i = 0; i < transactions.size(); i++) {
      transactions.at(i).print();
    }
  }
};

#endif
