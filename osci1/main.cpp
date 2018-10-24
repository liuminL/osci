#include "mainwindow.h"
#include <QApplication>
#include <xil_io.h>
#include <move.h>
#include <iostream>
#define XPAR_DDR_MEM_BASEADDR		0x00100000
#define DDR_BASEARDDR	XPAR_DDR_MEM_BASEADDR //+ 0x10000000

int main(int argc, char *argv[])
{
    uint32_t i;
    int rev;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    printf("Hello World!!!\n\r");
//    u16 dat[100];
        //int i;
//    Read_Sector(0,10,dat);
//    for(i=0;i<10;i++)
//    {
//        printf("0x%x\n",dat[i]);
//    }
//    printf("ok\n");

    Xil_Out32(DDR_BASEARDDR, 0x0);
    //while(1)
    //{
        for (i = 0x0; i <= 0xf; i++)
        {
            Xil_Out32(DDR_BASEARDDR, i);

            //sleep(1);

            rev = Xil_In32(DDR_BASEARDDR);
            //std::cout<< PAGE_SIZE <<std::endl;
            std::cout<<std::hex<<DDR_BASEARDDR<<" is "<<std::hex<<rev<<std::endl;
            //printf(" %x is %x \n\r", DDR_BASEARDDR, rev);
            //sleep(1);
        }
//        rev = Xil_In32(DDR_BASEARDDR+17);
//        printf(" %x is %x \n\r", DDR_BASEARDDR, rev);
//        sleep(1);

     //}
    return a.exec();
}
