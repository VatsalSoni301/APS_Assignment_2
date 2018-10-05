#include <bits/stdc++.h>
#define ll long long
#define x 31
#define size 3
using namespace std;

template <class T, class U>
class Unordered_map
{
  public:
    class node
    {
      public:
        T key;
        U value;
        class node *next;
    };
    T key;
    U value;
    class node *store[size];

    Unordered_map()
    {
        for (ll i = 0; i < size; i++)
            store[i] = NULL;
        string op;
        while (1)
        {
            cout << "Press-1 to Insert" << endl;
            cout << "Press-2 to Search" << endl;
            cout << "Press-3 to Delete" << endl;
            cin >> op;
            if (op == "1")
            {
                cout << "Enter Key" << endl;
                cin >> key;
                cout << "Enter value" << endl;
                cin >> value;
                pair<U, bool> ans = insert();
                if (ans.second)
                    cout << "Insert Successfully" << endl;
                else
                    cout << "Already Exist" << endl;
            }
            else if (op == "2")
            {
                cout << "Enter key" << endl;
                cin >> key;
                pair<U, bool> ans = search();
                if (ans.second)
                    cout << "Value=" << ans.first << endl;
                else
                    cout << "NOT FOUND" << endl;
            }
            else if (op == "3")
            {
                cout << "Enter key" << endl;
                cin >> key;
                pair<U, bool> ans = delete_mp();
                if (ans.second)
                    cout << "Delete Successfully" << endl;
                else
                    cout << "NOT FOUND" << endl;
            }
            else if (op == "q")
            {
                break;
            }
            else
            {
                cout << "Invalid Option" << endl;
            }
            cout << "Start" << endl;
            for (ll i = 0; i < size; i++)
            {
                class node *head = store[i];
                while (head != NULL)
                {
                    cout << "i=" << i << " " << head->key << " " << head->value << "  ";
                    head = head->next;
                }
            }
            cout << endl;
            cout << "Finish" << endl;
        }
    }

    ll hashing(string k)
    {
        ll i, mul = 1, index = 0;
        for (i = 0; i < k.length(); i++)
        {
            if (i == 0)
                index = index + (mul * k[i]);
            else
            {
                mul = (mul * x) % size;
                index = index + (mul * k[i]);
            }
        }
        index = index % size;
        return index;
    }
    pair<U, bool> insert()
    {
        pair<U, bool> res;
        ll index;
        ostringstream str1;
        str1 << key;
        string k = str1.str();
        index = hashing(k);
        class node *new_node = new node;
        new_node->next = NULL;
        new_node->key = key;
        new_node->value = value;

        class node *head = store[index];

        if (head == NULL)
        {
            head = new_node;
            store[index] = head;
            res.second = true;
            return res;
        }
        else
        {
            ll flag = 0;
            while (head->next != NULL)
            {
                if (head->key == key)
                {
                    flag = 1;
                    res.second = false;
                    return res;
                }
                head = head->next;
            }
            if (flag == 0)
            {
                if (head->key != key)
                    head->next = new_node;
                else
                {
                    res.second = false;
                    return res;
                }
            }

            res.second = true;
            return res;
        }
    }
    pair<U, bool> search()
    {
        pair<U, bool> res;
        ll index;
        ostringstream str1;
        str1 << key;
        string k = str1.str();
        index = hashing(k);
        class node *head = store[index];
        //cout<<index;
        if (head == NULL)
        {
            res.second = false;
            return res;
        }
        else
        {
            while (head->next != NULL)
            {
                if (head->key == key)
                {
                    res.first = head->value;
                    res.second = true;
                    return res;
                }
                head = head->next;
            }
            if (head->key == key)
            {
                res.first = head->value;
                res.second = true;
                return res;
            }
            else
            {
                res.second = false;
                return res;
            }
        }
    }
    pair<U, bool> delete_mp()
    {

        pair<U, bool> p;
        ll index;
        ostringstream str1;
        str1 << key;
        string k = str1.str();
        index = hashing(k);
        class node *head = store[index];
        if (head == NULL)
        {
            p.second = false;
            return p;
        }
        else
        {
            if (head->next == NULL)
            {
                if (head->key == key)
                {
                    store[index] = NULL;
                    p.second = true;
                    return p;
                }
                else
                {
                    p.second = false;
                    return p;
                }
            }
            else if (head->key == key)
            {
                head = head->next;
                store[index] = head;
                //free(head);
                p.second = true;
                return p;
            }
            else
            {
                class node *prev = head;
                head = head->next;
                while (head != NULL)
                {
                    if (head->key == key)
                    {
                        prev->next = head->next;
                        //free(head);
                        p.second = true;
                        return p;
                    }
                    prev = head;
                    head = head->next;
                }
                p.second = false;
                return p;
            }
        }
    }
};

int main()
{
    Unordered_map<string, string> ump;
    cout << "Thank You!!!" << endl;
}