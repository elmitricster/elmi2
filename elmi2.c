#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>


#define BUFFER_SIZE 100

int main(void)
{
	HANDLE ReadHandle;
	int buffer[BUFFER_SIZE], i = 0;
	double *avg = (double*)calloc(1, sizeof(double));
	double temp, std, sum = 0;
	DWORD read;

	//파이프의 읽기 핸들을 얻는다
	ReadHandle = GetStdHandle(STD_INPUT_HANDLE);

	//자식이 파이프로부터 읽는다
	if (ReadFile(ReadHandle, buffer, sizeof(int)*BUFFER_SIZE, &read, NULL))
	{
		printf("프로세스 C로 100개 숫자 전달받음\n");
	}
	else
		fprintf(stderr, "Child: Error reading from pipe\n");

	if (ReadFile(ReadHandle, avg, sizeof(double), &read, NULL))
	{

		for (i = 0; i < 100; i++)
		{
			temp = (buffer[i] - *avg)*(buffer[i] - *avg);
			sum = sum + temp;
		}
		std = sqrt(sum / 100);
		printf("표준편차 : %lf\n", std);
	}
	else
		fprintf(stderr, "Child: Error reading from pipe\n");


	return 0;
}