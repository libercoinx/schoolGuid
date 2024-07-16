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
    // 确保 setupUi 调用后再隐藏控件
    QTimer::singleShot(0, this, [this]()
                       {
        // 隐藏这些控件，等待 setButton 点击时显示
        ui->widget_set->hide();
    });
    // 初始化按钮组
    buttons.push_back(ui->site_0);
    buttons.push_back(ui->site_1);
    buttons.push_back(ui->site_2);
    buttons.push_back(ui->site_3);
    buttons.push_back(ui->site_4);
    buttons.push_back(ui->site_5);
    buttons.push_back(ui->site_6);
    buttons.push_back(ui->site_7);
    buttons.push_back(ui->site_8);
    buttons.push_back(ui->site_9);

    // 为按钮安装事件过滤器
    ui->map->installEventFilter(this);
    ui->pathTable->installEventFilter(this);
    for(auto button = buttons.begin(); button != buttons.end(); button++){
        (*button)->installEventFilter(this);
        (*button)->setToolTip(path.getName(std::distance(buttons.begin(), button)) + "\n" + path.getInfo(std::distance(buttons.begin(), button)));
    }

    // 设置景点图标
    siteIcon = QPixmap(":/images/img/position.png");

    // 确认图标是否加载成功
    if (siteIcon.isNull()) {
        qDebug() << "Failed to load site icon.";
    } else {
        qDebug() << "Site icon loaded successfully.";
    }

    //初始化pathTable
    tableModel = new QStandardItemModel();
    ui->pathTable->setModel(tableModel);
    QStringList table_h_headers;
    table_h_headers << "" << "" << "" << "";
    tableModel->setHorizontalHeaderLabels(table_h_headers);
    ui->pathTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);  //设置宽度固定
    ui->pathTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);  //设置居中
    ui->pathTable->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    ui->pathTable->setColumnWidth(0, 100);
    ui->pathTable->setColumnWidth(1, 40);
    ui->pathTable->setColumnWidth(2, 100);
    ui->pathTable->setColumnWidth(3, 100);
    updatePathTable();

    //更新comboBox
    updateComboBox();

    // 连接信号和槽
    connect(ui->setButton, &QPushButton::clicked, this, &MainWindow::on_setButton_clicked);
}

MainWindow::~MainWindow()
{
    delete tableModel;
    delete ui;
}

void MainWindow::on_homeButton_clicked()
{
    //隐藏set界面，显示主页
    ui->widget_home->show();
    ui->widget_set->hide();
    this->setStyleSheet("background-color: rgb(240, 240, 240)");
}

void MainWindow::on_setButton_clicked()
{
    //隐藏主页，显示set界面
    ui->widget_home->hide();
    ui->widget_set->show();
    this->setStyleSheet("background-color: rgb(255, 255, 213)");

}

void MainWindow::updateComboBox() {
    ui->combo_begin->clear();
    ui->combo_end->clear();
    ui->comboAdd_1->clear();
    ui->comboAdd_2->clear();
    QStringList list = path.getSiteList();
    ui->combo_begin->addItems(list);
    ui->combo_end->addItems(list);
    ui->comboAdd_1->addItems(list);
    ui->comboAdd_2->addItems(list);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->map && event->type() == QEvent::ContextMenu)  //添加景点
    {
        QContextMenuEvent *contextMenuEvent = static_cast<QContextMenuEvent *>(event);
        showAddSiteDialog(contextMenuEvent->globalPos());
        return true;
    } else if(obj == ui->pathTable && event->type() == QEvent::ContextMenu)  //删除路径
    {
        if(ui->pathTable->currentIndex().isValid()){
            QMenu menu;
            menu.addAction("删除路线");
            QAction* action = menu.exec(cursor().pos());
            if(action && action->text().compare("删除路线") == 0) {
                int currentRow = ui->pathTable->currentIndex().row();
                QString begin = tableModel->data(tableModel->index(currentRow,0)).toString();
                QString end = tableModel->data(tableModel->index(currentRow,2)).toString();
                path.deleteEdge(begin, end);  //删除这条边
                tableModel->removeRow(currentRow);
            }
        }
        return true;
    } else if (event->type() == QEvent::ContextMenu)  //删除景点
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
    QAction* deleteAction = menu.addAction("删除景点");
    QAction* addBeginAction = menu.addAction("作为起点");
    QAction* addEndAction = menu.addAction("作为终点");
    QAction *selectedAction = menu.exec(globalPos);

    if (selectedAction == deleteAction)
    {
        confirmAndDeleteSite(button);
    } else if (selectedAction == addBeginAction)
    {
        auto it = std::find(buttons.begin(), buttons.end(), button);  //查找对应按钮下标
        ui->combo_begin->setCurrentIndex(std::distance(buttons.begin(), it));
    } else if(selectedAction == addEndAction)
    {
        auto it = std::find(buttons.begin(), buttons.end(), button);  //查找对应按钮下标
        ui->combo_end->setCurrentIndex(std::distance(buttons.begin(), it));
    }
}

void MainWindow::confirmAndDeleteSite(QPushButton *button)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "删除景点", "你确定要删除这个景点吗？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        auto it = std::find(buttons.begin(), buttons.end(), button);  //查找对应按钮下标
        path.deleteSite(std::distance(buttons.begin(), it));  //删除site组和edges组中对应的对象
        buttons.erase(it);  //删除按钮组中的对应按钮
        updateComboBox();  //更新下拉框
        updatePathTable();  //更新pathTable
        buttonToSiteIndexMap.remove(button);
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
    siteButton->setStyleSheet("background-color: rgba(0,0,0,0);");  //设置背景透明
    siteButton->setCursor(Qt::PointingHandCursor);  //设置光标
    siteButton->setGeometry(position.x() - 12, position.y() - 12, 24, 24);  // 确保图标中心对齐
    siteButton->setToolTip(name + "\n" + info);
    siteButton->installEventFilter(this);
    siteButton->show();

    // 将景点信息存储到sites vector和button vector中
    buttons.push_back(siteButton);
    path.addSite(name, info);

    //更新下拉框
    updateComboBox();

    // 更新buttonToSiteIndexMap
    buttonToSiteIndexMap[siteButton] = path.getSiteNum() - 1;
}

void MainWindow::updatePathTable() {
    QList<QStandardItem*> add_items;
    tableModel->removeRows(0, tableModel->rowCount());
    for(int i = 0; i < path.getSiteNum(); i++)
        for(int j = 0; j <= i; j++)
            if(path.edges[i][j] != INF){
                add_items << new QStandardItem(path.getName(i)) << new QStandardItem("->") << new QStandardItem(path.getName(j)) << new QStandardItem(QString::number(path.edges[i][j]));
                tableModel->appendRow(add_items);
                add_items.clear();
            }
}


void MainWindow::on_addButton_clicked()
{
    int site_1 = ui->comboAdd_1->currentIndex();
    int site_2 = ui->comboAdd_2->currentIndex();
    int dis = ui->pathDis_in->value();
    if(site_1 != site_2) {
        path.addEdge(site_1, site_2, dis);
        updatePathTable();  //更新pathTable
    }
}


void MainWindow::on_searchButton_clicked()
{
    int begin = ui->combo_begin->currentIndex();
    int end = ui->combo_end->currentIndex();
    ui->pathText->setText(path.Dijkstra(begin, end));
}

