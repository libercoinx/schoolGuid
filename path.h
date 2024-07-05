#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>

class Path {
public:
    struct Site {
        std::string name;
        bool del; // 标记该景点是否删除
    };

    struct Edge {
        int beginIndex;
        int endIndex;
        int length;
    };

    Path();
    void addSite(const std::string &name);
    void addEdge(int beginIndex, int endIndex, int length);
    void deleteEdge(int beginIndex, int endIndex);
    std::vector<Site> getSites() const;
    std::vector<Edge> getEdges() const;

private:
    std::vector<Site> sites;
    std::vector<Edge> edges;
};

#endif // PATH_H

