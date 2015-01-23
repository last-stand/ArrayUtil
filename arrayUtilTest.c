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

int isUpperCase(void* a,void *b){
	return (*((char*)a) >= 'A' && *((char*)a) <= 'Z') ? 1 : 0;
}

int isEqual(void* hint, void* item){
	if(*(int*)item==8 ||*(float*)item == 9.0 || *(double*)item==8.9)
		return 1;
	return 0;
}

int compare(void *hint,void* item){
	if(*(char*)item=='a')
		return 1;
	return 0;
};

int stringCompare(void *hint, void* item){
	String str ="hello";
	String getItem = *(String*)item;
	if(getItem==str)
		return 1;
	return 0;
}

int isEven(void* a,void *b){
	return (*((int*)b)%2==0) ? 1 : 0;
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
}

void test_array_util_areEqual_returns_0_if_both_array_are_not_equal_in_length_and_elements(){
	int a[]={0,3,8,5,2,3,4,5}, b[]={1,5,2,3,7};
	ArrayUtil a_array = {a,sizeof(int),8};
	ArrayUtil b_array = {b,sizeof(int),5};
	assertEqual(areEqual(a_array, b_array),0);
}

void test_create_should_returns_array_within_structure_with_given_typeSize(){
	util = create(sizeof(int),5);
	assertEqual(util.typeSize,sizeof(int));
	dispose(util);
}

void test_create_should_returns_array_within_structure_with_given_length(){
	util = create(sizeof(int),5);
	assertEqual(util.length,5);
	dispose(util);
}

void test_create_allocates_space_for_INT_array_and_assigns_zero_to_all_bytes(){
	int intArray[] = {0,0,0,0};
	expectedUtil = (ArrayUtil){intArray,sizeof(int),4};
	util = create(sizeof(int),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
}

void test_create_allocates_space_for_CHAR_array_and_assigns_zero_to_all_bytes(){
	char charArray[] = {0,0,0,0};
	expectedUtil = (ArrayUtil){charArray,sizeof(char),4};
	util = create(sizeof(char),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
}

void test_create_allocates_space_for_FLOAT_array_and_assigns_zero_to_all_bytes(){
	float floatArray[] = {0,0,0,0};
	expectedUtil = (ArrayUtil){floatArray,sizeof(float),4};
	util = create(sizeof(float),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
}

void test_create_allocates_space_for_DOUBLE_array_and_assigns_zero_to_all_bytes(){
	double doubleArray[] = {0,0,0,0};
	expectedUtil = (ArrayUtil){doubleArray,sizeof(double),4};
	util = create(sizeof(double),4);
	assertEqual(areEqual(expectedUtil,util),1);
	dispose(util);
}

void test_create_Structures_with_all_fields_NULL(){
	student temp = {"",0,0.0};
	student Student[1] = {temp};
	ArrayUtil expected = {Student,sizeof(student),1};
	util = create(sizeof(student),1);
	assert(areEqual(expected,util));
};


void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal_by_each_element_typeof_double(){
	double a [] = {2.34};
	double b [] = {2.34};
	ArrayUtil array1 = {a, sizeof(double), 1};
	ArrayUtil array2 = {b, sizeof(double), 1};

	assert(areEqual(array1,array2));
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal_by_each_element_typeof_string(){
	String a [] = {"hello"};
	String b [] = {"hello"};
	ArrayUtil array1 = {a, sizeof(String), 1};
	ArrayUtil array2 = {b, sizeof(String), 1};

	assert(areEqual(array1,array2));
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_not_be_equal_String(){
	String a [] = {"hallo"};
	String b [] = {"hello"};
	ArrayUtil array1 = {a, sizeof(String), 1};
	ArrayUtil array2 = {b, sizeof(String), 1};

	assertEqual(areEqual(array1,array2),0);
};

void test_resize_returns_INT_array_within_structure_with_new_allocated_space(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(int []){1,2,3,4},sizeof(int),4};
	resizedArray = resize(util,6);
	expectedUtil = (ArrayUtil){(int []){1,2,3,4,0,0},sizeof(int),6}; 
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(resizedArray);
}


void test_resize_returns_FLOAT_array_within_structure_with_new_allocated_space(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(float []){1.0,2.11111,3.123,4.89},sizeof(float),4};
	resizedArray = resize(util,6);
	expectedUtil = (ArrayUtil){(float []){1.0,2.11111,3.123,4.89,0,0},sizeof(float),6};
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(resizedArray);
}

void test_resize_returns_DOUBLE_array_within_structure_with_new_allocated_space(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(double []){1.0,2.11111,3.123,4.89},sizeof(double),4};
	resizedArray = resize(util,6);
	expectedUtil = (ArrayUtil){(double []){1.0,2.11111,3.123,4.89,0,0},sizeof(double),6};
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(resizedArray);
}

void test_resize_returns_DOUBLE_array_within_structure_with_new_allocated_space_less_than_previous(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(double []){1.0,2.11111,3.123,4.89},sizeof(double),4};
	resizedArray = resize(util,2);
	expectedUtil = (ArrayUtil){(double []){1.0,2.11111},sizeof(double),2};
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(resizedArray);
}

void test_resize_returns_CHAR_array_within_structure_with_new_allocated_space(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(char []){'a','e','i','o'},sizeof(char),4};
	resizedArray = resize(util,6);
	expectedUtil = (ArrayUtil){(char []){'a','e','i','o',0,0},sizeof(char),6};
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(resizedArray);
}

void test_resize_returns_CHAR_array_within_structure_with_new_allocated_space_less_than_previous(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(char []){'a','e','i','o','u'},sizeof(char),5};
	resizedArray = resize(util,2);
	expectedUtil = (ArrayUtil){(char []){'a','e'},sizeof(char),2};
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(resizedArray);
}

void test_findIndex_should_return_index_of_the_element_in_INT_array_if_found(){
	int x = 5,y = 0;
	util = (ArrayUtil){(int []){4,2,1,5,6,0},sizeof(int),6};
	assertEqual(findIndex(util, &x),3);
	assertEqual(findIndex(util, &y),5);
}

void test_findIndex_should_return_negative_1_in_array_if_not_found(){
	int x = 7,y=9;
	util = (ArrayUtil){(int []){4,2,1,5,6,0},sizeof(int),6};
	assertEqual(findIndex(util, &x),-1);
	assertEqual(findIndex(util, &y),-1);
}

void test_findLast_returns_NULL_if_there_is_no_match_in_INTEGER_array(){
	ArrayUtil a = {(int[]){1,3,5,7,9},sizeof(int),5};
	int x = 2;
	assertEqual((int)findLast(a,isEven,&x),(int)NULL);
}

void test_findFirst_should_return_first_element_of_mathching_CHAR_array(){
	char array[6] = {'a','e','i','o','u','a'};
	char x = 'a',*result;
	util = (ArrayUtil){array,sizeof(char),6};
	result = (char*)findFirst(util,&match_Func,&x);
	assertEqual(*result,'a');
}

void test_findFirst_should_return_NULL_if_nothing_matches_in_array(){
	char array[5] = {'a','e','i','o','u'};
	char x = 'x';
	util = (ArrayUtil){array,sizeof(char),5};
	assertEqual((int)findFirst(util,&match_Func,&x),(int)NULL);
}

void test_findLast_should_return_last_element_which_matches_in_INT_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 3,*result;
	util = (ArrayUtil){array,sizeof(int),6};
	result = (int*)findLast(util,&isDivisible,&x);
	assertEqual(*result,9);
}

void test_findLast_should_return_NULL_if_nothing_matches_in_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 7;
	util = (ArrayUtil){array,sizeof(int),6};
	assertEqual((int)findLast(util,&isDivisible,&x),(int)NULL);
}

void test_count_should_count_matched_element_in_INT_array(){
	int base[5] = {2,9,15,11,27};
	int hint = 3;
	util = (ArrayUtil){base,sizeof(int),5};
	assertEqual(count(util, isDivisible, &hint),3);
}

void test_count_should_count_matched_element_in_CHAR_array(){
	char array[5] = {'a','e','i','a','u'};
	char x = 'a';
	util = (ArrayUtil){array,sizeof(char),5};
	assertEqual(count(util,&match_Func,&x),2);
}

void test_count_should_count_matched_element_in_FLOAT_array(){
	float array[5] = {99.0,167.88,22.66,39.10,15.47908};
	float x = 'a';
	util = (ArrayUtil){array,sizeof(float),5};
	assertEqual(count(util,&is_CeillEven,&x),3);
}

void test_count_should_count_matched_element_in_DOUBLE_array(){
	double array[5] = {99.89,167.88,22.66,36.10,15.47908};
	double x = 'a';
	util = (ArrayUtil){array,sizeof(double),5};
	assertEqual(count(util,&is_FloorEven,&x),2);
}

void test_filters_all_numbers_divisible_by_2(){
	int *base;
	int result,i,_2 = 2;
	void *destination; 
	util = (ArrayUtil){(int[]){21,34,90,17,12},sizeof(int),5};
	base = util.base;
	result = filter(util,isDivisible,&_2,&destination,5);
	assert(3 == result);
	assert(((int*)destination)[0] == 34);
	assert(((int*)destination)[1] == 90);
	assert(((int*)destination)[2] == 12);
	free(destination);
}

void test_filter_will_return_the_array_a_a_a(){
	char a[]={'a','a','a','b','d'},hint=3;
	int length;
	void* result;
	ArrayUtil array = {a, sizeof(char), 5};
	length = filter(array,compare,&hint,&result,5);

	assertEqual(((char*)result)[1],'a');
	assertEqual(length,3);
	free(result);
};

void test_filter_will_return_the_array_of_8_8_8(){
	int a[]={1,8,8,7,8,9},hint=3,length;
	void* result;
	ArrayUtil array = {a, sizeof(int), 6};
	length = filter(array,isEqual,&hint,&result,5);

	assertEqual(((int*)result)[0],8);
	assertEqual(length,3);
	free(result);
};

void test_filter_will_return_the_array_of_only_two_8(){
	int a[]={1,8,8,7,8,9},hint=3,length;
	void* result;
	ArrayUtil array = {a, sizeof(int), 6};
	length = filter(array,isEqual,&hint,&result,2);

	assertEqual(((int*)result)[1],8);
	assertEqual(length,2);
	free(result);
};

void test_filter_will_return_the_array_of_only_two_8_point_7_in_float(){
	float a[]={1.4,8.4,8.9,7,8,9.0},hint=3;
	int length;
	void* result;
	ArrayUtil array = {a, sizeof(float), 6};
	length = filter(array,isEqual,&hint,&result,2);

	assertEqual(((float*)result)[0],9.0);
	assertEqual(length,1);
	free(result);
};

void test_filter_will_return_the_array_of_only_one_element_8_point_9_in_double(){
	double a[]={8.4,8.4,8.9},hint=3.9;
	int length;
	void* result;
	ArrayUtil array = {a, sizeof(double), 3};
	length = filter(array,isEqual,&hint,&result,2);

	assertEqual(((double*)result)[0],a[2]);
	assertEqual(length,1);
	free(result);
};

void test_filter_will_return_the_array_string_contain_hello(){
	int length,hint=9;
	void* result,*expected;
	ArrayUtil array = create(sizeof(String),2);
	((char**)array.base)[0]="hello";
	((char**)array.base)[1]="gello";
	length = filter(array,stringCompare,&hint,&result,2);
	expected = ((String*)result)[0];
	
	assertEqual(length,1);
	assertEqual(strcmp(expected,"hello"),0);
	free(result);
};

void test_filter_populate_destination_array_with_evenNumbers(){
    int maxItem=6,result;
    void *evens;
    util = (ArrayUtil){(int[]){101,22,12,13},sizeof(int),4};
    result = filter(util,isEven,0,&evens,maxItem);
	assertEqual(result,2);
	assertEqual(((int*)evens)[0],22);
	assertEqual(((int*)evens)[1],12);
	free(evens);
}

void test_filter_populate_destination_array_until_hits_max_size_and_return_no_element_added_to_id(){
    void *evens;
    util = (ArrayUtil){(int[]){101,22,12,14},sizeof(int),4};   	 

	 assertEqual(filter(util,isEven,0,&evens,2),2);
	 assertEqual(((int*)evens)[0],22);
	 assertEqual(((int*)evens)[1],12);
	 free(evens); 
}