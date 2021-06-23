#include "submainwindow.h"

submainwindow::submainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* 设置标题栏 */
    this->setWindowTitle("myNotePad");
    this->setWindowIcon(QIcon(":/icon/edit_1.png"));

    /* 设置菜单栏 */
    QMenuBar *mbar = menuBar(); //获取QMenuBar对象
    QMenu *file = new QMenu("文件");
    QMenu *edit = new QMenu("编辑");
    QMenu *save = new QMenu("保存");
    QMenu *saveas = new QMenu("另存为");
    QMenu *font = new QMenu("字体");
    QMenu *color = new QMenu("颜色");
    QMenu *copy = new QMenu("复制");
    QMenu *paste = new QMenu("粘贴");
    QMenu *find = new QMenu("查找");

    QAction *file_new = new QAction(QIcon(":/icon/add.png"),"新建文件");
    QAction *file_open = new QAction(QIcon(":/icon/edit_1.png"),"打开文件");
    QAction *file_save = new QAction(QIcon(":/icon/save.png"),"保存文件");
    QAction *file_saveas = new QAction(QIcon(":/icon/saveas.png"),"另存为");
    QAction *file_font = new QAction(QIcon(":/icon/font.png"),"设置字体");
    QAction *file_color = new QAction(QIcon(":/icon/color.png"),"设置颜色");
    QAction *file_copy = new QAction(QIcon(":/icon/copy.png"),"复制");
    QAction *file_paste = new QAction(QIcon(":/icon/paste.png"),"粘贴");
    QAction *file_find = new QAction(QIcon(":/icon/find.png"),"查找");

    mbar->addMenu(file);        //向QMenuBar添加menu
    mbar->addMenu(edit);
    mbar->addMenu(save);
    mbar->addMenu(saveas);
    mbar->addMenu(font);
    mbar->addMenu(color);
    mbar->addMenu(copy);
    mbar->addMenu(paste);
    mbar->addMenu(find);

    file->addAction(file_new);  //向QMenu添加action
    file->addAction(file_open);
    file->addAction(file_save);
    file->addAction(file_saveas);
    file->addAction(file_copy);
    file->addAction(file_paste);
    file->addAction(file_find);

    font->addAction(file_font);
    color->addAction(file_color);

    /* 设置工具栏 */
    QToolBar *tb = addToolBar("工具"); //获取QToolBar对象
    tb->addAction(file_new);
    tb->addAction(file_open);
    tb->addAction(file_save);
    tb->addAction(file_saveas);
    tb->addAction(file_font);
    tb->addAction(file_color);
    tb->addAction(file_copy);
    tb->addAction(file_paste);
    tb->addAction(file_find);

    /* 设置中央窗口 */
    te = new QTextEdit;
    this->setCentralWidget(te);

  //  tab = new QTabWidget;
  //  this->setCentralWidget(tab);

   // QTextEdit *te = new QTextEdit;
   // tab->addTab(te,"new.txt");

    /* 设置状态栏 */
    QStatusBar *stbar = statusBar(); //获取QStatusBar对象
    QLabel *lab = new QLabel("11:22");

    stbar->addWidget(lab);  //把标签放入状态栏
    this->setMinimumSize(400,300);      //最小大小
    this->resize(800,600);              //默认大小

    /* 连接action与槽函数 */
   // connect(file_open,SIGNAL(triggered(bool)),this,SLOT(FileOpen()));
    connect(file_new,SIGNAL(triggered(bool)),this,SLOT(FileNew()));
    connect(file_open,SIGNAL(triggered(bool)),this,SLOT(FileOpen()));
    connect(file_save,SIGNAL(triggered(bool)),this,SLOT(FileSave()));
    connect(file_saveas,SIGNAL(triggered(bool)),this,SLOT(FileSaveas()));
    connect(file_font,SIGNAL(triggered(bool)),this,SLOT(FileFont()));
    connect(file_color,SIGNAL(triggered(bool)),this,SLOT(FileColor()));
    connect(file_copy,SIGNAL(triggered(bool)),this,SLOT(FileCopy()));
    connect(file_paste,SIGNAL(triggered(bool)),this,SLOT(FilePaste()));
    connect(file_find,SIGNAL(triggered(bool)),this,SLOT(FileFind()));
}



void submainwindow::FileNew()
{
    qDebug()<<"new";

  //  QTextEdit *new_te = new QTextEdit;
 //   tab->addTab(new_te,"new.txt");

}

void submainwindow::FileOpen()                 //打开文件
{
    qDebug()<<"open ";
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::currentPath()); //获取路径
    qDebug()<<fileName;
    QFile *file=new QFile;
    file->setFileName(fileName);
    bool ok = file->open(QIODevice::ReadOnly);      //只读打开
    if(ok)
    {
          QTextStream in(file);
          te->setText(in.readAll());
          file->close();
          delete file;
    }
}

void submainwindow::FileSave()                 //保存文件
{
    qDebug()<<"save ";
    QFile *file = new QFile;
    file->setFileName(fileName);
    bool ok = file->open(QIODevice::WriteOnly);     //只写打开
    if(ok)
    {
        //QTextStream out(file);
        QString demo = te->toPlainText();//这里是取出textEdit当中的纯文本
        qDebug()<<demo;
        QTextStream writefiletext(file); //写入文件路径
        writefiletext<<demo;             //写入内容
        file->close();
        delete file;
    }
}


void submainwindow::FileSaveas()               //另存为
{
    qDebug()<<"saveas ";
    QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath()); //获取路径
    QFile *file = new QFile;
    file->setFileName(fileName);
    bool ok = file->open(QIODevice::WriteOnly);     //只写打开
    if(ok)
    {
        //QTextStream out(file);
        QString demo = te->toPlainText();//这里是取出textEdit当中的纯文本
        qDebug()<<demo;
        QTextStream writefiletext(file); //写入文件路径
        writefiletext<<demo;             //写入内容
        file->close();
        delete file;
    }
}


void submainwindow::FileFont()
{
    qDebug()<<"font ";
    //弹出字体对话框
    bool ok;
    QFont font =  QFontDialog::getFont(&ok);

    if(ok == true)
    {
        qDebug()<<"获取字体成功:"<<font;
        te->setFont(font);
    }
    else
    {
        qDebug()<<"失败";
    }
}

void submainwindow::FileColor()
{
    qDebug()<<"color ";
    QColor col = QColorDialog::getColor();
    qDebug()<<col;
    te->setTextColor(col);
}

void submainwindow::FileCopy()
{
    qDebug()<<"copy";
    te->copy();				//拷贝
}

void submainwindow::FilePaste()
{
    qDebug()<<"paste";
    te->paste();			//粘贴
}

void submainwindow::FileFind()
{
    qDebug()<<"paste";
    bool ok;
    QString name = QInputDialog::getText(this, tr("查找"),
                                         tr("name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
   qDebug()<<name;
   int sum = 0;
   bool temp = true;
   if(name != "")                   //判断输入是否为空
   {
       while(temp)                  //循环查找
       {
           int food = te->find(name);	//查找
           qDebug()<<"food = "<<food;
           if(food == 1)
           {
               sum++;               //数量++
           }
           if(food == 0)
           {
               temp = false;
           }
           if(food == 0 && sum == 0)
           {
               QMessageBox::warning(this,"查找",tr("找不到%1").arg(name));
           }
       }
   }
   qDebug()<<"sum = "<<sum;

   //光标移动到文末：
   //myTextEdit ->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}



submainwindow::~submainwindow()
{

}
