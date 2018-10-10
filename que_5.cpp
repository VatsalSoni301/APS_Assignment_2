#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct node
{
    const char *str;
    ll size;
    struct node *next;
};

class StringBuilder
{
  public:
    struct node *head;
    ll size;
    StringBuilder()
    {
        head = new struct node;
        head->next = NULL;
        size = 0;
    }
    StringBuilder(const char *s)
    {
        head = new struct node;
        head->next = NULL;
        head->str = s;
        size = strlen(s);
    }
};

StringBuilder stringAppend(StringBuilder s1, StringBuilder s2)
{
    StringBuilder newstr;
    newstr.size = s1.size + s2.size;
    cout << "size=" << newstr.size << endl;
    if (s1.size != 0 && s2.size != 0)
    {
        memcpy(newstr.head, s1.head, sizeof(struct node));
        struct node *temp = s1.head;
        struct node *newtemp = newstr.head;
        temp = temp->next;
        while (temp != NULL)
        {
            struct node *newAppendnode = new struct node;
            memcpy(newAppendnode, temp, sizeof(struct node));
            newtemp->next = newAppendnode;
            newtemp = newtemp->next;
            temp = temp->next;
        }
        temp = s2.head;
        while (temp != NULL)
        {
            struct node *newAppendnode = new struct node;
            memcpy(newAppendnode, temp, sizeof(struct node));
            newtemp->next = newAppendnode;
            newtemp = newtemp->next;
            temp = temp->next;
        }
    }
    else if (s2.size != 0)
    {
        struct node *temp = s2.head;
        memcpy(newstr.head, temp, sizeof(struct node));
        struct node *newtemp = newstr.head;
        temp = temp->next;
        while (temp != NULL)
        {
            struct node *newAppendnode = new struct node;
            memcpy(newAppendnode, temp, sizeof(struct node));
            newtemp->next = newAppendnode;
            newtemp = newtemp->next;
            temp = temp->next;
        }
    }
    else if (s1.size != 0)
    {
        struct node *temp = s1.head;
        memcpy(newstr.head, temp, sizeof(struct node));
        struct node *newtemp = newstr.head;
        temp = temp->next;
        while (temp != NULL)
        {
            struct node *newAppendnode = new struct node;
            memcpy(newAppendnode, temp, sizeof(struct node));
            newtemp->next = newAppendnode;
            newtemp = newtemp->next;
            temp = temp->next;
        }
    }
    else
    {
        cout << "NULL" << endl;
    }
    return newstr;
}

StringBuilder stringInitialize(const char *str)
{
    StringBuilder s1(str);
    //cout << str << endl;
    return s1;
}

StringBuilder traverse(StringBuilder s)
{
    if (s.size != 0)
    {
        ll f = 0;
        char *merge;
        merge = new char[s.size];
        struct node *prev;
        struct node *temp = s.head;
        while (temp != NULL)
        {
            //cout << "f=" << f << endl;
            cout << temp->str;
            strcat(merge, temp->str);
            prev = temp;
            temp = temp->next;
            if (f != 0)
                free(prev);
            f++;
        }
        cout << endl;
        //cout << "M=" << merge << endl;
        s.head->str = merge;
        s.head->next = NULL;
    }
    return s;
}

ll kmp(const char *org, const char *sub)
{
    ll sublen = strlen(sub);
    ll orglen = strlen(org);
    ll arr[sublen];
    ll i = 0;
    ll j = 0;
    arr[0] = 0;
    ll f = 0;
    i = 1;
    while (i < sublen)
    {
        if (sub[i] == sub[f])
        {
            f++;
            arr[i] = f;
            i++;
        }
        else
        {
            if (f != 0)
            {
                f = arr[f - 1];
            }
            else
            {
                arr[i] = 0;
                i++;
            }
        }
    }
    i = 0;

    //for (ll k = 0; k < sublen; k++)
    //cout << arr[k] << " ";

    while (i < orglen)
    {
        if (org[i] == sub[j])
        {
            if (j == sublen - 1)
                return i - j;
            else
            {
                i += 1;
                j += 1;
            }
        }
        else
        {
            if (j <= 0)
                i += 1;
            else
                j = arr[j - 1];
        }
    }

    return -1;
}

ll findSubstring(StringBuilder s, const char *a)
{
    s = traverse(s);
    const char *finalstring = s.head->str;
    ll index = kmp(finalstring, a);
    return index;
}

int main()
{
    ios_base::sync_with_stdio(false);
    StringBuilder s1 = stringInitialize("Hello");
    StringBuilder s2 = stringInitialize("World");
    StringBuilder s3 = stringAppend(s1, s2);
    cout << "----s3----" << endl;
    s3 = traverse(s3);
    s1 = stringAppend(s1, s2);
    cout << "----s1----" << endl;
    s1 = traverse(s1);
    cout << "----s3----" << endl;
    s3 = traverse(s3);
    StringBuilder s4 = StringBuilder("ABCD");
    s4 = stringAppend(s4, s2);
    cout << "----s4----" << endl;
    s4 = traverse(s4);
    s3 = stringAppend(s4, s3);
    cout << "----s3----" << endl;
    s3 = traverse(s3);
    StringBuilder rj;
    StringBuilder vs;
    StringBuilder x = stringAppend(rj, vs);
    cout << "----x----" << endl;
    x = traverse(x);
    x = stringAppend(x, s1);
    cout << "----x----" << endl;
    x = traverse(x);
    StringBuilder w;
    StringBuilder y = stringAppend(s1, w);
    cout << "----y----" << endl;
    y = traverse(y);
    y = stringAppend(y, s4);
    cout << "----y----" << endl;
    y = traverse(y);
    x = stringAppend(x, y);
    cout << "----x----" << endl;
    x = traverse(x);

    ll index = findSubstring(s3, "abcabcdab");
    if (index == -1)
        cout << "Not found" << endl;
    else
        cout << "index=" << index << endl;

    index = findSubstring(s3, "Wor");
    if (index == -1)
        cout << "Not found" << endl;
    else
        cout << "index=" << index << endl;
    return 0;
}