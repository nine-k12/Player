#ifndef MUSICSEARCH_H
#define MUSICSEARCH_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class MusicSearch : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSearch(QWidget *parent = nullptr);

signals:

};

#endif // MUSICSEARCH_H
