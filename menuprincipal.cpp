#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include <QPixmap>
#include <QMessageBox>
#include "slots.h"
#include <iostream>
#include <QTextStream>
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include <algorithm>
#include<functional>
#include<set>
#include "clickablelable.h"
#include <QtGui>
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <stdio.h>
#include <stdlib.h>




using namespace  std;



int id;
string Nombre[25];
int PCant[25];
string diffs_name[25];
string printproducts[25] = {"Coca Cola" ,"Coca Zero" ,"Imperial" ,"Pilsen" ,"GingerAle" ,"Powerade Azul" ,"Powerade Rojo" ,"Gatorade Azul" ,"Gatorade Rojo" ,"7 UP" ,"Root Beer" ,"Coca Light" ,"Agua" ,"Fanta Naranja" ,"Fanta Uva" ,"Fanta Azul" ,"Fanta Kolita" ,"Te Frio" ,"Evervess" ,"Vainilla" ,"Chocolate" ,"Fresa" ,"Pepsi" ,"Pepsi Light" ,"Imperial Ultra" };


struct Slot_Info
{
    string ProductName = "No Product";
    string Slotid = "Not Used";
    int ProductCount = 0;
};

/// Declaracion de arreglo de Pilas
struct Slot_Info Pilas[25];



MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);

    m_client = new QMqttClient(this);
    m_client->setHostname(ui->lineEditHost->text());
    m_client->setPort(ui->spinBoxPort->value());

    connect(m_client, &QMqttClient::stateChanged, this, &MenuPrincipal::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MenuPrincipal::brokerDisconnected);

    // Conectarse al host
    connect(ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MenuPrincipal::setClientPort);
    updateLogStateChange();

    // Conectarse a respuesta de ping
    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
            const QString content = QDateTime::currentDateTime().toString()
                        + QLatin1String(" PingResponse")
                        + QLatin1Char('\n');
            string ping = content.toStdString();
            cout<<"Repuesta ping: "<<ping<<endl;
        });

   // label_31 = new ClickableLabel("",this);
   // connect(label_31,SIGNAL(clicked()),this,SLOT(ui->stackedWidget->setCurrentIndex(4)));
    ui->stackedWidget->setCurrentIndex(2);

   /*
    * ui->label->setPixmap(coke);
    ui->label_2->setPixmap(coke_zero);
    ui->label_3->setPixmap(imperial);
    ui->label_4->setPixmap(pilsen);
*/

}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}


void MenuPrincipal::ImprimirProducto()
{
    QPixmap coke("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/coke.png");
    QPixmap coke_zero("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/coke_zero.png");
    QPixmap imperial("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/imperial.png");
    QPixmap pilsen("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/pilsen.png");
    QPixmap ginger("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/ginger.png");
    QPixmap seveup("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/7up.png");
    QPixmap agua("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/agua.png");
    QPixmap bluegatorade("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/bluegatorade.png");
    QPixmap bluepower("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/bluepower.png");
    QPixmap chocolate("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/chocolate.png");
    QPixmap cocalight("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/cocalight.png");
    QPixmap evervess("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/evervess.png");
    QPixmap fantaazul("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantaazul.png");
    QPixmap fantakolita("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantakolita.png");
    QPixmap fantanaranja("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantanaranja.png");
    QPixmap fantauva("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantauva.png");
    QPixmap fresa("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fresa.png");
    QPixmap pepsi("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/pepsi.png");
    QPixmap pepsilight("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/pepsilight.png");
    QPixmap redgatorade("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/redgatorade.png");
    QPixmap redpower("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/redpower.png");
    QPixmap root("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/root.png");
    QPixmap tefrio("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/tefrio.png");
    QPixmap ultra("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/ultra.png");
    QPixmap vainilla("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/vainilla.png");

    QIcon Coke(coke);
    QIcon Zero(coke_zero);
    QIcon Imperial(imperial);
    QIcon Pilsen(pilsen);
    QIcon Ginger(ginger);
    QIcon Sevenup(seveup);
    QIcon Agua(agua);
    QIcon BlueGatorade(bluegatorade);
    QIcon BluePowerade(bluepower);
    QIcon Chocolate(chocolate);
    QIcon CocaLight(cocalight);
    QIcon Evervess(evervess);
    QIcon FantaAzul(fantaazul);
    QIcon FantaKolita(fantakolita);
    QIcon FantaNaranja(fantanaranja);
    QIcon FantaUva(fantauva);
    QIcon Fresa(fresa);
    QIcon Pepsi(pepsi);
    QIcon PepsiLight(pepsilight);
    QIcon RedGatorade(redgatorade);
    QIcon RedPowerade(redpower);
    QIcon Root(root);
    QIcon TeFrio(tefrio);
    QIcon Ultra(ultra);
    QIcon Vainilla(vainilla);

   for (int i = 0;i<25;i++) {
        string s = Pilas[i].ProductName;
        if (s == printproducts[0])
        {
            ui->producto1->setIcon(Coke);
            ui->producto1->setIconSize(coke.rect().size());
            ui->name01->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[1])
        {
            ui->producto2->setIcon(Zero);
            ui->producto2->setIconSize(coke_zero.rect().size());
            ui->name02->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[2])
        {
            ui->producto3->setIcon(Imperial);
            ui->producto3->setIconSize(imperial.rect().size());
            ui->name03->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[3])
        {
            ui->producto4->setIcon(Pilsen);
            ui->producto4->setIconSize(pilsen.rect().size());
            ui->name04->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[4])
        {
            ui->producto5->setIcon(Ginger);
            ui->producto5->setIconSize(ginger.rect().size());
            ui->name05->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[5])
        {
            ui->producto6->setIcon(BluePowerade);
            ui->producto6->setIconSize(bluepower.rect().size());
            ui->name06->setText(QString::fromUtf8(s.c_str()));
        }

        if (s == printproducts[6])
        {
            ui->producto7->setIcon(RedPowerade);
            ui->producto7->setIconSize(redpower.rect().size());
            ui->name07->setText(QString::fromUtf8(s.c_str()));
        }

        if (s == printproducts[7])
        {
            ui->producto8->setIcon(BlueGatorade);
            ui->producto8->setIconSize(bluegatorade.rect().size());
            ui->name08->setText(QString::fromUtf8(s.c_str()));
        }

        if (s == printproducts[8])
        {
            ui->producto9->setIcon(RedGatorade);
            ui->producto9->setIconSize(redgatorade.rect().size());
            ui->name09->setText(QString::fromUtf8(s.c_str()));
        }

        if (s == printproducts[9])
        {
            ui->producto10->setIcon(Sevenup);
            ui->producto10->setIconSize(seveup.rect().size());
            ui->name10->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[10])
        {
            ui->producto11->setIcon(Root);
            ui->producto11->setIconSize(root.rect().size());
            ui->name11->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[11])
        {
            ui->producto12->setIcon(CocaLight);
            ui->producto12->setIconSize(cocalight.rect().size());
            ui->name12->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[12])
        {
            ui->producto13->setIcon(Agua);
            ui->producto13->setIconSize(agua.rect().size());
            ui->name13->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[13])
        {
            ui->producto14->setIcon(FantaNaranja);
            ui->producto14->setIconSize(fantanaranja.rect().size());
            ui->name14->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[14])
        {
            ui->producto15->setIcon(FantaUva);
            ui->producto15->setIconSize(fantauva.rect().size());
            ui->name15->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[15])
        {
            ui->producto16->setIcon(FantaAzul);
            ui->producto16->setIconSize(fantaazul.rect().size());
            ui->name16->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[16])
        {
            ui->producto17->setIcon(FantaKolita);
            ui->producto17->setIconSize(fantakolita.rect().size());
            ui->name17->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[17])
        {
            ui->producto18->setIcon(TeFrio);
            ui->producto18->setIconSize(tefrio.rect().size());
            ui->name18->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[18])
        {
            ui->producto19->setIcon(Evervess);
            ui->producto19->setIconSize(evervess.rect().size());
            ui->name19->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[19])
        {
            ui->producto20->setIcon(Vainilla);
            ui->producto20->setIconSize(vainilla.rect().size());
            ui->name20->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[20])
        {
            ui->producto21->setIcon(Chocolate);
            ui->producto21->setIconSize(chocolate.rect().size());
            ui->name21->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[21])
        {
            ui->producto22->setIcon(Fresa);
            ui->producto22->setIconSize(fresa.rect().size());
            ui->name22->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[22])
        {
            ui->producto23->setIcon(Pepsi);
            ui->producto23->setIconSize(pepsi.rect().size());
            ui->name23->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[23])
        {
            ui->producto24->setIcon(PepsiLight);
            ui->producto24->setIconSize(pepsilight.rect().size());
            ui->name24->setText(QString::fromUtf8(s.c_str()));
        }
        if (s == printproducts[24])
        {
            ui->producto25->setIcon(Ultra);
            ui->producto25->setIconSize(ultra.rect().size());
            ui->name25->setText(QString::fromUtf8(s.c_str()));
        }


        else;


    }
}

int MenuPrincipal::countDistinct(string arr[], int n)
{
    sort(arr, arr+n);
    int res=0;
    for (int i=0;i<n;i++) {
        while(i< n -1 && arr[i] == arr[i+1])
            i++;
        res++;

    }
    return res;
}

int MenuPrincipal::returnProductAmount(string diffs_name)
{
    int cuenta = 0;
          for (int vars = 0; vars  < 25; ++vars ) {
                if(diffs_name == Nombre[vars])
                {
                    int counter = Pilas[vars].ProductCount;
                    cuenta = counter;
                    cout<<"Producto: "<<diffs_name<<", cantidad: "<<Pilas[vars].ProductCount<<endl;
                }
                else;
            }
          return cuenta;

 }

int MenuPrincipal::returnCantidadDisponible(string nombre, int cant)
{
    int p1;
    for (int i = 0;i<25;i++)
    {
        if (nombre == Pilas[i].ProductName)
        {
            p1 = p1+Pilas[i].ProductCount;
        }
    }
    return p1 - cant;
}

void MenuPrincipal::newValue(string Pnombre, int cantidad_requerida)
{
    string su[25];
    int contador;
    //revisar los slots que tienen
    for (int i = 0 ;i<25;i++) {

        if (Pnombre == Pilas[i].ProductName)
        {
            contador++;
            string pid = Pilas[i].Slotid;
            int stock = Pilas[i].ProductCount;
            Pilas[i].ProductCount = stock - cantidad_requerida;
            cout<<Pilas[i].ProductCount<<endl;
            if(Pilas[i].ProductCount == 0)
            {
                borrarImagenProducto(Pnombre);
                Pilas[i].ProductName = "No Product";
                Pilas[i].Slotid = "Not Used";
                Nombre[i] = "";
                cout<<"Se borro el nombre del producto "<<Nombre[i]<<endl;
                string mensaje = "Estado de Pila " +pid + ": Vacia";
                publishmessage(mensaje);
                on_publish_clicked();
            }
            if(Pilas[i].ProductCount < 0)
            {

                cantidad_requerida = -Pilas[i].ProductCount;
                Pilas[i].ProductCount = 0;
                Pilas[i].ProductName = "No Product";
                Pilas[i].Slotid = "Not Used";
                string mensaje = "Estado de Pila " + pid + ": Vacia";
                publishmessage(mensaje);
                on_publish_clicked();

                continue;

            }
            if(Pilas[i].ProductCount >= 0)
            {
                cout<<"Slot: "<<Pilas[i].Slotid<<" | Disponible: "<<stock-cantidad_requerida<<" | Producto: "<<Pnombre<<endl;
                break;
            }

        }
        else;

    }
    //cout<<"Cantidad de slots con "<<Pnombre<<" : "<<contador<<endl;
}

// Funcion para borrar las imagenes de los productos que ya no tienen cantidad disponible
void MenuPrincipal::borrarImagenProducto(string Pname)
{
    if(Pname == "Coca Cola")
    {
        ui->producto1->setIcon(QIcon());
        ui->name01->setText("");

    }
    if(Pname == "Coca Zero")
    {
        ui->producto2->setIcon(QIcon());
        ui->name02->setText("");
    }
    if(Pname == "Imperial")
    {
        ui->producto3->setIcon(QIcon());
        ui->name03->setText("");
    }
    if(Pname == "Pilsen")
    {
        ui->producto4->setIcon(QIcon());
        ui->name04->setText("");
    }
    if(Pname == "GingerAle")
    {
        ui->producto5->setIcon(QIcon());
        ui->name05->setText("");
    }
    if(Pname == "Powerade Azul")
    {
        ui->producto6->setIcon(QIcon());
        ui->name06->setText("");
    }
    if(Pname == "Powerade Rojo")
    {
        ui->producto7->setIcon(QIcon());
        ui->name07->setText("");
    }
    if(Pname == "Gatorade Azul")
    {
        ui->producto8->setIcon(QIcon());
        ui->name08->setText("");
    }
    if(Pname == "Gatorade Rojo")
    {
        ui->producto9->setIcon(QIcon());
        ui->name09->setText("");
    }
    if(Pname == "7 UP")
    {
        ui->producto10->setIcon(QIcon());
        ui->name10->setText("");
    }
    if(Pname == "Root Beer")
    {
        ui->producto11->setIcon(QIcon());
        ui->name11->setText("");
    }
    if(Pname == "Coca Light")
    {
        ui->producto12->setIcon(QIcon());
        ui->name12->setText("");
    }
    if(Pname == "Agua")
    {
        ui->producto13->setIcon(QIcon());
        ui->name13->setText("");
    }
    if(Pname == "Fanta Naranja")
    {
        ui->producto14->setIcon(QIcon());
        ui->name14->setText("");
    }
    if(Pname == "Fanta Uva")
    {
        ui->producto15->setIcon(QIcon());
        ui->name15->setText("");
    }
    if(Pname == "Fanta Azul")
    {
        ui->producto16->setIcon(QIcon());
        ui->name16->setText("");
    }
    if(Pname == "Fanta Kolita")
    {
        ui->producto17->setIcon(QIcon());
        ui->name17->setText("");
    }
    if(Pname == "Te Frio")
    {
        ui->producto18->setIcon(QIcon());
        ui->name18->setText("");
    }
    if(Pname == "Evervess")
    {
        ui->producto19->setIcon(QIcon());
        ui->name19->setText("");
    }
    if(Pname == "Vainilla")
    {
        ui->producto20->setIcon(QIcon());
        ui->name20->setText("");
    }
    if(Pname == "Chocolate")
    {
        ui->producto21->setIcon(QIcon());
        ui->name21->setText("");
    }
    if(Pname == "Fresa")
    {
        ui->producto22->setIcon(QIcon());
        ui->name22->setText("");
    }
    if(Pname == "Pepsi")
    {
        ui->producto23->setIcon(QIcon());
        ui->name23->setText("");
    }
    if(Pname == "Pepsi Light")
    {
        ui->producto24->setIcon(QIcon());
        ui->name24->setText("");
    }
    if(Pname == "Imperial Ultra")
    {
        ui->producto25->setIcon(QIcon());
        ui->name25->setText("");
    }
    string mensaje = "No hay mas " + Pname + " disponible en la maquina";
    cout<<mensaje<<endl;
    publishmessage(mensaje);
    on_publish_clicked();




}

void MenuPrincipal::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MenuPrincipal::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MenuPrincipal::on_ComprarP1_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MenuPrincipal::on_ComprarP2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MenuPrincipal::on_ComprarP3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MenuPrincipal::on_ComprarP4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}



void MenuPrincipal::on_Regresar_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MenuPrincipal::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MenuPrincipal::on_CompraFinal_clicked()
{
    QString cantProducto = ui->spinBox->cleanText();
    QString slotid = ui->SlotID->text();
    int cant = cantProducto.toInt();
    QString pnombre = ui->nombreBebida->text();
    string pname = pnombre.toStdString();
    cout<<pname<<endl;
    int available = returnCantidadDisponible(pname, 0);
    cout<<"Cantidad disponible "<<available<<endl;
    cout<<"La cantidad requerida: "<<cant<<endl;

    if (available >= cant)
    {
        //int ProductoRestante = returnCantidadDisponible(pname,available);
        cout<<"Producto Restante :"<<available-cant<<endl;
        newValue(pname,cant);
        string cantidad = to_string(cant);
        string mensaje = "Se compro " + cantidad+ " unidad(es) de " + pname;
        publishmessage(mensaje);
        on_publish_clicked();
        ui->quantity->setText(ui->spinBox->cleanText());
        ui->stackedWidget->setCurrentIndex(5);

    }
    if (available < cant)
    {
        ui->stackedWidget->setCurrentIndex(8);
    }


}

void MenuPrincipal::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MenuPrincipal::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Funcion de finalizar ingreso de producto
void MenuPrincipal::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QString PN = ui->PName->text();
    string p_name = PN.toStdString();

}

string MenuPrincipal::on_PName_returnPressed()
{
    QString ProName = ui->PName->text();
    string Pname = ProName.toStdString();
    QMessageBox P_Name;
    P_Name.setText(ProName);
    P_Name.exec();
    return Pname;
}

string MenuPrincipal::on_PFila_returnPressed()
{
    QString ProFila = ui->PFila->text();
    string pfila = ProFila.toStdString();
    QMessageBox P_Fila;
    P_Fila.setText(ProFila);
    P_Fila.exec();
    return pfila;
}

string MenuPrincipal::on_SeleccionarCantidad_clicked()
{
    QString ProCantidad = ui->PCantidad->text();
    string pcantidad = ProCantidad.toStdString();
    QMessageBox P_Cantidad;
    P_Cantidad.setText(ProCantidad);
    P_Cantidad.exec();
    return pcantidad;
}

// FUNCION QUE LLENA LA INFORMACION DEL INVENTARIO EN LAS PILAS
int MenuPrincipal::on_SeleccionarPosicion_clicked()
{
    QString PName = ui->PName->text();
    QString PCount = ui->PCantidad->text();
    QString ProColumna = ui->PColumna->text();
    QString ProFila = ui->PFila->text();

    string Pname = PName.toStdString();
    string Pcount = PCount.toStdString();
    string pcolumna = ProColumna.toStdString();
    string pfila = ProFila.toStdString();

    pfila.append(pcolumna);

    QString Posicion = QString::fromUtf8(pfila.c_str());

    int Cantidad = stoi(Pcount);


    ui->SlotPosition->setText(Posicion);


    // Impresion
    cout<<"Informacion ingresada en pila: "<<pfila<<endl;



    if (pfila == "A1")
        {
            Pilas[0].ProductName = Pname;
            Pilas[0].Slotid = "A1";
            Pilas[0].ProductCount = Cantidad;
            Nombre[0] = Pname;
            PCant[0] = Cantidad;
            return 0;
        }

        if (pfila == "A2")
        {
            Pilas[1].ProductName = Pname;
            Pilas[1].Slotid = "A2";
            Pilas[1].ProductCount = Cantidad;
            Nombre[1] = Pname;
            PCant[0] = Cantidad;
            return 1;
        }

        if (pfila == "A3")
        {
            Pilas[2].ProductName = Pname;
            Pilas[2].Slotid = "A3";
            Pilas[2].ProductCount = Cantidad;
            Nombre[2] = Pname;
            PCant[0] = Cantidad;
            return 2;
        }

        if (pfila == "A4")
        {
            Pilas[3].ProductName = Pname;
            Pilas[3].Slotid = "A4";
            Pilas[3].ProductCount = Cantidad;
            Nombre[3] = Pname;
            PCant[3] = Cantidad;
            return 3;
        }

        if (pfila == "A5")
        {
            Pilas[4].ProductName = Pname;
            Pilas[4].Slotid = "A5";
            Pilas[4].ProductCount = Cantidad;
            Nombre[4] = Pname;
            PCant[4] = Cantidad;
            return 4;
        }

        // FILA B

        if (pfila == "B1")
        {
            Pilas[5].ProductName = Pname;
            Pilas[5].Slotid = "B1";
            Pilas[5].ProductCount = Cantidad;
            Nombre[5] = Pname;
            PCant[5] = Cantidad;
            return 5;
        }

        if (pfila == "B2")
        {
            Pilas[6].ProductName = Pname;
            Pilas[6].Slotid = "B2";
            Pilas[6].ProductCount = Cantidad;
            Nombre[6] = Pname;
            PCant[6] = Cantidad;
            return 6;
        }

        if (pfila == "B3")
        {
            Pilas[7].ProductName = Pname;
            Pilas[7].Slotid = "B3";
            Pilas[7].ProductCount = Cantidad;
            Nombre[7] = Pname;
            PCant[7] = Cantidad;
            return 7;
        }

        if (pfila == "B4")
        {
            Pilas[8].ProductName = Pname;
            Pilas[8].Slotid = "B4";
            Pilas[8].ProductCount = Cantidad;
            Nombre[8] = Pname;
            PCant[8] = Cantidad;
            return 8;
        }

        if (pfila == "B5")
        {
            Pilas[9].ProductName = Pname;
            Pilas[9].Slotid = "B5";
            Pilas[9].ProductCount = Cantidad;
            Nombre[9] = Pname;
            PCant[9] = Cantidad;
            return 9;
        }

        // FILA C

        if (pfila == "C1")
        {
            Pilas[10].ProductName = Pname;
            Pilas[10].Slotid = "C1";
            Pilas[10].ProductCount = Cantidad;
            Nombre[10] = Pname;
            PCant[10] = Cantidad;
            return 10;
        }

        if (pfila == "C2")
        {
            Pilas[11].ProductName = Pname;
            Pilas[11].Slotid = "C2";
            Pilas[11].ProductCount = Cantidad;
            Nombre[11] = Pname;
            PCant[11] = Cantidad;
            return 11;
        }

        if (pfila == "C3")
        {
            Pilas[12].ProductName = Pname;
            Pilas[12].Slotid = "C3";
            Pilas[12].ProductCount = Cantidad;
            Nombre[12] = Pname;
            PCant[12] = Cantidad;
            return 12;
        }

        if (pfila == "C4")
        {
            Pilas[13].ProductName = Pname;
            Pilas[13].Slotid = "C4";
            Pilas[13].ProductCount = Cantidad;
            Nombre[13] = Pname;
            PCant[13] = Cantidad;
            return 13;
        }

        if (pfila == "C5")
        {
            Pilas[14].ProductName = Pname;
            Pilas[14].Slotid = "C5";
            Pilas[14].ProductCount = Cantidad;
            Nombre[14] = Pname;
            PCant[14] = Cantidad;
            return 14;
        }

        // FILA D

        if (pfila == "D1")
        {
            Pilas[15].ProductName = Pname;
            Pilas[15].Slotid = "D1";
            Pilas[15].ProductCount = Cantidad;
            Nombre[15] = Pname;
            PCant[15] = Cantidad;
            return 15;
        }

        if (pfila == "D2")
        {
            Pilas[16].ProductName = Pname;
            Pilas[16].Slotid = "D2";
            Pilas[16].ProductCount = Cantidad;
            Nombre[16] = Pname;
            PCant[16] = Cantidad;
            return 16;
        }

        if (pfila == "D3")
        {
            Pilas[17].ProductName = Pname;
            Pilas[17].Slotid = "D3";
            Pilas[17].ProductCount = Cantidad;
            Nombre[17] = Pname;
            PCant[17] = Cantidad;
            return 17;
        }

        if (pfila == "D4")
        {
            Pilas[18].ProductName = Pname;
            Pilas[18].Slotid = "D4";
            Pilas[18].ProductCount = Cantidad;
            Nombre[18] = Pname;
            PCant[18] = Cantidad;
            return 18;
        }

        if (pfila == "D5")
        {
            Pilas[19].ProductName = Pname;
            Pilas[19].Slotid = "D5";
            Pilas[19].ProductCount = Cantidad;
            Nombre[19] = Pname;
            PCant[19] = Cantidad;
            return 19;
        }

        // FILA E

        if (pfila == "E1")
        {
            Pilas[20].ProductName = Pname;
            Pilas[20].Slotid = "E1";
            Pilas[20].ProductCount = Cantidad;
            Nombre[20] = Pname;
            PCant[20] = Cantidad;
            return 20;
        }

        if (pfila == "E2")
        {
            Pilas[21].ProductName = Pname;
            Pilas[21].Slotid = "E2";
            Pilas[21].ProductCount = Cantidad;
            Nombre[21] = Pname;
            PCant[21] = Cantidad;
            return 21;
        }

        if (pfila == "E3")
        {
            Pilas[22].ProductName = Pname;
            Pilas[22].Slotid = "E3";
            Pilas[22].ProductCount = Cantidad;
            Nombre[22] = Pname;
            PCant[22] = Cantidad;
            return 22;
        }

        if (pfila == "E4")
        {
            Pilas[23].ProductName = Pname;
            Pilas[23].Slotid = "E4";
            Pilas[23].ProductCount = Cantidad;
            Nombre[23] = Pname;
            PCant[23] = Cantidad;
            return 23;
        }

        if (pfila == "E5")
        {
            Pilas[24].ProductName = Pname;
            Pilas[24].Slotid = "E5";
            Pilas[24].ProductCount = Cantidad;
            Nombre[24] = Pname;
            PCant[24] = Cantidad;
            return 24;
    }
    else{
        return 0;
    }


    /*Slots slot_id(pfila,pcolumna);


    string pile_id = slot_id.SlotAssign(pfila,pcolumna);

    Slots pile_info(pile_id);

    int pile_number;

    */
    QMessageBox P_Columna;
    P_Columna.setText(Posicion);
    P_Columna.exec();


}


void MenuPrincipal::on_Verificacion_clicked()
{
    id = on_SeleccionarPosicion_clicked();
    string PN = Pilas[id].ProductName;
    int PC =Pilas[id].ProductCount;
    string sid = Pilas[id].Slotid;

    // Convsersion de int quint
    quint8 pc = PC;
    PC = pc;
    // Conversion de int a Qstring
    QString p_c = QString::number(PC);
    QString SID = QString::fromUtf8(sid.c_str());
    QString Pro_name = QString::fromUtf8(PN.c_str());

    ui->SlotCantidad->setText(p_c);
    ui->SlotName->setText(Pro_name);
    ui->SlotID->setText(SID);

    int pamount = returnCantidadDisponible(PN,0);
    cout<<"Cantidad Disponible :"<<pamount<<endl;
    string mensaje = "Se ingreso " + to_string(PC) + " unidades de " + PN + " en la pila " + sid;
    publishmessage(mensaje);
    on_publish_clicked();
    on_revisarDisponibles_clicked();

}


// Funcion para mostrar los slots con su respectivo material

void MenuPrincipal::on_RevisarInventario_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);

    // Stock Primera fila
    ui->A1_pos->setText(QString::fromUtf8(Pilas[0].Slotid.c_str()));
    ui->A1_name->setText(QString::fromUtf8(Pilas[0].ProductName.c_str()));
    ui->A1_count->setText(QString::number(Pilas[0].ProductCount));
    ui->A1_pos_2->setText(QString::fromUtf8(Pilas[1].Slotid.c_str()));
    ui->A1_name_2->setText(QString::fromUtf8(Pilas[1].ProductName.c_str()));
    ui->A1_count_2->setText(QString::number(Pilas[1].ProductCount));
    ui->A1_pos_3->setText(QString::fromUtf8(Pilas[2].Slotid.c_str()));
    ui->A1_name_3->setText(QString::fromUtf8(Pilas[2].ProductName.c_str()));
    ui->A1_count_3->setText(QString::number(Pilas[2].ProductCount));
    ui->A1_pos_4->setText(QString::fromUtf8(Pilas[3].Slotid.c_str()));
    ui->A1_name_4->setText(QString::fromUtf8(Pilas[3].ProductName.c_str()));
    ui->A1_count_4->setText(QString::number(Pilas[3].ProductCount));
    ui->A1_pos_5->setText(QString::fromUtf8(Pilas[4].Slotid.c_str()));
    ui->A1_name_5->setText(QString::fromUtf8(Pilas[4].ProductName.c_str()));
    ui->A1_count_5->setText(QString::number(Pilas[4].ProductCount));

    // Stock Segunda Fila
    ui->A1_pos_6->setText(QString::fromUtf8(Pilas[5].Slotid.c_str()));
    ui->A1_name_6->setText(QString::fromUtf8(Pilas[5].ProductName.c_str()));
    ui->A1_count_6->setText(QString::number(Pilas[5].ProductCount));
    ui->A1_pos_7->setText(QString::fromUtf8(Pilas[6].Slotid.c_str()));
    ui->A1_name_7->setText(QString::fromUtf8(Pilas[6].ProductName.c_str()));
    ui->A1_count_7->setText(QString::number(Pilas[6].ProductCount));
    ui->A1_pos_8->setText(QString::fromUtf8(Pilas[7].Slotid.c_str()));
    ui->A1_name_8->setText(QString::fromUtf8(Pilas[7].ProductName.c_str()));
    ui->A1_count_8->setText(QString::number(Pilas[7].ProductCount));
    ui->A1_pos_9->setText(QString::fromUtf8(Pilas[8].Slotid.c_str()));
    ui->A1_name_9->setText(QString::fromUtf8(Pilas[8].ProductName.c_str()));
    ui->A1_count_9->setText(QString::number(Pilas[8].ProductCount));
    ui->A1_pos_28->setText(QString::fromUtf8(Pilas[9].Slotid.c_str()));
    ui->A1_name_28->setText(QString::fromUtf8(Pilas[9].ProductName.c_str()));
    ui->A1_count_28->setText(QString::number(Pilas[9].ProductCount));

    // Stock Tercera Fila
    ui->A3_pos->setText(QString::fromUtf8(Pilas[10].Slotid.c_str()));
    ui->A3_name->setText(QString::fromUtf8(Pilas[10].ProductName.c_str()));
    ui->A3_count->setText(QString::number(Pilas[10].ProductCount));
    ui->A3_pos_2->setText(QString::fromUtf8(Pilas[11].Slotid.c_str()));
    ui->A3_name_2->setText(QString::fromUtf8(Pilas[11].ProductName.c_str()));
    ui->A3_count_2->setText(QString::number(Pilas[11].ProductCount));
    ui->A3_pos_3->setText(QString::fromUtf8(Pilas[12].Slotid.c_str()));
    ui->A3_name_3->setText(QString::fromUtf8(Pilas[12].ProductName.c_str()));
    ui->A3_count_3->setText(QString::number(Pilas[12].ProductCount));
    ui->A3_pos_4->setText(QString::fromUtf8(Pilas[13].Slotid.c_str()));
    ui->A3_name_4->setText(QString::fromUtf8(Pilas[13].ProductName.c_str()));
    ui->A3_count_4->setText(QString::number(Pilas[13].ProductCount));
    ui->A3_pos_5->setText(QString::fromUtf8(Pilas[14].Slotid.c_str()));
    ui->A3_name_5->setText(QString::fromUtf8(Pilas[14].ProductName.c_str()));
    ui->A3_count_5->setText(QString::number(Pilas[14].ProductCount));

    // Stock Cuarta Fila
    ui->A4_pos->setText(QString::fromUtf8(Pilas[15].Slotid.c_str()));
    ui->A4_name->setText(QString::fromUtf8(Pilas[15].ProductName.c_str()));
    ui->A4_count->setText(QString::number(Pilas[15].ProductCount));
    ui->A4_pos_2->setText(QString::fromUtf8(Pilas[16].Slotid.c_str()));
    ui->A4_name_2->setText(QString::fromUtf8(Pilas[16].ProductName.c_str()));
    ui->A4_count_2->setText(QString::number(Pilas[16].ProductCount));
    ui->A4_pos_3->setText(QString::fromUtf8(Pilas[17].Slotid.c_str()));
    ui->A4_name_3->setText(QString::fromUtf8(Pilas[17].ProductName.c_str()));
    ui->A4_count_3->setText(QString::number(Pilas[17].ProductCount));
    ui->A4_pos_4->setText(QString::fromUtf8(Pilas[18].Slotid.c_str()));
    ui->A4_name_4->setText(QString::fromUtf8(Pilas[18].ProductName.c_str()));
    ui->A4_count_4->setText(QString::number(Pilas[18].ProductCount));
    ui->A4_pos_5->setText(QString::fromUtf8(Pilas[19].Slotid.c_str()));
    ui->A4_name_5->setText(QString::fromUtf8(Pilas[19].ProductName.c_str()));
    ui->A4_count_5->setText(QString::number(Pilas[19].ProductCount));

    // Stock Quinta Fila
    ui->A4_pos_6->setText(QString::fromUtf8(Pilas[20].Slotid.c_str()));
    ui->A4_name_6->setText(QString::fromUtf8(Pilas[20].ProductName.c_str()));
    ui->A4_count_6->setText(QString::number(Pilas[20].ProductCount));
    ui->A4_pos_7->setText(QString::fromUtf8(Pilas[21].Slotid.c_str()));
    ui->A4_name_7->setText(QString::fromUtf8(Pilas[21].ProductName.c_str()));
    ui->A4_count_7->setText(QString::number(Pilas[21].ProductCount));
    ui->A4_pos_8->setText(QString::fromUtf8(Pilas[22].Slotid.c_str()));
    ui->A4_name_8->setText(QString::fromUtf8(Pilas[22].ProductName.c_str()));
    ui->A4_count_8->setText(QString::number(Pilas[22].ProductCount));
    ui->A4_pos_9->setText(QString::fromUtf8(Pilas[23].Slotid.c_str()));
    ui->A4_name_9->setText(QString::fromUtf8(Pilas[23].ProductName.c_str()));
    ui->A4_count_9->setText(QString::number(Pilas[23].ProductCount));
    ui->A4_pos_10->setText(QString::fromUtf8(Pilas[24].Slotid.c_str()));
    ui->A4_name_10->setText(QString::fromUtf8(Pilas[24].ProductName.c_str()));
    ui->A4_count_10->setText(QString::number(Pilas[24].ProductCount));

}


void MenuPrincipal::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


// Funcion que revisa los productos disponibles en todo el stock
void MenuPrincipal::on_revisarDisponibles_clicked()
{
   // cout<<"Cantidad disponible: "<<PCant[0]<<endl;
    int diffs_orig = countDistinct(Nombre, 25);
    //int diffs_orig = countDistinct(Nombre, 25);
    int diffs = diffs_orig-1;
    //diffs_name[diffs];
   // string name_diffs[5];
    cout<<"ProductosDiferentes: "<<diffs<<endl;
    string s = diffs_name[diffs];

    for (int i=0;i<25;i++)
        {
            int count = 24 - i;
            //cout<<"Nombre del producto: "<<Nombre[i]<<endl;
            if(Nombre[i] != ""){
                for (int j=0;j<1;j++) {
                    string Name = Nombre[i];
                    cout<<"Producto con nombre no nulo: "<<25-i<<endl;
                    cout<<"Nombre: "<<Name<<endl;
                    diffs_name[count] = Name;
                }

            }
            if (Nombre[i] == "")
            {
             //   cout<<"Slots Vacios: "<<25-diffs<<endl;
               // cout<<"NombreDiferente: "<<Nombre[i]<<endl;
            }
            else;
        }

    // CODIGO PARA ELIMINAR REPETIDOS DEL STRING DE NOMBRES DISPONIBLES
    set<string> duplicates;
    auto it = remove_if(begin(diffs_name),end(diffs_name), [&duplicates](string i){
        return !duplicates.insert(i).second;
    });

    size_t n = distance(begin(diffs_name),it);

    for (size_t i =0;i<n;i++) {
        cout<<diffs_name[i]<< "";

    }

    ui->Pdiscant1->setText(QString::number(diffs));
    ui->label_14->setText(QString::fromUtf8(diffs_name[0].c_str()));
    ui->label_15->setText(QString::fromUtf8(diffs_name[1].c_str()));
    ui->label_16->setText(QString::fromUtf8(diffs_name[2].c_str()));
    ui->label_17->setText(QString::fromUtf8(diffs_name[3].c_str()));
    ui->label_18->setText(QString::fromUtf8(diffs_name[4].c_str()));
    ui->label_19->setText(QString::fromUtf8(diffs_name[5].c_str()));
    ui->label_20->setText(QString::fromUtf8(diffs_name[6].c_str()));
    ui->label_21->setText(QString::fromUtf8(diffs_name[7].c_str()));
    ui->label_22->setText(QString::fromUtf8(diffs_name[8].c_str()));
    ui->label_23->setText(QString::fromUtf8(diffs_name[9].c_str()));
    ui->label_24->setText(QString::fromUtf8(diffs_name[10].c_str()));
    ui->label_25->setText(QString::fromUtf8(diffs_name[11].c_str()));
    ui->label_26->setText(QString::fromUtf8(diffs_name[12].c_str()));
    ui->label_227->setText(QString::fromUtf8(diffs_name[13].c_str()));

    /*ui->label_31->setText(QString::fromUtf8(diffs_name[0].c_str()));
    ui->label_32->setText(QString::fromUtf8(diffs_name[1].c_str()));
    ui->label_33->setText(QString::fromUtf8(diffs_name[2].c_str()));
    ui->label_34->setText(QString::fromUtf8(diffs_name[3].c_str()));
    ui->label_35->setText(QString::fromUtf8(diffs_name[4].c_str()));
    ui->label_36->setText(QString::fromUtf8(diffs_name[5].c_str()));
    ui->label_37->setText(QString::fromUtf8(diffs_name[6].c_str()));
    ui->label_38->setText(QString::fromUtf8(diffs_name[7].c_str()));
    ui->label_39->setText(QString::fromUtf8(diffs_name[8].c_str()));
    ui->label_40->setText(QString::fromUtf8(diffs_name[9].c_str()));
    ui->label_41->setText(QString::fromUtf8(diffs_name[10].c_str()));
    ui->label_42->setText(QString::fromUtf8(diffs_name[11].c_str()));
    ui->label_43->setText(QString::fromUtf8(diffs_name[12].c_str()));
    ui->label_44->setText(QString::fromUtf8(diffs_name[13].c_str()));
    ui->label_45->setText(QString::fromUtf8(diffs_name[14].c_str()));
    ui->label_46->setText(QString::fromUtf8(diffs_name[15].c_str()));
    ui->label_47->setText(QString::fromUtf8(diffs_name[16].c_str()));
    ui->label_48->setText(QString::fromUtf8(diffs_name[17].c_str()));
    ui->label_49->setText(QString::fromUtf8(diffs_name[18].c_str()));
    ui->label_50->setText(QString::fromUtf8(diffs_name[19].c_str()));
    ui->label_51->setText(QString::fromUtf8(diffs_name[20].c_str()));
    ui->label_52->setText(QString::fromUtf8(diffs_name[21].c_str()));
    ui->label_53->setText(QString::fromUtf8(diffs_name[22].c_str()));
    ui->label_54->setText(QString::fromUtf8(diffs_name[23].c_str()));
    ui->label_55->setText(QString::fromUtf8(diffs_name[24].c_str()));

*/
    //Imprimir los productos en el menu del inventario, para mostrar solo los disponibles:


    if (diffs == 0)
    {
        string s = "No hay productos disponibles en este momento";
        ui->MensajeMenu->setText(QString::fromUtf8(s.c_str()));
    }
    if (diffs > 0)
    {
        ui->MensajeMenu->setText("");
        ImprimirProducto();
    }


    // codigo para ver la cantidad de producto del inventario:

    if (diffs_name[0] != "")
    {
        int cp = returnProductAmount(diffs_name[0]);
        ui->label_228->setText(QString::number(cp));
    }
    else;

}

void MenuPrincipal::on_Menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MenuPrincipal::on_regresarMain_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MenuPrincipal::on_ResetInventory_clicked()
{
    for (int i =0;i<25;i++) {
        Pilas[i].ProductName="No Product";
        Pilas[i].ProductCount=0;
        Pilas[i].Slotid="Not Used";
    }
}

void MenuPrincipal::on_producto1_clicked()
{
    QPixmap coke("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/coke.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Coca Cola");
    ui->imagenBebida->setPixmap(coke);
}

void MenuPrincipal::on_producto2_clicked()
{
    QPixmap coke_zero("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/coke_zero.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Coca Zero");
    ui->imagenBebida->setPixmap(coke_zero);
}

void MenuPrincipal::on_regresarAcantidad_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MenuPrincipal::on_producto3_clicked()
{
    QPixmap imperial("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/imperial.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Imperial");
    ui->imagenBebida->setPixmap(imperial);
}

void MenuPrincipal::on_producto4_clicked()
{
    QPixmap pilsen("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/pilsen.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Pilsen");
    ui->imagenBebida->setPixmap(pilsen);
}

void MenuPrincipal::on_producto5_clicked()
{
    QPixmap ginger("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/ginger.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Ginger Ale");
    ui->imagenBebida->setPixmap(ginger);
}

void MenuPrincipal::on_producto6_clicked()
{
    QPixmap azul("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/bluepower.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Powerade Azul");
    ui->imagenBebida->setPixmap(azul);
}

void MenuPrincipal::on_producto7_clicked()
{
    QPixmap red("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/redpower.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Powerade Rojo");
    ui->imagenBebida->setPixmap(red);
}

void MenuPrincipal::on_producto8_clicked()
{
    QPixmap bluegato("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/bluegatorade.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Gat");
    ui->imagenBebida->setPixmap(bluegato);
}

void MenuPrincipal::on_producto9_clicked()
{
    QPixmap redgato("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/redgatorade.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Gatorade Rojo");
    ui->imagenBebida->setPixmap(redgato);
}

void MenuPrincipal::on_producto10_clicked()
{
    QPixmap sevenup("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/7up.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("7 UP");
    ui->imagenBebida->setPixmap(sevenup);
}

void MenuPrincipal::on_producto11_clicked()
{
    QPixmap root("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/root.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Root Beer");
    ui->imagenBebida->setPixmap(root);
}

void MenuPrincipal::on_producto12_clicked()
{
    QPixmap cocalight("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/cocalight.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Coca Light");
    ui->imagenBebida->setPixmap(cocalight);
}

void MenuPrincipal::on_producto13_clicked()
{
    QPixmap agua("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/agua.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Agua");
    ui->imagenBebida->setPixmap(agua);
}

void MenuPrincipal::on_producto14_clicked()
{
    QPixmap fantanaranja("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantanaranja.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Fanta Naranja");
    ui->imagenBebida->setPixmap(fantanaranja);
}

void MenuPrincipal::on_producto15_clicked()
{
    QPixmap fantauva("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantauva.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Fanta Uva");
    ui->imagenBebida->setPixmap(fantauva);
}

void MenuPrincipal::on_producto16_clicked()
{
    QPixmap fantaazul("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantaazul.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Fanta Azul");
    ui->imagenBebida->setPixmap(fantaazul);
}

void MenuPrincipal::on_producto17_clicked()
{
    QPixmap fantakolita("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fantakolita.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Fanta Kolita");
    ui->imagenBebida->setPixmap(fantakolita);
}

void MenuPrincipal::on_producto18_clicked()
{
    QPixmap tefrio("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/tefrio.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Te Frio");
    ui->imagenBebida->setPixmap(tefrio);
}

void MenuPrincipal::on_producto19_clicked()
{
    QPixmap evervess("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/evervess.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Evervess");
    ui->imagenBebida->setPixmap(evervess);
}

void MenuPrincipal::on_producto20_clicked()
{
    QPixmap vainilla("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/vainilla.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Vainilla");
    ui->imagenBebida->setPixmap(vainilla);
}

void MenuPrincipal::on_producto21_clicked()
{
    QPixmap chocolate("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/chocolate.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Chocolate");
    ui->imagenBebida->setPixmap(chocolate);
}

void MenuPrincipal::on_producto22_clicked()
{
    QPixmap fresa("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/fresa.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Fresa");
    ui->imagenBebida->setPixmap(fresa);
}

void MenuPrincipal::on_producto23_clicked()
{
    QPixmap pepsi("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/pepsi.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Pepsi");
    ui->imagenBebida->setPixmap(pepsi);
}

void MenuPrincipal::on_producto24_clicked()
{
    QPixmap pepsilight("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/pepsilight.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Pepsi Light");
    ui->imagenBebida->setPixmap(pepsilight);
}

void MenuPrincipal::on_producto25_clicked()
{
    QPixmap ultra("C:/Users/valve/OneDrive/Documentos/QT/Imagenes/ultra.png");
    ui->stackedWidget->setCurrentIndex(4);
    ui->nombreBebida->setText("Ultra");
    ui->imagenBebida->setPixmap(ultra);
}

void MenuPrincipal::publishmessage(string mensaje)
{
    ui->mqtt_message->setText(QString::fromUtf8(mensaje.c_str()));
}
// Funciones de MQTT
void MenuPrincipal::on_Broker_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MenuPrincipal::setClientPort(int p)
{
    m_client->setPort(p);
}
void MenuPrincipal::updateLogStateChange()
{
    const QString contenido = QDateTime::currentDateTime().toString()
            + QLatin1String(": Cambio de Estado")
            + QString::number(m_client->state())
            + QLatin1Char('\n');
    string salida = contenido.toStdString();
    cout<<salida<<endl;
}
void MenuPrincipal::brokerDisconnected()
{
    ui->lineEditHost->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
    ui->Connect->setText(tr("Connect"));
}

void MenuPrincipal::on_Subscribe_clicked()
{
    auto subscription = m_client->subscribe(ui->topic->text());
    if (!subscription){
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
                return;
    }
}

void MenuPrincipal::on_publish_clicked()
{
    if (m_client->publish(ui->topic->text(), ui->mqtt_message->text().toUtf8()) == -1)
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Mensaje no publicado"));
}

void MenuPrincipal::on_regresarMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MenuPrincipal::on_Connect_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
            ui->lineEditHost->setEnabled(false);
            ui->spinBoxPort->setEnabled(false);
            ui->Connect->setText(tr("Disconnect"));
            m_client->connectToHost();
        } else {
            ui->lineEditHost->setEnabled(true);
            ui->spinBoxPort->setEnabled(true);
            ui->Connect->setText(tr("Connect"));
            m_client->disconnectFromHost();
        }
}

void MenuPrincipal::on_regresarTemp_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MenuPrincipal::on_tempdisplay_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    int vi = 0;

    vi = rand() % 5 + 2;
    ui->tempValue->display(vi);
    string message = "La temperatura del sistema: " + to_string(vi);
    publishmessage(message);
    on_publish_clicked();

}
