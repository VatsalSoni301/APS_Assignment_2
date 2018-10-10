#include<bits/stdc++.h>
using namespace std;


int main(){
    FILE* in = fopen("input_4.txt", "w");
    srand(time(NULL));
    for (long long i = 0; i < 100000 ; i++)
    {
        fprintf(in,"1\n");
        fprintf(in, "%d\n", rand() );
        fprintf(in, "%d\n", rand() );
    }
    // for (long long i = 0; i < 1000 ; i++)
    // 	fprintf(in, "%d\n", 1 + (rand()) % (100000) ); 
    fclose(in);
    return 0;
}