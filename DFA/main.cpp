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

        // mid to post
        vector<char> result;
        if (PrefixToPostfix::preToPost(input, result) == STATUS::ERROR) continue;
        
        // data convertion
        string postfix;
        postfix.assign(result.begin(), result.end());
        for (auto it = postfix.begin(); it != postfix.end(); it++) {
            if (*it == '.') {
                *it = '+';
            }
        }

        cell NFA_Cell, DFA_Cell;

        //表达式转NFA
        NFA_Cell = express_2_NFA(postfix);

        //显示
        // Display_NFA(NFA_Cell);
        NFA tempNFA = NFA(NFA_Cell);
        cout << "NFA: " << endl << tempNFA << endl;


        DFA_Cell = express_2_DFA(NFA_Cell);
        // Display_DFA(DFA_Cell);
        DFA tempDFA = DFA(DFA_Cell);
        cout << "DFA: " << endl << tempDFA << endl;
        

        tempDFA.DFAMinimise();
        cout << "min-DFA: " << endl << tempDFA << endl;
    }
    return 0;
}
