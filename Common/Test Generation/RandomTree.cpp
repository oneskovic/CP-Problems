vector<int> generate_tree(int n)
{
    vector<int> prufer_seq(n - 2);
    for (int i = 0; i < n - 2; i++)
    {
        prufer_seq[i] = rand() % n + 1;
    }

    vector<int> degree(n + 1);
    vector<vector<int>> adj = vector<vector<int>>(n + 1, vector<int>());
    for (int i = 1; i <= n; i++)
        degree[i] = 1;
    for (int i : prufer_seq)
        degree[i]++;
    for (int i : prufer_seq)
    {
        for (int j = 1; j <= n; j++)
        {
            if (degree[j] == 1)
            {
                adj[i-1].push_back(j-1);
                adj[j-1].push_back(i-1);
                degree[i]--;
                degree[j]--;
                break;
            }
        }
    }
    int u = 0, v = 0;
    for (int i = 1; i <= n; i++)
    {
        if (degree[i] == 1)
        {
            if (u == 0)
                u = i;
            else
            {
                v = i;
                break;
            }
        }
    }
    adj[u-1].push_back(v-1);
    adj[v-1].push_back(u-1);

    vector<int> dag(adj.size());
    dfs(0, -1, dag, adj);
    return dag;
}