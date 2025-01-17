#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

void print(int *array, int length){
	for(int i=0; i<length; i++)
		cout << array[i] << " ";
	cout << endl;
}

void print(double *array, int length){
	for(int i=0; i<length; i++)
		cout << array[i] << " ";
	cout << endl;
}

void print(int *array, int i, int f){
	for(;i<=f; i++)
		cout << array[i] << " ";
	cout << endl;
}

void swap(int *x, int *y){
	int a = *x;
	*x = *y;
	*y = a;
}

void insertionSort(int *array, int length){
	
	for(int i=0; i<length-1; i++){
		for(int j=i+1; j>0; j--){
			if(array[j] < array[j-1])
				swap(array+j, array+j-1);
		}
	}
	
}

void selectionSort(int *array, int length){
	
	int indexLower;
	for(int i=0; i<length; i++){
		indexLower = i;
		for(int j=i; j<length; j++){
			if(array[j] < array[indexLower]){
				indexLower = j;
			}
		}
		swap(array+i, array+indexLower);
	}
	
}


// merge sort
void intercala(int *array, int i, int q, int f){
	int n = f-i+1;
	int arr[n];
	for(int k=0; k<=q-i; k++){
		arr[k] = array[i+k];
	}
	for(int k=1; k<=f-q; k++){
		arr[n-k] = array[q+k];
	}
	
	int iArr = 0;
	int fArr = n-1;
	for(int k=i; k<=f; k++){
		 if(arr[iArr] <= arr[fArr]){
		 	array[k] = arr[iArr++];
		 }else{
		 	array[k] = arr[fArr--];
		 }
	}
}

void mergeSort(int *array, int indexInit, int indexFinal){
	if(indexInit >= indexFinal)
		return;
	
	int q = indexInit + (indexFinal-indexInit)/2;
	
	mergeSort(array, indexInit, q);
	mergeSort(array, q+1, indexFinal);
	intercala(array, indexInit, q, indexFinal);
}

void mergeSortCall(int *array, int n){
	mergeSort(array, 0, n-1);
}


// quick sort
int partition(int *array, int low, int high){
	int pivot = array[high];
	
	int i = low-1;
	
	for(int j=low; j<high; j++){
		if(array[j] <= pivot){
			swap(array + ++i, array+j);
		}
	}
	
	swap(array + ++i, array+high);
	return i;
}

void quickSort(int *array, int low, int high){
	
	if(high > low || low < 0){
		int p = partition(array, low, high);
		quickSort(array, low, p-1);
		quickSort(array, p+1, high);
	}
	
}

void quickSortCall(int *array, int n){
	quickSort(array, 0, n-1);
}


// heap sort
void heapfy(int *array, int i, int f){
	if(i >= f)
		return;
		
	int leftChild = 2*i+1;
	int rightChild = 2*i+2;
	
	if(leftChild > f)
		return;
		
	if(leftChild == f){
		if(array[leftChild] > array[i])
			swap(array+leftChild, array+i);
		
		return;
	}
	
	heapfy(array, leftChild, f);
	heapfy(array, rightChild, f);
	
	if(array[leftChild] >= array[rightChild]){
		if(array[leftChild] > array[i]){
			swap(array+leftChild, array+i);
			heapfy(array, leftChild, f);
		}
	}else{
		if(array[rightChild] > array[i]){
			swap(array+rightChild, array+i);
			heapfy(array, rightChild, f);
		}
	}
}

void heapSort(int *array, int length){
	
	for(int f = length-1; f > 0; f--){
		heapfy(array, 0, f);
		swap(array, array+f);
	}
	
}

double clock_to_sec(clock_t initial_clock, clock_t final_clock) {
	double t = (double) final_clock - (double) initial_clock;
	return t/CLOCKS_PER_SEC;
}

double get_time(int *array, int length, void (*sort)(int *,int)) {
	
	clock_t initial_clock = clock();
	sort(array, length);
	clock_t final_clock = clock();
	
	return clock_to_sec(initial_clock, final_clock);
}

void fill_array(int *array, int length) {
	for(int i=0; i<length; i++)
		array[i] = rand();
}

double get_mean(double *array, int length) {
	double sum = 0;
	
	for(int i=0; i<length; i++)
		sum += array[i];
		
	return sum/length;
}

double get_sd(double *array, int length) {
	double mean = get_mean(array, length);
	
	double sum = 0;
	
	for(int i=0; i<length; i++){
		double deviation = mean - array[i];
		sum += deviation * deviation;
	}
	
	return sqrt(sum/(length-1));
}

double** get_data(int qtdd, int length) {

	double timesInsertionSort[qtdd];
	double timesSelectionSort[qtdd];
	double timesMergeSort[qtdd];
	double timesQuickSort[qtdd];
	double timesHeapSort[qtdd];
	
	int array[length];
	
	for(int i=0; i<qtdd; i++) {
		cout << "i = " << i << endl;
		fill_array(array, length);
		timesInsertionSort[i] = get_time(array, length, &insertionSort);
		timesSelectionSort[i] = get_time(array, length, &selectionSort);
		timesMergeSort[i] = get_time(array, length, &mergeSortCall);
		timesQuickSort[i] = get_time(array, length, &quickSortCall);
		timesHeapSort[i] = get_time(array, length, &heapSort);
	}
	
	double **result = (double **)calloc(5, sizeof(double*));
	
	result[0] = (double*)calloc(2, sizeof(double));
	result[1] = (double*)calloc(2, sizeof(double));
	result[2] = (double*)calloc(2, sizeof(double));
	result[3] = (double*)calloc(2, sizeof(double));
	result[4] = (double*)calloc(2, sizeof(double));
	
	result[0][0] = get_mean(timesInsertionSort, qtdd);
	result[1][0] = get_mean(timesSelectionSort, qtdd);
	result[2][0] = get_mean(timesMergeSort, qtdd);
	result[3][0] = get_mean(timesQuickSort, qtdd);
	result[4][0] = get_mean(timesHeapSort, qtdd);
	
	result[0][1] = get_sd(timesInsertionSort, qtdd);
	result[1][1] = get_sd(timesSelectionSort, qtdd);
	result[2][1] = get_sd(timesMergeSort, qtdd);
	result[3][1] = get_sd(timesQuickSort, qtdd);
	result[4][1] = get_sd(timesHeapSort, qtdd);
	
	return result;
}

int main(){
	
	int length, qtdd;
	
	cin >> length >> qtdd;
	
	double **result = get_data(qtdd, length);
	
	cout << "Insertion Sort: " << endl;
	cout << "Media: " << result[0][0] << endl;
	cout << "Desvio Padrao: " << result[0][1] << endl << endl;
	
	cout << "Selection Sort: " << endl;
	cout << "Media: " << result[1][0] << endl;
	cout << "Desvio Padrao: " << result[1][1] << endl << endl;
	
	cout << "Merge Sort: " << endl;
	cout << "Media: " << result[2][0] << endl;
	cout << "Desvio Padrao: " << result[2][1] << endl << endl;
	
	cout << "Quick Sort: " << endl;
	cout << "Media: " << result[3][0] << endl;
	cout << "Desvio Padrao: " << result[3][1] << endl << endl;
	
	cout << "Heap Sort: " << endl;
	cout << "Media: " << result[4][0] << endl;
	cout << "Desvio Padrao: " << result[4][1] << endl << endl;
	
	return 0;
}







