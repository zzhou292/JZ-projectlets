// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class FoodRatings {
public:
  unordered_map<string, set<pair<int, string>>> c2fr; // cuisine to food
  unordered_map<string, string> f2c;                  // food to cuisine
  unordered_map<string, int> f2r;                     // food to rating

  FoodRatings(vector<string> &foods, vector<string> &cuisines,
              vector<int> &ratings) {
    for (int i = 0; i < foods.size(); i++) {
      c2fr[cuisines[i]].insert({-ratings[i], foods[i]});
      f2c[foods[i]] = cuisines[i];
      f2r[foods[i]] = ratings[i];
    }
  }

  void changeRating(string food, int newRating) {
    auto &cuisine = f2c.find(food)->second;
    c2fr[cuisine].erase({-f2r[food], food});
    c2fr[cuisine].insert({-newRating, food});
    f2r[food] = newRating;
  }

  string highestRated(string cuisine) { return c2fr[cuisine].begin()->second; }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */

int main() {
  vector<string> foods{"Pizza", "Pasta", "Burger", "Salad"};
  vector<string> cuisines{"Italian", "Italian", "American", "Healthy"};
  vector<int> ratings{4, 3, 2, 5};

  FoodRatings a(foods, cuisines, ratings);
  cout << a.highestRated("Italian") << endl;
  a.changeRating("Pizza", 1);
  cout << a.highestRated("Italian") << endl;

  return 0;
}