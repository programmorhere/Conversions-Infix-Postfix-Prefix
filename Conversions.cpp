#include <iostream>
using namespace std;

//Node struct
struct Node
{
    string data;
    Node *next;
};

//Stack Class
class Stack
{
private:
    class List
    {
    public:
        Node *head;
        List()
        {
            head = nullptr;
        }
    };
    List list;

public:
    Stack()
    {
        list.head = NULL;
    }
    void Push(string data)
    {

        Node *newNode = new Node;
        newNode->next = list.head;
        newNode->data = data;
        list.head = newNode;
    }
    string Pop()
    {
        if (isEmpty())
        {
            return "maa chuda";
        }
        if (list.head->next == NULL)
        {
            string temp = list.head->data;
            delete list.head;
            list.head = NULL;
            return temp;
        }
        Node *temp = list.head->next;
        string temp2 = list.head->data;
        delete list.head;
        list.head = temp;
        return temp2;
    }
    bool isEmpty()
    {
        return (list.head == NULL);
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Nothing to Display\n";
        }
        Node *temp;
        temp = list.head;
        int i = 0;
        while (temp != NULL)
        {
            cout << temp->data << endl;
            temp = temp->next;
            i++;
        }
    }
};

///Function to check if ch is alphabet or not
bool checkAlpha(char ch)
{
    if (int(ch) >= 65 && int(ch) <= 90)
    {
        return true;
    }
    else if (int(ch) >= 97 && int(ch) <= 122)
    {
        return true;
    }
    return false;
}
//function to check precedence of operators
int checkPrec(string ch, Stack &stack, string stackop)
{
    pair<int, string> pair1[7];
    pair<int, string> userpair, stackpair;
    userpair.second = ch;
    //Lowest Precedence
    pair1[0].first = 1;
    pair1[0].second = "+";
    pair1[1].first = 1;
    pair1[1].second = "-";

    //Medium Precedence
    pair1[2].first = 2;
    pair1[2].second = "*";
    pair1[3].first = 2;
    pair1[3].second = "*";
    pair1[4].first = 2;
    pair1[4].second = "/";

    //Highest Precendence
    pair1[5].first = 3;
    pair1[5].second = "!";

    //Most highest precedence
    pair1[6].first = 3;
    pair1[6].second = "^";

    //Creating Pair of Expression operator
    for (int i = 0; i < 7; i++)
    {
        if (userpair.second == pair1[i].second)
        {
            userpair.first = pair1[i].first;
            break;
        }
    }
    //Creating Pair of Stack Operator
    stackpair.second = stackop;
    for (int i = 0; i < 7; i++)
    {
        if (stackpair.second == pair1[i].second)
        {
            stackpair.first = pair1[i].first;
            break;
        }
    }
    if (userpair.first == stackpair.first)
    {
        return 1;
    }
    else if (stackpair.first > userpair.first)
    {
        return 2;
    }
    return 3;
}
//Function to convert Infix to Postfix
string InfixtoPostfix(string str, Stack &stack)
{
    string result = "";
    int bracket = -1;
    for (int i = 0; i < str.length(); i++)
    {
        string temp(1, str[i]);
        if (checkAlpha(str[i]))
        {
            result = result + temp;
        }
        else
        {
            if (temp == "(")
            {
                bracket++;
                cout << "pushing: " << temp << endl;
                stack.Push(temp);
            }
            else
            {
                if (stack.isEmpty())
                {
                    cout << "pushing: " << temp << endl;
                    stack.Push(temp);
                }
                else
                {
                    if (temp != ")")
                    {
                        string stackop = stack.Pop();
                        cout << "popped element: " << stackop << endl;
                        if (stackop == "(")
                        {

                            stack.Push(stackop);
                            stack.Push(temp);
                            cout << "pushing" << stackop << endl;
                            cout << "pushing" << temp << endl;
                        }
                        else if (checkPrec(temp, stack, stackop) == 1)
                        {
                            result = result + stackop;
                            stack.Push(temp);
                            cout << "pushing: " << temp << endl;
                        }
                        else if (checkPrec(temp, stack, stackop) == 2)
                        {
                            do
                            {
                                result = result + stackop;
                                stackop = stack.Pop();
                                if (stackop == "(")
                                    break;
                                cout << "poping: " << stackop << endl;
                            } while (stack.isEmpty() == false);
                            if (stackop != "(")
                                result = result + stackop;
                            else
                                stack.Push(stackop);
                            stack.Push(temp);
                            cout << "pushing: " << temp << endl;
                        }
                        else if (checkPrec(temp, stack, stackop) == 3)
                        {
                            cout << "pushing: " << temp << endl;
                            stack.Push(stackop);
                            cout << "pushing: " << temp << endl;
                            stack.Push(temp);
                        }
                    }
                    else if (temp == ")")
                    {
                        string stackop;
                        if (bracket > -1)
                        {
                            do
                            {
                                stackop = stack.Pop();
                                if (stackop != "(")
                                    result = result + stackop;
                            } while (stackop != "(");

                            bracket--;
                        }
                        else
                        {
                            cout << "wrong Input\n";
                            exit(0);
                        }
                    }
                    cout << "Display\n";
                    stack.display();
                    cout << "result = " << result << endl;
                }
            }
        }
    }
    string stackop;
    while (stack.isEmpty() == false)
    {
        stackop = stack.Pop();
        result = result + stackop;
    }
    return result;
}
//Function to convert Postfix to Infix
Stack PostFixtoInfix(string str, Stack &stack)
{

    for (int i = 0; i < str.length(); i++)
    {
        if (checkAlpha(str[i]))
        {
            string temp(1, str[i]);
            stack.Push(temp);
        }
        else
        {
            string temp2 = stack.Pop();
            string temp1 = stack.Pop();

            string result = "(" + temp1 + str[i] + temp2 + ")";
            stack.Push(result);
        }
    }
    return stack;
}
//Main Function
int main()
{
    Stack stack;
    int ch;
    string str;
    while (true)
    {
        //Menu
        cout << "1.) Infix to Postfix\n2.) Postfix to infix\n3.) Quit\n\nEnter : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter infix Expression\n";
            cin >> str;
            cout << InfixtoPostfix(str, stack);
            break;
        case 2:
            cout << "Enter PostFix Expression\n";
            stack = PostFixtoInfix(str, stack);
            stack.display();
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid Input\n";
            break;
        }
    }
}