#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long long n, len, max_tr=0, max_len=0, temp_tr;
    scanf("%lld", &n);
    long long int* a=NULL;
    long long int* m;
    for(long long f=0; f<n; f++){
        temp_tr=0;
        scanf("%lld", &len);
        m=(long long int*)malloc(sizeof(long long int)*len*len);
        for(long long i=0; i<len; i++){
            for(long long j=0; j<len; j++){
                scanf("%lld", &m[i+j*len]);
                if(i==j) temp_tr+=m[i+j*len];
            }
        }
        if(f==0){
            max_len=len;
            a=m;
            max_tr=temp_tr;
        }
        else{
            if(temp_tr>max_tr){
                max_len=len;
                free(a);
                a=m;
                max_tr=temp_tr;
            }
            else free(m);
        }
    }
    for(long long i=0; i<max_len; i++){
        for(long long j=0; j<max_len; j++) printf("%lld ", a[i+j*max_len]);
        printf("\n");
    }
    return 0;
}
