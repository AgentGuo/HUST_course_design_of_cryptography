#include<iostream>
//#include<stack>
//#include<stdio.h>
#include "gmp.h"
#pragma comment(lib,"libgmp-10.lib")
//#define DEBUG 1
using namespace std;
mpz_t st[800];
unsigned long long t[32];
mpz_t R, k;
//stack<int> que;
void calInverse(mpz_t eInverse, mpz_t paraE, mpz_t paraN) {
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
void expmod(mpz_t a, mpz_t paraE, mpz_t n) {
	mpz_t e, eBack, aPow, temp;
	mpz_init_set(e, paraE);
	mpz_init_set(eBack, e);
	mpz_init_set(aPow, a);
	mpz_init(temp);


	//mpz_set_ui(a, 1);
	//
	//while (mpz_cmp_ui(eBack, 0) != 0) {
	//	mpz_mod_ui(temp, eBack, 2);
	//	mpz_div_ui(eBack, eBack, 2);
	//	if (mpz_cmp_ui(temp, 1) == 0) {
	//		que.push(1);
	//	}
	//	else {
	//		que.push(0);
	//	}
	//	//mpz_mod_ui(temp, eBack, 2);
	//	//mpz_div_ui(eBack, eBack, 2);
	//}
	//while (!que.empty()) {
	//	mpz_mul(a, a, a);
	//	if (que.top()) {
	//		mpz_mul(a, a, aPow);
	//	}
	//	mpz_mod(a, a, n);
	//	que.pop();
	//}

	mpz_set_ui(a, 1);
	mpz_mod_ui(temp, eBack, 2);	// 一些准备工作
	while (mpz_cmp_ui(eBack, 0) != 0) {		// 当还没被除完时
		if (mpz_cmp_ui(temp, 1) == 0) {		// 余数为1，则加上
			mpz_mul(a, a, aPow);
			mpz_mod(a, a, n);
		}
#ifdef DEBUG
		gmp_printf("a = %Zd\n", a);
		gmp_printf("temp = %Zd\n", temp);
		gmp_printf("aPow = %Zd\n", aPow);
		gmp_printf("eBack = %Zd\n", eBack);
#endif // DEBUG

		mpz_mul(aPow, aPow, aPow);		// 平方
		mpz_mod(aPow, aPow, n);
		mpz_div_ui(eBack, eBack, 2);
		mpz_mod_ui(temp, eBack, 2);		// 求余数
	}
}
void ChineseRemainderTheorem(mpz_t paraB1, mpz_t paraB2, mpz_t m1, mpz_t m2, mpz_t m1Inverse, mpz_t m2Inverse) {
	mpz_t b1, b2, m;
	mpz_init_set(b1, paraB1);
	mpz_init_set(b2, paraB2);
	mpz_init(m);
	mpz_mul(m, m1, m2);
	mpz_mul(b1, b1, m2);
	mpz_mul(b1, b1, m2Inverse);
	mpz_mul(b2, b2, m1);
	mpz_mul(b2, b2, m1Inverse);
	mpz_add(b1, b1, b2);
	mpz_mod(b1, b1, m);
	gmp_printf("%Zd\n", b1);
}
void MontMult(mpz_t T2, mpz_t A, mpz_t B, mpz_t IN, mpz_t N) {
	mpz_t T1, t0, temp;
	mpz_init(T1);
	mpz_init(t0);
	mpz_init(temp);
	mpz_mul(T1, A, B);
	for (int i = 0; i < 32; i++) {
		mpz_mod(t0, T1, k);
		mpz_mul(t0, t0, IN);
		mpz_addmul(T1, N, t0);
		mpz_mod(temp, T1, k);
		mpz_div(T1, T1, k);
	}
	mpz_mod(T1, T1, N);
	mpz_set(T2, T1);
}
int main() {
	int n, count;
	mpz_t e, m, p, q, b1, b2, B, B1, B2, d, two, dBack, phi, temp, pInverse, qInverse, pIN, qIN, RpInverse, RqInverse;
	for (int i = 0; i < 800; i++) {
		mpz_init(st[i]);
	}
	mpz_init(e);
	mpz_init(m);
	mpz_init(p);
	mpz_init(q);
	mpz_init(b1);
	mpz_init(b2);
	mpz_init(B);
	mpz_init(B1);
	mpz_init(B2);
	mpz_init(d);
	mpz_init(temp);
	mpz_init(phi);
	mpz_init(pInverse);
	mpz_init(qInverse);
	mpz_init(pIN);
	mpz_init(qIN);
	mpz_init(RpInverse);
	mpz_init(RqInverse);
	mpz_init(dBack);
	mpz_init_set_ui(two, 2);
	mpz_init(R);
	
	mpz_set_str(k, "4294967296", 10);
	mpz_set_str(R, "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137216", 10);
	gmp_scanf("%d%Zd%Zd%Zd", &n, p, q, e);
	mpz_mul(B, p, q);
	calInverse(pInverse, p, q);
	calInverse(qInverse, q, p);
	calInverse(RpInverse, R, p);
	calInverse(RqInverse, R, q);
	calInverse(pIN, p, k);
	mpz_sub(pIN, k, pIN);
	calInverse(qIN, q, k);
	mpz_sub(qIN, k, qIN);
	mpz_sub_ui(temp, p, 1);
	mpz_sub_ui(phi, q, 1);
	mpz_mul(phi, phi, temp);
	calInverse(d, e, phi);
	for (int i = 0; i < n; i++) {
		gmp_scanf("%Zd", m);

		mpz_set(B1, m);
		mpz_mul(B1, B1, R);
		mpz_mod(B1, B1, p);
		mpz_set(b1, R);
		mpz_mod(b1, b1, p);

		mpz_set(B2, m);
		mpz_mul(B2, B2, R);
		mpz_mod(B2, B2, q);
		mpz_set(b2, R);
		mpz_mod(b2, b2, q);

		mpz_set(dBack, d);
		while (mpz_cmp_ui(dBack, 0) != 0) {
			mpz_fdiv_qr(dBack, temp, dBack, two);
			if (mpz_cmp_ui(temp, 1) == 0) {
				MontMult(b1, b1, B1, pIN, p);
				MontMult(b2, b2, B2, qIN, q);
			}
			MontMult(B1, B1, B1, pIN, p);
			MontMult(B2, B2, B2, qIN, q);
		}

		mpz_mul(b1, b1, RpInverse);
		mpz_mod(b1, b1, p);
		mpz_mul(b2, b2, RqInverse);
		mpz_mod(b2, b2, q);

		mpz_mul(b1, b1, q);
		mpz_mod(b1, b1, B);
		mpz_mul(b1, b1, qInverse);
		mpz_mod(b1, b1, B);

		mpz_mul(b2, b2, p);
		mpz_mod(b2, b2, B);
		//mpz_addmul(b1, b2, pInverse);
		mpz_mul(b2, b2, pInverse);
		mpz_mod(b2, b2, B);

		mpz_add(b1, b1, b2);
		mpz_mod(b1, b1, B);
		gmp_printf("%Zd\n", b1);
		//ChineseRemainderTheorem(b1, b2, p, q, pInverse, qInverse);
	}
	return 0;
}