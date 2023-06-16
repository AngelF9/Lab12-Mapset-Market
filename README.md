# Lab 12: Mapset Market

In this lab, you will learn how to:
- use sets
- use maps

You will write a series of functions related to a free market (separated into 2 parts), then test them using the GoogleTest framework.

## File structure

* `Makefile` - Configuration for `make`.
* `market.cpp` - Your code goes here.
* `market_test.cpp` - Your tests go here.
* `market.h` - Header file for `market.cpp`, already written for you.
* `googletest/` - Contains code for the GoogleTest framework.

**Do not change any files other than `market.cpp` and `market_test.cpp`!**

## Make commands

You have the same `make` commands (format, test, all, clean) as usual except there is no `make build` command. **Don't use g++**.

## Program specifications

### The admin set

`set<string> admins`

This is a set of strings containing the names of market admins - those who are authorized to call the Part 1 functions and modify the catalog.

Eg. `{"Alice", "Bob"}` means Alice and Bob are admins.

### The catalog

`map<string, int> catalog`

This is a map of strings to ints (keys are strings and values are ints) that represents available items in the market and their associated price.

Eg. `{{"tuna", 7}, {"tofu", 4}}` means tuna sells for $7 and tofu sells for $4 on the market.

## Part 1

### 1.1 `is_admin()`

```c++
bool is_admin(
  const set<string>& admins,
  const string& user
);
```

Given the admin set and a user, return whether the user is an admin. Examples can be found in `TEST(MarketTest, IsAdmin)` which has already been written for you.

**TODO**: Complete the implementation for `is_admin()`.

### 1.2 `upsert_item()` and `remove_item()`

```c++
bool upsert_item(
  const set<string>& admins,
  const string& user,
  const string& item,
  int price,
  map<string, int>& catalog
);
```

Insert an item or update its price in the catalog.
* The user needs to be an admin. If not, return false.
* The price needs to be positive. If not, return false.
* If the item is already in the catalog, update its price in the catalog and return true.
* Otherwise, insert it into the catalog with its price and return true.

Eg.
```c++
set<string> admins = {"Alice"};
map<string, int> catalog = {{"tofu", 3}};
upsert_item(admins, "Bob", "fish", 9, catalog); // false, Bob is not an admin
upsert_item(admins, "Alice", "fish", 9, catalog); // true, fish inserted
// now catalog should have value {{"tofu", 3}, {"fish", 9}}
```

---

```c++
bool remove_item(
  const set<string>& admins,
  const string& user,
  const string& item,
  map<string, int>& catalog
);
```

Remove an item and its price from the catalog.
* The user needs to be an admin. If not, return false.
* The item needs to be in the catalog already. If not, return false.
* Erase the key-value pair that represents the item and its price from the catalog, then return true.

Eg.
```c++
set<string> admins = {"Alice"};
map<string, int> catalog = {{"tofu", 3}};
remove_item(admins, "Alice", "raisin", catalog); // false, raisin is not in the catalog
remove_item(admins, "Alice", "tofu", catalog); // true, tofu removed
// now catalog should have value {}
```

**TODO**: Complete the test case in `TEST(MarketTest, UpsertRemoveItem)`.
- Fill in the admin set.
- Fill in the catalog's starting state.
- Call `upsert_item()` and `remove_item()` at least 4 times each.
- Wrap each call in `EXPECT_FALSE` or `EXPECT_TRUE`.
- Fill the catalog's ending state.

**TODO**: Complete the implementation for `upsert_item()`.

**TODO**: Complete the implementation for `remove_item()`.

### 1.3 `apply_sale()`

```c++
bool apply_sale(
  const set<string>& admins,
  const string& user,
  int percentage,
  map<string, int>& catalog
);
```

Apply a percentage discount to all items in the catalog.
* The user needs to be an admin. If not, return false.
* The percentage needs to be between 1 and 99 (inclusive). If not, return false.
* Apply the discounts in the catalog directly, then return true.
* If a price would go below 1, set it to 1 instead.

Eg.
```c++
set<string> admins = {"Alice"};
map<string, int> catalog = {{"tofu", 1}, {"raisin", 10}};
apply_sale(admins, "Alice", 100, catalog); // false, can't apply a 100% discount
apply_sale(admins, "Alice", 20, catalog); // true, discounts applied
// now catalog should have value {{"tofu", 1}, {"raisin", 8}}
// 20% discount on $1 would be $0, so we set it to $1.
// 20% discount on $10 would be $8.
```

**TODO**: Complete the test case in `TEST(MarketTest, ApplySale)`.
- Fill in the admin set.
- Fill in the catalog's starting state.
- Call `apply_sale()` at least 4 times.
- Wrap each call in `EXPECT_FALSE` or `EXPECT_TRUE`.
- Fill the catalog's ending state.

**TODO**: Complete the implementation for `apply_sale()`.

## Part 2

### 2.1 `sell()`

```c++
vector<string> sell(
  const map<string, int>& catalog,
  const vector<string>& list,
  int& wallet
);
```

Sell a list of items according to the catalog prices.
* An item can only be sold if it has an entry in the catalog.
* Update the wallet amount depending on items sold.
* Return the leftover items that couldn't be sold, in order.

Eg.
```c++
map<string, int> catalog = {{"tofu", 1}, {"raisin", 10}};
int wallet = 20; // $20 at the start
vector<string> leftovers = sell(catalog, {"tofu", "raisin", "fish", "tofu", "pie"}, wallet);
// leftovers should have value {"fish", "pie"} since they're not in the catalog
// now wallet should have value 20 + 1 + 10 + 1 = 32
```

**TODO**: Complete the test case in `TEST(MarketTest, Sell)`.
- Fill in the catalog.
- Write at least 2 test cases. For each:
  - Fill in a starting wallet amount.
  - Fill in the items to sell.
  - Fill in the expected leftover items, in the correct order.
  - Fill in the expected wallet amount after the sale.

**TODO**: Complete the implementation for `sell()`.

### 2.2 `buy()`

```c++
vector<string> buy(
  const map<string, int>& catalog,
  const vector<string>& list,
  int& wallet
);
```

Buy a list of items according to the catalog prices.
* An item can be purchased if it has a price in the catalog.
* If the wallet can't afford all the items that can be purchased, buy nothing.
* Update the wallet amount depending on items purchased.
* Return the items purchased, in order.

Eg.
```c++
map<string, int> catalog = {{"tofu", 1}, {"raisin", 10}};
int wallet = 20; // $20 at the start
vector<string> purchase = buy(catalog, {"raisin", "tofu", "raisin"}, wallet);
// purchase should have value {} since total cost = 10 + 1 + 10 = 21 > 20
// wallet should still have value 20
purchase = buy(catalog, {"fish", "tofu", "raisin"}, wallet);
// purchase should have value {"tofu", "raisin"}
// now wallet should have value 20 - (1 + 10) = 9
```

**TODO**: Complete the test case in `TEST(MarketTest, Buy)`.
- Fill in the catalog.
- Write at least 2 test cases. For each:
  - Fill in a starting wallet amount.
  - Fill in the items to buy.
  - Fill in the expected purchased items, in the correct order.
  - Fill in the expected wallet amount after the purchase.

**TODO**: Complete the implementation for `buy()`.

### 2.3 `hoard()`

```c++
int hoard(
  const map<string, int>& catalog,
  int& wallet
);
```

Buy the most amount of items possible given the catalog prices.
* If there's a tie for the most amount of items purchased, do so while spending the least.
* Update the wallet amount depending on items purchased.
* Return the number of items purchased.

```c++
map<string, int> catalog = {{"tofu", 6}, {"raisin", 7}};
int wallet = 15; // $15 at the start
int amount_purchased = hoard(catalog, wallet); // can buy a maximum of 2 items
// now wallet should have value 15 - (2 * 6) = 3
```

**TODO**: Complete the test case in `TEST(MarketTest, Hoard)`.
- Write at least 2 test cases. For each:
  - Fill in the catalog.
  - Fill in a starting wallet amount.
  - Fill in the expected amount of items purchased.
  - Fill in the expected wallet amount after the purchase.

**TODO**: Complete the implementation for `hoard()`.
