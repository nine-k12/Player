#include "surface.h"
#include "ui_surface.h"

#include <QDebug>
#include <QCommandLinkButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QVideoWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QDateTime>
#include <QMessageBox>
#include <QStringList>
#include <QTableWidgetItem>
#include <QTableView>
#include <QHeaderView>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <tuple>

//#include <QMediaContent>

Player::Player(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // initialize object
    //setWindowFlags(Qt::FramelessWindowHint);

    void initWindowBar();

    // initialize states
    m_bIsPlaying = false;
    m_bIsShowLyric = false;
    M_TIMER_TIMEOUT = 1000;

    // database
    DEFAULT_USER_NAME = "root";
    DEFAULT_PASSWD = "111111";
    m_sUserName = DEFAULT_USER_NAME;
    m_sPasswd = DEFAULT_PASSWD;
    m_pDataBase = new MyDataBaseModule;
    m_pDataBase->connect2UserDataBase(m_sUserName, m_sPasswd);
    initDataBaseForCurrentUser();

    // left bar
    ui->listWidgetLeftBarMyMusic->setGeometry(1, 1, 200,200);
    ui->listWidgetLeftBarMyMusic->setStyleSheet(QString("QListWidget{color:rgb(173,175,178); background:rgb(25,27,31);border:0px solid gray;}"
                                                 "QListWidget::Item{height:30px;border:0px solid gray;padding-left:15;}"
                                                 "QListWidget::Item:hover{color:rgb(255,255,255);background:transparent;border:0px solid gray;}"
                                                 "QListWidget::Item:selected{border-image:url(images/listwidget_h.png); color:rgb(255,255,255);border:0px solid gray;}"
                                                 "QListWidget::Item:selected:active{background:#00FFFFFF;color:#FFFFFF;border-width:0;}"));
    ui->listWidgetLeftBarMyMusic->addColumnTitle(QString("ζηι³δΉ"));
    ui->listWidgetLeftBarMyMusic->updateMyMusicItem();

    connect(ui->listWidgetLeftBarMyMusic, SIGNAL(openLocalFolderIsSelected()), this, SLOT(OpenFiles()));
    connect(ui->listWidgetLeftBarMyMusic, SIGNAL(TableIsSelected(const QString&)), this, SLOT(showDataFromTable(const QString&)));

    ui->listWidgetLeftBarCollect->setGeometry(1,201, 200, 400);
    ui->listWidgetLeftBarCollect->addColumnTitle(QString("εε»Ίηζ­ε"));
    ui->listWidgetLeftBarCollect->addFavorite(QString("δΈ­ζ"));

    // song list view


    // Timer Display
    ui->labelCurrentTime->setTextFormat(Qt::AutoText);
    ui->labelCurrentTime->setAlignment(Qt::AlignCenter);
    ui->labelTotalTime->setTextFormat(Qt::AutoText);
    ui->labelTotalTime->setAlignment(Qt::AlignCenter);

    ui->labelCurrentTime->setText(QString("00:00"));
    ui->labelTotalTime->setText(QString("00:00"));

    // Timer slider
    M_INIT_DURATION = 1000;
    m_bIsSetTotalTime = false;
    ui->horizontalSliderTimer->setRange(0, M_INIT_DURATION);
    //ui->horizontalSliderTimer->setValue(500);

    // Search Box display
    ui->lineEditSearch->setGeometry(600, 25,200,50);
    ui->lineEditSearch->setStyleSheet(QString("background: rgb(204,0,0);border-width:0;"
                                              "border-style:outset; color:white;font-family:'εΎ?θ½―ιι»';"));

    // network set
    m_pNetworkAccessManager = new QNetworkAccessManager(this);
    m_pRequest = new QNetworkRequest;
    m_bCurrentSearchStage = IDLE;
    connect(m_pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),
                this,SLOT(replyFinished(QNetworkReply*)));

    createSearchTableWidget();

    // play mode
    //ui->pushButtonPlayMode->setIcon(QIcon(":/images/inorder.svg"));
    //ui->pushButtonPlayMode->setIconSize(QSize(40,40));
    ui->pushButtonPlayMode->setFixedSize(QSize(40,40));
    ui->pushButtonPlayMode->setStyleSheet("background:transparent;");

    // previous next button
    ui->pushButtonUp->setIcon(QIcon(":/images/previous.svg"));
    ui->pushButtonUp->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    // next button
    ui->pushButtonDown->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->pushButtonDown->setIcon(QIcon(":/images/next.svg"));

    // play/stop button
    ui->pushButtonStop->setIcon(QIcon(":/images/stop.svg"));
    ui->pushButtonStop->setStyleSheet(QString("QPushButton{min-width:50px;min-height:50px;"
                                              "max-width:50px;max-height:50px;"
                                              "border-radius:25px;background:grey}"
                                              "QToolTip{border:1px solid rgb(118, 118, 118); "
                                              "background-color: #ffffff; color:#484848; font-size:16px;}"));

    ui->pushButtonStop->setToolTip("ζ­ζΎ");

    // lyric button
    ui->pushButtonLyric->setText("θ―");
    ui->pushButtonLyric->setStyleSheet("background:transparent;border-width:0;border-style:outset;"
                                       "QPushButton{font-family:'ζ₯·δ½';font-size:14px;color:rgb(0,0,0,255);}");

    // list button
    ui->pushButtonFiles->setPushButtonGeometry(153,1,40,40);
    ui->pushButtonFiles->setListGeometry(100, 800, 300,600);
    ui->pushButtonFiles->setIcon(QIcon(":/images/list.svg"));
    ui->pushButtonFiles->setIconSize(QSize(30,30));
    ui->pushButtonFiles->setListStyleSheet(QString("QListWidget{color:rgb(173,175,178); background:rgb(25,27,31);border:0px solid gray;}"
                                                   "QListWidget::Item{height:30px;border:0px solid gray;padding-left:15;}"
                                                   "QListWidget::Item:hover{color:rgb(255,255,255);background:transparent;border:0px solid gray;}"
                                                   "QListWidget::Item:selected{border-image:url(images/listwidget_h.png); color:rgb(255,255,255);border:0px solid gray;}"
                                                   "QListWidget::Item:selected:active{background:#00FFFFFF;color:#FFFFFF;border-width:0;}"));

    // sound button
    ui->pushButtonSound->setIcon(QIcon(":/images/sound.svg"));
    ui->pushButtonSound->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->pushButtonSound->setIconSize(QSize(40,40));

    // sound
    M_INIT_VOLUMN = 20;
    m_bIsSoundSetZero = false;
    m_Volumn = M_INIT_VOLUMN;
    //ui->horizontalSliderSound->setFixedSize(QSize(100, 40));
    ui->horizontalSliderSound->setRange(0,100);
    ui->horizontalSliderSound->setTickInterval(1);
    ui->horizontalSliderSound->setValue(M_INIT_VOLUMN);

    // song
    ui->labelSongName->setAlignment(Qt::AlignLeft);
    ui->labelSongName->setText(QString("ζ ζ­£ζ­ζΎζ­ζ²"));
    ui->labelSongName->setFont(QFont("ι»δ½",9,QFont::Normal));
    ui->labelSongName->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    ui->labelSingerName->setAlignment(Qt::AlignLeft);
    ui->labelSingerName->setText(QString("ζͺη₯ε"));
    ui->labelSongName->setFont(QFont("η­ηΊΏ",6,QFont::Normal));
    ui->labelSingerName->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    QPixmap pixmap_cover(":/images/startcover.png");
    ui->pushButtonSongCover->setIcon(QIcon(":/images/startcover.png"));
    //ui->pushButtonDown->setIconSize(QSize(80,80));

    // forward
    ui->pushButtonForward->setIcon(QIcon(":/images/forward.svg"));
    ui->pushButtonForward->setIconSize(QSize(40,40));
    ui->pushButtonForward->setStyleSheet(QString("background: rgb(204,0,0);border-width:0;"
                                                 "border-style:outset;boarder-radius:20;"));


    // back
    ui->pushButtonBack->setIcon(QIcon(":/images/back.svg"));
    ui->pushButtonBack->setIconSize(QSize(40,40));
    ui->pushButtonBack->setStyleSheet(QString("background: rgb(204,0,0);border-width:0;"
                                                 "border-style:outset;"));

    // scale
    ui->pushButtonScale->setIcon(QIcon(":/images/minimize.svg"));
    ui->pushButtonScale->setIconSize(QSize(40,40));
    ui->pushButtonScale->setStyleSheet(QString("background: transparent;border-width:0;"
                                                 "border-style:outset;"));

    // enlarge
    ui->pushButtonEnlarge->setIcon(QIcon(":/images/maximize.svg"));
    ui->pushButtonEnlarge->setIconSize(QSize(40,40));
    ui->pushButtonEnlarge->setStyleSheet(QString("background: transparent;border-width:0;"
                                                 "border-style:outset;border-radius:20;"));

    // exit
    ui->pushButtonExit->setIcon(QIcon(":/images/exit.svg"));
    ui->pushButtonExit->setIconSize(QSize(30,30));
    ui->pushButtonExit->setStyleSheet(QString("background: transparent;border-width:0;"
                                                 "border-style:outset;"));

    // user
    ui->pushButtonUser->setIcon(QIcon(":/images/user.svg"));
    ui->pushButtonUser->setIconSize(QSize(50,50));

    // setting
    ui->pushButtonSetting->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->pushButtonSetting->setIcon(QIcon(":/images/setting.svg"));
    ui->pushButtonSetting->setIconSize(QSize(40,40));

    // radio or video
    m_bIsRadio = false;
    m_bIsVideo = false;
    m_pMediaPlayer = nullptr;
    m_pVideoWidget = nullptr;
    m_pTimer = nullptr;

    // play list
    m_pMediaPlayList = nullptr;
    DEFAULT_FILE_PATH = "C:/Users/28056/Music";
    m_sCurrentPlayTableName = "";
    initMediaPlayList();
}

Player::~Player()
{
    delete m_pMediaPlayList;
    delete m_pTimer;
    delete m_pVideoLayout;
    delete m_pVideoWidget;
    delete ui;
}

void Player::initDataBaseForCurrentUser(){
    m_pDataBase->createTable(QString("DownLoadManager"));
    m_pDataBase->createTable(QString("RecentPlay"));
    m_pDataBase->createTable(QString("MyFavoriteMusic"));
    m_pDataBase->createTable(QString("NetSearch"));
}

void Player::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QBrush brush(QColor(236,65,65),Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0, 0, 1080, 100);
    brush.setColor(QColor(255,255,255));
    painter.setBrush(brush);
    painter.drawRect(0, 700, 1080,100);

    brush.setColor(QColor(204,0,0));
    painter.setBrush(brush);
    QRectF rectangule(380.0, 22.0,275.0,50.0);
    painter.drawRoundedRect(rectangule, 25.0, 25.0);
    painter.drawPixmap(380, 22, 50,50, QPixmap(":/images/search.svg"));
}

void Player::initMediaPlayList(){
    if(DEFAULT_FILE_PATH.isEmpty())
        return;

    // collect .mp3,.mp4 files
    QDir* m_pDir = new QDir(DEFAULT_FILE_PATH);
    if(!m_pDir->exists()){
        qDebug() << "θ·―εΎδΈε­ε¨";
        return;
    }
    m_pDir->setFilter(QDir::Files);
    //QStringList filter;
    //filter << "*.mp3";
    //filter << "*.mp4";

    m_pMediaPlayer = new QMediaPlayer;
    m_pMediaPlayList = new QMediaPlaylist;
    m_pMediaPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
    m_pMediaPlayer->setPlaylist(m_pMediaPlayList);

   /*for(int i=0; i<m_pFileInfo->count(); i++){
        QFileInfo aFile = m_pFileInfo->at(i);
        qDebug() << aFile.filePath();
        m_pMediaPlayList->addMedia(QUrl::fromLocalFile(aFile.filePath()));
    }
    if(m_pMediaPlayer->state() != QMediaPlayer::PlayingState){
        qDebug() << "index 0 is ready for playing";
        m_pMediaPlayList->setCurrentIndex(0);
    }*/

    m_pTimer = new QTimer();
    m_pTimer->setInterval(M_TIMER_TIMEOUT);

    m_pVideoLayout = new QVBoxLayout;
    m_pVideoWidget = new QVideoWidget;
    m_pVideoWidget->resize(ui->textBrowserScreen->size());
    m_pVideoLayout->addWidget(m_pVideoWidget);
    ui->textBrowserScreen->setLayout(m_pVideoLayout);
    m_pMediaPlayer->setVideoOutput(m_pVideoWidget);

    m_pMediaPlayer->setVolume(m_Volumn);
    reloadPlayList("RecentPlay");

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(updateTimeSlider()));
    //connect(ui->horizontalSliderTimer, SIGNAL(sliderReleased()), m_pMediaPlayer, SLOT(setPosition(qint64)));
}

void Player::reloadPlayList(const QString& tableName){
    if(m_pDataBase->isTableExist(tableName)){
        QVector<std::tuple<QString,QString,QString,QString>> records = m_pDataBase->fetchRecords(tableName);

        for(const std::tuple<QString,QString,QString,QString>& record: records){
            qDebug() << std::get<0>(record) << std::get<1>(record) << std::get<2>(record), std::get<3>(record);
            m_pMediaPlayList->addMedia(QUrl::fromLocalFile(std::get<2>(record)));
        }

        m_pMediaPlayList->setCurrentIndex(0);
        qDebug() << "reload ζ­ζΎεθ‘¨ζε";
    }
    else
        qDebug() << "θ‘¨δΈε­ε¨οΌζ ζ³reloadζ­ζΎεθ‘¨";
}

QString Player::ms2minute(qint64 ms){
    int second = ms / 1000;
    int hour = second / 3600;
    second -= hour*3600;
    int minute = second / 60;
    second -= 60*minute;

    QString curtime;
    if(hour == 0)
        curtime = curtime.sprintf("%02d:%02d", minute, second);
    else
        curtime = curtime.sprintf("%02d:%02d:%02d", hour, minute, second);
    return curtime;
}

void Player::updateTimeSlider(){
    qint64 curposition = m_pMediaPlayer->position();
    int val = curposition*1000/m_pMediaPlayer->duration();
    ui->horizontalSliderTimer->setValue(val);
    QString curtime = ms2minute(curposition);
    ui->labelCurrentTime->setText(curtime);
    if(!m_bIsSetTotalTime){
        m_bIsSetTotalTime = true;
        qint64 duration = m_pMediaPlayer->duration();
        QString totalTime = ms2minute(duration);
        ui->labelTotalTime->setText(totalTime);
    }
}

void Player::updateTotalDuration(){
    qint64 duration = m_pMediaPlayer->duration();
    QString totalTime = ms2minute(duration);
    ui->labelTotalTime->setText(totalTime);
}

void Player::on_pushButtonUp_clicked()
{
    int cur = m_pMediaPlayList->currentIndex();
    if(--cur < 0)
        cur = 0;
    m_pMediaPlayList->setCurrentIndex(cur);
    qDebug() << tr("εζ’δΈδΈι¦");
    m_pTimer->start(M_TIMER_TIMEOUT);
    m_bIsSetTotalTime = false;
    m_pMediaPlayer->play();
}

void Player::on_pushButtonDown_clicked()
{
    int row = m_pMediaPlayList->mediaCount();
    int cur = m_pMediaPlayList->currentIndex();
    if(++cur == row)
        cur = row-1;
    m_pMediaPlayList->setCurrentIndex(cur);
    qDebug() << tr("εζ’δΈδΈι¦");
    m_pTimer->start(M_TIMER_TIMEOUT);
    m_bIsSetTotalTime = false;
    m_pMediaPlayer->play();
}

void Player::on_pushButtonStop_clicked()
{
    qDebug() << "on_pushButtonStop_clicked";
    if(m_pMediaPlayList->isEmpty()){
        QMessageBox::information(NULL, "ζη€Ί", "ε½εζ­ζΎεθ‘¨δΈΊη©Ί");
        return;
    }

    if(m_pMediaPlayer->state() == QMediaPlayer::PlayingState){
        m_pMediaPlayer->pause();
        m_pTimer->stop();
        qDebug() << tr("εζ­’ζ­ζΎ");
        m_bIsPlaying = false;
        ui->pushButtonStop->setIcon(QIcon(":/images/stop.svg"));
    }
    else {
        m_pMediaPlayer->play();
        qDebug() << tr("εΌε§ζ­ζΎ");
        m_pTimer->start();

        m_bIsPlaying = true;
        ui->pushButtonStop->setIcon(QIcon(":/images/start.svg"));
    }
}

void Player::OpenFiles(){
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this,
                                               tr("ζεΌζ­ζΎζδ»Ά"),
                                               "",
                                               "θ§ι’η±»ε (*.mp3 *.mp4);;All files(*)");
    if(filePath.isEmpty())
        return;

    int index = filePath.lastIndexOf("/");
    QString fileName =filePath.right(filePath.length()-index-1) ;
    qDebug() << filePath << fileName;

    QVector<QString> record{fileName, "ζͺη₯δ½θ", filePath, ""};
    m_pTimer->stop();
    if(m_pDataBase->insertRecord("RecentPlay", record)){
        m_pMediaPlayList->addMedia(QUrl::fromLocalFile(filePath));
        int numMedia = m_pMediaPlayList->mediaCount();
        qDebug() << "current media count: " << numMedia;
        m_pMediaPlayList->setCurrentIndex(numMedia-1);
    }
    else{
        qDebug() << "θ―₯ζ²η?ε·²ε­ε¨";
        m_pMediaPlayer->setMedia(QUrl::fromLocalFile(filePath));
    }

    reloadPlayList("RecentPlay");

    m_pMediaPlayer->play();
    m_pTimer->start();
}

void Player::ShowPlayList(){
    m_pListWidget = new QListWidget;
    m_pListWidget->setStyleSheet("QListWidget{color:rgb(173,175,178); background:rgb(25,27,31);border:0px solid gray;}"
                                 "QListWidget::Item{height:30px;border:0px solid gray;padding-left:15;}"
                                 "QListWidget::Item:hover{color:rgb(255,255,255);background:transparent;border:0px solid gray;}"
                                 "QListWidget::Item:selected{border-image:url(images/listwidget_h.png); color:rgb(255,255,255);border:0px solid gray;}"
                                 "QListWidget::Item:selected:active{background:#00FFFFFF;color:#FFFFFF;border-width:0;}");
}

void Player::on_pushButtonFiles_clicked()
{
    qDebug() << tr("ζεΌ/ε³ι­ζ­ζΎεθ‘¨");
}

void Player::on_pushButtonLyric_clicked()
{
    if(m_bIsShowLyric){
        qDebug() << tr("ε³ι­ζ­θ―ζΎη€Ί");
        m_bIsShowLyric = false;
    }
    else{
        qDebug() << tr("ζεΌζ­θ―ζΎη€Ί");
        m_bIsShowLyric = true;
    }
}

void Player::on_pushButtonSound_clicked()
{
    if(m_bIsSoundSetZero){
        qDebug() << tr("ζεΌε£°ι³");
        m_bIsSoundSetZero = false;
        ui->pushButtonSound->setIcon(QIcon(":/images/sound.svg"));
        m_Volumn = M_INIT_VOLUMN;
        ui->horizontalSliderSound->setValue(m_Volumn);

        if(m_pMediaPlayer)
            m_pMediaPlayer->setVolume(m_Volumn);
    }
    else{
        qDebug() << tr("ε³ι­ε£°ι³");
        m_bIsSoundSetZero = true;
        m_Volumn = 0;
        ui->pushButtonSound->setIcon(QIcon(":/images/nosound.svg"));
        ui->horizontalSliderSound->setValue(0);
        if(m_pMediaPlayer)
            m_pMediaPlayer->setVolume(0);
    }
}

void Player::on_horizontalSliderSound_sliderMoved(int position)
{
    if(position > 0 && m_bIsSoundSetZero){
        ui->pushButtonSound->setIcon(QIcon(":/images/sound.svg"));
        m_bIsSoundSetZero = false;
    }
    else if(!position && !m_bIsSoundSetZero){
        ui->pushButtonSound->setIcon(QIcon(":/images/nosound.svg"));
        m_bIsSoundSetZero = true;
    }

    m_Volumn = position;
    m_pMediaPlayer->setVolume(m_Volumn);
    qDebug() << tr("ι³ι%1").arg(position);
}

void Player::on_horizontalSliderTimer_sliderMoved(int position)
{
    if(!m_pMediaPlayer)
        return;
    m_pMediaPlayer->setPosition(position);
}


void Player::on_pushButtonSongCover_clicked()
{
    qDebug() << tr("εζ’ε°θ―¦ζι‘΅ι’");
}

void Player::on_pushButtonUser_clicked()
{
    qDebug() << tr("εζ’ε°η»ε½ζη¨ζ·θ΅ζι‘΅ι’");
}

void Player::on_pushButtonSetting_clicked()
{
    qDebug() << tr("εζ’ε°θ?Ύη½?ι‘΅ι’");
}

void Player::on_pushButtonPlayMode_MachineStateChanged()
{
    if(ui->pushButtonPlayMode->currentState() == PlayModeButton::Sequential){
        m_pMediaPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
        qDebug() << tr("εζ’ε°ι‘ΊεΊζ­ζΎ");
    }
    else if(ui->pushButtonPlayMode->currentState() == PlayModeButton::Loop){
        m_pMediaPlayList->setPlaybackMode(QMediaPlaylist::Loop);
        qDebug() << tr("εζ’ε°εθ‘¨εΎͺη―");
    }
    else if(ui->pushButtonPlayMode->currentState() == PlayModeButton::Random){
        m_pMediaPlayList->setPlaybackMode(QMediaPlaylist::Random);
        qDebug() << tr("εζ’ε°ιζΊζ­ζΎ");
    }
    else if(ui->pushButtonPlayMode->currentState() == PlayModeButton::CurrentItemInLoop){
        m_pMediaPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        qDebug() << tr("εζ’ε°εζ²εΎͺη―");
    }
}


void Player::on_horizontalSliderTimer_sliderReleased()
{
    int val = ui->horizontalSliderTimer->value();
    qint64 pos = val*m_pMediaPlayer->duration()/M_INIT_DURATION;
    qDebug() << "current position " << pos;

    m_pMediaPlayer->setPosition(pos);
    m_pTimer->start();
}

void Player::on_horizontalSliderTimer_sliderPressed()
{
    m_pTimer->stop();
}

void Player::showDataFromTable(const QString& tableName){
    //QString enTableName = chinese2english(tableName);

    auto tableWidget = m_hashTableWidgets.find(tableName);
    if(tableWidget == m_hashTableWidgets.end()){
        qDebug() << "εΈ¦ζΎη€Ίηθ‘¨δΈε­ε¨οΌζ­£ιζ°ζι ";
        updateListViewContent(tableName);
    }

    tableWidget = m_hashTableWidgets.find(tableName);
    if(tableWidget.value()->isHidden()){
        qDebug() << "ζεΌεθ‘¨: " << tableName;
        tableWidget.value()->show();
        m_sCurrentPlayTableName = tableName;
    }
    else{
        qDebug() << "ε³ι­εθ‘¨: " << tableName;
        tableWidget.value()->hide();
        m_sCurrentPlayTableName.clear();
    }
}

void Player::updateListViewContent(const QString& tableName){
    // set format
    QTableWidget* m_pTableWidegt2ShowTable = new QTableWidget(this);
    m_pTableWidegt2ShowTable->hide();
    m_pTableWidegt2ShowTable->setGeometry(200, 101, 880, 599);
    m_pTableWidegt2ShowTable->setAlternatingRowColors(true);
    m_pTableWidegt2ShowTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidegt2ShowTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidegt2ShowTable->setStyleSheet(QString("QTableWidget{background-color: rgb(249,249,249);"
                                                    "alternate-background-color: white;"
                                                    "selection-background-color:rgb(213,213,213);}"));

    m_pTableWidegt2ShowTable->setColumnCount(4);

    m_pTableWidegt2ShowTable->setFrameShape(QFrame::NoFrame);
    m_pTableWidegt2ShowTable->setFrameShadow(QFrame::Plain);
    m_pTableWidegt2ShowTable->setShowGrid(false);
    m_pTableWidegt2ShowTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pTableWidegt2ShowTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_pTableWidegt2ShowTable->hideColumn(2);

    QStringList header;
    header << "ι³δΉζ ι’" << "ζ­ζ" << "SongLink" << "CoverLink";
    m_pTableWidegt2ShowTable->setHorizontalHeaderLabels(header);
    QHeaderView* headerView = m_pTableWidegt2ShowTable->horizontalHeader();
    headerView->resizeSections(QHeaderView::Stretch);
    headerView->setDefaultAlignment(Qt::AlignLeft);


    // insert item
    QVector<std::tuple<QString, QString, QString, QString>> records = m_pDataBase->fetchRecords(tableName);

    int numRows = records.size();
    m_pTableWidegt2ShowTable->setRowCount(numRows);
    for(int i=0; i<numRows; i++){
        m_pTableWidegt2ShowTable->setItem(i, 0, new QTableWidgetItem(std::get<0>(records[i])));
        m_pTableWidegt2ShowTable->setItem(i, 1, new QTableWidgetItem(std::get<1>(records[i])));
        m_pTableWidegt2ShowTable->setItem(i, 2, new QTableWidgetItem(std::get<2>(records[i])));
        m_pTableWidegt2ShowTable->setItem(i, 3, new QTableWidgetItem(std::get<3>(records[i])));
    }

    qDebug() << numRows;
    m_hashTableWidgets[tableName] = m_pTableWidegt2ShowTable;
    m_pTableWidegt2ShowTable = nullptr;
    connect(m_hashTableWidgets[tableName], SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(playCurrentSong(int,int)));
}

void Player::playCurrentSong(int row, int col){
    Q_UNUSED(col);
    qDebug() << "ζ­ζΎε½εεθ‘¨δΈ­ζ­ζ²" << m_sCurrentPlayTableName << row;
    QString link = m_hashTableWidgets[m_sCurrentPlayTableName]->item(row, 2)->text();
    qDebug() << "ζ­ζΎε½εεθ‘¨δΈ­ζ­ζ²" << m_sCurrentPlayTableName << link;
    m_pMediaPlayer->setMedia(QUrl(link));
    m_pMediaPlayer->play();
}

void Player::on_lineEditSearch_editingFinished()
{
    QString searchName = ui->lineEditSearch->text();
    qDebug() << searchName;
    if(searchName.isEmpty())
        return;

    QString url = QString("http://mobilecdn.kugou.com/api/v3/search/song?format=json" "&keyword=%1&page=1&pagesize=18").arg(searchName);
    m_pRequest->setUrl(QUrl(url));
    m_pNetworkAccessManager->get(*m_pRequest);
    m_bCurrentSearchStage = SEARCH_SONGLIST;
}

void Player::replyFinished(QNetworkReply *reply)
{
    if(m_bCurrentSearchStage == SEARCH_SONGLIST)
        replyFinishedForSongList(reply);
    else if(m_bCurrentSearchStage == SEARCH_ONE_SONG){
        replyFinishedForOneSong(reply);
    }
    m_bCurrentSearchStage = IDLE;
}

void Player::replyFinishedForSongList(QNetworkReply *reply)
{
    qDebug() << "εεΊη»ζ";
    //θ·εεεΊηδΏ‘ζ―οΌηΆζη δΈΊ200θ‘¨η€Ίζ­£εΈΈ
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute); //ζ ιθ――θΏε
    qDebug() << status_code;
    if(reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();  //θ·εε­θ
        QString result(bytes);  //θ½¬εδΈΊε­η¬¦δΈ²
        parseJson(result);//θ―₯ε½ζ°η¨δΊθ§£ζapiζ₯ε£θΏεηjson
        showSearchResultInTable();
    }
    else { //ε€ηιθ――
        qDebug()<<"ζη΄’ε€±θ΄₯";
    }
}

void Player::parseJson(const QString& json){
    m_vSongName = {};
    m_vSingerName = {};
    m_vFileHash = {};
    m_vAlbumID = {};

    qDebug() << "In parseJson data size: " << json.size();
        QString songname_original; //ζ­ζ²ε
        QString singername; //ζ­ζ
        QString filehash; //hash
        QString album_name; //δΈθΎ
        QString album_id;
        int duration; //ζΆι΄
        QByteArray byte_array;
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json), &json_error);

        if (json_error.error == QJsonParseError::NoError) {
            if (parse_doucment.isObject()) {
                QJsonObject rootObj = parse_doucment.object();

                // data section
                if (rootObj.contains("data")) {
                    qDebug() << "contains data";
                    QJsonValue valuedata = rootObj.value("data");
                    if (valuedata.isObject()) {
                        QJsonObject valuedataObject = valuedata.toObject();
                        qDebug() << "valuedata isObject";

                        // lists section
                        if (valuedataObject.contains("info")) {
                            qDebug() << "contains lists";
                            QJsonValue valueArray = valuedataObject.value("info");
                            if (valueArray.isArray()) {
                                QJsonArray array = valueArray.toArray();
                                int size = array.size();
                                qDebug() << "array size: " << size;
                                for (int i = 0; i < size; i++) {
                                    QJsonValue value = array.at(i);
                                    if (value.isObject()) {
                                        QJsonObject object = value.toObject();
                                        if (object.contains("songname_original")) {
                                            QJsonValue AlbumID_value = object.take("songname_original");
                                            if (AlbumID_value.isString()) {
                                                //songname_original = AlbumID_value.toString();
                                                m_vSongName.append(AlbumID_value.toString());

                                                //qDebug() << "songname_original: " << songname_original;
                                            }
                                        }
                                        // SingerName
                                        if (object.contains("singername")) {
                                            QJsonValue AlbumID_value = object.take("singername");
                                            if (AlbumID_value.isString()) {
                                                //singername = AlbumID_value.toString();
                                                m_vSingerName.push_back(AlbumID_value.toString());
                                                //qDebug() << "singername: " << singername;
                                            }
                                        }
                                        // AlbumName
                                        if (object.contains("album_name")) {
                                            QJsonValue AlbumID_value = object.take("album_name");
                                            if (AlbumID_value.isString()) {
                                                album_name = AlbumID_value.toString();
                                                qDebug() << "album_name: " << album_name;
                                            }
                                        }
                                        if (object.contains("hash")) {
                                            QJsonValue FileHash_value = object.take("hash");
                                            if (FileHash_value.isString()) {
                                                //filehash = FileHash_value.toString(); //η¨VectorδΏε­ζ―ι¦ζ­ζ²ηhash
                                                m_vFileHash.push_back(FileHash_value.toString());
                                                //qDebug() << "hash: " << filehash;
                                            }
                                        }
                                        if (object.contains("album_id")) {
                                            QJsonValue FileHash_value = object.take("album_id");
                                            if (FileHash_value.isString()) { //η¨VectorδΏε­ζ―ι¦ζ­ζ²ηalbum_id
                                                //album_id = FileHash_value.toString();
                                                m_vAlbumID.push_back(FileHash_value.toString());
                                                //qDebug() << "album_id: " << album_id;
                                            }
                                        }
                                        /*if (object.contains("duration")) {
                                            QJsonValue AlbumID_value = object.take("duration").toInt();
                                            duration = AlbumID_value.toInt();
                                            qDebug() << "duration: " << duration;
                                        }*/
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else {
            qDebug() << json_error.errorString();
        }
        qDebug() << "parse finished" << m_vSongName.size();
}

void Player::showSearchResultInTable(){
    QTableWidget* m_pTableWidegt2ShowTable = m_hashTableWidgets["Search"];

    int numRows = m_vSongName.size();
    qDebug() << numRows;
    m_pTableWidegt2ShowTable->setRowCount(numRows);
    for(int i=0; i<numRows; i++){
        m_pTableWidegt2ShowTable->setItem(i, 0, new QTableWidgetItem(m_vSongName[i]));
        m_pTableWidegt2ShowTable->setItem(i, 1, new QTableWidgetItem(m_vSingerName[i]));
        m_pTableWidegt2ShowTable->setItem(i, 2, new QTableWidgetItem(m_vFileHash[i]));
        m_pTableWidegt2ShowTable->setItem(i, 3, new QTableWidgetItem(m_vAlbumID[i]));
    }
    m_pTableWidegt2ShowTable->show();
    qDebug() << numRows;
    m_sCurrentPlayTableName = "Search";


}

void Player::createSearchTableWidget(){
    QTableWidget* m_pTableWidegt2ShowTable = new QTableWidget(this);
    m_pTableWidegt2ShowTable->hide();
    m_pTableWidegt2ShowTable->setGeometry(200, 101, 880, 599);
    m_pTableWidegt2ShowTable->setAlternatingRowColors(true);
    m_pTableWidegt2ShowTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidegt2ShowTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidegt2ShowTable->setStyleSheet(QString("QTableWidget{background-color: rgb(249,249,249);"
                                                    "alternate-background-color: white;"
                                                    "selection-background-color:rgb(213,213,213);}"));

    m_pTableWidegt2ShowTable->setColumnCount(4);

    m_pTableWidegt2ShowTable->setFrameShape(QFrame::NoFrame);
    m_pTableWidegt2ShowTable->setFrameShadow(QFrame::Plain);
    m_pTableWidegt2ShowTable->setShowGrid(false);
    m_pTableWidegt2ShowTable->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pTableWidegt2ShowTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_pTableWidegt2ShowTable->hideColumn(2);

    QStringList header;
    header << "ι³δΉζ ι’" << "ζ­ζ" << "FileHash" << "AlbumID" << "SongLink" << "CoverLink";
    m_pTableWidegt2ShowTable->setHorizontalHeaderLabels(header);
    QHeaderView* headerView = m_pTableWidegt2ShowTable->horizontalHeader();
    headerView->resizeSections(QHeaderView::Stretch);
    headerView->setDefaultAlignment(Qt::AlignLeft);

    m_hashTableWidgets["Search"] = m_pTableWidegt2ShowTable;
    connect(m_hashTableWidgets["Search"], SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(RequireAudioSource(int,int)));
}


void Player::on_pushButtonExit_clicked()
{
    QApplication* app;
    app->exit(0);
}

void Player::on_pushButtonBack_clicked()
{
    qDebug() << m_sCurrentPlayTableName;
    if(m_sCurrentPlayTableName.isEmpty())
        return;

    QTableWidget* m_pTableWidegt2ShowTable = m_hashTableWidgets[m_sCurrentPlayTableName];
    qDebug() << "ει";
    if(!m_pTableWidegt2ShowTable->isHidden()){
        qDebug() <<"ε³ι­ηͺε£";
        m_pTableWidegt2ShowTable->hide();
    }
    m_sCurrentPlayTableName.clear();
}

void Player::on_pushButtonForward_clicked()
{

}

void Player::RequireAudioSource(int row, int col){
    QString filehash = m_hashTableWidgets[m_sCurrentPlayTableName]->item(row, 2)->text();
    QString albumid = m_hashTableWidgets[m_sCurrentPlayTableName]->item(row, 3)->text();

    //ζ­ζ²θ―·ζ± row ζ―θ‘ε·
    QString url =QString("http://www.kugou.com/yy/index.php?r=play/getdata"
                               "&hash=%1&album_id=%2&_=1497972864535").arg(filehash).arg(albumid);

    m_pRequest->setUrl(QUrl(url)); //θΏε₯θ―εΎιθ¦οΌζδ»¬ζε¨ε€εΆurlζΎε°ζ΅θ§ε¨ε―δ»₯θ·εjsonοΌδ½ζ―ιθΏδ»£η δΈθ‘οΌεΏι‘»ε δΈδΈι’θΏε₯ζε―δ»₯
    m_pRequest->setRawHeader("Cookie","kg_mid=2333");
    m_pRequest->setHeader(QNetworkRequest::CookieHeader, 2333);
    m_pNetworkAccessManager->get(*m_pRequest);
    m_bCurrentSearchStage = SEARCH_ONE_SONG;
}

void Player::replyFinishedForOneSong(QNetworkReply *reply) {
    //θ·εεεΊηδΏ‘ζ―οΌηΆζη δΈΊ200θ‘¨η€Ίζ­£εΈΈ 
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute); 
    //ζ ιθ――θΏε 
    if(reply->error() == QNetworkReply::NoError) { 
        QByteArray bytes = reply->readAll();  //θ·εε­θ
        QString result(bytes);  //θ½¬εδΈΊε­η¬¦δΈ²
        m_tNetSongRecord = parseJsonSongInfo(result); //θ§£ζjson
        add2RecentAndPlay();
    } 
    else { //ε€ηιθ――
        qDebug()<<"ζ­ζ²ζ­ζΎε€±θ΄₯";
    }
}

QVector<QString> Player::parseJsonSongInfo(const QString& json)
{ 
    QString album_name;
    QString author_name;
    QString play_url;//ζ­ζΎε°ε 
    QString lyrics;
    QString img; 

    QByteArray byte_array; 
    QJsonParseError json_error; 
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json), &json_error); 

    if(json_error.error == QJsonParseError::NoError) { 
        if(parse_doucment.isObject()) { 
            QJsonObject rootObj = parse_doucment.object(); 
            if(rootObj.contains("data")) { 
                QJsonValue valuedata = rootObj.value("data"); 

                if(valuedata.isObject()) { 
                    QJsonObject valuedataObject = valuedata.toObject(); 
                    //QString play_urlStr("");

                    if(valuedataObject.contains("audio_name")) {
                        QJsonValue play_name_value = valuedataObject.take("audio_name");
                        if(play_name_value.isString()) {
                        album_name = play_name_value.toString(); //ζ­ζ²εε­
                            if(album_name!="") { //ζΎη€Ί
                                qDebug()<<album_name;
                             }
                         }
                    }

                    if(valuedataObject.contains("author_name")) {
                        QJsonValue play_name_value = valuedataObject.take("author_name");
                        if(play_name_value.isString()) {
                        author_name = play_name_value.toString(); //ζ­ζεε­
                            if(author_name!="") { //ζΎη€Ί
                                qDebug()<<author_name;
                             }
                         }
                    }

                    if(valuedataObject.contains("play_url")) { 
                        QJsonValue play_url_value = valuedataObject.take("play_url"); 
                        if(play_url_value.isString()) { 
                            play_url = play_url_value.toString(); //ζ­ζ²ηurl
                            if(play_url!="") {
                                qDebug()<<play_url;
                            }
                        }
                    }

                    //θ·εζ­θ―
                    if(valuedataObject.contains("lyrics")) {
                        QJsonValue play_name_value = valuedataObject.take("lyrics");
                        if(play_name_value.isString()) {
                        lyrics = play_name_value.toString(); //ζ­ζ²εε­
                            if(lyrics!="") { //ζΎη€Ί
                                qDebug()<<lyrics;
                             }
                         }
                    }

                    //εΎηζΎη€Ί
                    if(valuedataObject.contains("img")) {
                        QJsonValue play_name_value = valuedataObject.take("img");
                        if(play_name_value.isString()) {
                        img = play_name_value.toString(); //ζ­ζ²εε­
                            if(img!="") { //ζΎη€Ί
                                qDebug()<<img;
                             }
                         }
                    }
               }
               else {
                    qDebug()<<"εΊι";
                }
            }
        }
    }
    //qDebug() << album_name  << author_name << play_url << img;
    return {album_name, author_name, play_url,img};
}

void Player::add2RecentAndPlay(){
    if(m_tNetSongRecord.isEmpty()){
        QMessageBox::information(NULL, "ζη€Ί", "θ·εζ­ζ²ε€±θ΄₯");
        return;
    }
    if(m_pDataBase->insertRecord("RecentPlay", m_tNetSongRecord)){
        m_pMediaPlayList->addMedia(QUrl(m_tNetSongRecord[2]));
        int numMedia = m_pMediaPlayList->mediaCount();
        qDebug() << "current media count: " << numMedia;
        m_pMediaPlayList->setCurrentIndex(numMedia-1);
    }
    else{
        qDebug() << "θ―₯ζ²η?ε·²ε­ε¨";
        m_pMediaPlayer->setMedia(QUrl(m_tNetSongRecord[2]));
    }

    reloadPlayList("RecentPlay");
    updateMediaInfo(m_tNetSongRecord[0], m_tNetSongRecord[1], m_tNetSongRecord[3]);

    m_pMediaPlayer->play();
    m_pTimer->start();
}

void Player::updateMediaInfo(const QString& songName, const QString& author, const QString& cover){
    ui->labelSongName->setText(songName);
    ui->labelSingerName->setText(author);
}









