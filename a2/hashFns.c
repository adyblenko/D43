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


int wang_hash(int a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

char insertIntoBitArray(char eightBitArray, int bucketNumber){

	switch(bucketNumber){
                case 1: eightBitArray |= BIT1;break;
                case 2: eightBitArray |= BIT2;break;
                case 3: eightBitArray |= BIT3;break;
                case 4: eightBitArray |= BIT4;break;
                case 5: eightBitArray |= BIT5;break;
                case 6: eightBitArray |= BIT6;break;
                case 7: eightBitArray |= BIT7;break;
                case 8: eightBitArray |= BIT8;break;
                default: printf("%s %d \n", "Unknown bucket", bucketNumber);
        }

	printbincharpad(eightBitArray);

	return eightBitArray;
}

int normalizeHashValue(int hashValue){
	int normalized = hashValue / ((double)INT_MAX / 7.0) + 1.0;
	printf("%s %d \n", "normalized", normalized);
	return normalized;
}

int isInBitArray(char eightBitArray, int queryBucketNumber){

	char result;

	switch(queryBucketNumber){
                case 1: result = eightBitArray & BIT1;break;
                case 2: result = eightBitArray & BIT2;break;
                case 3: result = eightBitArray & BIT3;break;
                case 4: result = eightBitArray & BIT4;break;
                case 5: result = eightBitArray & BIT5;break;
                case 6: result = eightBitArray & BIT6;break;
                case 7: result = eightBitArray & BIT7;break;
                case 8: result = eightBitArray & BIT8;break;
                default: printf("%s %d \n", "Unknown hash value", queryBucketNumber);
        }

	printbincharpad(result);

	if (result == 0){
                return 0;
        }else{
                return 1;
        }
}



int main()
{
	char eightBitArray = 0;
	

	int data = 44;

	int hashValue = wang_hash(data);
	
	//make sure hash is normalized to bucket value between 1 and 8
	int bucketNum = normalizeHashValue(hashValue);

	//insert hash values into the bitArray
	eightBitArray = insertIntoBitArray(eightBitArray, bucketNum);
	
	//check if hash value is in array
	int queryData = 352;

	int queryHash = wang_hash(queryData);
	queryHash = normalizeHashValue(queryHash);
	int isInArray = isInBitArray(eightBitArray, queryHash);
	if (isInArray){
		printf("%s \n", "Match!");
	}else{
		printf("%s \n", "No Match");
	}

}

//http://burtleburtle.net/bob/hash/integer.html


int three_shift_hash( int a)
{
    a = a ^ (a>>4);
    a = (a^0xdeadbeef) + (a<<5);
    a = a ^ (a>>11);
    return a;
}

int java_hashmap_hash(int h) {
    // This function ensures that hashCodes that differ only by
    // constant multiples at each bit position have a bounded
    // number of collisions (approximately 8 at default load factor).
    h ^= (h >> 20) ^ (h >> 12);
    return h ^ (h >> 7) ^ (h >> 4);
}

int half_avalanche_hash( int a)
{
    a = (a+0x479ab41d) + (a<<8);
    a = (a^0xe4aa10ce) ^ (a>>5);
    a = (a+0x9942f0a6) - (a<<14);
    a = (a^0x5aedd67d) ^ (a>>3);
    a = (a+0x17bea992) + (a<<7);
    return a;
}

int full_avalanche_hash( int a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
}


//VVVVVVVVVVVVVVVVV___Below are string hashes, probably not needed___VVVVVVVVVVVVVV



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




