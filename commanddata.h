#ifndef COMMANDDATA_H
#define COMMANDDATA_H




//unsigned char FVCdata[3][2]         = {{0x61,0x02},{0x61,0x01},{0x61,0x03}};

//unsigned char lensControlData[8][2] = {{0x60,0x03},{0x60,0xFD},{0x25,0x01},{0x66,0x01},{0x66,0x02},
//                                       {0x0F,0x00},{0x0F,0x04},{0x0F,0x01}};

#define NFOVc                       0x61
#define NFOVd                       0x02

#define WFOVc                       0x61
#define WFOVd                       0x01

#define MFOVc                       0x61
#define MFOVd                       0x03

#define MFocusIncc                  0x60
#define MFocusIncd                  0x03

#define MFocusDecc                  0x60
#define MFocusDecd                  0xFD

#define AFocusc                     0x25
#define AFocusd                     0x01

#define BSNUCc                      0x66
#define BSNUCd                      0x01

#define BNSNUCc                     0x66
#define BNSNUCd                     0x02

#define BPRMTD1c                    0x0F
#define BPRMTD1d                    0x00

#define BPRMTD2c                    0x0F
#define BPRMTD2d                    0x04


#define SBPTc                       0x0F
#define SBPTd                       0x01

#define AGOC0c                      0x20
#define AGOC0d                      0x01

#define AGOC1c                      0x20
#define AGOC1d                      0x02

#define MGOCc                       0x20
#define MGOCd                       0x00

#define MGainc                      0x21
#define MOffsetc                    0x30


#define NormalImgc                  0x50
#define NormalImgd                  0x00

#define RotImageXc                  0x50
#define RotImageXd                  0x01

#define RotImageYc                  0x50
#define RotImageYd                  0x02

#define RotImageCentPntc            0x50
#define RotImageCentPntd            0x03

#define DDEOffc                     0x37
#define DDEOffd                     0x00

#define DDEOnc                      0x37
#define DDEOnd                      0x02

#define DDEMode0c                   0x6D
#define DDEMode0d                   0x00

#define DDEMode1c                   0x6F
#define DDEMode1d                   0x01

#define DDEMode2c                   0x6D
#define DDEMode2d                   0x01

#define Zoom2c                      0x0B
#define Zoom2d                      0x00

#define Zoom1c                      0x0B
#define Zoom1d                      0x01

#define FreezingImgc                0x1F
#define FreezingImgd                0x01

#define ActiveImgc                  0x1F
#define ActiveImgd                  0x00

#define BlackHotVideoNegc           0x51
#define BlackHotVideoNegd           0x01

#define WhiteHotVideoPosc           0x51
#define WhiteHotVideoPosd           0x02

#define DispAimCrossc               0x52
#define DispAimCrossd               0x01

#define HideAimCrossc               0x52
#define HideAimCrossd               0x00

#define  SaveParamDefaultc          0x18
#define  SaveParamDefaultd          0x00


#define COM1                        "ttyS0"
#define COM2                        "ttyS1"
#define COM3                        "ttyS2"
#define COM4                        "ttyS3"


enum rxStates
{
    HeaderLow = 1,
    HeaderHigh,
    CData,
    DData,
    Checksum
};

#endif // COMMANDDATA_H
