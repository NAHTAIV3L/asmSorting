#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <random>
#include "BenchmarkTimer.h"


#define MYSORTCPP
#define MYSORT
#define NUMBER_ROUNDS l

#pragma region
#ifdef MYSORT
	#define MYSORT 1
#endif
#ifdef BUBBLESORTCPP
	#define BUBBLESORTCPP 1
#endif
#ifdef BUBBLESORT
	#define BUBBLESORT 1
#endif
#ifdef BUCKETSORT
	#define BUCKETSORT 1
#endif
#ifdef MYSORTCPP
	#define MYSORTCPP 1
#endif

#if MYSORT
	#define SORT1 mysort(arry, len)
	#define SORT1STRN "My Sort:\n"
	#define SORT1STR "My Sort:"
	#if BUCKETSORT
		#define SORT2 bucketsort(arry2, arry3, bucketarray, output)
		#define SORT2STRN "Bucket Sort:\n"
		#define SORT2STR "Bucket Sort:"
	#elif BUBBLESORT
		#define SORT2 bubblesort(arry2, len)
		#define SORT2STRN "Bubble Sort:\n"
		#define SORT2STR "Bubble Sort:"
	#elif BUBBLESORTCPP
		#define SORT2 bubblesortcpp(arry2, len)
		#define SORT2STRN "Bubble Sort(C++):\n"
		#define SORT2STR "Bubble Sort(C++):"
	#elif MYSORTCPP
		#define SORT2 mysortcpp(arry2, len)
		#define SORT2STRN "My Sort(C++):\n"
		#define SORT2STR "My Sort(C++):"
	#endif
#elif BUBBLESORT && !MYSORT
	#define SORT1 bubblesort(arry, len)
	#define SORT1STRN "Bubble Sort:\n"
	#define SORT1STR "Bubble Sort:"
	#if BUBBLESORTCPP
		#define SORT2 bubblesortcpp(arry2, len)
		#define SORT2STRN "Bubble Sort(C++):\n"
		#define SORT2STR "Bubble Sort(C++):"
	#elif BUCKETSORT
		#define SORT2 bucketsort(arry2, arry3, bucketarray, output)
		#define SORT2STRN "Bucket Sort:\n"
		#define SORT2STR "Bucket Sort:"
	#elif MYSORTCPP
		#define SORT2 mysortcpp(arry2, len)
		#define SORT2STRN "My Sort(C++):\n"
		#define SORT2STR "My Sort(C++):"
	#endif
#elif BUBBLESORTCPP && !BUBBLESORT && !MYSORT
	#define SORT1 bubblesortcpp(arry, len)
	#define SORT1STRN "Bubble Sort(C++):\n"
	#define SORT1STR "Bubble Sort(C++):"
	#if BUCKETSORT
		#define SORT2 bucketsort(arry2, arry3, bucketarray, output)
		#define SORT2STRN "Bucket Sort:\n"
		#define SORT2STR "Bucket Sort:"
	#elif MYSORTCPP
		#define SORT2 mysortcpp(arry2, len)
		#define SORT2STRN "My Sort(C++):\n"
		#define SORT2STR "My Sort(C++):"
	#endif
#elif BUCKETSORT && !BUBBLESORT && !MYSORT && !BUBBLESORTCPP
	#define SORT2 bucketsort(arry2, arry3, bucketarray, output)
	#define SORT2STRN "Bucket Sort:\n"
	#define SORT2STR "Bucket Sort:"
	#if MYSORTCPP
		#define SORT1 mysortcpp(arry, len)
		#define SORT1STRN "My Sort(C++):\n"
		#define SORT1STR "My Sort(C++):"
	#endif
#else
#define SORT1 printf("Forgot to decide which sorts to use")
#define SORT2 printf("Forgot to decide which sorts to use")
#define SORT1STR "ERROR: Forgot to decide which sorts to use "
#define SORT2STR "ERROR: Forgot to decide which sorts to use "
#define SORT1STRN "ERROR\n"
#define SORT2STRN "ERROR\n"
#endif
#pragma endregion

inline void PrintArray(uint8_t* arry, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		if (i == size - 1)
		{
			printf("%hhu", arry[i]);
		}
		else
		{
			printf("%hhu, ", arry[i]);
		}
	}
}

void mysortcpp(uint8_t* inputarray, uint64_t length)
{
	uint8_t* ptrlarge = inputarray;
	uint8_t largevalue = 0;
	uint8_t newvalue = 0;
	for (int l = length - 1; l > 0; l--)
	{
		ptrlarge = inputarray;
		largevalue = *ptrlarge;
		for (uint64_t i = 0; i < l+1; i++)
		{
			newvalue = inputarray[i];
			if (newvalue > largevalue)
			{
				ptrlarge = &inputarray[i];
				largevalue = *ptrlarge;
			}
			else {}
		}
		*ptrlarge = newvalue;
		inputarray[l] = largevalue;
	}
}

void  bubblesortcpp(uint8_t* inputarray, int length)
{
	if (length <= 1) { return; }

	bool done = false;

	while (!done)
	{
		done = true;
		for (int i = 0; i < length; i++)
		{
			if (inputarray[i] > inputarray[i + 1])
			{
				uint8_t temp = inputarray[i + 1];
				inputarray[i + 1] = inputarray[i];
				inputarray[i] = temp;
				done = false;
			} else { }
		}
	}
}

extern "C" void mysort(uint8_t * inputarray, uint64_t lenght);
extern "C" void bubblesort(uint8_t* inputarray, uint64_t length);
extern "C" void bucketsort(uint8_t* inputarray, uint8_t* outputarray, uint64_t* bucketarray, uint64_t length);
extern "C" void lshift32timesandcombine(uint32_t, uint32_t, uint64_t*);


uint32_t random32(uint32_t& state)
{
	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
	return state;
}

inline void SetArrayRandom(uint8_t* arry, uint32_t size)
{
	uint32_t seed = rand();
	for (uint32_t i = 0; i < size; i++)
	{
		arry[i] = random32(seed) % 256;
	}
}

int main()
{
	srand(time(NULL));
	uint32_t seed = rand();
	uint16_t l = -1;
	uint32_t len = NUMBER_ROUNDS;
	

	
	//***Bubblesort worst case***
	//for (int i = 0; i < len; i++)
	//{
	//	arry[i] = len - i;
	//}

	uint8_t* arry = (uint8_t*)malloc(len * sizeof(uint8_t));
	if (arry == nullptr) { return 1; }
	SetArrayRandom(arry, len);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	//		array allocation	   //
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//

	uint8_t* arry2 = (uint8_t*)malloc(len * sizeof(uint8_t));
	if (arry2 == nullptr) { return 1; }
	memcpy(arry2, arry, len);

#ifdef BUCKETSORT
	uint8_t* arry3 = (uint8_t*)malloc(len * sizeof(uint8_t));
	if (arry3 == nullptr) { return 1; }
	memset(arry3, 0, len);
	
	uint64_t* bucketarray = (uint64_t*)malloc(10 * sizeof(uint64_t));
	if (bucketarray == nullptr) { return 1; }
	memset(bucketarray, 0, 10 * sizeof(uint64_t));
	
	uint32_t digits = 3;
	uint64_t output;
	lshift32timesandcombine(digits, len, &output);
#endif
	
	BenchmarkTimer timer1;
	BenchmarkTimer timer2;


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	//			 Sort 1		       //
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	printf(SORT1STRN);
	PrintArray(arry, len);
	printf("\n\n");

	timer1.Start();
	SORT1;
	timer1.End();

	PrintArray(arry, len);
	printf("\n\n");
	


	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	//			 Sort 2		       //
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	printf(SORT2STRN);
	PrintArray(arry2, len);
	
	printf("\n\n");
	
	timer2.Start();
	SORT2;
	timer2.End();

	
#if BUCKETSORT
	PrintArray(arry3, len);
#else
	PrintArray(arry2, len);
#endif
	printf("\n\n");

	printf(SORT1STR); timer1.Print();
	printf(SORT2STR); timer2.Print();

	free(arry);
	free(arry2);
#ifdef BUCKETSORT
	free(arry3);
	free(bucketarray);
#endif
	return 0;
}