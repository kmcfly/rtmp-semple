/**
 * Simplest Librtmp Send 264
 *
 * 雷霄骅，张晖
 * leixiaohua1020@126.com
 * zhanghuicuc@gmail.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 * 本程序用于将内存中的H.264数据推送至RTMP流媒体服务器。
 * This program can send local h264 stream to net server as rtmp live stream.
 */

#include <stdio.h>
#include "librtmp_send264.h"

#include <windows.h>

FILE *fp_send1;

//读文件的回调函数
//we use this callback function to read data from buffer
int read_buffer1(unsigned char *buf, int buf_size ){
	if(!feof(fp_send1)){
		int true_size=fread(buf,1,buf_size,fp_send1);
		return true_size;
	}else{
		return -1;
	}
}

int main(int argc, char* argv[])
{
	while(1)
	{


	fp_send1 = fopen("cuc_ieschool.h264", "rb");

	//初始化并连接到服务器
	while(1)
	{
		bool bConnect = RTMP264_Connect("rtmp://localhost/live/_definst_");//("rtmp://localhost/publishlive/livestream");
		printf("connect to rtmp://127.0.0.1:1234/stream/live ............\n");
		if(bConnect)
			break;
		Sleep(1000);
	}
	
	//发送
	RTMP264_Send(read_buffer1);

	//断开连接并释放相关资源
	RTMP264_Close();

	Sleep(10);
	}
	return 0;
}

