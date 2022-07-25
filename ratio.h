typedef __uint128_t uint128;
typedef signed char int8;

uint128 nwd (uint128 a, uint128 b){
      uint128 ab = a * b, t = 0;
      while(b)
      {
        t = b;
        b = a % b;
        a = t;
      }
      return ab / a;
}

uint128 gcd(uint128 a, uint128 b) {
    return (b ? gcd(b, a % b) : a);
}

unsigned log10i(uint128 v){
	unsigned res = 1;
	while(v >= 10){
		v /= 10;
		res++;
	}
	return res;
}


uint128 pow10(uint128 x){
	if (x == 0) return 1;
    return pow10(x-1) * 10;
}

void print128(uint128 n)
{
   int i = 0;
   
   char* buffer[41];
   
   do {  
      buffer[i++] = (n % 10) + '0'; 
   } while ((n /= 10) > 0);
   
   for(int j = i-1; j >= 0;j--) putchar(buffer[j]);
}

#define printr(x) print128(x.a);printf(" / ");print128(x.b);


void reduce128(uint128* a, uint128* b){
	uint128 g = gcd(*a,*b);
	if(g == 1) return;
	*a = ((*a) / g);
	*b = ((*b) / g);
}

#define reduce(x) reduce128(&x.a, &x.b)
#define reducer(x,y) reduce128(&x.a, &y.b);reduce128(&y.a, &x.b)

uint128 pow128(uint128 a, uint128 b){
	if(b == 0) return 1;
	return pow128(a,b-1) * a;
}

struct ratio {
    int8 sign;
	uint128 a,b;
};

typedef struct ratio ratio;

ratio powr(ratio r, uint128 p){
    ratio n = (ratio){p & 1 ? r.sign : r.sign & 127,pow128(r.a,p),pow128(r.b,p)}; // 127 is just -1 >> 1, quick way to abs the 8bit int
    reduce(n);
	return n;
}

ratio mulr(ratio a, ratio b){
	reducer(a,b);
	return (ratio){a.sign * b.sign,a.a * b.a,a.b * b.b};
}

ratio divr(ratio a, ratio b){
    ratio n = mulr(a , (ratio){1,b.b,b.a});
    n.sign = a.sign * b.sign;
    return n;
}

ratio subr(ratio a, ratio b); // declaration needed for addr

ratio addr(ratio a, ratio b){
    
	uint128 n = nwd(a.b,b.b);
	
	a.a = a.a * (n / a.b);
	a.b = n;
	
	b.a = b.a * (n / b.b);
	b.b = n;
	// -128 is used as 0b10000000 to check for sign bit
	if(b.sign & -128 && a.sign & -128){ b.sign = 1; a.sign = 1; }
	if(b.sign & -128 || a.sign & -128){ return subr(a,b); }
    
	return (ratio){1,a.a + b.a, n};
}

ratio subr(ratio a, ratio b){
	if(b.sign == -1){
        b.sign = 1;
	    return addr(a,b);
    }
	uint128 n = nwd(a.b,b.b);
	
	a.a = a.a * (n / a.b);
	a.b = n;
	
	b.a = b.a * (n / b.b);
	b.b = n;
    if(a.sign == -1){ return (ratio){-1,a.a + b.a, n}; }
    if(b.a > a.a){
        return (ratio){-1,b.a - a.a, n};
    }
    return (ratio){1,a.a - b.a, n};
}

void print_ratio(ratio r,unsigned prec) {
	if(r.b == 0){
		perror("Freaking 0 in denominator are you serious?\n");
		exit(1);
	}
	if(r.sign == -1) putchar('-');
    print128(r.a); printf(" / ");
    print128(r.b); putchar('\n');

	if(prec == 0) puts("yooo boy you ballin!");

	uint128 comp = 0;
	
    if(r.sign == -1) putchar('-');
	uint128 m = r.a / r.b;
	print128(m);putchar('.');
	comp = r.a - (m * r.b);
	
	while(prec){
			if(comp == 0) return;
			while(comp < r.b) { comp *= 10; if(comp < r.b)putchar('0'); }
			
			uint128 m = comp / r.b; 
			print128(m);
			comp = comp - (m * r.b);
			prec--;
	}
}

