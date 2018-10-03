#include<bits/stdc++.h>
#include<time.h>
#define ll long long
using namespace std;
ll partition(vector<ll> &arr,ll low,ll high);
void quicksort(vector<ll> &arr,ll low,ll high,ll k)
{
	ll mid;
	bool wantpos=false;
	if(low<high)
	{
		mid=partition(arr,low,high);
		if(mid>k)
		{
			quicksort(arr,low,mid-1,k);
		}
		else if(mid<k)
		{
			quicksort(arr,mid+1,high,k);
		}
	}
}
ll partition(vector<ll> &arr,ll low,ll high)
{
	ll randpos=rand()%(high-low)+low;
    ll i=low-1;
  	ll tmp;
  	tmp=arr[randpos];
  	arr[randpos]=arr[high];
  	arr[high]=tmp;
  	ll pivot=arr[high];
    for (ll j = low; j<=high-1; j++) 
    { 
        if (arr[j] <= pivot) 
        { 
        	i++;
            tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp; 
        } 
    }
    tmp=arr[high];
    arr[high]=arr[i+1];
    arr[i+1]=tmp;
    return (i + 1); 
}
int main()
{
	ll n,i,tmp,k;
	cin>>n;
	vector<ll> arr;
	for(i=0;i<n;i++)
	{
		cin>>tmp;
		arr.push_back(tmp);
	}
	vector<ll> v=arr;
	while(1)
	{
		cin>>k;
		k--;
		quicksort(arr,0,arr.size()-1,k);
		cout<<"nth="<<arr[k]<<endl;
		nth_element(v.begin(),v.begin()+k,v.end());
    	cout << "nth=" << v[k] << '\n';
	}
	// cout<<"SOrted"<<endl;
	// for(i=0;i<arr.size();i++)
	// 	cout<<arr[i]<<endl;
}