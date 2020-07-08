#include <stdio.h>
#include <stdlib.h>
struct stud_node {
	char name[100];
	struct stud_node *next;
};
struct stud_node *head,*tail;
FILE *fp=NULL;
char fname[100];
int open=0,create=0;

void my_open(char fname[]);/*打开文件*/
struct stud_node *my_create();/*创建新文件*/
void my_look(struct stud_node *head);/*显示文件内容*/
struct stud_node *my_insert(struct stud_node *head);/*插入行*/
struct stud_node *my_delete(struct stud_node *head);/*删除行*/
struct stud_node *my_copy(struct stud_node *head);/*拷贝行*/
struct stud_node *my_mix(struct stud_node *head);/*修改行*/
void my_search(struct stud_node *head);/*查找字符串*/
struct stud_node *my_replace(struct stud_node *head);/*替换字符串*/
void my_save(struct stud_node *head, FILE *fp, char fname[]);/*存盘退出*/
void my_give_up(FILE *fp, struct stud_node *head);/*放弃编辑*/
int my_strcmp(const char *str1, const char *str2);/*我的字符串比较*/
int my_strlen(char *p);/*我的字符串长度测量*/
char *my_strcpy(char*str1,const char*str2);/*我的字符串复制*/
char *my_strcat(char*str1,char*str2);/*我的字符串连接*/

int main()
{
	int choice;

	while (1) {
	printf("*******************************************************\n");
	printf("***  请选择:1.打开文件<新或旧> 2.显示文件内容       ***\n");
	printf("***         3.插入行  4.删除行 5.拷贝行  6.修改行   ***\n");
	printf("***         7.查找字符串       8.替换字符串         ***\n");
	printf("***         9.存盘退出         0.放弃编辑           ***\n");
	printf("*******************************************************\n");
	scanf("%d",&choice);
	while(open==0 && choice!=1){
		printf("文件未打开，请重新输入选项：");
		scanf("%d",&choice);
	}
	while(open==1 && choice==1){
		printf("文件已打开，请重新输入选项：");
		scanf("%d",&choice);
	}
	switch (choice) {
	case 1:
		printf("请输入选择  1:打开文件 2：新建文件 :");
		scanf("%d",&choice);
		if(choice==1){
			printf("请输入文件名<可包括盘符、路径、不超过19个字符>（目前只支持英文）：");
			scanf("%s",fname);
			my_open(fname);
		}
		else{
			head = my_create(head);
		}
		break;
	case 2:my_look(head); break;
	case 3:head = my_insert(head); break;
	case 4:head = my_delete(head); break;
	case 5:head = my_copy(head); break;
	case 6:head = my_mix(head); break;
	case 7:my_search(head); break;
	case 8:head = my_replace(head); break;
	case 9:my_save(head, fp, fname); break;
		case 0: my_give_up(fp,head); break;
		}
	}
	return 0;
}
/*打开文件*/
void my_open(char fname[])
{
	FILE *fp;
	char q[100];
	int choice = 0;
	struct stud_node *p;

	while ((fp = fopen(fname, "r")) == NULL) {
		printf("文件打开错误,请输入选择：  1：重新输入2：新建文件\n");
		scanf("%d", &choice);
		if (choice == 2) {
			head = tail = my_create();
			break;
		}
		else {
			printf("请输入文件名<可包括盘符、路径、不超过19个字符>：");
			scanf("%s", fname);
		}
	}
	if(choice!=2){
		printf("打开成功\n");
		open=1;
		/*用链表来保存文件的数据*/
		head = tail = NULL;
		while (!feof(fp)) {//到文件结尾就退出循环
			p = (struct stud_node*)malloc(sizeof(struct stud_node));
			p->next = NULL;
			fgets(q,100,fp);
			my_strcpy(p->name, q);
			if (head == NULL) {
				head = p;
			}
			else {
				tail->next = p;
			}
			tail = p;
		}
		tail->next=NULL;
	}
}
/*创建文件*/
struct stud_node *my_create()
{
	char q[100], flag[20];

	printf("请输入要创建的文件名及位置:");
	scanf("%s", fname);
	while ((fp = fopen(fname, "w")) == NULL)
	{
		printf("创建错误,请重新输入：\n");
		scanf("%s", fname);
	}
	printf("创建成功\n");
	head=tail=NULL;
	create=1;
	open=1;

	return head;
}
/*显示文件内容*/
void my_look(struct stud_node *head)
{
	int i=1,sum=0;
	struct stud_node *p,*pre;

	for(pre=head;pre!=NULL;pre=pre->next){//遍历链表，sum计算链表有多少个结点
	sum++;
	}
	p=(struct stud_node*)malloc(sizeof(struct stud_node));
	p=head;
	if(sum==0 || head==NULL ){
		printf("此文本为空");
	}
	else if(create == 1){
		for(i=1;i<=sum;i++){
			printf("%d:%s",i,p->name);
			p=p->next;
		}
	}
	else{
		for(i=1;i<sum;i++){
			printf("%d:%s",i,p->name);
			p=p->next;
		}
	}
	printf("\n");
}
/*插入行*/
struct stud_node *my_insert(struct stud_node *head)
{
	struct stud_node *pre, *now, *p, *newhead, *newtail;
	int l, m, i, k, sum=0;
	char q[100];


	newhead = newtail = NULL;
	pre = now = head;
	for(pre=head;pre!=NULL;pre=pre->next){//遍历链表，sum计算链表有多少个结点
		sum++;
	}
	pre = head;
	printf("在第l行前插入m行，请输入l m:");
	scanf("%d%d", &l, &m);
	if(l<=0){
		printf("插入的行号不对,请重新输选择\n");
		return head;
	}
	printf("请顺序输入待插入内容：\n");
	scanf("\n");
	/*先将输入进来的内容弄成新链表*/
	for (i = 0; i < m; i++) {
		p = (struct stud_node*)malloc(sizeof(struct stud_node));
		p->next = NULL;
		gets(q);
		my_strcat(q,"\n");
		my_strcpy(p->name, q);
		if (newhead == NULL) {
			newhead = p;
		}
		else {
			newtail->next = p;
		}
		newtail = p;
	}
	if (head == NULL) {//头为空
		head = newhead;
	}
	else {//头不为空
		k = 1;
		while (now->next != NULL && k != l) {//找位置,now指向第l行
			k++;
			pre = now;
			now = pre->next;
		}//k<=l
		if (l == 1) {//插在第一行前面
			newtail->next = now;
			head = newhead;
		}
		else if(l>sum){//插在尾部
			newtail->next = NULL;
			now->next = newhead;
		}
		else {//插在中间
			newtail->next = now;
			pre->next = newhead;
		}
	}
	return head;
}
/*删除行*/
struct stud_node *my_delete(struct stud_node *head)
{
	int l, m, i, k,sum=0;
	struct stud_node *pre, *now;

	for(pre=head;pre!=NULL;pre=pre->next){//遍历链表，sum计算链表有多少个结点
		sum++;
	}
	if(sum==0||head==NULL){
		printf("此文本为空，无可修改行\n");
		return head;
	}
	printf("从第l行起删除m行，请输入l m:");
	scanf("%d%d", &l, &m);
	while(l<=0||l>sum){
		printf("删除的行号不对,请重新输选择\n");
		return head;
	}
	if (head != NULL && l == 1) {//被删除的为表头结点
		for (i = 0; i < m; i++) {
			now = head;
			head = head->next;
			free(now);
		}
		if (head == NULL) {
			printf("数据已全部删除\n");
		}
	}
	else {//被删除的为非表头结点  l!=1
		pre = head;
		now = pre->next;
		k = 2;
		while (now->next != NULL && k != l) {//找位置,now指向第k行
			k++;
			pre = now;
			now = pre->next;
		}//k==l
		for (i = 0; i < m && now != NULL; i++) {
			pre->next = now->next;
			free(now);
			now=pre->next;
		}
	}
	return head;
}
/*拷贝行*/
struct stud_node *my_copy(struct stud_node *head)
{
	int l, m, k, i, j, sum=0;//i用来找行，j用于循环计算
	struct stud_node *pre, *now, *p, *newhead, *newtail;

	for(pre=head;pre!=NULL;pre=pre->next){//遍历链表，sum计算链表有多少个结点
		sum++;
	}
	if(sum==0||head==NULL){
		printf("此文本为空，无拷贝数据\n");
		return head;
	}
	printf("把第l行开始的m行插在原k行之前，请输入l m k:");
	scanf("%d%d%d",&l,&m,&k);
	while(l<=0||k<=0){
		printf("选择的行号不对,请重新输选择\n");
		return head;
	}
	pre = now = head;
	newhead = newtail = NULL;
	i = 1;
	while (now->next !=NULL && i != l) {//找第l行
		i++;
		pre = now;
		now = pre->next;//now指向第l行，pre指向第l-1行
	}//i==l
	for (j = 0; j < m; j++) {//把要拷贝的行建成新的链表
		p = (struct stud_node*)malloc(sizeof(struct stud_node));
		my_strcpy(p->name, now->name);
		pre = now;
		now = pre->next;
		if (newhead == NULL) {
			newhead = p;
		}
		else {
			newtail->next = p;
		}
		newtail = p;
		}
	pre = now = head;
	i = 1;
	while (now->next != NULL && i != k) {//找第k行
		i++;
		pre = now;
		now = pre->next;
	}//i==k
	if (k == 1) {//插在第一行前面
		newtail->next = now;
		head = newhead;
	}
	else if(k>sum){//插在尾部
		printf("已超过最大行号，默认插在最后一行\n");
		my_strcat(now->name,"\n");
		newtail->next = NULL;
		now->next = newhead;
	}
	else {//插在中间
		newtail->next = now;
		pre->next = newhead;
	}
	return head;
}
/*修改行*/
struct stud_node *my_mix(struct stud_node *head)
{
	struct stud_node *pre, *now;
	int i,k,sum=0;

	for(pre=head;pre!=NULL;pre=pre->next){//遍历链表，sum计算链表有多少个结点
		sum++;
	}
	if(sum==0||head==NULL){
		printf("此文本为空，无可修改行\n");
		return head;
	}
	printf("请输入待修改的行号：");
	scanf("%d", &k);
	if(k<=0){
		printf("修改的行号不对,请重新输选择\n");
		return head;
	}
	i = 1;
	pre = now = head;
	while (now->next != NULL && i != k) {
		i++;
		pre = now;
		now = pre->next;
	}//i<=k
	if(i==k){//k<=sum
		printf("%d:%s\n", k, now->name);
		printf("请输入新内容：");
		scanf(" ");
		gets(now->name);
		my_strcat(now->name,"\n");

	}else{//k>sum
		printf("已超过最大行号，默认修改最后一行\n");
		printf("%d:%s\n", i, now->name);
		printf("请输入新内容：");
		scanf(" ");
		gets(now->name);
		my_strcat(now->name,"\n");
	}
	return head;
}
/*查找字符串*/
void my_search(struct stud_node *head)
{
	char q[100],m[100],flag[20]="Y";//q为待查找字符串,即m为母串，q为子串
	int count = 0, i, j, k, n1, n2, sign=0,sum=0;
	struct stud_node *pre, *now;

	for(pre=head;pre!=NULL;pre=pre->next){//遍历链表，sum计算链表有多少个结点
		sum++;
	}
	if(sum==0||head==NULL){
		printf("此文本为空，无可查找字符\n");
	}
	else{
		printf("请输入待查找的字符串：\n");
		scanf("\n");
		gets(q);
		pre = now = head;
		k = 1;//行
		while (now != NULL && strcmp(flag,"N")!=0 && k<sum) {//一行一行比较
			n1 = my_strlen(now->name);//行的长度
			n2 = my_strlen(q);//要查找的字符串长度
			my_strcpy(m, now->name);
			/*在m中找q*/
			for (i = 0; i < n1; i++) {//在一行内查找
				j = 0;//刷新j
				if (m[i] == q[0]) {//m的第i个字符与q第0个字符比较
					for (j = 0; j < n2; j++) {//第一个相等，判断后续是否也相等
						if (m[i + j] != q[j]) {//m的第i+j个字符与q的第j个字符比较
							break;
						}
					}
				}
				if (j == n2) {//正常退出循环，说明全部相等，找到了
					printf("第%d行：%s\n", k, m);
					count++; sign = 1;
					printf("第%d个字符处找到。继续查找吗<Y/N>?", count);
					gets(flag);
				}
				if (strcmp(flag,"N")==0) {//flag等于N
					break;
				}
				else {
					sign = 0;
				}
			}
			pre = now;
			now = pre->next;
			k++;
		}
		if (sign == 0) {
			printf("没找到\n");
		}
	}
}
/*替换字符串*/
struct stud_node *my_replace(struct stud_node *head)
{
	char q[100], t[100], m[100], flag[20], flag2[20];//q为待替换字符串,即m为母串，q为子串，q将替换为t, flag用于决定是否替换， flag2用于决定是否继续替换
	int count = 0, i, j, k, n1, n2, n3, sign = 0,sum=0;//sign用来表示是否找到
	struct stud_node *pre, *now;

	for(pre=head;pre!=NULL;pre=pre->next){//遍历链表，sum计算链表有多少个结点
		sum++;
	}
	if(sum==0||head==NULL){
		printf("此文本为空，无可替换字符\n");
		return head;
	}
	printf("请输入待替换的字符串：");
	scanf("%s", q);
	printf("替换为(暂时只能接受相同字符数量):");
	scanf("%s", t);
	pre = now = head;
	k = 1;//行
	while (now != NULL && k<sum) {//一行一行比较
		n1 = my_strlen(now->name);
		n2 = my_strlen(q);
		n3 = my_strlen(t);
		my_strcpy(m, now->name);//m用来暂时储存该行的数据
		/*在m中找q*/
		for (i = 0; i < n1; i++) {//在一行内查找
			j = 0;//刷新j
			my_strcpy(flag,"N");
			my_strcpy(flag2,"N");
			if (m[i] == q[0]) {//m的第i个字符与q第0个字符比较
				for (j = 0; j < n2; j++) {//第一个相等，判断后续是否也相等
					if (m[i + j] != q[j]) {//m的第i+j个字符与q的第j个字符比较
						break;
					}
				}
			}
			if (j == n2) {//正常退出循环，说明全部相等，找到了
				printf("第%d行：%s\n", k, m);
				count++; sign = 1;
				printf("第%d个字符处找到。是否替换<Y/N>?", count);
				scanf(" ");
				gets(flag);
			}
			if (my_strcmp(flag,"Y")==0) {//要替换
				for (j = 0; j < n3; j++) {//把m中的q替换成t
					m[i + j] = t[j];
				}
				my_strcpy(now->name,m);//暂时只能替换相同数量的
				printf("替换成功,继续替换吗<Y/N>?");
				scanf(" ");
				gets(flag2);
			}
			if (my_strcmp(flag2,"N")==0 && my_strcmp(flag,"Y")==0) {//退出for循环
				break;
			}
			else {//继续替换接着找 或者 没找到接着找 或者 不替换接着找
				sign = 0;
			}
		}
		if (my_strcmp(flag2,"N")==0 && my_strcmp(flag,"Y")==0) {//退出while循环
				break;
			}
		pre = now;
		now = pre->next;
		k++;
	}
	if (sign == 0) {
		printf("没找到\n");
	}
	return head;
}
/*存盘退出*/
void my_save(struct stud_node *head, FILE *fp, char *fname)
{
	struct stud_node *now;

	now = head;
	fclose(fp);
	fp = fopen(fname, "w");//改变文件属性，切换为写操作
	//将链表内容输入到文件中
	while (now != NULL) {
		fprintf(fp, "%s", now->name);
		now = now->next;
	}
	if (fclose(fp) == 0) {
		printf("Press any key to continue");
		exit(0);
	}
}
/*放弃编辑*/
void my_give_up(FILE *fp, struct stud_node *head)
{
    fclose(fp);
    printf("Press any key to continue");
	exit(0);
}
/*我的字符串比较*/
int my_strcmp(const char *str1, const char *str2)
{
	int num;
	while(!(num=*(unsigned char*)str1-*(unsigned char*)str2) && *str1){
		str1++;//用unsigned char*  强转因为相减的字符ASC码值为正数没有负数，也就是无符号数
		str2++;//字符相等继续比较，字符不相等就跳出循环
	}//当两个字符串相同时，比较到最后一个字符\0  字符相减num==0，取反成立，所以就要看str1或者str2的字符，如果是\0表示0为假跳出循环

	if(num<0){
		return -1;
	}
	else if(num>0){
		return 1;
	}
	else{
		return 0;
	}
}
 /*我的字符串长度测量*/
int my_strlen(char *p)
{
	int count=0;
	while(*p){
		p++;
		count++;
	}
	return count;
}
/*我的字符串复制*/
char *my_strcpy(char*str1,const char*str2)
{
	char*str3 = str1;//str3用来保存str1起始地址
	while(*str1 = *str2){//一个一个复制
		str1++;
		str2++;
	}
	return str3;//返回数组起始地址
}
/*我的字符串连接*/
char *my_strcat(char*str1,char*str2)
{
	char*p=str1;
	while(*str1!='\0'){
		str1++;
	}
	while(*str2!='\0'){
		*str1=*str2;
		str1++;
		str2++;
	}
	*str1='\0';
	return p;
}
