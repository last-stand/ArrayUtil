#include "expr_assert.h"
#include "arrayUtil.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

ArrayUtil util,expectedUtil;

int isDivisible(void* hint, void* item){
	int* _hint = (int*)hint;
	int* _item = (int*)item;
	return (*_item % *_hint) == 0 ? 1 : 0;
}

int match_Func(void* hint, void* item){
	char* _hint = (char*)hint;
	char* _item = (char*)item;
	return *_hint == *_item ? 1 : 0;
}

int is_CeillEven(void* hint, void* item){
	float* _item = (float*)item;
	int ceil_item = ceil(*_item);
	return (ceil_item % 2) == 0 ? 1 : 0;
}

int is_FloorEven(void* hint, void* item){
	double* _item = (double*)item;
	int ceil_item = floor(*_item);
	return (ceil_item % 2) == 0 ? 1 : 0;
}

void test_array_util_areEqual_returns_1_if_both_array_are_equal_in_length_and_elements(){
	int a[]={1,2,3,4,5};
	ArrayUtil a_array = {a,sizeof(int),5}, b_array = a_array;
	assertEqual(areEqual(a_array, b_array),1);
	dispose(a_array);
	dispose(b_array);
}

void test_array_util_areEqual_returns_0_if_both_array_are_not_equal_in_length_and_elements(){
	int a[]={0,3,8,5,2,3,4,5}, b[]={1,5,2,3,7};
	ArrayUtil a_array = {a,sizeof(int),8};
	ArrayUtil b_array = {b,sizeof(int),5};
	assertEqual(areEqual(a_array, b_array),0);
	dispose(a_array);
	dispose(b_array);
}

void test_create_should_returns_array_within_structure_with_given_typeSize(){
	ArrayUtil newArray = create(sizeof(int),5);
	assertEqual(newArray.typeSize,sizeof(int));
	dispose(newArray);
}

void test_create_should_returns_array_within_structure_with_given_length(){
	ArrayUtil newArray = create(sizeof(int),5);
	assertEqual(newArray.length,5);
	dispose(newArray);
}

void test_create_allocates_space_for_INT_array_and_assigns_zero_to_all_bytes(){
	int intArray[] = {0,0,0,0};
	expectedUtil.base = intArray;
	expectedUtil.typeSize = sizeof(int);
	expectedUtil.length = 4;
	util = create(sizeof(int),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
	dispose(expectedUtil);
}

void test_create_allocates_space_for_CHAR_array_and_assigns_zero_to_all_bytes(){
	char charArray[] = {0,0,0,0};
	expectedUtil.base = charArray;
	expectedUtil.typeSize = sizeof(char);
	expectedUtil.length = 4;
	util = create(sizeof(char),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
	dispose(expectedUtil);
}

void test_create_allocates_space_for_FLOAT_array_and_assigns_zero_to_all_bytes(){
	float floatArray[] = {0,0,0,0};
	expectedUtil.base = floatArray;
	expectedUtil.typeSize = sizeof(float);
	expectedUtil.length = 4;
	util = create(sizeof(float),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
	dispose(expectedUtil);
}

void test_create_allocates_space_for_DOUBLE_array_and_assigns_zero_to_all_bytes(){
	double doubleArray[] = {0,0,0,0};
	expectedUtil.base = doubleArray;
	expectedUtil.typeSize = sizeof(double);
	expectedUtil.length = 4;
	util = create(sizeof(double),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
	dispose(expectedUtil);
}

void test_resize_returns_INT_array_within_structure_with_new_allocated_space(){
	int array1[] = {1,2,3,4}, array2[]={1,2,3,4,0,0};
	ArrayUtil resizedArray;
	util = create(sizeof(int),4);
	util.base = array1;
	resizedArray = resize(util,6);

	expectedUtil = create(sizeof(int),6);
	expectedUtil.base = array2;
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(util);
	dispose(resizedArray);
	dispose(expectedUtil);
}

void test_findIndex_should_return_index_of_the_element_in_array_if_found(){
	int array[6] = {4,2,1,5,6,0};
	int x = 5,y = 0;
	util = create(sizeof(int),6);
	util.base = array;
	assertEqual(findIndex(util, &x),3);
	assertEqual(findIndex(util, &y),5);
	dispose(util);
}

void test_findIndex_should_return_negative_1_in_array_if_not_found(){
	int array[6] = {4,2,1,5,6,0};
	int x = 7,y=9;
	util = create(sizeof(int),6);
	util.base = array;
	assertEqual(findIndex(util, &x),-1);
	assertEqual(findIndex(util, &y),-1);
	dispose(util);
}

void test_findFirst_should_return_first_element_which_matches_in_array(){
	char array[6] = {'a','e','i','o','u','a'};
	char x = 'a';
	char *result;
	util = create(sizeof(char),6);
	util.base = array;
	result = (char*)findFirst(util,&match_Func,&x);
	assertEqual(*result,'a');
	dispose(util);
}

void test_findFirst_should_return_NULL_if_nothing_matches_in_array(){
	char array[5] = {'a','e','i','o','u'};
	char x = 'x';
	util = create(sizeof(char),5);
	util.base = array;
	assertEqual((int)findFirst(util,&match_Func,&x),(int)NULL);
	dispose(util);
}

void test_findLast_should_return_last_element_which_matches_in_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 3;
	int *result;
	util = create(sizeof(int),6);
	util.base = array;
	result = (int*)findLast(util,&isDivisible,&x);
	assertEqual(*result,9);
	dispose(util);
}

void test_findLast_should_return_NULL_if_nothing_matches_in_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 7;
	util = create(sizeof(int),6);
	util.base = array;
	assertEqual((int)findLast(util,&isDivisible,&x),(int)NULL);
	dispose(util);
}

void test_count_should_count_matched_element_in_INT_array(){
	ArrayUtil util = create( sizeof(int), 5);
	int base[5] = {2,9,15,11,27};
	int hint = 3;
	util.base = base;
	assertEqual(count(util, isDivisible, &hint),3);
}

void test_count_should_count_matched_element_in_CHAR_array(){
	char array[5] = {'a','e','i','a','u'};
	char x = 'a';
	util = create(sizeof(char),5);
	util.base = array;
	assertEqual(count(util,&match_Func,&x),2);
	dispose(util);
}

void test_count_should_count_matched_element_in_FLOAT_array(){
	float array[5] = {99.0,167.88,22.66,39.10,15.47908};
	float x = 'a';
	util = create(sizeof(float),5);
	util.base = array;
	assertEqual(count(util,&is_CeillEven,&x),3);
	dispose(util);
}

void test_count_should_count_matched_element_in_DOUBLE_array(){
	double array[5] = {99.89,167.88,22.66,36.10,15.47908};
	double x = 'a';
	util = create(sizeof(double),5);
	util.base = array;
	assertEqual(count(util,&is_FloorEven,&x),2);
	dispose(util);
}