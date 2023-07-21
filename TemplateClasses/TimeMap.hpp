#ifndef TIMEhpp
#define TIMEhpp

#include<bits/stdc++.h>
using namespace std;

template<typename T,typename U> class TimeMap {
public:
    TimeMap() {
    }
    
    void set(T key, U value, int timestamp) {
        store[key].push_back({value,timestamp});
    }
    
    U get(T key, int timestamp) {
        for (int i = store[key].size()-1; i >= 0; i--) {
            if (store[key][i].second <= timestamp)
                return store[key][i].first;  
        }
        return 0;
    }

private:
    map<T, vector<pair<U, int>>> store;
};

#endif // TIMEhpp