#include <gmp.h>
#include<stack>
#include <iostream>
#include <stdio.h>
using namespace std;
#define DEBUG 1
bool isPrime(mpz_t n){
        int count = 0;
        gmp_randstate_t state;
        gmp_randinit_mt(state);
        mpz_t b, t, temp, a;
        mpz_init(b);
        mpz_init(a);
        mpz_init(t);
        mpz_init(temp);
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
        gmp_printf("b=%Zd\n",b);
        gmp_printf("t=%Zd\n",t);
        for(int i = 0; i < 100; i++){
                //mpz_init_set_ui(a, 4);
                mpz_urandomm(a, state, n);              // 随机选择a
                gmp_printf("a=%Zd\n",a);
                if(mpz_cmp_ui(a, 0) != 0 && mpz_cmp_ui(a, 1) != 0){
                        mpz_powm(temp, a, t, n);
                        gmp_printf("temp=%Zd\n",temp);
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
bool gcdIsOne(mpz_t a, mpz_t b){
        mpz_t temp;
        mpz_init(temp);
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
        stack<mpz_t> q;
        mpz_t phi, temp;
        mpz_init(phi);
        mpz_init(temp);
        mpz_sub(temp, p, q);
        mpz_abs(temp, temp);
        if(!(isPrime(p) && isPrime(q))){                // p, q不是素数
                printf("ERROR");
                return;
        }
        if(mpz_cmp_ui(temp, 100) < 0){              // p,q差值过小
                printf("ERROR");
                return;
        }
        mpz_sub_ui(p, p, 1);
        mpz_sub_ui(q, q, 1);
        mpz_mul(phi, p, q);
        if(!gcdIsOne(e, phi)){          // e和phi不互素
                printf("ERROR");
                return;
        }
        // 求解d
        mpz_t temp;
        mpz_init(temp);
        mpz_mod(temp, a, b);
        while(mpz_cmp_ui(temp, 0) != 0){
                mpz_init_set(a, b);
                mpz_init_set(b, temp);
                mpz_mod(temp, a, b);
        }
}
int main()
{
        int n;
        mpz_t e,p,q;
        mpz_init(e);
        mpz_init(p);
        mpz_init(q);
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
                // gmp_scanf("%Zd%Zd%Zd",e,p,q);
                //gmp_scanf("%Zd",p);
                gmp_scanf("%Zd%Zd",p,q);
                if(gcdIsOne(p,q)){
                        cout<<"yes"<<endl;
                }
                else{
                        cout<<"No"<<endl;
                }
                // if(isPrime(p) && isPrime(q)){
                //         cout<<"prime"<<endl;
                // }
                // else{
                //         cout<<"ERROR"<<endl;
                // }
        }
        // mpz_add(c,a,b);
        // gmp_printf("c= %Zd\n",c);
        return 0;
}