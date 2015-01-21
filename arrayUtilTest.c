#include "expr_assert.h"
#include "arrayUtil.h"
#include <stdlib.h>
#include <string.h>

ArrayUtil util,expectedUtil;
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

void test_resize_returns_array_within_structure_with_new_allocated_space(){
	int array1[] = {1,2,3,4};
	int *resizeArray;
	ArrayUtil new_Array;
	util = create(sizeof(int),4);
	util.base = array1;

	new_Array = resize(util,6);
	resizeArray = new_Array.base;
	assertEqual(new_Array.length,6);
	assertEqual(resizeArray[0],1);
	assertEqual(resizeArray[1],2);
	assertEqual(resizeArray[2],3);
	assertEqual(resizeArray[3],4);
	assertEqual(resizeArray[4],0);
	assertEqual(resizeArray[5],0);
	dispose(util);
	dispose(new_Array);
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

int match_Func(void* hint, void* item){
	char* _hint = (char*)hint;
	char* _item = (char*)item;
	return *_hint == *_item ? 1 : 0;
}

void test_findFirst_should_return_first_element_which_matches_in_array(){
	char array[6] = {'a','e','i','o','u','a'};
	char x = 'a';
	char* x_ptr = &x;
	char *result;
	MatchFunc *match = &match_Func;
	util = create(sizeof(char),6);
	util.base = array;
	result = (char*)findFirst(util,match,(void*)x_ptr);
	assertEqual(*result,'a');
	dispose(util);
}

void test_findFirst_should_return_NULL_if_nothing_matches_in_array(){
	char array[5] = {'a','e','i','o','u'};
	char x = 'x';
	char* x_ptr = &x;
	MatchFunc *match = &match_Func;
	util = create(sizeof(char),5);
	util.base = array;
	assertEqual((int)findFirst(util,match,(void*)x_ptr),(int)NULL);
	dispose(util);
}

int isDivisible(void* hint, void* item){
	int* _hint = (int*)hint;
	int* _item = (int*)item;
	return (*_item % *_hint) == 0 ? 1 : 0;
}

void test_findLast_should_return_last_element_which_matches_in_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 3;
	int* x_ptr = &x;
	int *result;
	MatchFunc *match = &isDivisible;
	util = create(sizeof(int),6);
	util.base = array;
	result = (int*)findLast(util,match,(void*)x_ptr);
	assertEqual(*result,9);
	dispose(util);
}

void test_findLast_should_return_NULL_if_nothing_matches_in_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 7;
	int* x_ptr = &x;
	MatchFunc *match = &isDivisible;
	util = create(sizeof(int),6);
	util.base = array;
	assertEqual((int)findLast(util,match,(void*)x_ptr),(int)NULL);
	dispose(util);
}