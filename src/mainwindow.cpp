#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aspectratiowidget.h"
#include <calendarpopupdialog.h>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
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
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QAbstractItemView>
#include <QCalendarWidget>
#include <QScrollBar>
#include <QDate>

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
    this->setMinimumSize(850,620);
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

    connect(notesButton, &QPushButton::clicked, [=]() { on_notesButton_clicked(inspirationButton,goalsButton, notesButton,centralWidget, mainLayout, buttonLayout, mainWidget, helloLabel, gridLayout, aspectRatioWidget); });
    connect(homeButton, &QPushButton::clicked, [=]() { resetWindow(inspirationButton,goalsButton, notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget); });
    connect(inspirationButton, &QPushButton::clicked,[=](){on_inspirationButton_clicked(inspirationButton,goalsButton, centralWidget, mainWidget, notesButton, mainLayout, buttonLayout, helloLabel,gridLayout,aspectRatioWidget);});
    connect(goalsButton, &QPushButton::clicked,[=](){on_GoalsButton_clicked(inspirationButton,goalsButton,centralWidget, mainWidget, notesButton, mainLayout, buttonLayout, helloLabel,gridLayout,aspectRatioWidget);});
    connect(habitsButton, &QPushButton::clicked,[=](){on_habitsButton_clicked(habitsButton, inspirationButton,goalsButton,centralWidget, mainWidget, notesButton, mainLayout, buttonLayout, helloLabel,gridLayout,aspectRatioWidget);});


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

void MainWindow::resetWindow(QPushButton* inspirationButton, QPushButton* goalsButton, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget)
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
    if (centralWidget()->findChild<QWidget*>("goalsWidget")){
        if (goalsButton)
        {
            goalsButton->setEnabled(true);
        }
    }
}

void MainWindow::on_notesButton_clicked(QPushButton* inspirationButton,QPushButton* goalsButton,QPushButton *notesButton, QWidget *centralWidget, QVBoxLayout *mainLayout, QHBoxLayout *buttonLayout, QWidget *mainWidget, QLabel *helloLabel, QGridLayout *gridLayout, AspectRatioWidget *aspectRatioWidget)
{
    resetWindow(inspirationButton,goalsButton, notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

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

    QPushButton *recentFilesButton = new QPushButton("Recent Files");
    connect(recentFilesButton, &QPushButton::clicked, [button3Style, notepad] (){

        QDialog recentFilesDialog(notepad);
        recentFilesDialog.setWindowTitle("Recent Files");

        QComboBox comboBox(&recentFilesDialog);
        QString comboBoxStylesheet = "QComboBox {"
                                       "    padding-left: 85px;"
                                       "    background-color: #071426;"
                                       "    color: white;"
                                       "    border: 1px solid white;"
                                       "}"
                                       "QComboBox:hover {"
                                       "    background-color: #071426;"
                                       "    border: 1px solid #009ace;"
                                       "}"
                                       "QComboBox::drop-down {"
                                       "    subcontrol-origin: padding;"
                                       "    subcontrol-position: top right;"
                                       "    width: 20px;"
                                       "    border-left-width: 1px;"
                                       "    border-left-color: white;"
                                       "    border-left-style: solid;"
                                       "}" ;
        comboBox.setStyleSheet(comboBoxStylesheet);
        QString defaultFolder = QDir::currentPath() + QDir::separator() + "savedFiles";
        QDir dir(defaultFolder);

        QStringList recentFileNames;
        QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files, QDir::Time);

        for (int i = 0; i < fileInfoList.size() && i < 10; ++i) {
            recentFileNames.push_back(fileInfoList[i].fileName());
        }

        comboBox.addItems(recentFileNames);
        QPushButton loadButton("Load", &recentFilesDialog);
        loadButton.setStyleSheet(button3Style);
        connect(&loadButton, &QPushButton::clicked, [defaultFolder, &comboBox, notepad]() {
            QString selectedFile = comboBox.currentText();
            QString filePath = defaultFolder + QDir::separator() + selectedFile;
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                QString loadedText = stream.readAll();
                file.close();

                notepad->setPlainText(loadedText);
                notepad->setProperty("filePath", filePath);  // Set the file path
            }
        });

        QVBoxLayout layout(&recentFilesDialog);
        layout.addWidget(&comboBox);
        layout.addWidget(&loadButton);

        recentFilesDialog.exec();
    });

    loadButton->setStyleSheet(button3Style);
    saveButton->setStyleSheet(button3Style);
    newButton->setStyleSheet(button3Style);
    recentFilesButton->setStyleSheet(button3Style);

    QHBoxLayout *button3Layout = new QHBoxLayout();
    button3Layout->addWidget(saveButton);
    button3Layout->addWidget(newButton);
    button3Layout->addWidget(loadButton);
    button3Layout->addWidget(recentFilesButton);

    // Main layout for the notes widget
    QVBoxLayout *mainNotesLayout = new QVBoxLayout(notesWidget);
    mainNotesLayout->addLayout(button3Layout);
    mainNotesLayout->addWidget(scrollArea);

    notesWidget->setLayout(mainNotesLayout);

    // Hide Hello message
    helloLabel->setVisible(false);
}

void MainWindow::on_inspirationButton_clicked(QPushButton* inspirationButton,QPushButton* goalsButton,QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget)
{
    resetWindow(inspirationButton,goalsButton, notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

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
    resetWindow(inspirationButton,goalsButton, notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

    if (goalsButton)
    {
        goalsButton->setEnabled(false);
    }

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
            int goalCounterCopy = goalCounter;
            totalGoalCounter++;

            QString folderName = "savedGoals";
            QDir folderDir;
            folderDir.mkpath(folderName);
            QJsonObject jsonGoal;
            QJsonObject jsonSubgoals;
            QString goalTitle = QString("Goal %1").arg(goalCounter);
            QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
            QFile file(fileName);

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
            subgoalsScrollArea->setWidget(subgoalsContainerWidget);;


          if(!file.exists()){
            jsonGoal.insert("title",goalTitle);
            jsonGoal.insert("number",goalCounter);
            jsonGoal.insert("subgoals",0);
            jsonGoal.insert("subgoalsTitles",jsonSubgoals);

            QJsonDocument document;
                    document.setObject( jsonGoal );
                    QByteArray bytes = document.toJson( QJsonDocument::Indented );
                    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
                    {
                        QTextStream iStream( &file );
                        iStream << bytes;
                        file.close();
                    }}

          else{
              if( file.open( QIODevice::ReadOnly | QIODevice::Text | QIODevice::Truncate ) )
              {
              QJsonObject jsonObj = QJsonDocument::fromJson(file.readAll()).object();
              int numSubgoals = jsonObj["subgoals"].toInt();
              QJsonObject subgoalTitlesObj = jsonObj["subgoalsTitles"].toObject();

              for (auto subgoalIt = subgoalTitlesObj.begin(); subgoalIt != subgoalTitlesObj.end(); ++subgoalIt){
                  QString subgoalKey = subgoalIt.key();
                  QJsonObject subgoalObj = subgoalTitlesObj[subgoalKey].toObject();
                  QString subgoalGivenTitle = subgoalKey;
                  QString firstValue = "";

                  for(int i = 7; i < subgoalGivenTitle.length(); i++ ){
                      firstValue.append(subgoalGivenTitle.at(i));
                  }

                  int intValue = firstValue.toInt();
                  addSubgoal(intValue, goalCounter,folderName,subgoalsContainerLayout, goalsWidget, subgoalObj["title"].toString(), subgoalObj["marked"].toBool());
              }
              }
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

            QObject::connect(deleteGoalButton, &QPushButton::clicked, [goalCounterCopy, goalWidget, &goalCounter]() mutable {
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
                        QString changeFile = QString("%1/goal_%2.json").arg("savedGoals").arg(goalCounterCopy+1);
                        QString currentFile =QString("%1/goal_%2.json").arg("savedGoals").arg(goalCounterCopy);

                        if(goalCounterCopy >= goalCounter){
                            QString currentFile =QString("%1/goal_%2.json").arg("savedGoals").arg(goalCounter);
                             QFile::remove(currentFile);}

                        QFile::remove(currentFile);
                        if(goalCounterCopy < goalCounter){
                            QFile::rename(changeFile, currentFile);
                            if(goalCounterCopy == 1 && goalCounter == 3)
                                QFile::rename("savedGoals/goal_3.json", "savedGoals/goal_2.json");

                        }
                        goalCounter--;
                        goalCounterCopy--;

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

            if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QByteArray data = file.readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();
                if(jsonObj["title"].toString() != goalNameLineEdit->text()){
                    goalNameLineEdit->setText(jsonObj["title"].toString());
                }
                file.resize(0);
                file.write(QJsonDocument(jsonObj).toJson());
                file.close();
        }

            connect(addSubgoalButton, &QPushButton::clicked, [=]() {addSubgoal(0, goalCounter,folderName,subgoalsContainerLayout, goalsWidget, "None", false);});

            goalWidgetLayout->addWidget(subgoalsScrollArea);
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

    loadGoals(addGoalButton);

}

void MainWindow::addSubgoal(int subgoalIndex, int goalCounter,QString folderName,QVBoxLayout* subgoalsContainerLayout, QWidget* goalsWidget, QString subgoalGivenTitle, bool subgoalMarked ){
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

        if(subgoalIndex)
            subgoalLabel->setText(subgoalGivenTitle);
        if(subgoalMarked){
            QFont font = subgoalLabel->font();
            font.setStrikeOut(1);
            subgoalLabel->setFont(font);
        }

        if(subgoalIndex == 0){

        QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){

            QByteArray data = file.readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            jsonObj["subgoals"] = jsonObj["subgoals"].toInt() + 1;

            QJsonObject subgoalTitles = jsonObj["subgoalsTitles"].toObject();
            QJsonObject subgoalDefault;
            subgoalDefault.insert("marked", false);
            subgoalDefault.insert("title", "Subgoal");
            QString subgoalTitle = QString("Subgoal%1").arg(jsonObj["subgoals"].toInt());
            subgoalTitles.insert(subgoalTitle,subgoalDefault);
            jsonObj["subgoalsTitles"] = subgoalTitles;
            subgoalIndex = jsonObj["subgoals"].toInt();

            file.resize(0);
            file.write(QJsonDocument(jsonObj).toJson());
            file.close();
        }
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
                QString subgoalSetTitle = QString("Subgoal%1").arg(subgoalIndex);
                QJsonObject subgoalTitles = jsonObj["subgoalsTitles"].toObject();

                QJsonObject subgoal1 = subgoalTitles[subgoalSetTitle].toObject();
                if(subgoal1["marked"] == false)
                    subgoal1["marked"] = true;
                else
                    subgoal1["marked"] = false;

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
                    QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(goalCounter);
                    QFile file(fileName);
                    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                        QByteArray data = file.readAll();
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                        QJsonObject jsonObj = jsonDoc.object();
                        QString subgoalSetTitle = QString("Subgoal%1").arg(subgoalIndex);
                        QJsonObject subgoalTitles = jsonObj["subgoalsTitles"].toObject();

                        QJsonObject subgoal1 = subgoalTitles[subgoalSetTitle].toObject();
                        subgoal1["title"] = editText;
                        subgoalTitles[subgoalSetTitle] = subgoal1;
                        jsonObj["subgoalsTitles"] = subgoalTitles;

                        file.resize(0);
                        file.write(QJsonDocument(jsonObj).toJson());
                        file.close();
                    }
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
                QString subgoalSetTitle = QString("Subgoal%1").arg(subgoalIndex);
                QJsonObject subgoalsObject = jsonObj["subgoalsTitles"].toObject();
                subgoalsObject.remove(subgoalSetTitle);
                jsonObj["subgoalsTitles"] = subgoalsObject;
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
}

void MainWindow::loadGoals(QPushButton* addGoalButton){
    for (int i = 1; i <= 3; i++){

        QString folderName = "savedGoals";
        QString fileName = QString("%1/goal_%2.json").arg(folderName).arg(i);
        QFile file(fileName);

        if (file.exists()) {
              addGoalButton->click();

          }
    }
}

void MainWindow::on_habitsButton_clicked(QPushButton* habitsButton, QPushButton* inspirationButton, QPushButton* goalsButton, QWidget* centralWidget, QWidget* mainWidget, QPushButton* notesButton, QVBoxLayout* mainLayout, QHBoxLayout* buttonLayout, QLabel* helloLabel, QGridLayout* gridLayout, AspectRatioWidget* aspectRatioWidget) {

    resetWindow(inspirationButton, goalsButton, notesButton, mainLayout, buttonLayout, helloLabel, gridLayout, aspectRatioWidget);

    QWidget* habitsWidget = new QWidget(centralWidget);
    habitsWidget->setObjectName("habitsWidget");
    habitsWidget->setMinimumSize(800, 500);
    AspectRatioWidget* habitsAspectRatioWidget = new AspectRatioWidget(habitsWidget, 16, 9, centralWidget);
    gridLayout->addWidget(habitsAspectRatioWidget, 1, 0, 5, 1);
    habitsWidget->setStyleSheet("background-color: #071426");

    QString folderName = "savedHabits";
    QDir folderDir;
    folderDir.mkpath(folderName);
    QJsonObject jsonHabits;
    QJsonObject jsonList;
    QString fileName = QString("%1/habits.json").arg(folderName);
    QFile file(fileName);

    bool hidden;
    QList<QWidget*> upComingList;

    QVBoxLayout* mainHabitsLayout = new QVBoxLayout(habitsWidget);
    mainHabitsLayout->setAlignment(Qt::AlignTop);

    QScrollArea* scrollArea = new QScrollArea(habitsWidget);
    scrollArea->setStyleSheet("QScrollArea { background-color: transparent; border: none; width:10px;margin: 0px 0px 0px 0px; }");

    QWidget* habitsContainerWidget = new QWidget();
    scrollArea->setWidget(habitsContainerWidget);
    scrollArea->setWidgetResizable(true);

    QString scrollbarStyle = "QScrollBar:vertical { background-color: transparent; width: 20px; }"
                             "QScrollBar::add-page:vertical { background-color: #08172b; }"
                             "QScrollBar::sub-page:vertical { background-color: #08172b; }"
                            "QScrollBar::handle:vertical {"
                            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                            "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
                            "    min-height: 0px;"
                            "}";

    scrollArea->verticalScrollBar()->setStyleSheet(scrollbarStyle);

    mainHabitsLayout->addWidget(scrollArea);

    QVBoxLayout* habitsContainerLayout = new QVBoxLayout(habitsContainerWidget);
    habitsContainerLayout->setSpacing(10);
    habitsContainerLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton* addHabitButton = new QPushButton("Add Habit");
    addHabitButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 8px 16px; border-radius: 4px;");
    mainHabitsLayout->addWidget(addHabitButton, 0, Qt::AlignBottom | Qt::AlignLeft);

    QPushButton* hideButton = new QPushButton("Hide Upcoming");
    hideButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 8px 16px; border-radius: 4px;");
    mainHabitsLayout->addWidget(hideButton, 0, Qt::AlignBottom | Qt::AlignLeft);

    //check if json file exists

    if(!file.exists()){
      jsonHabits.insert("hideUpcoming",false);
      hidden = false;
      jsonHabits.insert("number",0);
      jsonHabits.insert("list", jsonList);

      QJsonDocument document;
              document.setObject( jsonHabits );
              QByteArray bytes = document.toJson( QJsonDocument::Indented );
              if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
              {
                  QTextStream iStream( &file );
                  iStream << bytes;
                  file.close();
              }}

    else if( file.open( QIODevice::ReadOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
    QJsonObject jsonObj = QJsonDocument::fromJson(file.readAll()).object();
    int numHabits = jsonObj["number"].toInt();
    hidden = jsonObj["hideUpcoming"].toBool();
    QJsonObject list = jsonObj["list"].toObject();

    for (auto habitIt = list.begin(); habitIt != list.end(); ++habitIt){
        QString habitKey = habitIt.key();
        QJsonObject habitObj = list[habitKey].toObject();
        QString habitGivenTitle = habitKey;
        QString firstValue = "";

        for(int i = 5; i < habitGivenTitle.length(); i++ ){
            firstValue.append(habitGivenTitle.at(i));
        }

        int intValue = firstValue.toInt();
        addHabit(habitsButton,upComingList, habitsWidget, habitsContainerLayout, intValue, habitObj["title"].toString(), habitObj["repetition"].toString(),habitObj["times"].toString());
    }
        file.close();
    }

    //hide upcoming habits

    if (hidden)
        hideButton->setText("Hide Upcoming");
    else
        hideButton->setText("Show Upcoming");
    if(!upComingList.empty())
        for(auto upComingWidget : upComingList)
            if(upComingWidget)
                upComingWidget->setVisible(hidden);

    QObject::connect(hideButton, &QPushButton::clicked, [=]() mutable {

        if (!hidden) {
            hideButton->setText("Hide Upcoming");
            hidden = true;
        } else{
            hideButton->setText("Show Upcoming");
            hidden = false;
        }

        QString folderName = "savedHabits";
        QString fileName = QString("%1/habits.json").arg(folderName);
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QByteArray data = file.readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            jsonObj["hideUpcoming"] = hidden;
            file.resize(0);
            file.write(QJsonDocument(jsonObj).toJson());
            file.close();
        }
        if(!upComingList.empty())
            for(auto upComingWidget : upComingList)
                if(upComingWidget)
                    upComingWidget->setVisible(hidden);
    });

    connect(addHabitButton, &QPushButton::clicked, [=]() mutable{ addHabit(habitsButton,upComingList, habitsWidget, habitsContainerLayout, 0, "", "", ""); });

}

void MainWindow::addHabit(QPushButton* habitsButton, QList<QWidget*> &upComingList, QWidget* habitsWidget,QVBoxLayout* habitsLayout, int habitIndex, QString habitTitle, QString repetition, QString times){

    QWidget* habitWidget = new QWidget(habitsWidget);
    habitWidget->setObjectName("habitWidget");
    habitWidget->setStyleSheet("background-color: #0B1F3B;");
    habitWidget->setMaximumHeight(200);
    int position = upComingList.size() +1;

    QHBoxLayout* habitWidgetLayout = new QHBoxLayout(habitWidget);

    QVBoxLayout* habitHeaderLayout = new QVBoxLayout();
    habitWidgetLayout->addLayout(habitHeaderLayout);

    QLineEdit* habitNameLineEdit = new QLineEdit;
    habitNameLineEdit->setText("Habit");
    habitNameLineEdit->setStyleSheet("background-color: transparent; border: none; color: white; font-size: 24px; padding: 5px;");
    habitNameLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    habitNameLineEdit->setReadOnly(true);
    habitHeaderLayout->addWidget(habitNameLineEdit);

    QLineEdit* repetitionNameLineEdit = new QLineEdit;
    repetitionNameLineEdit->setText("Daily");
    repetitionNameLineEdit->setStyleSheet("background-color: transparent; border: none; color: white; font-size: 16px; padding: 5px;");
    repetitionNameLineEdit->setAlignment(Qt::AlignHCenter | Qt::AlignBaseline);
    repetitionNameLineEdit->setReadOnly(true);
    habitHeaderLayout->addWidget(repetitionNameLineEdit);

    QPushButton* doneHabitButton = new QPushButton();
    doneHabitButton->setFixedSize(24, 24);
    doneHabitButton->setIcon(QIcon(":/imgs/doneIcon.png"));
    doneHabitButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
    habitHeaderLayout->addWidget(doneHabitButton);

    QPushButton* editHabitButton = new QPushButton();
    editHabitButton->setFixedSize(24, 24);
    editHabitButton->setIcon(QIcon(":/imgs/modifyIcon.png"));
    editHabitButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
    habitHeaderLayout->addWidget(editHabitButton);

    QPushButton* deleteHabitButton = new QPushButton();
    deleteHabitButton->setFixedSize(24, 24);
    deleteHabitButton->setIcon(QIcon(":/imgs/deleteIcon.png"));
    deleteHabitButton->setStyleSheet("background-color: #009ace; color: white; border: none; padding: 0; border-radius: 12px;");
    habitHeaderLayout->addWidget(deleteHabitButton);

    QWidget* bottomLeftWidget = new QWidget(habitsWidget);
    bottomLeftWidget->setStyleSheet("background-color: transparent;");
    bottomLeftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    bottomLeftWidget->setMaximumWidth(120);

    QVBoxLayout* bottomLeftLayout = new QVBoxLayout(bottomLeftWidget);

    QLineEdit* progressLineEdit = new QLineEdit;
    progressLineEdit->setText("In progress");
    progressLineEdit->setStyleSheet("background-color: transparent; border: none; color: white; font-size: 16px; padding: 5px;");
    progressLineEdit->setAlignment(Qt::AlignRight | Qt::AlignBaseline);
    progressLineEdit->setReadOnly(true);
    bottomLeftLayout->addWidget(progressLineEdit);

    bottomLeftLayout->addStretch(1);

    QDate currentDate = QDate::currentDate();
    QString formattedDate = currentDate.toString("dd/MM/yyyy");
    QLineEdit* dateLineEdit = new QLineEdit;
    dateLineEdit->setText(formattedDate);
    dateLineEdit->setStyleSheet("background-color: transparent; border: none; color: white; font-size: 16px; padding: 5px;");
    dateLineEdit->setAlignment(Qt::AlignRight | Qt::AlignBaseline);
    dateLineEdit->setReadOnly(true);
    bottomLeftLayout->addWidget(dateLineEdit);

    habitWidgetLayout->addWidget(bottomLeftWidget);

    QString folderName = "savedHabits";
    QString fileName = QString("%1/habits.json").arg(folderName);
    QFile file(fileName);

    //create json for new habits
    if(habitIndex == 0){
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)){

        QByteArray data = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        jsonObj["number"] = jsonObj["number"].toInt() + 1;

        QJsonObject list = jsonObj["list"].toObject();
        QJsonObject habitSettings;
        habitSettings.insert("times", "");
        habitSettings.insert("repetition", "Daily");
        habitSettings.insert("title", "Habit");
        QString habit = QString("Habit%1").arg(jsonObj["number"].toInt());
        list.insert(habit,habitSettings);
        jsonObj["list"] = list;
        habitIndex = jsonObj["number"].toInt();

        file.resize(0);
        file.write(QJsonDocument(jsonObj).toJson());
        file.close();
    }}

    //load json for old habits
    else{
        habitNameLineEdit->setText(habitTitle);
        repetitionNameLineEdit->setText(repetition);
       if (file.open(QIODevice::ReadWrite | QIODevice::Text)){

           QByteArray data = file.readAll();
           QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
           QJsonObject jsonObj = jsonDoc.object();
           QString habitString = QString("Habit%1").arg(habitIndex);
           QJsonObject habitList = jsonObj["list"].toObject();
           QJsonObject editedHabit = habitList[habitString].toObject();

        if(repetition != "Custom"){
        QDate inputDate = QDate::fromString(times,"dd/MM/yyyy");
        QDate outputDate = inputDate;
         if (inputDate < currentDate){
             if(repetition == "Weekly"){
                 int daysToAdd = inputDate.dayOfWeek() - currentDate.dayOfWeek();
                 if (daysToAdd < 0)
                     daysToAdd += 7;
                 outputDate = currentDate.addDays(daysToAdd);
             }
             if(repetition == "Daily")
                 outputDate = currentDate;
             if(repetition == "Monthly"){
                 outputDate.setDate(currentDate.year(), currentDate.month(), inputDate.day());
                 if(outputDate < currentDate)
                     outputDate = outputDate.addMonths(1);
             }
             if(repetition == "Yearly"){
                 int yearsToAdd = inputDate.year() - currentDate.year();
                             if (yearsToAdd < 0)
                                 yearsToAdd += 1;
                outputDate = currentDate.addYears(yearsToAdd);
             }
         }
         if (currentDate == outputDate)
            progressLineEdit->setText("In progress");
         else{
            progressLineEdit->setText("Upcoming");
            upComingList.append(habitWidget);
            position = upComingList.size() - 1;
         }
        dateLineEdit->setText(outputDate.toString("dd/MM/yyyy"));
        editedHabit["times"] = outputDate.toString("dd/MM/yyyy");
        }

        else{
            QStringList futureDates;
            QStringList dateList = times.split(", ");
            foreach (const QString &date, dateList) {
                QDate inputDate = QDate::fromString(date, "dd/MM/yyyy");
                if(inputDate >= currentDate)
                    futureDates.append(date);
            }
            if(!futureDates.empty()){
            QString futureDatesStr = futureDates.join(", ");
            QDate outputDate = QDate::fromString(futureDates[0], "dd/MM/yyyy");
            dateLineEdit->setText(outputDate.toString("dd/MM/yyyy"));
            editedHabit["times"] = futureDatesStr;
            if (currentDate == outputDate)
               progressLineEdit->setText("In progress");
            else{
               progressLineEdit->setText("Upcoming");
               upComingList.append(habitWidget);
               position = upComingList.size() - 1;
            }
            }
            else{

                habitWidget->deleteLater();
                habitList.remove(habitString);

            }
        }
        habitList[habitString] = editedHabit;
        jsonObj["list"] = habitList;
        file.resize(0);
        file.write(QJsonDocument(jsonObj).toJson());
        file.close();
    }
    }

    QObject::connect(deleteHabitButton, &QPushButton::clicked, [=, &upComingList]() mutable {
        QMessageBox msgBox;
                            msgBox.setWindowTitle("Confirmation");
                            msgBox.setText("Are you sure you want to delete this habit?");
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

          habitWidget->deleteLater();

          QString folderName = "savedHabits";
          QString fileName = QString("%1/habits.json").arg(folderName);
          QFile file(fileName);
          if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
              QByteArray data = file.readAll();
              QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
              QJsonObject jsonObj = jsonDoc.object();
              QString deletedHabit = QString("Habit%1").arg(habitIndex);
              QJsonObject habitObject = jsonObj["list"].toObject();
              habitObject.remove(deletedHabit);
              jsonObj["list"] = habitObject;
              file.resize(0);
              file.write(QJsonDocument(jsonObj).toJson());
              file.close();
      }
          habitsButton->click();
      }
    });

    QObject::connect(editHabitButton, &QPushButton::clicked, [=]() mutable {
        QDialog dialog(this);
        dialog.setWindowTitle("Edit Habit Settings");
        dialog.setFixedSize(250, 150);
        dialog.setModal(true);

        QVBoxLayout mainLayout(&dialog);

        QFormLayout formLayout;
        mainLayout.addLayout(&formLayout);

        QPushButton* changeHabitRepetition = new QPushButton("Change Repetition");
        changeHabitRepetition->setStyleSheet("QPushButton {"
                                                           "border: 1px solid white;"
                                                             "color: white;"
                                                            "}"
                                                           "QPushButton:hover {"
                                                            "background-color: #009ace;"
                                                            "}");
        changeHabitRepetition->setText(repetitionNameLineEdit->text());

        QLineEdit *changeLineEdit = new QLineEdit(&dialog);
        changeLineEdit->setText(habitNameLineEdit->text());
        changeLineEdit->setStyleSheet("background-color: #071426;"
                                      "color: white;"
                                      "border: 1px solid white;");
        mainLayout.addWidget(changeLineEdit);

        QComboBox *comboBox = new QComboBox(&dialog);
            comboBox->addItem("Daily");
            comboBox->addItem("Weekly");
            comboBox->addItem("Monthly");
            comboBox->addItem("Yearly");
            comboBox->addItem("Custom");
       mainLayout.addWidget(comboBox);

       QString comboBoxStylesheet = "QComboBox {"
                                      "    padding-left: 85px;"
                                      "    background-color: #071426;"
                                      "    color: white;"
                                      "    border: 1px solid white;"
                                      "}"
                                      "QComboBox:hover {"
                                      "    background-color: #071426;"
                                      "    border: 1px solid #009ace;"
                                      "}"
                                      "QComboBox::drop-down {"
                                      "    subcontrol-origin: padding;"
                                      "    subcontrol-position: top right;"
                                      "    width: 20px;"
                                      "    border-left-width: 1px;"
                                      "    border-left-color: white;"
                                      "    border-left-style: solid;"
                                      "}" ;
       QString listViewStylesheet = "QListView {"
                                   "    border: none;"
                                   "    color: white;"
                                   "    font-weight: bold;"
                                   "    selection-background-color: #071426;"
                                   "    margin-left: -10px;"
                                   "    padding-left: 15px;"
                                   "}"
                                   "QListView::item:hover {"
                                   "    background-color: #071426;"
                                   "    border: none;"
                                   "}";

       comboBox->setStyleSheet(comboBoxStylesheet);
       comboBox->view()->setStyleSheet(listViewStylesheet);
       comboBox->hide();

        CalendarPopupDialog calendarPopup;

        mainLayout.addWidget(changeHabitRepetition, Qt::AlignLeft);
        QObject::connect(changeHabitRepetition, &QPushButton::clicked, [&changeHabitRepetition, &comboBox]() mutable {

            comboBox->show();
            changeHabitRepetition->hide();
            changeHabitRepetition = nullptr;

        });

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);
        buttonBox.button(QDialogButtonBox::Ok)->setStyleSheet("color:white;background-color:#009ace;border:none;");
        buttonBox.button(QDialogButtonBox::Cancel)->setStyleSheet("color:white;background-color:#009ace;border:none;");
        mainLayout.addWidget(&buttonBox);

        QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        if (dialog.exec() == QDialog::Accepted) {

            bool validate = false;
            if(progressLineEdit->text() == "Upcoming")
                validate = false;

            habitNameLineEdit->setText(changeLineEdit->text());
            QString folderName = "savedHabits";
            QString fileName = QString("%1/habits.json").arg(folderName);
            QFile file(fileName);
         if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
             QByteArray data = file.readAll();
             QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
             QJsonObject jsonObj = jsonDoc.object();
             QString habitSetTitle = QString("Habit%1").arg(habitIndex);
             QJsonObject list = jsonObj["list"].toObject();

             QJsonObject editedHabit = list[habitSetTitle].toObject();
             editedHabit["title"] = changeLineEdit->text();
            if(changeHabitRepetition == nullptr){

            editedHabit["repetition"] = comboBox->currentText();
            repetitionNameLineEdit->setText(comboBox->currentText());
            if (comboBox->currentText() == "Yearly") {
                int result = calendarPopup.exec();
                if (result == QDialog::Accepted) {
                    QString selectedDate = calendarPopup.getSelectedDate().toString("dd/MM/yyyy");
                    if (calendarPopup.getSelectedDate() < currentDate)
                            selectedDate = calendarPopup.getSelectedDate().addYears(1).toString("dd/MM/yyyy");
                    if(calendarPopup.getSelectedDate() != currentDate)
                        progressLineEdit->setText("Upcoming");
                    else
                        progressLineEdit->setText("In progress");
                    dateLineEdit->setText(selectedDate);
                    editedHabit["times"] = selectedDate;

                }
            }
            if (comboBox->currentText() == "Daily") {
                progressLineEdit->setText("In progress");
                dateLineEdit->setText(currentDate.toString("dd/MM/yyyy"));
            }
            if (comboBox->currentText() == "Monthly") {
                        QDate repetitionDate = calendarPopup.showMonthlyRepetitionPopup();
                        if (repetitionDate.isValid()) {
                            if (repetitionDate < currentDate)
                                   repetitionDate = repetitionDate.addMonths(1);
                           dateLineEdit->setText(repetitionDate.toString("dd/MM/yyyy"));
                           editedHabit["times"] = repetitionDate.toString("dd/MM/yyyy");
                           if(repetitionDate > currentDate)
                               progressLineEdit->setText("Upcoming");
                           else
                               progressLineEdit->setText("In progress");
                        }
            }
            if (comboBox->currentText() == "Weekly") {
                        QDate repetitionDate = calendarPopup.showWeeklyRepetitionPopup();
                        if (repetitionDate.isValid()) {
                            dateLineEdit->setText(repetitionDate.toString("dd/MM/yyyy"));
                            if(repetitionDate > currentDate)
                                progressLineEdit->setText("Upcoming");
                            else
                                progressLineEdit->setText("In progress");
                            editedHabit["times"] = repetitionDate.toString("dd/MM/yyyy");
                        }
            }
            if(comboBox->currentText() == "Custom"){
                QStringList repetitionDates = calendarPopup.customRepetitionPopup();
                if(!repetitionDates.empty()){
                 dateLineEdit->setText(repetitionDates[0]);
                 QDate date = QDate::fromString(repetitionDates[0], "dd/MM/yyyy");
                 QString timesString = repetitionDates.join(", ");
                 editedHabit["times"] = timesString;
                 if (date > currentDate)
                     progressLineEdit->setText("Upcoming");
                 else{
                    progressLineEdit->setText("In progress");
                 }
                }
                else{
                    editHabitButton->click();
                }
            }

          if(progressLineEdit->text() == "In progress" && validate){
                upComingList.removeAt(position);
                position = upComingList.size() -1;
            }
            else{
                upComingList.append(habitWidget);
                position = upComingList.size() -1;
            }

            list[habitSetTitle] = editedHabit;
            jsonObj["list"] = list;
            file.resize(0);
            file.write(QJsonDocument(jsonObj).toJson());
            file.close();
            }
         }

        }

    });

    QObject::connect(doneHabitButton,&QPushButton::clicked, [=]() mutable {

        QString messageBoxStylesheet = "QMessageBox {"
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
                              "}";

        if(progressLineEdit->text() == "In progress"){
            QMessageBox msgBox;
                            msgBox.setWindowTitle("Achieved habit");
                            msgBox.setText("Have you successfully practiced this habit today?");
                            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                            msgBox.setDefaultButton(QMessageBox::No);
                            msgBox.setStyleSheet(messageBoxStylesheet);

      if (msgBox.exec() == QMessageBox::Yes) {

        progressLineEdit->setText("Upcoming");
        QString folderName = "savedHabits";
        QString fileName = QString("%1/habits.json").arg(folderName);
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){

            QByteArray data = file.readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString habitString = QString("Habit%1").arg(habitIndex);
            QJsonObject habitList = jsonObj["list"].toObject();
            QJsonObject editedHabit = habitList[habitString].toObject();

        QDate inputDate = QDate::fromString(dateLineEdit->text(), "dd/MM/yyyy");
        QDate outputDate = QDate();

        if(repetitionNameLineEdit->text() == "Daily")
            outputDate = inputDate.addDays(1);
        if(repetitionNameLineEdit->text() == "Weekly")
            outputDate = inputDate.addDays(7);
        if(repetitionNameLineEdit->text() == "Monthly")
            outputDate = inputDate.addMonths(1);
        if(repetitionNameLineEdit->text() == "Yearly")
            outputDate = inputDate.addYears(1);
        if(repetitionNameLineEdit->text() == "Custom"){

            QStringList futureDates;
            QStringList dateList = times.split(", ");
            foreach (const QString &date, dateList) {
                QDate inputDate = QDate::fromString(date, "dd/MM/yyyy");
                if(inputDate >= currentDate)
                    futureDates.append(date);
            }
            if(!futureDates.empty()){
            QString futureDatesStr = futureDates.join(", ");
            outputDate = QDate::fromString(futureDates[0], "dd/MM/yyyy");
            }
            else{
                habitWidget->deleteLater();
                habitList.remove(habitString);
            }
        }

        dateLineEdit->setText(outputDate.toString("dd/MM/yyyy"));
        editedHabit["times"] = outputDate.toString("dd/MM/yyyy");

        habitList[habitString] = editedHabit;
        jsonObj["list"] = habitList;
        file.resize(0);
        file.write(QJsonDocument(jsonObj).toJson());
        file.close();
      }
        habitsButton->click();
      }
        }
        else{
            QMessageBox errorBox;
            errorBox.setWindowTitle("Error");
            errorBox.setText("You can not practice an upcoming habit!");
            errorBox.setIcon(QMessageBox::Critical);
            errorBox.setStandardButtons(QMessageBox::Ok);
            errorBox.setStyleSheet(messageBoxStylesheet);
            errorBox.exec();

      }
    });

    habitsLayout->addWidget(habitWidget);

}
