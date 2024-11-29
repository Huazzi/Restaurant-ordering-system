#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<windows.h>
#define size sizeof(struct menu)
#define MAX_SEATS 11  //有限座位号

struct menu    //声明一个结构体 存储菜品信息 
{
	int serial_number;//菜品序号 
	char dishes_name[100];//菜品名称 
	int money;//菜品价格
	struct menu* next; //结构体指针 指向下一个结构体 
};

struct menu* creat(void); //创建菜单函数 （链表的创建） 
struct menu* del(struct menu* head, int number); //删除菜品函数 （链表节点的删除） 
struct menu* insert(struct menu* head); //添加菜品函数 （链表节点的插入） 
void menu(struct menu* head); //输出菜单信息界面的函数 （链表的打印）
void outside(void); //外部界面函数 
void DiningOut(int* length); //出餐功能函数
int ChooseSeat(int* desknumber); //选座功能函数
void welcome(int PEOPLENUMBER, int DESK); //欢迎客人界面的函数 
int order(struct menu* head, int Num[]); //点餐计费函数 
void waiting(int length, int num); //等待上餐界面函数 
void bill(int NUM[], struct menu* p, int PAYMONEY); //输出账单函数 
void daybook(int NUM[], struct menu* p, int PAYMONEY);//记录餐厅流水账函数 
void goodbye(void); //送客界面函数 
void backstage_welcome(void); //后台管理系统函数 
void dish_change(void); //进入菜品修改系统函数 
void dish_money_change(struct menu* head);//菜品价格修改系统函数
void dish_name_change(struct menu* head, int number, char dish_name[]); //菜品名修改系统函数  

struct menu* head;

int main() {
	struct menu* pmenu;//定义结构体指针 
	head = creat(); //创建菜单信息链表
	//pmenu = head;//将表头赋予pmenu
	int id, dishnum = 0, length = -1; //第一位顾客前面排队人数为 0 
start:
	int desknumber, human;
	int n, num[50], paymoney = 0;//所需支付费用 
	int keyword;//密码 
	int change;//选项 
	outside();//进入外部界面函数 
	printf("请选择您的身份（顾客 1 ；管理员 2）：");
	scanf("%d", &id);
	if (id == 2) goto start_backstage;//跳入后台管理系统 
	ChooseSeat(&desknumber);
	printf("请输入就餐人数: ");
	scanf("%d", &human);
	system("cls");
	welcome(desknumber, human);//欢迎 
	system("pause");
	system("cls");
	menu(head); //打印菜单 
	paymoney = order(head, num); //点餐并计费 
	++length; //每点一次餐，等待出餐排队伍长度 + 1
	waiting(length, ++dishnum); //等待界面
start_to_bill:
	printf("查看账单请输入1\n");
	scanf("%d", &n);
	system("cls");
start_to_pay:
	if (n == 1) //输入正确
	{
		bill(num, head, paymoney); //打印账单
		daybook(num, head, paymoney); //记录到流水账文件中 
	}
	else
	{
		printf("\n输入有误，请重新输入!\n");//输入错误 
		goto start_to_bill; //返回 
	}
	printf("已经帮您联系服务员，服务员将很快到达，请您稍等\n");
	printf("\n请服务员确认后输入密码（1111）：\n");
	scanf("%d", &keyword);//输入密码 
	system("cls");
	if (keyword == 1111)
	{
		int input;
		goodbye();//送客界面
		printf("输入1，重置点餐系统\n");
		printf("输入0，关闭点餐系统\n");
		printf("请选择：");
		scanf("%d", &input);
		system("cls");
		if (input == 1)
			goto start;
		else {
			length = 0;//重置
			exit(0);
		}
	}
	else {
		printf("\n密码输入错误！请重新输入: \n\n");
		goto start_to_pay;
	}
start_backstage://后台 
	printf("请输入管理员密码（1111）: ");
	scanf("%d", &keyword);
	if (keyword != 1111) {
		printf("密码错误！");
		system("pause");
		system("cls");
		goto start;//密码错误 返回 
	}
	system("cls");//密码正确 清屏 
start_manage:
	backstage_welcome();//后台欢迎界面 
	scanf("%d", &change);//输入选项 
	if (change == 1) { //出餐
		DiningOut(&length);
		system("pause");
		system("cls");
		goto start_manage;
	}
	else if (change == 2) {
		dish_money_change(head);//进入菜品价格修改函数 
		goto start_manage;

	}
	else if (change == 4) {//返回上一界面 
		system("cls");
		goto start;
	}
	else if (change == 3) {
		getchar();//吸收换行符
	start_dishchange:      //进入菜品修改系统
		system("cls");
		dish_change();//菜品修改系统欢迎函数 
		int number = 0;
		char dish_name[50], choice;
		printf("\n请选择您的项目：");

		scanf("%c", &choice);
		if (choice == 'A')
			dish_name_change(head, number, dish_name);//菜名修改 
		else if (choice == 'B')
			head = del(head, number);//删除菜品 
		else if (choice == 'C')
			head = insert(head);//添加菜品 
		else if (choice == 'D') {
			system("cls");
			goto start_manage;//返回上一步的后台欢迎界面
		}
		else {  // 错误提示 
			printf("\n请输入有效选项编号（A-D）");
			system("pause");
			system("cls");
			goto start_dishchange;
		}
		goto start_dishchange;
	}
	else  //错误输入 
	{
		printf("\n请输入有效选项编号（1-4）：");
		system("cls");
		goto start_manage;//返回管理界面 
	}
}

//创建菜单链表函数 
struct menu* creat(void) {
	struct menu* p1, * p2, * head;
	int n = 0;
	head = NULL;
	p1 = p2 = (struct menu*)malloc(size);
	FILE* fp;
	fp = fopen("D:\\桌面\\课程设计\\点餐系统\\餐馆菜单信息.txt", "r");
	if (fp == NULL) {
		printf("菜单信息文件打开失败！\n");
		exit(0);
	}
	fscanf(fp, "%d %s %d", &p1->serial_number, p1->dishes_name, &p1->money);
	while (p1->serial_number != 0) {  //菜单结尾标志 
		n = n + 1;
		if (n == 1) head = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (struct menu*)malloc(size);
		fscanf(fp, "%d %s %d", &p1->serial_number, p1->dishes_name, &p1->money);
	}
	fclose(fp);
	p2->next = NULL;
	return head;
}

//将菜单信息写入文件中
void print_to_file(struct menu* p) {
	FILE* pf;
	pf = fopen("D:\\桌面\\课程设计\\点餐系统\\餐馆菜单信息.txt", "w");//注意这里是"w"格式打开，覆盖文件原内容
	if (pf == NULL) {
		printf("文件打开失败！");
		exit(0);
	}
	while (p) {
		fprintf(pf, "%d %s %d\n", p->serial_number, p->dishes_name, p->money);
		p = p->next;
	}
	fprintf(pf, "%d %s %d", 0, NULL, 0);//最后一行 设置截止标志
}

//删除菜品函数 
struct menu* del(struct menu* head, int number) {
	printf("\n请输入要删除的菜品编号：");
	scanf("%d", &number);
	getchar();//吸收换行符
	struct menu* p1, * p2;
	p1 = head;
	p2 = NULL;
	if (head == NULL) printf("菜单列表为空，请您前往添加！\n");
	//遍历寻找结点
	while (p1->serial_number != number && p1->next) {
		p2 = p1; //p2指向前一节点
		p1 = p1->next;
	}
	//删除结点
	if (p1->serial_number == number) {
		if (p1 == head) head = p1->next;
		else p2->next = p1->next;
		printf("编号为 %d 的菜品已被成功删除！\n", number);
	}
	else printf("菜单中未找到编号为 %d 的菜品，请您确认后再输入！\n", number);
	print_to_file(head);//将修改过后的菜单信息写入文件中
	system("pause");
	return (head);
}

//添加菜品函数
struct menu* insert(struct menu* head) {
	struct menu* dish_insert;//定义一个结构体 用来存储要插入的菜品信息 
	dish_insert = (struct menu*)malloc(size);//开辟空间 
	printf("\n请输入要添加的菜品编号、名称和价格：");
	scanf("%d %s %d", &dish_insert->serial_number, dish_insert->dishes_name, &dish_insert->money);
	getchar();//吸收换行符
	struct menu* p0, * p1, * p2;
	p1 = head;
	p2 = NULL;
	p0 = dish_insert;
	if (head == NULL) {//空表 
		head = p0;
		p0->next = NULL;
	}
	else {
		while (p0->serial_number > p1->serial_number && p1->next != NULL) { //查找位置 
			p2 = p1;
			p1 = p1->next;
		}
		if (p0->serial_number <= p1->serial_number) { //表中间 
			if (p1 == head) head = p0;
			else p2->next = p0;
			p0->next = p1;
		}
		else { //表尾 
			p1->next = p0;
			p0->next = NULL;
		}
		printf("编号为 %d 的菜品已被成功加入!\n", dish_insert->serial_number);
	}
	print_to_file(head);//将修改过后的菜单信息写入文件中
	system("pause");
	return (head);
}

//出餐功能函数 
void DiningOut(int* length) {
	int dishnum;
	if (*length <= 0) {   //无需出餐则退出
		printf("\n暂时无需出餐！");
		return;
	}
	printf("请输入餐号(输入 0 结束出餐）：");
	while (scanf("%d", &dishnum) && dishnum != 0) {
		printf("%03d 号餐已出餐\n", dishnum);
		--(*length);//待出餐队伍长度-1
	}
}

//选座功能函数
int ChooseSeat(int* desknumber) {
	FILE* pf;
	int numbers[MAX_SEATS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0 }; // 初始化座位为10个数字
	int i, num, isUsed = 0;
	// 打开文件以读取座位信息
	pf = fopen("D:\\桌面\\课程设计\\点餐系统\\座位编号.txt", "r");
	if (pf == NULL) {
		printf("无法打开文件\n");
		exit(0);
	}
	for (i = 0; i < MAX_SEATS; i++) {
		if (fscanf(pf, "%d", &numbers[i]) != 1) { // 如果无法读取到数字，则说明文件已经读到末尾了
			break;
		}
	}
	fclose(pf); // 关闭文件
choose:
	do {
		printf("请选择您的的座位号(1 - 10)：");
		scanf("%d", &num);
	} while (num < 1 || num > 10);
	for (i = 0; i < MAX_SEATS; i++) { // 检索数字是否在文件里
		if (numbers[i] == num) { // 如果数字在文件里
			isUsed = 1;
			break;
		}
	}
	if (isUsed) { // 如果数字在文件里，输出用户输入的数字并从文件里删除这个数字
		printf("选择成功！您的座位号是：%d\n", num);
		for (i = 0; i < MAX_SEATS; i++) { // 将后面的数字向前移动一位
			if (numbers[i] == num) { // 如果找到该数字，则删除它
				int j;
				for (j = i; j < MAX_SEATS - 1; j++) { // 将后面的数字向前移动一位
					numbers[j] = numbers[j + 1];
				}
				break;
			}
		}
		pf = fopen("D:\\桌面\\课程设计\\点餐系统\\座位编号.txt", "w"); // 重新打开文件以写入修改后的座位信息
		if (pf == NULL) {
			printf("无法打开文件\n");
			exit(0);
		}
		for (i = 0; i < MAX_SEATS; i++) { // 将修改后的数字写入文件
			fprintf(pf, "%d\n", numbers[i]);
		}
		fclose(pf); // 关闭文件
	}
	else { // 如果数字不在文件里，输出座位已被使用
		printf("座位已被使用，请您重新选择\n");
		goto choose;
	}
	*desknumber = num;
}


//输出菜单信息界面的函数 
void menu(struct menu* head)
{
	struct menu* p;
	p = head;
	printf("------编号------名称-----价格---------------\n");
	while (p != NULL) {
		printf("|     %2d\t      %s\t    %d\t   |\t\n", p->serial_number, p->dishes_name, p->money);
		p = p->next;
	}
	printf("--------------------------------------------\n");

}

//点餐计费函数 
int order(struct menu* head, int Num[])
{
	int Money = 0;
	printf("请您开始点餐 ^_^\n");
	printf("（请输入想吃的菜品的编号，可一次输入多个编号，每两个编号之间请用空格分开，最后以0结束）\n");
	for (int i = 0;; i++)
	{
		scanf("%d", &Num[i]);
		if (Num[i] == 0)
		{
			break;
		}
		else
		{
			int j;//链表无法像数组一样直接跳到指定位置，需要从前往后挨个找 
			struct menu* p1;
			p1 = head;//使每次从表头开始往后找
			for (j = 1; j < Num[i]; j++) {
				p1 = p1->next;
			}
			Money += (p1->money);
		}
	}
	system("cls");
	return Money;
}


//记录流水函数 
void daybook(int NUM[], struct menu* p, int PAYMONEY) {
	FILE* fp1;//定义文件指针 
	fp1 = fopen("D:\\桌面\\课程设计\\点餐系统\\餐馆订单流水.txt", "a+");
	while ((fp1 = fopen("D:\\桌面\\课程设计\\点餐系统\\餐馆订单流水.txt", "a+")) == NULL) {
		printf("订单流水文件打开失败！");
		exit(0);
	}
	int i;
	for (i = 0;; i++)
	{
		if (NUM[i] == 0)
		{
			break;
		}
		int j;//链表无法像数组一样直接跳到指定位置，需要从前往后挨个找 
		struct menu* p1;
		p1 = p;//使每次都是从表头开始往后找
		for (j = 1; j < NUM[i]; j++) {
			p1 = p1->next;
		}
		fprintf(fp1, "   %d\t     %s\t   %d\t\n", NUM[i], p1->dishes_name, p1->money);//写入文件，方便查看餐厅流水 
	}
	fprintf(fp1, "本桌总共消费 %d 元\n", PAYMONEY);
	fclose(fp1);
}

//菜品价格修改系统函数
void dish_money_change(struct menu* head)
{
	int number, changemoney;
	printf("\n请输入菜品编号: ");
	scanf("%d", &number);
	printf("\n请输入要修改的价格: ");
	scanf("%d", &changemoney);
	int j;//链表无法像数组一样直接跳到指定位置，需要从前往后挨个找 
	struct menu* p;
	p = head;//使每次都从表头开始往后找 
	for (j = 1; j < number; j++)
		p = p->next;
	p->money = changemoney;
	printf("\n修改成功！");
	print_to_file(head);//将修改过后的菜单信息写入文件中
	system("pause");
	system("cls");
}

//菜品名修改功能函数 
void dish_name_change(struct menu* head, int number, char dish_name[])
{
	printf("请输入要修改的菜品编号: ");
	scanf("%d", &number);
	getchar(); //吸收换行符 
	printf("\n请输入修改的名称: ");
	gets_s(dish_name, sizeof(dish_name));
	int j;  //链表无法像数组一样直接跳到指定位置，需要从前往后挨个找 
	struct menu* p;
	p = head;  //使每次从表头开始往后找
	for (j = 1; j < number; j++)
		p = p->next;
	strcpy(p->dishes_name, dish_name);
	print_to_file(head);//将修改过后的菜单信息写入文件中
	printf("\n修改成功！");
	system("pause");
	system("cls");
}

//等待上餐界面函数 
void waiting(int length, int num)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|  已收到您的菜单，请等待上餐  |\n");
	printf("|                              |\n");
	printf("|      您的取餐号是 %03d        |\n", num);
	printf("|                              |\n");
	printf("| 你的前方还有 %d 位客人在等待  |\n", length);
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}

//输出账单函数
void bill(int NUM[], struct menu* p, int PAYMONEY)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|        请查收您的账单        |\n");
	printf("|      如有异议请联系服务员    |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");

	int i;
	for (i = 0;; i++)
	{
		if (NUM[i] == 0)
		{
			break;
		}
		int j;//链表无法像数组一样直接跳到指定位置，需要从前往后挨个找 
		struct menu* p1;
		p1 = p;//使每次都是从表头开始往后找
		for (j = 1; j < NUM[i]; j++) {
			p1 = p1->next;
		}
		printf("   %d\t     %s\t   %d\t\n", NUM[i], p1->dishes_name, p1->money);//打印到屏幕
	}
	printf("您总共消费 %d 元\n", PAYMONEY);
}

//外部界面的函数
void outside(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|     欢迎来到餐厅点餐系统     |\n");
	printf("|                              |\n");
	printf("|           Welcome!           |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}

//欢迎客人界面的函数
void welcome(int PEOPLENUMBER, int DESK)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|  %d号桌的%02d位客人，欢迎光临   |\n", PEOPLENUMBER, DESK);
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}


//后台管理系统函数
void backstage_welcome(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|     欢迎进入后台管理系统     |\n");
	printf("|                              |\n");
	printf("|         <出餐请输入1>        |\n");
	printf("|                              |\n");
	printf("|       <修改价格请输入2>      |\n");
	printf("|                              |\n");
	printf("|       <修改菜品请输入3>      |\n");
	printf("|                              |\n");
	printf("|    <退出管理员界面请输入4>   |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
	printf("\n请输入您的选择的管理项目：");
}

//进入菜品修改系统函数
void dish_change(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|     欢迎进入菜品修改系统     |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|      <修改菜品名请输入A>     |\n");
	printf("|                              |\n");
	printf("|       <删除菜品请输入B>      |\n");
	printf("|                              |\n");
	printf("|       <添加菜品请输入C>      |\n");
	printf("|                              |\n");
	printf("|   <退出菜品修改界面请输入D>  |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}

//送客界面函数 
void goodbye(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|        感谢您的惠顾！        |\n");
	printf("|                              |\n");
	printf("|         Thank  You!          |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}
