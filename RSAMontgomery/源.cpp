#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include "gmp.h"
#pragma comment(lib,"libgmp-10.lib")
//#define DEBUG 1
using namespace std;
mpz_t st[800];
char str1[1100], str2[1100];
mpz_t R1, R2, k;
mp_limb_t T1[64];
mp_limb_t t0_in[4];
mp_limb_t carry;
//stack<int> que;
void calInverse(mpz_t eInverse, mpz_t paraE, mpz_t paraN) {
	// 使用辗转相除法求逆
	int count = -1;
	mpz_t n, temp, temp1, temp2, e;
	mpz_init_set(e, paraE);
	mpz_init_set(n, paraN);
	mpz_init(temp);
	mpz_init(temp1);
	mpz_init(temp2);
	//mpz_init_set_ui(temp, 0);
	//mpz_sub(n, temp, n);
	mpz_neg(n, n);
	// 求解e的逆
	//mpz_mod(temp, e, n);
	//mpz_sub(temp1, e, temp);
	//mpz_div(temp1, temp1, n);
	mpz_tdiv_qr(temp1, temp, e, n);
	mpz_set(st[0], temp1);
	while (mpz_cmp_ui(temp, 0) != 0) {
		count++;
		mpz_set(st[count], temp1);
		mpz_set(e, n);
		mpz_set(n, temp);
		mpz_tdiv_qr(temp1, temp, e, n);
		//mpz_mod(temp, e, n);
		//mpz_sub(temp1, e, temp);
		//mpz_div(temp1, temp1, n);
	}
	mpz_mul(temp, temp1, e);
	mpz_set_ui(temp2, 1);
	if (mpz_cmp_ui(temp, 0) < 0)
		mpz_neg(temp2, temp2);
	mpz_set_ui(temp1, 0);

	mpz_sub(n, temp1, n);
	for (int i = count; i >= 0; i--) {
		mpz_init_set(temp, temp2);
		mpz_mul(temp2, temp2, st[i]);
		mpz_sub(temp2, temp1, temp2);
		mpz_set(temp1, temp);
	}
	//gmp_printf("%Zd\n", temp1);
	mpz_set(eInverse, temp1);
	mpz_mod(eInverse, eInverse, paraN);
}
void MontMult(int n,  mpz_t T, mp_limb_t IN, mpz_t N) {
	// 蒙哥马利乘 第层加速版本
	mp_limb_t* pos = T1;
	int T_size = T->_mp_size;
	memcpy(T1, T->_mp_d, T_size * 8);
	memset(T1 + T_size, 0, ((n << 1) + 1 - T_size) * 8);
	int high_size = n + 1;
	for (int i = 0; i < n; i++) {
		mpn_mul_1(t0_in, pos, 1, IN);
		carry = mpn_addmul_1(pos, N->_mp_d, n, t0_in[0]);
		mpn_add_1(pos + n, pos + n, high_size, carry);
		++pos;
		--high_size;
	}
	if (mpn_cmp(pos, N->_mp_d, n) >= 0 || pos[n])
		mpn_sub(pos, pos, n + 1, N->_mp_d, n);
	//pos[n] &= 1;
	memcpy(T->_mp_d, pos, n * 8);
	T->_mp_size = n;
}
int main() {
	//freopen("1.in", "r", stdin);
	int n, length1, length2;
	mpz_t e, m, p, q, _p, _q, d1, d2, b1, b2, B, B1, B2, d, two, dBack, phi, temp, pInverse, qInverse, pIN, qIN, RpInverse, RqInverse;
	for (int i = 0; i < 800; i++) {
		mpz_init(st[i]);
	}
	mpz_init(e);mpz_init(m);mpz_init(p);mpz_init(q);mpz_init(_p);mpz_init(_q);mpz_init(b1);
	mpz_init(b2);mpz_init(B);mpz_init(B1);mpz_init(B2);mpz_init(d);mpz_init(d1);mpz_init(d2);
	mpz_init(temp);mpz_init(phi);mpz_init(pInverse);mpz_init(qInverse);mpz_init(pIN);mpz_init(qIN);
	mpz_init(RpInverse);mpz_init(RqInverse);mpz_init(dBack);mpz_init_set_ui(two, 2);mpz_init(R1);
	mpz_init(R2);

	mpz_set_str(k, "18446744073709551616", 10);		// 2^64
	gmp_scanf("%d%Zd%Zd%Zd", &n, p, q, e);

	mpz_set(R1, k);
	length1 = 1;
	while (mpz_cmp(R1, p) <= 0) {		//	 对p,q分别求出R
		mpz_mul(R1, R1, k);
		length1++;
	}
	mpz_set(R2, k);
	length2 = 1;
	while (mpz_cmp(R2, q) <= 0) {
		mpz_mul(R2, R2, k);
		length2++;
	}


	mpz_mul(B, p, q);
	calInverse(pInverse, p, q);		// 中国剩余定理需要用到的逆
	calInverse(qInverse, q, p);
	calInverse(RpInverse, R1, p);	// 蒙哥马利R的逆
	calInverse(RqInverse, R2, q);
	calInverse(pIN, p, k);			// 负逆IN
	mpz_sub(pIN, k, pIN);
	calInverse(qIN, q, k);
	mpz_sub(qIN, k, qIN);
	mpz_sub_ui(_p, p, 1);
	mpz_sub_ui(_q, q, 1);
	mpz_mul(phi, _p, _q);
	calInverse(d, e, phi);			// 求出解密指数d
	mpz_mod(d1, d, _p);				// 解密指数分别模除p-1和q-1，中国剩余定理加速
	mpz_mod(d2, d, _q);
	mpz_get_str(str1, 2, d1);		// 将解密指数转化位字符串，加速计算
	mpz_get_str(str2, 2, d2);

	for (int i = 0; i < n; i++) {
		gmp_scanf("%Zd", m);		// 输入m
		mpz_set(B1, m);				// 转化位蒙哥马利数
		mpz_mul(B1, B1, R1);
		mpz_mod(B1, B1, p);
		mpz_set(b1, R1);
		mpz_mod(b1, b1, p);

		mpz_set(B2, m);
		mpz_mul(B2, B2, R2);
		mpz_mod(B2, B2, q);
		mpz_set(b2, R2);
		mpz_mod(b2, b2, q);


		for (int i = 0; str1[i] != '\0'; i++) {		// 循环计算蒙哥马利乘
			mpz_mul(b1, b1, b1);
			MontMult(length1, b1, pIN->_mp_d[0], p);
			if (str1[i] == '1') {
				mpz_mul(b1, b1, B1);
				MontMult(length1, b1, pIN->_mp_d[0], p);
			}
		}
		for (int i = 0; str2[i] != '\0'; i++) {
			mpz_mul(b2, b2, b2);
			MontMult(length2, b2, qIN->_mp_d[0], q);
			if (str2[i] == '1') {
				mpz_mul(b2, b2, B2);
				MontMult(length2, b2, qIN->_mp_d[0], q);
			}
		}

		mpz_mul(b1, b1, RpInverse);		// 计算蒙哥马利逆
		mpz_mod(b1, b1, p);
		mpz_mul(b2, b2, RqInverse);
		mpz_mod(b2, b2, q);

		mpz_mul(b1, b1, q);				// 使用中国剩余定理计算最终结果
		mpz_mod(b1, b1, B);
		mpz_mul(b1, b1, qInverse);
		mpz_mod(b1, b1, B);

		mpz_mul(b2, b2, p);
		mpz_mod(b2, b2, B);
		mpz_mul(b2, b2, pInverse);
		mpz_mod(b2, b2, B);

		mpz_add(b1, b1, b2);
		mpz_mod(b1, b1, B);
		gmp_printf("%Zd\n", b1);
	}
	return 0;
}