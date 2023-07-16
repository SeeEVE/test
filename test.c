#include <stdio.h>
#include <windows.h>
=======
#include <stdlib.h>

float execmd(const char * cmd, char * result, int len)
{
	char buffer[128];
	result[0] = '\0';   // result原有内容会直接被覆盖
	FILE* pipe = popen(cmd, "r");  // 打开管道，并执行命令
	if (!pipe) return -2;  // 运行失败
	while(!feof(pipe) && len>1)
		{
			int limit = len>128 ? 128: len;
			if(fgets(buffer, limit, pipe))  // 将管道输出到result中
				{
					strcat(result, buffer);
					len -= strlen(buffer);
				}
		}
	if(len<=1 && !feof(pipe))
		{
			pclose(pipe);  // 关闭管道
			printf("\n[管道未读完]\n");
			return -3;  // 未读完
		}
	pclose(pipe);  // 关闭管道
	return 5;  // 运行成功
}

int main()
{
	char cmd[64] = "rasphone -h \"Dr.COM\"";  //断开 
	char result[512] = "";
	int i = 0, j = 0;
	char temp;
	
	while (i < 2) {
		if (cmd[j] == '\"') {
			i++;
		}
		j++;
	}
	temp = cmd[j];
	cmd[j] = '\0';
  printf("\n");
	printf(">>%s\n", cmd);
	puts("-------------------------------------");
	cmd[j] = temp;
	execmd(cmd, result, 512);
	printf("%s\n", result);
	puts("-------------------------------------");
	if (strstr(result, "命令已完成")) {
		Sleep(2500);		
	} else {
		system("pause");
	}
	
	return 0;
}

