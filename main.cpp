#include "Portfolio.h"
#include <iostream>

using namespace std;

int main() {
  Portfolio p("My Portfolio", 9.95, 0.15);

  p.import_portfolio("transaction_history.csv");
  p.print_transactions();
  cout << "=====================" << endl;
  p.print_holdings();

  p.export_portfolio("transaction_history_export.csv");
}
