#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qsslnetrequest.h"
#include "qsslnetaccessmanager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_manager = new QSslNetAccessManager(this);
    connect(m_manager, &QSslNetAccessManager::finished, this, &MainWindow::requestFinished);

    ui->tableTarjetaCredito->setSelectionBehavior(QTableWidget::SelectRows);
    ui->tableTarjetaCredito->setSelectionMode(QTableWidget::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::requestFinished(QNetworkReply *reply)
{
    const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "statusCode:" << statusCode;
    qDebug() << "error enum:" << reply->error();
    qDebug() << "error string:" << reply->errorString();
    QByteArray responseData = reply->readAll();
    qDebug() << "read-all:" << responseData;
    if (m_operation == Get)
    {
        ui->tableTarjetaCredito->setRowCount(0);
        QJsonArray array = QJsonDocument::fromJson(responseData).array();
        for (const QJsonValue &value : array)
        {
            QJsonObject tarjetaCredito = value.toObject();
            appendTarjetaCredito(tarjetaCredito.value("id").toInt(),
                                 tarjetaCredito.value("titular").toString(),
                                 tarjetaCredito.value("fechaExpiracion").toString(),
                                 tarjetaCredito.value("numeroTarjeta").toString(),
                                 tarjetaCredito.value("cvv").toString());
        }
    }
    else if (m_operation == Post)
    {
        on_getAllTarjetaCreditoButton_clicked();
    }
    else if (m_operation == Put)
    {
        on_getAllTarjetaCreditoButton_clicked();
    }
    else if (m_operation == Delete)
    {
        on_getAllTarjetaCreditoButton_clicked();
    }
}

void MainWindow::on_getAllTarjetaCreditoButton_clicked()
{
    m_operation = Get;
    m_manager->get(QSslNetRequest(QUrl("https://localhost:7211/tarjetacredito")));
}

void MainWindow::on_addRecordButton_clicked()
{
    m_operation = Post;
    QString titular = ui->txtTitular->text();
    QString fechaExpiracion = ui->txtFechaExpiracion->text();
    QString numeroTarjeta = ui->txtNumeroTarjeta->text();
    QString cvv = ui->txtCVV->text();
    QString json = QString("{'Titular':'%1','FechaExpiracion':'%2','NumeroTarjeta':'%3','CVV':'%4'}")
                           .arg(titular, fechaExpiracion, numeroTarjeta, cvv);
    json = json.replace("'", "\"");
    QByteArray postData = json.toUtf8();
    m_manager->post(QSslNetRequest(QUrl("https://localhost:7211/tarjetacredito")), postData);
}

void MainWindow::on_editRecord_clicked()
{
    m_operation = Put;
    QString titular = ui->txtTitular->text();
    QString fechaExpiracion = ui->txtFechaExpiracion->text();
    QString numeroTarjeta = ui->txtNumeroTarjeta->text();
    QString cvv = ui->txtCVV->text();
    QString json = QString("{'Id':%1,'Titular':'%2','FechaExpiracion':'%3','NumeroTarjeta':'%4','CVV':'%5'}")
                           .arg(m_Id).arg(titular).arg(fechaExpiracion).arg(numeroTarjeta).arg(cvv);
    json = json.replace("'", "\"");
    QByteArray putData = json.toUtf8();
    m_manager->put(QSslNetRequest(QUrl(QString("https://localhost:7211/tarjetacredito/%1").arg(m_Id))), putData);
}

void MainWindow::on_deleteRecordButton_clicked()
{
    m_operation = Delete;
    QIODevice *ptr = nullptr;
    m_manager->post(QSslNetRequest(QUrl(QString("https://localhost:7211/tarjetacredito/eliminar/%1").arg(m_Id))), ptr);
}

void MainWindow::on_tableTarjetaCredito_itemClicked(QTableWidgetItem *item)
{
    const int row = item->row();
    m_Id = ui->tableTarjetaCredito->item(row, 0)->text().toInt();
    QString Titular = ui->tableTarjetaCredito->item(row, 1)->text();
    QString FechaExpiracion = ui->tableTarjetaCredito->item(row, 2)->text();
    QString NumeroTarjeta = ui->tableTarjetaCredito->item(row, 3)->text();
    QString CVV = ui->tableTarjetaCredito->item(row, 4)->text();
    ui->txtTitular->setText(Titular);
    ui->txtFechaExpiracion->setText(FechaExpiracion);
    ui->txtNumeroTarjeta->setText(NumeroTarjeta);
    ui->txtCVV->setText(CVV);
}

void MainWindow::appendTarjetaCredito(int Id,
                                        const QString &Titular,
                                        const QString &FechaExpiracion,
                                        const QString &NumeroTarjeta,
                                        const QString &CVV)
{
    const int row = ui->tableTarjetaCredito->rowCount();
    ui->tableTarjetaCredito->insertRow(row);
    ui->tableTarjetaCredito->setItem(row, 0, new QTableWidgetItem(QString::number(Id)));
    ui->tableTarjetaCredito->setItem(row, 1, new QTableWidgetItem(Titular));
    ui->tableTarjetaCredito->setItem(row, 2, new QTableWidgetItem(FechaExpiracion));
    ui->tableTarjetaCredito->setItem(row, 3, new QTableWidgetItem(NumeroTarjeta));
    ui->tableTarjetaCredito->setItem(row, 4, new QTableWidgetItem(CVV));
}





