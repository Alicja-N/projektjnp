
#include <QApplication>
#include "mainwindow.h"
#include "swetrki.h"

// Definicja globalnego storage (jeśli tu ma się znajdować)
VectorStorage storage;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Inicjalizacja Qt

    // Tutaj możesz zostawić swoją testową bazę:
    Film film1;
    film1.title = "Shrek";
    film1.keywords = "ogry,osioł,bagno";
    storage.SaveFilm(film1);

    // Tworzymy i pokazujemy okno
    MainWindow window;
    window.show();

    return app.exec(); // Uruchomienie pętli okienkowej
}
