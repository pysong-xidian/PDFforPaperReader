﻿#ifndef PAPERVIEWS_H
#define PAPERVIEWS_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <poppler-qt5.h>
#include <QPainter>
#include <QFrame>
#include <QLayout>
#include <QGraphicsView>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QPicture>
#include <QWheelEvent>
#include <QtMath>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QStackedWidget>
#include <paperannotation.h>
#include <QAction>
#include <QCursor>

class MainFrame;

class PaperItem : public QGraphicsItem
{
public:
    PaperItem(int index, QImage *image) {this->index=index; this->image = image; setZValue(-10);}
    ~PaperItem() override;
    QImage *image;
    int index;
    virtual QRectF boundingRect()const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class MainScene : public QGraphicsScene
{
    Q_OBJECT
    friend class MainFrame;
    friend class GraphicsView;
public:
    MainScene();
    void loadFile(const QString &addr);
    void refreshView(qreal scale);
    void drawAnnotations();
    QList<PaperAnnotation::Annotation *> annotations;
    QTimer *refreshtimer;
    void updateSize();
    int xres;
    int yres;
    double width;
    double height;
    double scale = 1;
    bool isDrawing = false;
    bool isPressing = false;
    int shape = 0;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void changeIsDrawing(const QString &text, bool isDrawing);
    void setCurrentShape(int i);
    QGraphicsLineItem *tmplineitem;
    QGraphicsEllipseItem *tmpellipseitem;
    QGraphicsRectItem *tmprectitem;
    QGraphicsTextItem *tmptextitem;
    QPointF startPoint, endPoint;
    void newFlatText(const QString &text, QFont font, QColor color);

private:
    Poppler::Document *document;
    //PaperWidgets *paperwidgets;
    QList<PaperItem *> pages;
    QGraphicsProxyWidget *paperproxywidget;

signals:
    void is_drawing(bool flag);
};

class SideScene : public QGraphicsScene
{
public:
    SideScene();
};

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(MainFrame *frame);
    void setScene(MainScene *scene);
    QTimer *refreshtimer;
    void updateSize();
    MainScene *mainscene;

protected:
    virtual void wheelEvent(QWheelEvent *ev) override; 

private:
    MainFrame *frame;
    qreal scalefactor = 1; 
    QPointF point;


signals:
    void sizeChanged(qreal deltascale, qreal rotate);
};

class MainFrame : public QFrame
{
public:
    MainFrame();
    GraphicsView *view() const;
    void zoom();

private:
    double scale = 1;
    GraphicsView *graphicsview;
};

#endif // PAPERVIEWS_H
