#include <vector>
#include <iostream>
#include <algorithm>

int main(){
    std::vector<int>v={1,2,3,5};
    std::vector<int>c={10,20,30,40};
    c.insert(c.begin(),v[2]);
    for(auto &x : c) std::cout << x << " ";
}
