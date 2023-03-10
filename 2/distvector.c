#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
int main(){
	printf("Enter number of nodes\n");
	int n,i,j,k;
	scanf("%d", &n);
	int cost[n+1][n+1], dist[n+1][n+1], nexthop[n+1][n+1];
	/*
0 4 2 999 999
4 0 999 -8 999
2 999 0 1 999
999 -8 1 0 6
999 999 999 6 0
Negative weight cycle present in topology
	*/
	printf("Enter the cost matrix\n");
	for( i=1;i<=n;i++){
		for( j=1;j<=n;j++){
			scanf("%d",&cost[i][j]);
			if(cost[i][j] == 999)cost[i][j] = INT_MAX;
			if(i==j){
				dist[i][j] = 0;
				nexthop[i][j] = i;
			}
			else {
				dist[i][j] = cost[i][j] == INT_MAX ? INT_MAX : cost[i][j];
				nexthop[i][j] = cost[i][j] == INT_MAX ? -1 : j; 
			}
		}
	}

	int cnt = 0;
	bool flag = true;
	while(flag){
		cnt++;

		flag = false;
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				if(i != j){
					for(k=1;k<=n;k++){
						if(cost[i][k] != INT_MAX){
							if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j]){
								flag = true;
								if(cnt >= n){printf("Negative weight cycle present in topology\n"); exit(0);}
								dist[i][j] = dist[i][k] + dist[k][j];
								nexthop[i][j] = k;
							}
						}
					}
				} 
			}
		}
	}
	for(i=1;i<=n;i++){
		printf( "\nThe routing table for %d is :\nDest\tDist\tNext\n", i);
		for(j=1;j<=n;j++) printf("%d\t%d\t%d\n",j,dist[i][j],nexthop[i][j]);
	}
	return 0;
}
