#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class QNetworkReply;
class QSslNetAccessManager;
class QTableWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum Operation
    {
        Get,
        Post,
        Put,
        Delete
    };

    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
private slots:
    void requestFinished(QNetworkReply *reply);

    void on_getAllTarjetaCreditoButton_clicked();
    void on_addRecordButton_clicked();
    void on_editRecord_clicked();
    void on_deleteRecordButton_clicked();
    void on_tableTarjetaCredito_itemClicked(QTableWidgetItem *item);
private:
    void appendTarjetaCredito(int Id,
                                const QString &Titular,
                                const QString &FechaExpiracion,
                                const QString &NumeroTarjeta,
                                const QString &CVV);

    Ui::MainWindow *ui;
    int m_Id;
    Operation m_operation;
    QSslNetAccessManager *m_manager;
};

#endif // MAINWINDOW_H
