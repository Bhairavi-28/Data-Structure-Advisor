#include<stdio.h>
#include<stdlib.h>

int a[20][20], s[20], visited[20], n, i, j, top = -1;

void dfs(int);
void main(){
    int v;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix: ");

    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    printf("Enter the starting vertex: ");
    scanf("%d", &v);

    for(i=0; i<n; i++){
        s[i]=0;
        visited[i]=0;
    }

    dfs(v);
    printf("The reachable nodes are: ");
    for(i=0; i<n; i++){
        if(visited[i])
            printf("%d\t", i);
    }
}

void dfs(int v){
    for(i=0; i<n; i++)
        if(a[v][i] && !visited[i])
            s[++top]=i;

    if (top!=-1)
    {
        visited[s[top]]=1;
        dfs(s[top--]);
    }

}