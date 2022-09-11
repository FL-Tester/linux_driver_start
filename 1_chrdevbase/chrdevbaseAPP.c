#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

/*******************************************************
filename:       chrdevbaseAPP.c
description:    chrdevbase driver example
author:         FengLE
email:          yuanfanggaodi@gmail.com
version:        1.0
date:           2022-09-11
copyobj:        正点原子
*******************************************************/

static char usrdata[] = {"usr data!"};

//正常的文件打开以及读写操作
int main(int argc, char *argv[])
{
    int fd, retvalue;
    char *filename;
    char readbuf[100], writebuf[100];

    if(argc != 3){
		printf("Error Usage!\r\n");
		return -1;
	}

    filename = argv[1];

    //打开驱动文件
    fd = open(filename, O_RDWR);
    if(fd < 0){
       printf("Can't open file %s\r\n", filename);
	   return -1; 
    }
    
    if(atoi(argv[2]) == 1){
        retvalue = read(fd, readbuf, 50);

		if(retvalue < 0){
			printf("read file %s failed!\r\n", filename);
		}else{
			/*  读取成功，打印出读取成功的数据 */
			printf("read data:%s\r\n",readbuf);
		}
    }

    //atoi 把字符串转换为整型的函数
    if(atoi(argv[2]) == 2){
 	/* 向设备驱动写数据 */
		memcpy(writebuf, usrdata, sizeof(usrdata));
		retvalue =  (fd, writebuf, 50);
		if(retvalue < 0){
			printf("write file %s failed!\r\n", filename);
		}
	}

    /* 关闭设备 */
	retvalue = close(fd);

	if(retvalue < 0){
		printf("Can't close file %s\r\n", filename);
		return -1;
	}
	
    return  0;
}