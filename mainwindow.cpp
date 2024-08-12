#include"ladraglist.h"
#include"ladraglistview.h"
#include"lastyleditemdelegate.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QVBoxLayout>
#include<QStandardItemModel>

//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    QStringList list;

////    ui-listView
//}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initUi();
}

void MainWindow::initUi()
{
    setFixedSize(250, 600);

    QStandardItemModel *listModel = new QStandardItemModel();
    listModel->setItem(0, 0, new LaDragListView(QIcon(":/listBar_Icon/1.png"), QIcon(":/listBar_Icon/1_hover.png"), "发现音乐"));
    listModel->setItem(1, 0, new LaDragListView(QIcon(":/listBar_Icon/2.png"), QIcon(":/listBar_Icon/2_hover.png"), "私人FM"));
    listModel->setItem(2, 0, new LaDragListView(QIcon(":/listBar_Icon/3.png"), QIcon(":/listBar_Icon/3_hover.png"), "朋友"));
    listModel->setItem(3, 0, new LaDragListView(QIcon(":/listBar_Icon/4.png"), QIcon(":/listBar_Icon/4_hover.png"), "MV"));
    listModel->setItem(4, 0, new LaDragListView(QIcon(":/listBar_Icon/5.png"), QIcon(":/listBar_Icon/5_hover.png"), "本地音乐"));
    listModel->setItem(5, 0, new LaDragListView(QIcon(":/listBar_Icon/6.png"), QIcon(":/listBar_Icon/6_hover.png"), "下载管理"));
    listModel->setItem(6, 0, new LaDragListView(QIcon(":/listBar_Icon/7.png"), QIcon(":/listBar_Icon/7_hover.png"), "我的音乐云盘"));
    listModel->setItem(7, 0, new LaDragListView(QIcon(":/listBar_Icon/8.png"), QIcon(":/listBar_Icon/8_hover.png"), "我的收藏"));

    LaDragList *listView = new LaDragList(this);
    listView->setIconSize(QSize(25, 25));
    listView->setFocusPolicy(Qt::NoFocus);  //这样可禁用tab键和上下方向键并且除去复选框
    listView->setFixedHeight(320);
    listView->setFont(QFont("宋体", 10, QFont::DemiBold));
    listView->setStyleSheet(
                //"*{outline:0px;}"  //除去复选框
                "QListView{background:rgb(245, 245, 247); border:0px; margin:0px 0px 0px 0px;}"
                "QListView::Item{height:40px; border:0px; padding-left:14px; color:rgba(200, 40, 40, 255);}"
                "QListView::Item:hover{color:rgba(40, 40, 200, 255); padding-left:14px;}"
                "QListView::Item:selected{color:rgba(40, 40, 200, 255); padding-left:15px;}"
                );

    LaStyledItemDelegate *delegate = new LaStyledItemDelegate();
    listView->setItemDelegate(delegate);
    listView->setModel(listModel);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->addWidget(listView);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

