#include<iostream>
#include<vector>
#include<list>
#include<string>

#define ll long long
#define endl '\n'

using namespace std;

struct dict{
    string key;
    string value;
    dict():key(""),value(""){};
    dict(string Key, string Value):key(Key),value(Value){};
};

class HashChain_std{
private:
    int size;
    int count;
    vector<list<dict> >table;

    int PreHashing(string key_str);
    int HashFunction(string key_str);
public: 
    HashChain_std(){};
    HashChain_std(int m):size(m),count(0){
        table.resize(size);
    }
    void Insert(dict data);
    void Delete(string key);
    string Search(string key);
    void DisplayTable();
};

void HashChain_std::Insert(dict data){
    int index = HashFunction(data.key);
    table[index].push_front(data);
}

string HashChain_std::Search(string key_str){
    int index = HashFunction(key_str);
    for(list<dict>::iterator itr = table[index].begin();
    itr != table[index].end(); itr++){
        if(itr->key == key_str){
            return itr->value;
        }
    }
    return "...\nno such data";
}

void HashChain_std::Delete(string key_str){
    int index = HashFunction(key_str);
    for(list<dict>::iterator itr = table[index].begin();
    itr != table[index].end(); itr++){
        if(itr->key == key_str){
            table[index].erase(itr);
        }
    }
}

int HashChain_std::PreHashing(string key_str){
    int exp = 9;
    int key_int = 0;
    int p = 1;

    for(int i = (int)key_str.size() - 1; i >= 0; i--){
        key_int += key_str[i]*p;
        p *= exp;
    }
    return key_int;
}

int HashChain_std::HashFunction (string key_str){
    return (PreHashing(key_str) % this->size);
}

void HashChain_std::DisplayTable(){
    for (int i = 0; i < table.size(); i++) {
        cout << "slot#" << i << ": ";
        for (list<dict>::iterator itr = table[i].begin(); itr != table[i].end(); itr++) {
            cout << "(" << (*itr).key << "," << (*itr).value << ") ";
        }
        cout << endl;
    }
    cout << endl;
}


int main(){
    HashChain_std hash(5);
    hash.Insert(dict("T-Mac","Magic"));
    hash.Insert(dict("Bryant","Lakers"));
    hash.Insert(dict("Webber","Kings"));
    hash.Insert(dict("Arenas", "Wizards"));
    hash.Insert(dict("Davis","Clippers"));
    hash.Insert(dict("Kidd","Nets"));
    hash.DisplayTable();

    cout << "T-Mac is in " << hash.Search("T-Mac") << ". " << endl;
    cout << "Arenas is in " << hash.Search("Arenas") << ". " << endl;

    hash.Delete("Kidd");
    hash.Delete("T-Mac");
    cout << "\nAfter deleting Kidd and T-Mac:\n";
    hash.DisplayTable();
    return 0;
}