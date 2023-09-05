#include <QDialog>
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QAbstractItemView>

class CalendarPopupDialog : public QDialog {
    Q_OBJECT
public:
    CalendarPopupDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Date");
        setFixedSize(300, 250);
        setStyleSheet("background-color: #071426;");

        QVBoxLayout *layout = new QVBoxLayout(this);

        calendarWidget = new QCalendarWidget(this);
        layout->addWidget(calendarWidget);

        QPushButton *okButton = new QPushButton("OK", this);
        okButton->setStyleSheet("color:white;background-color:#009ace;border:none;");
        layout->addWidget(okButton);

        QDate currentDate = QDate::currentDate();
           calendarWidget->setMinimumDate(QDate(currentDate.year(), 1, 1));
           calendarWidget->setMaximumDate(QDate(currentDate.year(), 12, 31));
           calendarWidget->setStyleSheet(calendarStylesheet);

        connect(okButton, &QPushButton::clicked, this, &CalendarPopupDialog::accept);
    }

    QDate getSelectedDate() const {
        return calendarWidget->selectedDate();
    }
    QDate showMonthlyRepetitionPopup() {
        QCalendarWidget *monthlyCalendarWidget = new QCalendarWidget(this);

        monthlyCalendarWidget->setGridVisible(true);
        monthlyCalendarWidget->setNavigationBarVisible(false);
        monthlyCalendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
        monthlyCalendarWidget->setStyleSheet(calendarStylesheet);
        monthlyCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        QDialog monthlyDialog(this);
        monthlyDialog.setWindowTitle("Select Monthly Repetition Day");
        monthlyDialog.setFixedSize(300, 250);

        QVBoxLayout *monthlyLayout = new QVBoxLayout(&monthlyDialog);
        monthlyLayout->addWidget(monthlyCalendarWidget);

        QPushButton *monthlyOkButton = new QPushButton("OK", &monthlyDialog);
        monthlyOkButton->setStyleSheet("color:white;background-color:#009ace;border:none;");
        monthlyLayout->addWidget(monthlyOkButton);

        connect(monthlyOkButton, &QPushButton::clicked, &monthlyDialog, &QDialog::accept);

        QDate currentDate = QDate::currentDate();

        QDate firstDayOfMonth(currentDate.year(), currentDate.month(), 1);
        monthlyCalendarWidget->setMinimumDate(firstDayOfMonth);

        QDate lastDayOfMonth(currentDate.year(), currentDate.month(), currentDate.daysInMonth());
        monthlyCalendarWidget->setMaximumDate(lastDayOfMonth);

        if (monthlyDialog.exec() == QDialog::Accepted) {
            return monthlyCalendarWidget->selectedDate();
        }

        return QDate();
    }

    QDate showWeeklyRepetitionPopup() {
        QDialog weeklyDialog(this);
        weeklyDialog.setWindowTitle("Select Weekly Repetition Day");
        weeklyDialog.setFixedSize(300, 150);

        QVBoxLayout *weeklyLayout = new QVBoxLayout(&weeklyDialog);

        QComboBox *dayOfWeekComboBox = new QComboBox(&weeklyDialog);
        dayOfWeekComboBox->addItem("Sunday");
        dayOfWeekComboBox->addItem("Monday");
        dayOfWeekComboBox->addItem("Tuesday");
        dayOfWeekComboBox->addItem("Wednesday");
        dayOfWeekComboBox->addItem("Thursday");
        dayOfWeekComboBox->addItem("Friday");
        dayOfWeekComboBox->addItem("Saturday");
        dayOfWeekComboBox->setStyleSheet(comboBoxStylesheet);
        dayOfWeekComboBox->view()->setStyleSheet(listViewStylesheet);

        weeklyLayout->addWidget(dayOfWeekComboBox);

        QPushButton *weeklyOkButton = new QPushButton("OK", &weeklyDialog);
        weeklyOkButton->setStyleSheet("color:white;background-color:#009ace;border:none;");
        weeklyLayout->addWidget(weeklyOkButton);
        connect(weeklyOkButton, &QPushButton::clicked, &weeklyDialog, &QDialog::accept);

        if (weeklyDialog.exec() == QDialog::Accepted) {
            int selectedDayIndex = dayOfWeekComboBox->currentIndex();
            if (selectedDayIndex >= 0 && selectedDayIndex < 7) {
                QDate currentDate = QDate::currentDate();
                QDate selectedDate = currentDate.addDays(selectedDayIndex - currentDate.dayOfWeek());
                if (selectedDate < currentDate) {
                    selectedDate = selectedDate.addDays(7);
                }

                return selectedDate;
            }
        }


        return QDate();
    }

    void customRepetitionPopup() {
        QDialog weeklyDialog(this);
        weeklyDialog.setWindowTitle("Custom Repetition");
        weeklyDialog.setFixedSize(300, 150);

        QVBoxLayout *customDialogLayout = new QVBoxLayout(&weeklyDialog);
    }




private:
    QCalendarWidget *calendarWidget;
    const   QString calendarStylesheet =
            "QCalendarWidget QToolButton {"
            "    height: 30px;"
            "    width: 80px;"
            "    color: white;"
            "    font-size: 12px;"
            "    icon-size: 16px, 16px;"
            "    background-color: #071426;"
            "}"
            "QCalendarWidget QMenu {"
            "    width: 150px;"
            "    left: 20px;"
            "    color: white;"
            "    font-size: 12px;"
            "    background-color: #071426;"
            "}"
            "QCalendarWidget QSpinBox {"
            "    width: 80px;"
            "    font-size: 12px;"
            "    color: white;"
            "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #cccccc, stop: 1 #333333);"
            "    selection-background-color: #071426;"
            "    selection-color: #009ace;"
            "}"
            "QCalendarWidget QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; width: 16px; }"
            "QCalendarWidget QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; width: 16px; }"
            "QCalendarWidget QSpinBox::up-arrow { width: 16px; height: 16px; }"
            "QCalendarWidget QSpinBox::down-arrow { width: 16px; height: 16px; }"
            "QCalendarWidget QWidget { alternate-background-color: #071426; }"
            "QCalendarWidget QAbstractItemView:enabled {"
            "    font-size: 12px;"
            "    color: white;"
            "    background-color: #071426;"
            "    selection-background-color: #071426;"
            "    selection-color: #009ace;"
            "}"
            "QCalendarWidget QWidget#qt_calendar_navigationbar {"
            "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #cccccc, stop: 1 #333333);"
            "}"
            "QCalendarWidget QAbstractItemView:disabled {"
            "    color: rgb(100, 100, 100);;"
            "}";
    const        QString comboBoxStylesheet = "QComboBox {"
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
     const          QString listViewStylesheet = "QListView {"
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
};
