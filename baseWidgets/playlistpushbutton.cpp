#include "playlistpushbutton.h"

#include <QDebug>
#include <QListWidgetItem>
#include <QPair>

PlayListPushButton::PlayListPushButton(QWidget *parent) : QWidget(parent)
{
    m_pPushButton = new QPushButton(parent);

    m_pListWidget = new QListWidget(parent);
    m_pListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pListWidget->hide();

    updateList();


    currentState = CLOSED;

    connect(m_pPushButton, SIGNAL(clicked()), this, SLOT(stateChanged()));
}

PlayListPushButton::~PlayListPushButton(){
    delete m_pPushButton;
    delete m_pListWidget;
}

void PlayListPushButton::stateChanged(){
    if(currentState == CLOSED){
        currentState = OPEN;
        showList();
    }
    else{
        currentState = CLOSED;
        closeList();
    }
}

void PlayListPushButton::showList(){
    qDebug() << "打开播放列表";
    m_pListWidget->show();
}

void PlayListPushButton::closeList(){
    qDebug() << "关闭播放列表";
    m_pListWidget->close();
}

void PlayListPushButton::updateList(){
    QListWidgetItem* item = new QListWidgetItem(m_pListWidget);
    item->setIcon(QIcon(":/images/music.svg"));
    item->setText("本地音乐");
    m_vListItems.push_back(item);

}

void PlayListPushButton::setIconSize(const QSize& qsize){
    m_pPushButton->setIconSize(qsize);
}

void PlayListPushButton::setText(const QString& text){
    m_pPushButton->setText(text);
}

void PlayListPushButton::setIcon(const QIcon& icon){
    m_pPushButton->setIcon(icon);
}


void PlayListPushButton::setFixedSize(const QSize & qsize){
    m_pPushButton->setFixedSize(qsize);
}

void PlayListPushButton::setPushButtonGeometry(int ax, int ay, int aw, int ah){
    m_pPushButton->setGeometry(ax, ay, aw, ah);
}

void PlayListPushButton::setListGeometry(int ax, int ay, int aw, int ah){
    m_pListWidget->setGeometry(ax, ay, aw, ah);
}

void PlayListPushButton::setPushButtonStyleSheet(const QString& styleSheet){
    m_pPushButton->setStyleSheet(styleSheet);
}

void PlayListPushButton::setListStyleSheet(const QString& styleSheet){
    m_pListWidget->setStyleSheet(styleSheet);
}

void PlayListPushButton::setAutoRepeatInterval(int val){
    m_pPushButton->setAutoRepeatInterval(val);
}
