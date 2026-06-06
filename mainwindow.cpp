
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Ustawiamy rozmiar okna i tytuł
    resize(400, 300);
    setWindowTitle("Knitted Sweaters - Recenzje Filmowe");

    // Tworzymy przycisk
    button = new QPushButton("Wyświetl filmy", this);
    button->setGeometry(100, 100, 200, 50);
}

MainWindow::~MainWindow() {}