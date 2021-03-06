#include<iostream>
#include "gmp.h"
#pragma comment(lib,"libgmp-10.lib")
//#define DEBUG 1
void calInverse(mpz_t eInverse, mpz_t paraE, mpz_t paraN) {
    mpz_t st[5000];
    int count = -1;
    for (int i = 0; i < 5000; i++) {
        mpz_init(st[i]);
    }
    mpz_t n, temp, temp1, temp2, e;
    mpz_init_set(e, paraE);
    mpz_init_set(n, paraN);
    mpz_init(temp);
    mpz_init(temp1);
    mpz_init(temp2);
    mpz_init_set_ui(temp, 0);
    mpz_sub(n, temp, n);
    // 求解e的逆
    mpz_mod(temp, e, n);
    mpz_sub(temp1, e, temp);
    mpz_div(temp1, temp1, n);
    mpz_init_set(st[0], temp1);
    while (mpz_cmp_ui(temp, 0) != 0) {
        count++;
        mpz_init_set(st[count], temp1);
        mpz_init_set(e, n);
        mpz_init_set(n, temp);
        mpz_mod(temp, e, n);
        mpz_sub(temp1, e, temp);
        mpz_div(temp1, temp1, n);
    }
    mpz_init_set_ui(temp1, 0);
    mpz_init_set_ui(temp2, 1);
    mpz_sub(n, temp1, n);
    for (int i = count; i >= 0; i--) {
        mpz_init_set(temp, temp2);
        mpz_mul(temp2, temp2, st[i]);
        mpz_sub(temp2, temp1, temp2);
        mpz_init_set(temp1, temp);
    }
    //gmp_printf("%Zd\n", temp1);
	mpz_set(eInverse, temp1);
}
void expmod(mpz_t a, mpz_t paraE, mpz_t paraN) {
	mpz_t e, n, eBack, aPow,temp;
	mpz_init_set(e, paraE);
	mpz_init_set(n, paraN);
	mpz_init_set(eBack, e);
	mpz_init_set(aPow, a);
	mpz_init(temp);
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
void ChineseRemainderTheorem(mpz_t paraB1, mpz_t paraB2, mpz_t paraM1, mpz_t paraM2) {
	mpz_t b1, b2, m1, m2, m, m1Inverse, m2Inverse;
	mpz_init_set(b1, paraB1);
	mpz_init_set(b2, paraB2);
	mpz_init_set(m1, paraM1);
	mpz_init_set(m2, paraM2);
	mpz_init(m1Inverse);
	mpz_init(m2Inverse);
	mpz_init(m);
	mpz_mul(m, m1, m2);
	calInverse(m1Inverse, m1, m2);
	calInverse(m2Inverse, m2, m1);
	mpz_mul(b1, b1, m2);
	mpz_mul(b1, b1, m2Inverse);
	mpz_mul(b2, b2, m1);
	mpz_mul(b2, b2, m1Inverse);
	mpz_add(b1, b1, b2);
	mpz_mod(b1, b1, m);
	gmp_printf("%Zd\n", b1);
}
using namespace std;
int main() {
	int n;
	mpz_t e, m, p, q, b1, b2;
	mpz_init(e);
	mpz_init(m);
	mpz_init(p);
	mpz_init(q);
	mpz_init(b1);
	mpz_init(b2);
	cin >> n;
	for (int i = 0; i < n; i++) {
		gmp_scanf("%Zd%Zd%Zd%Zd", e, m, p, q);
		mpz_set(b1, m);
		mpz_set(b2, m);
		expmod(b1, e, p);
		expmod(b2, e, q);
		//mpz_set_ui(b1, 1);
		//mpz_set_ui(b2, 2);
		//mpz_set_ui(p, 6);
		//mpz_set_ui(q, 35);
		ChineseRemainderTheorem(b1, b2, p, q);
		//gmp_printf("after mod: %Zd\n", e);
	}
	return 0;
}