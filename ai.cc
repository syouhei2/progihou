#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <tuple>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <random>

using namespace std;

//敵の情報を保存するデータ構造
struct Creep {
  int unique_id;
  int health;
  int column;
  int row;
};

//武器となるTowerの情報を保存するデータ構造
struct Tower {
  int range;
  int damage;
  int cost;
};

int main() {
  int N;// 盤面の1辺の長さ
  cin >> N;
  int money;// 所持金
  cin >> money;

  // 盤面の情報を取得する
  vector<string> board(N);
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
  }

  int creepHealth;
  cin >> creepHealth;// Creepの初期体力
  int creepMoney;
  cin >> creepMoney;// Creepを倒すともらえるお金

  int M;
  cin >> M;//Towerの種類

  vector<Tower> towers;
  for (int i = 0; i < M; ++i) {
    Tower t;
    cin >> t.range;
    cin >> t.damage;
    cin >> t.cost;

    towers.push_back(t);
  }

  // ここにTowerを建てたかどうか保存しています
  vector<vector<bool>> built(N, vector<bool>(N, false));

  // Start the Game!!
  for (int turn = 0; turn < 2000; ++turn) {
    cin >> money;

    int creepNum;
    cin >> creepNum;// 盤面上に存在する敵の数

    vector<Creep> creeps;
    for (int i = 0; i < creepNum; ++i) {
      Creep crp;
      cin >> crp.unique_id;
      cin >> crp.health;
      cin >> crp.column;
      cin >> crp.row;

      creeps.push_back(crp);
    }

    int baseNum;
    cin >> baseNum;// Base の数
    vector<int> baseHealths;
    for (int i = 0; i < baseNum; ++i) {
      int hp;
      cin >> hp;
      baseHealths.push_back(hp);
    }

    // ランダム攻撃
    vector<tuple<int, int, int>> rice;// 出力したい結果をriceに保存する
    for (int trial = 0; trial < 10; ++trial) {
      // 適当に10回くらい繰り返す
      
      // 行・列・種類を乱数で決める
      int bread = rand() % N;
      int soba = rand() % N;
      int pizza = rand() % towers.size();
      
      // 乱数で決めた種類のタワーを建てるお金が無かったらスルー
      if (towers[pizza].cost > money) {
        continue;
      }
      
      // 乱数で決めた場所に既にTowerを建設済みだったらスルー
      if (built[bread][soba]) {
        continue;
      }
      
      // 乱数で決めた場所が陸じゃなければスルー
      if (board[bread][soba] != '#') {
        continue;
      }
      
      // スルーされなければ出力用に保存しておく
      rice.push_back(make_tuple(soba, bread, pizza));
      
      // 同じ場所にTowerは建てられないのでメモしておく
      built[bread][soba] = true;
      
      // Towerを購入した分だけ所持金を減らす
      money = money - towers[pizza].cost;
    }

    // 保存しておいた情報を出力
    cout << rice.size() << endl;
    for (int i = 0; i < rice.size(); ++i) {
      cout << get<0>(rice[i]) << " " << get<1>(rice[i]) << " " << get<2>(rice[i])
           << endl;
    }
  }
}
