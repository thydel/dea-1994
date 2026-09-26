von_neumann_256_256_4_0 (unsigned char *past, unsigned char *futur,
			 unsigned char *transition, int side, int size)
{
  register unsigned char *north;
  register unsigned char *center;
  register unsigned char *south;
  register int index;
  int line;
  int col;

  north = (past + (size - side));
  center = past;
  south = (center + side);
/* conex */
/* first_col */
/* set_first_col_index */
  index = ((north[255] << 32) | (center[255] << 28) | (south[255] << 24));
  index = (index | (*north++ << 20) | (*center++ << 16) | (*south++ << 12));
  index = (index | (*north++ << 8) | (*center++ << 4) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		((index & 0xf0000000) >> 12))];
/* cols */
  for (col = 254; col--;)
    {
/* set_col_index */
      index = ((index << 12) | (*north++ << 8) | (*center++ << 4) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		    ((index & 0xf0000000) >> 12))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 12) | (north[-256] << 8) | (center[-256] << 4) | south[-256]);
/* set_futur */
  *futur++ =
    transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		((index & 0xf0000000) >> 12))];
  north = past;
  center = (north + side);
  south = (center + side);
  for (line = 254; line--;)
    {
/* conex */
/* first_col */
/* set_first_col_index */
      index = ((north[255] << 32) | (center[255] << 28) | (south[255] << 24));
      index =
	(index | (*north++ << 20) | (*center++ << 16) | (*south++ << 12));
      index = (index | (*north++ << 8) | (*center++ << 4) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		    ((index & 0xf0000000) >> 12))];
/* cols */
      for (col = 254; col--;)
	{
/* set_col_index */
	  index =
	    ((index << 12) | (*north++ << 8) | (*center++ << 4) | *south++);
/* set_futur */
	  *futur++ =
	    transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
			((index & 0xf0000000) >> 12))];
	}
/* last_col */
/* set_last_col_index */
      index =
	((index << 12) | (north[-256] << 8) | (center[-256] << 4) |
	 south[-256]);
/* set_futur */
      *futur++ =
	transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		    ((index & 0xf0000000) >> 12))];
    }
  north = (past + (size - (side << 1)));
  center = (north + side);
  south = past;
/* conex */
/* first_col */
/* set_first_col_index */
  index = ((north[255] << 32) | (center[255] << 28) | (south[255] << 24));
  index = (index | (*north++ << 20) | (*center++ << 16) | (*south++ << 12));
  index = (index | (*north++ << 8) | (*center++ << 4) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		((index & 0xf0000000) >> 12))];
/* cols */
  for (col = 254; col--;)
    {
/* set_col_index */
      index = ((index << 12) | (*north++ << 8) | (*center++ << 4) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		    ((index & 0xf0000000) >> 12))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 12) | (north[-256] << 8) | (center[-256] << 4) | south[-256]);
/* set_futur */
  *futur++ =
    transition[(((index & 0xf0) >> 4) | ((index & 0xfff000) >> 8) |
		((index & 0xf0000000) >> 12))];
}
