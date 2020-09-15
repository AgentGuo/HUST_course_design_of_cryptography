#include<iostream>
#include<string.h>
using namespace std;
// S盒
short int substitution[2][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 }, {14, 3, 4, 8, 1, 12, 10, 15, 7, 13, 9, 6, 11, 2, 0, 5} };
//short int permutationList[16] = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
// 字段结构体
struct bit16 {
	unsigned short key16 : 1, key15 : 1, key14 : 1, key13 : 1,
		key12 : 1, key11 : 1, key10 : 1, key9 : 1,
		key8 : 1, key7 : 1, key6 : 1, key5 : 1,
		key4 : 1, key3 : 1, key2 : 1, key1 : 1;
};
struct bit4 {
	unsigned short key4 : 4, key3 : 4, key2 : 4, key1 : 4;
};
// 联合
union shortInt
{
	unsigned short num;
	bit16 numBit16;
	bit4 numBit4;
};
// P盒
void permutation(shortInt &after, int mode) {
	shortInt before = after;
	if (mode == 0) {
		after.numBit16.key2 = before.numBit16.key5;
		after.numBit16.key3 = before.numBit16.key9;
		after.numBit16.key4 = before.numBit16.key13;
		after.numBit16.key5 = before.numBit16.key2;
		after.numBit16.key6 = before.numBit16.key6;
		after.numBit16.key7 = before.numBit16.key10;
		after.numBit16.key8 = before.numBit16.key14;
		after.numBit16.key9 = before.numBit16.key3;
		after.numBit16.key10 = before.numBit16.key7;
		after.numBit16.key11 = before.numBit16.key11;
		after.numBit16.key12 = before.numBit16.key15;
		after.numBit16.key13 = before.numBit16.key4;
		after.numBit16.key14 = before.numBit16.key8;
		after.numBit16.key15 = before.numBit16.key12;
	}
	else {
		after.numBit16.key5 = before.numBit16.key2;
		after.numBit16.key9 = before.numBit16.key3;
		after.numBit16.key13 = before.numBit16.key4;
		after.numBit16.key2 = before.numBit16.key5;
		after.numBit16.key6 = before.numBit16.key6;
		after.numBit16.key10 = before.numBit16.key7;
		after.numBit16.key14 = before.numBit16.key8;
		after.numBit16.key3 = before.numBit16.key9;
		after.numBit16.key7 = before.numBit16.key10;
		after.numBit16.key11 = before.numBit16.key11;
		after.numBit16.key15 = before.numBit16.key12;
		after.numBit16.key4 = before.numBit16.key13;
		after.numBit16.key8 = before.numBit16.key14;
		after.numBit16.key12 = before.numBit16.key15;
	}
}
// SPN 参数说明：密钥， 明文， 模式（0：加密， 1：解密）
void SPN(shortInt k[5], shortInt &plaintext, int mode) {
	if (mode == 1) {
		for (int i = 1; i < 4; i++) {
			permutation(k[i], 1);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (mode == 1)
			plaintext.num ^= k[4 - i].num;
		else
			plaintext.num ^= k[i].num;
		plaintext.numBit4.key1 = substitution[mode][plaintext.numBit4.key1];
		plaintext.numBit4.key2 = substitution[mode][plaintext.numBit4.key2];
		plaintext.numBit4.key3 = substitution[mode][plaintext.numBit4.key3];
		plaintext.numBit4.key4 = substitution[mode][plaintext.numBit4.key4];
		permutation(plaintext, mode);
	}
	if(mode == 1)
		plaintext.num ^= k[1].num;
	else
		plaintext.num ^= k[3].num;
	plaintext.numBit4.key1 = substitution[mode][plaintext.numBit4.key1];
	plaintext.numBit4.key2 = substitution[mode][plaintext.numBit4.key2];
	plaintext.numBit4.key3 = substitution[mode][plaintext.numBit4.key3];
	plaintext.numBit4.key4 = substitution[mode][plaintext.numBit4.key4];

	if (mode == 1)
		plaintext.num ^= k[0].num;
	else
		plaintext.num ^= k[4].num;
	printf("%04x", plaintext.num);
}
int main()
{
	//ios::sync_with_stdio(false);
	int n;
	char c;
	unsigned short temp[8];
	shortInt k[5];
	shortInt plaintext;
	unsigned int temp1, temp2;
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		for (int i = 0; i < 8; i++) {
			temp[i] = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
		}
		for (int i = 0; i < 5; i++) {
			k[i].numBit4.key1 = temp[i];
			k[i].numBit4.key2 = temp[i+1];
			k[i].numBit4.key3 = temp[i+2];
			k[i].numBit4.key4 = temp[i+3];
		}
		getchar();
		plaintext.numBit4.key1 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
		plaintext.numBit4.key2 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
		plaintext.numBit4.key3 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
		plaintext.numBit4.key4 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
		getchar();
		//scanf("%x %x", &temp1, &temp2);
		//plaintext.num = temp2;
		//for (int i = 0; i < 5; i++) {
		//	k[4-i].num = temp1 & 0xffff;
		//	temp1 >>= 4;
		//}

		SPN(k, plaintext, 0);		// 加密
		printf(" ");
		plaintext.numBit16.key16 = ~(plaintext.numBit16.key16);		// 最后一位取反
		SPN(k, plaintext, 1);		// 解密
		printf("\n");
	}
	return 0;
}