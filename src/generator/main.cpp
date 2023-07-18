#include <bits/stdc++.h>
using namespace std;
#define str(n) to_string(n)
#define binary(n) std::bitset<32>(n).to_string()
#define all(arr) arr.begin(), arr.end()
#define RANDOM mt19937 tourist(chrono::steady_clock::now().time_since_epoch().count())
#define random(x, y) uniform_int_distribution<int>(x, y)(tourist)
#define gc getchar_unlocked
#define fo(i, n) for (i = 0; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define si(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(s) scanf("%s", s)
#define pi(x) printf("%d\n", x)
#define pl(x) printf("%lld\n", x)
#define ps(s) printf("%s\n", s)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
#define YES cout << "YES" \
                 << "\n";
#define NO cout << "NO" \
                << "\n";
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pl;
typedef vector<ll> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

struct fraction
{
    int num, den;

    fraction() : num(0), den(1) {}

    fraction(int _num, int _den) : num(_num), den(_den) {}

    bool operator<(const fraction &other) const
    {
        return num * other.den < other.num * den;
    }

    bool operator<=(const fraction &other) const
    {
        return num * other.den <= other.num * den;
    }

    bool operator>(const fraction &other) const
    {
        return num * other.den > other.num * den;
    }

    bool operator>=(const fraction &other) const
    {
        return num * other.den >= other.num * den;
    }

    bool operator==(const fraction &other) const
    {
        return num * other.den == other.num * den;
    }

    bool operator!=(const fraction &other) const
    {
        return num * other.den != other.num * den;
    }
    fraction operator+(const ll &other)
    {
        return (fraction(num + other * den, den));
    }
    fraction operator-(const ll &other)
    {
        return (fraction(num - other * den, den));
    }
    fraction operator*(const ll &other)
    {
        return (fraction(num * other, den));
    }
    fraction operator/(const ll &other)
    {
        return (fraction(num, den * other));
    }

    bool operator!=(const ll &other)
    {
        return num != other * den;
    }

    fraction operator*(const fraction &other) const
    {
        return fraction(num * other.num, den * other.den);
    }
    fraction operator+(const fraction &other) const
    {
        return fraction(num * other.den + other.num * den, den * other.den);
    }
    fraction operator-(const fraction &other) const
    {
        return fraction(num * other.den - other.num * den, den * other.den);
    }
    fraction operator/(const fraction &other) const
    {
        return fraction(num * other.den, den * other.num);
    }

    friend ostream &operator<<(ostream &os, const fraction &f)
    {
        // return os << f.num << "/" << f.den << "=" << (long double) f.num / f.den;
        return os << (long double)f.num / f.den;
    }
};

ll mpow(ll base, ll exp);
ll npow(ll base, ll exp);
void ipgraph(ll n, ll m);
void dfs(ll u, ll par);
void read(vl &arr);

const ll mod = 1'000'000'007;
const ll N = 3e5, M = N;
//=======================

vi g[N];
ll a[N];

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

ll gcd(ll a, ll b)
{
    while (b != 0)
    {
        ll tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

#define int int64_t
vvl moves = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {0, 0, -1}, {0, -1, 0}, {-1, 0, 0}};
ll fileCount = 0;
vector<vector<vector<vector<bool>>>> solved;

void write(vector<vector<vector<bool>>> grid, int n)
{
    string filePath = "../outputs/" + to_string(n) + "/" + to_string(fileCount) + ".txt";
    fstream fout(filePath, ios::out);
    fileCount++;
    ll o = 2 * n + 1;

    fout << o << endl;
    fout << endl;

    for (int i = 0; i < o; i++)
    {
        for (int j = 0; j < o; j++)
        {
            for (int k = 0; k < o; k++)
                fout << grid[i][j][k] << " ";
            fout << endl;
        }
        fout << endl;
    }
    fout.close();
    cout << filePath << endl;
}

bool isSame(vector<vector<vector<bool>>> &grid1, vector<vector<vector<bool>>> &grid2)
{
    for (int i = 0; i < grid1.size(); i++)
        for (int j = 0; j < grid1.size(); j++)
            for (int k = 0; k < grid1.size(); k++)
                if (grid1[i][j][k] != grid2[i][j][k])
                    return false;
    return true;
}

bool visited(vector<vector<vector<bool>>> &grid)
{
    for (auto sol : solved)
        if (isSame(sol, grid))
            return true;
    return false;
}

void helper(vector<vector<vector<bool>>> &grid, int n, int filled, vvl &used)
{
    cout << filled << endl;
    if (filled == n)
    {
        if (!visited(grid))
        {
            solved.push_back(grid);
        }
        return;
    }

    vvl cubesFilled = used;

    for (auto pos : cubesFilled)
    {
        for (auto move : moves)
        {
            vl curr = {pos[0] + move[0], pos[1] + move[1], pos[2] + move[2]};
            if (curr[0] < 0 || curr[0] > 2 * n || curr[1] < 0 || curr[1] > 2 * n || curr[2] < 0 || curr[2] > 2 * n)
                continue;
            if (grid[curr[0]][curr[1]][curr[2]])
                continue;
            grid[curr[0]][curr[1]][curr[2]] = 1;
            // if (visited(grid))
            //     continue;
            used.push_back(curr);
            helper(grid, n, filled + 1, used);
            cout << "backtracking" << endl;
            if (used.size() > 0)
                used.pop_back();
            grid[curr[0]][curr[1]][curr[2]] = 0;
            cout << "backtracked" << endl;
        }
    }
}

void solve()
{
    ll i, j, n, m;
    cin >> n;
    ll o = 2 * n + 1;
    vector<vector<vector<bool>>> arr(o, vector<vector<bool>>(o, vector<bool>(o, 0)));
    vvl used;
    vl curr = {n, n, n};
    arr[n][n][n] = 1;
    used.push_back(curr);
    helper(arr, n, 1, used);
    cout << solved.size() << endl;
    // write(arr, n);
    for(auto sol : solved)
        write(sol, n);
}

int32_t main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    /*#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif*/

    ll t = 1;
    while (t-- > 0)
    {
        solve();
    }

    return 0;
}

ll mpow(ll base, ll exp)
{
    base %= mod;
    ll result = 1;
    while (exp > 0)
    {
        if (exp & 1)
            result = ((ll)result * base) % mod;
        base = ((ll)base * base) % mod;
        exp >>= 1;
    }
    return result;
}

ll npow(ll base, ll exp)
{
    ll result = 1;
    while (exp > 0)
    {
        if (exp & 1)
            result = ((ll)result * base);
        base = ((ll)base * base);
        exp >>= 1;
    }
    return result;
}

void ipgraph(ll n, ll m)
{
    ll i, u, v;
    while (m--)
    {
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(ll u, ll par)
{
    for (ll v : g[u])
    {
        if (v == par)
            continue;
        dfs(v, u);
    }
}
void read(vl &arr)
{
    for (int i = 0; i < arr.size(); i++)
        cin >> arr[i];
}
