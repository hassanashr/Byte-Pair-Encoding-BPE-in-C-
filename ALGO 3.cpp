#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
using namespace std;
void AddSymbolPair(priority_queue<tuple<int, pair<int, string>, pair<int, string>>> &symbolpairs, 
                        map<string, int> &merges, 
                        string &s1, 
                        string &s2,
                        int pos1,
                        int pos2) {
    string combined = s1 + " " + s2;
    int score = merges.count(combined) ? merges[combined] : -1;
    symbolpairs.push({score, {pos1, s1} , {pos2, s2} });
    return;
}
pair<int, string> MergeBestPair(multiset<pair<int,string>> & symbols, pair<pair<int, string>, pair<int, string>>& BestPair){
    pair<int, string> left = BestPair.first;
    pair<int, string> right = BestPair.second;
    int pos1 = left.first, pos2 = right.first;
    string combined = left.second + right.second;
    auto it_left = symbols.find(left);
    auto it_right = symbols.find(right);

    symbols.erase(it_left);
    symbols.erase(it_right);
    symbols.insert({min(pos1, pos2), combined});

    return {min(pos1, pos2), combined};
}
multiset<pair<int,string>> Tokenize(string &text, map<string,int> & merges){
    multiset<pair<int,string>> symbols; //{position, string}
    priority_queue<tuple<int, pair<int, string>, pair<int, string>>> symbolpairs; //{score, left, right}

    for(int i = 0 ; i < text.size(); i++){
        string s = static_cast<string>(string(1,text[i]));
        symbols.insert({i, s});
    }
    for(int i = 0; i < text.size() - 1; i++){
        string s1 = static_cast<string>(string(1,text[i]));
        string s2 = static_cast<string>(string(1,text[i + 1]));
        AddSymbolPair(symbolpairs, merges, s1, s2, i, i + 1);
    }

    while(1){
        auto [cost, left, right] = symbolpairs.top();
        symbolpairs.pop();
        if(cost == - 1 || symbolpairs.empty()) break;
        pair<pair<int, string>, pair<int, string>> Bestpair = {left, right};
        pair<int, string> new_symbol = MergeBestPair(symbols, Bestpair);
        auto left_it = symbols.find(new_symbol);
        auto right_it = left_it;

        left_it = (left_it == symbols.begin()) ? symbols.end() : prev(left_it);
        right_it = (next(right_it) == symbols.end()) ? symbols.end() : next(right_it);
      
        if (left_it != symbols.end()) {
            string prev_symbol = left_it->second;
            AddSymbolPair(symbolpairs, merges, prev_symbol, new_symbol.second, left_it->first, left.first);
        }
        if (right_it != symbols.end()) {
            string next_symbol = right_it->second;
            AddSymbolPair(symbolpairs, merges, new_symbol.second, next_symbol, right.first, right_it->first);
        }
    }
    return symbols;
}
int main(){
    
};
