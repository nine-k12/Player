#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>

class LeftBarMyMusic : public QWidget
{
    Q_OBJECT
public:
    explicit LeftBarMyMusic(QWidget *parent = nullptr);
    ~LeftBarMyMusic();

    void updateMyMusicItem();
    void setGeometry(int ax, int ay, int aw, int ah);
    void setListStyleSheet(const QString& styleSheet);
    void setListItemSize(int w, int h);
    void addColumnTitle(const QString& title);

signals:
    void openLocalFolderIsSelected();
    void TableIsSelected(const QString& tableName);

public slots:
    void ListWidgetItemIsLeftClicked(QListWidgetItem* item);

private:
    QListWidget* m_pListWidget;
    QMenu* m_pMenu;

    void initMenu();

};

#endif // LEFTBAR_H
