/**
* n 阶勒让德多项式求值
* 迭代法和递归法
* @time:17.11.09
* @author:icesongqiang
*/

#include <stdio.h>

#include <stdlib.h>      // for srand()
#include <malloc.h>      // for malloc() && free()

#include <time.h>        // for time()
#include <math.h>        // for fabs()
#include <assert.h>      // for assert()

/**
* 区分一次项和常数项， 按公式递推
* 可以再优化，只保留上两次的系数，不用保留所有的
* n: n阶多项式 int  
* coefficient： 保存函数的系数 double *
*/
void process(int n, double *coefficient)
{
	double *primary = (double *)malloc((n + 1)*sizeof(double));
	double *constant = (double *)malloc((n + 1)*sizeof(double));

	for (int i = 0; i <= n; ++i){
		if (0 == i){
			*(primary + i) = 0;
			*(constant + i) = 1;
		}else if (1 == i){
			*(primary + i) = 1;
			*(constant + i) = 0;
		}else{
			//iteration
			*(primary + i) = (2 * i - 1) - *(primary + i - 1) - *(primary + i - 2)*(i - 1) / i;
			*(constant + i) = - *(constant + i - 1) - *(constant + i - 2) * (i - 1) / i;
		}
	}

	*coefficient = *(primary + n);
	*(coefficient + 1) = *(constant + n);

	for (int i = 0; i <= n; ++i){
		*(primary + i) = NULL;
		*(constant + i) = NULL;
	}
	free(primary);
	free(constant);

	return;
}

/**
***迭代法***
* n 阶 求函数值
* 0. 先求系数
* 1. 在计算函数值
*/
double poly_it(int n, double x){
	
	double coe[2] = { 0, 0 };
	process(n, coe);

	return *coe * x + *(coe + 1);
}

/**
***递归法***
* 根据定义调用函数即可
*/
double poly_re(int n, double x){
	if (n == 0) return(1);
	else if (n == 1) return(x);
	else return((2 * n - 1)*x - poly_re(n - 1, x) - (n - 1)*poly_re(n - 2, x) / n);
}

int main()
{
	const int MAX_X = 20;
	const int MAX_N = 10;
	int i = 100;
	srand((unsigned)time(0));
	int count = 0;
	while(i--){
		double x = int(rand()) % MAX_X;
		int n = int(rand()) % MAX_N;
		double ans = poly_it(n, x);
		double ans1 = poly_re(n, x);
		if (fabs(ans-ans1)<1e-6){
			printf("x = %lf, n= %d, ans = %lf\n", x, n, ans);
		}else{
			++count;
			printf("x = %lf, n= %d, ans = %lf, ans1 = %lf\n", x, n, ans, ans1);
		}
	}
	
	printf("\n %d error(s).\n", count);

	system("pause");

	return 0;

}
