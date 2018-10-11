#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll comparator(pair<ll, pair<ll, ll>> a, pair<ll, pair<ll, ll>> b);
void suffixSort();

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
    ios_base::sync_with_stdio(false);
    ll i, f = 0, pos, n, k, j, count = 0, max = -9999;
    cin >> input;
    cin >> k;
    n = input.size();
    inputlen = n;
    suffixarray = new pair<ll, pair<ll, ll>>[n];
    suffixSort();

    // get longest common prefix which is longest substring.
    for (i = 0; i < n - k + 1; i++)
    {
        count = 0;
        string s = input.substr(suffixarray[i].first);
        string s1 = input.substr(suffixarray[i + k - 1].first);
        if (s.length() < s1.length())
        {
            for (j = 0; j < s.length(); j++)
            {
                if (s[j] == s1[j])
                    count++;
                else
                    break;
            }
        }
        else
        {
            for (j = 0; j < s1.length(); j++)
            {
                if (s[j] == s1[j])
                    count++;
                else
                    break;
            }
        }
        if (max < count)
            max = count;
    }

    if (max == 0)
        cout << -1 << endl;
    else
        cout << max << endl;

    return 0;
}