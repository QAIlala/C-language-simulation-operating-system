#include <bits/stdc++.h>     
using namespace std;
int n;
//进程模拟
struct jincheng
{ 
	int pid;
	int youxian;
	int daxiao;
};
struct jincheng jiuxu[20];//就绪数组。
struct jincheng guaqi[20];//挂起数组。
struct jincheng cpu;//运行进程。
int shumu1=0,shumu2=0,first=0;//shumu1 表示就绪的进程数，shumu2 表示，first表示第一个创建的进程。

//处理机调度
struct job
{
	char status;
	char name[10];
	float arrtime;
	float reqtime;
	float startime;
	float finitime;
	float zhouzhuan;
};
//内存管理
int wulikuai; //物理块数
int yemianshu; //页面数
int queyeshu; //缺页数
int zouxiang[100]; //页面走向数组
int *neicun; //内存中的物理块
int *xia; //当前内存与下一次的距离
int *shang; //当前内存与上一次的距离
int *fangwen; //用于clock中做访问位

void mulu(); //声明目录函数


//文件管理系统
struct File 
{
	char user; 
	int fid;
	char name[10];
	char status[10];
	string content;
};
vector<File> FV[4];

//进程模拟。
void create()              //创建新进程
{
	if(shumu1>=20)
	{
		printf("\n 就绪进程已满,请先删除或挂起进程\n");
	}
	else
	{
		if(first==0)
		{
			cout<<"\n 这是你第一次输入进程信息,它将直接调入 CPU 运行!";
			cout<<"\n 请输入新进程的 pid\n";
			cin>>cpu.pid;
			cout<<"请输入新进程的优先级\n";
			cin>>cpu.youxian;
			cout<<"请输入新进程的大小\n";
			cin>>cpu.daxiao;
			first++;
		}
		else
		{
			cout<<"\n 请输入新进程的 pid\n";
			cin>>jiuxu[shumu1].pid;
			cout<<"请输入新进程的优先级\n";
			cin>>jiuxu[shumu1].youxian;
			cout<<"请输入新进程的大小\n";
			cin>>jiuxu[shumu1].daxiao;
			shumu1++;
		}
	}
}

void run()
{
	cout<<"\n 现在正在运行的进程的资料如下:\n";
	printf("PID 码 为 :%d;\n 优 先 级 为 :%d;\n 大 小为:%d.",cpu.pid,cpu.youxian,cpu.daxiao);
}//查看运行进程。

void huanchua()//将优先数小的进程换入，并换出当前正在执行的进程
{
	int i,p,m,n,t;
	p=jiuxu[0].youxian;
	for(i=0;i<shumu1;i++)//找优先数最小的进程
	{
		if(p>jiuxu[i].youxian)
		{
			p=jiuxu[i].youxian;
		}
	}
	for(i=0;i<20;i++)//换出当前正在运行的进程
	{
		if(p==jiuxu[i].youxian)
		{
			m=cpu.daxiao;
			cpu.daxiao=jiuxu[i].daxiao;
			n=cpu.pid;
			cpu.pid=jiuxu[i].pid;
			t=cpu.youxian;
			cpu.youxian=jiuxu[i].youxian;
			break;
		}
		else continue;
	}
	for(i=0;i<shumu1-1;i++)//将换入的进程从就绪队列中删除，并将换出的进程插入到就绪队列的最后
	{
		jiuxu[i].daxiao=jiuxu[i+1].daxiao;
		jiuxu[i].pid=jiuxu[i+1].pid;
		jiuxu[i].youxian=jiuxu[i+1].youxian;
	}
	jiuxu[i].daxiao=m;
	jiuxu[i].pid=n;
	jiuxu[i].youxian=t;
}

void huanchub()//根据输入的 p 挂起一个进程
{
	int i,p;
	printf("\n 请输入想要挂起的进程的 PID 码:\n(在以下中选:");
	for(i=0;i<shumu1;i++)
	{
		printf("%d ",jiuxu[i].pid);
	}
	printf(")\n");
	scanf("%d",&p);
	for(i=0;i<shumu1;i++)
	{
		if(p==jiuxu[i].pid)
		{
			guaqi[shumu2].daxiao=jiuxu[i].daxiao;
			guaqi[shumu2].pid=jiuxu[i].pid;
			guaqi[shumu2].youxian=jiuxu[i].youxian;
			shumu2++;
			break;
		}
		else continue;
	}
	for(i=0;i<shumu1;i++)
	{
		jiuxu[i].daxiao=jiuxu[i+1].daxiao;
		jiuxu[i].pid=jiuxu[i+1].pid;
		jiuxu[i].youxian=jiuxu[i+1].youxian;
	}
	shumu1--;
}
void huanchuc()//激活一个进程
{
	int i;
	jiuxu[shumu1].daxiao=guaqi[0].daxiao;
	jiuxu[shumu1].pid=guaqi[0].pid;
	jiuxu[shumu1].youxian=guaqi[0].youxian;
	shumu1++;
	for(i=0;i<shumu2;i++)
	{
		guaqi[i].daxiao=guaqi[i+1].daxiao;
		guaqi[i].pid=guaqi[i+1].pid;
		guaqi[i].youxian=guaqi[i+1].youxian;
	}
	shumu2--;
}
void huanchud()//根据输入的 pid 号，将 cpu 分配给该进程，并挂起正在执行的进程
{
	int i,p,m,n,t;
	printf("\n 请输入想要运行的进程的 PID 码:\n(在以下中选:");
	for(i=0;i<shumu1;i++)
	{
		printf("%d ",jiuxu[i].pid);
	}
	printf(")\n");
	scanf("%d",&p);
	for(i=0;i<shumu1;i++)
	{
		if(p==jiuxu[i].pid)
		{
			m=cpu.daxiao;
			cpu.daxiao=jiuxu[i].daxiao;
			jiuxu[i].daxiao=m;
			n=cpu.pid;
			cpu.pid=jiuxu[i].pid;
			jiuxu[i].pid=n;
			t=cpu.youxian;
			cpu.youxian=jiuxu[i].youxian;
			jiuxu[i].youxian=t;
			break;
		}
		else continue;
	}
}
void huanchue()
{
	int i,p;
	printf("\n 请输入想要调入就绪的进程的 PID 码:\n(在以下中选:");
	for(i=0;i<shumu2;i++)
	{
		printf("%d ",guaqi[i].pid);
	}
	printf(")\n");
	scanf("%d",&p);
	for(i=0;i<shumu2;i++)
	{
		if(p==guaqi[i].pid)
		{
			jiuxu[shumu1].daxiao=guaqi[i].daxiao;
			jiuxu[shumu1].pid=guaqi[i].pid;
			jiuxu[shumu1].youxian=guaqi[i].youxian;
			break;
		}
		else continue;
	}
	shumu1++;
	for(i=0;i<shumu2;i++)
	{
		guaqi[i].daxiao=guaqi[i+1].daxiao;
		guaqi[i].pid=guaqi[i+1].pid;
		guaqi[i].youxian=guaqi[i+1].youxian;
	}
	shumu2--;
}
//交换进程的原码。
void huanchu()
{
	int a;
	cout<<"请你选择需要的交换方式:\n";
	cout<<"1.将优先级高的进程调入 CPU 执行.\n";
	cout<<"2.手动将进程挂起.\n";
	cout<<"3.将挂起的进程按先如先出的方式调入就绪队列.\n";
	cout<<"4.手动将就绪进程调入 CPU 执行.\n";
	cout<<"5.手动将挂起的进程调入就绪队列.\n";
	cin>>a;
	switch(a)
{
	case 1: huanchua();break;
	case 2: huanchub();break;
	case 3: huanchuc();break;
	case 4: huanchud();break;
	case 5: huanchue();break;
	default:break;
}
}
void del()
{
	int i,p;
	printf("\n 请输入想要删除的进程的 PID 码:\n(在以下中选:");
	for(i=0;i<shumu2;i++)
	{
		printf("%d ",guaqi[i].pid);
	}
	printf("\n");
	scanf("%d",&p);
	for(i=0;i<shumu2;i++)
	{
		if(p==guaqi[i].pid)
		{
			for(i=0;i<shumu2;i++)
			{
				guaqi[i].daxiao=guaqi[i+1].daxiao;
				guaqi[i].pid=guaqi[i+1].pid;
				guaqi[i].youxian=guaqi[i+1].youxian;
			}
			shumu2--;
			break;
		}
		else continue;
	}
}
void os1()
{
	int a;
	while(1)
	{
		cout<<"********************************************\n";
		cout<<"*              进程管理系统                *\n";
		cout<<"*------------------------------------------*\n";
		cout<<"*               请选择操作                 *\n";
		cout<<"*------------------------------------------*\n";
		cout<<"*              1.创建新的进程              *\n";
		cout<<"*              2.查看运行进程              *\n";
		cout<<"*              3.换出某个进程              *\n";
		cout<<"*              4.删除某个进程              *\n";
		cout<<"*              5.退出系统                  *\n";
		cout<<"********************************************\n";
		cout<<"请选择（1～5)\n";
		cin>>a;
		if(a==1)
		{
			create();
		}
		else if(a==2)
		{
			run();
		}
		else if(a==3)
		{
			huanchu();
		}
		else if(a==4)
		{
			del();
		}
		else if(a==5)
		{
			break;
		}
		else
		{
			printf("输入有错!\n");
		}
		printf("\n********************************************");
	}
}

//处理及调度
void FCFS(job jobs[10],int temp[100],int jobnum)
{
	
	int i=0;
	jobs[temp[0]].startime=jobs[temp[0]].arrtime;
	jobs[temp[0]].finitime=jobs[temp[0]].arrtime+jobs[temp[0]].reqtime;
	jobs[temp[0]].zhouzhuan=jobs[temp[0]].finitime-jobs[temp[0]].arrtime;
	for(i=1;i<jobnum;i++)
	{
		jobs[temp[i]].startime=jobs[temp[i-1]].finitime;
		jobs[temp[i]].finitime=jobs[temp[i]].startime+jobs[temp[i]].reqtime;
		jobs[temp[i]].zhouzhuan=jobs[temp[i]].finitime-jobs[temp[i]].arrtime;
	}
	cout<<"\n\n";
	cout<<"调用先到先服务算法:\n\n";
	cout<<"作业名   到达系统时间   CPU所需时间/h   开始时间   结束时间   周转时间/h\n";
	for(i=0;i<jobnum;i++)
	{    
		cout<<jobs[temp[i]].name;
		cout<<jobs[temp[i]].arrtime;
		cout<<jobs[temp[i]].reqtime;
		cout<<jobs[temp[i]].startime;
		cout<<jobs[temp[i]].finitime;
		cout<<jobs[temp[i]].zhouzhuan;        
		cout<<"\n";
	}
}
void os2()
{
	job jobs[10];
	int jobnum,i;
	int temp[100];
	int x,y;
	int k=0;
	int choice;
	
	while(1)
	{   
		cout<<"*************************************\n";
		cout<<"*           处理机调度系统          *\n";
		cout<<"*-----------------------------------*\n";
		cout<<"*            请选择操作             *\n";
		cout<<"*-----------------------------------*\n";
		cout<<"*           1.开始FCFS算法调度      *\n";
		cout<<"*           2.退出                  *\n";
		cout<<"*************************************\n";
		cout<<"请输入操作：\n";
		cin>>choice;
		if(choice==1)
		{
			cout<<"请输入作业个数:";
			cin>>jobnum;
			for(i=0;i<jobnum;i++)
			{
				printf("第%d个作业:\n",i+1);
				printf("作业%d名称:",i+1);
				cin>>jobs[i].name;
				printf("到达系统时间:");
				scanf("%f",&jobs[i].arrtime);
				printf("CPU所需时间:");
				scanf("%f",&jobs[i].reqtime);
				temp[i]=i;
			}
			//按到达系统时间排序
			for(x=0;x<jobnum;x++)
			{
				for(y=x+1;y<jobnum;y++)
				{
					if(jobs[temp[x]].arrtime>jobs[y].arrtime)
					{
						k=temp[x];
						temp[x]=temp[y];
						temp[y]=k;
					}
				}
			}
			cout<<"\n按到达系统时间排序:\n";
			for(i=0;i<jobnum;i++)
			{
				cout<<"\t作业名\t到达时间\t需要时间\n";
				printf("\t%d",i+1);
				printf("\t%s",jobs[temp[i]].name);
				printf("\t%.2f",jobs[temp[i]].arrtime);
				printf("\t%.2f",jobs[temp[i]].reqtime);
				printf("\n");
			}
		}	
		else if(choice==2)
			break;
	}
}

//内存管理系统
void shuru() //输入
{
	cout<<"页面数:";
	cin>>yemianshu;
	cout<<"页面走向:";
	for (int i=0;i<yemianshu;i++) 
		cin>>zouxiang[i];
	cout<<"物理块数:";
	cin>>wulikuai;
	neicun=(int*)malloc(sizeof(int)*wulikuai); //指针变量分配空间
	xia=(int*)malloc(sizeof(int)*wulikuai);
	shang=(int*)malloc(sizeof(int)*wulikuai);
	fangwen=(int*)malloc(sizeof(int)*wulikuai);
}

void xianshi() //显示现有内存中的物理块
{
	for (int i=0;i<wulikuai;i++) //遍历现有内存
	{
		if (neicun[i]>=0) //逐个输出
			printf("%d ",neicun[i]);
	}
}

int zhao(int *a,int x) //找一下传入的页面是否在内存中
{
	for (int i=0;i<wulikuai;i++) //遍历现有内存
	{
		if (x==a[i]) //找到
		{
			return i;
		}	
	}
	return -1; //内存中没有，返回-1
}

int xiajuli(int i,int j,int* a) //统计内存中的某个页面，离下一次出现的距离
{ //i表示从页面走向里的第几个页面开始搜索，j是内存中的某个页面，a是页面走向
	int juli=0; 
	while (i<yemianshu&&j!=a[i]) //在页面走向中逐个搜索并且不匹配时
	{  
		juli++; //距离数增加
		i++; //下一个页面
	}
	if (i>=yemianshu) //页面走向搜索完，说明没找到匹配的
		return juli+1;
	else //没搜索完，找到匹配的
		return juli; 
}

int shangjuli(int i,int j,int*a) //统计内存中的某个页面，离上一次出现的距离
{ //i表示从页面走向里的第几个页面开始搜索，j是内存中的某个页面，a是页面走向
	int juli=0;
	while (i>=0&&j!=a[i]) //在页面走向中逐个向前搜索并且不匹配时
	{
		juli++; //距离数增加
		i--; //下一个页面
	}
	if (i<0) //页面走向搜索完，说明没找到匹配的
		return juli+1;
	else //没搜索完，找到匹配的
		return juli;
}

int max(int *a) //用来找一个数组中最大的
{
	int k=0;
	int max=a[0];
	for (int i=1;i<wulikuai;i++) //遍历现有内存
	{
		if (a[i]>max)
		{
			max=a[i];
			k=i;
		}
	}
	return k; //返回最大值的下标
}

void OPT() //最佳置换
{
	int i=0,j=0;
	int taotai=-1; //要淘汰的页面
	queyeshu=0; //缺页个数
	while (i<yemianshu) //对页面走向逐个访问
	{
		printf("访问%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //页面不在内存中
		{  
			if (j<wulikuai) //内存不满
			{
				neicun[j]=zouxiang[i]; //页面直接进入内存
				j++;
			}
			else //内存满，找页面换出
			{
				for (int k=0;k<wulikuai;k++) //遍历现有内存
				{
					xia[k]=xiajuli(i+1,neicun[k],zouxiang); //统计当前内存与下一次的距离
				}
				int m=max(xia); //找内存中距离最远的页面
				taotai=neicun[m]; //记录要淘汰的页面
				neicun[m]=zouxiang[i]; //把距离最远的页面换出去
			}
			xianshi();
			if (taotai==-1) //内存不满的时候进去的，没有淘汰页面
			{
				for (int k=j;k<wulikuai;k++)
				{
					printf("  "); //输出空格，为了使页面美观
				}
				printf(" 未命中 ");
				printf("\n");
			}
			else
			{
				printf(" 未命中 ");
				printf("淘汰%d\n",taotai);
			}
			queyeshu++; //统计缺页数
		}
		else //页面在内存中，就直接显示
		{
			xianshi();
			if (taotai==-1) //如果此时内存不满
			{
				for (int k=j;k<wulikuai;k++)
				{
					printf("  "); //输出空格，为了使页面美观
				}
			}
			printf(" 命中\n");
		}
		i++; //一个页面访问完成，进行下一个页面
	}
	printf("缺页次数:%d\n",queyeshu);
	printf("缺页率:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
	memset(neicun,-1,sizeof(int)*wulikuai); //memset是在一段内存块中填充给定的值，对指针初始化
}

void FIFO() //先进先出
{
	int i=0,j=0;
	int taotai=-1; //要淘汰的页面
	queyeshu=0; //缺页个数
	queue<int>duilie; //队列初始化
	while (i<yemianshu) //对页面走向逐个访问
	{
		printf("访问%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //页面不在内存中
		{
			if (j<wulikuai) //内存不满
			{
				neicun[j]=zouxiang[i]; //页面直接进入内存
				j++;
				duilie.push(zouxiang[i]); //页面入队
			}
			else //内存满，找页面换出
			{
				for (int k=0;k<wulikuai;k++) //遍历现有内存
				{
					if (neicun[k]==duilie.front()) //找到队列第一个被放入的页面，在内存中的位置，淘汰
					{
						taotai=neicun[k]; //记录要淘汰的页面
						neicun[k]=zouxiang[i]; //把第一个放入的页面换出去
						duilie.pop(); //从队列中移除
						duilie.push(zouxiang[i]); //页面入队
						break;
					}
				}
			}
			xianshi();
			if (taotai==-1) //内存不满的时候进去的，没有淘汰页面
			{
				for (int k=j;k<wulikuai;k++)
				{
					printf("  "); //输出空格，为了使页面美观
				}
				printf(" 未命中 ");
				printf("\n");
			}
			else
			{
				printf(" 未命中 ");
				printf("淘汰%d\n",taotai);
			}
			queyeshu++; //统计缺页数
		}
		else //页面在内存中，就直接显示
		{
			xianshi();
			if (taotai==-1) //如果此时内存不满
			{
				for (int k=j;k<wulikuai;k++)
				{
					printf("  "); //输出空格，为了使页面美观
				}
			}
			printf(" 命中\n");
		}
		i++; //一个页面访问完成，进行下一个页面
	}
	printf("缺页次数:%d\n",queyeshu);
	printf("缺页率:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
	memset(neicun,-1,sizeof(int) * wulikuai); //memset是在一段内存块中填充给定的值，对指针初始化
}   

void os3()
{
	int xuan; //菜单选择的功能号
	while(1)
	{	
		cout<<"********************************************\n";
		cout<<"*              内存管理系统                *\n";
		cout<<"*------------------------------------------*\n";
		cout<<"*              1.输入                      *\n";
		cout<<"*              2.OPT页面置换算法           *\n";
		cout<<"*              3.FIFO页面置换算法          *\n";
		cout<<"*              4.退出                      *\n";
		cout<<"********************************************\n";
		cout<<"*请选择操作:\n";
		cin>>xuan;
		if(xuan==1)
		{
			shuru();
		}
		else if(xuan==2)
		{
			printf("\nOPI算法:\n");
			OPT();
		}
		else if(xuan == 3)
		{
			printf("\nFIFO算法:\n");
			FIFO();
		}
		else if (xuan == 4)
			break;
	}
}


//文件管理系统
void instructframe()
{ 
	cout<<"--------------------------------------------------------------------------------\n";
	cout<<"******************************请执行指令****************************************\n";
	cout<<"--------------------------------------------------------------------------------\n";
	printf("1、创建新文件\t2、删除文件\n3、打开文件\t4、关闭文件\n5、读出文件\t6、写入文件\n7、退出\n");
}

void Creat(int id)
{
	if (FV[id].size() < 10)
	{
		File f;
		printf("请输入新建的文件名：\n");
		scanf("%s", f.name);
		f.fid = FV[id].size() + 1;
		f.user = id + 'A';
		memset(f.status, '\0', sizeof(f.status));
		strcpy(f.status, "close");
		FV[id].push_back(f);
	}
	else
	{
		printf("文件数目过多\n");
	}
}

void Delete(int id)
{
	printf("请输入你需要删除文件的序号：\n");
	int fid;
	scanf("%d", &fid);
	for (int i = 0; i < FV[id].size(); i++)
	{
		if (FV[id][i].fid == fid)
		{
			FV[id].erase(FV[id].begin() + i);
			printf("已删除\n");
			break;
		}
		if(i == FV[id].size()-1)
		{
			cout<<"不存在此文件\n";
		}
	}
}

void Open(int id)
{
	printf("请输入你需要打开文件的序号：\n");
	int fid;
	bool judge=false;
	scanf("%d", &fid);
	for (int i = 0; i < FV[id].size(); i++)
	{
		if(strcmp(FV[id][i].status, "open")==0) 
			judge=true;
		if (FV[id][i].fid == fid)
		{//检查是否有已打开文件
			if(judge)
			{
				cout<<"无法打开，存在已打开文件\n";
			}         
			else
			{
				strcpy(FV[id][i].status, "open");
				printf("已打开\n");
			}
			break;
		}
		if(i == FV[id].size()-1)
		{
			cout<<"不存在此文件\n";
		}
	}
}

void Close(int id)
{
	printf("请输入你需要关闭文件的序号：\n");
	int fid;
	scanf("%d", &fid);
	for (int i = 0; i < FV[id].size(); i++)
	{
		if (FV[id][i].fid == fid)
		{
			strcpy(FV[id][i].status, "close");
			break;
			printf("已关闭\n");
		}
		if(i == FV[id].size()-1)
		{
			cout<<"不存在此文件\n";
		}
	}
}

void Read(int id)
{
	printf("请输入你需要读取文件的序号：\n");
	int fid;
	scanf("%d", &fid);
	for (int i = 0; i < FV[id].size(); i++)
	{
		if (FV[id][i].fid == fid)
		{
			if(strcmp(FV[id][i].status, "open")==0)
			{
				cout << FV[id][i].content << endl;
				strcpy(FV[id][i].status, "read");
				printf("已成功读取\n");
			}
			else
			{
				cout<<"文件未打开，无法读取\n";
			}
			break;
		}
		if(i == FV[id].size())
		{
			cout<<"不存在此文件\n";
		}
	}
}

void Write(int id)
{
	printf("请输入你需要写入文件的序号：\n");
	int fid;
	scanf("%d", &fid);
	for (int i = 0; i < FV[id].size(); i++)
	{
		if (FV[id][i].fid == fid)
		{
			if(strcmp(FV[id][i].status, "open")==0)
			{
				cout << "请输入希望写入的内容(请以'#'结束)：" << endl;
				string temp;
				char t;
				while (t != '#')
				{
					t = getchar();
					if (t != '#')
						temp = temp + t;
				}
				FV[id][i].content = FV[id][i].content + temp;
				strcpy(FV[id][i].status, "write");
				printf("已写入\n");
			}
			else
			{
				cout<<"文件未打开，无法写入\n";
			}
			
			break;
		}
		if(i == FV[id].size()-1)
		{
			cout<<"不存在此文件\n";
		}
	}
}
void os4()
{
	char option;
	cout<<"*************************************\n";
	cout<<"*            文件管理系统           *\n";
	cout<<"*-----------------------------------*\n";
	cout<<"*             请选择用户            *\n";
	cout<<"*-----------------------------------*\n";
	cout<<"*                1.A                *\n";
	cout<<"*                2.B                *\n";
	cout<<"*                3.C                *\n";
	cout<<"*                4.D                *\n";
	cout<<"*************************************\n";
	cout<<"请输入用户名以进入文件管理系统:\n";
	cin>>option;
	getchar();
	if (option - 'A' < 4 && option - 'A' >= 0)
	{
		int id = option - 'A';
		instructframe();
		int op = -1;
		while (op != 10)
		{
			printf("请输入指令序号：\n");
			scanf("%d", &op);
			if (op == 1)
			{
				Creat(id);
			}
			else if (op == 2)
			{
				Delete(id);
			}
			else if (op == 3)
			{
				Open(id);
			}
			else if (op == 4)
			{
				Close(id);
			}
			else if (op == 5)
			{
				Read(id);
			}
			else if (op == 6)
			{
				Write(id);
			}
			else if (op == 7)
			{
				break;
			}
		}
	}
}


int main() 
{	
	while(1)
	{
		cout<<"*********************************************\n";
		cout<<"*                操作系统                   *\n";
		cout<<"*-------------------------------------------*\n";
		cout<<"*            请选择你需要的功能             *\n";
		cout<<"*-------------------------------------------*\n";
		cout<<"*              1.进程管理                   *\n";
		cout<<"*              2.处理机调度                 *\n";
		cout<<"*              3.存储管理                   *\n";
		cout<<"*              4.文件管理                   *\n";
		cout<<"*********************************************\n\n";
		cin>>n;
		if(n==1)
		{
			os1();
		}
		else if(n==2)
		{
			os2();
		}
		else if(n==3)
		{
			os3();
		}
		else if(n==4)
		{
			os4();
		}
	}
}
