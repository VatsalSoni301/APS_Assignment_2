#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct suffixnode
{
    ll position;
    ll child[2];
};

struct suffixnode *suffixarray;
ll inputlen;
string input;

ll comp(struct suffixnode a, struct suffixnode b)
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

void suffixsort()
{
    ll i, j;
    for (i = 0; i < inputlen; i++)
    {
        suffixarray[i].position = i;
        suffixarray[i].child[0] = input[i] - '0';
        if (i + 1 < inputlen)
        {
            suffixarray[i].child[1] = input[i + 1] - '0';
        }
        else
            suffixarray[i].child[1] = -1;
    }

    sort(suffixarray, suffixarray + inputlen, comp);

    for (i = 2; i < inputlen; i = i * 2)
    {
        ll index[inputlen];
        ll current = 0;
        ll previous = suffixarray[0].child[0];
        suffixarray[0].child[0] = current;
        index[suffixarray[0].position] = 0;

        for (j = 1; j < inputlen; j++)
        {
            if (suffixarray[j].child[1] == suffixarray[j - 1].child[1] && previous == suffixarray[j].child[0])
            {
                previous = suffixarray[j].child[0];
                suffixarray[j].child[0] = current;
            }
            else
            {
                previous = suffixarray[j].child[0];
                suffixarray[j].child[0] = ++current;
            }
            index[suffixarray[j].position] = i;
        }

        for (j = 0; j < inputlen; j++)
        {
            ll child_1 = suffixarray[j].position + i;
            if (child_1 < inputlen)
            {
                suffixarray[j].child[1] = suffixarray[index[child_1]].child[0];
            }
            else
            {
                suffixarray[j].child[1] = -1;
            }
        }

        sort(suffixarray, suffixarray + inputlen, comp);
    }
}

int main()
{
    ll i;
    cin >> input;
    inputlen = input.size();
    suffixarray = new struct suffixnode[inputlen];
    suffixsort();
    for(i=0;i<inputlen;i++)
        cout<<suffixarray[i].position<<" ";
    return 0;
}