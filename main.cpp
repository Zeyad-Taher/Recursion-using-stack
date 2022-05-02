#include <iostream>
#include <stack>
using namespace std;

int F(int n)
{
    if(n<=1) return 1;
    int a=n+F(n-1);
    int b=n*F(n/2);
    int c=n-2-(a+b)%2;
    int d=F(c);
    return a+b+d;
}

enum FReturnAddress{CALLER_A, CALLER_B, CALLER_D, CALLER_MAIN};

struct FCall {
    FCall(int& n, FReturnAddress returnAddress = CALLER_MAIN) {
        this->n = n;
        this->returnAddress = returnAddress;
        a = b = c = d = returnVar = 0;
    }
    int a, b, c, d;
    int n;
    int returnVar;
    FReturnAddress returnAddress;
};

int FIterative(int n) {
    stack<FCall> s;
    FCall call(n);
    s.push(call);
//    int retVal;
    while (!s.empty()) {
        FCall& currentCall = s.top();
        if (currentCall.n<= 1 && !currentCall.returnVar) {currentCall.returnVar = 1;}
        if (currentCall.returnVar && s.size() >= 2) {
            s.pop();
//            FCall currentCall2 = s.top();
            if (currentCall.returnAddress == CALLER_A) {
//                s.pop();
//                FCall& c1 = s.top(); s.pop();
                FCall& c2 = s.top(); s.pop();
                FCall& c3 = s.top();
//                currentCall2.a = currentCall2.n * currentCall.returnVar;
                c3.a = c3.n + currentCall.returnVar;
                s.push(c2);
//                s.push(c1);
//                s.push(currentCall);
            }
            if (currentCall.returnAddress == CALLER_B) {
//                currentCall2.b = currentCall2.n * currentCall.returnVar;
//                currentCall2.c = currentCall2.n - 2 - (currentCall2.a + currentCall2.b) % 2;
//                FCall call3(currentCall2.c, CALLER_D);
//                s.push(call3);
//                s.pop();
//                FCall& c1 = s.top(); s.pop();
                FCall& c2 = s.top();
                c2.b = c2.n * currentCall.returnVar;
                c2.c = c2.n - 2 - (c2.a + c2.b) % 2;
                FCall call3(c2.c, CALLER_D);
                s.push(call3);
//                s.push(currentCall);

            }
            if (currentCall.returnAddress == CALLER_D) {
//                currentCall2.d = currentCall.returnVar;
//                currentCall.returnVar = currentCall.a + currentCall.b + currentCall.d;
                FCall& c1 = s.top();
                c1.d = currentCall.returnVar;
                c1.returnVar = c1.a + c1.b + c1.d;

            }
            continue;
        }else if(currentCall.returnVar && s.size() == 1) {
            return s.top().returnVar;
        }
        int call1N = currentCall.n-1;
        int call2N = currentCall.n/2;
        FCall call1(call1N, CALLER_A);
        FCall call2(call2N, CALLER_B);
//        FCall call3(currentCall.c, CALLER_D);

//        s.push(call3);
        s.push(call2);
        s.push(call1);

//        FCall call3()
    }

}

int main() {
    for (int i = 1; i <= 20; ++i) {
        cout << "Recursive F("<<i<<"): "<< F(i)<<endl;
        cout << "Non-recursive F("<<i<<"): "<< FIterative(i)<<endl;
    }
    return 0;
}
