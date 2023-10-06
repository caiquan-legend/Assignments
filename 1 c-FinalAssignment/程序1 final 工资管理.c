#define _CRT_SECURE_NO_WARNINGS 1//Visual Studio 2022 scanf,sprintf的使用需要(若不是此编译器则需要删除此句)
#include<stdio.h>//puts,printf,getchar等io前置库
#include<string.h>//strcpy,strcmp,strchr,strlen,sprintf前置库
#include<stdlib.h>//atoi(malloc/calloc动态分配数组(貌似没用到))前置库
//#include<stdbool.h>可选(将P,Q,R=1/0等转换成true/false,增强程序可读性)

#define LEN 21      //全程序可容纳的字符上限为 LEN-1 ( -1是因为要存储'\0'空字符)
#define Number 100  //结构数组person的容量(员工记录上限),可随时更改且无需改动其他函数

struct subsidy {
	char item[LEN];                         //6.补贴项目
	float amount;                           //6.补贴金额
};
struct deduction {
	char item[LEN];                         //7.扣款项目
	float amount;                           //7.扣款金额
};
struct staff {
	char name[LEN];                         //1.姓名
	int number;                             //2.职工号(规定为6位数字)·
	char department[LEN];                   //3.所属部门
	float salary;                           //4.基本工资
	float wage;                             //5.奖励工资
	struct subsidy ic;                      //6.补贴项目及金额
	struct deduction dc;                    //7.扣款项目及金额
};
enum dpn {//使用枚举为了增强程序可读性(熟悉使用方法)
	占位符, 行政部, 财务部, 质检部, 营销部, 运营部, 技术部, 维修部门, 人力资源部, 客户服务部
};
                                                                 //优化方案:增加中英文切换功能(使用位操作实现),更友好、多元化的交互显示(可选,难度高)
char menu(void);                                                 //菜单显示
char sort_menu(int* N);                                          //排序菜单显示
char inquire_menu(int* N);                                       //查询菜单显示
char count_menu(int* N);                                         //统计菜单显示
void departmentmenu(void);                                       //部门菜单显示

void add_staff(struct staff* fp, int* N);                        //1.加入员工                          (已实现)
void del_staff(struct staff* fp, int* N);                        //2.删除员工                          (已实现)
void show_all_staff(struct staff* fp, int* N);                   //3.显示所有员工                      (已实现)
void sort_number(struct staff* fp, int* N);                      //4.职工号排序                        (已实现)
void sort_name(struct staff* fp, int* N);                        //4.姓名字母排序                      (已实现)
void sort_money(struct staff* fp, int* N);                       //*4.按工资排序(额外)                 (已实现)
void inquire_name(struct staff* fp, int* N);                     //5.按人名查询工资                    (已实现)
void inquire_range(struct staff* fp, int* N);                    //5.显示某工资范围记录                (已实现)
void count_salary(struct staff* fp, int* N);                     //6.统计某工资范围人数                (已实现)
void count_department_all(struct staff* fp, int* N);             //6.统计某部门工资总数                (已实现)
void count_department_mid(struct staff* fp, int* N);             //*6.统计某部门工资中位数(额外)       (已实现)
void count_department_ave(struct staff* fp, int* N);             //*6.统计某部门工资平均数(额外)       (已实现)
void count_all_department(struct staff* fp, int* N);             //6.统计所有部门工资总数              (已实现)
void count_mid_department(struct staff* fp, int* N);             //*6.统计所有部门工资中位数(额外)     (已实现)
void count_ave_department(struct staff* fp, int* N);             //*6.统计所有部门工资平均数(额外)     (已实现)
void revise(struct staff* fp, int* N);                           //7.修改                              (已实现)

void Start(struct staff* fp);                                    //员工补贴/扣款项目金额初始化
float Sum(struct staff* fp);                                     //工资求和
void clean(void);                                                //清除多余换行符
char* s_gets(char* st, int n);                                   //输入
char Gets(int n, char* Input);                                   //有效输入判断
char department_input(struct staff* fp, int* N, char ch);        //所属部门输入选择
void detect_name(struct staff* fp, int* N, char* Input);         //姓名输入检测
void detect_number(struct staff* fp, int* N, char* Input);       //职工号输入检测
void detect_department(struct staff* fp, int* N, char* Input);   //所属部门输入检测
void detect_salary(struct staff* fp, int* N, char* Input);       //基本工资输入检测
void detect_wage(struct staff* fp, int* N, char* Input);         //奖励工资输入检测
int detect_revise_input(struct staff* fp, int* N);               //姓名修改输入检测
void detect_revise_ic_it(struct staff* fp, int* N, char* Input); //补贴项目名修改输入检测
void detect_revise_ic_am(struct staff* fp, int* N, char* Input); //补贴金额修改输入检测
void detect_revise_dc_it(struct staff* fp, int* N, char* Input); //扣款修改输入检测
void detect_revise_dc_am(struct staff* fp, int* N, char* Input); //扣款金额修改输入检测
int detect_upper(int n, char* Input);                            //输入上界检测
int detect_lower(char* Input);                                   //输入下界检测

int main(void) {
	struct staff person[Number];//定义结构数组person，最大员工记录容量为Number=100, Number为宏定义,可在开头修改
	int N = 0;    //N为员工记录的数量，初始为0
	char P = '1'; //定义标记P用于判断是否退出循环
	Start(person);//初始化person结构数组在staff结构中的ic/dc结构为"无",0.0 ，防止显示员工时出现随机数/随机字符的情况
	puts("说明:");
	printf("本系统容纳人名或补贴/扣款项目的最多字数为%d(中文为%d)\n", LEN - 1, (LEN - 1) / 2);//简简单单的小说明
	puts("本系统最多仅能记录一项补贴/扣款项目,超出会被覆盖");
	puts("本系统不具备存储功能,请谨慎使用退出选项");
	puts("本系统能容纳的最大数额不超过8位数字");
	printf("本系统最大能容纳%d名员工记录\n", Number);
	do {
		switch (menu()) {//使用do while循环，先显示菜单->用户输入字符/字符串->检测->仅当输入'1'-'8'时->进入switch判断
		case '1':
			add_staff(person, &N); break;//选择'1'时调用add_staff函数....以下同理
		case '2':                        //参数person传递结构指针,&N传递员工记录数量用于加工处理
			del_staff(person, &N); break;
		case '3':
			show_all_staff(person, &N); break;
		case '4':                    //当用户选择'4'排序功能时进行再次判断
			switch (sort_menu(&N)) { //显示排序菜单->用户输入->检测->仅当输入'1'-'3'时->进入switch判断...以下同理
			case '1':
				sort_number(person, &N); break;
			case '2':
				sort_name(person, &N); break;
			case '3':
				sort_money(person, &N); break;
			case '4':
				break;
			}break;
		case '5':
			switch (inquire_menu(&N)) {
			case '1':
				inquire_name(person, &N); break;
			case '2':
				inquire_range(person, &N); break;
			case '3':
				break;
			}break;
		case '6':
			switch (count_menu(&N)) {
			case '1':
				count_salary(person, &N); break;
			case '2':
				count_department_all(person, &N); break;
			case '3':
				count_department_ave(person, &N); break;
			case '4':
				count_department_mid(person, &N); break;
			case '5':
				count_all_department(person, &N); break;
			case '6':
				count_ave_department(person, &N); break;
			case '7':
				count_mid_department(person, &N); break;
			case '8':
				break;
			}break;
		case '7':
			revise(person, &N); break;
		case '8':                     //当用户输入'8'退出时，标记字符P为'8'便于退出switch后进行循环退出判断
			P = '8'; break;
		}

	} while (P != '8');
	puts("感谢使用本系统,祝您生活愉快.");//结束语

	return 0;
}
int detect_lower(char* Input) {//逻辑原理:判断输入是否全部为数字->利用atoi函数将字符串转换为int类型->返回下界lower
	int lower;                 //定义下界
	while (1) {                //由于在循环过程中进行退出判断，所以定义为无限循环
		int Q = 0;             //定义标记Q用于是否再次循环
		char input[LEN];       //定义输入字符串input
		printf(Input);         //打印提示语Input
		s_gets(input, LEN - 1);//利用s_gets函数获取输入
		if (input[0] == '\0')  //若用户敲击回车键[Enter]则再次循环并打印提示语
			continue;
		for (int i = 0; i < strlen(input); i++)//对输入字符串进行判断是否全部为数字字符,若不符合则利用标记Q要求用户重新输入
			if (input[i] < 48 || input[i]>57) {
				puts(">>下界应全部为有效数字,请重新输入");
				Q = 1;
				break;
			}
		if (Q)
			continue;
		lower = atoi(input);//若通过以上2要求,则利用atoi函数将数字字符串转换为数字并退出循环
		break;
	}
	return lower;           //返回下界
}
int detect_upper(int n, char* Input) {//逻辑原理:判断输入是否全部为数字->判断输入是否大于等于下界n->利用atoi函数转换->返回上界upper
	int upper;                        //大体与下界检测相同
	while (1) {
		int Q = 0;
		char input[LEN];
		printf(Input);
		s_gets(input, LEN - 1);
		if (input[0] == '\0')
			continue;
		for (int i = 0; i < strlen(input); i++)
			if (input[i] < 48 || input[i]>57) {
				puts(">>上界应全部为有效数字,请重新输入");
				Q = 1;
				break;
			}
		if (Q)
			continue;
		if (atoi(input) < n) {//若输入上界小于下界则再次循环，要求用户重新输入
			printf(">>上界%d应大于或等于下界%d,请重新输入\n", atoi(input), n);
			continue;
		}
		upper = atoi(input);
		break;
	}
	return upper;
}
int detect_revise_input(struct staff* fp, int* N) {//逻辑原理:遍历所有员工记录->输入判断->利用标记P来判断输入姓名是否存在,若存在返回位置i,不存在则进行选择
	char name[LEN];
	int i = 0;
	while (1) {
		printf("请输入预修改职工的现姓名:");
		int P = 1;                         //定义标记P
		s_gets(name, LEN - 1);
		if (name[0] == '\0')//判断是否输入回车[Enter]
			continue;
		for (i = 0; i < *N; i++)
			if (!strcmp(fp[i].name, name)) {//判断输入的姓名是否存在，若存在则记录位置i并标记P=0，跳出循环
				P = 0;
				break;
			}
		if (P) {
			puts(">>该员工不存在.");//若姓名不存在则进行选择
			puts("-------------------------------------------------------------");
			printf("1)重新输入    2)显示所有员工信息并重新输入    3)退出修改功能\n");
			printf("请选择:");
			switch (Gets(3, "请选择:")) {
			case '1':
				printf("请输入预修改员工的姓名:");
				break;
			case '2'://显示员工信息并再次循环
				show_all_staff(fp, N); continue;
			case '3':
				return '8';
			}
		}
		else
			break;
	}
	return i;//返回姓名位置i
}
void detect_revise_dc_it(struct staff* fp, int* N, char* Input) {//逻辑原理:输入判断是否为回车->项目名称是否重复->复制输入项目名称
	while (1) {
		int R = 1;//定义标记R
		char icname[LEN];
		printf(Input);
		s_gets(icname, LEN - 1);
		if (icname[0] == '\0')
			continue;
		if (!strcmp(fp[*N].dc.item, icname)) {//若项目名称重复则重新输入
			puts(">>%s项目已经存在,请重新输入");
			continue;
		}
		strcpy(fp[*N].dc.item, icname);//复制输入的项目名
		break;
	}
}
void detect_revise_dc_am(struct staff* fp, int* N, char* Input) {//逻辑原理:输入判断是否为回车->输入字符串是否全部为数字->利用atoi转换字符串为int类型
	while (1) {
		int Q = 0;
		char dcamount[LEN];
		printf(Input);
		s_gets(dcamount, LEN - 1);
		if (dcamount[0] == '\0')
			continue;
		for (int i = 0; i < strlen(dcamount); i++)//判断输入字符串是否全部为数字字符
			if (dcamount[i] < 48 || dcamount[i]>57) {
				puts(">>补贴金额应全部为有效数字,请重新输入");
				Q = 1;
				break;
			}
		if (Q)//若其中有字符不为数字字符则再次循环
			continue;
		fp[*N].dc.amount = atoi(dcamount);//将字符串转换成数字
		break;
	}
}
void detect_revise_ic_it(struct staff* fp, int* N, char* Input) {//逻辑原理与detect_revise_dc_it完全相同
	while (1) {
		int R = 1;
		char icname[LEN];
		printf(Input);
		s_gets(icname, LEN - 1);
		if (icname[0] == '\0')
			continue;
		if (!strcmp(fp[*N].ic.item, icname)) {
			puts(">>%s项目已经存在,请重新输入");
			continue;
		}
		strcpy(fp[*N].ic.item, icname);
		break;
	}
}
void detect_revise_ic_am(struct staff* fp, int* N, char* Input) {//逻辑原理与detect_revise_dc_am完全相同
	while (1) {
		int Q = 0;
		char icamount[LEN];
		printf(Input);
		s_gets(icamount, LEN - 1);
		if (icamount[0] == '\0')
			continue;
		for (int i = 0; i < strlen(icamount); i++)
			if (icamount[i] < 48 || icamount[i]>57) {
				puts(">>补贴金额应全部为有效数字,请重新输入");
				Q = 1;
				break;
			}
		if (Q)
			continue;
		fp[*N].ic.amount = atoi(icamount);
		break;
	}
}
void detect_wage(struct staff* fp, int* N, char* Input) {//逻辑原理:判断输入是否为回车->判断输入是否全部为数字->利用atoi转换字符串为int类型
	while (1) {
		int R = 0, Q = 0;
		char input[LEN];
		printf(Input);
		s_gets(input, LEN - 1);
		if (input[0] == '\0') {//判断输入是否为回车
			R = 1;
			continue;
		}
		for (int i = 0; i < strlen(input); i++)//判断输入是否全部为数字字符
			if (input[i] < 48 || input[i]>57) {
				puts(">>奖励工资应全部为有效数字,请重新输入");
				Q = 1;
				break;
			}
		if (Q || R)
			continue;
		else {
			fp[*N].wage = atoi(input);
			break;
		}
	}
}
void detect_salary(struct staff* fp, int* N, char* Input) {//逻辑原理:判断输入是否为回车->判断输入是否全部为数字字符->利用atoi转换字符串为int类型
	while (1) {
		int R = 0, Q = 0;
		char input[LEN];
		printf(Input);
		s_gets(input, LEN - 1);
		if (input[0] == '\0') {
			R = 1;
			continue;
		}
		for (int i = 0; i < strlen(input); i++)
			if (input[i] < 48 || input[i]>57) {
				puts(">>基本工资应全部为有效数字,请重新输入");
				Q = 1;
				break;
			}
		if (Q || R)
			continue;
		else {
			fp[*N].salary = atoi(input);
			break;
		}
	}
}
void detect_department(struct staff* fp, int* N, char* Input) {//逻辑原理:判断输入是否为回车->判断输入是否全部为数字字符,若不是则利用goto返回输入部分(不打印提示语)
	departmentmenu();//打印部门名称编号                          若满足以上2要求则利用sprintf将名称打印进dpname来对选择的编号进行对应->若选择的部门与当前部门相同
	char dpname[LEN];                                          //则重新输入->满足以上3要求则跳转至department_input函数进行选择编号与对应名称的填充
	while (1) {
		int R = 0;
		char input[LEN];
		printf(Input);
	arr://goto跳转项
		s_gets(input, LEN - 1);
		if (input[0] == '\0') {//判断输入是否为回车
			R = 1;
			continue;
		}
		else if (input[0] < 49 || input[0] > 9 + 48 || strlen(input) != 1) {//选择是否在'1'-'9'内
			printf(">>%s为无效输入，请重新选择:", input);
			goto arr;//若不为'1'-'9'则跳转至arr(使用goto的原因,跳过打印提示语部分)
		}
		if (R)
			continue;
		else {
			switch (input[0]) {//对选择的编号进行对应
			case '1':
				sprintf(dpname, "%s", "行政部"); break;
			case '2':
				sprintf(dpname, "%s", "财务部"); break;
			case '3':
				sprintf(dpname, "%s", "质检部"); break;
			case '4':
				sprintf(dpname, "%s", "营销部"); break;
			case '5':
				sprintf(dpname, "%s", "运营部"); break;
			case '6':
				sprintf(dpname, "%s", "技术部"); break;
			case '7':
				sprintf(dpname, "%s", "维修部门"); break;
			case '8':
				sprintf(dpname, "%s", "人力资源部"); break;
			case '9':
				sprintf(dpname, "%s", "客户服务部"); break;
			}
			if (!strcmp(fp[*N].department, dpname)) {//判断选择编号是否与当前部门编号相同,若相同则要求用户重新选择
				puts(">>该员工已是该部门成员,请重新选择");
				continue;
			}
			else {
				department_input(fp, N, input[0]);//将对应的编号转换成字符串填充至fp[*N].department中并结束循环
				break;
			}
		}
	}
}
void detect_name(struct staff* fp, int* N, char* Input) {//逻辑原理:判断输入是否为回车->判断输入的姓名是否重复，若重复则重新输入
	while (1) {
		int R = 1;
		printf(Input);
		s_gets(fp[*N].name, LEN - 1);
		if (fp[*N].name[0] == '\0')
			continue;
		for (int i = 0; i < *N; i++)
			if (!strcmp(fp[i].name, fp[*N].name)) {//判断输入姓名是否已经存在
				R = 0;
				break;
			}
		if (R)
			break;
		else
			printf(">>%s已经存在,请重新输入:", fp[*N].name);

	}
}
void detect_number(struct staff* fp, int* N, char* Input) {//逻辑原理:判断输入是否为回车->判断职工号是否已经存在->判断输入是否全部为数字字符
	while (1) {                                            //->判断输入是否为6位->利用atoi转换为int类型
		int R = 1, P = 1, Q = 0;
		char input[LEN];
		printf(Input);
		s_gets(input, LEN - 1);
		if (input[0] == '\0')//判断回车
			continue;
		for (int i = 0; i < strlen(input); i++)
			if (input[i] < 48 || input[i]>57) {//判断输入是否全部为数字字符
				puts(">>职工号中应全部为有效数字,请重新输入");
				Q = 1;
				break;
			}
		if (Q)
			continue;
		for (int i = 0; i < *N; i++)//判断职工号是否已经存在,若存在则要求用户重新输入
			if (fp[i].number == atoi(input)) {
				R = 0;
				break;
			}
		if (atoi(input) > 999999 || atoi(input) < 100000) {//判断职工号是否为6位字符，若不是则重新循环并打印提示语
			printf(">>该职工号无效,");
			continue;
		}
		if (R) {//若满足以上要求则利用atoi转换
			fp[*N].number = atoi(input);
			break;
		}
		else
			printf(">>%d已经存在,请重新输入:", atoi(input));
	}
}
char department_input(struct staff* fp, int* N, char ch) {//对应编号的部门名称填充
	switch (ch) {
	case '1':
		sprintf(fp[*N].department, "%s", "行政部"); break;
	case '2':
		sprintf(fp[*N].department, "%s", "财务部"); break;
	case '3':
		sprintf(fp[*N].department, "%s", "质检部"); break;
	case '4':
		sprintf(fp[*N].department, "%s", "营销部"); break;
	case '5':
		sprintf(fp[*N].department, "%s", "运营部"); break;
	case '6':
		sprintf(fp[*N].department, "%s", "技术部"); break;
	case '7':
		sprintf(fp[*N].department, "%s", "维修部门"); break;
	case '8':
		sprintf(fp[*N].department, "%s", "人力资源部"); break;
	case '9':
		sprintf(fp[*N].department, "%s", "客户服务部"); break;
	}
};
void revise(struct staff* fp, int* N) {//逻辑原理:判断*N是否为0,若为0利用goto跳转至最后并打印提示->
	int i = 0, R = 0, P = 1;
	if (*N == 0) {
		R = 1;
		goto arr;//若*N为0则跳转至最后arr位置
	}
	do {//修改功能进行循环使用
		puts("           修改功能");
		puts("--------------------------------");//打印简简单单的小菜单
		puts("1)姓名");
		puts("2)职工号(6位数字)");
		puts("3)所属部门");
		puts("4)基本工资");
		puts("5)奖励工资");
		puts("6)补贴项目及金额");
		puts("7)扣款项目及金额");
		puts("8)退出修改功能");
		puts("--------------------------------");
		printf("请选择:");
		switch (Gets(8, "请选择:")) {//判断输入是否为'1'-'8',若满足要求则进行switch判断
		case '1':
			i = detect_revise_input(fp, N);//利用输入判断姓名是否存在->返回位置i
			detect_name(fp, &i, "请输入该员工修改后的姓名:");//调用函数进行判断
			puts(">>成功修改该员工姓名"); break;//打印提示....以下同理
		case '2':
			i = detect_revise_input(fp, N);
			detect_number(fp, &i, "请输入该员工修改后的职工号(第一位不为0):");
			puts(">>成功修改该员工职工号"); break;
		case '3':
			i = detect_revise_input(fp, N);
			detect_department(fp, &i, "请选择该员工修改后的所属部门:");
			puts(">>成功修改该员工所属部门"); break;
		case '4':
			i = detect_revise_input(fp, N);
			detect_salary(fp, &i, "请输入该员工修改后的基本工资:");
			puts(">>成功修改该员工基本工资"); break;
		case '5':
			i = detect_revise_input(fp, N);
			detect_wage(fp, &i, "请输入该员工修改后的奖励工资:");
			puts(">>成功修改该员工奖励工资"); break;
		case '6':
			i = detect_revise_input(fp, N);
			puts("1)增加(覆盖)补贴项目及金额");
			puts("2)删除现有补贴项目及金额");
			printf("请选择:");
			switch (Gets(2, "请选择:")) {//判断输入字符是否为'1'和'2',满足则再次switch判断
			case '1':
				detect_revise_ic_it(fp, &i, "请输入补贴项目名称:");
				puts(">>已成功修改补贴项目");
				detect_revise_ic_am(fp, &i, "请输入补贴金额:");
				puts(">>已成功修改补贴金额"); break;
			case '2'://若删除则复制"无"覆盖原有项目名
				strcpy(fp[i].ic.item, "无");
				fp[i].ic.amount = 0.0;//将原金额化为0...,以下同理
				puts(">>已成功删除现有记录"); break;
			}break;
		case '7':
			i = detect_revise_input(fp, N);
			puts("1)增加(覆盖)扣款项目及金额");
			puts("2)删除现有扣款项目及金额");
			printf("请选择:");
			switch (Gets(2, "请选择:")) {
			case '1':
				detect_revise_dc_it(fp, &i, "请输入扣款项目名称:");
				puts(">>已成功修改扣款项目");
				detect_revise_dc_am(fp, &i, "请输入扣款金额:");
				puts(">>已成功修改扣款金额"); break;
			case '2':
				strcpy(fp[i].dc.item, "无");
				fp[i].dc.amount = 0.0;
				puts(">>已成功删除现有记录"); break;
			}break;
		case '8':
			P = 0;//若用户选择退出则标记P化为0
			break;
		}
	} while (P);//利用标记判断是否退出循环
arr:
	if (R)
		puts("无员工记录可供修改");
}
void count_mid_department(struct staff* fp, int* N) {//大体功能与其他统计功能相同
	struct staff sort;//定义中间结构变量sort
	struct staff* Sort = (struct staff*)malloc(*N * sizeof(struct staff));//复制Sort作为fp的副本进行排序
	for (int i = 0; i < *N; i++)
		Sort[i] = fp[i];
	for (int i = 0; i < *N - 1; i++)//冒泡法排序
		for (int j = 0; j < *N - 1 - i; j++)
			if (Sum(&Sort[j]) > Sum(&Sort[j + 1])) {
				sort = Sort[j];
				Sort[j] = Sort[j + 1];
				Sort[j + 1] = sort;
			}
	if (*N % 2)
		printf(">>所有部门工资中位数为:%g\n", Sum(&Sort[*N / 2]));
	else
		printf(">>所有部门工资中位数为:%g\n", Sum(&Sort[*N / 2]) + Sum(&Sort[*N / 2 - 1]));
	free(Sort);
}
void count_ave_department(struct staff* fp, int* N) {
	float sum = 0.0;
	for (int i = 0; i < *N; i++)
		sum += Sum(&fp[i]);
	printf(">>所有部门工资平均数为:%g\n", sum / *N);
}
void count_all_department(struct staff* fp, int* N) {//逻辑原理:遍历*N,利用Sum函数对每个员工进行工资求和->打印总工资
	float sum = 0.0;
	for (int i = 0; i < *N; i++)
		sum += Sum(&fp[i]);
	printf(">>所有部门工资总数为:%g\n", sum);
}
void count_department_mid(struct staff* fp, int* N) {//工资总数统计与总中位数统计的结合体
	puts("           部门名称");
	puts("--------------------------------");//打印简简单单的名称
	puts("1)行政部");
	puts("2)财务部");
	puts("3)质检部");
	puts("4)营销部");
	puts("5)运营部");
	puts("6)技术部");
	puts("7)维修部门");
	puts("8)人力资源部");
	puts("9)客户服务部");
	puts("--------------------------------");
	printf("请选择预统计工资总数部门的编号:");
	int r = 0, u = 0, R = (Gets(9, "请选择预统计工资总数部门的编号:") - 48);//判断输入是否'1'-'9'->利用ASCII码的数值将选择由字符char类型转换成数字int类型
	float middle = 0.0;
	char dpname[LEN];
	switch (R) {//对选择进行判断并填充(此步与字符判断同理,只是熟悉一下枚举的使用方法)
	case 行政部://利用枚举判断,增强可读性
		sprintf(dpname, "%s", "行政部"); break;
	case 财务部:
		sprintf(dpname, "%s", "财务部"); break;
	case 质检部:
		sprintf(dpname, "%s", "质检部"); break;
	case 营销部:
		sprintf(dpname, "%s", "营销部"); break;
	case 运营部:
		sprintf(dpname, "%s", "运营部"); break;
	case 技术部:
		sprintf(dpname, "%s", "技术部"); break;
	case 维修部门:
		sprintf(dpname, "%s", "维修部门"); break;
	case 人力资源部:
		sprintf(dpname, "%s", "人力资源部"); break;
	case 客户服务部:
		sprintf(dpname, "%s", "客户服务部"); break;
	}
	for (int i = 0; i < *N; i++) //统计该部门的人数
		if (!strcmp(fp[i].department, dpname))
			r++;
	struct staff sort;
	struct staff* Sort = (struct staff*)malloc(r * sizeof(struct staff));//复制Sort作为fp副本
	for(int i = 0;i<*N;i++)
		if (!strcmp(fp[i].department, dpname)) {
			Sort[u] = fp[i];
			u++;//标记该部门的人数u
		}
	for(int i=0;i<u-1;i++)
		for(int j=0;j<u-1-i;j++)//冒泡法排序
			if (Sum(&Sort[j]) > Sum(&Sort[j + 1])) {
				sort = Sort[j];
				Sort[j] = Sort[j + 1];
				Sort[j + 1] = sort;
			}
	if (!u);
	else if (u % 2)
		middle = Sum(&Sort[u / 2]);
	else
		middle = Sum(&Sort[u / 2 - 1]) + Sum(&Sort[u / 2]);
	printf(">>%s部门的工资中位数: %g\n", dpname, middle);
	free(Sort);
}
void count_department_ave(struct staff* fp, int* N) {//与工资总数统计完全相同
	puts("           部门名称");
	puts("--------------------------------");//打印简简单单的名称
	puts("1)行政部");
	puts("2)财务部");
	puts("3)质检部");
	puts("4)营销部");
	puts("5)运营部");
	puts("6)技术部");
	puts("7)维修部门");
	puts("8)人力资源部");
	puts("9)客户服务部");
	puts("--------------------------------");
	printf("请选择预统计工资总数部门的编号:");
	int r = 0, R = (Gets(9, "请选择预统计工资总数部门的编号:") - 48);//判断输入是否'1'-'9'->利用ASCII码的数值将选择由字符char类型转换成数字int类型
	float sum = 0.0, average = 0.0;
	char dpname[LEN];
	switch (R) {//对选择进行判断并填充(此步与字符判断同理,只是熟悉一下枚举的使用方法)
	case 行政部://利用枚举判断,增强可读性
		sprintf(dpname, "%s", "行政部"); break;
	case 财务部:
		sprintf(dpname, "%s", "财务部"); break;
	case 质检部:
		sprintf(dpname, "%s", "质检部"); break;
	case 营销部:
		sprintf(dpname, "%s", "营销部"); break;
	case 运营部:
		sprintf(dpname, "%s", "运营部"); break;
	case 技术部:
		sprintf(dpname, "%s", "技术部"); break;
	case 维修部门:
		sprintf(dpname, "%s", "维修部门"); break;
	case 人力资源部:
		sprintf(dpname, "%s", "人力资源部"); break;
	case 客户服务部:
		sprintf(dpname, "%s", "客户服务部"); break;
	}
	for (int i = 0; i < *N; i++) //统计该部门的工资总和(遍历,判断是否为该部门,若是则+该员工总工资)
		if (!strcmp(fp[i].department, dpname)) {
			sum += Sum(&fp[i]);
			r++;
		}
	if(r)
		average = sum / r;
	printf(">>%s部门的平均工资: %g\n", dpname, average);
}
void count_department_all(struct staff* fp, int* N) {//逻辑原理:判断输入->进行switch选择与填充->统计工资总和并打印结果
	puts("           部门名称");
	puts("--------------------------------");//打印简简单单的名称
	puts("1)行政部");
	puts("2)财务部");
	puts("3)质检部");
	puts("4)营销部");
	puts("5)运营部");
	puts("6)技术部");
	puts("7)维修部门");
	puts("8)人力资源部");
	puts("9)客户服务部");
	puts("--------------------------------");
	printf("请选择预统计工资总数部门的编号:");
	int R = (Gets(9, "请选择预统计工资总数部门的编号:") - 48);//判断输入是否'1'-'9'->利用ASCII码的数值将选择由字符char类型转换成数字int类型
	float sum = 0.0;
	char dpname[LEN];
	switch (R) {//对选择进行判断并填充(此步与字符判断同理,只是熟悉一下枚举的使用方法)
	case 行政部://利用枚举判断,增强可读性
		sprintf(dpname, "%s", "行政部"); break;
	case 财务部:
		sprintf(dpname, "%s", "财务部"); break;
	case 质检部:
		sprintf(dpname, "%s", "质检部"); break;
	case 营销部:
		sprintf(dpname, "%s", "营销部"); break;
	case 运营部:
		sprintf(dpname, "%s", "运营部"); break;
	case 技术部:
		sprintf(dpname, "%s", "技术部"); break;
	case 维修部门:
		sprintf(dpname, "%s", "维修部门"); break;
	case 人力资源部:
		sprintf(dpname, "%s", "人力资源部"); break;
	case 客户服务部:
		sprintf(dpname, "%s", "客户服务部"); break;
	}
	for (int i = 0; i < *N; i++) //统计该部门的工资总和(遍历,判断是否为该部门,若是则+该员工总工资)
		if (!strcmp(fp[i].department, dpname))
			sum += Sum(&fp[i]);
	printf(">>%s部门的总计工资: %g\n", dpname, sum);
}
void count_salary(struct staff* fp, int* N) {//逻辑原理:判断下界与上界->遍历,记录在范围内的员工数量->打印结果
	float lower, upper;
	int P = 1, r = 0;
	lower = detect_lower("请输入预统计范围的下界:");//下界判断
	upper = detect_upper(lower, "请输入预统计范围的上界:");//上界判断
	for (int i = 0; i < *N; i++)
		if (Sum(&fp[i]) >= lower && Sum(&fp[i]) <= upper) {//遍历,若员工工资处于该范围内则标记r +1
			r++;
			P = 0;
		}
	if (P)
		puts(">>该工资范围内无员工记录");
	else
		printf(">>共有%d名员工处于该工资范围内\n", r);
}
void inquire_range(struct staff* fp, int* N) {//逻辑原理:判断下界,上界->遍历,打印在该工资范围内的员工信息
	float lower, upper;
	int P = 1;
	lower = detect_lower("请输入预查询工资范围的下界:");
	upper = detect_upper(lower, "请输入预查询工资范围的上界:");
	for (int i = 0; i < *N; i++)
		if (Sum(&fp[i]) >= lower && Sum(&fp[i]) <= upper) {
			printf(">>姓名:%s 职工号:%d 所属部门:%s 基本工资:%g 奖励工资:%g 补贴项目及金额:%s,%g 扣款项目及金额:%s,%g\n",
				fp[i].name, fp[i].number, fp[i].department, fp[i].salary, fp[i].wage,
				fp[i].ic.item, fp[i].ic.amount, fp[i].dc.item, fp[i].dc.amount);
			P = 0;
		}
	if (P)
		puts(">>无员工处于该工资范围内");
}
void inquire_name(struct staff* fp, int* N) {//逻辑原理:判断输入是否为回车->判断输入姓名是否存在->打印结果->退出循环
	char Name[LEN];
	int R = 1;
	while (1) {
		printf("请输入待查询员工的姓名:");
		s_gets(Name, LEN - 1);
		if (Name[0] == '\0')//判断回车
			continue;
		for (int i = 0; i < *N; i++)
			if (!strcmp(fp[i].name, Name)) {//若输入姓名存在,则打印信息并使标记R为0
				printf(">>%8s: 基本工资:%-7g 奖励工资:%-7g 补贴项目:%5s 补贴金额%-5g 扣款项目:%5s 扣款金额%-5g\n",
					Name, fp[i].salary, fp[i].wage, fp[i].ic.item,
					fp[i].ic.amount, fp[i].dc.item, fp[i].dc.amount);
				printf("总工资:%g\n", Sum(&fp[i]));
				R = 0;
				break;
			}
		if (R)//若不存在
			puts(">>无该员工相关记录.");
		break;//无论是否存在均退出循环
	}
}
void sort_money(struct staff* fp, int* N) {//逻辑原理:与按职工号排序完全相同
	struct staff sort;//定义中间结构变量sort
	for (int i = 0; i < *N - 1; i++)//冒泡法排序
		for (int j = 0; j < *N - 1 - i; j++)
			if (Sum(&fp[j]) < Sum(&fp[j + 1])) {
				sort = fp[j];
				fp[j] = fp[j + 1];
				fp[j + 1] = sort;
			}
	if (*N == 0)
		puts(">>无员工记录");
	else {
		puts(">>排序成功");
		show_all_staff(fp, N);
	}
}
void sort_name(struct staff* fp, int* N) {//逻辑原理:字符串冒泡法排序(可更换为时间复杂度更低的排序算法).利用strcmp函数比较->排序->打印结果
	struct staff sort;//定义中间结构变量sort
	for (int i = 0; i < *N - 1; i++)//冒泡法排序
		for (int j = 0; j < *N - 1 - i; j++)
			if (strcmp(fp[j].name, fp[j + 1].name) > 0) {
				sort = fp[j];
				fp[j] = fp[j + 1];
				fp[j + 1] = sort;
			}
	if (*N == 0)
		puts(">>无员工记录");
	else {
		puts(">>排序成功");
		show_all_staff(fp, N);
	}
}
void sort_number(struct staff* fp, int* N) {//逻辑原理:数字冒泡法排序(可更换为时间复杂度更低的排序算法).比较->排序->打印结果
	struct staff sort;//定义中间结构变量sort
	for (int i = 0; i < *N - 1; i++)
		for (int j = 0; j < *N - 1 - i; j++)
			if (fp[j].number > fp[j + 1].number) {
				sort = fp[j];
				fp[j] = fp[j + 1];
				fp[j + 1] = sort;
			}
	if (*N == 0)
		puts(">>无员工记录");
	else {
		puts(">>排序成功");
		show_all_staff(fp, N);
	}
}
void show_all_staff(struct staff* fp, int* N) {//逻辑原理:判断员工记录*N是否为0->遍历,打印信息
	if (*N == 0)
		puts(">>无员工记录.");
	else
		for (int i = 0; i < *N; i++)
			printf(">>姓名:%8s 职工号:%6d 所属部门:%10s 基本工资:%-7g 奖励工资:%-7g 补贴项目:%6s 补贴金额:%-5g 扣款项目:%6s 扣款金额:%-5g\n",
				fp[i].name, fp[i].number, fp[i].department, fp[i].salary, fp[i].wage,
				fp[i].ic.item, fp[i].ic.amount, fp[i].dc.item, fp[i].dc.amount);
}
void del_staff(struct staff* fp, int* N) {//逻辑原理:判断员工记录*N是否为0->若删除后*N为0,打印提示语并退出循环->输入判断->职工号存在判断->打印结果
	int P = 1, Q = 1;
	if (*N == 0)
		puts(">>无员工记录可被删除");
	else {
		do {
			if (*N == 0) {//若删除后*N为0则打印提示并退出循环
				puts(">>所有员工记录均被删除");
				break;
			}
			while (1) {//与detect_number函数类似的输入检测
				int T = 0, K = 0;
				char input[LEN];
				printf("请输入预删除员工的6位有效职工号:");
				s_gets(input, LEN - 1);
				if (input[0] == '\0')//判断回车
					continue;
				for (int i = 0; i < strlen(input); i++)
					if (input[i] < 48 || input[i]>57) {//判断输入是否全部为数字字符
						puts(">>预删除的职工号应全部为有效数字,请重新输入");
						K = 1;
						break;
					}
				if (K)
					continue;
				for (int i = 0; i < *N; i++)//判断职工号是否存在->利用被删除记录的下一个记录覆盖自身->员工记录数*N-1->标记P为0跳过判断->打印提示语
					if (fp[i].number == atoi(input)) {
						for (int j = i; j < *N - 1; j++)
							fp[j] = fp[j + 1];
						(*N)--;
						P = 0;
						break;
					}
				break;
			}
			if (P) {//若不存在->选择判断
				puts(">>该员工不存在");
				puts("----------------------------------------------------------------");
				puts("1)重新输入职工号    2)显示所有员工信息并重新输入职工号    3)退出");
				printf("请选择:");
				switch (Gets(3, "请选择:")) {
				case '1':
					break;
				case '2':
					show_all_staff(fp, N); continue;
				case '3':
					Q = 0;
					break;
				}
			}
			else {//打印提示语
				puts(">>该员工记录已成功被删除");
				Q = 0;
			}
		} while (Q);
	}
}
void add_staff(struct staff* fp, int* N) {//逻辑原理:基于以上各个函数的组合函数.判断->输入->打印提示语
	if (*N == 100)//若记录达到Number则不进行处理并打印提示语
		printf("员工记录已达到最大限制%d,无法增加新的员工信息\n", Number);
	else {
		detect_name(fp, N, "请输入预增加员工的姓名:");

		detect_number(fp, N, "请输入员工6位有效职工号(第一位不为0):");

		detect_department(fp, N, "请选择员工的所属部门:");

		detect_salary(fp, N, "请输入员工的基本工资:");

		detect_wage(fp, N, "请输入员工的奖励工资:");

		puts("是否有补贴项目:");
		puts("1)有   2)无");
		printf("请选择:");
		if (Gets(2, "请选择:") == '1') {
			puts("请输入员工的补贴项目及金额:");
			printf("请输入项目名:");
			s_gets(fp[*N].ic.item, LEN - 1);
			printf("请输入补贴金额:");
			scanf("%f", &fp[*N].ic.amount); clean();
		}
		puts("是否有扣款项目:");
		puts("1)有   2)无");
		printf("请选择:");
		if (Gets(2, "请选择:") == '1') {
			puts("请输入员工的扣款项目及金额:");
			printf("请输入项目名:");
			s_gets(fp[*N].dc.item, LEN - 1);
			printf("请输入扣款金额:");
			scanf("%f", &fp[*N].dc.amount); clean();
		}
		puts(">>成功加入该员工记录");
		(*N)++;
	}
}
void departmentmenu(void) {//打印简简单单的部门菜单
	puts("           部门名称");
	puts("--------------------------------");
	puts("1)行政部");
	puts("2)财务部");
	puts("3)质检部");
	puts("4)营销部");
	puts("5)运营部");
	puts("6)技术部");
	puts("7)维修部门");
	puts("8)人力资源部");
	puts("9)客户服务部");
	puts("--------------------------------");
}
char count_menu(int* N) {//若员工记录*N为0则返回'4'传回main函数,不为0进行选择->选择结果返回main函数的switch分支
	if (*N == 0) {
		puts(">>无员工记录可供统计");
		return '8';
	}
	puts("           统计功能");
	puts("--------------------------------");
	puts("1)统计某一工资范围人数");
	puts("2)统计某部门工资总数");
	puts("3)统计某部门工资平均数");
	puts("4)统计某部门工资中位数");
	puts("5)统计所有部门工资总数");
	puts("6)统计所有部门工资平均数");
	puts("7)统计所有部门工资中位数");
	puts("--------------------------------");
	printf("输入以上数字以选择功能:");
	return Gets(7, "输入以上数字以选择功能:");
}
char inquire_menu(int* N) {//若员工记录*N为0则返回'3'传回main函数,不为0进行选择->选择结果返回main函数的switch分支
	if (*N == 0) {
		puts(">>无员工记录可供查询");
		return '3';
	}
	puts("           查询功能");
	puts("--------------------------------");
	puts("1)按人名查询工资");
	puts("2)显示某一工资范围的记录");
	puts("--------------------------------");
	printf("输入以上数字以选择功能:");
	return Gets(2, "输入以上数字以选择功能:");
}
char sort_menu(int* N) {//若员工记录*N为0则返回'3'传回main函数,不为0进行选择->选择结果返回main函数的switch分支
	if (*N == 0) {
		puts(">>无员工记录可供排序");
		return '4';
	}
	puts("           排序功能");
	puts("--------------------------------");
	puts("1)按职工号排序");
	puts("2)按姓名字母排序");
	puts("3)按工资排序");
	puts("--------------------------------");
	printf("输入以上数字以选择功能:");
	return Gets(3, "输入以上数字以选择功能:");
}
char menu(void) {//打印初始菜单并进行输入判断
	puts("        ");
	puts("----------工资管理系统-------------");
	puts("1)加入一个员工的记录");
	puts("2)删除一个员工的记录");
	puts("3)显示所有员工的记录");
	puts("4)排序功能");
	puts("5)查询功能");
	puts("6)统计功能");
	puts("7)修改功能");
	puts("8)退出");
	puts("-----------------------------------");
	printf("输入以上数字以选择功能:");
	return Gets(8, "输入以上数字以选择功能:");
}
void Start(struct staff* fp) {//对staff结构中的ic/dc结构进行初始化,防止打印随机字符/数字
	for (int i = 0; i < Number; i++) {
		sprintf(fp[i].ic.item, "%s", "无");
		sprintf(fp[i].dc.item, "%s", "无");
		fp[i].ic.amount = 0.0;
		fp[i].dc.amount = 0.0;
	}
}
void clean(void) {//对使用scanf函数输入时不清理的\n进行处理(貌似没用到?)
	while (getchar() != '\n')
		continue;
}
float Sum(struct staff* fp) {//对某一员工进行工资求和
	return fp->salary + fp->wage + fp->ic.amount - fp->dc.amount;
}
char* s_gets(char* st, int n) {//与gets/fgets函数类似的输入,但该输入会将敲击回车时产生的'\n'处理成'\0',并清空之后的无用输入
	char* find;
	char* ret_val;
	ret_val = fgets(st, n, stdin);
	if (ret_val) {
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}
char Gets(int n, char* Input) {//对n个字符选择进行判断，若超出'1'-'n'范围之外则重新循环并打印对应的参数字符串
	char ch[LEN];
	while (s_gets(ch, LEN - 1)) {
		if (ch[0] == '\0')
			printf(Input);
		else if (ch[0] < 49 || ch[0] > n + 48 || strlen(ch) != 1)
			printf(">>%s为无效输入，请重新选择:", ch);
		else
			break;
	}
	return ch[0];
}