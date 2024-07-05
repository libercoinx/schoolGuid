/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QButtonGroup>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>
#include <QContextMenuEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Site
{
    int num;
    std::string name;
    std::string info;
     bool del = false;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPixmap siteIcon;
    QPixmap mapImage;

    void showAddSiteDialog(const QPointF &position);
    void addSite(const QPointF &position, const QString &name, const QString &info);
    void showContextMenu(QGraphicsItem *item, const QPoint &globalPos);
    void confirmAndDeleteSite(QGraphicsItem *item);
    std::vector<Site> sites;
    QButtonGroup buttonGroup;

private slots:
    void on_setButton_clicked();

    void on_homeButton_clicked();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMap>
#include <vector>
#include <string>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "path.h"
struct Site
{
    int num;
    std::string name;
    std::string info;

    Site(int n, std::string name, std::string info) : num(n), name(name), info(info) {}
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_setButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void updateComboBoxes();
    void on_homeButton_clicked();
    void showContextMenu(QPushButton *button, const QPoint &globalPos);
    void confirmAndDeleteSite(QPushButton *button);
    void showAddSiteDialog(const QPoint &globalPos);
    void addSite(const QPoint &position, const QString &name, const QString &info);

private:
    Ui::MainWindow *ui;
    Path path;
    QButtonGroup buttonGroup;
    QPixmap siteIcon;
    QMap<QPushButton*, int> buttonToSiteIndexMap; // Map to store QPushButton to site index
    std::vector<Site> sites; // Vector to store site information
};

#endif // MAINWINDOW_H
