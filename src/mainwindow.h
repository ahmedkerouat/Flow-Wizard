#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
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
    void on_notesButton_clicked(QPushButton* inspirationButton,QPushButton *notesButton, QWidget *centralWidget, QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QWidget *mainWidget,QLabel *helloLabel,QGridLayout *gridLayout,AspectRatioWidget *aspectRatioWidget);
    void resetWindow(QPushButton* inspirationButton,QPushButton *notesButton, QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QLabel *helloLabel, QGridLayout *gridLayout, AspectRatioWidget *aspectRatioWidget);
    void on_inspirationButton_clicked(QPushButton* inspirationButton,QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget);
    void on_GoalsButton_clicked(QPushButton* inspirationButton,QPushButton* goalsButton,QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget);
    void addSubgoal(int subgoalIndex,int goalCounter,QString folderName,QVBoxLayout* subgoalsContainerLayout, QWidget* goalsWidget,QString subgoalGivenTitle, bool subgoalMarked);
    void loadGoals(QPushButton* addGoalButton);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
