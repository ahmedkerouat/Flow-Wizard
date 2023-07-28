#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include "aspectratiowidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QFileDialog>
#include <QFile>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QShortcut>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //background
    QString styleSheet = "background-color: #071426;";
    this->setStyleSheet(styleSheet);

    //central widget and layout
    QWidget *centralWidget = new QWidget(this);
    this->setMinimumSize(750,600);
    QGridLayout *gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    //main widget added to central widget using AspectRatioWidget
    QWidget *mainWidget = new QWidget(centralWidget);
    mainWidget->setObjectName("mainWidget");
    mainWidget->setStyleSheet("background-color:  #071426");
    AspectRatioWidget *aspectRatioWidget = new AspectRatioWidget(mainWidget, 4, 3, centralWidget);
    gridLayout->addWidget(aspectRatioWidget, 0, 0, 1, 1);

    //"hello" message
    QLabel *helloLabel = new QLabel(mainWidget);
    helloLabel->setText("Hello, User.");
    helloLabel->setAlignment(Qt::AlignHCenter);
    helloLabel->setStyleSheet("font-size: 44px; color: white;");
    gridLayout->addWidget(helloLabel, 0, 0, Qt::AlignTop | Qt::AlignHCenter);

    //create the buttons
    QPushButton *homeButton = new QPushButton(mainWidget);
        homeButton->setIcon(QIcon(":/imgs/logoHome.png"));
        homeButton->setIconSize(QSize(64, 64));
        homeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *goalsButton = new QPushButton(mainWidget);
        goalsButton->setIcon(QIcon(":/imgs/logoGoals.png"));
        goalsButton->setIconSize(QSize(64, 64));
        goalsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *habitsButton = new QPushButton(mainWidget);
        habitsButton->setIcon(QIcon(":/imgs/logoHabits.png"));
        habitsButton->setIconSize(QSize(64, 64));
        habitsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *inspirationButton = new QPushButton(mainWidget);
        inspirationButton->setIcon(QIcon(":/imgs/logoInspiration.png"));
        inspirationButton->setIconSize(QSize(64, 64));
        inspirationButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPushButton *notesButton = new QPushButton(mainWidget);
        notesButton->setIcon(QIcon(":/imgs/logoNotes.png"));
        notesButton->setIconSize(QSize(64, 64));
        notesButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    //create the layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->addWidget(goalsButton);
    buttonLayout->addWidget(habitsButton);
    buttonLayout->addWidget(homeButton);
    buttonLayout->addWidget(inspirationButton);
    buttonLayout->addWidget(notesButton);

    //create a spacer
    QSpacerItem *spacer = new QSpacerItem(40, 200, QSizePolicy::Preferred, QSizePolicy::Minimum);
    mainLayout->addItem(spacer);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addItem(spacer);

    //button style
    QString buttonStyle = "QPushButton {"
                          "border-radius: 32px;"
                          "border: 0px;"
                          "background-color: #071426;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #009ace;"
                          "}";

    homeButton->setStyleSheet(buttonStyle);
    goalsButton->setStyleSheet(buttonStyle);
    habitsButton->setStyleSheet(buttonStyle);
    inspirationButton->setStyleSheet(buttonStyle);
    notesButton->setStyleSheet(buttonStyle);

    connect(notesButton, &QPushButton::clicked, [=]() { on_notesButton_clicked(inspirationButton,notesButton,centralWidget, mainLayout, buttonLayout, mainWidget, helloLabel, gridLayout, aspectRatioWidget); });
    connect(homeButton, &QPushButton::clicked, [=]() { resetWindow(inspirationButton,notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget); });
    connect(inspirationButton, &QPushButton::clicked,[=](){on_inspirationButton_clicked(inspirationButton,centralWidget, mainWidget, notesButton, mainLayout, buttonLayout, helloLabel,gridLayout,aspectRatioWidget);});
    connect(goalsButton, &QPushButton::clicked,[=](){on_GoalsButton_clicked(inspirationButton,goalsButton,centralWidget, mainWidget, notesButton, mainLayout, buttonLayout, helloLabel,gridLayout,aspectRatioWidget);});


    //add the layout to the grid layout
    gridLayout->addLayout(mainLayout, 0, 0, Qt::AlignTop | Qt::AlignHCenter);

    setCentralWidget(centralWidget);
    mainLayout->removeItem(mainLayout->itemAt(0));
    if (homeButton)
            {
                homeButton->setEnabled(false);
            }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetWindow(QPushButton* inspirationButton,QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget)
{
    helloLabel->setVisible(false);
    if (centralWidget()->findChild<QWidget*>("notesWidget"))
    {
        QWidget* notesWidget = centralWidget()->findChild<QWidget*>("notesWidget");
        QWidget* mainWidget = centralWidget()->findChild<QWidget*>("mainWidget");
        gridLayout->removeWidget(notesWidget);
        delete notesWidget;
        mainLayout->addWidget(mainWidget); // Add mainWidget back to the mainLayout
        if (notesButton)
        {
            notesButton->setEnabled(true);
        }

    }
    if (centralWidget()->findChild<QWidget*>("inspirationWidget")){
        QWidget* inspirationWidget = centralWidget()->findChild<QWidget*>("inspirationWidget");
        gridLayout->removeWidget(inspirationWidget);
        delete inspirationWidget;
        if (inspirationButton)
        {
            inspirationButton->setEnabled(true);
        }
    }
}

void MainWindow::on_notesButton_clicked(QPushButton* inspirationButton,QPushButton *notesButton, QWidget *centralWidget, QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QWidget *mainWidget, QLabel *helloLabel, QGridLayout *gridLayout, AspectRatioWidget *aspectRatioWidget)
{
    resetWindow(inspirationButton, notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

    if (notesButton)
    {
        notesButton->setEnabled(false);
    }

    QWidget *notesWidget = new QWidget(centralWidget);
    notesWidget->setObjectName("notesWidget");
    notesWidget->setStyleSheet("background-color: #071426");
    AspectRatioWidget *notesAspectRatioWidget = new AspectRatioWidget(notesWidget, 4, 4, centralWidget);
    gridLayout->addWidget(notesAspectRatioWidget, 1, 0, 5, 1);

    //scroll area for the notes
    QScrollArea *scrollArea = new QScrollArea(notesWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { background-color: transparent; border: none; width:10px;margin: 0px 0px 0px 0px;}"
                              "QScrollBar::add-page:vertical { background-color: #071426; }"
                              "QScrollBar::sub-page:vertical { background-color: #071426; }"
                              "QScrollBar::handle:vertical {"
                                  "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                  "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
                                  "    min-height: 0px;"
                                  "}");

    // text edit widget for the notepad
    QTextEdit *notepad = new QTextEdit(scrollArea);
    notepad->setObjectName("notepad");
    notepad->setStyleSheet("background-color: #0B1F3B;; color: white;");

    scrollArea->setWidget(notepad);

    QString button3Style = "QPushButton {"
                           "background-color: #009ace;"
                           "color: white;"
                           "border: none;"
                           "padding: 8px 16px;"
                           "border-radius: 4px;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: #1C82E7;"
                           "}"
                           "QPushButton:pressed {"
                           "background-color: #1669C6;"
                           "}";
    // save button
    QPushButton *saveButton = new QPushButton("Save");
    connect(saveButton, &QPushButton::clicked, [notepad]() {
        QString text = notepad->toPlainText();
        QString filePath = notepad->property("filePath").toString();

        // If the file path is not set, prompt for a file name
        if (filePath.isEmpty()) {
            bool gotOk = false;

            QDialog inputDialog(notepad);
            inputDialog.setWindowTitle("Save File");

            QLabel* label = new QLabel("Enter file name:", &inputDialog);

            QLineEdit* lineEdit = new QLineEdit(&inputDialog);
            lineEdit->setObjectName("fileNameLineEdit");

            QPushButton* okButton = new QPushButton("OK", &inputDialog);
            okButton->setObjectName("okButton");
            connect(okButton, &QPushButton::clicked, &inputDialog, &QDialog::accept);

            QPushButton* cancelButton = new QPushButton("Cancel", &inputDialog);
            cancelButton->setObjectName("cancelButton");
            connect(cancelButton, &QPushButton::clicked, &inputDialog, &QDialog::reject);

            QVBoxLayout* layout = new QVBoxLayout(&inputDialog);
            layout->addWidget(label);
            layout->addWidget(lineEdit);

            QHBoxLayout* buttonLayout = new QHBoxLayout;
            buttonLayout->addWidget(okButton);
            buttonLayout->addWidget(cancelButton);
            layout->addLayout(buttonLayout);

            inputDialog.setStyleSheet("QDialog {"
                                          "background-color: #071426;"
                                          "border: transparent;"
                                      "}"
                                      "QLabel {"
                                          "color: white;"
                                      "}"
                                      "QLineEdit#fileNameLineEdit {"
                                          "background-color: #071426;"
                                          "color: white;"
                                          "border: 1px solid white;"
                                      "}"
                                      "QPushButton#okButton {"
                                          "background-color: #009ace;"
                                          "color: white;"
                                          "border: none;"
                                      "}"
                                      "QPushButton#okButton:hover {"
                                          "background-color: #1C82E7;"
                                      "}"
                                      "QPushButton#cancelButton {"
                                          "background-color: #009ace;"
                                          "color: white;"
                                          "border: none;"
                                      "}"
                                      "QPushButton#cancelButton:hover {"
                                          "background-color: #1C82E7;"
                                      "}"
                                      "QPushButton:pressed {"
                                          "background-color: #1669C6;"
                                      "}");

            if (inputDialog.exec() == QDialog::Accepted) {
                QString fileName = lineEdit->text();
                if (!fileName.isEmpty()) {
                    QString defaultFolder = QDir::currentPath();
                    QString folderPath = defaultFolder + QDir::separator() + "savedFiles";
                    QDir().mkpath(folderPath);

                    filePath = folderPath + QDir::separator() + fileName + ".txt";

                    // Check if the file already exists
                    if (QFile::exists(filePath)) {
                        int fileCount = 1;
                        QString baseFileName = fileName;
                        while (QFile::exists(filePath)) {
                            fileName = baseFileName + "_" + QString::number(fileCount);
                            filePath = folderPath + QDir::separator() + fileName + ".txt";
                            fileCount++;
                        }
                    }
                }
            }
        }


        // Save the file
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << text;
            file.close();

            notepad->setProperty("filePath", filePath);
        }
    });

    QShortcut* saveShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), notepad);

    QObject::connect(saveShortcut, &QShortcut::activated, saveButton, &QPushButton::click);



    QPushButton *newButton = new QPushButton("New");
    connect(newButton, &QPushButton::clicked, [notepad]() {
        notepad->clear();
        notepad->setProperty("filePath", "");  // Reset the file path
    });

    QPushButton *loadButton = new QPushButton("Load");
    connect(loadButton, &QPushButton::clicked, [notepad]() {
        QString defaultFolder = QDir::currentPath();
        QString folderPath = defaultFolder + QDir::separator() + "savedFiles";
        QString filePath = QFileDialog::getOpenFileName(notepad, "Load File", folderPath);
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString loadedText = stream.readAll();
            file.close();

            notepad->setPlainText(loadedText);
            notepad->setProperty("filePath", filePath);  // Set the file path
        }
    });

    loadButton->setStyleSheet(button3Style);
    saveButton->setStyleSheet(button3Style);
    newButton->setStyleSheet(button3Style);

    QHBoxLayout *button3Layout = new QHBoxLayout();
    button3Layout->addWidget(saveButton);
    button3Layout->addWidget(newButton);
    button3Layout->addWidget(loadButton);

    // Main layout for the notes widget
    QVBoxLayout *mainNotesLayout = new QVBoxLayout(notesWidget);
    mainNotesLayout->addLayout(button3Layout);
    mainNotesLayout->addWidget(scrollArea);

    notesWidget->setLayout(mainNotesLayout);

    // Hide Hello message
    helloLabel->setVisible(false);
}

void MainWindow::on_inspirationButton_clicked(QPushButton* inspirationButton,QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget)
{
    resetWindow(inspirationButton,notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

    if (inspirationButton)
    {
        inspirationButton->setEnabled(false);
    }

        QWidget *inspirationWidget = new QWidget(centralWidget);
        inspirationWidget->setObjectName("inspirationWidget");
        inspirationWidget->setMinimumSize(500,500);
        AspectRatioWidget *inspirationAspectRatioWidget = new AspectRatioWidget(inspirationWidget, 4, 4, centralWidget);
        gridLayout->addWidget(inspirationAspectRatioWidget, 1, 0, 5, 1);
        QFile quotes(":/motivation/mfile.txt");
            if(!quotes.open(QIODevice::ReadOnly | QIODevice::Text)){
                return;
            }

            QList<QString> allQuotes;
            QTextStream in(&quotes);

            while (!in.atEnd()) {
                QString quoteDisplayed = in.readLine();
                allQuotes.append(quoteDisplayed);
            }

            quotes.close();

            int randomNumber = QRandomGenerator::global()->bounded(allQuotes.size());
            QString quoteDisplayed = allQuotes[randomNumber];


        QLabel *quoteLabel = new QLabel(quoteDisplayed, inspirationAspectRatioWidget);
        quoteLabel->setWordWrap(true);
        quoteLabel->setAlignment(Qt::AlignCenter);
        quoteLabel->setStyleSheet("font-size: 24px; color: white;");

        QVBoxLayout *inspirationLayout = new QVBoxLayout(inspirationWidget);
        inspirationLayout->addWidget(quoteLabel);
        inspirationWidget->setLayout(inspirationLayout);

}

void MainWindow::on_GoalsButton_clicked(QPushButton* inspirationButton, QPushButton* goalsButton, QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget)
{
    resetWindow(inspirationButton, notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

    QWidget* goalsWidget = new QWidget(centralWidget);
    goalsWidget->setObjectName("goalsWidget");
    goalsWidget->setMinimumSize(750, 500);
    AspectRatioWidget* goalsAspectRatioWidget = new AspectRatioWidget(goalsWidget, 16, 9, centralWidget);
    gridLayout->addWidget(goalsAspectRatioWidget, 1, 0, 5, 1);

    QVBoxLayout* mainGoalsLayout = new QVBoxLayout(goalsWidget);
    mainGoalsLayout->setAlignment(Qt::AlignTop);

    QHBoxLayout* goalsLayout = new QHBoxLayout();
    mainGoalsLayout->addLayout(goalsLayout);

    int goalCounter = 0;
    int totalGoalCounter = 0;
    const int maxGoals = 3;

    QHBoxLayout* goalsContainerLayout = new QHBoxLayout();
    goalsContainerLayout->setSpacing(10);
    goalsContainerLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton* addGoalButton = new QPushButton("Add Goal");
    addGoalButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 8px 16px; border-radius: 4px;");
    goalsLayout->addWidget(addGoalButton, 0, Qt::AlignBottom | Qt::AlignLeft);

    goalsWidget->setStyleSheet("background-color: #071426");

    QObject::connect(addGoalButton, &QPushButton::clicked,[=]() mutable {
        if (goalCounter < maxGoals) {
            goalCounter++;
            totalGoalCounter++;

            QString folderName = "savedGoals";
            QDir folderDir;
            folderDir.mkpath(folderName);
            QJsonObject jsonGoal;
            QJsonObject jsonSubgoals;

            jsonGoal.insert("title",goalCounter);
            jsonGoal.insert("number",goalCounter);
            jsonGoal.insert("subgoals",0);
            jsonGoal.insert("subgoalsTitles",jsonSubgoals);

            QJsonDocument document;
                    document.setObject( jsonGoal );
                    QByteArray bytes = document.toJson( QJsonDocument::Indented );
                    QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
                    QFile file(fileName);
                    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
                    {
                        QTextStream iStream( &file );
                        iStream << bytes;
                        file.close();
                    }

            QWidget* goalWidget = new QWidget(goalsWidget);
            goalWidget->setObjectName("goalWidget");
            goalWidget->setStyleSheet("background-color: #0B1F3B;");

            QVBoxLayout* goalWidgetLayout = new QVBoxLayout(goalWidget);

            QHBoxLayout* goalHeaderLayout = new QHBoxLayout();
            goalWidgetLayout->addLayout(goalHeaderLayout);

            QLineEdit* goalNameLineEdit = new QLineEdit;
            goalNameLineEdit->setText("Goal " + QString::number(totalGoalCounter));
            goalNameLineEdit->setStyleSheet("background-color: transparent; border: none; color: white; font-size: 16px; padding: 5px;");
            goalNameLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            goalNameLineEdit->setReadOnly(true);
            goalHeaderLayout->addWidget(goalNameLineEdit);

            QPushButton* deleteGoalButton = new QPushButton();
            deleteGoalButton->setFixedSize(24, 24);
            deleteGoalButton->setIcon(QIcon(":/imgs/deleteIcon.png"));
            deleteGoalButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
            goalHeaderLayout->addWidget(deleteGoalButton);

            QPushButton* editGoalNameButton = new QPushButton();
            editGoalNameButton->setFixedSize(24, 24);
            editGoalNameButton->setIcon(QIcon(":/imgs/modifyIcon.png"));
            editGoalNameButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
            goalHeaderLayout->addWidget(editGoalNameButton);

            QPushButton* addSubgoalButton = new QPushButton("+");
            addSubgoalButton->setFixedSize(24, 24);
            addSubgoalButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
            goalHeaderLayout->addWidget(addSubgoalButton);

            QObject::connect(deleteGoalButton, &QPushButton::clicked, [goalWidget, &goalCounter]() mutable {
                goalCounter--;
                if (goalWidget && goalWidget->parentWidget()) {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Confirmation");
                    msgBox.setText("Are you sure you want to delete this goal?");
                    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    msgBox.setDefaultButton(QMessageBox::No);

                    msgBox.setStyleSheet("QMessageBox {"
                                          "background-color: #071426;"
                                          "border: transparent;"
                                          "}"
                                          "QMessageBox QLabel {"
                                          "color: white;"
                                          "}"
                                          "QMessageBox QPushButton {"
                                         "background-color: #009ace;"
                                         "color: white;"
                                         "border: none;"
                                          "}"
                                          "QMessageBox QPushButton:hover {"
                                          "background-color: #1C82E7;"
                                          "}"
                                         "QMessageBox QPushButton:pressed{"
                                         "background-color: #1669C6;"
                                         "}");

                    if (msgBox.exec() == QMessageBox::Yes) {
                        goalWidget->deleteLater();
                    }
                }
            });



            QObject::connect(editGoalNameButton, &QPushButton::clicked, [=]() mutable {
                QString currentText = goalNameLineEdit->text();

                QDialog inputDialog(goalsWidget);
                inputDialog.setWindowTitle("Edit Goal Name");

                QLabel* label = new QLabel("Enter new text:", &inputDialog);

                QLineEdit* lineEdit = new QLineEdit(&inputDialog);
                lineEdit->setObjectName("newTextEdit");

                QPushButton* okButton = new QPushButton("OK", &inputDialog);
                okButton->setObjectName("okButton");
                connect(okButton, &QPushButton::clicked, &inputDialog, &QDialog::accept);

                QPushButton* cancelButton = new QPushButton("Cancel", &inputDialog);
                cancelButton->setObjectName("cancelButton");
                connect(cancelButton, &QPushButton::clicked, &inputDialog, &QDialog::reject);

                QVBoxLayout* layout = new QVBoxLayout(&inputDialog);
                layout->addWidget(label);
                layout->addWidget(lineEdit);

                QHBoxLayout* buttonLayout = new QHBoxLayout;
                buttonLayout->addWidget(okButton);
                buttonLayout->addWidget(cancelButton);
                layout->addLayout(buttonLayout);

                inputDialog.setStyleSheet("QDialog {"
                                              "background-color: #071426;"
                                              "border: transparent;"
                                          "}"
                                          "QLabel {"
                                              "color: white;"
                                          "}"
                                          "QLineEdit#newTextEdit {"
                                              "background-color: #071426;"
                                              "color: white;"
                                              "border: 1px solid white;"
                                          "}"
                                          "QPushButton#okButton {"
                                              "background-color: #009ace;"
                                              "color: white;"
                                              "border: none;"
                                          "}"
                                          "QPushButton#okButton:hover {"
                                              "background-color: #1C82E7;"
                                          "}"
                                          "QPushButton#cancelButton {"
                                              "background-color: #009ace;"
                                              "color: white;"
                                              "border: none;"
                                          "}"
                                          "QPushButton#cancelButton:hover {"
                                              "background-color: #1C82E7;"
                                          "}"
                                          "QPushButton:pressed {"
                                              "background-color: #1669C6;"
                                          "}");

                if (inputDialog.exec() == QDialog::Accepted) {
                    QString editText = lineEdit->text();
                    if (!editText.isEmpty()) {
                        goalNameLineEdit->setText(editText);
                        QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
                        QFile file(fileName);
                        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                            QByteArray data = file.readAll();
                            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                            QJsonObject jsonObj = jsonDoc.object();
                            jsonObj["title"] = editText;
                            file.resize(0);
                            file.write(QJsonDocument(jsonObj).toJson());
                            file.close();
                    }
                }
            }});

            QScrollArea* subgoalsScrollArea = new QScrollArea();
            subgoalsScrollArea->setStyleSheet("QScrollArea { background-color: transparent; border: none; width:10px;margin: 0px 0px 0px 0px;}"
                                              "QScrollBar::add-page:vertical { background-color: #071426; }"
                                              "QScrollBar::sub-page:vertical { background-color: #071426; }"
                                              "QScrollBar::handle:vertical {"
                                                  "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                                                  "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
                                                  "    min-height: 0px;"
                                                  "}");
            subgoalsScrollArea->setWidgetResizable(true);
            subgoalsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

            QWidget* subgoalsContainerWidget = new QWidget();
            QVBoxLayout* subgoalsContainerLayout = new QVBoxLayout(subgoalsContainerWidget);
            subgoalsContainerLayout->setSpacing(10);
            subgoalsContainerLayout->setContentsMargins(0, 0, 0, 0);
            subgoalsScrollArea->setWidget(subgoalsContainerWidget);

            goalWidgetLayout->addWidget(subgoalsScrollArea);

            QObject::connect(addSubgoalButton, &QPushButton::clicked, [=]() mutable {
                QHBoxLayout* subgoalLayout = new QHBoxLayout();

                QLabel* subgoalLabel = new QLabel("Subgoal");
                subgoalLabel->setStyleSheet("color:white; font-size: 14px;");
                subgoalLayout->addWidget(subgoalLabel);

                QPushButton* markSubgoalButton = new QPushButton();
                markSubgoalButton->setFixedSize(24, 24);
                markSubgoalButton->setIcon(QIcon(":/imgs/doneIcon.png"));
                markSubgoalButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
                subgoalLayout->addWidget(markSubgoalButton);

                QPushButton* editSubgoalButton = new QPushButton();
                editSubgoalButton->setIcon(QIcon(":/imgs/modifyIcon.png"));
                editSubgoalButton->setFixedSize(24, 24);
                editSubgoalButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
                subgoalLayout->addWidget(editSubgoalButton);

                QPushButton* deleteSubgoalButton = new QPushButton();
                deleteSubgoalButton->setFixedSize(24, 24);
                deleteSubgoalButton->setIcon(QIcon(":/imgs/deleteIcon.png"));
                deleteSubgoalButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
                subgoalLayout->addWidget(deleteSubgoalButton);

                int subgoalIndex;

                QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
                QFile file(fileName);
                if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
                    QByteArray data = file.readAll();
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                    QJsonObject jsonObj = jsonDoc.object();
                    jsonObj["subgoals"] = jsonObj["subgoals"].toInt() + 1;

                    subgoalIndex = jsonObj["subgoals"].toInt();

                    QJsonObject subgoalTitles = jsonObj["subgoalsTitles"].toObject();
                    QJsonObject subgoalDefault;
                    subgoalDefault.insert("marked", false);
                    subgoalDefault.insert("title", "Subgoal");
                    QString subgoalTitle = QString("Subgoal%1").arg(jsonObj["subgoals"].toInt());
                    subgoalTitles.insert(subgoalTitle,subgoalDefault);
                    jsonObj["subgoalsTitles"] = subgoalTitles;

                    file.resize(0);
                    file.write(QJsonDocument(jsonObj).toJson());
                    file.close();
                }

                QObject::connect(markSubgoalButton, &QPushButton::clicked, [=]() mutable {
                    QFont font = subgoalLabel->font();
                    bool isStrikedOut = font.strikeOut();
                    font.setStrikeOut(!isStrikedOut);
                    subgoalLabel->setFont(font);

                    QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
                    QFile file(fileName);
                    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                        QByteArray data = file.readAll();
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                        QJsonObject jsonObj = jsonDoc.object();
                        subgoalIndex = jsonObj["subgoals"].toInt();
                        QString subgoalSetTitle = QString("Subgoal%1").arg(subgoalIndex);
                        QJsonObject subgoalTitles = jsonObj["subgoalsTitles"].toObject();

                        QJsonObject subgoal1 = subgoalTitles[subgoalSetTitle].toObject();
                        subgoal1["marked"] = true;
                        subgoalTitles[subgoalSetTitle] = subgoal1;
                        jsonObj["subgoalsTitles"] = subgoalTitles;

                        file.resize(0);
                        file.write(QJsonDocument(jsonObj).toJson());
                        file.close();
                    }

                });


                QObject::connect(editSubgoalButton, &QPushButton::clicked, [=]() mutable {
                    QString currentText = subgoalLabel->text();

                    QDialog inputDialog(goalsWidget);
                    inputDialog.setWindowTitle("Edit Subgoal");

                    QLabel* label = new QLabel("Enter new text:", &inputDialog);

                    QLineEdit* lineEdit = new QLineEdit(&inputDialog);
                    lineEdit->setObjectName("newTextEdit");

                    QPushButton* okButton = new QPushButton("OK", &inputDialog);
                    okButton->setObjectName("okButton");
                    connect(okButton, &QPushButton::clicked, &inputDialog, &QDialog::accept);

                    QPushButton* cancelButton = new QPushButton("Cancel", &inputDialog);
                    cancelButton->setObjectName("cancelButton");
                    connect(cancelButton, &QPushButton::clicked, &inputDialog, &QDialog::reject);

                    QVBoxLayout* layout = new QVBoxLayout(&inputDialog);
                    layout->addWidget(label);
                    layout->addWidget(lineEdit);

                    QHBoxLayout* buttonLayout = new QHBoxLayout;
                    buttonLayout->addWidget(okButton);
                    buttonLayout->addWidget(cancelButton);
                    layout->addLayout(buttonLayout);

                    inputDialog.setStyleSheet("QDialog {"
                                                  "background-color: #071426;"
                                                  "border: transparent;"
                                              "}"
                                              "QLabel {"
                                                  "color: white;"
                                              "}"
                                              "QLineEdit#newTextEdit {"
                                                  "background-color: #071426;"
                                                  "color: white;"
                                                  "border: 1px solid white;"
                                              "}"
                                              "QPushButton#okButton {"
                                                  "background-color: #009ace;"
                                                  "color: white;"
                                                  "border: none;"
                                              "}"
                                              "QPushButton#okButton:hover {"
                                                  "background-color: #1C82E7;"
                                              "}"
                                              "QPushButton#cancelButton {"
                                                  "background-color: #009ace;"
                                                  "color: white;"
                                                  "border: none;"
                                              "}"
                                              "QPushButton#cancelButton:hover {"
                                                  "background-color: #1C82E7;"
                                              "}"
                                              "QPushButton:pressed {"
                                                  "background-color: #1669C6;"
                                              "}");

                    if (inputDialog.exec() == QDialog::Accepted) {
                        QString editText = lineEdit->text();
                        if (!editText.isEmpty()) {
                            subgoalLabel->setText(editText);
                        }
                    }
                });


                QObject::connect(deleteSubgoalButton, &QPushButton::clicked, [=]() mutable {

                    QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
                    QFile file(fileName);
                    if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
                        QByteArray data = file.readAll();
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                        QJsonObject jsonObj = jsonDoc.object();
                        jsonObj["subgoals"] = jsonObj["subgoals"].toInt() - 1;
                        file.resize(0);
                        file.write(QJsonDocument(jsonObj).toJson());
                        file.close();
                    }


                    deleteSubgoalButton->deleteLater();
                    markSubgoalButton->deleteLater();
                    editSubgoalButton->deleteLater();
                    subgoalLabel->deleteLater();
                    subgoalLayout->deleteLater();
                });

                subgoalsContainerLayout->addLayout(subgoalLayout);
            });

            goalsContainerLayout->insertWidget(goalsContainerLayout->count() / 2, goalWidget);
            AspectRatioWidget* goalWidgetAspectRatioWidget = new AspectRatioWidget(goalWidget, 12, 8, goalsWidget);
            goalsContainerLayout->insertWidget(goalsContainerLayout->count() / 2, goalWidgetAspectRatioWidget);

        }
        else{
            QMessageBox warningBox;
            warningBox.setWindowTitle("Warning");
            warningBox.setText("You should focus on 3 goals or less for your own good.");
            warningBox.setStandardButtons(QMessageBox::Ok);

            warningBox.setStyleSheet("QMessageBox {"
                                  "background-color: #071426;"
                                  "border: transparent;"
                                  "}"
                                  "QMessageBox QLabel {"
                                  "color: white;"
                                  "}"
                                  "QMessageBox QPushButton {"
                                 "background-color: #009ace;"
                                 "color: white;"
                                 "border: none;"
                                  "}"
                                  "QMessageBox QPushButton:hover {"
                                  "background-color: #1C82E7;"
                                  "}"
                                 "QMessageBox QPushButton:pressed{"
                                 "background-color: #1669C6;"
                                 "}");

            warningBox.exec();
        }

    });

    mainGoalsLayout->addLayout(goalsContainerLayout);

    goalsWidget->setLayout(mainGoalsLayout);

}



