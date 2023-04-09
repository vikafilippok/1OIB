#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

char* chartobin(char c, char* result)
{
	char output[8]="\0";
	int j = 0;
	
    for (int i = 7; i >= 0; i--) {
		putchar((c & (1 << i)) ? '1' : '0');
		char tmp = ((c & (1 << i)) ? '1' : '0');
		output[j] = tmp;
		result[j] = output[j];
		j++;
	}
	printf(" ");
	return result;
}

long Nod(long a, long b)
{
	while (a && b)
		if (a >= b)
			a -= b;
		else
			b -= a;
	return a | b;
}

void extended_euclid(long a, long b, long *x, long *y, long *d)
/* вычисление a * *x + b * *y = gcd(a, b) = *d */
{
    long q, r, x1, x2, y1, y2;
    if (b == 0) {
        *d = a, *x = 1, *y = 0;
        return;
    }

    x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0) {
        q = a / b, r = a - q * b;
        *x = x2 - q * x1, *y = y2 - q * y1;
        a = b, b = r;
        x2 = x1, x1 = *x, y2 = y1, y1 = *y;
    }

    *d = a, *x = x2, *y = y2;
}

long inverse(long a, long n)
/* вычисление инверсии модуля n */
{
    int x1 = 0;
    long d, x, y;
    extended_euclid(a, n, &x, &y, &d);
    if (d == 1) {
        if (x < 0) {
            x1 = n + x;
            return x1;
        } else return x;
    }
    return 0;
}

int pow(int a, int n);
int in10sys(char* a, int n);



int main() {

	char result[MAX] = "\0";
	char** binum;//хранится весь текст в бинарном виде
	binum = (char**)malloc(sizeof(char*) * MAX);
	printf("Enter the massege: ");

	int ch;
	int i = 0;
	int size = 40;
	char* msg;

	msg = (char*)realloc(NULL, size);
	
	if (!result) {
		printf("memory error.\n");
		exit(1);
	}

	do {
		ch = getchar();
		if ( ch == '\n' || ch == '\t' || ch == EOF) break;
		msg = (char*)realloc(msg, (i + 1) * sizeof(char));
		msg[i + 1] = '\0';
		*(msg + i) = ch;
		i++;
	} while (1);


	int cnt_msg = 0;
    for (int i = 0;; i++){
        if (msg[i] != '\0'){
            cnt_msg += 1;
        }
        else
            break;
    }

	for (int i = 0; i < strlen(msg); i++) {
		chartobin(msg[i], result);//перевод одного символа в бинарный вид
		binum[i] = (char*)malloc(sizeof(char) * 8);//выделение памяти каждому символу в бинарном виде
		strcpy(binum[i], result);//занесение результата в массив строк
	}
	int N = sizeof(binum);
	int* A = (int*)malloc(N * sizeof(int));
	srand((time(NULL)));
	A[0] = rand() % 100;
	A[1] = rand() % (100 - A[0] + 1) + A[0];
	int sumlast = A[0] + A[1] + 1;
	for (int i = 2; i < N; i++) {

		A[i] = rand() % ((100 + sumlast) - sumlast + 1) + sumlast;
		sumlast += A[i] + 1;
	}
	int M = rand() % ((100 + sumlast) - sumlast + 1) + sumlast;
	printf("\nA is");
	for (int i = 0; i < N; i++) {
		printf(" %d", A[i]);
	}
	printf("\nM is %d", M);
	//выбор W
	int W = 0;
	while (Nod(W, M) != 1) {
		W = rand() % 1000;
	}
	printf("\nW is %d", W);

	printf("\nB is");
	int* B = (int*)malloc(N * sizeof(int));
	B[N] = '\0';
	for (int i = 0; i < N; i++) {
		B[i] = (A[i] * W) % M;//рюкзак(ключ)
		printf(" %d", B[i]);
	}

	printf("\nSecret key: (A,W) = (");
	for (int i = 0; i < N; i++) {
		printf(" %d", A[i]);
	}
	printf(", %d)\n", W);

	printf("Open key: (B,M) = (");
	for (int i = 0; i < N; i++) {
		printf(" %d", B[i]);
	}
	printf(", %d)\n", M);

    //W*W^(-1)(mod M) = 1
    //10 * (19) % 189 = 1
    int w_obrat = inverse(W,M);
    printf("\n W^(-1) is %d", w_obrat);

	
	int* c = calloc(cnt_msg, sizeof(int));
	printf("\nC is ");
    for (int i = 0; i < (cnt_msg); i++) {
		int C = 0;
        for (int j = 0; j < N; j++) {
            int tmp = (binum[i][j] - 48);
            C += (((tmp) * (B[j])) % M);//шифрограмма
        }
        printf(" %d ", C);
        c[i] = C;
    }

	unsigned long long* x = calloc(cnt_msg, sizeof(unsigned long long));
    printf("\nX is ");
	for (int i = 0; i < cnt_msg; i++) {
		unsigned long long X = 0;
        X = (c[i] * w_obrat) % M;
        printf(" %d ", X);
        x[i] = X;
	}

	printf("\n");
	int sum = 0;
    char** bin = calloc(cnt_msg, sizeof(char*));
	bin[cnt_msg] = '\0';
	for (int i = 0; i < cnt_msg; i++) {
		bin[i] = calloc(8, sizeof(char));
		bin[i][8] = '\0';
		sum = 0;
		for (int j = 7; j >= 0; j--) {
			if (sum < x[i] && A[j] <= x[i] && (sum + A[j]) <= x[i]) {
				sum += A[j];
				bin[i][j] = '1';
				
				
			}
			else {
				bin[i][j] = '0';
			}
		}	
	}
	printf("\n");
	
	
	for (int i = 0; i < cnt_msg; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%c", bin[i][j]);
		}
		printf(" ");	
		
	}
	printf("\n\nText: ");
	for (int i = 0; i < cnt_msg; i++) {
		char* y = bin[i];
		int z = 0;
		while (1) {
			if (*y == " " || *y == '\0') {

				printf("%c", in10sys(y - z, z), z);
				z = 0;
				if (*y == '\0') break;
				++y;
			}
			++y;
			z++;
		}
	}
	printf("\n");

	return 0;
}


int pow(int a, int n)
{
	if (n > 0) return a * pow(a, n - 1);
	else return 1;
}
int in10sys(char* a, int n)
{
	int i = 0;
	int m = 0;
	int str = n;
	while (i < n) {
		m = m + (*a - '0') * pow(2, str - i - 1);
		i++;
		*(a++);
	}
	return m;
}
