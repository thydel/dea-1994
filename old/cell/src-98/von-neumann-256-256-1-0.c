von_neumann_256_256_1_0 (unsigned char *past, unsigned char *futur,
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
  index = ((north[255] << 8) | (center[255] << 7) | (south[255] << 6));
  index = (index | (*north++ << 5) | (*center++ << 4) | (*south++ << 3));
  index = (index | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		((index & 0x80) >> 3))];
/* cols */
  for (col = 254; col--;)
    {
/* set_col_index */
      index = ((index << 3) | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		    ((index & 0x80) >> 3))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 3) | (north[-256] << 2) | (center[-256] << 1) | south[-256]);
/* set_futur */
  *futur++ =
    transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		((index & 0x80) >> 3))];
  north = past;
  center = (north + side);
  south = (center + side);
  for (line = 254; line--;)
    {
/* conex */
/* first_col */
/* set_first_col_index */
      index = ((north[255] << 8) | (center[255] << 7) | (south[255] << 6));
      index = (index | (*north++ << 5) | (*center++ << 4) | (*south++ << 3));
      index = (index | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		    ((index & 0x80) >> 3))];
/* cols */
      for (col = 254; col--;)
	{
/* set_col_index */
	  index =
	    ((index << 3) | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
	  *futur++ =
	    transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
			((index & 0x80) >> 3))];
	}
/* last_col */
/* set_last_col_index */
      index =
	((index << 3) | (north[-256] << 2) | (center[-256] << 1) |
	 south[-256]);
/* set_futur */
      *futur++ =
	transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		    ((index & 0x80) >> 3))];
    }
  north = (past + (size - (side << 1)));
  center = (north + side);
  south = past;
/* conex */
/* first_col */
/* set_first_col_index */
  index = ((north[255] << 8) | (center[255] << 7) | (south[255] << 6));
  index = (index | (*north++ << 5) | (*center++ << 4) | (*south++ << 3));
  index = (index | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		((index & 0x80) >> 3))];
/* cols */
  for (col = 254; col--;)
    {
/* set_col_index */
      index = ((index << 3) | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		    ((index & 0x80) >> 3))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 3) | (north[-256] << 2) | (center[-256] << 1) | south[-256]);
/* set_futur */
  *futur++ =
    transition[(((index & 0x2) >> 1) | ((index & 0x38) >> 2) |
		((index & 0x80) >> 3))];
}
