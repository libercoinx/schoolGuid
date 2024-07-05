#include "path.h"
#include <algorithm>

Path::Path()
{
    // 初始构造函数可以根据需要初始化内容，比如读取文件中存储的路径信息，或者是数据库里面的路径信息
}

void Path::addSite(const std::string &name)
{
    Site site;
    site.name = name;
    site.del = false;
    sites.push_back(site);
}

void Path::addEdge(int beginIndex, int endIndex, int length)
{
    Edge edge; // 声明 Edge 类型的变量
    edge.beginIndex = beginIndex;
    edge.endIndex = endIndex;
    edge.length = length;
    edges.push_back(edge);
}

void Path::deleteEdge(int beginIndex, int endIndex)
{
    edges.erase(
        std::remove_if(edges.begin(), edges.end(), [beginIndex, endIndex](const Edge &edge)

                       {
            return edge.beginIndex == beginIndex && edge.endIndex == endIndex;
        }),
        edges.end()
        );
}

std::vector<Path::Site> Path::getSites() const
{
    return sites;
}

std::vector<Path::Edge> Path::getEdges() const
{
    return edges;
}

