#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
#define ll long long
int main(){
	ll int p, g, a, b, pa, pb, secret;
	printf("Enter prime number p : ");
	scanf("%lld", &p);
	printf("Enter primitive root g : ");
	scanf("%lld", &g);	
	printf("Enter Alice private key : ");
	scanf("%lld", &a);	
	printf("Enter Bob private key : ");
	scanf("%lld", &b);	
	printf("Alice public key is : ");
	pa = (ll int)pow(g,a) % p;
	printf("%lld\n", pa);
	printf("Bob public key is : ");
	pb = (ll int)pow(g,b) % p;
	printf("%lld\n", pb);		
	printf("Alice shared secret key is : ");
	printf("%lld\n", (ll int)pow(pb,a) % p);	
	printf("Bob shared secret key is : ");
	printf("%lld\n", (ll int)pow(pa,b) % p);	
	return 0;
}
