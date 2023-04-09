#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupGame();

private slots:
    void ButtonCliked();
    void TimerTick();

private:
    Ui::MainWindow *ui;
    int matchesfound;
    int tenthsOfSecondsElapsed;
    QTimer* timer;
    QPushButton* lastEmojiClicked;
    bool finding_match;
};
#endif // MAINWINDOW_H
