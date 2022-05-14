#include <stdio.h>
#include <assert.h>


long long int counting( long long int n)
{
	int count = 0;
	while(n != 0)
	{
		n &= (n - 1);
		count++;
	}
	return count;
}



int main()
{
	assert(counting(-558) == 59);
	printf("number of one`s is %lld\n", counting(-558));
	assert(64 == counting(-1));
	printf("number of one`s is %lld\n", counting(-1));
	assert(63 == counting(-2));
	printf("number of one`s is %lld\n", counting(-2));
	assert(0 == counting(0));
	printf("number of one`s is %lld\n", counting(0));
	assert(1 == counting(1));
	printf("number of one`s is %lld\n", counting(1));
	assert(1 == counting(2));
	printf("number of one`s is %lld\n", counting(2));
	assert(4 == counting(15));
	printf("number of one`s is %lld\n", counting(15));
	assert(37 == counting(9999999999999999999));
	printf("number of one`s is %lld\n", counting(9999999999999999999));


}