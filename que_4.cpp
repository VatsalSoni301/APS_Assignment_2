#include <bits/stdc++.h>
#define ll long long
#define x 31
#define size 100001
using namespace std;

template <class T, class U>
class Unordered_map
{
  public:
    struct node
    {
        T key;
        U value;
        struct node *next;
    };
    T key;
    U value;
    struct node *store[size];

    Unordered_map()
    {
        ll op;
        cout << "Press-1 to Insert" << endl;
        cout << "Press-2 to Search" << endl;
        cout << "Press-3 to Delete" << endl;
        cin >> op;
        if (op == 1)
        {
            cout << "Enter Key" << endl;
            cin >> key;
            cout << "Enter value" << endl;
            cin >> value;
            insert();
        }
        else if (op == 2)
        {
            cout << "Enter key" << endl;
            cin >> key;
            pair<U, bool> ans = search();
            if (ans.second)
                cout << ans.first << endl;
            else
                cout << "NOT FOUND" << endl;
        }
        else if (op == 3)
        {
            cout << "Enter key" << endl;
            cin >> key;
            pair<U, bool> ans = delete_mp();
            if (ans.second)
                cout << "Delete Successfully" << endl;
            else
                cout << "NOT FOUND" << endl;
        }
        else
        {
            cout << "Invalid Option" << endl;
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
    void insert()
    {
        ll index;
        ostringstream str1;
        str1 << key;
        string k = str1.str();
        index = hashing(k);
        struct node *new_node = new node;
        new_node->next = NULL;
        new_node->key = key;
        new_node->value = value;

        struct node *head = store[index];

        if (head == NULL)
        {
            head = new_node;
            store[index] = head;
        }
        else
        {
            ll flag = 0;
            while (head->next != NULL)
            {
                if (head->key == key)
                {
                    flag = 1;
                    break;
                }
                head = head->next;
            }
            if (flag == 0)
                head->next = new_node;
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
        struct node *head = store[index];
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
        struct node *head = store[index];
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
                p.second = true;
                return p;
            }
            else
            {
                struct node *prev = head;
                head = head->next;
                while (head != NULL)
                {
                    if (head->key == key)
                    {
                        prev->next = head->next;
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
    while (1)
    {
        Unordered_map<int, string> ump;
    }
}