#include "xil_io.h"
#include "move.h"

#define AXI_RIO_BASEADDR 0x40000000
#define AXI_RIO_NODE_BASEADDR 0x10100
#define AXI_RIO_MAX_HOPCOUNT 13

void rio_setreg32(unsigned int addrBase,unsigned int addrOffset,unsigned int value)
{
    Xil_Out32(addrBase+addrOffset, value);
}
int rio_getreg32(unsigned int addrBase,unsigned int addrOffset)
{
    int ans=0;
    ans=Xil_In32(addrBase+addrOffset);
    return ans;
}
int hlMaintWrite(unsigned int dstId,unsigned short hopcount, unsigned int offset, unsigned int writedata)
{
    unsigned int reg_addr;
    if( hopcount > AXI_RIO_MAX_HOPCOUNT )
    {
        printf("!!!error, hopcount = %d, > %d\n",hopcount,AXI_RIO_MAX_HOPCOUNT);
        return -1;
    }
    rio_setreg32(AXI_RIO_BASEADDR,AXI_RIO_NODE_BASEADDR,dstId);
    reg_addr = (((hopcount+1)<<24)|offset);
    rio_setreg32(AXI_RIO_BASEADDR,reg_addr,writedata);
    return 0;
}
int hlMaintRead(unsigned int dstId,unsigned short hopcount, unsigned int offset, int mrdataAdr)
{
    unsigned int reg_addr;
    if( hopcount > AXI_RIO_MAX_HOPCOUNT )
    {
        printf("!!!error, hopcount = %d, > %d\n",hopcount,AXI_RIO_MAX_HOPCOUNT);
        return -1;
    }
    rio_setreg32(AXI_RIO_BASEADDR,AXI_RIO_NODE_BASEADDR,dstId);
    reg_addr = (((hopcount+1)<<24)|offset); mrdataAdr = rio_getreg32(AXI_RIO_BASEADDR,reg_addr);
    printf("M_SRIO_MAINT_REG_READ: hopcount = %d, offset = 0x%x, value = 0x%x\n",hopcount,offset,mrdataAdr);
    return 0;
}


void flash_set16(unsigned int addrBase,unsigned int addrOffset,unsigned int value)
{
    Xil_Out16(addrBase+2*addrOffset, value);
    //printf("flash set reg 0x%x value is 0x%x\n",addrBase+2*addrOffset,value);
}

int flash_get16(unsigned int addrBase,unsigned int addrOffset)
{

    int ans=0;
    ans=Xil_In16(addrBase+2*addrOffset);
    return ans;
}

int Erase_Flash(int sectorNum)
{

    unsigned short flag;
    int i=0;
    int val=0;
    unsigned short *base_addr;
    base_addr = (unsigned short*)(XPAR_AXI_EMC_0_S_AXI_MEM0_BASEADDR+SECSIZE*sectorNum*2);
    printf("erase start addr 0x%x\n",base_addr);

    flash_set16((unsigned int)base_addr,0x555,0x00AA);
    flash_set16((unsigned int)base_addr,0x2AA,0x0055);
    flash_set16((unsigned int)base_addr,0x555,0x0080);
    flash_set16((unsigned int)base_addr,0x555,0x00AA);
    flash_set16((unsigned int)base_addr,0x2AA,0x0055);
    flash_set16((unsigned int)base_addr,0,0x0030);
    val=flash_get16((unsigned int)base_addr,0);
    printf("base addr 0x%x val is 0x%x\n",base_addr,val);
    while((val&0x80)!=0x80)
    {
        i++;
        if( i>=WAIT_TICKS)
        {
            printf("addr %x Erase_Flash failed!\n",base_addr);
            flash_set16((unsigned int)base_addr,0x555,0x0090);
            flash_set16((unsigned int)base_addr,0x000,0x0000);
            return -1;
        }
        //flag = base_addr;
        val=flash_get16((unsigned int)base_addr,0);
    }
    flash_set16((unsigned int)base_addr,0x555,0x0090);
    flash_set16((unsigned int)base_addr,0x000,0x0000);
    printf("erase end addr %x\n",base_addr+SECSIZE);
    return 0;
}

int Write_Sector(int sectorNum,int offset,u16 *src_addr,int wr_num)
{
    int i,j;
    u16 *dst_addr;
    int val=0;
    int ans=0;
    dst_addr = (u16*)(XPAR_AXI_EMC_0_S_AXI_MEM0_BASEADDR+SECSIZE*sectorNum*2+offset);

    flash_set16((unsigned int)dst_addr,0x555,0x00AA);
    flash_set16((unsigned int)dst_addr,0x2AA,0x0055);
    printf("dst addr is 0x%x\n",dst_addr);
    for(i=0;i<wr_num;i++)
    {
        flash_set16((unsigned int)dst_addr,0x555,0x0020);
        flash_set16((unsigned int)dst_addr,0x000,0x00A0);
        // printf("i is %d\n",i); val=src_addr[i];
        printf("val is 0x%x\n",val);
        flash_set16((unsigned int)dst_addr,i,val);
        ans=flash_get16((unsigned int)dst_addr,i);
        //printf("ans is 0x%x\n",ans);
        j=0;
        while( ans!= val)
        {
            j++;
            if(j>=WAIT_TICKS) {
                flash_set16((unsigned int)dst_addr,0x555,0x0090);
                flash_set16((unsigned int)dst_addr,0x000,0x0000);
                return -1;
            }
            ans=flash_get16((unsigned int)dst_addr,i);
        }
    }
    flash_set16((unsigned int)dst_addr,0x555,0x0090);
    flash_set16((unsigned int)dst_addr,0x000,0x0000);
    return 0;
}
int Read_Sector(int sectorNum,int rd_num,unsigned short *buf)
{
    unsigned short *sector_addr;
    int i; int val=0;
    if( rd_num <= 0)
    {
        return -1;
    }
    printf("flash read start--sectorNum= %d rd_num= %d\n",sectorNum,rd_num);
    sector_addr = (u16*)(XPAR_AXI_EMC_0_S_AXI_MEM0_BASEADDR+SECSIZE*sectorNum*2);
    printf("sector addr is 0x%x\n",sector_addr);
    if( rd_num <= SECSIZE )
    {
        for(i=0;i<rd_num;i++)
        {
            printf("val is 0x%x\n",flash_get16((unsigned int)sector_addr,0));
            val = flash_get16((unsigned int)sector_addr,0); *buf=val; buf++; sector_addr++;
        }
    }
    else
    {
        printf("error\n");
    }
    return 0;
}


