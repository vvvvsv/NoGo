#ifndef HELPSENSE_H
#define HELPSENSE_H

#include <QMainWindow>

class HelpSense : public QMainWindow
{
    Q_OBJECT
public:
    explicit HelpSense(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
signals:
    void backToMenu();

public slots:
};

#endif // HELPSENSE_H
