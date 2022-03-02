#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ratio.h"

#define a1 545140134.0
#define a2 13591409.0
#define a3 -262537412640768000.0
//#define a4 (426880 * sqrt(10005)) // 100.0248

typedef __int128_t int128;
typedef __uint128_t uint128;

static const uint128 UINT128_MAX = (uint128)((int128)-1);
static const int128 INT128_MAX = UINT128_MAX >> 1;
static const int128 INT128_MIN = -INT128_MAX - 1;

int128 fib(int128 f, int128* r){ // doing this so i can save one number behind
	int128 a = 1,b = 1,c;
	if(f == 0) return 1;
	
	while(f){
		c = a + b;
		a = b;
		b = c;
		f--;
	}
	*r = a;
	return b;
}

ratio fibr(int128 f){
	int128 r = 0;
	int128 t = fib(f,&r);
	
	return (ratio){t,r};
}

int128 factorial(int128 n) {
    if (n == 0) return 1;
    return factorial(n - 1) * n;
}

ratio factr(int128 n){
    return (ratio){factorial(n),1};
}

ratio pi(uint k){
	const ratio r1 = {a1,1};
	const ratio r3 = {a3,1};

	ratio C = {8582422400,201}; // commented a4
	ratio X = {1,1};
	ratio L = {a2,1};
	ratio sum = L;
	ratio M = {0,0};
	
	ratio i = {1,1};
	for(; i.a <= k;i.a++){
		M = divr( factr(6*i.a), mulr( factr(3*i.a), powr(factr(i.a),3 ) ) );
		reduce(M);
		L = addr(L,r1);
		reduce(L);
		X = mulr(X,r3);
		reduce(X);
		sum = addr(sum, divr(mulr(M,L),X));
		reduce(sum);
	}
	
	ratio res = divr(C, sum);
	reduce(res);
	return res;
}

ratio leibniz(uint k){
	ratio r = {1,3};
	ratio res = {1,1};
	
	while(k){
		if(k % 2 == 0) res = subr(res,r);
		else 	  	   res = addr(res,r);
		
		r.b += 2;
		k--;
		reduce(res);
	}
	res = mulr(res,(ratio){4,1});
	reduce(res);
	return res;
}

int main(int argc, char *argv[]){
	// those are max iterations that work for those stupid ratio pi calculators lol
	puts("Chudnovsky");
	print_ratio(pi(2),15);
	puts("\n-------------\n");
	puts("Leibniz series");
	print_ratio(leibniz(42),15);
	puts("\n-------------\n");
	puts("Just using 355/113");
	print_ratio((ratio){355,113},15);
	puts("\n-------------\n");
	puts("Golden ratio using fibbonacci");
	print_ratio(fibr(150),40);
    return 0;
}
