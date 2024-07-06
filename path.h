#ifndef PATH_H
#define PATH_H

#include <vector>
#include <QString>
#include <algorithm>
#include <QDebug>
#define INF 0x3f3f3f3f

struct Site
{
//    std::string name;
//    std::string info;
    QString name;
    QString info;

    Site(QString name, QString info) : name(name), info(info) {}
};

class Path {
public:
    std::vector<std::vector<int>> edges;

    Path();
    void addSite(const QString &name, const QString &info);  //增加景点
    void deleteSite(int key);  //删除景点
    int getSiteNum();  //获取实际site数量
    QString getName(int key);  //获取site名字
    QString getInfo(int key);  //获取site信息
    void addEdge(int beginIndex, int endIndex, int length);
    void deleteEdge(QString begin, QString end);
//    std::vector<Site> getSites() const;
//    std::vector<Edge> getEdges() const;

private:
    std::vector<Site> sites;
};

#endif // PATH_H

