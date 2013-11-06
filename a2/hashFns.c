#define BIT8 0x01
#define BIT7 0x02
#define BIT6 0x04
#define BIT5 0x08
#define BIT4 0x10
#define BIT3 0x20
#define BIT2 0x40
#define BIT1 0x80


#include <stdio.h>
#include <string.h>
#include <limits.h>

void printbincharpad(char c)
{
//TODO: only used for debugging http://stackoverflow.com/questions/7863499/conversion-of-char-to-binary-in-c
    int i;

    for (i = 7; i >= 0; --i)
    {
        putchar( (c & (1 << i)) ? '1' : '0' );
    }
    putchar('\n');
}

unsigned fnv_hash ( void *key, int len )
{
	unsigned char *p = key;
	unsigned h = 2166136261;
	int i;
	for ( i = 0; i < len; i++ )
		h = ( h * 16777619 ) ^ p[i];
	return h;
}




int main()
{
	//char bits[8] = {BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8};

	char eightBitArray = 0;
	
	//TODO: make array bigger so that 0s count? / convert int to binary rep?
	int data = 44;
	int len = 2;//strlen(data);

	int hashValue = fnv_hash(&data, len);
	
	//TODO: make sure normalized between 1 and 8
	int normalized = hashValue / ((double)INT_MAX / 7.0) + 1.0;
	
	printf("%s %d \n", "normalized", normalized);
	//insert hash values into the bitArray
	switch(normalized){
		case 1: eightBitArray |= BIT1;break;
		case 2: eightBitArray |= BIT2;break;
		case 3: eightBitArray |= BIT3;break;
		case 4: eightBitArray |= BIT4;break;
		case 5: eightBitArray |= BIT5;break;
		case 6: eightBitArray |= BIT6;break;
		case 7: eightBitArray |= BIT7;break;
		case 8: eightBitArray |= BIT8;break;
		default: printf("%s %d \n", "Unknown hash value", hashValue);
	}
	
	printbincharpad(eightBitArray);
	
	//check if hash value is in array
	int queryHash = 0;
	char result;

	switch(queryHash){
                case 1: result = eightBitArray & BIT1;break;
                case 2: result = eightBitArray & BIT2;break;
                case 3: result = eightBitArray & BIT3;break;
                case 4: result = eightBitArray & BIT4;break;
                case 5: result = eightBitArray & BIT5;break;
                case 6: result = eightBitArray & BIT6;break;
                case 7: result = eightBitArray & BIT7;break;
                case 8: result = eightBitArray & BIT8;break;
                default: printf("%s %d \n", "Unknown hash value", queryHash);
        }

	if (result == 0){
		printf("%s", "NO match");
	}else{
		printf("%s", "match!");
	}

	printbincharpad(result);


}


//http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx


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




