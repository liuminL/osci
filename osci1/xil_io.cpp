#include <xil_io.h>

void Xil_Out32(uint64_t phyaddr, uint32_t val)
{
    int fd;
    volatile uint8_t *map_base;
    uint64_t base = phyaddr & PAGE_MASK;
    uint64_t pgoffset = phyaddr & (~PAGE_MASK);

    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
        perror("open /dev/mem:");
    }
    map_base = (volatile uint8_t *)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
    if(map_base == MAP_FAILED)
    {
        perror("mmap:");
    }
    *(volatile uint32_t *)(map_base + pgoffset) = val;


    //printf("%x\n",*map_base);

    close(fd);
    munmap((void *)map_base, PAGE_SIZE);
}
uint32_t Xil_In32(uint64_t phyaddr)
{
    int fd;
    uint32_t val;
    volatile uint8_t *map_base;
    uint64_t base = phyaddr & (PAGE_MASK);
    uint64_t pgoffset = phyaddr & (~PAGE_MASK);
    //open /dev/mem
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
        perror("open /dev/mem:");
    } //mmap
    map_base = (volatile uint8_t *)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
    if(map_base == MAP_FAILED)
    {
        perror("mmap:");
    }
    val = *((volatile uint32_t *)(map_base + pgoffset));
    printf("is %x \n",val);
    close(fd);
    munmap((void *)map_base, PAGE_SIZE);
    return val;
}
void Xil_Out16(uint64_t phyaddr, uint16_t val)
{

    int fd;
    volatile uint8_t *map_base;
    uint64_t base = phyaddr & PAGE_MASK;
    uint64_t pgoffset = phyaddr & (~PAGE_MASK);
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {

        perror("open /dev/mem:");
    }
    map_base = (volatile uint8_t *)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
    if(map_base == MAP_FAILED)
    {

        perror("mmap:");
    }
    *(volatile uint16_t *)(map_base + pgoffset) = val;
    close(fd);
    munmap((void *)map_base, PAGE_SIZE);
}
int Xil_In16(uint64_t phyaddr)
{
    int fd;
    uint16_t val;
    volatile uint8_t *map_base;
    uint64_t base = phyaddr & PAGE_MASK;
    uint64_t pgoffset = phyaddr & (~PAGE_MASK); //open /dev/mem
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
        perror("open /dev/mem:");
    } //mmap
    map_base = (volatile uint8_t *)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
    if(map_base == MAP_FAILED)
    {

        perror("mmap:");
    }
    val = *((volatile uint16_t *)(map_base + pgoffset));
    close(fd);
    munmap((void *)map_base, PAGE_SIZE);
    return val;
}
void Xil_Out8(uint64_t phyaddr, uint16_t val)
{

    int fd;
    volatile uint8_t *map_base;
    uint64_t base = phyaddr & PAGE_MASK;
    uint64_t pgoffset = phyaddr & (~PAGE_MASK);
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {

        perror("open /dev/mem:");
    }
    map_base = (volatile uint8_t *)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
    if(map_base == MAP_FAILED)
    {

        perror("mmap:");
    }
    *(volatile uint8_t *)(map_base + pgoffset) = val;
    close(fd);
    munmap((void *)map_base, PAGE_SIZE);
}
int Xil_In8(uint64_t phyaddr)
{

    int fd;
    uint8_t val;
    volatile uint8_t *map_base;
    uint64_t base = phyaddr & PAGE_MASK;
    uint64_t pgoffset = phyaddr & (~PAGE_MASK); //open /dev/mem
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {

        perror("open /dev/mem:");
    } //mmap
    map_base = (volatile uint8_t *)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
    if(map_base == MAP_FAILED)
    {
        perror("mmap:");
    }
    val = *(volatile uint8_t *)(map_base + pgoffset);
    close(fd);
    munmap((void *)map_base, PAGE_SIZE);
    return val;
}
