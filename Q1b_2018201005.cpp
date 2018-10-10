#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll comparator(struct suffixNode a, struct suffixNode b);
void suffixSort();

struct suffixNode
{
    ll position; // to store original position of suffix string in suffix array.
    ll child[2]; // help to sort suffix array based on first child and next child.
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
    ll i, j, k, size;
    size = input.length();
    ll index[size];

    // store initial postion of suffix string in suffix array
    // and store child and next child based on first and second char.

    for (i = 0; i < size; i++)
    {
        suffixarray[i].position = i;
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

    // sort the initial suffix array base on first child and
    // if first child is same then sort based on next child.

    sort(suffixarray, suffixarray + size, comparator);

    // we have got sorted suffix array based on first two char.
    // now continue this process for first 2 char,4 char,8 char till the end of string.

    for (j = 2; j < size; j = j * 2)
    {
        index[suffixarray[0].position] = 0;
        ll before = suffixarray[0].child[0];
        ll current = 0;
        suffixarray[0].child[0] = current;

        // calculate child.
        // if both child and next child are same for current and previos suffix string
        // then make child same as previous suffix string child.
        // else store current string child as previous child + 1.
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

            index[suffixarray[k].position] = k;
        }

        // calculate next child.
        // get child of a suffix string and add j which is number of char that you are
        // examining and get the position of the suffix string which has distance j
        // then find its original index and get child which is a next rank of current
        // suffix string.
        for (k = 0; k < size; k++)
        {
            ll child_1 = suffixarray[k].position + j;
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

        // sorting based on child and next child.
        sort(suffixarray, suffixarray + size, comparator);
    }

    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    ll i, f = 0, pos, n, k, j, count = 0, max = -9999;
    cin >> input;
    cin >> k;
    n = input.size();
    suffixarray = new struct suffixNode[n];
    suffixSort();

    // get longest common prefix which is longest substring.
    for (i = 0; i < n - k + 1; i++)
    {
        count = 0;
        string s = input.substr(suffixarray[i].position);
        string s1 = input.substr(suffixarray[i + k - 1].position);
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