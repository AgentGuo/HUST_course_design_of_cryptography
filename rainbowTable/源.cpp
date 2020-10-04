#include<iostream>
#include<string.h>
using namespace std;
void getstr(unsigned n, char str[8])
{
	str[0] = 'a'; str[1] = '0'; str[2] = '0'; str[3] = '0'; str[4] = '0'; str[5] = '0'; str[6] = '0'; str[7] = '0';
	int i = 2;
	while (n)
	{
		unsigned tmp = n % 36;
		if (tmp < 10)
			str[i++] = tmp + '0';
		else
		{
			str[i++] = tmp - 10 + 'a';
		}
		n = n / 36;
	}
}
inline void R(unsigned sha1[5], char str[8], int i)
{
	getstr((sha1[0] + sha1[1] * i) % 2176782336, str);
}
unsigned int SHA1_tmp;

#define SHA1_ROTL(a,b) (SHA1_tmp=(a),((SHA1_tmp>>(32-b))&(0x7fffffff>>(31-b)))|(SHA1_tmp<<b))

#define SHA1_F(B,C,D,t) ((t<40)?((t<20)?((B&C)|((~B)&D)):(B^C^D)):((t<60)?((B&C)|(B&D)|(C&D)):(B^C^D)))

inline int UnitSHA1(const char* str, int length, unsigned sha1[5]) {
	/*
	计算字符串SHA-1
	参数说明：
	str         字符串指针
	length      字符串长度
	sha1         用于保存SHA-1的字符串指针
	返回值为参数sha1
	*/
	unsigned char* pp, * ppend;
	unsigned int l, i, K[80], W[80], TEMP, A, B, C, D, E, H0, H1, H2, H3, H4;
	H0 = 0x67452301, H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0;
	for (i = 0; i < 20; K[i++] = 0x5A827999);
	for (i = 20; i < 40; K[i++] = 0x6ED9EBA1);
	for (i = 40; i < 60; K[i++] = 0x8F1BBCDC);
	for (i = 60; i < 80; K[i++] = 0xCA62C1D6);
	l = length + ((length % 64 > 56) ? (128 - length % 64) : (64 - length % 64));
	if (!(pp = (unsigned char*)malloc((unsigned int)l))) return -1;
	for (i = 0; i < length; pp[i + 3 - 2 * (i % 4)] = str[i], i++);
	for (pp[i + 3 - 2 * (i % 4)] = 128, i++; i < l; pp[i + 3 - 2 * (i % 4)] = 0, i++);
	*((unsigned int*)(pp + l - 4)) = length << 3;
	*((unsigned int*)(pp + l - 8)) = length >> 29;
	for (ppend = pp + l; pp < ppend; pp += 64) {
		for (i = 0; i < 16; W[i] = ((unsigned int*)pp)[i], i++);
		for (i = 16; i < 80; W[i] = SHA1_ROTL((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]), 1), i++);
		A = H0, B = H1, C = H2, D = H3, E = H4;
		for (i = 0; i < 80; i++) {
			TEMP = SHA1_ROTL(A, 5) + SHA1_F(B, C, D, i) + E + W[i] + K[i];
			E = D, D = C, C = SHA1_ROTL(B, 30), B = A, A = TEMP;
		}
		H0 += A, H1 += B, H2 += C, H3 += D, H4 += E;
	}
	free(pp - l);
	sha1[0] = H0, sha1[1] = H1, sha1[2] = H2, sha1[3] = H3, sha1[4] = H4;
	return 0;
}
char startStr[10000][9] = { 0 }, endStr[10000][9] = { 0 };
int m;
bool findStr(char str[9], unsigned sha1[5]) {
	int k = 0;
	unsigned sha1Temp[5];
	char strTemp[9];
	for (int i = 0; i < m; i++) {
		if (strcmp(str, endStr[i]) == 0) {
			//cout << endStr[i] << endl;
			strcpy(strTemp, startStr[i]);
			for (int j = 0; j < 100000; j++) {
				UnitSHA1(strTemp, 8, sha1Temp);		// 得到sha1
				for (k = 0; k < 5; k++) {
					if (sha1Temp[k] != sha1[k]) {
						break;
					}
				}
				if (k == 5) {
					strcpy(str, strTemp);
					return true;
				}
				R(sha1Temp, strTemp, j % 100 + 1);	// 得到str
			}
		}
	}
	return false;
}
int main() {
	//freopen("1.in", "r", stdin);
	bool findFlag = false;
	unsigned sha1[5], sha1Temp[5];// = { 0x0f78779a , 0x24c55d7b, 0x6a10faad, 0x18f55ad3, 0x8023016f };
	char str[9] = { 0 };
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%s%s", startStr[i], endStr[i]);
		//cin >> startStr[i] >> endStr[i];
	}
	scanf("%8x%8x%8x%8x%8x", &(sha1[0]), &(sha1[1]), &(sha1[2]), &(sha1[3]), &(sha1[4]));
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 5; j++)
			sha1Temp[j] = sha1[j];
		for (int j = 0; j < (i <= 1?100000:10000); j++) {
			R(sha1Temp, str, (i + j) % 100 + 1);	// 得到str
			findFlag = findStr(str, sha1);
			if (findFlag)
				break;
			UnitSHA1(str, 8, sha1Temp);		// 得到sha1
		}
		if (findFlag)
			break;
	}
	if (findFlag) {
		printf("%s\n", str);
	}
	else {
		printf("None\n");
	}
	//cin >> str;
	//for (int i = 0; i < 100000; i++) {
	//	UnitSHA1(str, 8, sha1);		// 得到sha1
	//	R(sha1, str, i%100 + 1);	// 得到str
	//}
	return 0;
}