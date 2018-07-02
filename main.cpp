#include<stdio.h>
#include<time.h>
#include<cstdlib>
void Merge(int* a, int left, int mid, int right){
	int* p;
	int i = left;
	int j = mid + 1;
	p = new int[right - left + 1];
	for (int k = 0; k < right - left; k++){
		//lay phan tu nho nhat dua vao mang tam
		if (a[i] < a[j]){
			p[k] = a[i];
			i++;
		}
		else{
			p[k] = a[j];
			j++;
		}
		//xem mang con 2 ben con phan tu nao khong?
		if (i == mid + 1){
			while (j <= right){
				k++;
				p[k] = a[j];
				j++;
			}
			break;
		}
		if (j == right){
			while (i <= mid){
				k++;
				p[k] = a[i];
				i++;
			}
			break;
		}
	}
	for (int k = 0; k < right - left; k++){
		a[left + k] = p[k];
	}
	delete[]p;
}
void heapify(int *a, int n, int i)
{
	int max = i;  
	int l = 2 * i + 1;  
	int r = 2 * i + 2;  
	if (l < n && a[l] > a[max])
		max = l;
	if (r < n && a[r] > a[max])
		max = r;
	if (max != i)
	{
		int temp = a[i];
		a[i] = a[max];
		a[max] = temp;
		heapify(a, n, max);
	}
}
void HeaSort(int *a, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(a, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		heapify(a, i, 0);
	}
}
void InsSort(int* a, int n){
	for (int i = 0; i <n ; i++){
		for (int j = 0; j < i; j++){
			if (a[j]>a[i]){
				int c = a[i];
				for (int k = i; k>j; k--){
					a[k] = a[k - 1];
				}
				a[j] = c;
			}
		}
	}
}
void BubSort(int* a, int n){
	for (int i = 0; i < n-1; i++){
		for (int j = 0; j < n-i-1; j++){
			if (a[j]>a[j + 1]){
				int c = a[j+1];
				a[j + 1] = a[j];
				a[j] = c;
			}
		}
	}
}
void ShaSort(int* a, int n){
	int left, right;
	left = 0;
	right = n - 1;
	int k;
	while (left < right){
		for (int i = left; i < right; i++){
			if (a[i]>a[i + 1]){
				int c = a[i + 1];
				a[i + 1] = a[i];
				a[i] = c;
				k = i;
			}
		}
		right=k;
		for (int i = right; i >left; i--){
			if (a[i]<a[i - 1]){
				int c = a[i - 1];
				a[i - 1] = a[i];
				a[i] = c;
				k = i;
			}
		}
		left=k;
	}
}
void QuiSort(int* a, int left,int right){
	int i, j, x;
	i = left;
	j = right;
	x = a[(left + right) / 2];
	do{
		while (a[i] < x)i++;
		while (a[j] > x)j--;
		int c = a[i];
		a[i] = a[j];
		a[j] = c;
		i++; 
		j--;
	} while (i < j);
	if (left < j){
		QuiSort(a, left, j);
	}
	if (right>i){
		QuiSort(a, i, right);
	}
}
void MerSort(int* a, int left, int right){
	int mid = (left + right) / 2;
	if (left < right){
		MerSort(a, left, mid);
		MerSort(a, mid+1, right);
		Merge(a, left, mid, right);
	}
}
void SheSort(int* a, int n){
	for (int step = n / 2; step>0; step /= 2){
		for (int i = step; i < n; i++){
			int c = a[i];
			int j;
			for (j = i; j >= step && c < a[j - step]; j-=step){
				a[j] = a[j-step];
			}
			a[j] = c;
		}
	}
}
void RadSort(int *a, int n)
{
	int i, *b, m = a[0], exp = 1;
	b = new int[n];
	for (i = 0; i < n; i++)
	{
		if (a[i] > m)
			m = a[i];
	}
	while (m / exp > 0)
	{
		int bucket[10] = { 0 };
		for (i = 0; i < n; i++)
			bucket[a[i] / exp % 10]++;
		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (i = n - 1; i >= 0; i--)
			b[--bucket[a[i] / exp % 10]] = a[i];
		for (i = 0; i < n; i++)
			a[i] = b[i];
		exp *= 10;
	}
	delete[]b;
}
void XuatMang(int* a, int n){
	for (int i = 0; i < n; i++){
		printf("%8d", a[i]);
	}
	printf("\n");
}
void TaoMang(int*&a, int&n){
	int i;
	printf("Cac bo so\n1: 100 phan tu\n2: 1000 phan tu\n3: 10000 phan tu\n4: 100000 phan tu\n5: 1000000 phan tu\nBan chon bo so: ");
	scanf_s("%d", &i);
	switch (i){
		case 1:{
			   n = 100;
			   break;
			}
		case 2:{
			   n = 1000;
			   break;
			}
		case 3:{
			   n = 10000;
			   break;
			}
		case 4:{
				   n = 100000;
				   break;
		}
		default:{
				n = 1000000;
				break;
			}
	}
	a = new int[n];
}
void NhapMang(int*a, int n){
	for (int i = 0; i < n; i++){
		a[i] = rand();
	}
}
void XoaMang(int*&a){
	delete[]a;
}
void SapXep(int*a, int n,int i){
	switch (i){
	case 1:{
			   HeaSort(a, n);
			   break;
	}
	case 2:{
			   InsSort(a, n);
			   break;
	}
	case 3:{
			   BubSort(a, n);
			   break;
	}
	case 4:{
			   ShaSort(a, n);
			   break;
	}
	case 5:{
			   QuiSort(a, 0, n - 1);
			   break;
	}
	case 6:{
			   MerSort(a, 0, n - 1);
			   break;
	}
	case 7:{
			   SheSort(a, n);
	}
	default:{
				RadSort(a, n);
				break;
		}
	}
}
void main(){
	clock_t start, end;
	double runtime;
	int*A, n;
	srand(time(NULL));
	TaoMang(A, n);
	NhapMang(A, n);
	XuatMang(A, n);
	int i;
	printf("Cac thuat toan sap xep:\n1: Heap Sort\n2: Insert Sort\n");
	printf("3: Bubble Sort\n4: Shaker Sort\n5: Quick Sort\n6: Merge Sort\n7: Shell Sort\n8: Radix Sort\n");
	printf("Ban chon kieu sap xep: ");
	scanf_s("%d", &i);
	//tinh thoi gian ham sap xep
	start = clock();
	SapXep(A, n, i);
	end = clock();
	runtime = (double)(end - start)/CLOCKS_PER_SEC;
	XuatMang(A, n);
	XoaMang(A);
	printf("thoi gian chay: %0.5lf\n", runtime);
}