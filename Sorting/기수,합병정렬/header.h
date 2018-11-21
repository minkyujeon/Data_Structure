#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

void random(int arr[]);
void BubbleSort(int * arr, int n); //버블
void merge(int arr[],int left, int mid, int right);//두 배열 합치기
void MergeSort(int arr[], int left, int right);//합병
void RadixSort(int*arr, int n);//기수
void sorted(int arr[]); //출력
