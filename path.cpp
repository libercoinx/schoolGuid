#include "path.h"
#include <algorithm>

Path::Path()
{
    //初始化sites组
    sites.push_back(Site(0,"珞珈门","正在探索中"));
    sites.push_back(Site(1,"珞珈门","正在探索中"));
    sites.push_back(Site(2,"珞珈门","正在探索中"));
    sites.push_back(Site(3,"珞珈门","正在探索中"));
    sites.push_back(Site(4,"珞珈门","正在探索中"));
    siteNum += 5;
}

void Path::addSite(const std::string &name, const std::string &info)
{
    Site site(siteNum, name, info);
    sites.push_back(site);
    siteNum++;
}

void Path::deleteSite(int key){
    sites.erase(sites.begin() + key);
}

int Path::getSiteNum(){
    return sites.size();
}

std::string Path::getName(int key) {
    return sites[key].name;
}

std::string Path::getInfo(int key) {
    return sites[key].info;
}
//void Path::addEdge(int beginIndex, int endIndex, int length)
//{
//    Edge edge; // 声明 Edge 类型的变量
//    edge.beginIndex = beginIndex;
//    edge.endIndex = endIndex;
//    edge.length = length;
//    edges.push_back(edge);
//}

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

