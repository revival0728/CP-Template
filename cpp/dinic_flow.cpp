// copied from https://github.com/GuanH/Rurudo_daisuki_Codebook/blob/main/flow/dinic.cpp
const int MXN=1000;
#define DINIC_MAX INT_MAX
struct Dinic
{
  struct Edge
  {
    int v, f, re;
  };
  int n, s, t, level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t)
  {
    n = _n;
    s = _s;
    t = _t;
    for (int i = 0; i < n; i++)
      E[i].clear();
  }
  void addEdge(int u, int v, int f)
  {
    E[u].push_back({v, f, (int)(E[v].size())});
    E[v].push_back({u, 0, (int)(E[u].size())-1});
  }
  bool BFS()
  {
    for (int i = 0; i < n; i++)
      level[i] = -1;
    queue<int> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty())
    {
      int u = que.front();
      que.pop();
      for (auto it : E[u])
      {
        if (it.f > 0 && level[it.v] == -1)
        {
          level[it.v] = level[u] + 1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  int DFS(int u, int nf)
  {
    if (u == t)
      return nf;
    int res = 0;
    for (auto &it : E[u])
    {
      if (it.f > 0 && level[it.v] == level[u] + 1)
      {
        int tf = DFS(it.v, min(nf, it.f));
        res += tf;
        nf -= tf;
        it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0)
          return res;
      }
    }
    if (!res)
      level[u] = -1;
    return res;
  }
  int flow(int res = 0)
  {
    while (BFS())
      res += DFS(s, DINIC_MAX);
    return res;
  }
} flow;
