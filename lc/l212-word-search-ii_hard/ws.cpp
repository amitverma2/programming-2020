#include<iostream>
#include<vector>
#include<string>
using namespace std;

#define __DO_PRUNING

class Solution_TLE {
  unsigned long long int count;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        count = 0;
        vector<string> out;
        for (int i = 0; i < words.size(); ++i) {
            if (found(board, words[i])) {
                out.push_back(words[i]);
            }
        }
        cout << "Count : " << count << endl;
        return out;
    }
    bool found(vector<vector<char>>& board, string& word) {
        // words[i] is always >=1
        char c = word[0];
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == c) {
                    // check if from this position this word can be found
                    bool visited[12][12] = { 0 };
                    if (foundFromPos(i, j, board, word, 0, visited)) {
                        //cout << "i =" << i << " j = " << j << endl;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    bool foundFromPos(int i, int j, vector<vector<char>>& board, string& word, int pos, bool visited[12][12]) {
      count++;
        //cout << "i " << i << " j " << j << " pos " << pos << " s " << word << endl;
        if (pos == word.length()) return true;

        if (board[i][j] != word[pos]) return false;
        
        if (pos == word.length() - 1) return true;
        
        visited[i][j] = true; // mark this position as visited
        
        bool saved[12][12] = { 0 };
        
        if (i > 0) {
            saveVisited(visited, saved);
            if (!visited[i-1][j] && foundFromPos(i - 1, j, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        if (i < (board.size() - 1)) {
            saveVisited(visited, saved);
            if (!visited[i+1][j] && foundFromPos(i + 1, j, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        if (j > 0) {
            saveVisited(visited, saved);
            if (!visited[i][j-1] && foundFromPos(i, j - 1, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        if (j < (board[i].size() - 1)) {
            saveVisited(visited, saved);
            if (!visited[i][j+1] && foundFromPos(i, j + 1, board, word, pos+1, visited)) {
                restoreVisited(saved, visited);
                return true;
            }
            restoreVisited(saved, visited);
        }
        return false;
    }
    
    void saveVisited(bool v[12][12], bool s[12][12]) {
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                s[i][j] = v[i][j];
    }
    
    void restoreVisited(bool s[12][12], bool v[12][12]) {
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                v[i][j] = s[i][j];
    }
};

class Solution2 {
  unsigned long long int count;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        count = 0;
        vector<string> out;
        for (int i = 0; i < words.size(); ++i) {
            if (found(board, words[i])) {
                out.push_back(words[i]);
            }
        }
        cout << "Count : " << count << endl;
        return out;
    }
    bool found(vector<vector<char>>& board, string& word) {
        // words[i] is always >=1
        char c = word[0];
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == c) {
                    if (foundFromPos(i, j, board, word, 0)) {
                        //cout << "i =" << i << " j = " << j << endl;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    bool foundFromPos(int i, int j, vector<vector<char>>& board, string& word, int pos) {
      count++;
        //cout << "i " << i << " j " << j << " pos " << pos << " s " << word << endl;
        if (pos == word.length()) return true;

        if (board[i][j] != word[pos]) return false;
        
        if (pos == word.length() - 1) return true;

        char saved = board[i][j];

        board[i][j] = '#'; // mark visited

        if (i > 0) {
            if (board[i-1][j] != '#' && foundFromPos(i - 1, j, board, word, pos+1)) {
                board[i][j] = saved;
                return true;
            }
        }
        if (i < (board.size() - 1)) {
            if (board[i+1][j] != '#' && foundFromPos(i + 1, j, board, word, pos+1)) {
                board[i][j] = saved;
                return true;
            }
        }
        if (j > 0) {
            if (board[i][j-1] != '#' && foundFromPos(i, j - 1, board, word, pos+1)) {
                board[i][j] = saved;
                return true;
            }
        }
        if (j < (board[i].size() - 1)) {
            if (board[i][j+1] != '#' && foundFromPos(i, j + 1, board, word, pos+1)) {
                board[i][j] = saved;
                return true;
            }
        }
        board[i][j] = saved;
        return false;
    }
    
    void saveVisited(bool v[12][12], bool s[12][12]) {
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                s[i][j] = v[i][j];
    }
    
    void restoreVisited(bool s[12][12], bool v[12][12]) {
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j)
                v[i][j] = s[i][j];
    }
};

class Solution {
  struct TrieNode {
    string word;
    bool eow;
    TrieNode * children[26];
    TrieNode() : eow(false) { for (int i = 0; i < 26; ++i) children[i] = NULL; }
  };
  TrieNode * root;
  unsigned long long int count;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
      vector<string> out;
      makeDictionary(words);

      count = 0;

      for (int r = 0; r < board.size(); ++r) {
        for (int c = 0; c < board[r].size(); ++c) {
          TrieNode* cur = (root->children)[board[r][c] - 'a'];
          if (cur) {
            findWordsTrie(board, r, c, root, out);
          }
        }
      }
      cout << "Count = " << count << endl;
      return out;
    }
    void findWordsTrie(vector<vector<char>>& board, int r, int c, TrieNode* node, vector<string>& out) {
      
      ++count;
      char saved = board[r][c];
      if (saved == '#') return;
      board[r][c] = '#'; // mark visited

      TrieNode* cur = (node->children)[saved - 'a'];

      if (cur->eow) {
        out.push_back(cur->word);
        cur->eow = false;
        cur->word = "";
      }

      int offsets[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
      for (int i = 0 ; i < 4; ++i) {
        int r_next = r + offsets[i][0];
        int c_next = c + offsets[i][1];
        if (r_next >= 0 && r_next < board.size() && c_next >= 0 && c_next < board[r_next].size()) {
          int next_char = board[r_next][c_next];
          if (next_char != '#') {
            TrieNode* next_node = (cur->children)[next_char - 'a'];
            if (next_node) {
              findWordsTrie(board, r_next, c_next, cur, out);
            }
          }
        }
      }
      board[r][c] = saved;
#ifdef __DO_PRUNING
      // prune
      if (isLeaf(cur)) {
        delete cur;
        (node->children)[saved - 'a'] = NULL;
      }
#endif // __DO_PRUNING
    }
    bool isLeaf(TrieNode* node) {
      for (int i = 0 ; i < 26; ++i) {
        if ((node->children)[i]) {
          return false;
        }
      }
      return true;
    }
    void makeDictionary(vector<string>& words) {
      root = new TrieNode();
      for (int i = 0 ; i < words.size(); ++i) {
        addToDictionary(root, words[i]);
      }
    }
    void addToDictionary(TrieNode* root, string& word) {
      TrieNode* cur = root;
      string::const_iterator i = word.begin();
      while (i != word.end()) {
        if ((cur->children)[*i - 'a'] == NULL) {
          (cur->children)[*i - 'a'] = new TrieNode();
        }
        cur = (cur->children)[*i - 'a'];
        ++i;
      }
      cur->eow = true;
      cur->word = word;
    }
};

int main (void) {
  //Solution2* obj = new Solution2();
  Solution* obj = new Solution();
  //Solution_TLE* obj = new Solution_TLE();
  vector<vector<char>> board = {
    { 'o', 'a', 'a', 'n' },
    { 'e', 't', 'a', 'e' },
    { 'i', 'h', 'k', 'r' },
    { 'i', 'f', 'l', 'v' },
  };
  vector<string> words = {
    "oath",
    "pea",
    "eat",
    "rain",
  };

vector<vector<char>> board2 = {
{'b','a','b','a','b','a','b','a','b','a'},{'a','b','a','b','a','b','a','b','a','b'},{'b','a','b','a','b','a','b','a','b','a'},{'a','b','a','b','a','b','a','b','a','b'},{'b','a','b','a','b','a','b','a','b','a'},{'a','b','a','b','a','b','a','b','a','b'},{'b','a','b','a','b','a','b','a','b','a'},{'a','b','a','b','a','b','a','b','a','b'},{'b','a','b','a','b','a','b','a','b','a'},{'a','b','a','b','a','b','a','b','a','b'}
};
vector<string> words2 = {
"ababababaa","ababababab","ababababac","ababababad","ababababae","ababababaf","ababababag","ababababah","ababababai","ababababaj","ababababak","ababababal","ababababam","ababababan","ababababao","ababababap","ababababaq","ababababar","ababababas","ababababat","ababababau","ababababav","ababababaw","ababababax","ababababay","ababababaz","ababababba","ababababbb","ababababbc","ababababbd","ababababbe","ababababbf","ababababbg","ababababbh","ababababbi","ababababbj","ababababbk","ababababbl","ababababbm","ababababbn","ababababbo","ababababbp","ababababbq","ababababbr","ababababbs","ababababbt","ababababbu","ababababbv","ababababbw","ababababbx","ababababby","ababababbz","ababababca","ababababcb","ababababcc","ababababcd","ababababce","ababababcf","ababababcg","ababababch","ababababci","ababababcj","ababababck","ababababcl","ababababcm","ababababcn","ababababco","ababababcp","ababababcq","ababababcr","ababababcs","ababababct","ababababcu","ababababcv","ababababcw","ababababcx","ababababcy","ababababcz","ababababda","ababababdb","ababababdc","ababababdd","ababababde","ababababdf","ababababdg","ababababdh","ababababdi","ababababdj","ababababdk","ababababdl","ababababdm","ababababdn","ababababdo","ababababdp","ababababdq","ababababdr","ababababds","ababababdt","ababababdu","ababababdv","ababababdw","ababababdx","ababababdy","ababababdz","ababababea","ababababeb","ababababec","ababababed","ababababee","ababababef","ababababeg","ababababeh","ababababei","ababababej","ababababek","ababababel","ababababem","ababababen","ababababeo","ababababep","ababababeq","ababababer","ababababes","ababababet","ababababeu","ababababev","ababababew","ababababex","ababababey","ababababez","ababababfa","ababababfb","ababababfc","ababababfd","ababababfe","ababababff","ababababfg","ababababfh","ababababfi","ababababfj","ababababfk","ababababfl","ababababfm","ababababfn","ababababfo","ababababfp","ababababfq","ababababfr","ababababfs","ababababft","ababababfu","ababababfv","ababababfw","ababababfx","ababababfy","ababababfz","ababababga","ababababgb","ababababgc","ababababgd","ababababge","ababababgf","ababababgg","ababababgh","ababababgi","ababababgj","ababababgk","ababababgl","ababababgm","ababababgn","ababababgo","ababababgp","ababababgq","ababababgr","ababababgs","ababababgt","ababababgu","ababababgv","ababababgw","ababababgx","ababababgy","ababababgz","ababababha","ababababhb","ababababhc","ababababhd","ababababhe","ababababhf","ababababhg","ababababhh","ababababhi","ababababhj","ababababhk","ababababhl","ababababhm","ababababhn","ababababho","ababababhp","ababababhq","ababababhr","ababababhs","ababababht","ababababhu","ababababhv","ababababhw","ababababhx","ababababhy","ababababhz","ababababia","ababababib","ababababic","ababababid","ababababie","ababababif","ababababig","ababababih","ababababii","ababababij","ababababik","ababababil","ababababim","ababababin","ababababio","ababababip","ababababiq","ababababir","ababababis","ababababit","ababababiu","ababababiv","ababababiw","ababababix","ababababiy","ababababiz","ababababja","ababababjb","ababababjc","ababababjd","ababababje","ababababjf","ababababjg","ababababjh","ababababji","ababababjj","ababababjk","ababababjl","ababababjm","ababababjn","ababababjo","ababababjp","ababababjq","ababababjr","ababababjs","ababababjt","ababababju","ababababjv","ababababjw","ababababjx","ababababjy","ababababjz","ababababka","ababababkb","ababababkc","ababababkd","ababababke","ababababkf","ababababkg","ababababkh","ababababki","ababababkj","ababababkk","ababababkl","ababababkm","ababababkn","ababababko","ababababkp","ababababkq","ababababkr","ababababks","ababababkt","ababababku","ababababkv","ababababkw","ababababkx","ababababky","ababababkz","ababababla","abababablb","abababablc","ababababld","abababable","abababablf","abababablg","abababablh","ababababli","abababablj","abababablk","ababababll","abababablm","ababababln","abababablo","abababablp","abababablq","abababablr","ababababls","abababablt","abababablu","abababablv","abababablw","abababablx","abababably","abababablz","ababababma","ababababmb","ababababmc","ababababmd","ababababme","ababababmf","ababababmg","ababababmh","ababababmi","ababababmj","ababababmk","ababababml","ababababmm","ababababmn","ababababmo","ababababmp","ababababmq","ababababmr","ababababms","ababababmt","ababababmu","ababababmv","ababababmw","ababababmx","ababababmy","ababababmz","ababababna","ababababnb","ababababnc","ababababnd","ababababne","ababababnf","ababababng","ababababnh","ababababni","ababababnj","ababababnk","ababababnl","ababababnm","ababababnn","ababababno","ababababnp","ababababnq","ababababnr","ababababns","ababababnt","ababababnu","ababababnv","ababababnw","ababababnx","ababababny","ababababnz","ababababoa","ababababob","ababababoc","ababababod","ababababoe","ababababof","ababababog","ababababoh","ababababoi","ababababoj","ababababok","ababababol","ababababom","ababababon","ababababoo","ababababop","ababababoq","ababababor","ababababos","ababababot","ababababou","ababababov","ababababow","ababababox","ababababoy","ababababoz","ababababpa","ababababpb","ababababpc","ababababpd","ababababpe","ababababpf","ababababpg","ababababph","ababababpi","ababababpj","ababababpk","ababababpl","ababababpm","ababababpn","ababababpo","ababababpp","ababababpq","ababababpr","ababababps","ababababpt","ababababpu","ababababpv","ababababpw","ababababpx","ababababpy","ababababpz","ababababqa","ababababqb","ababababqc","ababababqd","ababababqe","ababababqf","ababababqg","ababababqh","ababababqi","ababababqj","ababababqk","ababababql","ababababqm","ababababqn","ababababqo","ababababqp","ababababqq","ababababqr","ababababqs","ababababqt","ababababqu","ababababqv","ababababqw","ababababqx","ababababqy","ababababqz","ababababra","ababababrb","ababababrc","ababababrd","ababababre","ababababrf","ababababrg","ababababrh","ababababri","ababababrj","ababababrk","ababababrl","ababababrm","ababababrn","ababababro","ababababrp","ababababrq","ababababrr","ababababrs","ababababrt","ababababru","ababababrv","ababababrw","ababababrx","ababababry","ababababrz","ababababsa","ababababsb","ababababsc","ababababsd","ababababse","ababababsf","ababababsg","ababababsh","ababababsi","ababababsj","ababababsk","ababababsl","ababababsm","ababababsn","ababababso","ababababsp","ababababsq","ababababsr","ababababss","ababababst","ababababsu","ababababsv","ababababsw","ababababsx","ababababsy","ababababsz","ababababta","ababababtb","ababababtc","ababababtd","ababababte","ababababtf","ababababtg","ababababth","ababababti","ababababtj","ababababtk","ababababtl","ababababtm","ababababtn","ababababto","ababababtp","ababababtq","ababababtr","ababababts","ababababtt","ababababtu","ababababtv","ababababtw","ababababtx","ababababty","ababababtz","ababababua","ababababub","ababababuc","ababababud","ababababue","ababababuf","ababababug","ababababuh","ababababui","ababababuj","ababababuk","ababababul","ababababum","ababababun","ababababuo","ababababup","ababababuq","ababababur","ababababus","ababababut","ababababuu","ababababuv","ababababuw","ababababux","ababababuy","ababababuz","ababababva","ababababvb","ababababvc","ababababvd","ababababve","ababababvf","ababababvg","ababababvh","ababababvi","ababababvj","ababababvk","ababababvl","ababababvm","ababababvn","ababababvo","ababababvp","ababababvq","ababababvr","ababababvs","ababababvt","ababababvu","ababababvv","ababababvw","ababababvx","ababababvy","ababababvz","ababababwa","ababababwb","ababababwc","ababababwd","ababababwe","ababababwf","ababababwg","ababababwh","ababababwi","ababababwj","ababababwk","ababababwl","ababababwm","ababababwn","ababababwo","ababababwp","ababababwq","ababababwr","ababababws","ababababwt","ababababwu","ababababwv","ababababww","ababababwx","ababababwy","ababababwz","ababababxa","ababababxb","ababababxc","ababababxd","ababababxe","ababababxf","ababababxg","ababababxh","ababababxi","ababababxj","ababababxk","ababababxl","ababababxm","ababababxn","ababababxo","ababababxp","ababababxq","ababababxr","ababababxs","ababababxt","ababababxu","ababababxv","ababababxw","ababababxx","ababababxy","ababababxz","ababababya","ababababyb","ababababyc","ababababyd","ababababye","ababababyf","ababababyg","ababababyh","ababababyi","ababababyj","ababababyk","ababababyl","ababababym","ababababyn","ababababyo","ababababyp","ababababyq","ababababyr","ababababys","ababababyt","ababababyu","ababababyv","ababababyw","ababababyx","ababababyy","ababababyz","ababababza","ababababzb","ababababzc","ababababzd","ababababze","ababababzf","ababababzg","ababababzh","ababababzi","ababababzj","ababababzk","ababababzl","ababababzm","ababababzn","ababababzo","ababababzp","ababababzq","ababababzr","ababababzs","ababababzt","ababababzu","ababababzv","ababababzw","ababababzx","ababababzy","ababababzz"
};

cout << "Words: " << words2.size() << endl;
cout << "Board: " << board2.size() << " x " << board2[0].size() << endl;
  vector<string> out = obj->findWords(board2, words2);
  for (int i = 0; i < out.size(); ++i) {
    cout << out[i] << endl;
  }
  return 0;
}
