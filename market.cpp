/** Implementation of functions related to a free market
@file market.cpp
@author Angel Fuentes
*/

#include "market.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

bool is_admin(const set<string>& admins, const string& user) {
  return admins.count(user) > 0;
}

bool upsert_item(const set<string>& admins, const string& user,
                 const string& item, int price, map<string, int>& catalog) {
  if (!is_admin(admins, user) || price <= 0) {
    return false;
  }

  if (catalog.count(item) > 0) {
    catalog.at(item) = price;
  } else {
    catalog.insert({item, price});
  }
  return true;
}

bool remove_item(const set<string>& admins, const string& user,
                 const string& item, map<string, int>& catalog) {
  if (!is_admin(admins, user) || catalog.count(item) <= 0) {
    return false;
  }
  catalog.erase(item);
  return true;
}

bool apply_sale(const set<string>& admins, const string& user, int percentage,
                map<string, int>& catalog) {
  if (!is_admin(admins, user) || percentage >= 100 || percentage <= 0) {
    return false;
  }

  for (const auto& [item, price] : catalog) {
    int new_price = price * (100 - percentage) / 100;
    catalog.at(item) = new_price > 0 ? new_price : 1;
  }
  return true;
}

vector<string> sell(const map<string, int>& catalog, const vector<string>& list,
                    int& wallet) {
  vector<string> leftovers;
  for (const string& item : list) {
    if (catalog.count(item) > 0) {
      wallet += catalog.at(item);
    } else {
      leftovers.push_back(item);
    }
  }
  return leftovers;
}

vector<string> buy(const map<string, int>& catalog, const vector<string>& list,
                   int& wallet) {
  vector<string> bought;
  int total = 0;

  for (const string& item : list) {
    if (catalog.count(item) > 0) {
      bought.push_back(item);
      total += catalog.at(item);
    }
  }

  if (total > wallet) {
    return {};
  }

  wallet -= total;
  return bought;
}

int hoard(const map<string, int>& catalog, int& wallet) {
  int min_price = -1;
  for (const auto& [item, price] : catalog) {
    if (min_price == -1 || price < min_price) {
      min_price = price;
    }
  }

  int amount = wallet / min_price;
  if (amount < 0 || min_price < 0) {
    return 0;
  }

  wallet -= amount * min_price;
  return amount;
}
