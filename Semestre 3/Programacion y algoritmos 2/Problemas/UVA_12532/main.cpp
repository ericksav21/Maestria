#include <cstdio>
#include <cstring>
#include <iostream>

#define MAXN 100005

using namespace std;

int arr[MAXN];

struct fenwick{
	int t[MAXN + 1];

	void clean(){
		memset(t, 0, sizeof(t));
	}

	int lowbit(int i){
		return (i & -i);
	}

	void update(int pos, int val){
		for(; pos <= MAXN; pos += lowbit(pos)){
			t[pos] += val;
		}
	}

	void build(int arr[], int n){
		for(int i = 0; i < n; i++){
			update(i + 1, arr[i]);
		}
	}

	int query(int pos){
		int res = 0;
		for(; pos > 0; pos -= lowbit(pos)){
			res += t[pos];
		}
		return res;
	}

	int range(int i, int j){
		return i > 1 ? query(j) - query(i - 1) : query(j);
	}
};

int main() {
	struct fenwick zero, neg;
	int n, k, i, a, x, y;
	char t[2];

	while(scanf("%d %d", &n, &k) == 2){
		zero.clean();
		neg.clean();

		for(i = 1; i <= n; i++){
			scanf("%d", &arr[i]);
			a = arr[i];

			if(a == 0)
				zero.update(i, 1);
			else if(a < 0)
				neg.update(i, 1);
		}
		for(i = 1; i <= k; i++){
			scanf("%s %d %d", &t[0], &x, &y);
			if(t[0] == 'C'){
				if(y == 0 && arr[x] != 0){
					zero.update(x, 1);
					if(arr[x] < 0){
						neg.update(x, -1);
					}
				}
				else if(y < 0 && arr[x] >= 0){
					neg.update(x, 1);
					if(arr[x] == 0){
						zero.update(x, -1);
					}
				}
				else if(y > 0){
					if(arr[x] == 0){
						zero.update(x, -1);
					}
					else if(arr[x] < 0){
						neg.update(x, -1);
					}
				}
				arr[x] = y;
			}
			else{
				int sumz = zero.range(x, y);
				int sumneg = neg.range(x, y);

				if(sumz > 0){
					printf("0");
				}
				else if(sumneg > 0 && (sumneg % 2 != 0)){
					printf("-");
				}
				else{
					printf("+");
				}
			}
		}
		printf("\n");
	}

	return 0;
}