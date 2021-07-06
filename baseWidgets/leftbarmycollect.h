#ifndef LEFTBARMYCOLLECT_H
#define LEFTBARMYCOLLECT_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QContextMenuEvent>
#include <QMenu>
#include <QVector>

class LeftBarMyCollec : public QWidget
{
    Q_OBJECT
public:
    explicit LeftBarMyCollec(QWidget *parent = nullptr);
    ~LeftBarMyCollec();

    void updateLeftBar();
    void setGeometry(int ax, int ay, int aw, int ah);
    void setListStyleSheet(const QString& styleSheet);
    void setListItemSize(int w, int h);
    void addFavorite(const QString& label);
    void addColumnTitle(const QString& title);
    void setRightClickEnabled();

signals:

public slots:
    void ListWidgetItemIsLeftClicked(QListWidgetItem* item);
    void ListWidgetIsRightClicked(const QPoint & pos);

    void playAllSongsInList();
    void playAtNextTime();
    void shareLink();
    void copyLink();
    void downloadAllSongsInList();
    void deleteCurrentSongList();

private:
    QListWidget* m_pListWidget;
    QMenu* m_pMenu;
    QVector<QAction*> m_vActions;

    void initMenu();
    void ListWidgetItemIsRightClicked(const QPoint & pos);
    void ListWidgetSpaceIsRightClicked(const QPoint & pos);

};
#endif // LEFTBARMYCOLLECT_H
