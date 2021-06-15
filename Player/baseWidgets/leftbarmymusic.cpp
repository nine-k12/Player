#include "leftbarmymusic.h"

#include <QPalette>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QKeySequence>

LeftBarMyMusic::LeftBarMyMusic(QWidget *parent) : QWidget(parent)
{
    m_pListWidget = new QListWidget(parent);
    m_pListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(m_pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(ListWidgetItemIsLeftClicked(QListWidgetItem*)));
}

LeftBarMyMusic::~LeftBarMyMusic(){
    delete m_pListWidget;
    delete m_pMenu;
}

void LeftBarMyMusic::updateMyMusicItem(){
    QListWidgetItem* item = new QListWidgetItem(m_pListWidget);
    item->setIcon(QIcon(":/images/music.svg"));
    item->setText("本地音乐");
    item->setTextAlignment(Qt::AlignLeft);
    item->setWhatsThis("LocalMusic");
    m_pListWidget->addItem(item);

    item = new QListWidgetItem(m_pListWidget);
    item->setIcon(QIcon(":/images/download.svg"));
    item->setText("下载管理");
    item->setTextAlignment(Qt::AlignLeft);
    item->setWhatsThis("DownLoadManager");
    m_pListWidget->addItem(item);

    item = new QListWidgetItem(m_pListWidget);
    item->setIcon(QIcon(":/images/recentplay.svg"));
    item->setText("最近播放");
    item->setTextAlignment(Qt::AlignLeft);
    item->setWhatsThis("RecentPlay");
    m_pListWidget->addItem(item);

    item = new QListWidgetItem(m_pListWidget);
    item->setIcon(QIcon(":/images/love.svg"));
    item->setText("我喜欢的音乐");
    item->setTextAlignment(Qt::AlignLeft);
    item->setWhatsThis("MyFavoriteMusic");
    m_pListWidget->addItem(item);
}

void LeftBarMyMusic::addColumnTitle(const QString& title){
    QListWidgetItem* item = new QListWidgetItem(m_pListWidget);
    item->setText(title);
    item->setFont(QFont("微软雅黑", 9));
    item->setTextColor(QColor(159, 159, 159));
    item->setFlags(Qt::ItemIsEnabled);
    m_pListWidget->addItem(item);
}

void LeftBarMyMusic::ListWidgetItemIsLeftClicked(QListWidgetItem* item){
    int row = m_pListWidget->row(item);
    if(row == 1)
        emit openLocalFolderIsSelected();
    else if(row > 1 && row < 5)
        emit TableIsSelected(item->whatsThis());
    qDebug() << "Left Clicked";
}


void LeftBarMyMusic::setGeometry(int ax, int ay, int aw, int ah){
    m_pListWidget->setGeometry(ax, ay, aw, ah);
}

void LeftBarMyMusic::setListStyleSheet(const QString& styleSheet){
    m_pListWidget->setStyleSheet(styleSheet);
}
