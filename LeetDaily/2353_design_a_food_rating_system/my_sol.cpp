// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class FoodRatings {
public:
  map<string, vector<pair<int, string>>> my_map;
  map<string, string> type_map;

  FoodRatings(vector<string> &foods, vector<string> &cuisines,
              vector<int> &ratings) {
    for (int i = 0; i < foods.size(); i++) {
      my_map[cuisines[i]].push_back({ratings[i], foods[i]});
      type_map[foods[i]] = cuisines[i];
    }
  }

  void changeRating(string food, int newRating) {
    string type = type_map[food];
    for (int i = 0; i < my_map[type].size(); i++) {
      if (my_map[type][i].second == food)
        my_map[type][i].first = newRating;
    }
  }

  string highestRated(string cuisine) {
    sort(my_map[cuisine].begin(), my_map[cuisine].end());
    vector<string> cand;
    int idx = my_map[cuisine].size() - 1;
    int top_rate = my_map[cuisine][idx].first;

    while (idx >= 0 && my_map[cuisine][idx].first == top_rate) {
      cand.push_back(my_map[cuisine][idx].second);
      idx--;
    }

    sort(cand.begin(), cand.end());

    return cand[0];
  }
};

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

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */