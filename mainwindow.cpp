#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new SerialPort("/dev/ttyS0");
    t_tiRecv = std::thread(&MainWindow::TIrecvHandler,this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(port->IsOpen())port->Close();
    t_tiRecv.join();

}

void MainWindow::init()
{

    this->openPortFlag = false;

    offset = -0x6F;
    gain = -0x6F;

    //TI Data Packet
    data.push_back(0xED);
    data.push_back(0x90);

    txdata[0] = 0xED;
    txdata[1] = 0x90;

    rxState = 1;
    connect(this,SIGNAL(updateTextBox(QString)),this,SLOT(rxtextboxData(QString)));

}
void MainWindow::serialPortInit(char *portname, int baudrate)
{


    char spn[10] = "/dev/";
    strcat(spn,portname);

    char buffer[34];

    sprintf(buffer, "sudo chown -R $USERNAME %s", spn);

    //system("sudo chown -R $USERNAME /dev/ttyS0");

    system(buffer);
    auto baud = SerialPort::BAUD_DEFAULT;

    switch (baudrate) {
    case 9600: //9600
    {
        baud = SerialPort::BAUD_9600;
        break;
    }

    case 115200://115200
    {
        baud = SerialPort::BAUD_115200;
        break;
    }
    default:
    {
        baud = SerialPort::BAUD_DEFAULT;
    }

    }




    try
    {
        port->Open(SerialPort::BAUD_9600,
                   SerialPort::CHAR_SIZE_8,
                   SerialPort::PARITY_ODD,
                   SerialPort::STOP_BITS_1,
                   SerialPort::FLOW_CONTROL_NONE);

        mbox.setWindowTitle("Success");
        mbox.setText("Serial Port Opened !");
        mbox.exec();
        openPortFlag = true;

    }

    catch (const SerialPort::AlreadyOpen& e)
    {
        mbox.setWindowTitle("Attention");
        mbox.setText(e.what());
        mbox.exec();
        openPortFlag = true;
    }

    catch (const SerialPort::OpenFailed& e)
    {
        mbox.setWindowTitle("Error");
        mbox.setText(e.what());
        mbox.exec();
        openPortFlag = false;
    }

    catch (const std::invalid_argument& e)
    {
        mbox.setWindowTitle("Error");
        mbox.setText(e.what());
        mbox.exec();
        openPortFlag = false;
    }

    catch (const SerialPort::UnsupportedBaudRate& e)
    {
        mbox.setWindowTitle("Error");
        mbox.setText(e.what());
        mbox.exec();
        openPortFlag = false;
    }

}

void MainWindow::on_bttnComStart_clicked()
{

    switch (ui->cBoxPortName->currentIndex()) {
    case 0: {serialPortInit("ttyS0",9600); break;}
    case 1: {serialPortInit("ttyS1",9600); break;}
    case 2: {serialPortInit("ttyS2",9600); break;}
    case 3: {serialPortInit("ttyS3",9600); break;}
    }


}

QString MainWindow::getBufferAsHex(unsigned char * buf, int buffsize)
{
    QString res;

    for (int i=0 ;i<buffsize;i++)
    {
        res += QString("%1").arg(buf[i],2,16,QChar('0').toUpper()) + " ";
    }

    return res;
}
void MainWindow::on_bttnComClose_clicked()
{

    try {

        port->Close();
        mbox.setWindowTitle("Attention");
        mbox.setText("Port Closed");
        mbox.exec();
        openPortFlag = false;

    }
    catch (const SerialPort::NotOpen& e)
    {
        mbox.setWindowTitle("Attention");
        mbox.setText("Port Already Closed");
        mbox.exec();
        openPortFlag = false;

    }
}


void MainWindow::on_bttnnfov_clicked()
{

    commandSend(NFOVc, NFOVd);



}

void MainWindow::on_bttnmfov_clicked()
{

    commandSend(MFOVc, MFOVd);

}

void MainWindow::on_bttnwfov_clicked()
{

    commandSend(WFOVc, WFOVd);

}

void MainWindow::on_bttnfocusInc_clicked()
{

    commandSend(MFocusIncc, MFocusIncd);

}

void MainWindow::on_bttnfocusdec_clicked()
{

    commandSend(MFocusDecc, MFocusDecd);


}

void MainWindow::on_bttnfocusAuto_clicked()
{

    commandSend(AFocusc, AFocusd);


}

void MainWindow::on_bttnBSNUC_clicked()
{
    commandSend(BSNUCc, BSNUCd);


}

void MainWindow::on_bttnBNSNUC_clicked()
{

    commandSend(BNSNUCc, BNSNUCd);

}



void MainWindow::on_bttnBPRMTD1_clicked()
{

    commandSend(BPRMTD1c, BPRMTD1d);


}

void MainWindow::on_bttnBPRMTD2_clicked()
{
    commandSend(BPRMTD2c, BPRMTD2d);


}

void MainWindow::on_bttnSBPT_clicked()
{
    commandSend(SBPTc, SBPTd);


}

void MainWindow::on_bttnAGOC0_clicked()
{
    commandSend(AGOC0c, AGOC0d);


}

void MainWindow::on_bttnAGOC1_clicked()
{

    commandSend(AGOC1c, AGOC1d);

}

void MainWindow::on_bttnMGOC_clicked()
{
    commandSend(MGOCc, MGOCd);


}

void MainWindow::on_bttnNormalImg_clicked()
{
    commandSend(NormalImgc, NormalImgd);

}

void MainWindow::on_bttnRotX_clicked()
{
    commandSend(RotImageXc, RotImageXc);

}

void MainWindow::on_bttnRotY_clicked()
{
    commandSend(RotImageYc, RotImageYd);

}

void MainWindow::on_bttnCentPoint_clicked()
{
    commandSend(RotImageCentPntc, RotImageCentPntd);

}

void MainWindow::on_bttnDDEOff_clicked()
{
    commandSend(DDEOffc, DDEOffd);

}

void MainWindow::on_bttnDDEOn_clicked()
{
    commandSend(DDEOnc, DDEOnd);

}

void MainWindow::on_bttnDDEM0_clicked()
{
    commandSend(DDEMode0c, DDEMode0d);

}

void MainWindow::on_bttnDDEM1_clicked()
{
    commandSend(DDEMode1c, DDEMode1d);

}

void MainWindow::on_bttnDDEM2_clicked()
{
    commandSend(DDEMode2c, DDEMode2d);

}

void MainWindow::on_bttnZoom2_clicked()
{
    commandSend(Zoom2c, Zoom2d);

}

void MainWindow::on_bttnZoom1_clicked()
{
    commandSend(Zoom1c, Zoom1d);

}

void MainWindow::on_bttnFrezImg_clicked()
{

    commandSend(FreezingImgc, FreezingImgd);

}

void MainWindow::on_bttnActImg_clicked()
{
    commandSend(ActiveImgc, ActiveImgd);
}

void MainWindow::on_bttnNegImg_clicked()
{
    commandSend(BlackHotVideoNegc, BlackHotVideoNegd);

}

void MainWindow::on_bttnPosImg_clicked()
{
    commandSend(WhiteHotVideoPosc, WhiteHotVideoPosd);



}

void MainWindow::on_bttnAimOn_clicked()
{
    commandSend(DispAimCrossc, DispAimCrossd);


}

void MainWindow::on_bttnAimOff_clicked()
{
    commandSend(HideAimCrossc, HideAimCrossd);


}

void MainWindow::on_bttnSavePara_clicked()
{
    commandSend(SaveParamDefaultc, SaveParamDefaultd);

}

void MainWindow::commandSend(unsigned char com,  char  dat)
{
    if(openPortFlag)
    {

        data.push_back(0xED);
        data.push_back(0x90);

        data.push_back(com);
        data.push_back(dat);

        txdata[2] = com;
        txdata[3] = dat;
        txdata[4] = txdata[2] + txdata[3];

        data.push_back(txdata[4]);

        try
        {
            port->Write(data);
        }
        catch (const std::exception& e)
        {
            cout << "Not sent" << endl;
        }

        ui->txtbxTxData->append(getBufferAsHex(txdata,5));
        data.clear();

    }

    else
    {
        mbox.setWindowTitle("Attention");
        mbox.setText("Serial Port is not open");
        mbox.exec();

    }
}



void MainWindow::on_bttnClearTx_clicked()
{
    ui->txtbxTxData->clear();
}

void MainWindow::on_bttnClearRx_clicked()
{
    ui->txtbxRxData->clear();
}

void MainWindow::on_bttnMGainInc_clicked()
{

    if(gain > 0x7E)
        gain = 0x7F;
    else
        gain = gain + 1;

    commandSend(MGainc, gain);



}

void MainWindow::on_bttnMGainDec_clicked()
{
    if(gain < -0x7F)
        gain = -0x80;
    else
        gain = gain - 1;
    commandSend(MGainc, gain);

}

void MainWindow::on_bttnMOffsetInc_clicked()
{
    if(offset > 0x7E)
        offset = 0x7F;
    else
        offset = offset + 1;

    commandSend(MOffsetc, offset);

}

void MainWindow::on_bttnMOffsetDec_clicked()
{
    if(offset < -0x7F)
        offset = -0x80;
    else
        offset = offset - 1;
    commandSend(MOffsetc, offset);
}

void MainWindow::on_bttnMGainReset_clicked()
{
    gain = 0;
    commandSend(MGainc, gain);

}

void MainWindow::on_bttnMOffsetReset_clicked()
{
    offset = 0;
    commandSend(MOffsetc, offset);

}

void MainWindow::TIrecvHandler(void)
{

    std::vector<unsigned char> DataBuffer ;
    unsigned char buffer;
    while (1) {
        try
        {


            buffer= port->ReadByte(0);
  //          cout << " b = " << (int)(buffer) <<endl;

            switch (rxState)
            {
            case HeaderLow:

                if(buffer == 0xED)
                {

                    rxState = HeaderHigh;
                    rxdata[0] = buffer;
                }
                else
                {
                    rxState = HeaderLow;
                    rxdata[0] = '0';

                }
                break;

            case HeaderHigh:

                if(buffer == 0x90)
                {
                    rxState = CData;
                    rxdata[1] = buffer;
                }
                else
                {
                    rxState = HeaderLow;
                    rxdata[0] = rxdata[1] = '\0';
                }
                break;

            case CData:

                rxState = DData;
                rxdata[2] = buffer;
                break;

            case DData:

                rxState = Checksum;
                rxdata[3] = buffer;
                break;


            case Checksum:


                rxdata[4] = buffer;
                if((rxdata[2] + rxdata[3]) == rxdata[4])
                {

                    //ui->txtbxRxData->append(getBufferAsHex(rxdata,5));
                    QString d = getBufferAsHex(rxdata,5);

                    for(int i=0;i<5;i++)
                    cout << "rxdata =" << rxdata[i] + 0 << endl;

                    //cout << "rxdata =" << rxdata[4]+0 << endl;
                    emit updateTextBox(d);


                    rxState = HeaderLow;
                    rxdata[0] = rxdata[1] = rxdata[2] = rxdata[3] = rxdata[4] = '0';
                }

                else
                {
                    rxState = HeaderLow;
                    rxdata[0] = rxdata[1] = rxdata[2] = rxdata[3] = rxdata[4] = '0';
                }
                break;

            default:

                rxState = HeaderLow;
                rxdata[0] = rxdata[1] = rxdata[2] = rxdata[3] = rxdata[4] = '\0';


            }

        }

        catch (const SerialPort::NotOpen& e)
        {

        }

        catch (const SerialPort::ReadTimeout& e)
        {

        }
        catch (const std::runtime_error& e)
        {

        }
    }

}

void MainWindow::rxtextboxData(QString data)
{
 ui->txtbxRxData->append(data);
}
