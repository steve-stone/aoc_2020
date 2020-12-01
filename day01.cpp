#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

vector<int> read_data(string day_num){

    ifstream ip("inputs/data" + day_num + ".txt");

    vector<int> result;
    string line;

    while (getline(ip, line)) {
      result.push_back(stoi(line));
    }

    ip.close();
    
    return result;
}

void part1(vector<int> res) {
  int vec_len = res.size();
  for(int i = 0; i < vec_len-1; i++)
  {
    int target = 2020 - res.at(i);
    for(int j = i+1; j<vec_len; j++)
    {
      if (res.at(j)==target)
      {
        cout << res.at(i) * res.at(j) << "\n";
      }
    }
  }
}

void part2(vector<int> res) {
  int vec_len = res.size();
  for(int i = 0; i < vec_len-2; i++)
  {
    int target1 = 2020 - res.at(i);
    for(int j = i+1; j<vec_len-1; j++)
    {
      int target2 = target1 - res.at(j);
      for(int k = j+1; k<vec_len; k++)
      {
        if (res.at(k)==target2)
        {
          cout << res.at(i) * res.at(j) * res.at(k) << "\n";
        }
      }
    }
  }
}

int main()
{
  vector<int> res = read_data("01");
  part1(res);
  part2(res);
  return 0;
}
