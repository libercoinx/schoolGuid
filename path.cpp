#include "path.h"

Path::Path()
{
    //初始化sites组
    sites.push_back(Site("珞珈门","正在探索中"));
    sites.push_back(Site("珞珈门","正在探索中"));
    sites.push_back(Site("珞珈门","正在探索中"));
    sites.push_back(Site("珞珈门","正在探索中"));
    sites.push_back(Site("珞珈门","正在探索中"));

    //初始化edges矩阵
    edges = std::vector<std::vector<int>>(5, std::vector<int>(5, INF));  //默认无穷大
    addEdge(0, 1, 5);
    addEdge(1, 3, 2);
    addEdge(2, 0, 9);
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

//void Path::deleteEdge(int beginIndex, int endIndex)
//{
//    edges.erase(
//        std::remove_if(edges.begin(), edges.end(), [beginIndex, endIndex](const Edge &edge)

//                       {
//            return edge.beginIndex == beginIndex && edge.endIndex == endIndex;
//        }),
//        edges.end()
//        );
//}

//std::vector<Path::Site> Path::getSites() const
//{
//    return sites;
//}

//std::vector<Path::Edge> Path::getEdges() const
//{
//    return edges;
//}

