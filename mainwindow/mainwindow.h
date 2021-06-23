#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QTabWidget>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDateTime>
#include <QTextCodec>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void timerEvent(QTimerEvent *event);        //时间事件 刷新时间

private slots:
    void FileNew();
    void FileOpen();
    void FileSave();
    void FileSaveas();
    void FileFont();
    void FileColor();
    void FileCopy();
    void FilePaste();
    void FileFind();

private:
    QTabWidget *tab;
    QTextEdit *te;
    QString fileName;       //文件路径
    int paint_timer;        //开启界面刷新timer
    int x;                  //横坐标
    int y;                  //纵坐标
    QDateTime current_date_time;    //时间
    QString current_date;           //时间字符串
    QStatusBar *stbar;  //状态栏
    QLabel *lab;        //标签
};

#endif // MAINWINDOW_H
