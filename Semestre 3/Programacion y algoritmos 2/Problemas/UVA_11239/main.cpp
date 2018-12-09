#include <bits/stdc++.h>

using namespace std;

typedef struct _Project {
	string name;
	int users;
} Project;

bool cmp(const Project &a, const Project &b) {
	if(a.users == b.users) {
		return a.name.compare(b.name) < 0;
	}
	return a.users > b.users;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string str, proj;
	map<string, string> sched;
	map<string, int> lst;
	unordered_set<string> banned;
	vector<Project> res;
	while(true) {
		getline(cin, str);
		if(str == "0") break;

		if(str[0] == '1') {
			map<string, string>::iterator it1;
			map<string, int>::iterator it2;
			for(it1 = sched.begin(); it1 != sched.end(); it1++) {
				string user = it1->first;
				//cout << it1->first << " " << it1->second << "\n";
				if(banned.find(user) == banned.end()) {
					lst[it1->second]++;
				}
			}
			for(it2 = lst.begin(); it2 != lst.end(); it2++) {
				Project p;
				p.name = it2->first;
				p.users = it2->second;
				res.push_back(p);
			}
			sort(res.begin(), res.end(), cmp);
			for(int i = 0; i < res.size(); i++) {
				cout << res[i].name << " " << res[i].users << "\n";
			}
			sched.clear();
			lst.clear();
			banned.clear();
			res.clear();
		}
		else if(isupper(str[0])) {
			proj = str;
			lst[str] = 0;
		}
		else {
			// Es alumno
			if(sched.count(str)) {
				if(sched[str] != proj) {
					banned.insert(str);
				}
			}
			else {
				sched[str] = proj;
			}
		}
	}

	return 0;
}