#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>

struct Site
{
    int num;
    std::string name;
    std::string info;

    Site(int n, std::string name, std::string info) : num(n), name(name), info(info) {}
};

class Path {
public:
    Path();
    void addSite(const std::string &name, const std::string &info);
    void deleteSite(int key);
    int getSiteNum();  //获取实际site数量
    std::string getName(int key);  //获取site名字
    std::string getInfo(int key);  //获取site信息
//    void addEdge(int beginIndex, int endIndex, int length);
//    void deleteEdge(int beginIndex, int endIndex);
//    std::vector<Site> getSites() const;
//    std::vector<Edge> getEdges() const;

private:
    std::vector<Site> sites;
    int** edges;
    int siteNum = 0;  //记录当前加到了邻接矩阵的哪个下标，邻接矩阵不会减小，对应Site中的num属性
};

#endif // PATH_H

