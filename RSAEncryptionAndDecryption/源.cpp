#include<iostream>
#include<stack>
#include<string.h>
#include "gmp.h"
#pragma comment(lib,"libgmp-10.lib")
mpz_t st[800];
char str[1000];
void calInverse(mpz_t eInverse, mpz_t paraE, mpz_t paraN) {
	// ʹ��շת���������
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
	// ���e����
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
	if(mpz_cmp_ui(temp, 0) < 0)
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
inline void expmod(mpz_t a, mpz_t paraE, mpz_t n) {
	// ƽ�����㷨
	int i = 0;
	mpz_t aBack;
	mpz_init_set(aBack, a);
	mpz_get_str(str, 2, paraE);		// ����ת��Ϊ�������ַ�������������
	mpz_set_ui(a, 1);
	while (str[i] != '\0') {		// ʹ��ƽ�����㷨
		mpz_mul(a, a, a);
		mpz_mod(a, a, n);
		if (str[i] == '1') {
			mpz_mul(a, a, aBack);
			mpz_mod(a, a, n);
		}
		i++;
	}
}

int main() {
	int n;
	mpz_t e, m, p, q, b1, b2, B, d, phi, temp, pInverse, qInverse, _p, _q, d1, d2;
	for (int i = 0; i < 800; i++) {
		mpz_init(st[i]);
	}
	// ��ʼ��һ����
	mpz_init(e);mpz_init(m);mpz_init(p);mpz_init(q);mpz_init(b1);mpz_init(b2);
	mpz_init(B);mpz_init(d);mpz_init(temp);mpz_init(phi);mpz_init(pInverse);
	mpz_init(qInverse);mpz_init(_p);mpz_init(_q);mpz_init(d1);mpz_init(d2);
	gmp_scanf("%d%Zd%Zd%Zd",&n , p, q, e);
	calInverse(pInverse, p, q);		// �����й�ʣ�ඨ����Ҫ�õ�����
	calInverse(qInverse, q, p);
	mpz_mul(B, p, q);		// ����p q֮��
	mpz_sub_ui(_p, p, 1);	// ����p-1��q-1
	mpz_sub_ui(_q, q, 1);
	mpz_mul(phi, _p, _q);
	calInverse(d, e, phi);	// ����d����e
	mpz_mod(d1, d, _p);		// ʹ���й�ʣ�ඨ���ֱ�dģ��p-1��q-1
	mpz_mod(d2, d, _q);
	while (n--) {
		gmp_scanf("%Zd", m);
		mpz_set(b1, m);
		mpz_set(b2, m);
		expmod(b1, d1, p);		// �ֱ����m^d1��m^d2
		expmod(b2, d2, q);


		mpz_mul(b1, b1, q);		// �����й�ʣ�ඨ�����
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