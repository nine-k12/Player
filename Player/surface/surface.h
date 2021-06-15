#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QLabel>
#include <QPaintEvent>
#include <QVideoWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QHash>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVector>

#include "mydatabasemodule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();

private slots:
    void on_pushButtonUp_clicked();

    void on_pushButtonDown_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonLyric_clicked();

    void on_pushButtonSound_clicked();

    void on_horizontalSliderSound_sliderMoved(int position);

    void on_horizontalSliderTimer_sliderMoved(int position);

    void on_lineEditSearch_editingFinished();

    void on_pushButtonSongCover_clicked();

    void on_pushButtonUser_clicked();

    void on_pushButtonSetting_clicked();

    void on_pushButtonPlayMode_MachineStateChanged();

    void on_pushButtonFiles_clicked();

    void on_horizontalSliderTimer_sliderReleased();

    void on_horizontalSliderTimer_sliderPressed();

    void OpenFiles();

    void updateTimeSlider();

    void showDataFromTable(const QString&);

    void playCurrentSong(int row, int col);

    void replyFinished(QNetworkReply *);

    void on_pushButtonExit_clicked();

    void on_pushButtonBack_clicked();

    void on_pushButtonForward_clicked();

    void RequireAudioSource(int, int);

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::Widget *ui;
    QMediaPlayer *m_pMediaPlayer;
    QMediaPlaylist *m_pMediaPlayList;
    QVideoWidget *m_pVideoWidget;
    QVBoxLayout *m_pVideoLayout;
    QTimer *m_pTimer;
    QListWidget* m_pListWidget;
    QString m_sCurrentPlayTableName;

    MyDataBaseModule* m_pDataBase;

    QNetworkAccessManager* m_pNetworkAccessManager;
    QNetworkReply* m_pReply;
    QNetworkRequest* m_pRequest;

    QVector<QString> m_vSongName;
    QVector<QString> m_vSingerName;
    QVector<QString> m_vFileHash;
    QVector<QString> m_vAlbumID;

    void parseJson(const QString& json);
    void showSearchResultInTable();
    void createSearchTableWidget();
    QVector<QString> parseJsonSongInfo(const QString& json);
    void replyFinishedForSongList(QNetworkReply *reply);
    void replyFinishedForOneSong(QNetworkReply *reply);
    enum SEARCH_STAGE {IDLE, SEARCH_SONGLIST, SEARCH_ONE_SONG};
    SEARCH_STAGE m_bCurrentSearchStage;
    QVector<QString> m_tNetSongRecord;
    void add2RecentAndPlay();

    QString DEFAULT_FILE_PATH;
    QString DEFAULT_USER_NAME;
    QString DEFAULT_PASSWD;
    QString m_sUserName;
    QString m_sPasswd;

    QHash<QString, QTableWidget*> m_hashTableWidgets;

    bool m_bIsPlaying;
    bool m_bIsShowLyric;
    bool m_bIsSoundSetZero;
    bool m_bIsRadio;
    bool m_bIsVideo;
    bool m_bIsSetTotalTime;

    int M_INIT_VOLUMN;
    int m_Volumn;
    int M_INIT_DURATION;
    int M_TIMER_TIMEOUT;

    void initMediaPlayList();
    void updateTotalDuration();
    void initDataBaseForCurrentUser();
    void reloadPlayList(const QString& tableName);
    void updateMediaInfo(const QString& songName, const QString& author, const QString& cover);
    void ShowPlayList();
    void updateListViewContent(const QString& tableName);
    QString ms2minute(qint64 ms);
};

#endif // WIDGET_H
