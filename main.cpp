#include<stdio.h>
#include<time.h>
#include<cstdlib>
struct BIGNUM{
	int n;
	short num[50];
};
BIGNUM TaoBigNum(int n){
	BIGNUM a;
	a.n = n;
	a.num[0] = rand() % 10;
	if (a.num[0] == 0){
		a.num[0]++;
	}
	for (int i = 1; i<a.n; i++){
		a.num[i] = rand() % 10;
	}
	return a;
}
int KiemTraLonHon_Int(void*a, void*b){
	return*(int*)a > *(int*)b;
}
int KiemTraLonHon_BigNum(void*a, void*b){
	if (*(int*)a > *(int*)b){
		return 1;
	}
	else if (*(int*)a < *(int*)b){
		return 0;
	}
	else{
		for (int i = 0; i < *(int*)a; i++){
			char*c = (char*)a + sizeof(int)+i*sizeof(short);
			char*d = (char*)b + sizeof(int)+i*sizeof(short);
			if (*(short*)c>*(short*)d){
				return 1;
			}
			else if (*(short*)c < *(short*)d){
				return 0;
			}
		}
		return 0;
	}
}
void Equal(void*a, void* b,int size){//phep gan
	for (int i = 0; i<size; i++){
		*((char*)a + i) = *((char*)b + i);
	}
}
void Swap_Int(void*a, void*b){
	int c = *(int*)a;
	*(int*)a = *(int*)b;
	*(int*)b = c;
}
void Swap_BigNum(void*a, void*b){
	BIGNUM c;
	Equal(&c, a, sizeof(BIGNUM));
	Equal(a, b, sizeof(BIGNUM));
	Equal(b, &c, sizeof(BIGNUM));
}
void* ChiaThapPhan_Int(void*a, int exp){
	int *c=new int[1];
	*c = *(int*)a / exp;
	return c;
}
void* ChiaThapPhan_BigNum(void*a, int exp){
	BIGNUM*c = new BIGNUM[1];
	Equal(c, a, sizeof(BIGNUM));
	int i;
	for (i = 0;; i++){
		if (exp == 1){
			break;
		}
		exp /= 10;
	}
	*(int*)c -= i;
	return c;
}
int* ModThapPhan_Int(void* a, int exp){
	int*c=new int[1];
	*c = *(int*)a % exp;
	return c;
}
int*ModThapPhan_BigNum(void*a, int exp){
	int *c = new int[1];
	for (int i = *(int*)a - 1; i >= 0; i--){
		*c = *(short*)((char*)a + sizeof(int)+i*sizeof(short));
		if (exp == 10){
			return c;
		}
		exp /= 10;
	}
	*c = 0;
	return c;
}
int DieuKien_Int(void*DieuKien, void*a, int exp){
	return *(int*)ChiaThapPhan_Int(a, exp);
}
int DieuKien_BigNum(void*DieuKien, void*a, int exp){
	return --*(int*)DieuKien;
}
void Merge(void* a, int left, int mid, int right,int size,int(*KiemTra)(void*,void*),void(*Swap)(void*,void*)){
	void *temp; // Khoi tao mang tam de sap xep
	int i = left; // Vi tri phan tu dau tien cua mang con ben trai
	int j = mid + 1; // Vi tri phan tu dau tien cua mang con ben phai

	temp = new char[(right - left + 1)*size]; // Khoi tao so luong phan tu cua mang tam

	for (int k = 0; k <= right - left; k++)
	{
		char*a_i = (char*)a + i*size;
		char*a_j = (char*)a + j*size;
		// Kiem phan tu cua mang con ben trai va ben phai
		if (KiemTra(a_j,a_i))//a[i]<a[j]
		{
			// Neu a[i] < a[j] thi copy phan tu ben trai vao mang tam
			char*temp_k = (char*)temp + k*size;
			Equal(temp_k, a_i, size);
			i++; // Vi tri phan tu tiep theo cua mang
		}
		else // Nguoc lai copy phan tu cua mang con ben phai vao mang tam
		{
			char*temp_k = (char*)temp + k*size;
			Equal(temp_k, a_j, size);
			j++; // Vi tri phan tu tiep theo cua mang
		}

		// Kiem tra mang con ben trai con phan tu nao khong
		if (i == mid + 1)
		{
			// Nguoc lai dua cac phan tu con lai cua mang con ben phai vao mang tam
			while (j <= right)
			{
				a_j = (char*)a + j*size;
				k++;
				char*temp_k = (char*)temp + k*size;
				Equal(temp_k, a_j, size);
				j++;
			}
			break;
		}

		// Kiem tra mang con ben phai con phan tu nao khong
		if (j == right + 1)
		{
			// Nguoc lai dua cac phan tu con lai cua mang con ben phai vao mang tam
			while (i <= mid)
			{
				a_i = (char*)a + i*size;
				k++;
				char*temp_k = (char*)temp + k*size;
				Equal(temp_k, a_i, size);
				i++;
			}
			break;
		}
	}

	for (int k = 0; k <= right - left; k++){ // Chep mang tam vao mang chinh
		Equal((char*)a + (left + k)*size, (char*)temp + k*size, size);
	}
	delete temp;
}
void heapify(void *a, int n, int i, int size, int(*KiemTra)(void*,void*),void(*Swap)(void*,void*))
{
	int max = i;  
	int l = 2 * i + 1;  
	int r = 2 * i + 2;  
	char* a_l = (char*)a + l*size;
	char* a_r = (char*)a + r*size;
	char* a_max = (char*)a + max*size;
	if (l < n && KiemTra(a_l, a_max)){//a[l] > a[max]
		max = l;
		a_max = (char*)a + max*size;
	}
	if (r < n && KiemTra(a_r, a_max)){//a[r] > a[max]
		max = r;
		a_max = (char*)a + max*size;
	}
	if (max != i)
	{
		char* a_i = (char*)a + i*size;
		Swap(a_i, a_max);
		heapify(a, n, max,size,KiemTra,Swap);
	}
}
void HeaSort(void *a, int n, int size, int(*KiemTra)(void*,void*), void(*Swap)(void*,void*))
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(a, n, i,size,KiemTra,Swap);
	for (int i = n - 1; i >= 0; i--)
	{
		char*a_i = (char*)a + i*size;
		Swap(a_i, a);
		heapify(a, i, 0,size,KiemTra,Swap);
	}
}
void InsSort(void *a,int size, int n,int(*KiemTra)(void*,void*),void(*Swap)(void*,void*)){
	for (int i = 0; i <n ; i++){
		char*a_i = (char*)a + i*size;
		for (int j = 0; j < i; j++){
			char*a_j = (char*)a + j*size;
			if (KiemTra(a_j,a_i)){
				void* c=new char[size];
				Equal(c,a_i, size);
				for (int k = i; k>j; k--){
					char*a_k = (char*)a + k*size;
					Swap(a_k,a_k-size);
				}
				Swap(a_j, c);
				delete[]c;
			}
		}
	}
}
void BubSort(void* a, int size, int n, int(*KiemTra)(void*, void*), void(*Swap)(void*, void*)){
	for (int i = 0; i < n-1; i++){
		char*a_i = (char*)a + i*size;
		for (int j = 0; j < n-i-1; j++){
			char*a_j = (char*)a + j*size;
			if (KiemTra(a_j,a_j+size)){
				Swap(a_j + size, a_j);
			}
		}
	}
}
void ShaSort(void* a, int size, int n, int(*KiemTra)(void*, void*), void(*Swap)(void*, void*)){
	int left, right;
	left = 0;
	right = n - 1;
	int k = 0;
	while (left < right){
		for (int i = left; i < right; i++){
			char*a_i = (char*)a + i*size;
			if (KiemTra(a_i,a_i+size)){
				Swap(a_i, a_i + size);
				k = i;
			}
		}
		right=k;
		for (int i = right; i >left; i--){
			char*a_i = (char*)a + i*size;
			if (KiemTra(a_i - size, a_i)){
				Swap(a_i, a_i - size);
				k = i;
			}
		}
		left=k;
	}
}
void QuiSort(void* a, int left, int right, int size, int(*KiemTra)(void*, void*), void(*Swap)(void*, void*)){
	int i, j;
	i = left;
	j = right;
	void* x = new char[size];
	Equal(x, (char*)a + (left + right) / 2 * size,size);
	do{
		char*a_i = (char*)a + i*size;
		while (KiemTra(x, a_i)){ 
			i++; 
			a_i = (char*)a + i*size;
		}
		char*a_j = (char*)a + j*size;
		while (KiemTra(a_j,x)){
			j--;
			a_j = (char*)a + j*size;
		}
		if (i <= j){
			Swap(a_i, a_j);
			i++;
			j--;
		}
	} while (i < j);
	if (left < j){
		QuiSort(a, left, j,size,KiemTra,Swap);
	}
	if (right>i){
		QuiSort(a, i, right,size,KiemTra,Swap);
	}
}
void MerSort(void* a, int left, int right,int size,int(*KiemTra)(void*,void*),void(*Swap)(void*,void*)){
	int mid = (left + right) / 2;
	if (left < right){
		MerSort(a, left, mid,size,KiemTra,Swap);
		MerSort(a, mid+1, right,size,KiemTra,Swap);
		Merge(a, left, mid, right,size,KiemTra,Swap);
	}
}
void SheSort(void* a, int n, int size, int(*KiemTra)(void*, void*), void(*Swap)(void*, void*)){
	for (int step = n / 2; step>0; step /= 2){
		for (int i = step; i < n; i++){
			char*c = new char[size];
			char*a_i = (char*)a + i*size;
			//c=a[i]
			Equal(c, a_i, size);
			int j;
			for (j = i; j >= step && KiemTra((char*)a + (j - step)*size,c); j -= step){//c < a[j - step]
				//a[j] = a[j-step]
				char*a_j = (char*)a + j*size;
				Equal(a_j, (char*)a+(j-step)*size, size);
			}
			//a[j] = c
			char*a_j = (char*)a + j*size;
			Equal(a_j, c, size);
			delete[]c;
		}
	}
}
void RadSort(void *a, int n, int size, int(*KiemTra)(void*, void*), void(*Swap)(void*, void*),void*(*ChiaThapPhan)(void*,int),int*(*Mod)(void*,int),int(*DieuKien)(void*,void*,int)){
	int i,exp=1;
	//, m = a[0]
	char*m = new char[size];
	Equal(m, a, size);
	//Tao mang b
	char*b = new char[n*size];
	for (i = 0; i < n; i++)
	{
		char*a_i = (char*)a + i*size;
		if (KiemTra(a_i,m))//a[i] > m
			Equal(m, a_i, size);
	}
	int*Dieu_Kien = (int*)ChiaThapPhan(m, exp);
	while (*Dieu_Kien > 0)
	{
		int bucket[10] = { 0 };
		for (i = 0; i < n; i++){
			char*a_i = (char*)a + i*size;
			//bucket[a[i] / exp % 10]++;
			bucket[*Mod(ChiaThapPhan(a_i, exp), 10)]++;
		}
		for (i = 1; i < 10; i++){
			bucket[i] += bucket[i - 1];
		}
		for (i = n - 1; i >= 0; i--){
			char*a_i = (char*)a + i*size;
			//b[--bucket[a[i]/exp % 10]] = a_i;
			int d = --bucket[*Mod(ChiaThapPhan(a_i, exp), 10)];
			Equal(b+d*size, a_i, size);
		}
		for (i = 0; i < n; i++){
			char*a_i = (char*)a + i*size;
			char*b_i = (char*)b + i*size;
			//a[i] = b[i];
			Equal(a_i, b_i, size);
		}
		exp *= 10;
		*Dieu_Kien = DieuKien(Dieu_Kien,m, exp);
	}
	delete[]Dieu_Kien;
	delete[]b;
}
void XuatMang_Int(int* a, int n){
	for (int i = 0; i < n; i++){
		printf("%8d", a[i]);
	}
	printf("\n");
}
void XuatMang_BigNum(BIGNUM *a,int n, int max_lenght){
	int ConsoleWidth = 120;
	for (int i = 0; i < n; i++){
		ConsoleWidth -= max_lenght + 1;
		for (int k = 0; k <= max_lenght-a[i].n; k++){
			printf(" ");
		}
		for (int j = 0; j < a[i].n; j++){
			printf("%d", a[i].num[j]);
		}
		if (ConsoleWidth < max_lenght + 1){
			printf("\n");
			ConsoleWidth = 120;
		}
	}
	printf("\n");
}
int SoPhanTu(){
	int i;
	int n;
	printf("Cac bo so\n1: 100 phan tu\n2: 1000 phan tu\n3: 10000 phan tu\n4: 100000 phan tu\n5: 1000000 phan tu\nBan chon bo so: ");
	scanf_s("%d", &i);
	switch (i){
		case 1:{
			   n = 10;
			   return n;
			}
		case 2:{
			   n = 1000;
			   return n;
			}
		case 3:{
			   n = 10000;
			   return n;
			}
		case 4:{
				   n = 100000;
				   return n;
		}
		default:{
				n = 1000000;
				return n;
			}
	}
}
int* TaoMang_Int(int n){
	int*a = new int[n];
	return a;
}
BIGNUM* TaoMang_BigNum(int n){
	BIGNUM*a = new BIGNUM[n];
	return a;
}
void NhapMang_Int(int*&a, int n){
	for (int i = 0; i < n; i++){
		a[i] = rand();
	}
}
void NhapMang_BigNum(BIGNUM*&a, int n, int max_lenght){
	for (int i = 0; i < n; i++){
		int l = rand() % max_lenght + 1;
		a[i] = TaoBigNum(l);
	}
}
void XoaMang_Int(int*a){
	delete[]a;
}
void XoaMang_BigNum(BIGNUM*a){
	delete[]a;
}
void SapXep(void*a, int n, int i, int size, int(*KiemTra)(void*, void*), void(*Swap)(void*, void*), void*(*Div)(void*, int), int*(*Mod)(void*, int), int(*DieuKien)(void*, void*, int)){
	switch (i){
	case 1:{
			   HeaSort(a, n, size, KiemTra, Swap);
			   break;
	}
	case 2:{
			   InsSort(a,size ,n,KiemTra,Swap);
			   break;
	}
	case 3:{
			   BubSort(a,size, n,KiemTra,Swap);
			   break;
	}
	case 4:{
			   ShaSort(a,size, n,KiemTra,Swap);
			   break;
	}
	case 5:{
			   QuiSort(a, 0, n - 1,size,KiemTra,Swap);
			   break;
	}
	case 6:{
			   MerSort(a, 0, n - 1, size, KiemTra, Swap);
			   break;
	}
	case 7:{
			   SheSort(a, n, size, KiemTra, Swap);
			   break;
	}
	default:{
				RadSort(a, n, size, KiemTra, Swap, Div, Mod,DieuKien);
				break;
		}
	}
}
void main(){
	clock_t start, end;
	double runtime;
	int n, mode;
	int*A;
	BIGNUM*B;
	int max_lenght;
	//Tao bo dem ngau nhien
	srand(time(NULL));
	//Chon loai mang
	printf("Chuong trinh gom 2 loai so:\n1: So nguyen kieu Int\n2: So nguyen rat lon\nBan chon loai: ");
	scanf_s("%d", &mode);
	n = SoPhanTu();
	//Tao Mang
	if (mode == 1){//Mang Int
		A = TaoMang_Int(n);
		NhapMang_Int(A, n);
		XuatMang_Int(A, n);
		int i;
		printf("Cac thuat toan sap xep:\n1: Heap Sort\n2: Insert Sort\n");
		printf("3: Bubble Sort\n4: Shaker Sort\n5: Quick Sort\n6: Merge Sort\n7: Shell Sort\n8: Radix Sort\n");
		printf("Ban chon kieu sap xep: ");
		scanf_s("%d", &i);
		start = clock();
		SapXep(A, n, i, sizeof(int), KiemTraLonHon_Int, Swap_Int, ChiaThapPhan_Int, ModThapPhan_Int,DieuKien_Int);
		end = clock();
		runtime = (double)(end - start) / CLOCKS_PER_SEC;
		XuatMang_Int(A, n);
		delete[]A;
	}
	else{//Mang BigNum
		printf("So lon nhat chuong trinh co the thuc hien la 50 chu so\nBan muon so lon nhat co bao nhieu chu so: ");
		scanf_s("%d", &max_lenght);
		B = TaoMang_BigNum(n);
		NhapMang_BigNum(B, n, max_lenght);
		XuatMang_BigNum(B, n, max_lenght);
		int i;
		printf("Cac thuat toan sap xep:\n1: Heap Sort\n2: Insert Sort\n");
		printf("3: Bubble Sort\n4: Shaker Sort\n5: Quick Sort\n6: Merge Sort\n7: Shell Sort\n8: Radix Sort\n");
		printf("Ban chon kieu sap xep: ");
		scanf_s("%d", &i);
		start = clock();
		SapXep(B, n, i, sizeof(BIGNUM), KiemTraLonHon_BigNum, Swap_BigNum, ChiaThapPhan_BigNum, ModThapPhan_BigNum,DieuKien_BigNum);
		end = clock();
		runtime = (double)(end - start) / CLOCKS_PER_SEC;
		XuatMang_BigNum(B, n, max_lenght);
		delete[]B;
	}
	printf("thoi gian chay: %0.5lf\n", runtime);
	system("pause");
}