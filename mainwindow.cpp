/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
QMap<QLabel*, Site> siteMap;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonGroup.setParent(this);

    // 初始化按钮组
    buttonGroup.addButton(ui->site_0, 0);
    buttonGroup.addButton(ui->site_1, 1);
    buttonGroup.addButton(ui->site_2, 2);
    buttonGroup.addButton(ui->site_3, 3);
    buttonGroup.addButton(ui->site_4, 4);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_setButton_clicked()
{
    ui->widget_home->hide();
    this->setStyleSheet("background-color: rgb(255, 255, 213)");
}


void MainWindow::on_homeButton_clicked()
{
    ui->widget_home->show();
    this->setStyleSheet("backgroundcolor: rgb(240, 240, 240)");
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QGraphicsItem *item = scene->itemAt(view->mapToScene(event->pos()), QTransform());
    if (item && item->data(0).isValid()) {
        showContextMenu(item, event->globalPos());
    } else {
        showAddSiteDialog(view->mapToScene(event->pos()));
    }
}

void MainWindow::showAddSiteDialog(const QPointF &position) {
    bool ok;
    QString name = QInputDialog::getText(this, "添加景点", "景点名称:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        QString info = QInputDialog::getText(this, "景点信息", "请输入景点信息:", QLineEdit::Normal, "", &ok);
        if (ok && !info.isEmpty()) {
            addSite(position, name, info);
        }
    }
}

void MainWindow::addSite(const QPointF &position, const QString &name, const QString &info) {
    QGraphicsPixmapItem *siteItem = scene->addPixmap(siteIcon);
    siteItem->setPos(position);
    siteItem->setData(0, QVariant(name));
    siteItem->setData(1, QVariant(info));
    siteItem->setToolTip(name + "\n" + info);
    siteItem->setFlag(QGraphicsItem::ItemIsSelectable);
}

void MainWindow::showContextMenu(QGraphicsItem *item, const QPoint &globalPos) {
    QMenu menu;
    QAction *deleteAction = menu.addAction("删除景点");
    QAction *selectedAction = menu.exec(globalPos);
    if (selectedAction == deleteAction) {
        confirmAndDeleteSite(item);
    }
}
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "path.h"
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QContextMenuEvent>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonGroup.setParent(this);
    // 确保 setupUi 调用后再隐藏控件
//    QTimer::singleShot(0, this, [this]()
//                       {
//        // 隐藏这些控件，等待 setButton 点击时显示
//        ui->add_begin->hide();
//        ui->add->hide();
//        ui->add_beignsite->hide();
//        ui->delete_2->hide();
//        ui->delete_beginsite->hide();
//        ui->add_endsite->hide();
//        ui->length->hide();
//        ui->delete_endsite->hide();
//        ui->add_end->hide();
//        ui->pathlength->hide();
//        ui->addButton->hide();
//        ui->delete_begin->hide();
//        ui->delete_end->hide();
//        ui->deleteButton->hide();
//    });
    // 初始化按钮组
    buttonGroup.addButton(ui->site_0, 0);
    buttonGroup.addButton(ui->site_1, 1);
    buttonGroup.addButton(ui->site_2, 2);
    buttonGroup.addButton(ui->site_3, 3);
    buttonGroup.addButton(ui->site_4, 4);

    // 为按钮安装事件过滤器
    ui->map->installEventFilter(this);
    for(auto* button : buttonGroup.buttons()){
        button->installEventFilter(this);
        button->setToolTip(QString::fromStdString(path.getName(buttonGroup.id(button))) + "\n" + QString::fromStdString(path.getInfo(buttonGroup.id(button))));
    }

    // 设置景点图标
    siteIcon = QPixmap(":/images/img/position.png");

    // 确认图标是否加载成功
    if (siteIcon.isNull()) {
        qDebug() << "Failed to load site icon.";
    } else {
        qDebug() << "Site icon loaded successfully.";
    }


    // 连接信号和槽
    connect(ui->setButton, &QPushButton::clicked, this, &MainWindow::on_setButton_clicked);
//    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
//    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_homeButton_clicked()
{
    ui->widget_home->show();
    this->setStyleSheet("background-color: rgb(240, 240, 240)");
}

void MainWindow::on_setButton_clicked()
{
    //隐藏主页控件
    ui->widget_home->hide();
    this->setStyleSheet("background-color: rgb(255, 255, 213)");

    // 显示相关控件
//    ui->add_begin->show();
//    ui->add->show();
//    ui->add_beignsite->show();
//    ui->delete_2->show();
//    ui->delete_beginsite->show();
//    ui->add_endsite->show();
//    ui->length->show();
//    ui->delete_endsite->show();
//    ui->add_end->show();
//    ui->pathlength->show();
//    ui->addButton->show();
//    ui->delete_begin->show();
//    ui->delete_end->show();
//    ui->deleteButton->show();

    // 更新下拉框选项
//    updateComboBoxes();
}
//void MainWindow::on_addButton_clicked()
//{
//    int beginIndex = ui->add_begin->currentIndex();
//    int endIndex = ui->add_end->currentIndex();
//    bool ok;
//    int length = ui->pathlength->text().toInt(&ok);

//    if (ok && beginIndex >= 0 && beginIndex < path.getSites().size() && endIndex >= 0 && endIndex < path.getSites().size())
//    {
//        path.addEdge(beginIndex, endIndex, length);
//        QMessageBox::information(this, "道路添加成功", "道路添加成功！");
//    }
//    else
//    {
//        QMessageBox::warning(this, "错误", "请输入有效的路径长度和景点！");
//    }
//}

//void MainWindow::on_deleteButton_clicked()
//{
//    int beginIndex = ui->delete_begin->currentIndex();
//    int endIndex = ui->delete_end->currentIndex();

//    if (beginIndex >= 0 && beginIndex < path.getSites().size() && endIndex >= 0 && endIndex < path.getSites().size())
//    {
//        path.deleteEdge(beginIndex, endIndex);
//        QMessageBox::information(this, "道路删除成功", "道路删除成功！");
//    }
//    else
//    {
//        QMessageBox::warning(this, "错误", "请选择有效的起点和终点！");
//    }
//}

//void MainWindow::updateComboBoxes()
//{
//    ui->add_begin->clear();
//    ui->add_end->clear();
//    ui->delete_begin->clear();
//    ui->delete_end->clear();

//    for (const auto &site : path.getSites())
//    {
//        if (!site.del)
//        {
//            ui->add_begin->addItem(QString::fromStdString(site.name));
//            ui->add_end->addItem(QString::fromStdString(site.name));
//            ui->delete_begin->addItem(QString::fromStdString(site.name));
//            ui->delete_end->addItem(QString::fromStdString(site.name));
//        }
//    }
//}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->map && event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent *contextMenuEvent = static_cast<QContextMenuEvent *>(event);
        showAddSiteDialog(contextMenuEvent->globalPos());
        return true;
    } else if (event->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent *contextMenuEvent = static_cast<QContextMenuEvent *>(event);
        QPushButton *button = qobject_cast<QPushButton *>(obj);
        if (button && button != ui->map)
        {
            showContextMenu(button, contextMenuEvent->globalPos());
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::showContextMenu(QPushButton *button, const QPoint &globalPos)
{
    QMenu menu;
    QAction *deleteAction = menu.addAction("删除景点");
    QAction *selectedAction = menu.exec(globalPos);
    if (selectedAction == deleteAction)
    {
        confirmAndDeleteSite(button);
    }
}

void MainWindow::confirmAndDeleteSite(QPushButton *button)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除景点", "你确定要删除这个景点吗？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        path.deleteSite(buttonGroup.id(button));
        buttonToSiteIndexMap.remove(button);
        buttonGroup.removeButton(button);  //按钮组中删除
        delete button;
    }
}

void MainWindow::showAddSiteDialog(const QPoint &globalPos)
{
    bool ok;
    QString name = QInputDialog::getText(this, "添加景点", "景点名称:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty())
    {
        QString info = QInputDialog::getText(this, "景点信息", "请输入景点信息:", QLineEdit::Normal, "", &ok);
        if (ok && !info.isEmpty())
        {
            addSite(ui->map->mapFromGlobal(globalPos), name, info);
        }
    }
}

void MainWindow::addSite(const QPoint &position, const QString &name, const QString &info)
{
    QPushButton *siteButton = new QPushButton(ui->map);
    siteButton->setIcon(QIcon(siteIcon));
    siteButton->setIconSize(QSize(24, 24));  // 设置图标大小为24x24
    siteButton->setStyleSheet("background-color: rgba(0,0,0,0);");
    siteButton->setGeometry(position.x() - 12, position.y() - 12, 24, 24);  // 确保图标中心对齐
    siteButton->setToolTip(name + "\n" + info);
    siteButton->installEventFilter(this);
    siteButton->show();

    // 将景点信息存储到sites vector中
    buttonGroup.addButton(siteButton, path.getSiteNum());
    path.addSite(name.toStdString(), info.toStdString());

    // 更新buttonToSiteIndexMap
    buttonToSiteIndexMap[siteButton] = path.getSiteNum() - 1;
}

