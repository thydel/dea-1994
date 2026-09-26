#define K 1024

main(){
    unsigned char buf[K];
    int i, n;

    while(n = read(0, buf, K)) {
	for (i = 0; i < n; ++i) {
	    printf("%d\n", buf[i]);
	}
    }
}
