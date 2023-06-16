/** Header file for market.cpp. Do not alter this file.
@file market.h
@author Hong Tai Wei
*/

#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

#ifndef MARKET_H
#define MARKET_H

// Admin functions

// Returns whether user is part of the set of admins.
bool is_admin(const set<string>& admins, const string& user);

// Inserts or updates an item's price in the catalog.
// The user needs to be an admin and the price needs to be positive.
// Returns whether the operation succeeded.
bool upsert_item(const set<string>& admins, const string& user,
                 const string& item, int price, map<string, int>& catalog);

// Removes an item from the catalog.
// The user needs to be an admin and the item has to be in the catalog.
// Returns whether the operation succeeded.
bool remove_item(const set<string>& admins, const string& user,
                 const string& item, map<string, int>& catalog);

// Applies a percentage discount to all items in the catalog.
// The user needs to be an admin and the percentage between 1 and 99.
// If a price goes below 1, it is set to 1.
// Returns whether the operation succeeded.
bool apply_sale(const set<string>& admins, const string& user, int percentage,
                map<string, int>& catalog);

// User functions

// Attempts to sell a list of items according to the catalog prices.
// An item can be sold if it has a price in the catalog.
// Updates the wallet amount depending on items sold.
// Returns the leftover items that couldn't be sold, in order.
vector<string> sell(const map<string, int>& catalog, const vector<string>& list,
                    int& wallet);

// Attempts to buy a list of items according to the catalog prices.
// An item can be purchased if it has a price in the catalog.
// If the wallet can't afford all the items that can be purchased, buy nothing.
// Updates the wallet amount depending on items purchased.
// Returns the items purchased, in order.
vector<string> buy(const map<string, int>& catalog, const vector<string>& list,
                   int& wallet);

// Attempts to buy the most amount of items from the catalog.
// If there's a tie, do so while spending the least.
// Updates the wallet amount depending on items purchased.
// Returns the number of items purchased.
int hoard(const map<string, int>& catalog, int& wallet);

#endif  // MARKET_H
