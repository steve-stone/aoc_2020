#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <map>

using namespace std;

vector<string> read_data(string file){

    ifstream ip("inputs/" + file + ".txt");
    vector<string> result;
    string s;

    while (getline(ip, s)) {
      result.push_back(s);
    }

    ip.close();
    
    return result;
}


void add_bag_from_str(string x, map<string, vector<pair<string, int>>> &capacity) {
  stringstream ss(x);
  string key_type;
  string key_type2;
  string val_type;
  string val_type2;
  ss >> key_type;
  ss >> key_type2;
  key_type += " " + key_type2;
  assert(capacity.find(key_type) == capacity.end()); // make sure it's not here
  vector<pair<string, int>> v;
  
  string tmp;
  ss >> tmp;
  assert(tmp=="bags");
  ss >> tmp;
  assert(tmp=="contain");
  
  string count_str;
  int count;
  while ( tmp.at(tmp.length()-1) != '.' ) {
    ss >> count_str;
    if (count_str == "no")
      break;
    count = stoi(count_str);
    ss >> val_type;
    ss >> val_type2;

    val_type += " " + val_type2;

    v.push_back( make_pair( val_type, count ) );
    ss >> tmp;
    assert ( tmp == "bag," || tmp == "bags," || tmp == "bag." || tmp == "bags."); 
  }
  capacity[key_type] = v;
  
}

map<string, bool> cache;

bool search(string key,
            vector<pair<string, int>> v,
            string tgt, 
            map<string, vector<pair<string, int>>> cap) {

  if ( cache.find(key) != cache.end() ) {
    return cache[key];
  }
  for (auto p: v) {
    if (p.first == tgt) {
      cache[key] = true;
      return true;
    } else {
      if (search(p.first, cap[p.first], tgt, cap)) {
        cache[key] = true;
        return true;
      }
    }
  }
  cache[key] = false;
  return false;
}


int part1(vector<string> vec) {
  map<string, vector<pair<string, int>>> capacity;
  map<string, vector<string>> bags;
  for (string s : vec) {
    add_bag_from_str(s, capacity);
  }

  int count = 0;
  string key;
  vector<pair<string, int>> val;
  for (auto it = capacity.begin(); it != capacity.end(); ++it) {
    key = it -> first;
    val = it -> second;
    if (search(key, val, "shiny gold", capacity)) {
      count++;
    }
  }
  
  return count;
}


int capacity_of(string tgt, map<string, vector<pair<string, int>>> cap) {
  if (cap[tgt].size() == 0) {
    return 0;
  }
  int count = 0;
  for (auto p : cap[tgt]) {
    count += p.second + p.second * capacity_of(p.first, cap);
  }

  return count;
}

int part2(vector<string> vec) {
  map<string, vector<pair<string, int>>> capacity;
  for (string s : vec) {
    add_bag_from_str(s, capacity);
  }
  int x = capacity_of("shiny gold", capacity);
  return x;
}


int main()
{
  vector<string> answers = read_data("data07");
  cout << part1(answers) << "\n";
  cout << part2(answers) << "\n";
  //vector<string> t2 = read_data("testdata07");
  //cout << part2(t2) << endl;
  return 0;
}
