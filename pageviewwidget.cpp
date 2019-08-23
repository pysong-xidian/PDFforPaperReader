#include "pageviewwidget.h"

PageViewWidget::PageViewWidget(QString filename, QWidget *parent) : QWidget(parent)
{

    setWindowTitle(tr("Bamboo PDF阅读器"));

    mainscene = new MainScene();

    leftscene = new SideScene();
    rightscene = new SideScene();
    leftSpliter = new QSplitter();
    rightSpliter = new QSplitter();
    centerSpliter = new QSplitter();
    totalSpliter = new QSplitter(Qt::Horizontal);
    leftSpliter->setFixedWidth(20);
    rightSpliter->setFixedWidth(20);
    MainFrame *mainframe = new MainFrame();
    mainframe->view()->setScene(mainscene);
    centerSpliter->addWidget(mainframe);
    totalSpliter->addWidget(leftSpliter);
    totalSpliter->addWidget(centerSpliter);
    totalSpliter->addWidget(rightSpliter);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(totalSpliter);
    this->setLayout(layout);

    mainscene->loadFile(filename);

    connect(mainframe->view()->refreshtimer, &QTimer::timeout, mainframe->view(), &GraphicsView::updateSize);
}
