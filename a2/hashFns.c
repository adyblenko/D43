#define BIT8 0x01
#define BIT7 0x02
#define BIT6 0x04
#define BIT5 0x08
#define BIT4 0x10
#define BIT3 0x20
#define BIT2 0x40
#define BIT1 0x80

char bits[8] = {BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8};


char eightBits = 0;
//eightBits = eightBits & (1 << 4);

eightBits &= (bits[3] & bits[4]);
//eightBits now looks like "00110000".


//http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx

unsigned fnv_hash ( void *key, int len )
{
	unsigned char *p = key;
	unsigned h = 2166136261;
	int i;
	for ( i = 0; i < len; i++ )
		h = ( h * 16777619 ) ^ p[i];
	return h;
}

unsigned oat_hash ( void *key, int len )
{
  unsigned char *p = key;
  unsigned h = 0;
  int i;

  for ( i = 0; i < len; i++ ) {
    h += p[i];
    h += ( h << 10 );
    h ^= ( h >> 6 );
  }

  h += ( h << 3 );
  h ^= ( h >> 11 );
  h += ( h << 15 );

  return h;
}

/*
unsigned jsw_hash ( void *key, int len )
{
  unsigned char *p = key;
  unsigned h = 16777551;
  int i;

  for ( i = 0; i < len; i++ )
    h = ( h << 1 | h >> 31 ) ^ tab[p[i]];

  return h;
}
*/

unsigned sax_hash ( void *key, int len )
{
  unsigned char *p = key;
  unsigned h = 0;
  int i;

  for ( i = 0; i < len; i++ )
    h ^= ( h << 5 ) + ( h >> 2 ) + p[i];

  return h;
}


unsigned elf_hash ( void *key, int len )
{
  unsigned char *p = key;
  unsigned h = 0, g;
  int i;

  for ( i = 0; i < len; i++ ) {
    h = ( h << 4 ) + p[i];
    g = h & 0xf0000000L;

    if ( g != 0 )
      h ^= g >> 24;

    h &= ~g;
  }

  return h;
}




