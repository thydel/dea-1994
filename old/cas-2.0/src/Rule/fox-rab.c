typedef struct {
    VN fox;
    VN rabbit;
    int fox_life;
    int rabbit_life;
} FoxRabIn;

typedef struct {
    Local fox;
    Local rabbit;
    Local fox_life;
    Local rabbit_life;
} FoxRabOut;

fox_rabbit(FoxRabIn* i, FoxRabOut* o) {
    int ifox;
    int ofox;
    int irabbit;
    int orabbit;
    int ifox_life;
    int ofox_life;
    int irabbit_life;
    int orabbit_life;

    int fox_sum;
    int rabbit_sum;

    ifox = i->fox.C
    irabbit = i->rabbit.C;
    ifox_life = i->fox_life.C
    irabbit_life = (L & 3 << 2) >> 2;

    fox_sum = W0 + N0 + S0 + E0;
    rabbit_sum = W1 + N1 + S1 + E1;

    ofox = ifox;
    orabbit = irabbit;

    if (ifox && irabbit) {
	orabbit = 0;
    }
    
    if (ifox) {
	ofox_life = ifox_life - 1;
	if (ofox_life > 0) {
	    ofox = 1;
	} else {
	    ofox = 0;
	}
    } 
    
    if (irabbit && !ifox) {
	orabbit_life = irabbit_life - 1;
	if (orabbit_life > 0) {
	    orabbit = 1;
	} else {
	    orabbit = 0;
	}
    }
    
    if (!ifox && fox_sum >= 2 && rabbit_sum >= 1) {
	ofox = 1;
	ofox_life = 3;
    }

    if (!irabbit && rabbit_sum >= 2) {
	orabbit = 1;
	orabbit_life = 3;
    }

    return ofox | orabbit << 1 | (ofox_life & 3) << 2 | (orabbit_life & 3) << 4 |
	(ofox & orabbit) << 6 | (ofox | orabbit) << 7;
}
