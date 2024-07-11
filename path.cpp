#include "path.h"

Path::Path()
{
    //初始化sites组
    sites.push_back(Site("珞珈门","正在探索中"));
    sites.push_back(Site("九一二操场","正在探索中"));
    sites.push_back(Site("松园操场","正在探索中"));
    sites.push_back(Site("樱花大道","正在探索中"));
    sites.push_back(Site("桂园操场","正在探索中"));
    sites.push_back(Site("计算机学院","正在探索中"));
    sites.push_back(Site("行政楼","正在探索中"));
    sites.push_back(Site("老图书馆","正在探索中"));
    sites.push_back(Site("工主教","正在探索中"));
    sites.push_back(Site("月湖","正在探索中"));

    //初始化edges矩阵
    edges = std::vector<std::vector<int>>(10, std::vector<int>(10, INF));  //默认无穷大
    addEdge(0, 4, 5);
    addEdge(4, 5, 3);
    addEdge(4, 3, 3);
    addEdge(4, 7, 5);
    addEdge(3, 7, 1);
    addEdge(7, 8, 4);
    addEdge(1, 3, 2);
    addEdge(1, 6, 1);
    addEdge(2, 1, 6);
    addEdge(2, 9, 3);
    addEdge(1, 9, 5);
    addEdge(6, 0, 6);
    addEdge(4, 6, 4);

}

void Path::addSite(const QString &name, const QString &info)
{
    Site site(name, info);
    sites.push_back(site);

    //修改edges矩阵
    for(auto& col : edges)
        col.push_back(INF);  //每列加一
    edges.push_back(std::vector<int>(sites.size(), INF));  //加一列
}

void Path::deleteSite(int key){
    sites.erase(sites.begin() + key);

    //修改edges矩阵
    edges.erase(edges.begin() + key);
    for(auto& col : edges)
        col.erase(col.begin() + key);
}

int Path::getSiteNum(){
    return sites.size();
}

QString Path::getName(int key) {
    return sites[key].name;
}

QString Path::getInfo(int key) {
    return sites[key].info;
}

void Path::addEdge(int beginIndex, int endIndex, int length) {
    edges[beginIndex][endIndex] = length;
    edges[endIndex][beginIndex] = length;
}

void Path::deleteEdge(QString begin, QString end) {
    auto begin_in_vec = std::find_if(sites.begin(), sites.end(), [begin](const Site& rhs)->bool{
        return begin == rhs.name;
    });
    auto end_in_vec = std::find_if(sites.begin(), sites.end(), [end](const Site& rhs)->bool{
        return end == rhs.name;
    });
    edges[std::distance(sites.begin(), begin_in_vec)][std::distance(sites.begin(), end_in_vec)] = INF;
    edges[std::distance(sites.begin(), end_in_vec)][std::distance(sites.begin(), begin_in_vec)] = INF;
}

QStringList Path::getSiteList(){  //获取当前sites的所有name，用来更新comboBox
    QStringList list;
    for(auto item : sites)
        list << item.name;
    return list;
}

QString Path::Dijkstra(int begin, int end) {
    std::vector<int> dist(sites.size(), INF);  // 存储从起点到每个景点的距离
    std::vector<int> prev(sites.size(), -1); // 存储最短路径的前驱节点
    std::vector<bool> visited(sites.size(), false); // 标记是否已经访问过该节点
    dist[begin] = 0; // 起点到自身的距离为0
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq; // 定义一个优先队列，按照距离排序
    pq.emplace(0, begin); // 将起点加入优先队列

    while (!pq.empty()) { // 当优先队列不为空时循环
        int u = pq.top().second; // 获取优先队列中距离最小的节点
        pq.pop(); // 从优先队列中移除该节点

        if (visited[u]) continue; // 如果已经访问过该节点，则跳过
        visited[u] = true; // 标记该节点为已访问
        for (int v = 0; v < sites.size(); ++v) { // 遍历所有景点
            if (edges[u][v] != INF && !visited[v]) { // 如果存在边且该节点未被访问
                int alt = dist[u] + edges[u][v]; // 计算通过u到达v的备选距离
                if (alt < dist[v]) { // 如果备选距离小于已知的最小距离
                    dist[v] = alt; // 更新最小距离
                    prev[v] = u; // 更新前驱节点
                    pq.emplace(alt, v); // 将新的备选距离和节点v加入优先队列
                }
            }
        }
    }

    if (dist[end] == INF) return "没有找到路径"; // 如果终点的最小距离仍然是无穷大，则表示没有路径

    //debug
    qDebug() << dist[end];

    QString path; // 用于存储最终的路径
    for (int at = end; at != -1; at = prev[at]) { // 从终点开始，通过前驱节点回溯到起点
        path = sites[at].name + (path.isEmpty() ? "" : " -> ") + path; // 构建路径字符串
    }
    return path; // 返回构建的路径字符串
}
