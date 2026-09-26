von_neumann_256_256_2_0 (unsigned char *past, unsigned char *futur,
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
  index = ((north[255] << 16) | (center[255] << 14) | (south[255] << 12));
  index = (index | (*north++ << 10) | (*center++ << 8) | (*south++ << 6));
  index = (index | (*north++ << 4) | (*center++ << 2) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		((index & 0xc000) >> 6))];
/* cols */
  for (col = 254; col--;)
    {
/* set_col_index */
      index = ((index << 6) | (*north++ << 4) | (*center++ << 2) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		    ((index & 0xc000) >> 6))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 6) | (north[-256] << 4) | (center[-256] << 2) | south[-256]);
/* set_futur */
  *futur++ =
    transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		((index & 0xc000) >> 6))];
  north = past;
  center = (north + side);
  south = (center + side);
  for (line = 254; line--;)
    {
/* conex */
/* first_col */
/* set_first_col_index */
      index = ((north[255] << 16) | (center[255] << 14) | (south[255] << 12));
      index = (index | (*north++ << 10) | (*center++ << 8) | (*south++ << 6));
      index = (index | (*north++ << 4) | (*center++ << 2) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		    ((index & 0xc000) >> 6))];
/* cols */
      for (col = 254; col--;)
	{
/* set_col_index */
	  index =
	    ((index << 6) | (*north++ << 4) | (*center++ << 2) | *south++);
/* set_futur */
	  *futur++ =
	    transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
			((index & 0xc000) >> 6))];
	}
/* last_col */
/* set_last_col_index */
      index =
	((index << 6) | (north[-256] << 4) | (center[-256] << 2) |
	 south[-256]);
/* set_futur */
      *futur++ =
	transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		    ((index & 0xc000) >> 6))];
    }
  north = (past + (size - (side << 1)));
  center = (north + side);
  south = past;
/* conex */
/* first_col */
/* set_first_col_index */
  index = ((north[255] << 16) | (center[255] << 14) | (south[255] << 12));
  index = (index | (*north++ << 10) | (*center++ << 8) | (*south++ << 6));
  index = (index | (*north++ << 4) | (*center++ << 2) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		((index & 0xc000) >> 6))];
/* cols */
  for (col = 254; col--;)
    {
/* set_col_index */
      index = ((index << 6) | (*north++ << 4) | (*center++ << 2) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		    ((index & 0xc000) >> 6))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 6) | (north[-256] << 4) | (center[-256] << 2) | south[-256]);
/* set_futur */
  *futur++ =
    transition[(((index & 0xc) >> 2) | ((index & 0xfc0) >> 4) |
		((index & 0xc000) >> 6))];
}
