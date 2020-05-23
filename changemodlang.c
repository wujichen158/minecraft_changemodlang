#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum { false, true } bool;
 
char source[16],target[16];

bool read()
{
	printf("欢迎来到minecraft mod语言文件转换程序！\n");
	printf("请输入源语言文件名（例如en_US）并按下回车：\n");
	scanf("%s",source);
	printf("请输入目标语言文件名（例如zh_CN）并按下回车：\n");
	scanf("%s",target);
	printf("是否在词条内保留源语言的内容？\n输入y表示保留，输入n表示不保留\n");
	getchar();
	char save;
	while(~scanf("%c",&save))
	{
		if(save=='y')
			return true;
		else if(save=='n')
			return false;
		else
			printf("输入有误！请重新输入\n");
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
	fp_res=fopen("转换结果.lang","w+");
	fp_lineNo=fopen("未翻译的行号.txt","a");
	if(fp_src==NULL || fp_res==NULL || fp_lineNo==NULL)
	{
		printf("源文件未能成功打开！\n");
		return 1;
	}
	
	int i=0; //记录未翻译的行号 
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
				printf("目标文件未能成功打开！\n");
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
	printf("操作完成！转换结果.lang文件为结果，未翻译的行号保存在未翻译的行号.txt文件内\n"); 
	return 0;
}
