#include <iostream>
#include "TimeMap.hpp" // Include the header file

int main() {
    
    TimeMap<string,string> T;
    T.set("foo","bar",1);
    cout << T.get("foo",1) << endl;
    T.set("foo","bar2",4);
    cout << T.get("foo",4) << endl;
    cout << T.get("foo",5) << endl;
}
