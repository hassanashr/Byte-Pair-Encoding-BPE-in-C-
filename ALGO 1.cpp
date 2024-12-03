#include <iostream>
#include <utility>
#include <vector>
#include <map>
using namespace std;
pair<string,int> FindBestPair(vector<string> & symbols, map<string,int> & merges){
    pair<string, int> BestPair = {"", 0};
    for(int i = 0; i < symbols.size() - 1; i++){
        int score = merges[ symbols[i] + " " + symbols[i + 1] ];
        if(score > BestPair.second){
            BestPair = {symbols[i] + " " + symbols[i + 1], score};
        }
    }
    return BestPair;
}
void MergeBestPair(vector<string> & symbols, pair<string, int> BestPair){
    for(int i = 0; i < symbols.size() - 1; i++){
        if(symbols[i] + " " + symbols[i + 1] == BestPair.first){
            string new_symbol = symbols[i] + symbols[i + 1];
            symbols.erase(symbols.begin() + i);
            symbols.erase(symbols.begin() + i);
            symbols.insert(symbols.begin() + i, new_symbol);
            break;
        }
    }
}
vector<string> Tokenize(string &text, map<string,int> & merges){
    vector<string> symbols(text.size());
    for(int i = 0 ; i < text.size(); i++){
        symbols[i] = text[i];
    }
    while(1){
        pair<string, int> BestPair = FindBestPair(symbols, merges);
        if(BestPair.first == "") break;
        MergeBestPair(symbols, BestPair);
    }
    return symbols;
}
int main(){

};