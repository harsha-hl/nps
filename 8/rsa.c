#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int prime(long int p){
	for(int i=2;i<p;i++) if(p % i == 0) return 0;
	return 1;
}

long int gcd(long int a, long int b){
	if(a==0) return b;
	else if(b==0)return a;
	else if(b>a) return gcd(b, a);
	else return gcd(b, a%b);
}

long int encrypt(char ch, long int n, long int e){
	long int num = ch, ans = ch;
	for(int i = 2; i<=e;i++) ans = (ans*num)%n;
	return ans;
}

char decrypt(long int ch, long int n, long int d){
	long int num = ch, ans = ch;
	for(int i = 2; i<=d;i++) ans = (ans*num)%n;
	return ans;
}

int main(){
	long int p, q, n, phi, e, d, cipher[50];
	char text[50];
	
	do{
		p = rand() % 40;
	}while(!prime(p));

	do{
		q = rand() % 40;
	}while(!prime(q) && p != q);	
	
	n = p*q;
	phi = (p-1)*(q-1);
	
	do{
		e = rand() % phi;
	}while(gcd(e, phi) != 1);
	
	do{
		d = rand() % phi;
	}while((e*d)% phi != 1);	
	
	printf("p = %ld, q = %ld, n = %ld, phi = %ld\n", p, q, n, phi);
	printf("Public key (n, e) --> (%ld, %ld)\n", n, e);
	printf("Public key (n, d) --> (%ld, %ld)\n", n, d);
	
	printf("Enter text to encrypt : ");
	gets(text);
	int i, len = strlen(text);
	for(i = 0; i<len;i++){
	 cipher[i] = encrypt(text[i], n, e);
	}
	printf("Encrypted text : ");
	for(i = 0; i<len;i++)printf("%ld",cipher[i]);
	printf("\n");
	
	for(i = 0; i<len;i++){
	 text[i] = decrypt(cipher[i], n, d);
	}
	printf("Decrypted text : ");
	for(i = 0; i<len;i++)printf("%c",text[i]);
	printf("\n");
	return 0;
}
