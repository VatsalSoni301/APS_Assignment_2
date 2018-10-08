#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll comparator(struct suffixNode a, struct suffixNode b);
void suffixSort();

struct suffixNode
{
    ll index;
    ll child[2];
};

struct suffixNode *suffixarray;
string input;

ll comparator(struct suffixNode a, struct suffixNode b)
{
    if (a.child[0] < b.child[0])
        return 1;
    else if (a.child[0] > b.child[0])
        return 0;
    else
    {
        if (a.child[1] <= b.child[1])
            return 1;
        else
            return 0;
    }
}

void suffixSort()
{
    ll i, size, j, k;
    size = input.length();
    ll index[size];
    for (i = 0; i < size; i++)
    {
        suffixarray[i].index = i;
        suffixarray[i].child[0] = input[i] - '0';
        if (i + 1 < size)
        {
            suffixarray[i].child[1] = input[i + 1] - '0';
        }
        else
        {
            suffixarray[i].child[1] = -1;
        }
    }
    sort(suffixarray, suffixarray + size, comparator);
    for (j = 4; j < 2 * size; j = j * 2)
    {
        index[suffixarray[0].index] = 0;
        ll before = suffixarray[0].child[0];
        ll current = 0;
        suffixarray[0].child[0] = current;
        for (k = 1; k < size; k++)
        {
            if (suffixarray[k].child[0] == before && suffixarray[k].child[1] == suffixarray[k - 1].child[1])
            {
                before = suffixarray[k].child[0];
                suffixarray[k].child[0] = current;
            }
            else
            {
                before = suffixarray[k].child[0];
                suffixarray[k].child[0] = current + 1;
                current++;
            }

            index[suffixarray[k].index] = k;
        }

        for (k = 0; k < size; k++)
        {
            ll child_1 = suffixarray[k].child[0] + (j / 2);
            if (child_1 < size)
            {
                ll in = index[child_1];
                suffixarray[k].child[1] = suffixarray[in].child[0];
            }
            else
            {
                suffixarray[k].child[1] = -1;
            }
        }
        sort(suffixarray, suffixarray + size, comparator);
    }

    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    ll i;
    cin >> input;
    suffixarray = new struct suffixNode[input.size()];
    suffixSort();

    for (i = 0; i < input.length(); i++)
    {
        cout << suffixarray[i].index << " ";
    }
    cout << endl;
    for (i = suffixarray[0].index; i < input.size(); i++)
    {
        cout << input[i];
    }
    for (i = 0; i < suffixarray[0].index; i++)
    {
        cout << input[i];
    }
    cout << endl;
    return 0;
}