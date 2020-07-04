#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QMainWindow>
#include <string>
#include "clickablelable.h"
#include <QMqttClient>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MenuPrincipal; }
QT_END_NAMESPACE

class MenuPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();




private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_ComprarP1_clicked();
    void on_ComprarP2_clicked();
    void on_ComprarP3_clicked();
    void on_ComprarP4_clicked();

    void on_Regresar_clicked();

    void on_pushButton_clicked();

    void on_CompraFinal_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();
    string on_PName_returnPressed();

    string on_PFila_returnPressed();

    string on_SeleccionarCantidad_clicked();

    int on_SeleccionarPosicion_clicked();



    void on_Verificacion_clicked();


    void on_RevisarInventario_clicked();

    void on_pushButton_9_clicked();

    void on_revisarDisponibles_clicked();
    int countDistinct(string arr[], int n);
    int returnProductAmount(string diffs_name);

    void on_Menu_clicked();

    void on_regresarMain_clicked();

    void on_ResetInventory_clicked();

    void ImprimirProducto();


    void on_producto1_clicked();

    int returnCantidadDisponible(string nombre, int cant);
    void newValue(string Pnombre, int newvalue);
    void borrarImagenProducto(string Pname);


    void on_regresarAcantidad_clicked();

    void on_producto2_clicked();

    void on_producto3_clicked();

    void on_producto4_clicked();

    void on_producto5_clicked();

    void on_producto6_clicked();

    void on_producto7_clicked();

    void on_producto8_clicked();

    void on_producto9_clicked();

    void on_producto10_clicked();

    void on_producto11_clicked();

    void on_producto12_clicked();

    void on_producto13_clicked();

    void on_producto14_clicked();

    void on_producto15_clicked();

    void on_producto16_clicked();

    void on_producto17_clicked();

    void on_producto18_clicked();

    void on_producto19_clicked();

    void on_producto20_clicked();

    void on_producto21_clicked();

    void on_producto22_clicked();

    void on_producto23_clicked();

    void on_producto24_clicked();

    void on_producto25_clicked();

    void on_Broker_clicked();

    void brokerDisconnected();

    void on_Subscribe_clicked();



    void on_publish_clicked();
    void updateLogStateChange();
    void setClientPort(int p);
    void publishmessage(string message);

    void on_regresarMenu_clicked();

    void on_Connect_clicked();

    void on_regresarTemp_clicked();

    void on_tempdisplay_clicked();

private:
    Ui::MenuPrincipal *ui;
    QLabel* label_31;
    QLabel* label_32;
    QLabel* label_33;
    QLabel* label_34;
    QLabel* label_35;
    QLabel* label_36;
    QLabel* label_37;
    QLabel* label_38;
    QLabel* label_39;
    QLabel* label_40;
    QLabel* label_41;
    QLabel* label_42;
    QLabel* label_43;
    QLabel* label_44;
    QLabel* label_45;
    QLabel* label_46;
    QLabel* label_47;
    QLabel* label_48;
    QLabel* label_49;
    QLabel* label_50;
    QLabel* label_51;
    QLabel* label_52;
    QLabel* label_53;
    QLabel* label_54;
    QLabel* label_55;
    QMqttClient *m_client;
};
#endif // MENUPRINCIPAL_H
