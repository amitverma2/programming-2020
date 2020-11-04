#include<iostream>
#include<vector>
#include<queue>
#include<string>

using namespace std;

class Solution {
    class CharCounts {
    public:
      int count;
      char ch;
      CharCounts() : count(0), ch(0) { }
      CharCounts(int _count, char _ch) : count(_count), ch(_ch) { }
      bool operator()(CharCounts const & c1, CharCounts const & c2) {
        if (c1.count < c2.count) return true;
        if (c1.count > c2.count) return false;
        if (c1.ch < c2.ch) return true;
        return false;
      }
    };
  
public:
    string reorganizeString(string S) {
      // count chars and use max heap to pick up top two chars and put them into string
      int N = S.length();
      int counts[26] = { 0 };
      for(char c : S) {
          counts[c-'a']++;
      }
      // add char + counts to max heap
      std::priority_queue<CharCounts, std::vector<CharCounts>, CharCounts> heap;
      for(int i = 0 ; i < 26; ++i) {
        if (counts[i])
          heap.push(CharCounts(counts[i], (char)('a'+i)));
      }
      string out;
      // construct string taking top two chars in the heap
      while (heap.size() > 1) {
        CharCounts top = heap.top();
        heap.pop();
        CharCounts next = heap.top();
        heap.pop();
        out += top.ch;
        out += next.ch;
        top.count--;
        next.count--;
        if (top.count) {
          heap.push(top);
        }
        if (next.count) {
          heap.push(next);
        }
      }
      if (heap.size() == 1) {
        CharCounts last = heap.top();
        heap.pop(); // not actually needed
        if (last.count > 1) {
          return "";
        }
        out += last.ch;
      }
      return out;
    }
};

int main() {
  //string str = "snnnnbpngobwznvnnnlnwhvnnnnfjnnlnnnnnnbnknnqkndzefncknnnnnaiqrntnndnnnjninnnunnunqhndnnqnnsjqnnpiqshntnnncnvnnnncnnqenlnninyndnnnljongnnjwnnnngllnnngkbnllnnnnontlbpngjnnenqnsnnnnnjeqqghnfpngepnodnnnnnnvnsrnughbnipvnhqmnzonoonnnjotnnonoennnpnfnnkdnnbmnmnpnqninnxronnnnvnlanlnnnebnnnlnvnfknsnbincnttnmnguqenhnnxunnnntnnnnhnqnzehvunfnvnndvnjnnnbnnpxnqipwnmnonnndlnsnonnninnxnnnjnnnnnesennmyiednnnnnnnnnhimtnnnonjlicnwnwvnntaxmnrntnnnnsnbnanninnecbcfjxncnnkvnnqgnunensanpnngjnzxjnopnnyvnnxskniyytnsnnnnx";
  string str = "tndsewnllhrtwsvxenkscbivijfqnysamckzoyfnapuotmdexzkkrpmppttficzerdndssuveompqkemtbwbodrhwsfpbmkafpwyedpcowruntvymxtyyejqtajkcjakghtdwmuygecjncxzcxezgecrxonnszmqmecgvqqkdagvaaucewelchsmebikscciegzoiamovdojrmmwgbxeygibxxltemfgpogjkhobmhwquizuwvhfaiavsxhiknysdghcawcrphaykyashchyomklvghkyabxatmrkmrfsppfhgrwywtlxebgzmevefcqquvhvgounldxkdzndwybxhtycmlybhaaqvodntsvfhwcuhvuccwcsxelafyzushjhfyklvghpfvknprfouevsxmcuhiiiewcluehpmzrjzffnrptwbuhnyahrbzqvirvmffbxvrmynfcnupnukayjghpusewdwrbkhvjnveuiionefmnfxao";
  //string str = "aab";

  Solution* obj = new Solution;
  string out = obj->reorganizeString(str);

  std::cout << "Input string: \n" << str << "\n Size = " << str.length() << std::endl;
  std::cout << "Output string: \n"<< out << "\n Size = " << out.length() << std::endl;

  return 0;
}