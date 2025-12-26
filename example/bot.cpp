#include <iostream>
using namespace std;

int main() {
  int board_size, turns;
  cin >> board_size >> turns;

  int players;
  cin >> players;
  for (int p = 0; p < players; p++) {
    int row, col;
    cin >> row >> col;
  }

  for (int t = 0; t < turns; t++) {
    int agents;
    cin >> agents;

    for (int i = 0; i < agents; i++) {
      int row, col;
      string type;
      int dist;
      char rot;
      cin >> row >> col >> type >> dist >> rot;
    }

    for (int i = 0; i < agents; i++) {
      cout << "FIRE\n";
    }
    cout.flush();
  }
}
