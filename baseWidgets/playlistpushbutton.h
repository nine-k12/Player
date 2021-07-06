#ifndef PLAYLISTPUSHBUTTON_H
#define PLAYLISTPUSHBUTTON_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QVector>

class PlayListPushButton : public QWidget
{
    Q_OBJECT
public:
    explicit PlayListPushButton(QWidget *parent = nullptr);
    ~PlayListPushButton();
    enum LIST_STATE{CLOSED, OPEN};

signals:
    void clicked();

public slots:
    void showList();
    void closeList();
    void updateList();
    void  stateChanged();
    void setIconSize(const QSize& qsize);
    void setText(const QString& text);
    void setIcon(const QIcon& icon);
    void setFixedSize(const QSize & qsize);
    void setPushButtonStyleSheet(const QString& styleSheet);
    void setListStyleSheet(const QString& styleSheet);
    void setAutoRepeatInterval(int val);
    void setPushButtonGeometry(int ax, int ay, int aw, int ah);
    void setListGeometry(int ax, int ay, int aw, int ah);

private:
    QPushButton* m_pPushButton;
    QListWidget* m_pListWidget;
    QVector<QListWidgetItem*> m_vListItems;

    LIST_STATE currentState;
};

#endif // PLAYLISTPUSHBUTTON_H
