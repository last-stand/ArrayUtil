#include "expr_assert.h"
#include "arrayUtil.h"

void test_array_util_areEqual_returns_1_if_both_array_are_equal_in_length_and_elements(){
	int a[]={1,2,3,4,5};
	int b[]={1,2,3,4,5};

	ArrayUtil a_array;
	ArrayUtil b_array;

	a_array.typeSize = sizeof(int);
	a_array.length = 5;
	a_array.base = a;

	b_array.typeSize = sizeof(int);
	b_array.length = 5;
	b_array.base = b;

	assertEqual(areEqual(a_array, b_array),1);
}

void test_array_util_areEqual_returns_0_if_both_array_are_not_equal_in_length_and_elements(){
	int a[]={0,3,8,5,2,3,4,5};
	int b[]={1,5,2,3,7};

	ArrayUtil a_array;
	ArrayUtil b_array;

	a_array.typeSize = sizeof(int);
	a_array.length = 8;
	a_array.base = a;

	b_array.typeSize = sizeof(int);
	b_array.length = 5;
	b_array.base = b;

	assertEqual(areEqual(a_array, b_array),0);
}

void test_create_should_return_structure_with_given_typeSize(){
	ArrayUtil newArray = create(sizeof(int),5);
	assertEqual(newArray.typeSize,sizeof(int));
}

void test_create_should_return_structure_with_given_length(){
	ArrayUtil newArray = create(sizeof(int),5);
	assertEqual(newArray.length,5);
}

void test_create_should_return_structure_with_array_initialized_each_element_with_0(){
	ArrayUtil newArray = create(sizeof(int),5);
	int *array = newArray.base;
	assertEqual((int)array[0],0);
	assertEqual((int)array[1],0);
	assertEqual((int)array[2],0);
	assertEqual((int)array[3],0);
	assertEqual((int)array[4],0);
}

void test_resize_returns_structure_with_new_allocated_space(){
	int array[] = {1,2,3,4};
	int *resizeArray;
	ArrayUtil previousArray;
	ArrayUtil new_Array;
	previousArray.base = array;
	previousArray.typeSize = sizeof(int);
	previousArray.length = 4;

	new_Array = resize(previousArray,6);
	resizeArray = new_Array.base;
	assertEqual(new_Array.length,6);
	assertEqual(resizeArray[0],1);
	assertEqual(resizeArray[1],2);
	assertEqual(resizeArray[2],3);
	assertEqual(resizeArray[3],4);
	assertEqual(resizeArray[4],0);
	assertEqual(resizeArray[5],0);
}

void test_findIndex_should_return_index_of_the_element_in_array_if_found(){
	int array[6] = {4,2,1,5,6,0};
	int x = 5,y = 0;
	ArrayUtil util;
	util.typeSize = sizeof(int);
	util.length = 6;
	util.base = array;
	assertEqual(findIndex(util, &x),3);
	assertEqual(findIndex(util, &y),5);
}

void test_findIndex_should_return_negative_1_in_array_if_not_found(){
	int array[6] = {4,2,1,5,6,0};
	int x = 7,y=9;
	ArrayUtil util;
	util.typeSize = sizeof(int);
	util.length = 6;
	util.base = array;
	assertEqual(findIndex(util, &x),-1);
	assertEqual(findIndex(util, &y),-1);
}