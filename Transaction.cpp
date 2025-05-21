#include "Transaction.h"
#include <cstddef>

Transaction::Transaction(string in_date, string in_type, float in_quantity,
                         float in_price, string in_ticker, string in_curr) {
  int res = set_date(in_date);
  if (res != 0) {
    cerr << "Failed to create transaction (date)." << endl;
  } else {
    res = set_type(in_type);
    if (res != 0) {
      cerr << "Failed to create transaction (type)." << endl;
    } else {

      res = set_quantity(in_quantity);
      if (res != 0) {
        cerr << "Failed to create transaction (quantity)." << endl;
      } else {
        res = set_price(in_price);
        if (res != 0) {
          cerr << "Failed to create transaction (price)." << endl;
        } else {
          res = set_ticker(in_ticker);
          if (res != 0) {
            cerr << "Failed to create transaction (ticker)." << endl;
          } else {
            res = set_curr(in_curr);
            if (res != 0) {
              cerr << "Failed to create transaction (curr)." << endl;
            }
          }
        }
      }
    }
  }
}

void Transaction::print() const {
  cout << "Transaction:" << "\n\tDate: " << date << "\n\tType: " << type
       << "\n\tQuantity: " << quantity << "\n\tPrice: " << price
       << "\n\tTicker: " << ticker << "\n\tPurchasing currency: " << curr
       << endl;
}

int Transaction::set_type(string in_type) {
  if (in_type != "DEPOSIT" && in_type != "CONVERT" && in_type != "BUY" &&
      in_type != "SELL" && in_type != "DIVIDEND") {
    cerr << "Invalid type provided: " << in_type
         << "\nMust be one of (DEPOSIT, CONVERT, BUY, SELL, DIVIDEND)" << endl;
  }

  type = in_type;
  return 0;
}

int Transaction::set_date(string &in_date) {
  if (in_date.size() != 10) {
    cerr << "Invalid date format, use YYYY-MM-DD" << endl;
    return 1;
  }
  strncpy(date, in_date.c_str(), sizeof(date));
  date[10] = '\0';
  return 0;
}

int Transaction::set_ticker(string in_ticker) {
  if (in_ticker.size() != 3 && in_ticker.size() != 4) {
    cerr << "Invalid ticker: " << in_ticker << endl;
    return 1;
  }
  ticker = in_ticker;
  return 0;
}

int Transaction::set_curr(string &in_curr) {
  if (in_curr.size() != 3) {
    cerr << "Invalid currency: " << in_curr << endl;
    return 1;
  }
  strncpy(curr, in_curr.c_str(), sizeof(curr));
  curr[3] = '\0';
  return 0;
}

// int main() {
//   Transaction t = Transaction("2024-03-01", "BUY", 10, 24.56, "NVDA", "USD");
//
//   t.print();
//
//   Transaction t1 =
//       Transaction("2024-03-01", "GOLDSD", 10, 24.56, "NVDA", "USD");
//
//   return 0;
// }
