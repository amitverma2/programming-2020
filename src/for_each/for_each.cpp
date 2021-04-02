#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

map<string, int> frequency;

void counts(const string& s) { frequency[s]++; }
void print(const pair<string, int>& p) { cout << p.first << ' ' << p.second << '\n'; }

int main() {
    istream_iterator<string> ii(cin);
    istream_iterator<string> eos;

    for_each(ii, eos, counts);
    for_each(frequency.begin(), frequency.end(), print);
    return 0;
}
