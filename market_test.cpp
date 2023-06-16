/** Test cases for functions defined in market.h
@file market_test.cpp
@author Angel Fuentes
*/

#include "market.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <map>
#include <set>
#include <vector>
using namespace std;
using ::testing::ContainerEq;

MATCHER_P(IsEqualToMap, expected_map, ::testing::PrintToString(expected_map)) {
  if (expected_map.size() != arg.size()) {
    return false;
  }
  return std::all_of(expected_map.cbegin(), expected_map.cend(),
                     [&](const std::pair<string, int>& item) {
                       const auto it = arg.find(item.first);
                       return it != arg.cend() && it->first == item.first &&
                              it->second == item.second;
                     });
}

TEST(MarketTest, IsAdmin) {
  set<string> admins = {"Alice", "Bob"};
  EXPECT_TRUE(is_admin(admins, "Alice"));
  EXPECT_FALSE(is_admin(admins, "bob"));
  EXPECT_FALSE(is_admin(admins, "Carl"));
}

// DO NOT MODIFY CODE ABOVE

TEST(MarketTest, UpsertRemoveItem) {
  set<string> admins = {"Alex", "Craig", "Nico"};

  map<string, int> catalog = {{"sushi", 8}, {"boba", 6}, {"cigars", 8}};

  EXPECT_FALSE(upsert_item(admins, "Chris", "Chips", 3, catalog));
  EXPECT_TRUE(remove_item(admins, "Alex", "cigars", catalog));
  EXPECT_TRUE(upsert_item(admins, "Craig", "mango", 4, catalog));
  EXPECT_TRUE(upsert_item(admins, "Nico", "ice cream", 5, catalog));
  EXPECT_FALSE(remove_item(admins, "Jerry", "ice cream", catalog));
  EXPECT_TRUE(upsert_item(admins, "Craig", "pizza", 10, catalog));
  EXPECT_FALSE(remove_item(admins, "Alex", "pickles", catalog));
  EXPECT_FALSE(remove_item(admins, "Blake", "cigars", catalog));

  map<string, int> expected = {
      {"sushi", 8}, {"boba", 6}, {"mango", 4}, {"ice cream", 5}, {"pizza", 10}};

  // Don't modify the next line.
  EXPECT_THAT(catalog, IsEqualToMap(expected));
}

TEST(MarketTest, ApplySale) {
  set<string> admins = {"Carl", "Craig", "Franky"};

  map<string, int> catalog = {{"sushi", 14}, {"Chicken", 13}, {"calamari", 16}};

  EXPECT_TRUE(apply_sale(admins, "Carl", 20, catalog));
  EXPECT_FALSE(apply_sale(admins, "Alex", 30, catalog));
  EXPECT_TRUE(apply_sale(admins, "Craig", 10, catalog));
  EXPECT_FALSE(apply_sale(admins, "Craig", -20, catalog));

  map<string, int> expected = {{"sushi", 9}, {"Chicken", 9}, {"calamari", 10}};

  // Don't modify the next line.
  EXPECT_THAT(catalog, IsEqualToMap(expected));
}

TEST(MarketTest, Sell) {
  int wallet;
  vector<string> to_sell;
  vector<string> expected_leftovers;
  int wallet_after;

  map<string, int> catalog = {{"sushi", 10},
                              {"boba", 8},
                              {"calamari", 14},
                              {"ice cream", 5},
                              {"pizza", 10}};

  // |--------- Test case ---------|
  wallet = 20;
  to_sell = {"calamari", "chips", "hot dog"};
  expected_leftovers = {"chips", "hot dog"};
  wallet_after = 34;

  // Don't modify the next 2 lines.
  EXPECT_THAT(sell(catalog, to_sell, wallet), ContainerEq(expected_leftovers));
  EXPECT_EQ(wallet, wallet_after);
  // |-----------------------------|

  // |--------- Test case2 ---------|
  wallet = 20;
  to_sell = {"calamari", "boba", "hot dog"};
  expected_leftovers = {"hot dog"};
  wallet_after = 42;

  // Don't modify the next 2 lines.
  EXPECT_THAT(sell(catalog, to_sell, wallet), ContainerEq(expected_leftovers));
  EXPECT_EQ(wallet, wallet_after);
  // |-----------------------------|
}

TEST(MarketTest, Buy) {
  int wallet;
  vector<string> to_buy;
  vector<string> expected_purchase;
  int wallet_after;

  map<string, int> catalog = {
      {"sushi", 8}, {"chips", 3}, {"avocado", 4}, {"tofu", 5}, {"hot dog", 6},
  };

  // |--------- Test case ---------|
  wallet = 30;
  to_buy = {"sushi", "avocado", "hot dog"};
  expected_purchase = {"sushi", "avocado", "hot dog"};
  wallet_after = 12;

  // Don't modify the next 2 lines.
  EXPECT_THAT(buy(catalog, to_buy, wallet), ContainerEq(expected_purchase));
  EXPECT_EQ(wallet, wallet_after);
  // |-----------------------------|

  // |--------- Test case2---------|
  wallet = 30;
  to_buy = {"cheese", "avocado", "hot dog"};
  expected_purchase = {"avocado", "hot dog"};
  wallet_after = 20;

  // Don't modify the next 2 lines.
  EXPECT_THAT(buy(catalog, to_buy, wallet), ContainerEq(expected_purchase));
  EXPECT_EQ(wallet, wallet_after);
  // |-----------------------------|
}

TEST(MarketTest, Hoard) {
  map<string, int> catalog;
  int wallet;
  int expected_amount_purchased;
  int wallet_after;

  // |--------- Test case ---------|
  catalog = {{"soda", 3}, {"boba", 5}, {"water", 4}};
  wallet = 14;
  expected_amount_purchased = 4;
  wallet_after = 2;

  // Don't modify the next 2 lines.
  EXPECT_EQ(hoard(catalog, wallet), expected_amount_purchased);
  EXPECT_EQ(wallet, wallet_after);
  // |-----------------------------|

  // |--------- Test case2 ---------|
  catalog = {{"cake", 10}, {"candy", 12}, {"water", 4}};
  wallet = 30;
  expected_amount_purchased = 7;
  wallet_after = 2;

  // Don't modify the next 2 lines.
  EXPECT_EQ(hoard(catalog, wallet), expected_amount_purchased);
  EXPECT_EQ(wallet, wallet_after);
  // |-----------------------------|
}
