#include<stdio.h>
#include<string.h>
#include<map>
#include<algorithm>
#include<iterator>
//#include<iostream>
using namespace std;
short int substitution[2][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 }, {14, 3, 4, 8, 1, 12, 10, 15, 7, 13, 9, 6, 11, 2, 0, 5} };
struct bit16 {
	unsigned short key16 : 1, key15 : 1, key14 : 1, key13 : 1,
		key12 : 1, key11 : 1, key10 : 1, key9 : 1,
		key8 : 1, key7 : 1, key6 : 1, key5 : 1,
		key4 : 1, key3 : 1, key2 : 1, key1 : 1;
};
struct bit4 {
	unsigned short key4 : 4, key3 : 4, key2 : 4, key1 : 4;
};
union shortInt
{
	unsigned short num;
	bit16 numBit16;
	bit4 numBit4;
};
void permutation(shortInt& after, int mode) {
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
bool SPN(shortInt k[5], shortInt plaintext, shortInt ciphertext, int mode) {
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
	if (mode == 1)
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
	return (plaintext.num == ciphertext.num);
}
inline unsigned short read()//inline 加速读入
{
	unsigned short x = 0;
	char c = getchar();//x代表返回值，c代表读取的字符
	while (c != ' ' && c != '\n') {
		x = x * 16 + ((c >= 'a') ? (c - 'a' + 10) : (c - '0'));
		c = getchar();
	}
	return x;
}
int main()
{
	//ios::sync_with_stdio(false);
	int n, key, times, maxNum[2], lastKey2;
	pair<int, int> count1[256], count2[256];
	char c;
	shortInt kHead, plaintext[8000], ciphertext[8000], temp, test, k[5], ktest;
	//freopen("2.in", "r", stdin);
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		lastKey2 = -1;
		fill(count1, count1+256, pair<int, int>(-4000, 0));
		for (int j = 0; j < 8000; j++) {
			plaintext[j].num = read();
			ciphertext[j].num = read();
			//plaintext[j].numBit4.key1 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//plaintext[j].numBit4.key2 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//plaintext[j].numBit4.key3 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//plaintext[j].numBit4.key4 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//getchar();
			//ciphertext[j].numBit4.key1 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//ciphertext[j].numBit4.key2 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//ciphertext[j].numBit4.key3 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//ciphertext[j].numBit4.key4 = (((c = getchar()) >= 'a') ? (c - 'a' + 10) : (c - '0'));
			//getchar();
		}
		// 计算第一条链
		for (int j = 0; j < 8000; j++) {
			k[4].numBit4.key2 = 0;
			while (1) {
				k[4].numBit4.key4 = 0;
				while (1) {
					temp.numBit4.key2 = ciphertext[j].numBit4.key2 ^ k[4].numBit4.key2;
					temp.numBit4.key4 = ciphertext[j].numBit4.key4 ^ k[4].numBit4.key4;
					temp.numBit4.key2 = substitution[1][temp.numBit4.key2];
					temp.numBit4.key4 = substitution[1][temp.numBit4.key4];
					if ((plaintext[j].numBit16.key5 ^ plaintext[j].numBit16.key7 ^ plaintext[j].numBit16.key8 ^
						temp.numBit16.key6 ^ temp.numBit16.key8 ^ temp.numBit16.key14 ^ temp.numBit16.key16) == 0)
						count1[k[4].numBit4.key2 * 16 + k[4].numBit4.key4].first ++;
					if (k[4].numBit4.key4 == 15)
						break;
					k[4].numBit4.key4++;
				}
				if (k[4].numBit4.key2 == 15)
					break;
				k[4].numBit4.key2++;
			}
		} 
		// 得到部分密钥
		for (int j = 0; j < 256; j++) {
			count1[j].second = j;
			count1[j].first = abs(count1[j].first);
		}
		sort(count1, count1+256);

		for(int j = 255; j >= 0; j--) {
			lastKey2 = k[4].numBit4.key2;
			k[4].numBit4.key2 = count1[j].second / 16;
			k[4].numBit4.key4 = count1[j].second % 16;

			// 计算第二条链
			if (j == 255 || lastKey2 != k[4].numBit4.key2) {
				fill(count2, count2 + 256, pair<int, int>(-4000, 0));
				for (int j = 0; j < 8000; j++) {
					k[4].numBit4.key1 = 0;
					while (1) {
						k[4].numBit4.key3 = 0;
						while (1) {
							temp.numBit4.key1 = ciphertext[j].numBit4.key1 ^ k[4].numBit4.key1;
							temp.numBit4.key2 = ciphertext[j].numBit4.key2 ^ k[4].numBit4.key2;
							temp.numBit4.key3 = ciphertext[j].numBit4.key3 ^ k[4].numBit4.key3;
							temp.numBit4.key1 = substitution[1][temp.numBit4.key1];
							temp.numBit4.key2 = substitution[1][temp.numBit4.key2];
							temp.numBit4.key3 = substitution[1][temp.numBit4.key3];
							if ((plaintext[j].numBit16.key5 ^ plaintext[j].numBit16.key6
								^ temp.numBit16.key2 ^ temp.numBit16.key4 ^ temp.numBit16.key6 ^ temp.numBit16.key8 ^ temp.numBit16.key10 ^ temp.numBit16.key12) == 0)
								count2[k[4].numBit4.key1 * 16 + k[4].numBit4.key3].first++;
							if (k[4].numBit4.key3 == 15)
								break;
							k[4].numBit4.key3++;
						}
						if (k[4].numBit4.key1 == 15)
							break;
						k[4].numBit4.key1++;
					}
				}
				for (int j = 0; j < 256; j++) {
					count2[j].second = j;
					count2[j].first = abs(count2[j].first);
				}
				sort(count2, count2 + 256);
			}

			for (int h = 255; h >= 254; h--) {
				k[4].numBit4.key1 = count2[h].second / 16;
				k[4].numBit4.key3 = count2[h].second % 16;
				kHead.num = 0;
				while (1) {
					k[0] = kHead;
					k[1].num = ((k[0].num & 0x0fff)<<4) | ((k[4].num & 0xf000)>>12);
					k[2].num = ((k[0].num & 0x00ff)<<8) | ((k[4].num & 0xff00)>>8);
					k[3].num = ((k[0].num & 0x000f)<<12) | ((k[4].num & 0xfff0)>>4);
					for (times = 0; times < 2; times++) {
						if (!SPN(k, plaintext[times], ciphertext[times], 0))
							break;
					}
					if (times == 2) {
						printf("%04x%04x\n", k[0].num, k[4].num);
						break;
					}
					if (kHead.num == 65535)
						break;
					kHead.num++;
				}
				if (times == 2)
					break;
			}
			if (times == 2)
				break;
		}
	}
	return 0;
}