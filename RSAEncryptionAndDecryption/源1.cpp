#include <gmp.h>
#pragma comment(lib,"libgmp-10.lib")
#include <string.h>
//Square_and_Multiply(base,exponent,n)
inline void mod_exp(mpz_t result, const mpz_t exponent, const mpz_t base, const mpz_t n)  //不能改变传入的参数
{
    mpz_t _exponent;
    mpz_init_set(_exponent, exponent);
    char exp[2048 + 10] = { '\0' };
    mpz_get_str(exp, 2, _exponent);
    mpz_t power;
    mpz_init(power);
    mpz_set_ui(result, 1);  // z = 1
    mpz_mod(power, base, n); //power = base mod n 底数
    for (int i = strlen(exp) - 1; i >= 0; i--)
    {
        if (exp[i] == '1')
        {
            mpz_mul(result, result, power);
            mpz_mod(result, result, n);   //z = z * power mod n
        }
        mpz_mul(power, power, power);
        mpz_mod(power, power, n);  //power = power^2 mod n
    }
}

inline void inverse_mod_N(mpz_t a, mpz_t x, mpz_t N)    //ax=1(mod N)
{
    mpz_t q, t1, t2, t3, x1, x2, x3, y1, y2, y3, temp;
    mpz_init(q); mpz_init(t1); mpz_init(t2); mpz_init(t3); mpz_init(temp);
    mpz_init_set_ui(x1, 1); mpz_init_set_ui(x2, 0); mpz_init_set(x3, N);
    mpz_init_set_ui(y1, 0); mpz_init_set_ui(y2, 1); mpz_init_set(y3, a);

    while (mpz_cmp_ui(y3, 0) != 0)
    {
        mpz_fdiv_q(q, x3, y3);
        //mpz_divexact(q,x3,y3);
        mpz_mul(temp, q, y1);
        mpz_sub(t1, x1, temp);
        mpz_mul(temp, q, y2);
        mpz_sub(t2, x2, temp);
        mpz_mul(temp, q, y3);
        mpz_sub(t3, x3, temp);
        mpz_set(x1, y1);
        mpz_set(x2, y2);
        mpz_set(x3, y3);
        mpz_set(y1, t1);
        mpz_set(y2, t2);
        mpz_set(y3, t3);
    }

    if (mpz_cmp_ui(x2, 0) < 0)  //取正数
        mpz_add(x2, x2, N);
    mpz_set(x, x2);
}

inline void CRT(mpz_t C, mpz_t d, mpz_t p, mpz_t q, mpz_t PlainText, mpz_t inverse_p_mod_q, mpz_t inverse_q_mod_p, mpz_t d1, mpz_t d2, mpz_t N)   //求e=c^d(mod pq)
{
    mpz_t one, m1, m2, y1, y2;
    mpz_init(m1); mpz_init(m2); mpz_init(y1); mpz_init(y2);
    mpz_init_set_ui(one, 1);

    mod_exp(m1, d1, C, p);   //此处验证正确
    //mod_exp(m2, d2, C, q);
    //mpz_powm(m1, C, d1, p);
    mpz_powm(m2, C, d2, q);

    mpz_mul(y1, q, inverse_q_mod_p);
    mpz_mul(y2, p, inverse_p_mod_q);
    mpz_mul(m1, m1, y1);
    mpz_mul(m2, m2, y2);
    mpz_add(PlainText, m1, m2);
    mpz_mod(PlainText, PlainText, N);
}

int main()
{
    //freopen("1.in", "r", stdin);
    //freopen("1out.out", "w", stdout);
    int n;
    mpz_t e, d, p, q, m, Plaintext, _p, _q, phi_pq, N, inverse_p_mod_q, inverse_q_mod_p, d1, d2, b1, b2;
    mpz_init(e); mpz_init(p); mpz_init(q); mpz_init(m);
    mpz_init(Plaintext); mpz_init(d); mpz_init(_p);
    mpz_init(_q); mpz_init(phi_pq); mpz_init(N);
    mpz_init(inverse_p_mod_q);  mpz_init(inverse_q_mod_p);
    mpz_init(d1); mpz_init(d2);

    gmp_scanf("%d %Zd %Zd %Zd", &n, p, q, e);
    mpz_mul(N, p, q);
    mpz_sub_ui(_p, p, 1);
    mpz_sub_ui(_q, q, 1);
    mpz_mul(phi_pq, _p, _q);
    inverse_mod_N(e, d, phi_pq);
    inverse_mod_N(p, inverse_p_mod_q, q);
    inverse_mod_N(q, inverse_q_mod_p, p);
    mpz_mod(d1, d, _p);
    mpz_mod(d2, d, _q);

    while (n--)
    {
        gmp_scanf("%Zd", m);
        mpz_powm(b1, m, d1, p);
        mpz_powm(b2, m, d2, q);
        //mpz_mul(b1, b1, q);
        //mpz_mul(b1, b1, inverse_p_mod_q);
        //mpz_mul(b2, b2, p);
        //mpz_mul(b2, b2, inverse_q_mod_p);
        //mpz_add(b1, b1, b2);
        //mpz_mod(b1, b1, N);
        //gmp_printf("%Zd\n", b1);
    }


}

