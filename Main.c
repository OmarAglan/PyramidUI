#include <stdio.h>

void main(void)
{
	/*Print Statment
	printf("Hello World");
	math();
	if_Test();
	while_Test();
	*/
	do_while_test();
}
void math(void)
{
	float a;
	int b = 3;
	int c;

	a = 2;
	c = a + b;
	printf("The sum of adding %f and %d is %d\n", a, b, c);
}

void if_Test(void)
{
	int a = 0;

	if (a == 0)
	{
		/* code */
		printf("a is equal to 0\n");
	}
	else
	{
		/* code */
		printf("a is not equal to 0\n");
	}
}

void while_Test(void)
{
	int a = 0;

	while (a < 5)
	{
		/* code */
		printf("a is equl to %d\n", a);
		a++;
	}
	printf("a is equal to %d and I've finished\n", a);
}

void do_while_test(void)
{
	int a = 0;
	do
	{
		/* code */
		printf("a is equal to %d\n", a);
		a++;
	} while (a < 5);
	printf ("a is equal to %d and I've finished\n", a);
}

