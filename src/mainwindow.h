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
    void on_notesButton_clicked(QPushButton* inspirationButton, QPushButton* goalsButton, QPushButton *notesButton, QWidget *centralWidget, QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QWidget *mainWidget,QLabel *helloLabel,QGridLayout *gridLayout,AspectRatioWidget *aspectRatioWidget);
    void resetWindow(QPushButton* inspirationButton, QPushButton* goalsButton, QPushButton *notesButton, QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QLabel *helloLabel, QGridLayout *gridLayout, AspectRatioWidget *aspectRatioWidget);
    void on_inspirationButton_clicked(QPushButton* inspirationButton, QPushButton* goalsButton,QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget);
    void on_GoalsButton_clicked(QPushButton* inspirationButton,QPushButton* goalsButton,QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget);
    void addSubgoal(int subgoalIndex,int goalCounter,QString folderName,QVBoxLayout* subgoalsContainerLayout, QWidget* goalsWidget,QString subgoalGivenTitle, bool subgoalMarked);
    void loadGoals(QPushButton* addGoalButton);
    void on_habitsButton_clicked(QPushButton* inspirationButton, QPushButton* goalsButton, QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget);
    void addHabit(QList<QWidget*> &upComingList, QWidget* habitsWidget,QVBoxLayout* habitsLayout, int habitIndex, QString habitTitle, QString repetition, QString times);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
