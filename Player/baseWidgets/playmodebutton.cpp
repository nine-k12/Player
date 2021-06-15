#include "playmodebutton.h"

#include <QDebug>

PlayModeButton::PlayModeButton(QWidget *parent) : QWidget(parent)
{
    m_width = 40;
    m_height = 40;

    // Sequential, Loop, Random, CurrentItemInLoop
    m_pPushBotton = new QPushButton(parent);
    m_pStateMachine = new QStateMachine;

    m_pStateSequential = new QState;
    m_pStateLoop = new QState;
    m_pStateRandom = new QState;
    m_pStateCurrentItemInLoop = new QState;

    m_pStateSequential->addTransition(m_pPushBotton, SIGNAL(clicked()), m_pStateLoop);
    m_pStateLoop->addTransition(m_pPushBotton, SIGNAL(clicked()), m_pStateRandom);
    m_pStateRandom->addTransition(m_pPushBotton, SIGNAL(clicked()), m_pStateCurrentItemInLoop);
    m_pStateCurrentItemInLoop->addTransition(m_pPushBotton, SIGNAL(clicked()), m_pStateSequential);

    m_pStateMachine->addState(m_pStateSequential);
    m_pStateMachine->addState(m_pStateLoop);
    m_pStateMachine->addState(m_pStateRandom);
    m_pStateMachine->addState(m_pStateCurrentItemInLoop);
    m_pStateMachine->setInitialState(m_pStateSequential);

    connect(m_pStateSequential, SIGNAL(entered()), this, SLOT(changeMode2Sequential()));
    connect(m_pStateLoop, SIGNAL(entered()), this, SLOT(changeMode2Loop()));
    connect(m_pStateRandom, SIGNAL(entered()), this, SLOT(changeMode2Random()));
    connect(m_pStateCurrentItemInLoop, SIGNAL(entered()), this, SLOT(changeMode2CurrentItemInLoop()));

    m_pStateMachine->start();
    qDebug() << "模式按钮初始化";
}

PlayModeButton::~PlayModeButton(){
    delete m_pStateSequential;
    delete m_pStateLoop;
    delete m_pStateRandom;
    delete m_pStateCurrentItemInLoop;
    delete m_pStateMachine;
    delete m_pPushBotton;
}

void PlayModeButton::changeMode2Sequential(){
    m_pPushBotton->setIcon(QIcon(":/images/sequential.svg"));
    m_pPushBotton->setIconSize(QSize(m_width, m_height));
    qDebug() << "Play in order";
    m_currentState = Sequential;
    emit MachineStateChanged();
}

void PlayModeButton::changeMode2Loop(){
    m_pPushBotton->setIcon(QIcon(":/images/loop.svg"));
    m_pPushBotton->setIconSize(QSize(m_width, m_height));
    qDebug() << "Play repeat in list";
    m_currentState = Loop;
    emit MachineStateChanged();
}

void PlayModeButton::changeMode2Random(){
    m_pPushBotton->setIcon(QIcon(":/images/random.svg"));
    m_pPushBotton->setIconSize(QSize(m_width, m_height));
    qDebug() << "Play in random";
    m_currentState = Random;
    emit MachineStateChanged();
}

void PlayModeButton::changeMode2CurrentItemInLoop(){
    m_pPushBotton->setIcon(QIcon(":/images/repeat.svg"));
    m_pPushBotton->setIconSize(QSize(m_width, m_height));
    qDebug() << "Play in repeat";
    m_currentState = CurrentItemInLoop;
    emit MachineStateChanged();
}

PlayModeButton::MODE_STATE PlayModeButton::currentState(){
    return m_currentState;
}

void PlayModeButton::setIconSize(const QSize& qsize){
    m_pPushBotton->setIconSize(qsize);
}

void PlayModeButton::setText(const QString& text){
    m_pPushBotton->setText(text);
}

void PlayModeButton::setIcon(const QIcon& icon){
    m_pPushBotton->setIcon(icon);
}


void PlayModeButton::setFixedSize(const QSize & qsize){
    m_width = qsize.width();
    m_height = qsize.height();
    m_pPushBotton->setFixedSize(qsize);
}

void PlayModeButton::setStyleSheet(const QString& styleSheet){
    m_pPushBotton->setStyleSheet(styleSheet);
}








