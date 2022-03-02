typedef __int128_t int128;
typedef __uint128_t uint128;

int128 nwd (int128 a, int128 b){
      int128 ab = a * b, t = 0;
      while(b)
      {
        t = b;
        b = a % b;
        a = t;
      }
      return ab / a;
}

int128 gcd(int128 a, int128 b) {
    return (b ? gcd(b, a % b) : a);
}

uint log10i(int128 v){
	if (v < 0) v = -v;
	uint res = 1;
	while(v >= 10){
		v /= 10;
		res++;
	}
	return res;
}


int128 pow10(int128 x){
	if (x == 0) return 1;
    return pow10(x-1) * 10;
}

void print128(int128 n)
{
   int i = 0;
   int128 sign;
   
   char* buffer[41];
   
   if ((sign = n) < 0) 
      n = -n;           /* make n positive */
   
   do {  
      buffer[i++] = n % 10 + '0'; 
   } while ((n /= 10) > 0);
   
   if (sign < 0) buffer[i++] = '-';
   for(int j = i-1; j >= 0;j--) putchar(buffer[j]);
}

#define printr(x) print128(x.a);printf(" / ");print128(x.b);


void reduce128(int128* a, int128* b){
	int128 g = gcd(*a,*b);	
	*a = ((*a) / g);
	*b = ((*b) / g);
}

#define reduce(x) reduce128(&x.a, &x.b)
#define reducer(x,y) reduce128(&x.a, &y.b);reduce128(&y.a, &x.b)

int128 pow128(int128 a, int128 b){
	if(b == 0) return 1;
	return pow128(a,b-1) * a;
}




struct ratio {
	int128 a,b;
};
typedef struct ratio ratio;

ratio powr(ratio r, int128 p){
	return (ratio){pow128(r.a,p),pow128(r.b,p)};
}

ratio mulr(ratio a, ratio b){
	reducer(a,b);
	return (ratio){a.a * b.a,a.b * b.b};
}

ratio divr(ratio a, ratio b){
	return mulr(a,(ratio){b.b,b.a});
}

ratio addr(ratio a, ratio b){
	int128 n = nwd(a.b,b.b);
	
	a.a = a.a * (n / a.b);
	a.b = n;
	
	b.a = b.a * (n / b.b);
	b.b = n;
	
	return (ratio){a.a + b.a, a.b};
}

ratio subr(ratio a, ratio b){
	return addr(a,mulr(b,(ratio){-1,1}));
}

int128 get_num(int128 num,uint idx, uint l){
	int128 t = num / pow10(log10i(num)-(idx + l) + 1);
	int128 sub = (t / pow10(l)) * pow10(l);
	return t - sub;
}

void print_ratio(ratio r,uint prec) {
	if(r.b == 0){
		perror("Freaking 0 in denominator are you serious?\n");
		exit(1);
	}
	
    print128(r.a); printf(" / ");
    print128(r.b); putchar('\n');

	if(prec == 0) puts("yooo boy you ballin!");

	if(r.a < 0)	  	 { putchar('-'); r.a *= -1;}
	else if(r.b < 0) { putchar('-'); r.b *= -1;}
	
	int128 comp = 0;
	
	int128 m = r.a /r.b;
	print128(m);putchar('.');
	comp = r.a - (m * r.b);
	
	while(prec){
			if(comp == 0) return;
			while(comp < r.b) { comp *= 10; if(comp < r.b)putchar('0'); }
			
			int128 m = comp / r.b; 
			print128(m);
			comp = comp - (m * r.b);
			prec--;
	}
}

