#include <iostream>
#include <vector>
#include <string>
#include "PrefixToPostfix.h"
#include "PostfixToNFA.h"
#include "MyGraphWithStartEnd.h"
using namespace std;

int main() {
    while (true) {
        string input = "(ab|c)*dde";
        cin >> input;
        vector<char> result;
        if (PrefixToPostfix::preToPost(input, result) == STATUS::ERROR) continue;
        
        for (vector<char>::iterator it = result.begin(); it != result.end(); it++) cout << *it;
        cout << endl;
        
        NFA res = PostfixToNFA::postfix2NFA(result);
        cout << res;
    }
    return 0;
}
