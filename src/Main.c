#include <stdio.h>

// Function prototypes
void math(void);
void if_Test(void);
void while_Test(void);
void do_while_test(void);

int main(void)
{
	/*Print Statment
	printf("Hello World");
	math();
	if_Test();
	while_Test();
	*/
	do_while_test();
	
	return 0;
}

void math(void)
{
	float a;
	int b = 3;
	float c;  // Changed to float to match calculation result

	a = 2;
	c = a + b;
	printf("The sum of adding %f and %d is %f\n", a, b, c);  // Fixed format specifier
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
		printf("a is equal to %d\n", a);  // Fixed spelling of "equal"
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

