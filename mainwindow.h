#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Site{
    int num;
    std::string name;
    std::string info;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<Site> sites;
    QButtonGroup buttonGroup;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
