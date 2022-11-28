#include <bits/stdc++.h>

using namespace std;

class MinNode {
public:
    int id;//顶点编号
    int length;//当前路长
    friend bool operator<(MinNode A, MinNode B) {
        return (A.length > B.length);//不能带等于号
    }
};

class Graph {
private:
    int n , m ;//顶点数,边数
    vector<int> prev;//路径上的前驱数组；
    vector<int> dist;//最短距离数组，记录从源到各顶点当前最短距离
    vector<vector<int> > edges;//邻接矩阵
    int v, u;//所求路径的起始点
public:
    void Input();
    void ShortPath();
    void Output();
    void Work();
};

void Graph::Input() {
    cout << "请输入顶点数和边数:" << endl;
    cin >> n >> m;
    vector<int> ie1;
    edges.push_back(ie1);
    for (int i = 1; i <= n; i++) {
        vector<int> ie2(n + 1, 100000);
        edges.push_back(ie2);
    }
    cout << "请输入边及其权值:" << endl;;
    for (int i = 1; i <= m; i++) {
        int in1, in2 ,w;
        cin >> in1 >> in2>>w;
        edges[in1][in2] = w;
    }
    prev.assign(n + 1, -1);
    dist.assign(n + 1, 100000);
    cout << "请输入所求路径的起始点:" << endl;
    cin >> v >> u;
}

void Graph::ShortPath() {
    priority_queue<MinNode> Q;
    MinNode E = { v , 0 };
    dist[v] = 0;
    prev[v] = 0;//源点的前驱设为0
    while (1) {
        for (int i = 1; i <= n; i++) {
            if (edges[E.id][i] != 100000) {//检查所有从顶点E.id可达的顶点i
                int temp = E.length + edges[E.id][i];
                if (temp < dist[i]) {//如果比当前最短距离小,作为活结点加入优先级队列
                    MinNode active = { i , temp };
                    prev[i] = E.id;
                    dist[i] = temp;
                    Q.push(active);
                }
            }
        }
        if (!Q.empty()) {
            E = Q.top();
            Q.pop();
        }
        else {
            break;
        }
    }
}

void Graph::Output() {
    int p = u;
    vector<int> path;
    while (prev[p] != 0) {
        path.push_back(p);
        p = prev[p];
    }
    path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "最短距离数组:" << endl;
    for (int i = 1; i < dist.size(); i++) {
        cout <<dist[i]<<" ";
    }
    cout << endl;
    cout<< "前驱数组:" << endl;
    for (int i = 1; i < prev.size(); i++) {
        cout <<prev[i]<< " ";
    }
    cout << endl;
    cout << v << "-->" << u << "的最短路径 :" << endl;
    cout << v;
    for (int i = 1; i < path.size(); i++) {
        cout << "->" << path[i];
    }
    cout << endl;
}

void Graph::Work() {
    Input();
    ShortPath();
    Output();
}

int main()
{
    Graph G;
    G.Work();
    system("pause");
    return 0;
}
