#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum { false, true } bool;
 
char source[16],target[16];

bool read()
{
	printf("��ӭ����minecraft mod�����ļ�ת������\n");
	printf("������Դ�����ļ���������en_US�������»س���\n");
	scanf("%s",source);
	printf("������Ŀ�������ļ���������zh_CN�������»س���\n");
	scanf("%s",target);
	printf("�Ƿ��ڴ����ڱ���Դ���Ե����ݣ�\n����y��ʾ����������n��ʾ������\n");
	getchar();
	char save;
	while(~scanf("%c",&save))
	{
		if(save=='y')
			return true;
		else if(save=='n')
			return false;
		else
			printf("������������������\n");
	}
}

int main()
{
	FILE *fp_src,*fp_res,*fp_lineNo;
	char line[1024];
	bool hasSRC=read();
	char source_temp[16];
	
	strcpy(source_temp,source);
	fp_src=fopen(strcat(source,".lang"),"r");
	strcat(target,".lang");
	fp_res=fopen("ת�����.lang","w+");
	fp_lineNo=fopen("δ������к�.txt","a");
	if(fp_src==NULL || fp_res==NULL || fp_lineNo==NULL)
	{
		printf("Դ�ļ�δ�ܳɹ��򿪣�\n");
		return 1;
	}
	
	int i=0; //��¼δ������к� 
	while( fgets(line,sizeof(line),fp_src) )
	{
		i++;
		if(line[0]=='\n' || line[0]=='#')
		{
			fprintf(fp_res,"%s",line);
			continue;
		}
		if(NULL!=strchr(line,'='))
		{
			FILE *fp_tgt=fopen(target,"r");
			if( fp_tgt==NULL )
			{
				printf("Ŀ���ļ�δ�ܳɹ��򿪣�\n");
				return 1;
			}
			
			char str_transKey[1024];
			memset(str_transKey,0,sizeof(str_transKey));
			strncpy(str_transKey,line,(strchr(line,'=')-line)*sizeof(char));
			char line_temp[1024];
			memset(line_temp,0,sizeof(line_temp));
			bool find_flag=false;
			
			while( fgets(line_temp,sizeof(line_temp),fp_tgt) )
			{
				if(NULL!=strstr(line_temp,str_transKey))
				{
					fprintf(fp_res,"%s",line_temp);
					find_flag=true;
					break;
				}
			}
			if(!find_flag)
			{
				if(hasSRC)
					fprintf(fp_res,"%s",line);
				else
					fprintf(fp_res,"%s=\n",str_transKey);
				fprintf(fp_lineNo,"%d\n",i);
			}
			fclose(fp_tgt);
		}
	}
	fclose(fp_src);
	fclose(fp_res);
	fclose(fp_lineNo);
	printf("������ɣ�ת�����.lang�ļ�Ϊ�����δ������кű�����δ������к�.txt�ļ���\n"); 
	return 0;
}
