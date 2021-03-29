
#define NUM (1024*1024)
int arr_a[NUM];
int arr_b[NUM];
int arr_c[NUM];

int main(int ac, char *av[])
{
    int one = ac + 1;
    for (int i = 0; i < NUM; i++) {
	arr_a[i] = i;
	arr_b[i] = NUM - i;
	arr_c[i] = 0;
    } 
    for (int i = 0; i < NUM; i++) {
	arr_c[i] = (arr_a[i] + arr_b[i]) / one;
    }
    int sum = 0;
    for (int i = 0; i < NUM; i++)
	sum += arr_c[i];
    return sum;
}

