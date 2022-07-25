#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ratio.h"

#define a1 545140134
#define a2 13591409
#define a3 262537412640768000

typedef __uint128_t uint128;

uint128 fib(uint128 f, uint128* r){
	uint128 a = 1,b = 1,c;
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

ratio fibr(uint128 f){
	uint128 r = 0;
	uint128 t = fib(f,&r);
	
	return (ratio){1,t,r};
}

uint128 factorial(uint128 n) {
    if (n == 0) return 1;
    return factorial(n - 1) * n;
}

ratio factr(uint128 n){
    return (ratio){1,factorial(n),1};
}

ratio pi(unsigned k){
	const ratio r1 = {1,a1,1};
	const ratio r3 = {-1,a3,1};

	ratio C = {1,8582422400,201};
	ratio X = {1,1,1};
	ratio L = {1,a2,1};
	ratio sum = L;
	ratio M = {1,0,0};
	
	for(uint128 i = 1; i <= k;i++){
		M = divr( factr(6*i), mulr( factr(3*i), powr(factr(i),3 ) ) );
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
	ratio r = {1,1,3};
	ratio res = {1,1,1};
	
	while(k){
		if(k % 2 == 0) res = subr(res,r);
		else 	  	   res = addr(res,r);
		
		r.b += 2;
		k--;
		reduce(res);
	}
	res = mulr(res,(ratio){1,4,1});
	reduce(res);
	return res;
}

ratio sqrt(uint n, uint iter){
	ratio res = {1,n / 2,1};
	while(iter--){
		res = mulr((ratio){1,1,2}, addr(res, divr((ratio){1,n,1},res)));
	}
	return res;
}

int main(int argc, char *argv[]){
	// those are max iterations that work for those stupid ratio pi calculators lol
	puts("Chudnovsky");
	print_ratio(pi(2),15);
	puts("\n-------------\n");
	puts("Leibniz series");
	print_ratio(leibniz(44),15);
	puts("\n-------------\n");
	puts("Just using 355/113");
	print_ratio((ratio){1,355,113},15);
	puts("\n-------------\n");
	puts("Golden ratio using fibbonacci");
	print_ratio(fibr(180),68);
	puts("\n-------------\n");
	puts("Approximating a square root of 2");
	print_ratio(sqrt(2,6),40);
    return 0;
}
