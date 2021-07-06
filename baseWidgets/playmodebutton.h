#ifndef PLAYMODEBUTTON_H
#define PLAYMODEBUTTON_H

#include <QWidget>
#include <QStateMachine>
#include <QPushButton>

class PlayModeButton : public QWidget
{
    Q_OBJECT
public:
    explicit PlayModeButton(QWidget *parent = nullptr);
    ~PlayModeButton();

    void setIconSize(const QSize& qsize);
    void setText(const QString& text);
    void setIcon(const QIcon& icon);
    void setFixedSize(const QSize & qsize);
    void setStyleSheet(const QString& styleSheet);
    enum MODE_STATE{Sequential, Loop, Random, CurrentItemInLoop};
    MODE_STATE currentState();

signals:
    void MachineStateChanged();

private slots:
    void changeMode2Sequential();
    void changeMode2Loop();
    void changeMode2Random();
    void changeMode2CurrentItemInLoop();

private:
    QStateMachine* m_pStateMachine;
    QState* m_pStateSequential;
    QState* m_pStateLoop;
    QState* m_pStateRandom;
    QState* m_pStateCurrentItemInLoop;
    QPushButton* m_pPushBotton;

    int m_width;
    int m_height;
    MODE_STATE m_currentState;

};

#endif // PLAYMODEBUTTON_H
