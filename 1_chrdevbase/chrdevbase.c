#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
/*******************
filename:       chrdevbase.c
description:    chrdevbase driver file--- my frist linux driver file 
author:         FengLE
email:          yuanfanggaodi@gmail.com
version:        1.0
date:           2022-09-11
copyobj:        正点原子
*******************/

//主设备好 设备名
#define CHRDEVBASE_MARJOR           199
#define CHRDEVBASE_NAME             "chrdevbase"

//定义读写缓冲区和字符串数组
static char readbuf[100];
static char writebuf[100];
static char kerneldata[] = {"kernel data!"};

//函数声明
static int chrdevbase_open(struct inode *inode, struct file *filp);
static ssize_t chrdevbase_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt);
static ssize_t chrdevbase_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt);
static int chrdevbase_release(struct inode *inode, struct file *filp);

/*
 * 设备操作函数结构体 
 很关键 字符设备需要操作的函数 一般都会齐全 根据自己的需要 设置相对于的函数 用到就写 
 这中写法是c中最像面向对象的写法 由于结构体中无法声明函数 但是可以声明函数指针
 */
static struct file_operations chrdevbase_fops = {
	.owner = THIS_MODULE,	
	.open = chrdevbase_open,
	.read = chrdevbase_read,
	.write = chrdevbase_write,
	.release = chrdevbase_release
};

//打开设备 
static int chrdevbase_open(struct inode *inode, struct file *filp){
	//printk("chrdevbase open!\r\n");
	return 0;
}

//从设备读取数据
static ssize_t chrdevbase_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt){
    
    //拷贝标志符
    int retvalue = 0;

    //写入readbuf
    memcpy(readbuf, kerneldata, sizeof(kerneldata));

    //拷贝到用户空间的buf
    retvalue = copy_to_user(buf, readbuf, cnt);

    //成功和失败打印情况
    if(retvalue == 0){
        printk("kernel sendata ok!\r\n");
    }else{
        printk("kernel sendata failed!\r\n");
    }


    return 0;
}

//向设备写入数据
static ssize_t chrdevbase_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt){

    int retvalue = 0;

    retvalue = copy_from_user(writebuf, buf, cnt);
    
    if(retvalue == 0){
        printk("kernel recevdata:%s\r\n", writebuf);
    }else{
        printk("kernel recevdata failed!\r\n");
    }        

    return 0;
}

//关闭释放设备
static int chrdevbase_release(struct inode *inode, struct file *filp){
    //printk("chrdevbase release！\r\n");
	return 0;
}



//定义函数
static int __init chardevbase_init(void){

    //设备注册函数 这个注册函数不能分配次设备号 造成设备号的浪费 所以实际工程中 不用这个 应该是吧
    int retvalue = register_chrdev(CHRDEVBASE_MARJOR, CHRDEVBASE_NAME, &chrdevbase_fops);

    //为负数 则注册失败
    if (retvalue < 0){
        printk("chrdevbase driver register failed\r\n");
    }else{
        printk("chrdevbase init!\r\n");
    }

    return 0;
}

static void __exit chardevbase_exit(void){

    //卸载设备函数 这个函数没有返回值
    unregister_chrdev(CHRDEVBASE_MARJOR, CHRDEVBASE_NAME);


	printk("chrdevbase exit!\r\n");
}


//出入口函数的注册
module_init(chardevbase_init);
module_exit(chardevbase_exit);

//license and author 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FengLE");

