#include "leftbarmycollect.h"

#include "leftbarmymusic.h"

#include <QPalette>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QKeySequence>

LeftBarMyCollec::LeftBarMyCollec(QWidget *parent) : QWidget(parent)
{
    m_pListWidget = new QListWidget(parent);
    m_pListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    initMenu();
    m_pListWidget->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    connect(m_pListWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ListWidgetIsRightClicked(const QPoint&)));

    connect(m_pListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(ListWidgetItemIsLeftClicked(QListWidgetItem*)));

}

LeftBarMyCollec::~LeftBarMyCollec(){
    delete m_pListWidget;
    delete m_pMenu;
}

void LeftBarMyCollec::initMenu(){
    m_pMenu = new QMenu(this);
    m_pMenu->setStyleSheet("background:white;QMenu::item:selected {background-color:rgb(159,159,159);}"
                           "QMenu::item:pressed {background-color: rgb(159,159,159);");

    QAction* action = new QAction("播放", this);
    action->setIcon(QIcon(":/images/LeftBarPlay.svg"));
    action->setShortcut(QKeySequence("enter"));
    m_vActions.push_back(action);
    m_pMenu->addAction(action);

    action = new QAction("下一首播放", this);
    action->setIcon(QIcon(":/images/LeftBarNext.svg"));
    m_vActions.push_back(action);
    m_pMenu->addAction(action);

    action = new QAction("分享", this);
    action->setIcon(QIcon(":/images/LeftBarSend.svg"));
    m_vActions.push_back(action);
    m_pMenu->addAction(action);

    action = new QAction("复制链接", this);
    action->setIcon(QIcon(":/images/LeftBarCopyLink.svg"));
    m_vActions.push_back(action);
    m_pMenu->addAction(action);

    action = new QAction("下载全部", this);
    action->setIcon(QIcon(":/images/LeftBarDownload.svg"));
    m_vActions.push_back(action);
    m_pMenu->addAction(action);

    action = new QAction("删除歌单", this);
    action->setIcon(QIcon(":/images/LeftBarDelete.svg"));
    action->setShortcut(QKeySequence::Delete);
    m_vActions.push_back(action);
    m_pMenu->addAction(action);

    connect(m_vActions[0], SIGNAL(triggered(bool)), this, SLOT(playAllSongsInList()));
    connect(m_vActions[1], SIGNAL(triggered(bool)), this, SLOT(playAtNextTime()));
    connect(m_vActions[2], SIGNAL(triggered(bool)), this, SLOT(shareLink()));
    connect(m_vActions[3], SIGNAL(triggered(bool)), this, SLOT(copyLink()));
    connect(m_vActions[4], SIGNAL(triggered(bool)), this, SLOT(downloadAllSongsInList()));
    connect(m_vActions[5], SIGNAL(triggered(bool)), this, SLOT(deleteCurrentSongList()));

}

void LeftBarMyCollec::playAllSongsInList(){
    qDebug() << "playAllSongsInList";
}

void LeftBarMyCollec::playAtNextTime(){
    qDebug() << "playAtNextTime";
}

void LeftBarMyCollec::shareLink(){
    qDebug() << "shareLink";
}

void LeftBarMyCollec::copyLink(){
    qDebug() << "copyLink";
}

void LeftBarMyCollec::downloadAllSongsInList(){
    qDebug() << "downloadAllSongsInList";
}

void LeftBarMyCollec::deleteCurrentSongList(){
    qDebug() << "deleteCurrentSongList";
}

void LeftBarMyCollec::addFavorite(const QString& label){
    QListWidgetItem* item = new QListWidgetItem(m_pListWidget);
    item->setIcon(QIcon(":/images/songlist.svg"));
    item->setText(label);
    item->setTextAlignment(Qt::AlignLeft);
    m_pListWidget->addItem(item);
}

void LeftBarMyCollec::addColumnTitle(const QString& title){
    QListWidgetItem* item = new QListWidgetItem(m_pListWidget);
    item->setText(title);
    item->setFont(QFont("微软雅黑", 9));
    item->setTextColor(QColor(159, 159, 159));
    item->setFlags(Qt::ItemIsEnabled);
    m_pListWidget->addItem(item);
}

void LeftBarMyCollec::ListWidgetItemIsLeftClicked(QListWidgetItem* item){
    qDebug() << item->text();
    qDebug() << "Left Clicked";

}

void LeftBarMyCollec::ListWidgetIsRightClicked(const QPoint & pos){
    ListWidgetItemIsRightClicked(pos);
}

void LeftBarMyCollec::ListWidgetItemIsRightClicked(const QPoint & pos){
    qDebug() << "right Clicked";
    m_pMenu->exec(QCursor::pos());
}

void LeftBarMyCollec::setGeometry(int ax, int ay, int aw, int ah){
    m_pListWidget->setGeometry(ax, ay, aw, ah);
}

void LeftBarMyCollec::setListStyleSheet(const QString& styleSheet){
    m_pListWidget->setStyleSheet(styleSheet);
}
