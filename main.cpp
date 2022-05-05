#include <iostream>
#include <stack>
using namespace std;

//recursive function
int F(int n)
{
    if(n<=1) return 1;
    int a=n+F(n-1);
    int b=n*F(n/2);
    int c=n-2-(a+b)%2;
    int d=F(c);
    return a+b+d;
}
//enum to store the name of different callers
enum Caller{CALLER_A, CALLER_B, CALLER_D, CALLER_MAIN};

//struct for a function that will be later stored in the stack
struct FCall
{
    //constructor that takes the integer n of the current call and the parent type calling it
    //The first caller is by default the CALLER_MAIN
    //initialize its local variables to 0 that will be calculated later
    FCall(int& n, Caller callerName = CALLER_MAIN)
    {
        this->n = n;
        this->callerName = callerName;
        a = b = c = d = returnVar = 0;
    }
    //struct local variables
    int a, b, c, d;
    int n;
    int returnVar;
    Caller callerName;
};

int FIterative(int n)
{
    //stack of type struct FCall
    stack<FCall> s;
    //initiating the first call by the first n and caller type by default is Caller-Main
    FCall call(n);
    //push the first call in the stack
    s.push(call);
    //loop on the stack until its empty then break
    while (!s.empty())
    {
        //get the last call on the top of the stack
        FCall& currentCall = s.top();
        //the n of current call is less than 0 and the returnVar is equal 0 (base case)
        if (currentCall.n<= 1 && !currentCall.returnVar)
        {
            //assign the returnVar of the currentCall to 1 according to the base case
            currentCall.returnVar = 1;
        }
        //the currentCall has return value greater than 0 and it is not the last object in the stack
        if (currentCall.returnVar && s.size() >= 2)
        {
            //remove the currentCall from the stack
            s.pop();
            //Now we have three cases for the parent caller to be called from variable a or b or d
            //First it is called from a
            if (currentCall.callerName == CALLER_A)
            {
                FCall& c2 = s.top();
                s.pop();
                FCall& c3 = s.top();
                c3.a = c3.n + currentCall.returnVar;
                s.push(c2);
            }
            //Second it is called from b
            if (currentCall.callerName == CALLER_B)
            {
                FCall& c2 = s.top();
                c2.b = c2.n * currentCall.returnVar;
                c2.c = c2.n - 2 - (c2.a + c2.b) % 2;
                FCall call3(c2.c, CALLER_D);
                s.push(call3);

            }
            //Third it is called from d
            if (currentCall.callerName == CALLER_D)
            {
                FCall& c1 = s.top();
                c1.d = currentCall.returnVar;
                c1.returnVar = c1.a + c1.b + c1.d;

            }
            continue;
        }
        //the currentCall has return value greater than 0 and it is not the last object in the stack
        else if(currentCall.returnVar && s.size() == 1)
        {
            //return the last call return value which is the final result
            return s.top().returnVar;
        }
        //calculate the new n needed by a
        int call1_N = currentCall.n-1;
        //calculate the new n needed by b
        int call2_N = currentCall.n/2;
        //get two objects from FCall struct one call for a and other for b with their new n values
        FCall call1(call1_N, CALLER_A);
        FCall call2(call2_N, CALLER_B);
        //push the two new calls in reversed order to keep a on the top of the stack and be calculated first
        s.push(call2);
        s.push(call1);
    }
}

int main()
{
    // 20 test cases to show the matching between recursive and iterative function from 1 to 20
    for (int i = 1; i <= 20; ++i)
    {
        cout << "Recursive F("<<i<<"): "<< F(i)<<endl;
        cout << "Non-recursive F("<<i<<"): "<< FIterative(i)<<endl;
    }
    return 0;
}