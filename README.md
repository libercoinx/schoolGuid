# SchoolGuide——校园导览系统
## 实现内容
* 求解最短路程
* 实现景点的添加和删除
* 实现路径的添加和删除
## 后端存储结构和基本定义
'  

    struct Site  
    {  
        QString name;  //景点名
        QString info;  //景点信息
        
        Site(QString name, QString info) : name(name), info(info) {}
    };

    class Path {
    private:
        std::vector<Site> sites;  //存储景点的数组
        std::vector<std::vector<int>> edges;  //存储边的矩阵
    };
'  

## log
### 7.3
* 搭建ui框架

### 7.4
* 完成了菜单栏和地图的基本部分
* 修改了一点ui设计

### 7.5
* 增加了景点的添加、删除功能

### 7.6
* 增加了路线编辑功能
* 完善边的存储结构
> ！！！注意修改了边的定义！！！

### 7.8
* 增加了添加、编辑路径的功能
* 增加了右键景点作为起点和终点功能
* ui修改

### 7.11
* 完成了dijkstra算法
* 补齐了10个基础景点（景点信息还没写
* 增加了查询路径功能
> 1.0版本完工

### 7.16
* 修bug
