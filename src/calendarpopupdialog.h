#include <QDialog>
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>

class CalendarPopupDialog : public QDialog {
    Q_OBJECT
public:
    CalendarPopupDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Yearly Date");
        setFixedSize(300, 250);

        QVBoxLayout *layout = new QVBoxLayout(this);

        calendarWidget = new QCalendarWidget(this);
        layout->addWidget(calendarWidget);

        QPushButton *okButton = new QPushButton("OK", this);
        layout->addWidget(okButton);

        QDate currentDate = QDate::currentDate();
           calendarWidget->setMinimumDate(QDate(currentDate.year(), 1, 1));
           calendarWidget->setMaximumDate(QDate(currentDate.year(), 12, 31));

           QToolBar *navBar = calendarWidget->findChild<QToolBar*>("qt_calendar_navigationbar");
           if (navBar) {
               QWidget *yearButton = navBar->findChild<QWidget*>("qt_calendar_yearbutton");
               if (yearButton) {
                   yearButton->setVisible(false);
               }
           }

        connect(okButton, &QPushButton::clicked, this, &CalendarPopupDialog::accept);
    }

    QDate getSelectedDate() const {
        return calendarWidget->selectedDate();
    }

private:
    QCalendarWidget *calendarWidget;
};
