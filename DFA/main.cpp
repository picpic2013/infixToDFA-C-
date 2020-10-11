#include <iostream>
#include <vector>
#include <string>
#include "PrefixToPostfix.h"
#include "PostfixToNFA.h"
#include "NFA.h"
#include "DFA.h"

#include "Thompson.h"

using namespace std;

int main() {
    while (true) {
        string input = "(ab|c)*dde";
        cin >> input;
        vector<char> result;
        if (PrefixToPostfix::preToPost(input, result) == STATUS::ERROR) continue;
        
        /*NFA res = PostfixToNFA::postfix2NFA(result);
        cout << res << endl;*/

        // data convertion
        string postfix;
        postfix.assign(result.begin(), result.end());
        for (auto it = postfix.begin(); it != postfix.end(); it++) {
            if (*it == '.') {
                *it = '+';
            }
        }

        // cout << postfix << endl;

        cell NFA_Cell, DFA_Cell;

        //表达式转NFA
        NFA_Cell = express_2_NFA(postfix);

        //显示
        Display_NFA(NFA_Cell);
        NFA tempNFA = NFA(NFA_Cell);
        cout << tempNFA << endl;


        DFA_Cell = express_2_DFA(NFA_Cell);
        Display_DFA(DFA_Cell);
        DFA tempDFA = DFA(DFA_Cell);
        cout << tempDFA << endl;
        

        tempDFA.DFAMinimise();
        cout << tempDFA << endl;
    }
    return 0;
}
