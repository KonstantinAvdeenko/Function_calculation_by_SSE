#include <cstdio>
#include <cmath>
#include <ctime>
#include <malloc.h>
#include <xmmintrin.h> // описания MMX и SSE интринсики для возможности решать арифметические задачи параллельно
#include <stdarg.h>
#include <iostream> 
#include <windows.h>
#include <stdlib.h>
#include<process.h>

using namespace VitheslenieZnatheniiSPrimeneniemTehnologiiSSE;

    void ComputeArrayCppSSE(float* pArray1, float* pArray2, float* pArray3, float* pResult, int nSize) 
	   
    {  nSize = 70000; 
       int nLoop = nSize/ 4; // разделение всех элементов исходного массива на количество всех SSE регистров, где каждый регистр переменная по формуле
       __m128   m1, m2, m3, m4;
       __m128* pSrc1 = (__m128*) pArray1; //__m128* операнды инструкций SSE для загрузки в регистр содержащий 128 байт, если ЦП технологию поддерживает - pentium 4 и новее  
       __m128* pSrc2 = (__m128*) pArray2;
       __m128* pSrc3 = (__m128*) pArray3;
       __m128* pDest = (__m128*) pResult;
       __m128 m7_25 = _mm_set_ps1(7.25f); // заполнение всех регистров числами из формулы, для параллельных операций с ними  
	   __m128 m0_7 = _mm_set_ps1(0.7f);
	   __m128 m5_0 = _mm_set_ps1(5.0f);
       __m128 m8_7 = _mm_set_ps1(8.7f);
	   
       for ( int i = 0; i < nLoop; i++ )
       {// для всех элементов массива каждого регистра выполнение формулы 7.25 * z * x - 0.7 - 5 / z * y + 8.7 * y * z
          m1 = _mm_mul_ps(m7_25, *pSrc3); // 7.25 * z
          m1 = _mm_mul_ps(m1,*pSrc1); //  m1 * x
          m2 = _mm_sub_ps(m1,m0_7);  // m1 - 0.7   
          m3 = _mm_div_ps(m5_0,*pSrc3);  // 5.0 / z       
          m3 = _mm_mul_ps(m3,*pSrc2);  // m3 * y
	      m4 = _mm_mul_ps(m8_7,*pSrc2); // 8.7 * y
	      m4 = _mm_mul_ps(m4,*pSrc3); // m4 * z
          m2 = _mm_sub_ps(m1,m3); // (7.25 * z * x) - (5 / z * y)
          *pDest = _mm_add_ps(m2, m4); // m2 + 8.7 * y * z 
          pSrc1++;
          pSrc2++;
          pSrc3++;
          pDest++;
       }   
       printf("Результат вычисления формулы используя все элементы массива: %d\n", pDest - nLoop);
    }
    void init(float* a, int size)	
    { // инициализация всех элементов массива синусоидой рандомных чисел
       for(int i = 0; i < size; i++)
       {
          float x = (float)rand()/RAND_MAX;
          a[i] = sin(x);
       }
    }
    
	int main(int argc, TCHAR* argv[])
		
    {
       setlocale(LC_ALL, "Russian"); // подключение возможности работы с русским языком
       const int MAX_SIZE = 70000; // количество элементов массива 
       float *a = (float*)_aligned_malloc(sizeof(float)*MAX_SIZE, 16); // каждый элемент массива должен занимать 16 байт для возможности его корректной загрузки в регистр SSE
       float *b = (float*)_aligned_malloc(sizeof(float)*MAX_SIZE, 16);
       float *c = (float*)_aligned_malloc(sizeof(float)*MAX_SIZE, 16);
       float *f = (float*)_aligned_malloc(sizeof(float)*MAX_SIZE, 16);
       DWORD startTime, endTime; // таймер чтобы засечь время инициализации массивов и выполнения задачи
       startTime = GetTickCount();
       init(a, MAX_SIZE); // инициализированный массив где каждый элемент массива должен занимать 16 байт 
       init(b, MAX_SIZE); // 3 массива 3 переменных по формуле
       init(c, MAX_SIZE);
       endTime = GetTickCount();
       printf("Инициализация массивов: %d мс\n", endTime - startTime);
       startTime = GetTickCount();
       ComputeArrayCppSSE(a, b, c, f, MAX_SIZE);
       endTime = GetTickCount();
       printf("Вычисление средствами SSE: %d мс\n", endTime - startTime);
       _aligned_free(a); // очистка выделенных блоков памяти для средств SSE
       _aligned_free(b);
       _aligned_free(c);
       _aligned_free(f);
	   system("pause");
       return 0;
    }