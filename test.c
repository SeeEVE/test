#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int execmd(const char * cmd, char * result, int len)
{
	char buffer[128];
	result[0] = '\0';   // resultԭ�����ݻ�ֱ�ӱ�����
	FILE* pipe = popen(cmd, "r");  // �򿪹ܵ�����ִ������
	if (!pipe) return -2;  // ����ʧ��
	while(!feof(pipe) && len>1)
		{
			int limit = len>128 ? 128: len;
			if(fgets(buffer, limit, pipe))  // ���ܵ������result��
				{
					strcat(result, buffer);
					len -= strlen(buffer);
				}
		}
	if(len<=1 && !feof(pipe))
		{
			pclose(pipe);  // �رչܵ�
			printf("\n[�ܵ�δ����]\n");
			return -3;  // δ����
		}
	pclose(pipe);  // �رչܵ�
	return 1;  // ���гɹ�
}

int main()
{
	char cmd[64] = "rasphone -h \"Dr.COM\"";  //�Ͽ� 
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
	printf(">>%s\n", cmd);
	puts("-------------------------------------");
	cmd[j] = temp;
	execmd(cmd, result, 512);
	printf("%s\n", result);
	puts("-------------------------------------");
	if (strstr(result, "���������")) {
		Sleep(2500);		
	} else {
		system("pause");
	}
	
	return 0;
}

