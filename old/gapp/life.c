life(){ /* Conway's life game */
	int i;
		/* Initialiser RAM 16-23 avec 1100	i.e. 3
		 *		   24-31 avec 0100	i.e. 2
		 */

	send(c,1); send(ram,16,c);
	send(c,1); send(ram,17,c);

	send(c,0); send(ram,24,c);
	send(c,1); send(ram,25,c);

			/* Compter les voisins dans le frame 1 */
	orth_voisins();
	diag_voisins();

			/* 1 dans RAM 120 si nb_voisins = 3 */
	send(c,1); send(ram,120,c);
	for(i=0; i<4; i++)
	{
	  send(ns,ram,i+8); send(ew,ram,i+16); send(c,1);
	  send(ram,80,sm);	/* auxiliaire RAM 80 = XNOR */
	  send(ns,ram,120); send(ew,ram,80); send(c,0);
				/* CY = AND */
	  send(c,cy); send(ram,120,c);
	}

			/* 1 dans RAM 121 si nb_voisins = 2 */
	send(c,1); send(ram,121,c);
	for(i=0; i<4; i++)
	{
	  send(ns,ram,i+8); send(ew,ram,i+24); send(c,1);
	  send(ram,80,sm);	/* auxiliaire RAM 80 = XNOR */
	  send(ns,ram,121); send(ew,ram,80); send(c,0);
				/* CY = AND */
	  send(c,cy); send(ram,121,c);
	}

			/* RAM 0 = RAM 120 or (RAM 121 and RAM 0) */
	send(ns,ram,121); send(ew,ram,0); send(c,0);
	send(c,cy);
	send(ns,c); send(ew,ram,120); send(c,1);
	send(c,cy);
	send(ram,0,c);
}

static
orth_voisins(){ /* Nb de voisins orthogonaux */
	int i;
				/* sud */
	for(i=0; i<3; i++)
	{
	  send(ns,ram,i);
	  send(ns,s); send(c,ns); send(ram,i+8,c);
	}
				/* plus nord */
	send(c,0);
	for(i=0; i<3; i++)
	{
	  send(ns,ram,i); send(ns,n);
	  send(ew,ram,i+8); send(ram,i+8,sm); send(c,cy);
	}
				/* plus west */
	send(c,0);
	for(i=0; i<3; i++)
	{
	  send(ew,ram,i); send(ew,w);
	  send(ns,ram,i+8); send(ram,i+8,sm); send(c,cy);
	}
				/* plus east */
	send(c,0);
	for(i=0; i<3; i++)
	{
	  send(ew,ram,i); send(ew,e);
	  send(ns,ram,i+8); send(ram,i+8,sm); send(c,cy);
	}
}

static
diag_voisins(){ /* Nb de voisins diagonaux */
	int i;
				/* plus nord-west */
	send(c,0);
	for(i=0; i<3; i++)
	{
	  send(ew,ram,i); send(ew,w); send(ns,ew); send(ns,n);
	  send(ew,ram,i+8); send(ram,i+8,sm); send(c,cy);
	}
				/* plus nord-east */
	send(c,0);
	for(i=0; i<3; i++)
	{
	  send(ew,ram,i); send(ew,e); send(ns,ew); send(ns,n);
	  send(ew,ram,i+8); send(ram,i+8,sm); send(c,cy);
	}
				/* plus sud-east */
	send(c,0);
	for(i=0; i<3; i++)
	{
	  send(ew,ram,i); send(ew,e); send(ns,ew); send(ns,s);
	  send(ew,ram,i+8); send(ram,i+8,sm); send(c,cy);
	}
				/* plus sud-west */
	send(c,0);
	for(i=0; i<3; i++)
	{
	  send(ew,ram,i); send(ew,w); send(ns,ew); send(ns,s);
	  send(ew,ram,i+8); send(ram,i+8,sm); send(c,cy);
	}
}
