#ifndef LRUhpp
#define LRUhpp

#include<bits/stdc++.h>
using namespace std;

template <typename T,typename U> class LRUCache {
public:
    list<pair<T,U>> l;
    unordered_map<T,typename list<pair<T,U>>::iterator> mp;
    int size;
    LRUCache(int capacity) {
        size = capacity;
    }
    
    U get(T key) {
        if(mp.find(key)==mp.end())
        {
            cout << "\nKey not Found\n";
            return 0;
        }
        l.splice(l.begin(),l,mp[key]);
        return mp[key]->second;
    }
    
    void put(T key, U value) {
        if(mp.find(key)!=mp.end())
        {
            mp[key]->second = value;
            l.splice(l.begin(),l,mp[key]);
            return;
        }
        if(l.size()==size)
        {
            int deletekey = l.back().first;
            l.pop_back();
            mp.erase(deletekey);
        }
        l.push_front({key,value});
        mp[key] = l.begin();
    }
};

#endif // LRUhpp