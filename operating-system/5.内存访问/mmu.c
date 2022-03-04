#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PSIZE 1024    //页大小
#define DLEN 10       //逻辑地址和物理地址中页内偏移所占的位数
#define PNUM 8        //逻辑页面数
#define PLEN 3        //逻辑地址中页号所占的位数
#define FNUM 16       //物理帧数
#define FLEN 4        //页表条目中物理帧数占4位,可表示16帧
#define TNUM 4        // TLB中缓存的条目数
#define PROSIZE 7000  //进程大小

int PageTable[PNUM] = {0x000C, 0x0008, 0x0005, 0x000A, 0x000F, 0x0000, 0x000F, 0x000F};
int TLB[TNUM] = {0x001C, 0x0118, 0x0215, 0x001A};

int searchTLB(int p) {
    for (int i = 0; i < TNUM; i++) {
        if (TLB[i] >> PNUM == p) {
            printf("TLB命中 -> ");
            return TLB[i] & 0xF;
        }
    }

    return -1;
}

void updateTLB(int TLB_addr) {  //随机替换
    TLB[rand() % 4] = TLB_addr;
}

void MMU(int v_addr) {
    if (v_addr > PSIZE * PNUM) {
        printf("访问越界\n");
        return;
    }

    int p = v_addr >> DLEN;   //逻辑地址页号
    int d = v_addr & 0x03FF;  //逻辑地址帧号（偏移量）
    int f = searchTLB(p);     //获取页表的低四位帧号
    int p_addr;

    if (f == -1) {
        int v = (PageTable[p] >> FLEN) & 0x1;  //获取页表的有效（无效）位

        if (v == 0) {  //无效
            printf("无效页\n");
            return;
        } else if (v_addr >= PROSIZE) {  //内部碎片判断
            printf("内部碎片区域\n");
            return;
        } else {                                           //有效
            f = PageTable[p] & 0xF;                        //获取页表的低四位帧号
            PageTable[p] = PageTable[p] | 0x020;           //访问位置1
            PageTable[p] = PageTable[p] | (rand() % 2);    //修改位随机置0或1
            updateTLB(p << PNUM | (PageTable[p] & 0xFF));  //缓存到TLB
        }
    }

    p_addr = (f << DLEN) + d;  //页表映射的物理起始地址加上地址偏移量
    printf("您访问的物理地址为：%x\n", p_addr);
}

//刷新PageTable的有效（无效）位
void refresh() {
    for (int i = 0; i < PNUM; i++) {
        if (i <= PROSIZE >> DLEN) {
            PageTable[i] = PageTable[i] | 0x010;
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    refresh();

    MMU(9000);
    MMU(8000);
    MMU(7000);
    MMU(6000);
    MMU(6500);
    MMU(5000);
    MMU(4500);
    MMU(0);
    MMU(4000);
    MMU(3000);
    MMU(1000);
    MMU(2000);
}