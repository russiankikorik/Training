#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

/* substring search with kmp and boyer - moore*/
using namespace std;

typedef long long int ll;

unordered_map<char, size_t> make_shifts(string& substr) {
	unordered_map<char, size_t> shifts;
	size_t substrsz = substr.size();
	for (size_t i = 0; i < substrsz; i += 1) {
		if (substrsz - i - 1 != 0) {
			shifts[substr[i]] = substrsz - i - 1;
		}
	}
	return shifts;
}

vector<size_t> bm(string& str, string& substr) {
	unordered_map<char, size_t> shifts = make_shifts(substr);
	vector<size_t> inds;
	size_t strsz = str.size();
	size_t substrsz = substr.size();
	size_t j = substrsz - 1;
	size_t i = substrsz - 1;
	while (i < strsz) {
		while (str[i] == substr[j]) {
			if (j == 0) {
				inds.push_back(i);
				j = substrsz - 1;
				i += substrsz;
			}
			else {
				i -= 1;
				j -= 1;
			}
		}
		if (shifts.find(str[i]) != shifts.end()) {
			i += shifts[str[i]];
		}
		else {
			i += substrsz;
		}
	}
	return inds;
}


vector<size_t> make_pf(string& str) {
	size_t sz = str.size();
	vector<size_t> pf = vector<size_t>(sz, 0);
	size_t j = 0;
	size_t i = 1;
	while (i < sz) {
		if (str[i] == str[j]) {
			pf[i] = j + 1;
			i += 1;
			j += 1;
		}
		else {
			if (j == 0) {
				i += 1;
			}
			else {
				j = pf[j - 1];
			}
		}
	}
	return pf;
}

vector<size_t> kmp(string& str, string& substr) {
	vector<size_t> pf = make_pf(substr);
	vector<size_t> inds;
	size_t strsz = str.size();
	size_t substrsz = substr.size();
	size_t j = 0;
	size_t i = 0;
while (i < strsz) {
		if (str[i] == substr[j]) {
			if (j == substrsz - 1) {
				inds.push_back(i - substrsz + 1);
				j = pf[j];
			}
			else {
				j += 1;
			}
			i += 1;
		}
		else {
			if (j == 0) {
				i += 1;
			}
			else {
				j = pf[j - 1];
			}
		}
	}
	return inds;
}
 
int main() {
	while (true) {
		string str, substr;
		cin >> str;
		cin >> substr;
		vector<size_t> inds = bm(str, substr);
		for (auto x: inds) {
			cout << x << ' ';
		}
		cout << endl;
	}
	return 0;
}







/*
int main() {
	ll mh, mm;
	cin >> mh >> mm;
	cout << (12 - mh) % 12 << ' ' << (60 - mm) % 60;
	return 0;
}
*/
/*int main() {
	size_t n, k, l;
	cin >> n >> k;
	vector<size_t> lengths;
	lengths.reserve(n);
	for (size_t i = 0; i < n; i += 1) {
		cin >> l;
		lengths.push_back(l);
	}
	sort(lengths.begin(), lengths.end());
	size_t left = 0;
	size_t right = n - 1;
	for (size_t i = 0; i < k; i += 1) {
		if (lengths[right] - lengths[left + 1] < lengths[right - 1] - lengths[left]) {
			left += 1;
		}
		else {
			right -= 1;
		}
	}	
	cout << lengths[right] - lengths[left];
	return 0;
}*/

/*int main() {
	ll n, m;
	cin >> n >> m;
	ll delta = m - n;
	if (delta <= 0) {
		cout << 0;
		return 0;
	}
	ll c2, c5;
	cin >> c2 >> c5;
	if (4 * c2 <= c5) {
		cout << delta * c2;
		return 0;
	}
	ll a, b, k;
	b = delta / 4;
	a = delta % 4;
	if (a * c2 > c5) {
		b += 1;
		a = 0;
	}
	cout << a * c2 + b * c5;
	return 0;
}*/

/*int main() {
	ll k, n, m;
	cin >> k >> n >> m;
	vector<vector<ll>> roads;
	roads.resize(k);
	ll roadi;
	ll day;
	ll inf = 1;
	inf = inf << 62;
	for (ll i = 0; i < n; i += 1) {
		cin >> day >> roadi;
		roads[roadi - 1].push_back(day);
	}
	vector<vector<ll>> interval_arrs;
	interval_arrs.resize(k);
	for (ll i = 0; i < k; i += 1) {
		interval_arrs[i].push_back(0);
		ll sz = roads[i].size();
		for (ll j = 0; j < sz - 1; j += 1) {
			interval_arrs[i].push_back(roads[i][j + 1] - roads[i][j]);
		}
		if (sz >= 1) {
			interval_arrs[i].push_back(inf);
		}
	}
	vector<ll> merged;
	for (auto& interval_arr : interval_arrs) {
		merged.insert(merged.end(), interval_arr.begin(), interval_arr.end());
	}
	sort(merged.begin(), merged.end());
	ll count = merged.size() - m;
	if (count < 0) {
		cout << 0;
		return 0;
	}
	if (merged[count - 1] == inf) {
		cout << -1;
		return 0;
	}
	ll sum = 0;
	for (ll i = 0; i < count; i += 1) {
		sum += merged[i];
	}
	cout << sum;
	return 0;
}*/

/**/


/*

*/

/*
typedef long long int ll;
int main() {

	ll n;
	cin >> n;
	unordered_map<ll, pair<ll, ll>> coords;
	coords.reserve(static_cast<size_t>(n));
	ll x, y;
	for (ll i = 0; i < n; i += 1) {
		cin >> x >> y;
		coords[i] = pair<ll, ll>(x, y);
	}
	ll maxlen;
	cin >> maxlen;
	ll start, finish;
	cin >> start >> finish;

	ll si, fi, sqml;
	si = start - 1;
	fi = finish - 1;
	//sqml = maxlen * maxlen;

	ll inf = 1;
	inf = inf << 62;

	vector<ll> roads;
	roads.reserve(static_cast<size_t>(n));
	for (ll i = 0; i < n; i += 1) {
		roads.push_back(inf);
	}
	roads[si] = 0;

	unordered_map<ll, pair<ll, ll>> checked;
	while (checked.size() != n) {
		ll m = inf;
		ll mi;
		for (auto& town : coords) {
			if (roads[town.first] < m) {
				m = roads[town.first];
				mi = town.first;
			}
		}
		if (m == inf) break;
		checked[mi] = coords[mi];
		coords.erase(mi);
		for (auto& town : coords) {
			//ll diff = (town.second.first - checked[mi].first) * (town.second.first - checked[mi].first) + (town.second.second - checked[mi].second) * (town.second.second - checked[mi].second) - sqml;
			ll diff = abs(town.second.first - checked[mi].first) + abs(town.second.second - checked[mi].second) - maxlen;
			if (diff <= 0) {
				if (roads[town.first] > 1 + roads[mi]) {
					roads[town.first] = 1 + roads[mi];
				}
			}
		}
	}
	if (roads[fi] == inf) {
		cout << -1;
	}
	else {
		cout << roads[fi];
	}
	return 0;
}
*/

/*int main() {
	
	ll n;
	cin >> n;
	vector<pair<ll, ll>> coords;
	coords.reserve(static_cast<size_t>(n));
	ll x, y;
	for (ll i = 0; i < n; i += 1) {
		cin >> x >> y;
		coords.push_back(pair<ll, ll>(x, y));
	}
	ll maxlen;
	cin >> maxlen;
	ll start, finish;
	cin >> start >> finish;

	ll si, fi, sqml;
	si = start - 1;
	fi = finish - 1;
	sqml = maxlen * maxlen;
	
	ll inf = 1;
	inf = inf << 62;

	vector<ll> sqds;
	sqds.reserve(static_cast<size_t>(n));
	for (ll i = 0; i < n; i += 1) {
		sqds.push_back(inf);
	}
	sqds[si] = 0;

	unordered_set<ll> inds;
	while (inds.size() != n) {
		ll m = inf;
		for (ll i = 0; i < n; i += 1) {
			if (inds.find(i) != inds.end()) {
				inds.insert(i);
				for (ll j = 0; j < n; j += 1) {
					if (inds.find(j) != inds.end()) {

					}
				}
			}
		}
	}

	return 0;
}*/

/*
int main() {
	int arr[256];
	for (int i = 0; i < 256; i += 1) {
		arr[i] = 0;
	}
	char ch = getchar();
	while (ch != '\n') {
		arr[ch] += 1;
		ch = getchar();
	}
	ch = getchar();
	while (ch != '\n') {
		arr[ch] -= 1;
		ch = getchar();
	}
	for (int i = 0; i < 256; i += 1) {
		if (arr[i] != 0) {
			cout << 0;
			return 0;
		}
	}
	cout << 1;
	return 0;
}
*/
/*
void generate(int step, int n, string& seq, int b) {
	if (step == 2 * n) {
		//if (b == 0) {
			cout << seq << endl;
		//}
		return;
	}
	if (2 * n - step - 1 > b) {
		seq[step] = '(';
		generate(step + 1, n, seq, b + 1);
	}
	if (b > 0) {
		seq[step] = ')';
		generate(step + 1, n, seq, b - 1);
	}
}


int main() {
	int n;
	cin >> n;
	string seq;
	int b = 0;
	seq.resize(static_cast<size_t>(2 * n));
	generate(0, n, seq, b);
	return 0;
}
*/
///////////////////////////////////////////////////////////////

/*
int main() {
	ll N, M, Q;
	cin >> N >> M >> Q;
	vector<vector<ll>> table;
	unordered_map<string, ll> col_names;
	table.reserve(static_cast<size_t>(N));
	string name;
	for (ll i = 0; i < M; i += 1) {
		cin >> name;
		col_names[name] = i;
	}
	ll val;
	char junk;
	for (ll i = 0; i < N; i += 1) {
		vector<ll> row;
		row.reserve(static_cast<size_t>(M));
		table.push_back(row);
		for (ll j = 0; j < M; j += 1) {
			scanf_s("%lld", &val);
			cin >> val;
			table[i].push_back(val);
		}
		//scanf_s("%c", &junk);
	}
	vector<ll> row_sums;
	row_sums.reserve(static_cast<size_t>(N));
	for (ll i = 0; i < N; i += 1) {
		ll row_sum = 0;
		for (ll j = 0; j < M; j += 1) {
			row_sum += table[i][j];
		}
		row_sums.push_back(row_sum);
	}
	unordered_set<ll> allowed;
	for (ll i = 0; i < N; i += 1) {
		allowed.insert(i);
	}

	string col_name;
	char cond;
	ll lim;
	ll col_num;
	for (ll i = 0; i < Q; i += 1) {
		cin >> col_name >> cond >> lim;
		//cin >> col_name >> cond;
		//scanf_s("%c", &cond);
		//scanf_s("%lld", &lim);
		//scanf_s("%c", &junk);
		col_num = col_names[col_name];
		if (cond == '<') {
			for (auto it = allowed.begin(); it != allowed.end(); it++) {
				if (table[*it][col_num] >= lim) {
					unordered_set<ll>::iterator sit;
					if ((sit = allowed.find(*it)) != allowed.end()) {
						allowed.erase(sit);
					}
				}
			}
			
		} else {
			for (auto it = allowed.begin(); it != allowed.end(); it++) {
				if (table[*it][col_num] <= lim) {
					unordered_set<ll>::iterator sit;
					if ((sit = allowed.find(*it)) != allowed.end()) {
						allowed.erase(sit);
					}
				}
			}
			
		}
	}
	ll total = 0;
	for (unordered_set<ll>::iterator it = allowed.begin(); it != allowed.end(); it++) {
		total += row_sums[*it];
	}
	cout << total;
	return 0;
}*/

/*
using namespace std;

typedef long long int ll;

unordered_map<ll, ll> build_deck(ll n) {

	unordered_map<ll, ll> deck;
	ll card;
	for (ll i = 0; i < n; i += 1) {
		cin >> card;
		unordered_map<ll, ll>::iterator it = deck.find(card);
		if (it == deck.end()) {
			deck[card] = 1;
		}
		else {
			deck[card] += 1;
		}
	}
	return deck;
}

void difference(unordered_map<ll, ll>& deckB, unordered_map<ll, ll>& deckA, unordered_map<ll, ll>& diff_deck) {
	diff_deck = deckB;
	for (unordered_map<ll, ll>::iterator it = deckA.begin(); it != deckA.end(); it++) {
		if (deckB.find(it->first) != deckB.end()) {
			diff_deck[it->first] = deckB[it->first] - it->second;
		}
		else {
			diff_deck[it->first] = 0 - it->second;
		}
	}
}

ll dif_sum(unordered_map<ll, ll>& diff_deck) {
	ll dif_sum = 0;
	for (unordered_map<ll, ll>::iterator it = diff_deck.begin(); it != diff_deck.end(); it++) {
		dif_sum += abs(it->second);
	}
	return dif_sum;
}

void change_ds(unordered_map<ll, ll>& diff_deck, ll* ds, ll tp, char player, ll card) {
	ll prev;
	if (diff_deck.find(card) == diff_deck.end()) {
		diff_deck[card] = 0;
		if (player == 'A') {
			diff_deck[card] -= tp;
		}
		else {
			diff_deck[card] += tp;
		}
		*ds += 1;
	}
	else {
		prev = diff_deck[card];
		if (player == 'A') {
			diff_deck[card] -= tp;
		} else {
			diff_deck[card] += tp;
		}
		if (abs(diff_deck[card]) > abs(prev)) {
			*ds += 1;
		}
		else *ds -= 1;
	}
}

int main() {
	ll N, M, Q;
	cin >> N >> M >> Q;
	unordered_map<ll, ll> deckA = build_deck(N);
	unordered_map<ll, ll> deckB = build_deck(M);
	unordered_map<ll, ll> diff_deck;
	difference(deckB, deckA, diff_deck);
	ll ds = dif_sum(diff_deck);
	ll tp;
	ll card;
	char player;
	for (ll i = 0; i < Q; i += 1) {
		cin >> tp >> player >> card;
		change_ds(diff_deck, &ds, tp, player, card);
		cout << ds << ' ';
	}
	return 0;
}
*/

/*unordered_map<ull, ull> build_deck(ull n) {
	
	unordered_map<ull, ull> deck;
	ull card;
	for (ull i = 0; i < n; i += 1) {
		cin >> card;
		unordered_map<ull, ull>::iterator it = deck.find(card);
		if (it == deck.end()) {
			deck[card] = 1;
		}
		else {
			deck[card] += 1;
		}
	}
	return deck;
}

ull diversity(unordered_map<ull, ull>& deckA, unordered_map<ull, ull>& deckB) {
	unordered_map<ull, ull> div_deck = deckA;
	unordered_map<ull, ull>::iterator bufit;
	for (unordered_map<ull, ull>::iterator it = deckB.begin(); it != deckB.end(); it++) {
		bufit = div_deck.find(it->first);
		if (bufit != div_deck.end()) {
			ull v1 = min<ull>(bufit->second, it->second);
			ull v2 = max<ull>(bufit->second, it->second);
			bufit->second = v2 - v1;
		}
		else {
			div_deck[it->first] = it->second;
		}
	}
	ull div_number = 0;
	for (unordered_map<ull, ull>::iterator it = div_deck.begin(); it != div_deck.end(); it++) {
		div_number += it->second;
	}
	return div_number;
}

inline void change_deck(unordered_map<ull, ull>& deck, int tp, ull card) {
	if (tp == 1) deck[card] += 1;
	else deck[card] -= 1;
}

int main() {
	ull N, M, Q;
	cin >> N >> M >> Q;
	unordered_map<ull, ull> deckA = build_deck(N);
	unordered_map<ull, ull> deckB = build_deck(M);
	int tp;
	ull card;
	char player;
	vector<ull> v;
	v.reserve(static_cast<size_t>(Q));
	for (ull i = 0; i < Q; i += 1) {
		cin >> tp >> player >> card;
		if (player == 'A') change_deck(deckA, tp, card);
		else change_deck(deckB, tp, card);
		v[i] = diversity(deckA, deckB);
	}
	for (ull i = 0; i < Q; i += 1) {
		cout << v[i] << ' ';
	}
	return 0;
}
*/










/*
const int dinm[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

ull totalsec_count(int *dinm_sum, ull y, ull m, ull d, ull h, ull min, ull s) {
	ull totalsec = (y - 1) * 365 * 24 * 60 * 60
		+ (static_cast<ull>(dinm_sum[m - 1])) * 24 * 60 * 60
		+ d * 24 * 60 * 60
		+ h * 60 * 60
		+ min * 60
		+ s;
	return totalsec;
}

int main() {
	int dinm[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int dinm_sum[12];
	dinm_sum[0] = 0;
	for (int i = 1; i < 12; i += 1) {
		dinm_sum[i] = dinm_sum[i - 1] + dinm[i - 1];
	}
	ull totalsec1, totalsec2;
	ull year1,
		month1,
		day1,
		hour1,
		min1,
		sec1,
		year2,
		month2,
		day2,
		hour2,
		min2,
		sec2;
	cin >> year1 >> month1 >> day1 >> hour1 >> min1 >> sec1;
	totalsec1 = totalsec_count(dinm_sum, year1, month1, day1, hour1, min1, sec1);
	cin >> year2 >> month2 >> day2 >> hour2 >> min2 >> sec2;
	totalsec2 = totalsec_count(dinm_sum, year2, month2, day2, hour2, min2, sec2);
	ull full_days = (totalsec2 - totalsec1) / (24 * 60 * 60);
	ull rem_sec = (totalsec2 - totalsec1) % (24 * 60 * 60);
	cout << full_days << ' ' << rem_sec;
	return 0;
}
*/