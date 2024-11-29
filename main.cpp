#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<windows.h>
#define size sizeof(struct menu)
#define MAX_SEATS 11  //������λ��

struct menu    //����һ���ṹ�� �洢��Ʒ��Ϣ 
{
	int serial_number;//��Ʒ��� 
	char dishes_name[100];//��Ʒ���� 
	int money;//��Ʒ�۸�
	struct menu* next; //�ṹ��ָ�� ָ����һ���ṹ�� 
};

struct menu* creat(void); //�����˵����� ������Ĵ����� 
struct menu* del(struct menu* head, int number); //ɾ����Ʒ���� ������ڵ��ɾ���� 
struct menu* insert(struct menu* head); //��Ӳ�Ʒ���� ������ڵ�Ĳ��룩 
void menu(struct menu* head); //����˵���Ϣ����ĺ��� ������Ĵ�ӡ��
void outside(void); //�ⲿ���溯�� 
void DiningOut(int* length); //���͹��ܺ���
int ChooseSeat(int* desknumber); //ѡ�����ܺ���
void welcome(int PEOPLENUMBER, int DESK); //��ӭ���˽���ĺ��� 
int order(struct menu* head, int Num[]); //��ͼƷѺ��� 
void waiting(int length, int num); //�ȴ��ϲͽ��溯�� 
void bill(int NUM[], struct menu* p, int PAYMONEY); //����˵����� 
void daybook(int NUM[], struct menu* p, int PAYMONEY);//��¼������ˮ�˺��� 
void goodbye(void); //�Ϳͽ��溯�� 
void backstage_welcome(void); //��̨����ϵͳ���� 
void dish_change(void); //�����Ʒ�޸�ϵͳ���� 
void dish_money_change(struct menu* head);//��Ʒ�۸��޸�ϵͳ����
void dish_name_change(struct menu* head, int number, char dish_name[]); //��Ʒ���޸�ϵͳ����  

struct menu* head;

int main() {
	struct menu* pmenu;//����ṹ��ָ�� 
	head = creat(); //�����˵���Ϣ����
	//pmenu = head;//����ͷ����pmenu
	int id, dishnum = 0, length = -1; //��һλ�˿�ǰ���Ŷ�����Ϊ 0 
start:
	int desknumber, human;
	int n, num[50], paymoney = 0;//����֧������ 
	int keyword;//���� 
	int change;//ѡ�� 
	outside();//�����ⲿ���溯�� 
	printf("��ѡ��������ݣ��˿� 1 ������Ա 2����");
	scanf("%d", &id);
	if (id == 2) goto start_backstage;//�����̨����ϵͳ 
	ChooseSeat(&desknumber);
	printf("������Ͳ�����: ");
	scanf("%d", &human);
	system("cls");
	welcome(desknumber, human);//��ӭ 
	system("pause");
	system("cls");
	menu(head); //��ӡ�˵� 
	paymoney = order(head, num); //��Ͳ��Ʒ� 
	++length; //ÿ��һ�βͣ��ȴ������Ŷ��鳤�� + 1
	waiting(length, ++dishnum); //�ȴ�����
start_to_bill:
	printf("�鿴�˵�������1\n");
	scanf("%d", &n);
	system("cls");
start_to_pay:
	if (n == 1) //������ȷ
	{
		bill(num, head, paymoney); //��ӡ�˵�
		daybook(num, head, paymoney); //��¼����ˮ���ļ��� 
	}
	else
	{
		printf("\n������������������!\n");//������� 
		goto start_to_bill; //���� 
	}
	printf("�Ѿ�������ϵ����Ա������Ա���ܿ쵽������Ե�\n");
	printf("\n�����Աȷ�Ϻ��������루1111����\n");
	scanf("%d", &keyword);//�������� 
	system("cls");
	if (keyword == 1111)
	{
		int input;
		goodbye();//�Ϳͽ���
		printf("����1�����õ��ϵͳ\n");
		printf("����0���رյ��ϵͳ\n");
		printf("��ѡ��");
		scanf("%d", &input);
		system("cls");
		if (input == 1)
			goto start;
		else {
			length = 0;//����
			exit(0);
		}
	}
	else {
		printf("\n���������������������: \n\n");
		goto start_to_pay;
	}
start_backstage://��̨ 
	printf("���������Ա���루1111��: ");
	scanf("%d", &keyword);
	if (keyword != 1111) {
		printf("�������");
		system("pause");
		system("cls");
		goto start;//������� ���� 
	}
	system("cls");//������ȷ ���� 
start_manage:
	backstage_welcome();//��̨��ӭ���� 
	scanf("%d", &change);//����ѡ�� 
	if (change == 1) { //����
		DiningOut(&length);
		system("pause");
		system("cls");
		goto start_manage;
	}
	else if (change == 2) {
		dish_money_change(head);//�����Ʒ�۸��޸ĺ��� 
		goto start_manage;

	}
	else if (change == 4) {//������һ���� 
		system("cls");
		goto start;
	}
	else if (change == 3) {
		getchar();//���ջ��з�
	start_dishchange:      //�����Ʒ�޸�ϵͳ
		system("cls");
		dish_change();//��Ʒ�޸�ϵͳ��ӭ���� 
		int number = 0;
		char dish_name[50], choice;
		printf("\n��ѡ��������Ŀ��");

		scanf("%c", &choice);
		if (choice == 'A')
			dish_name_change(head, number, dish_name);//�����޸� 
		else if (choice == 'B')
			head = del(head, number);//ɾ����Ʒ 
		else if (choice == 'C')
			head = insert(head);//��Ӳ�Ʒ 
		else if (choice == 'D') {
			system("cls");
			goto start_manage;//������һ���ĺ�̨��ӭ����
		}
		else {  // ������ʾ 
			printf("\n��������Чѡ���ţ�A-D��");
			system("pause");
			system("cls");
			goto start_dishchange;
		}
		goto start_dishchange;
	}
	else  //�������� 
	{
		printf("\n��������Чѡ���ţ�1-4����");
		system("cls");
		goto start_manage;//���ع������ 
	}
}

//�����˵������� 
struct menu* creat(void) {
	struct menu* p1, * p2, * head;
	int n = 0;
	head = NULL;
	p1 = p2 = (struct menu*)malloc(size);
	FILE* fp;
	fp = fopen("D:\\����\\�γ����\\���ϵͳ\\�͹ݲ˵���Ϣ.txt", "r");
	if (fp == NULL) {
		printf("�˵���Ϣ�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	fscanf(fp, "%d %s %d", &p1->serial_number, p1->dishes_name, &p1->money);
	while (p1->serial_number != 0) {  //�˵���β��־ 
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

//���˵���Ϣд���ļ���
void print_to_file(struct menu* p) {
	FILE* pf;
	pf = fopen("D:\\����\\�γ����\\���ϵͳ\\�͹ݲ˵���Ϣ.txt", "w");//ע��������"w"��ʽ�򿪣������ļ�ԭ����
	if (pf == NULL) {
		printf("�ļ���ʧ�ܣ�");
		exit(0);
	}
	while (p) {
		fprintf(pf, "%d %s %d\n", p->serial_number, p->dishes_name, p->money);
		p = p->next;
	}
	fprintf(pf, "%d %s %d", 0, NULL, 0);//���һ�� ���ý�ֹ��־
}

//ɾ����Ʒ���� 
struct menu* del(struct menu* head, int number) {
	printf("\n������Ҫɾ���Ĳ�Ʒ��ţ�");
	scanf("%d", &number);
	getchar();//���ջ��з�
	struct menu* p1, * p2;
	p1 = head;
	p2 = NULL;
	if (head == NULL) printf("�˵��б�Ϊ�գ�����ǰ����ӣ�\n");
	//����Ѱ�ҽ��
	while (p1->serial_number != number && p1->next) {
		p2 = p1; //p2ָ��ǰһ�ڵ�
		p1 = p1->next;
	}
	//ɾ�����
	if (p1->serial_number == number) {
		if (p1 == head) head = p1->next;
		else p2->next = p1->next;
		printf("���Ϊ %d �Ĳ�Ʒ�ѱ��ɹ�ɾ����\n", number);
	}
	else printf("�˵���δ�ҵ����Ϊ %d �Ĳ�Ʒ������ȷ�Ϻ������룡\n", number);
	print_to_file(head);//���޸Ĺ���Ĳ˵���Ϣд���ļ���
	system("pause");
	return (head);
}

//��Ӳ�Ʒ����
struct menu* insert(struct menu* head) {
	struct menu* dish_insert;//����һ���ṹ�� �����洢Ҫ����Ĳ�Ʒ��Ϣ 
	dish_insert = (struct menu*)malloc(size);//���ٿռ� 
	printf("\n������Ҫ��ӵĲ�Ʒ��š����ƺͼ۸�");
	scanf("%d %s %d", &dish_insert->serial_number, dish_insert->dishes_name, &dish_insert->money);
	getchar();//���ջ��з�
	struct menu* p0, * p1, * p2;
	p1 = head;
	p2 = NULL;
	p0 = dish_insert;
	if (head == NULL) {//�ձ� 
		head = p0;
		p0->next = NULL;
	}
	else {
		while (p0->serial_number > p1->serial_number && p1->next != NULL) { //����λ�� 
			p2 = p1;
			p1 = p1->next;
		}
		if (p0->serial_number <= p1->serial_number) { //���м� 
			if (p1 == head) head = p0;
			else p2->next = p0;
			p0->next = p1;
		}
		else { //��β 
			p1->next = p0;
			p0->next = NULL;
		}
		printf("���Ϊ %d �Ĳ�Ʒ�ѱ��ɹ�����!\n", dish_insert->serial_number);
	}
	print_to_file(head);//���޸Ĺ���Ĳ˵���Ϣд���ļ���
	system("pause");
	return (head);
}

//���͹��ܺ��� 
void DiningOut(int* length) {
	int dishnum;
	if (*length <= 0) {   //����������˳�
		printf("\n��ʱ������ͣ�");
		return;
	}
	printf("������ͺ�(���� 0 �������ͣ���");
	while (scanf("%d", &dishnum) && dishnum != 0) {
		printf("%03d �Ų��ѳ���\n", dishnum);
		--(*length);//�����Ͷ��鳤��-1
	}
}

//ѡ�����ܺ���
int ChooseSeat(int* desknumber) {
	FILE* pf;
	int numbers[MAX_SEATS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0 }; // ��ʼ����λΪ10������
	int i, num, isUsed = 0;
	// ���ļ��Զ�ȡ��λ��Ϣ
	pf = fopen("D:\\����\\�γ����\\���ϵͳ\\��λ���.txt", "r");
	if (pf == NULL) {
		printf("�޷����ļ�\n");
		exit(0);
	}
	for (i = 0; i < MAX_SEATS; i++) {
		if (fscanf(pf, "%d", &numbers[i]) != 1) { // ����޷���ȡ�����֣���˵���ļ��Ѿ�����ĩβ��
			break;
		}
	}
	fclose(pf); // �ر��ļ�
choose:
	do {
		printf("��ѡ�����ĵ���λ��(1 - 10)��");
		scanf("%d", &num);
	} while (num < 1 || num > 10);
	for (i = 0; i < MAX_SEATS; i++) { // ���������Ƿ����ļ���
		if (numbers[i] == num) { // ����������ļ���
			isUsed = 1;
			break;
		}
	}
	if (isUsed) { // ����������ļ������û���������ֲ����ļ���ɾ���������
		printf("ѡ��ɹ���������λ���ǣ�%d\n", num);
		for (i = 0; i < MAX_SEATS; i++) { // �������������ǰ�ƶ�һλ
			if (numbers[i] == num) { // ����ҵ������֣���ɾ����
				int j;
				for (j = i; j < MAX_SEATS - 1; j++) { // �������������ǰ�ƶ�һλ
					numbers[j] = numbers[j + 1];
				}
				break;
			}
		}
		pf = fopen("D:\\����\\�γ����\\���ϵͳ\\��λ���.txt", "w"); // ���´��ļ���д���޸ĺ����λ��Ϣ
		if (pf == NULL) {
			printf("�޷����ļ�\n");
			exit(0);
		}
		for (i = 0; i < MAX_SEATS; i++) { // ���޸ĺ������д���ļ�
			fprintf(pf, "%d\n", numbers[i]);
		}
		fclose(pf); // �ر��ļ�
	}
	else { // ������ֲ����ļ�������λ�ѱ�ʹ��
		printf("��λ�ѱ�ʹ�ã���������ѡ��\n");
		goto choose;
	}
	*desknumber = num;
}


//����˵���Ϣ����ĺ��� 
void menu(struct menu* head)
{
	struct menu* p;
	p = head;
	printf("------���------����-----�۸�---------------\n");
	while (p != NULL) {
		printf("|     %2d\t      %s\t    %d\t   |\t\n", p->serial_number, p->dishes_name, p->money);
		p = p->next;
	}
	printf("--------------------------------------------\n");

}

//��ͼƷѺ��� 
int order(struct menu* head, int Num[])
{
	int Money = 0;
	printf("������ʼ��� ^_^\n");
	printf("����������ԵĲ�Ʒ�ı�ţ���һ����������ţ�ÿ�������֮�����ÿո�ֿ��������0������\n");
	for (int i = 0;; i++)
	{
		scanf("%d", &Num[i]);
		if (Num[i] == 0)
		{
			break;
		}
		else
		{
			int j;//�����޷�������һ��ֱ������ָ��λ�ã���Ҫ��ǰ���󰤸��� 
			struct menu* p1;
			p1 = head;//ʹÿ�δӱ�ͷ��ʼ������
			for (j = 1; j < Num[i]; j++) {
				p1 = p1->next;
			}
			Money += (p1->money);
		}
	}
	system("cls");
	return Money;
}


//��¼��ˮ���� 
void daybook(int NUM[], struct menu* p, int PAYMONEY) {
	FILE* fp1;//�����ļ�ָ�� 
	fp1 = fopen("D:\\����\\�γ����\\���ϵͳ\\�͹ݶ�����ˮ.txt", "a+");
	while ((fp1 = fopen("D:\\����\\�γ����\\���ϵͳ\\�͹ݶ�����ˮ.txt", "a+")) == NULL) {
		printf("������ˮ�ļ���ʧ�ܣ�");
		exit(0);
	}
	int i;
	for (i = 0;; i++)
	{
		if (NUM[i] == 0)
		{
			break;
		}
		int j;//�����޷�������һ��ֱ������ָ��λ�ã���Ҫ��ǰ���󰤸��� 
		struct menu* p1;
		p1 = p;//ʹÿ�ζ��Ǵӱ�ͷ��ʼ������
		for (j = 1; j < NUM[i]; j++) {
			p1 = p1->next;
		}
		fprintf(fp1, "   %d\t     %s\t   %d\t\n", NUM[i], p1->dishes_name, p1->money);//д���ļ�������鿴������ˮ 
	}
	fprintf(fp1, "�����ܹ����� %d Ԫ\n", PAYMONEY);
	fclose(fp1);
}

//��Ʒ�۸��޸�ϵͳ����
void dish_money_change(struct menu* head)
{
	int number, changemoney;
	printf("\n�������Ʒ���: ");
	scanf("%d", &number);
	printf("\n������Ҫ�޸ĵļ۸�: ");
	scanf("%d", &changemoney);
	int j;//�����޷�������һ��ֱ������ָ��λ�ã���Ҫ��ǰ���󰤸��� 
	struct menu* p;
	p = head;//ʹÿ�ζ��ӱ�ͷ��ʼ������ 
	for (j = 1; j < number; j++)
		p = p->next;
	p->money = changemoney;
	printf("\n�޸ĳɹ���");
	print_to_file(head);//���޸Ĺ���Ĳ˵���Ϣд���ļ���
	system("pause");
	system("cls");
}

//��Ʒ���޸Ĺ��ܺ��� 
void dish_name_change(struct menu* head, int number, char dish_name[])
{
	printf("������Ҫ�޸ĵĲ�Ʒ���: ");
	scanf("%d", &number);
	getchar(); //���ջ��з� 
	printf("\n�������޸ĵ�����: ");
	gets_s(dish_name, sizeof(dish_name));
	int j;  //�����޷�������һ��ֱ������ָ��λ�ã���Ҫ��ǰ���󰤸��� 
	struct menu* p;
	p = head;  //ʹÿ�δӱ�ͷ��ʼ������
	for (j = 1; j < number; j++)
		p = p->next;
	strcpy(p->dishes_name, dish_name);
	print_to_file(head);//���޸Ĺ���Ĳ˵���Ϣд���ļ���
	printf("\n�޸ĳɹ���");
	system("pause");
	system("cls");
}

//�ȴ��ϲͽ��溯�� 
void waiting(int length, int num)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|  ���յ����Ĳ˵�����ȴ��ϲ�  |\n");
	printf("|                              |\n");
	printf("|      ����ȡ�ͺ��� %03d        |\n", num);
	printf("|                              |\n");
	printf("| ���ǰ������ %d λ�����ڵȴ�  |\n", length);
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}

//����˵�����
void bill(int NUM[], struct menu* p, int PAYMONEY)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|        ����������˵�        |\n");
	printf("|      ������������ϵ����Ա    |\n");
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
		int j;//�����޷�������һ��ֱ������ָ��λ�ã���Ҫ��ǰ���󰤸��� 
		struct menu* p1;
		p1 = p;//ʹÿ�ζ��Ǵӱ�ͷ��ʼ������
		for (j = 1; j < NUM[i]; j++) {
			p1 = p1->next;
		}
		printf("   %d\t     %s\t   %d\t\n", NUM[i], p1->dishes_name, p1->money);//��ӡ����Ļ
	}
	printf("���ܹ����� %d Ԫ\n", PAYMONEY);
}

//�ⲿ����ĺ���
void outside(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|     ��ӭ�����������ϵͳ     |\n");
	printf("|                              |\n");
	printf("|           Welcome!           |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}

//��ӭ���˽���ĺ���
void welcome(int PEOPLENUMBER, int DESK)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|  %d������%02dλ���ˣ���ӭ����   |\n", PEOPLENUMBER, DESK);
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}


//��̨����ϵͳ����
void backstage_welcome(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|     ��ӭ�����̨����ϵͳ     |\n");
	printf("|                              |\n");
	printf("|         <����������1>        |\n");
	printf("|                              |\n");
	printf("|       <�޸ļ۸�������2>      |\n");
	printf("|                              |\n");
	printf("|       <�޸Ĳ�Ʒ������3>      |\n");
	printf("|                              |\n");
	printf("|    <�˳�����Ա����������4>   |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
	printf("\n����������ѡ��Ĺ�����Ŀ��");
}

//�����Ʒ�޸�ϵͳ����
void dish_change(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|     ��ӭ�����Ʒ�޸�ϵͳ     |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|      <�޸Ĳ�Ʒ��������A>     |\n");
	printf("|                              |\n");
	printf("|       <ɾ����Ʒ������B>      |\n");
	printf("|                              |\n");
	printf("|       <��Ӳ�Ʒ������C>      |\n");
	printf("|                              |\n");
	printf("|   <�˳���Ʒ�޸Ľ���������D>  |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}

//�Ϳͽ��溯�� 
void goodbye(void)
{
	printf("--------------------------------\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|        ��л���Ļݹˣ�        |\n");
	printf("|                              |\n");
	printf("|         Thank  You!          |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("--------------------------------\n");
}
