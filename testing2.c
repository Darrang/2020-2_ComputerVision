
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


int  main(){

    int arr[10]={1,1,2,2,2,3,3,4,4,4};

    int n = sizeof(arr) / sizeof(int);
	int i, j, mode, freq, count = 1;     //변수 초기화
	for (i = 0; i < n; i++)
	{
		freq = 1;                       //처음 숫자를 기준으로 하기 때문에 freq는 초기값 1을 가진다
		for (j = i + 1; j < n; j++)
		{
			if (arr[i] == arr[j]) //a[i]를 기준으로 a[j]수 들을 비교한다 ex) a[1] == a[2] , a[1] == a[3] ....
				freq += 1;    //a[i] = a[j]가 같을 경우 freq를 1증가 시킨다
		}

		if (freq >= count)    // 새로운 freq 수가 기존에 저장된 count 수 보다 클 경우
		{
			mode = arr[i];
			count = freq;
		}
	}

	printf("mode = %d, freq = %d \n", mode, count);
	return 0;


}