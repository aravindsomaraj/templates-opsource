#include<bits/stdc++.h>
#include "AVL Tree/LRUcache.hpp"
int main()
{
    LRUCache<int,char> L(3);
    L.put(1,'a');
    L.put(2,'b');
    L.put(3,'c');
    cout << L.get(2);
    L.put(4,'d');
    cout << L.get(1);
}