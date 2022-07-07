#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "poopchar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<PoopChar*> text;
    QList<QTextEdit*> previewList;

public slots:
    void addChar();
    void updateText();
    void deleteLast();
    void clear();
};
#endif // MAINWINDOW_H
