#include <iostream>
#include <vector>

using namespace std;

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
  return 0;
}