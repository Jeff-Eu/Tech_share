/*

~~Sample 1系列~~

要說明stack memory的兩個觀念:
1. 同一層(相對於tree的概念)的sub functions，是共用同樣的變數宣告位址；
   不同層的sub functions，會用不同的變數宣告位址
2. stack meomory在pop掉stack之後，記憶體就被標記為free掉，可被系統修改，
   因此這時不該再用指標去取得它的值，否則會發生不可預期的錯誤
3. string在Java/C#與 char*在 c/c++ 差異在於，前者都是用new只會在heap memory，
   後者是還可以在 stack memory，例如 char* s[256] = "hello"，所以才會遇到 2的問題

*/


// sample 1.1
int g_num = 0;

void myCall_2(vector<char*>& v) {

	char str[2048];

	sprintf(str, "%d", g_num++);

	v.push_back(str);

}

void myCall_1(vector<char*>& v) {

	char str[2048];

	sprintf(str, "%d", g_num++);

	for(int i=0; i<3; i++)
		myCall_2(v);
}

void main()
{
	vector<char*> my_vector;

	myCall_1(my_vector);

	for (int i = 0; i < my_vector.size(); i++) {
		printf("path: %s\n", my_vector[i]);
	}
}

// sample 1.2
int g_num = 0;

void myCall_2(vector<int*>& v) {

	int str;

	str = g_num++;

	v.push_back(&str);

}

void myCall_1(vector<int*>& v) {

	for(int i=0; i<1; i++)
		myCall_2(v);
}

void main()
{
	vector<int*> my_vector;

	int x = 13;
	int* y = &x;
	printf("hahaha %d\n", *y);
	my_vector.push_back(y);

	for (int i = 0; i < my_vector.size(); i++) {
		printf("path: %d\n", *(my_vector[i]));
	}
}