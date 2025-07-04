#pragma once

#include <QMainWindow>

class MainAppWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainAppWindow(QWidget* parent = nullptr);

private:
    void setupUI();
};