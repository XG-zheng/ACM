#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
int p[20] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,51};
ll ans,n;
 ll cnt=0;
void dfs(int pos,ll num,ll sum,int len)//��ǰö��p��λ�ã�Լ����������sum,ǰһ�������ӵ�ָ�����ֵ
{
	cnt++;
    if (sum>n) return ;
    if (sum<=n) ans=max(ans,num);
    for (int i=len;i>=1;i--) {
        ll res=pow(p[pos],i);
        if (sum>n/res) continue;//ע�ⲻҪ��sum*res>n��ըlong long
        dfs(pos+1,num*(i+1),sum*(res),i);
    }
}
int main()
{
    cin>>n;
    ans=0;
    dfs(1,1,1,30);
    cout<<ans<<endl;
	return 0;
}

