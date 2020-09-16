#include <gmp.h>
#include <stdio.h>
using namespace std;
//#define DEBUG 1
bool isPrime(mpz_t paraN){
        int count = 0;
        gmp_randstate_t state;
        gmp_randinit_mt(state);
        mpz_t b, t, temp, a, n;
        mpz_init(b);
        mpz_init(n);
        mpz_init(a);
        mpz_init(t);
        mpz_init(temp);
        mpz_init_set(n, paraN);
        mpz_set(t, n);
        mpz_sub_ui(t,t,1);
        mpz_mod_ui(b, t, 2);
        while(mpz_cmp_ui(b, 0) == 0){           //  求解t
                mpz_div_ui(t, t, 2);
                mpz_mod_ui(b, t, 2);
                count++;
        }
        mpz_sub_ui(t,n,1);
        if(count == 0){
                return false;           // 偶数直接排除
        }
        for(int i = 0; i < 200; i++){
                //mpz_init_set_ui(a, 4);
                mpz_urandomm(a, state, n);              // 随机选择a
                if(mpz_cmp_ui(a, 0) != 0 && mpz_cmp_ui(a, 1) != 0){
                        mpz_powm(temp, a, t, n);
                        if(mpz_cmp_ui(temp, 1) == 0){           //  是素数
                                return true;
                        }
                        for(int j = 0; j < count; j++){
                                if(mpz_cmp(temp, t) == 0){          // 是素数
                                        return true;
                                }
                                mpz_powm_ui(temp, temp, 2, n);
                        }
                }
        }
        //gmp_printf("%Zd\n",n);
        return false;           // 不是素数
}
bool gcdIsOne(mpz_t paraA, mpz_t paraB){
        mpz_t temp, a, b;
        mpz_init(temp);
        mpz_init(a);
        mpz_init(b);
        mpz_init_set(a, paraA);
        mpz_init_set(b, paraB);
        mpz_mod(temp, a, b);
        while(mpz_cmp_ui(temp, 0) != 0){
                mpz_init_set(a, b);
                mpz_init_set(b, temp);
                mpz_mod(temp, a, b);
        }
        #ifdef DEBUG
        gmp_printf("gcd = %Zd\n",b);
        #endif
        
        if(mpz_cmp_ui(b, 1) == 0){
                return true;
        }
        else{
                return false;
        }
}
void calD(mpz_t e, mpz_t p, mpz_t q){
        mpz_t st[300];
        int count = -1;
        for(int i = 0; i < 100; i++){
                mpz_init(st[i]);
        }
        mpz_t phi, temp, temp1, temp2;
        mpz_init(phi);
        mpz_init(temp);
        mpz_init(temp1);
        mpz_init(temp2);
        mpz_sub(temp, p, q);
        mpz_div_ui(temp1, p, 10);
        mpz_abs(temp, temp);
        if(mpz_cmp_ui(e, 10) < 0){              // e过小
                printf("ERROR\n");
                return;
        }
        if(!(isPrime(p) && isPrime(q))){                // p, q不是素数
                printf("ERROR\n");
                return;
        }
        #ifdef DEBUG
        gmp_printf("p = %Zd\n", p);
        gmp_printf("q = %Zd\n", q);
        gmp_printf("temp = %Zd\n", temp);
        #endif
        if(mpz_cmp(temp, temp1) < 0){              // p,q差值过小
                printf("ERROR\n");
                return;
        }
        mpz_sub_ui(p, p, 1);
        mpz_sub_ui(q, q, 1);
        mpz_mul(phi, p, q);
        mpz_init_set_ui(temp, 0);
        mpz_sub(phi, temp, phi);
        #ifdef DEBUG
        gmp_printf("phi = %Zd\n", phi);
        #endif
        if(!gcdIsOne(e, phi)){          // e和phi不互素
                printf("ERROR\n");
                return;
        }
        // 求解d
        mpz_mod(temp, e, phi);
        mpz_sub(temp1, e, temp);
        mpz_div(temp1, temp1, phi);
        mpz_init_set(st[0], temp1);
        while(mpz_cmp_ui(temp, 0) != 0){
                #ifdef DEBUG
                gmp_printf("e = %Zd\n", e);
                gmp_printf("phi = %Zd\n", phi);
                gmp_printf("temp = %Zd\n", temp);
                gmp_printf("temp1 = %Zd\n", temp1);
                #endif
                count++;
                mpz_init_set(st[count], temp1);
                mpz_init_set(e, phi);
                mpz_init_set(phi, temp);
                mpz_mod(temp, e, phi);
                mpz_sub(temp1, e, temp);
                mpz_div(temp1, temp1, phi);
        }
        mpz_init_set_ui(temp1, 0);
        mpz_init_set_ui(temp2, 1);
        mpz_sub(phi, temp1, phi);
        for(int i = count; i >= 0; i--){
                mpz_init_set(temp, temp2);
                mpz_mul(temp2, temp2, st[i]);
                mpz_sub(temp2, temp1, temp2);
                mpz_init_set(temp1, temp);
                #ifdef DEBUG
                gmp_printf("temp1 = %Zd\n", temp1);
                gmp_printf("temp2 = %Zd\n", temp2);
                #endif
        }
        gmp_printf("%Zd\n",temp1);
}
int main()
{
        int n;
        //freopen("1.in", "r", stdin);
        mpz_t e,p,q;
        mpz_init(e);
        mpz_init(p);
        mpz_init(q);
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
                gmp_scanf("%Zd%Zd%Zd",e,p,q);
                calD(e, p, q);
        }
        return 0;
}