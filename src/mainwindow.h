#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <aspectratiowidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_notesButton_clicked(QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QWidget *mainWidget,QLabel *helloLabel,QGridLayout *gridLayout,AspectRatioWidget *aspectRatioWidget);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
