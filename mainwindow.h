#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "commanddata.h"
#include <SerialPort.h>
#include <QMessageBox>
#include <vector>
#include <thread>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bttnComStart_clicked();

    void on_bttnComClose_clicked();


    void on_bttnnfov_clicked();

    void on_bttnmfov_clicked();

    void on_bttnwfov_clicked();

    void on_bttnfocusInc_clicked();

    void on_bttnfocusdec_clicked();

    QString getBufferAsHex(unsigned char * buf, int buffsize);
    void on_bttnfocusAuto_clicked();

    void on_bttnBSNUC_clicked();

    void on_bttnBNSNUC_clicked();

    void on_bttnBPRMTD1_clicked();

    void on_bttnBPRMTD2_clicked();

    void on_bttnSBPT_clicked();

    void on_bttnAGOC0_clicked();

    void on_bttnAGOC1_clicked();

    void on_bttnMGOC_clicked();

    void on_bttnNormalImg_clicked();

    void on_bttnRotX_clicked();

    void on_bttnRotY_clicked();

    void on_bttnCentPoint_clicked();

    void on_bttnDDEOff_clicked();

    void on_bttnDDEOn_clicked();

    void on_bttnDDEM0_clicked();

    void on_bttnDDEM1_clicked();

    void on_bttnDDEM2_clicked();

    void on_bttnZoom2_clicked();

    void on_bttnZoom1_clicked();

    void on_bttnFrezImg_clicked();

    void on_bttnActImg_clicked();

    void on_bttnNegImg_clicked();

    void on_bttnPosImg_clicked();

    void on_bttnAimOn_clicked();

    void on_bttnAimOff_clicked();

    void on_bttnSavePara_clicked();

    void on_bttnClearTx_clicked();

    void on_bttnClearRx_clicked();

    void on_bttnMGainInc_clicked();

    void on_bttnMGainDec_clicked();

    void on_bttnMOffsetInc_clicked();

    void on_bttnMOffsetDec_clicked();

    void on_bttnMGainReset_clicked();

    void on_bttnMOffsetReset_clicked();

    void rxtextboxData(QString data);
private:
    Ui::MainWindow *ui;
    SerialPort *port;
    QString txStr;
    QMessageBox mbox;
    std::vector<unsigned char>data;
    std::thread t_tiRecv;
    void serialPortInit(char *portno, int baudrate);
    bool openPortFlag;
    unsigned char txdata[5];
    unsigned char rxdata[5],checksum,rxState;
    signed char offset;
    signed char gain;
    void init();
    void commandSend(unsigned char command, char  data);
    void TIrecvHandler(void);

signals:
     void updateTextBox(QString data);
};

#endif // MAINWINDOW_H
