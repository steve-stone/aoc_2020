#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <cassert>

using namespace std;

class Seat {
  private:
    int str_to_row(string seat_str);
    int str_to_col(string seat_str);
  public:
    Seat(string s);
    int row;
    int col;
    int seat_id;
};


vector<Seat> read_data(string day_num){

    ifstream ip("inputs/data" + day_num + ".txt");
    vector<Seat> result;
    string seat_str;

    while (getline(ip, seat_str)) {
      result.push_back(Seat(seat_str));
    }

    ip.close();
    
    return result;
}


Seat::Seat(string s) {
  regex seat_re("[F|B]{7}[L|R]{3}");
  if (!regex_match(s, seat_re)) {
    // TODO fix exception
    throw "invalid input";
  }
  row = str_to_row(s);
  col = str_to_col(s);
  seat_id = row * 8 + col;
}


int search(string dirs, int low, int high, char down, char up) {  
  float mid;
  for (char c : dirs) {
    mid = (float)(low) + (float)(high - low) / 2.0;
    if (c == down)
      high = (int)(mid - 0.5);
    if (c == up)
      low = (int)(mid + 0.5);
  }
  assert(low==high);
  return low;
}


int Seat::str_to_row(string x) {
  return search(x.substr(0,7), 0, 127, 'F', 'B');
}

int Seat::str_to_col(string x) {
  return search(x.substr(7,10), 0, 7, 'L', 'R');
}

int part1(vector<Seat> vec) {
  int max_id = 0;
  for (Seat i: vec)
    max_id = max(i.seat_id, max_id);
  return max_id;
}


int part2(vector<Seat> vec){
  vector<int> seat_ids;
  for (Seat i: vec)
    seat_ids.push_back(i.seat_id);

  sort(seat_ids.begin(), seat_ids.end());
  int last_id = seat_ids.at(0);
  for (int a : seat_ids) {
    if ((a-last_id) == 2)
      return last_id+1;
    last_id = a;
  }

  return 0;
}


void test() {
  string test = "FBFBBFFRLR";
  Seat s(test);
  cout << s.row << ',' << s.col << ',' << s.seat_id << "\n";
}

int main()
{
  vector<Seat> seats = read_data("05");
  cout << part1(seats) << "\n";
  cout << part2(seats) << "\n";
  return 0;
}
