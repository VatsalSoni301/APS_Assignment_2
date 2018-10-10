#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll partition(vector<ll> &arr, ll low, ll high);
void find_nth(vector<ll> &arr, ll low, ll high, ll k);

void find_nth(vector<ll> &arr, ll low, ll high, ll k)
{
	ll mid;
	bool wantpos = false;
	if (low < high)
	{
		mid = partition(arr, low, high);
		if (mid > k)
		{
			find_nth(arr, low, mid - 1, k);
		}
		else if (mid < k)
		{
			find_nth(arr, mid + 1, high, k);
		}
	}
}
ll partition(vector<ll> &arr, ll low, ll high)
{
	ll randpos = rand() % (high - low) + low;
	ll i = low - 1;
	ll tmp;
	tmp = arr[randpos];
	arr[randpos] = arr[high];
	arr[high] = tmp;
	ll pivot = arr[high];
	for (ll j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	tmp = arr[high];
	arr[high] = arr[i + 1];
	arr[i + 1] = tmp;
	return (i + 1);
}
int main()
{
	ios_base::sync_with_stdio(false);
	ll n, i, tmp, k;
	cin >> n;
	cin >> k;
	vector<ll> arr;
	for (i = 0; i < n; i++)
	{
		cin >> tmp;
		arr.push_back(tmp);
	}
	vector<ll> v = arr;
	k--;
	clock_t start1 = clock();
	find_nth(arr, 0, arr.size() - 1, k);
	cout << "nth=" << arr[k] << endl;
	clock_t end1 = clock();
	clock_t start = clock();
	nth_element(v.begin(), v.begin() + k, v.end());
	cout << "nth=" << v[k] << endl;
	clock_t end = clock();
	cout << "mine=" << 1.0 * (end1 - start1) / CLOCKS_PER_SEC << endl;
	cout << "org=" << 1.0 * (end - start) / CLOCKS_PER_SEC << endl;

	// cout<<"Sorted"<<endl;
	// for(i=0;i<arr.size();i++)
	// 	cout<<arr[i]<<endl;
}