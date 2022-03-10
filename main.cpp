#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

vector<double> pt_probs = {
  14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40, 0.02, 2.78, 4.74, 5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.10, 0.21, 0.01, 0.47
};

vector<double> en_probs = {
  8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.722, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

int mod (int num, int base) {
  int ret = num % base;
  if (ret < 0)
    ret += base;
  return ret;
}

string upperCase(string str, vector<bool> upper) {
  string ret;
  int size = str.size();
  for (int i = 0; i < size; i++) {
    if (upper[i]) ret.push_back(toupper(str[i]));
    else ret.push_back(str[i]);
  }  
  return ret;
}

pair<string, vector<bool>> lowerCase(string str) {
  string ret;
  int size = str.size();
  vector<bool> upper(size);
  for (int i = 0; i < size; i++) {
    upper[i] = str[i] >= 65 && str[i] <= 90;
    ret.push_back(tolower(str[i]));
  }
  pair<string, vector<bool>> ans = {ret, upper};
  return ans;
}

bool special_char (char c) {
  vector<char> char_list = {'.', ' ', ';', ',', '-', '\'', '"', '!', ':', '\r', '\n'};
  for (int i = 0; i < char_list.size(); i++) {
    if (c == char_list[i]) return true;
  }
  return false;
}

pair <string, vector<pair<char, int>>> filter(string str) {
  string ret;
  vector<pair<char, int>> special_char_map;
  for (int i = 0; i < str.size(); i++) {
    if (special_char(str[i])) {
      pair<char, int> p = {str[i], i};
      special_char_map.push_back(p);
    }
    else {
      ret.push_back(str[i]);
    }
  }
  return {ret, special_char_map};
}

string unfilter (string str, vector<pair<char, int>> pci) {
  string ret;
  bool flag = false;
  int i = 0, j = 0, k=0;
  while (j != pci.size()) {
    if (pci[j].second == k) {
      ret.push_back(pci[j].first);
      j++;
    }
    else {
      ret.push_back(str[i]);
      i++;
    }
    k++;
  }
  while (i != str.size()) {
    ret.push_back(str[i]);
  }
  return ret;
}

string code_decode (string wrd, string key, bool dcd) {
  int wrdIdx = 0, keyIdx = 0, wrdSize = wrd.size(), keySize = key.size();
  string ans;

  key = lowerCase(key).first;
  auto wrdPair = lowerCase(wrd);
  wrd = wrdPair.first;

  bool flag = true;
  while (flag) {
    char c;
    if (dcd == false) c = (((wrd[wrdIdx] + key[keyIdx])-194)%26)+97;
    else c = mod((wrd[wrdIdx] - key[keyIdx]),26)+97;
    ans.push_back(c);
    wrdIdx++;
    keyIdx = (keyIdx+1)%keySize;
    if (wrdIdx == wrdSize)
      flag = false;
  }

  return upperCase(ans, wrdPair.second);
}

string code(string wrd, string key) {
  return code_decode(wrd, key, 0);
}

string decode(string wrd, string key) {
  return code_decode(wrd, key, 1);
}

vector<int> trigram (string wrd) {
  vector<int> ret;
  for (int i = 0; i < wrd.size()-3; i++) {
    string tri = {wrd[i], wrd[i+1], wrd[i+2]};
    auto pos = wrd.find(tri, i+1);
    if (pos != string::npos) {
      ret.push_back(pos - i);
    }
  }
  return ret;
}

int key_size (vector<int> trigram_distances) {
  multiset<int> ms;
  for (int i = 0; i < trigram_distances.size(); i++) {
    for (int j = 2; j <= 20; j++) {
      if (trigram_distances[i]%j == 0) ms.insert(j);
    }
  }
  for (int j = 2; j <= 20; j++) {
    cout << j << " - " << ms.count(j) << endl;
  }
  return 0;
}

char shift_probs(vector<double> alph, vector<double> language) {
  pair<int, double> ret = {0, 10e3};
  for (int i = 0; i < 26; i++) {
    double diff = 0;
    for (int j = 0; j < 26; j++) {
      diff += abs(alph[mod(i + j, 26)] - language[j]);
    }
    if (diff < ret.second) {
      ret.second = diff;
      ret.first = i;
    }
  }
  return (char) (ret.first + 97);
}

pair<string, string> letter_frequency(string wrd, int key_s) {
  string key_pt;
  string key_en;
  for (int i = 0; i < key_s; i++) {
    multiset<char> ms;
    for (int pos = i; pos < wrd.size(); pos += key_s) {
      ms.insert(wrd[pos]);
    }
    vector<double> alph(26);
    int ltts_size = ms.size();
      double a = 0;
    for (int j = 0; j < 26; j++) {
      char c = j + 97;
      alph[j] = ((double) (((double)ms.count(c))/((double)ltts_size)))*100;
      a += alph [j];
    }
    key_pt.push_back(shift_probs(alph, pt_probs));
    key_en.push_back(shift_probs(alph, en_probs));
  }
  return {key_pt, key_en};
}

string read_file(string file_path) {
  ifstream f(file_path);
  stringstream buffer;
  buffer << f.rdbuf();
  auto s = buffer.str();
  return s;
}

pair<string, string> break_cipher(string file_path) {
  string wrd = read_file(file_path);
  auto ret_filter = filter(wrd);
  wrd = ret_filter.first;

  auto trigram_distances = trigram(wrd);
  key_size(trigram_distances);

  int key_s;
  cout << "Escolha um valor para a chave: "; 
  cin >> key_s;

  auto keys = letter_frequency(wrd, key_s);
  cout << "Chave em portugues encontrada: " << keys.first << endl << "Chave em ingles encontrada: " << keys.second << endl;

  pair<string, string> ret = {decode(wrd, keys.first), decode(wrd, keys.second)};
  ret = {unfilter(ret.first, ret_filter.second), unfilter(ret.second, ret_filter.second)};

  return ret;
}

int main () {
  string wrd, key;
  cout << "Palavra a ser cifrada: ";
  cin >> wrd;
  cout << "Chave de cifra: ";
  cin >> key;
  string cifrada = code(wrd, key);
  cout << "Cifrada: " << cifrada << endl;
  string decifrada = decode(cifrada, key);
  cout << "Decifrada: " << decifrada << endl;

  auto res = break_cipher("cifras/desafio1.txt");
  cout << res.first << endl << endl << res.second;

  return 0;
}