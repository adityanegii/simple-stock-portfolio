#include "Portfolio.h"
#include "Transaction.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Portfolio::Portfolio(string in_name, float in_transaction_fee,
                     float in_dividend_tax) {
  name = in_name;
  transaction_fee = in_transaction_fee;
  dividend_tax = in_dividend_tax;
}

int Portfolio::add_transaction(string in_date, string in_type, int in_quantity,
                               float in_price, string in_ticker,
                               string in_curr) {
  Transaction t =
      Transaction(in_date, in_type, in_quantity, in_price, in_ticker, in_curr);

  int res = add_transaction(t);

  return res;
}

int Portfolio::add_transaction(Transaction t) {

  int res = update_holding(t);

  if (res != 0) {
    cerr << "Transaction failed." << endl;
    return 1;
  }

  if (!transactions.empty()) {
    string prev_date = transactions.back().get_date();
    string prev_year = prev_date.substr(0, 4);
    string t_date = t.get_date();
    string t_year = t_date.substr(0, 4);

    if (prev_year != t_year) {
      res = calculate_value(prev_year);
    }
  }

  transactions.push_back(t);

  return 0;
}

int Portfolio::update_holding(Transaction t) {
  string t_type = t.get_type();
  int res;
  if (t_type == "DEPOSIT") {
    res = handle_cash_update(t);
  } else {
    res = handle_stock_or_convert_update(t);
  }

  return res;
}

int Portfolio::handle_cash_update(Transaction t) {
  string t_type = t.get_type();

  auto cash_it = holdings.find(t.get_ticker());

  if (cash_it == holdings.end()) {
    add_holding(t.get_ticker(), Holding(0, 1, t.get_ticker(), t.get_curr()));

    cash_it = holdings.find(t.get_ticker());
  }

  Holding &cash = cash_it->second;
  cash.set_quantity(cash.get_quantity() + t.get_quantity());

  return 0;
}

int Portfolio::handle_stock_or_convert_update(Transaction t) {
  string t_type = t.get_type();

  auto hol_it = holdings.find(t.get_ticker());
  auto cash_it = holdings.find(t.get_curr());

  // Verify cash exists
  if (cash_it == holdings.end()) {
    // Throw error if no currency to convert
    if (t_type == "CONVERT") {
      cerr << "CAN'T CONVERT " << t.get_curr() << " TO " << t.get_ticker()
           << "SINCE NO " << t.get_curr() << " HELD" << endl;
      return 1;
    } else if (t_type == "BUY") {
      cerr << "CAN'T BUY, DO NOT HOLD " << t.get_curr() << endl;
      return 1;
    }
    add_holding(t.get_curr(), Holding(0, 1, t.get_curr(), t.get_curr()));

    cash_it = holdings.find(t.get_curr());
  }

  Holding &cash = cash_it->second;

  // Verify holding exists
  if (hol_it == holdings.end()) {
    // Throw error if no stock held if operation is dividend or sell
    if (t_type == "DIVIDEND") {
      cerr << "NO STOCK OF " << t.get_ticker() << endl;
      return 1;
    } else if (t_type == "SELL") {
      cerr << "NO HOLDINGS OF " << t.get_ticker() << " FOUND" << endl;
      return 1;
    }
    add_holding(t.get_ticker(), Holding(0, 0, t.get_ticker(), t.get_curr()));

    hol_it = holdings.find(t.get_ticker());
  }

  Holding &hol = hol_it->second;

  float cash_held = cash.get_quantity();
  float total_price = t.get_quantity() * t.get_price();

  if (t_type == "CONVERT") {

    if (cash_held < total_price) {
      cerr << "Insuffienct " << t.get_curr() << " to convert to "
           << t.get_ticker() << "." << endl;
      return 1;
    }

    cash.set_quantity(cash_held - total_price);
    hol.set_quantity(hol.get_quantity() + t.get_quantity());

  } else if (t_type == "BUY") {

    if (cash_held < total_price + transaction_fee) {
      cerr << "Insufficient cash for transaction." << endl;
      return 1;
    }

    cash.set_quantity(cash_held - transaction_fee - total_price);
    hol.set_quantity(hol.get_quantity() + t.get_quantity());

  } else if (t_type == "SELL") {

    if (cash_held < transaction_fee) {
      cerr << "Insufficient cash for transaction." << endl;
      return 1;
    }

    if (hol.get_quantity() < t.get_quantity()) {
      cerr << "Insuffient amount of " << t.get_ticker()
           << " held for sale transaction." << endl;
      return 1;
    }

    cash.set_quantity(cash_held - transaction_fee + total_price);
    hol.set_quantity(hol.get_quantity() - t.get_quantity());

  } else if (t_type == "DIVIDEND") {

    float tot_div = total_price * hol.get_quantity();
    cash.set_quantity(cash.get_quantity() + tot_div);

  } else {
    cerr << "INVALID TYPE: " << t_type << endl;
    return 1;
  }
  return 0;
}

int Portfolio::calculate_value(string year) { return 0; }

int main() {
  Portfolio p = Portfolio("My Portfolio", 9.95, 0.15);

  int res = p.add_transaction("2024-05-01", "DEPOSIT", 1000, 1.0, "CAD", "CAD");
  if (res != 0) {
    cerr << "PROBLEM IN ADDING TRANSACTION" << endl;
    return 1;
  }
  cout << "SUCCESSFULLY ADDED TRANSACTION" << endl;
  p.print_transactions();
  cout << "\n===================================\n" << endl;

  p.print_holdings();

  cout << "\n===================================\n" << endl;
  p.add_transaction("2024-05-01", "BUY", 10, 10.95, "NVDA", "USD");

  p.print_holdings();
  res = p.add_transaction("2024-05-01", "DEPOSIT", 1000, 1.0, "CAD", "CAD");
  res = p.add_transaction("2025-05-01", "DEPOSIT", 1000, 1.0, "CAD", "CAD");
  cout << "\n===================================\n" << endl;
  p.print_holdings();
  return 0;
}
