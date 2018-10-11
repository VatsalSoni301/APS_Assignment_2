#include <bits/stdc++.h>
#define ll long long
using namespace std;

pair<ll, pair<ll, ll>> *suffixarray;
ll inputlen;
string input;

ll comp(pair<ll, pair<ll, ll>> a, pair<ll, pair<ll, ll>> b)
{
    ll f = a.second.first;
    ll n = a.second.second;
    ll f1 = b.second.first;
    ll n1 = b.second.second;
    if (f < f1)
        return 1;
    else if (f > f1)
        return 0;
    else
    {
        if (n <= n1)
            return 1;
        else
            return 0;
    }
}

void suffixSort()
{
    ll i, j;
    for (i = 0; i < inputlen; i++)
    {
        suffixarray[i].first = i;
        suffixarray[i].second.first = input[i] - '0';
        if (i + 1 < inputlen)
        {
            suffixarray[i].second.second = input[i + 1] - '0';
        }
        else
            suffixarray[i].second.second = -1;
    }

    sort(suffixarray, suffixarray + inputlen, comp);
    ll index[inputlen];

    for (i = 2; i < inputlen; i = i * 2)
    {
        ll current = 0;
        ll previous = suffixarray[0].second.first;
        suffixarray[0].second.first = current;
        index[suffixarray[0].first] = 0;

        for (j = 1; j < inputlen; j++)
        {
            ll prevnext = suffixarray[j].second.second;
            ll prevprev = suffixarray[j - 1].second.second;
            ll prev = suffixarray[j].second.first;
            if (prevnext == prevprev && previous == prev)
            {
                previous = prev;
                suffixarray[j].second.first = current;
            }
            else
            {
                previous = prev;
                suffixarray[j].second.first = ++current;
            }
            index[suffixarray[j].first] = j;
        }

        for (j = 0; j < inputlen; j++)
        {
            ll child_1 = suffixarray[j].first + i;
            if (child_1 < inputlen)
            {
                ll in = index[child_1];
                suffixarray[j].second.second = suffixarray[in].second.first;
            }
            else
            {
                suffixarray[j].second.second = -1;
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
    suffixarray = new pair<ll, pair<ll, ll>>[inputlen];
    suffixSort();
    for (i = 0; i < inputlen; i++)
        cout << suffixarray[i].first << " ";
    return 0;
}