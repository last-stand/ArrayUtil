#include "expr_assert.h"
#include "arrayUtil.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#define log(test_description) int log = (printf("\t     %s\n\n", test_description))

ArrayUtil util,expectedUtil;

int isDivisible(void* hint, void* item){
	int* _hint = (int*)hint;
	int* _item = (int*)item;
	return (*_item % *_hint) == 0 ? 1 : 0;
}

int isUpperCase(void* a,void *b){
	return (*((char*)b) >= 'A' && *((char*)b) <= 'Z') ? 1 : 0;	
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
	if(strcmp(getItem,str) == 0)
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

void test_areEqual_returns_0_when_length_is_equal_but_typeSize_is_not_equal(){
	int array1[]={1,2,3,4,5};
	char array2[]={'a','b','c','d','\0'};
	ArrayUtil u1={array1,sizeof(int),5};
	ArrayUtil u2={array2,sizeof(char),5};
	assertEqual(areEqual(u1,u2), 0);
}

void test_areEqual_returns_0_if_typeSize_of_two_arrays_are_not_equal(){
    int array1[] = {1,2,3,4};
    char array2[] = {'m','a','h','e'};
    ArrayUtil util1 = {array1,sizeof(int),4};
    ArrayUtil util2 = {array2,sizeof(char),4};
    assertEqual(areEqual(util1, util2), 0);
}


void test_array_util_areEqual_returns_0_if_both_array_are_not_equal_in_length_and_elements(){
	int a[]={0,3,8,5,2,3,4,5}, b[]={1,5,2,3,7};
	ArrayUtil a_array = {a,sizeof(int),8};
	ArrayUtil b_array = {b,sizeof(int),5};
	assertEqual(areEqual(a_array, b_array),0);
}

void test_for_the_ArrayUtil_for_charecter_and_int_are_not_equal(){
    char first_array[]={'c','d','e','f'};
    int second_array[]={2,5,8,4};
    ArrayUtil array1 = {first_array,sizeof(char),4};
    ArrayUtil array2 = {second_array,sizeof(int),4};
	assertEqual(areEqual(array1, array2),0);
};

void test_that_function_creates_new_array_or_not(){
	ArrayUtil array = create(sizeof(int),3);
	int *createArray  = (int*)array.base;
	assertEqual(createArray[0], 0);
	assertEqual(createArray[2], 0);
	assertEqual(array.length, 3);
	assertEqual(array.typeSize, 4);
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

void test_Create_creates_new_array_of_float_containing_all_elements_0 (){
	ArrayUtil expectedUtil = {(float[]){0,0},sizeof(float),2};
ArrayUtil newUtil = create(sizeof(float), 2);
	assertEqual(areEqual(expectedUtil,newUtil ), 1);
	dispose(newUtil);
}
void test_Create_creates_new_charArray_containing_all_elements_0_and_gives_0_for_different_lengths (){
	ArrayUtil expectedUtil = {(char[]){0,0,0},sizeof(char),3};
ArrayUtil newUtil =create(sizeof(char), 2);
	assertEqual(areEqual(expectedUtil, newUtil), 0);
dispose(newUtil);
}
void test_Create_creates_new_doubleArray_containing_all_elements_0_and_gives_0_for_different_lengths (){
	ArrayUtil expectedUtil = {(double[]){0,0},sizeof(double),2};
ArrayUtil newUtil =create(sizeof(double), 3);
	assertEqual(areEqual(expectedUtil, newUtil), 0);
dispose(newUtil);
}
void test_Create_creates_new_intArray_containing_all_elements_0_and_gives_0_for_different_lengths (){
	ArrayUtil expectedUtil = {(int[]){0,0,0},sizeof(int),3};
ArrayUtil newUtil =create(sizeof(int), 2);
	assertEqual(areEqual(expectedUtil, newUtil), 0);
dispose(newUtil);
}

void test_Create_creates_new_floatArray_containing_all_elements_0_and_gives_0_for_different_lengths (){
	ArrayUtil util = {(float[]){0,0},sizeof(float),2};
ArrayUtil newUtil =create(sizeof(float), 3);
	assertEqual(areEqual(util, newUtil), 0);
dispose(newUtil);
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

void test_resize_add_0_to_the_new_places_created_in_integer_array(){
	int array[] = {1,2,3}, arr[] = {1,2,3,0,0};
	ArrayUtil array2, util1 = {array, sizeof(int), 3};
	ArrayUtil expected = {arr, sizeof(int) ,5};
	array2 =  resize(util1,5);
	assert(areEqual(array2 , expected));
}
void test_resize_add_0_to_the_new_places_created_in_float_array(){
	float array[] = {1.1,2.2,3.2}, arr[] = {1.1,2.2,3.2,0.0,0.0};
	ArrayUtil array2, util1 = {array, sizeof(float), 3};
	ArrayUtil expected = {arr, sizeof(float) ,5};
	array2 =  resize(util1,5);
	assert(areEqual(array2 , expected));
}
void test_resize_add_0_to_the_new_places_created_in_char_array(){
	char *array= "abc";
	char arr[] = {'a','b','c',0,0};
	ArrayUtil array2, util1 = {array, sizeof(char), 3};
	ArrayUtil expected = {arr, sizeof(char) ,5};
	array2 =  resize(util1,5);
	assert(areEqual(array2 , expected));
}
void test_resize_add_0_to_the_new_places_created_in_double_array(){
	double array[] = {1,2,3}, arr[] = {1,2,3,0.0,0.0};
	ArrayUtil array2, util1 = {array, sizeof(double), 3};
	ArrayUtil expected = {arr, sizeof(double) ,5};
	array2 =  resize(util1,5);
	assert(areEqual(array2 , expected));
}


void test_resize_returns_new_Array_util_with_String_array_of_new_length_by_putting_0s_in_new_created_spaces(){
    String array1[] = {"Mahesh","Kumar"}, array2[] = {"Mahesh","Kumar",0,0,0};
    ArrayUtil util1 = {array1,sizeof(char *),2};
    ArrayUtil util2 = {array2,sizeof(char *),5};
    assertEqual(areEqual(resize(util1, 5), util2), 1);    
}
void test_resize_returns_new_Array_util_with_String_array_of_new_length_by_removing_extra_values(){
    String array1[] = {"Mahesh","Kumar","Kolla"}, array2[] = {"Mahesh","Kumar"};
    ArrayUtil util1 = {array1,sizeof(char *),3};
    ArrayUtil util2 = {array2,sizeof(char *),2};
    assertEqual(areEqual(resize(util1, 2), util2), 1);    
}

void test_resize_should_grow_length_of_array_and_set_them_to_zero_when_new_size_is_more(){
	ArrayUtil a = create(4,2);
	int i;
	a = resize(a,5);
	assert(a.length == 5);
	for (i = 0; i < 20; ++i)
	{
		assert(((char*)a.base)[i] == 0);
	}
	dispose(a);
}
void test_resize_should_not_change_length_of_array_when_new_size_is_same_as_old_size(){
	ArrayUtil a = create(1,5);
	int i;
	a = resize(a,5);
	assert(a.length == 5);
	dispose(a);
}

void test_resize_an_existing_array_to_resize_decrease_its_length(){
    int *resArray;
    ArrayUtil array,resizeArray;
    array = create(sizeof(int),5);
    ((int*)array.base)[0]=90;
    ((int*)array.base)[1]=40;
    ((int*)array.base)[2]=550;
    ((int*)array.base)[3]=550;
    ((int*)array.base)[4]=40;
    resizeArray=resize(array,4);
    resArray = resizeArray.base;
    assertEqual(resArray[2],550);
    assertEqual(areEqual(resizeArray,array),0);
};


void test_resize_an_existing_array_to_resize_increase_its_length(){
    ArrayUtil array = create(sizeof(int),3),resultArray;
    ((int*)array.base)[0]=90;
    ((int*)array.base)[1]=40;
    ((int*)array.base)[2]=550;
    resultArray = resize(array,5);
    assertEqual(((int *)resultArray.base)[0],90);
    assertEqual(((int *)resultArray.base)[1],40);
    assertEqual(((int *)resultArray.base)[2],550);
    assertEqual(((int *)resultArray.base)[3],0);
    assertEqual(((int *)resultArray.base)[4],0);
};

void test_resize_returns_INT_array_within_structure_with_new_allocated_space(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(int []){1,2,3,4},sizeof(int),4};
	resizedArray = resize(util,6);
	expectedUtil = (ArrayUtil){(int []){1,2,3,4,0,0},sizeof(int),6}; 
	assertEqual(areEqual(expectedUtil, resizedArray),1);
	dispose(resizedArray);
}

void test_when_an_array_is_resized_into_smaller_size_the_array_is_trimmed(){
	ArrayUtil util = create( sizeof(char) , 3);
	ArrayUtil resizedUtil = resize(util, 2);
	char array[]={0,0,0};
	ArrayUtil expected = { (void *)array, sizeof(char), 2};
	assert(areEqual(expected, resizedUtil));
}

void test_resize_should_contain_the_initial_array_element(){
	int src[]={5,3},i;
	ArrayUtil util={src,sizeof(int),4},array;
	int* base;
	array = resize(util,15);
	base = (int *)(array.base);
	assertEqual(base[0], 5);
	assertEqual(base[1], 3);
	assertEqual(base[14], 0);

	free(array.base);
};

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

void test_findIndex_returns_1_if_the_search_char_is_found_on_1st_location (){
	int x = 'a';
	char array[] = "car";
	ArrayUtil util = create(sizeof(char),3);
	util.base = (void*)array;
	assertEqual(findIndex(util,&x),1);
}

void test_findIndex_returns_index_of_the_String_element_where_it_presents(){
    String array1[] = {"Mahesh","Kumar","Kolla"};
    String element = "Kumar";
    util = (ArrayUtil){array1,sizeof(String),3};
    assertEqual(findIndex(util,&element), 1);
}

void test_findIndex_returns_index_of_the_char_element_where_it_presents(){
    char array1[] = {'m','a','h','e','s','h'};
    char element = 's';
    util = (ArrayUtil){array1,sizeof(char),6};
    assertEqual(findIndex(util,&element), 4);
}

void test_findIndex_returns_index_of_the_float_element_where_it_presents(){
    float array1[] = {1.1,2.2,3.3,4.4};
    float element = 4.4;
    util = (ArrayUtil){array1,sizeof(float),4};
    assertEqual(findIndex(util,&element), 3);
}

void test_findIndex_returns_index_of_the_integer_element_where_it_presents(){
    int array1[] = {1,2,3,4,5};
    int element = 2;
    util = (ArrayUtil){array1,sizeof(int),5};
    assertEqual(findIndex(util,&element), 1);
}

void test_findIndex_retruns_the_index_of_an_element_in_an_string_array(){
    char array[]= {"heloo"};
    char element ='o';
    ArrayUtil util = {array,sizeof(char),4};
    assertEqual(findIndex(util,&element),3);
};

void test_findIndex_returns_4_for_float_array_if_search_element_is_at_4th_location (){
	float element = 7.8;
	ArrayUtil util = {(float[]){4.2,2.9,1.4,3.1,7.8,8.7},sizeof(float),6};
	assertEqual(findIndex(util, &element),4);
}

void test_findIndex_will_return_the_minus_1_if_array_element_is_not_present(){
	int array[]={1,2,3,4,5};
	int x=7;
	ArrayUtil arr={array,sizeof(int),5};
	assertEqual(findIndex(arr,&x),-1);
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

int isCapital(void *hint, void *item) {
    return((*(char *)item >=65) && (*(char *)item <= 91));
}

int isGreaterThan5(void *hint, void *item) {
    return(*(float *)item > 5);
}

void test_findFirst_returns_the_address_of_the_first_element_in_the_array_that_is_capital(){
    char array1[] = {'k','M','k'};
    ArrayUtil util1 = {array1,sizeof(char),3};
    assertEqual(*(char *)(findFirst(util1,&isCapital,0)), 'M');
}

void test_findFirst_returns_the_address_of_the_first_element_in_the_array_that_is_even(){
    int array1[] = {1,2,3,4,5};
    ArrayUtil util1 = {array1,sizeof(int),5};
    assertEqual(*(int *)(findFirst(util1,&isEven, 0)), 2);
}

void test_findFirst_returns_the_adsdress_of_first_element_in_the_array_greater_than_5() {
    float array1[] = {1.1,6.6,5.5,8.8,2.2};
    ArrayUtil util1 ={array1, sizeof(float),5};
    assertEqual(*(float *)(findFirst(util1,&isGreaterThan5,0)), (float)6.6);
}

void test_findLast_should_return_last_element_which_matches_in_INT_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 3,*result;
	util = (ArrayUtil){array,sizeof(int),6};
	result = (int*)findLast(util,&isDivisible,&x);
	assertEqual(*result,9);
}

void test_findLast_returns_the_last_element_if_there_is_match_in_INTEGER_array(){
	ArrayUtil a = {(int[]){1,3,5,8,10},sizeof(int),5};
	int x = 2;
	assertEqual(*((int*)findLast(a,isEven,&x)),10);
}

void test_findLast_should_return_NULL_if_nothing_matches_in_array(){
	int array[6] = {1,6,4,5,9,11};
	int x = 7;
	util = (ArrayUtil){array,sizeof(int),6};
	assertEqual((int)findLast(util,&isDivisible,&x),(int)NULL);
}

void test_findLast_returns_the_last_element_if_there_is_match_in_CHAR_array(){
	ArrayUtil a = {(char[]){'a','b','C','D','e'},sizeof(char),5};
	int x = 'D';
	assertEqual(*((char*)findLast(a,isUpperCase,&x)),'D');
}

int isLessThanTheHints(void* hint,void* element){
    return (*(float*)element) < (*(float*)hint);

}

void test_for_findLast_gives_the_last_element_of_less_than_float_value_an_array(){
    float hint = 6.3;
    float *result;
    ArrayUtil util = {(float[]){2.5,4.5,6.3,4.5,6.0},sizeof(float),5};
    result = findFirst(util,isLessThanTheHints,&hint);
    assert(*result == 2.5);
};

int isGreaterThanHint (void* hint, void* element) {
	return (*((float*)element) > *((float*)hint)) ? 1 : 0;
}

void test_findLast_gives_occurence_of_last_element_in_floatArray_greaterThan5 (){
	float hint = 5.1;
	float *result;
	MatchFunc *match = &isGreaterThanHint;
	ArrayUtil util = {(float[]){7.1,2.4,1.6,3.7,8.3,0.1},sizeof(float),6};
	result = (float*)findLast(util,match,(void*)&hint);
	assertEqual(*result,(float)8.3);
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

void test_filter_gives_2_4_for_1_2_3_4_5(){
	ArrayUtil util = create(sizeof(int),5);
	int *arr,i,result,hint = 2;
	int** list = (int**)malloc(sizeof(int)*2);
	arr = (int*)util.base;
	for(i=0;i<5;i++){
		arr[i] = i+1;
	}
	result = filter(util, isDivisible,&hint,(void**)list,2);
	assertEqual(result,2);
	assertEqual(*(list[0]),2);
	assertEqual(*(list[1]),4);; 
}

void test_filters_all_numbers_divisible_by_2(){
	int *base;
	int result,i,_2 = 2;
	int **destination = calloc(5,sizeof(int)); 
	util = (ArrayUtil){(int[]){21,34,90,17,12},sizeof(int),5};
	base = util.base;
	result = filter(util,isDivisible,&_2,(void**)destination,5);
	assert(3 == result);
	assert(*(destination[0]) == 34);
	assert(*(destination[1]) == 90);
	assert(*(destination[2]) == 12);
	free(destination);
}

int start_with_j(void *hint, void* item){
	String getItem = *(String*)item;
	return (getItem[0] == 'J') || (getItem[0] == 'j');
}

void test_filter_string_should_filter_strings_start_with_j(){
	char str1[] = "hello", str2[]="James Bond", str3[]="jungle-jungle baat chali hai",str4[]="Big-Bang";
	String array[4] = {str1,str2,str3,str4};
	String **result_array = (String**)calloc(2, sizeof(String));
	util = (ArrayUtil){array,sizeof(String),4};
	assertEqual(filter(util,start_with_j,null,(void**)result_array,2),2);
	assertEqual(strcmp(*(result_array[0]),array[1]),0);
	assertEqual(strcmp(*(result_array[1]),array[2]),0);
}

void test_filter_should_filter_those_elements_which_are_matching_given_the_criteria(){
	int arr[] = {1,2,3,4,5},result,i,expected[] = {2,4};
	int **destination = calloc(5,sizeof(int));
	util = create(sizeof(int),5);
	util.base = arr;
	result = filter(util, isEven, null, (void**)destination, 5);	
	for (i = 0; i < 2; ++i)
	{
		assert(*(destination[i]) == expected[i]);
	}
	assert(result == 2);
}

void test_filter_will_return_the_array_a_a_a(){
	char a[]={'a','a','a','b','d'},hint=3;
	int length;
	char **result = calloc(5,sizeof(int));
	ArrayUtil array = {a, sizeof(char), 5};
	length = filter(array,compare,&hint,(void**)result,5);

	assertEqual(*(result[1]),'a');
	assertEqual(length,3);
	free(result);
};

void test_filter_gives_D_E_for_a_b_c_D_E() {
	ArrayUtil a = {(char[]){'a','b','c','D','E'},sizeof(char),5};
	char hint = 'a';
	char **list = calloc(2,sizeof(char));
	int count;
	count =  filter(a,isUpperCase,&hint,(void**)list,2);
	assert(count==2);
	assertEqual(*(list[0]),'D');
	assertEqual(*(list[1]),'E');
	free(list); 
}

void test_filter_will_return_the_array_of_8_8_8(){
	int a[]={1,8,8,7,8,9},hint=3,length;
	int **result = malloc(sizeof(int)*5);
	ArrayUtil array = {a, sizeof(int), 6};
	length = filter(array,isEqual,&hint,(void**)result,5);
	assertEqual(*(result[0]),8);
	assertEqual(*(result[1]),8);
	assertEqual(*(result[2]),8);
	assertEqual(length,3);
	free(result);
};

void test_filter_will_return_the_array_of_only_two_8(){
	int a[]={1,8,8,7,8,9},hint=3,length;
	int **result = malloc(sizeof(int)*2);
	ArrayUtil array = {a, sizeof(int), 6};
	length = filter(array,isEqual,&hint,(void**)result,2);
	assertEqual(*(result[0]),8);
	assertEqual(*(result[1]),8);
	assertEqual(length,2);
	free(result);
};

void test_filter_will_return_the_array_of_only_two_8_point_7_in_float(){
	float a[]={1.4,8.4,8.9,7,8,9.0},hint=3;
	int length;
	float **result = malloc(sizeof(float)*2);
	ArrayUtil array = {a, sizeof(float), 6};
	length = filter(array,isEqual,&hint,(void**)result,2);

	assertEqual(*(result[0]),9.0);
	assertEqual(length,1);
	free(result);
};

void test_filter_will_return_the_array_of_only_one_element_8_point_9_in_double(){
	double a[]={8.4,8.4,8.9},hint=3.9;
	int length;
	double **result = malloc(sizeof(double)*2);
	ArrayUtil array = {a, sizeof(double), 3};
	length = filter(array,isEqual,&hint,(void**)result,2);
	assertEqual(*(result[0]),a[2]);
	assertEqual(length,1);
	free(result);
};

void test_filter_will_return_the_array_string_contain_hello(){
	int length,hint=9;
	char str1[] = "hello",str2[] = "gello";
	String array[] = {str1,str2};
	String **result = calloc(2,sizeof(String));
	util = (ArrayUtil)create(sizeof(String),2);
	util.base = array;
	length = filter(util,stringCompare,&hint,(void**)result,2);
	assertEqual(length,1);
	assertEqual(strcmp(*(result[0]),str1),0);
	free(result);
};

void test_filter_populate_destination_array_with_evenNumbers(){
    int maxItem=6;
    int *evens[maxItem];
    util = (ArrayUtil){(int[]){101,22,12,13},sizeof(int),4};
	 assertEqual(filter(util,isEven,0,(void**)evens,maxItem),2);
	 assertEqual(*(evens[0]),22);
	 assertEqual(*(evens[1]),12);
}

void test_filter_populate_destination_array_until_hits_max_size_and_return_no_element_added_to_id(){
    int maxItem=2;
    int *evens [maxItem];
    util = (ArrayUtil){(int[]){101,22,12,14},sizeof(int),4};   	 

	 assertEqual(filter(util,isEven,0,(void**)evens,maxItem),2);
	 assertEqual(*(evens[0]),22);
	 assertEqual(*(evens[1]),12);    
}

void test_filter_filters_the_util_intArray_which_matches_the_criteria (){
	int hint = 4, maxItem=2;
	int *destination[maxItem];
	util = (ArrayUtil){(int[]){7,2,6,3,8,9},sizeof(int),6};
	assertEqual(filter(util, isGreaterThanHint, (void*)&hint, (void**)destination, 4),4);
	assertEqual(*(destination[0]), 7);
	assertEqual(*(destination[1]), 6);
	assertEqual(*(destination[2]), 8);
	assertEqual(*(destination[3]), 9);
}

void test_filter_filters_the_util_floatArray_which_matches_the_criteria (){
	float hint = 5.1;
	ArrayUtil util = {(float[]){7.1,2.4,1.6,3.7,8.3,0.1},sizeof(float),6};
	float **destination = (float**)malloc(sizeof(float)*2);
	assertEqual(filter(util,isGreaterThanHint,&hint, (void**)destination, 4),2);
	assertEqual(*(destination[0]), (float)7.1);
	assertEqual(*(destination[1]), (float)8.3);
	free(destination);
}

void test_filter_fills_filtered_array_with_even_numbers_of_existing_array_and_returns_count(){
	int array[]={1,2,3,4,5,6,7,8};
	int newArray[]={2,4,6,8};
	ArrayUtil util={array,sizeof(int),8};
	int **filtered=(int **)malloc(sizeof(int)*5);
	int counter=filter(util,isEven,0,(void**)filtered,5);
 	assertEqual(counter,4);
 	assertEqual(newArray[0],*(filtered[0]));
 	assertEqual(newArray[1],*(filtered[1]));
 	assertEqual(newArray[2],*(filtered[2]));
 	assertEqual(newArray[3],*(filtered[3]));
 	free(filtered);
}

void test_filter_returns_0_when_there_are_no_enven_no_in_existing_array(){
	int array[]={1,3,5,7};
	ArrayUtil util={array,sizeof(int),4};
	int *filtered=(int *)malloc(sizeof(int)*2);
	int counter=filter(util,isEven,0,(void**)&filtered,2);
 	assertEqual(counter,0);
 	free(filtered);
}

void add_given_number(void* hint, void* sourceItem, void* destinationItem){
	*(int*)destinationItem = *(int*)sourceItem + *(int*)hint;
};

void charConvertFunc(void* hint, void* sourceItem, void* destinationItem){
	*((char*)destinationItem) = *((char*)sourceItem) - 32;
}

void multiplyBy(void* hint, void* sourceItem, void* destinationItem){
    *(int*)destinationItem = *(int*)sourceItem * *(int*)(hint);
}

void square_elements(void *hint, void *sourceItem, void *destinationItem){
	*(int*)destinationItem=*(int*)sourceItem * *(int*)sourceItem;
}

void stringToUpper(void* hint, void* sourceItem, void* destinationItem){
	*((char*)destinationItem) = (char)toupper((int)*((char*)sourceItem));
}

void test_map_should_add_given_number_to_each_elemeny_in_INT_array(){
	ArrayUtil src,dest;
	int hint = 3;
	int i,result;
	expectedUtil = (ArrayUtil){(int[]){4,5,6,7,8},sizeof(int),5};
	src = create(sizeof(int),5);
	for(i=0;i<5;i++)
		*((int*)src.base+i) = i+1;
	dest = create(sizeof(int),5);
	map(src,dest,add_given_number,&hint);
	result = areEqual(expectedUtil,dest);
	assert(result);
}

void test_map_gives_2_3_4_5_6_for_1_2_3_4_5_for_integer_array(){
	ArrayUtil src = {(int[]){1,2,3,4,5},sizeof(int),5},dest = create(sizeof(int),5);
	ArrayUtil tmp = {(int[]){2,3,4,5,6},sizeof(int),5};
	int hint = 1;
	map(src,dest,add_given_number,&hint);
	assert(areEqual(dest,tmp)==1);
	dispose(dest);
}

void test_map_gives_A_B_C_D_E_for_a_b_c_d_e_for_character_array(){
	ArrayUtil src = {(char[]){'a','b','c','d','e'},sizeof(char),5},dest = create(sizeof(char),5);
	ArrayUtil tmp = {(char[]){'A','B','C','D','E'},sizeof(char),5};
	char hint = 32;
	map(src,dest,charConvertFunc,&hint);
	assertEqual(areEqual(dest,tmp),1);
	dispose(dest);
}

void test_map_should_returns_all_chars_in_uppercase_of_STRING_array(){
	char array[] = "mere sapno ki rani kab aayegi tu";
	char expectedArray[] = "MERE SAPNO KI RANI KAB AAYEGI TU";
	ArrayUtil src = {array,sizeof(char),strlen(array)+1},dest = create(sizeof(char),strlen(array)+1);
	expectedUtil = (ArrayUtil){expectedArray,sizeof(char),strlen(expectedArray)+1};
	map(src,dest,stringToUpper,null);
	assertEqual(areEqual(dest,expectedUtil),1);
	dispose(dest);
}

void test_map_converts_each_element_source_array_and_put_it_to_destination_array(){
    int hint =10;
    ArrayUtil util2;
    expectedUtil=(ArrayUtil){(int[]){10,20,30,40,50},sizeof(int),5};
    util=(ArrayUtil){(int[]){1,2,3,4,5},sizeof(int),5};
    util2 =create(sizeof(int),5);
    
    map(util,util2,multiplyBy,&hint);
    assert(areEqual(expectedUtil, util2));
}

void test_map_returns_square_of_each_element_in_array(){
	int array[]={1,2,3,4,5}, newArray[]={1,4,9,16,25};
	util=(ArrayUtil){calloc(5,sizeof(int)),sizeof(int),5};
	util = (ArrayUtil){array,sizeof(int),5};
	expectedUtil = (ArrayUtil){newArray,sizeof(int),5};
	map(util,util,square_elements,null);
	assert(areEqual(expectedUtil, util));
}

void increment(void* hint, void* sourceItem, void* destinationItem){
	int *hintPtr = (int*)hint;
	int *numberPtr = (int*)sourceItem;
	int *resultPtr = (int*)destinationItem;

	*resultPtr = *numberPtr + *hintPtr;
}

void test_map_should_map_source_to_destination_using_the_provided_convert_function(){
	int hint = 1, result[] = {2,3,4,5,6};
	int sample[] = {1,2,3,4,5};
	ArrayUtil resultUtil = create(util.typeSize, util.length);
	util = (ArrayUtil){sample, sizeof(int), 5};
	expectedUtil = (ArrayUtil){result, sizeof(int), 5};

	map(util, resultUtil, increment, &hint);
	
	assert(areEqual(expectedUtil, resultUtil));
	dispose(resultUtil);
}

void increment_by_1(void *hint, void *sourceItem, void *destinationItem){
	*(int*)destinationItem = *(int*)sourceItem+1;
}


void test_map_increments_by_one_all_array_elements(){
	void *hint;
	int array[]={1,2,3,4,5};
	int newArray[]={2,3,4,5,6};
	ArrayUtil util={array,sizeof(int),5};
	ArrayUtil expected={newArray,sizeof(int),5};
	ArrayUtil mapped={calloc(5,sizeof(int)),sizeof(int),5};
	map(util,mapped,increment_by_1,&hint);
	assert(areEqual(expected, mapped));
}

void square(void* hint, void* item){
	*(int*)item = (*(int*)item)*(*(int*)item);
};

void charToUpper(void* hint, void* item){
	*(char*)item = toupper(*(char*)item);
}

void float_increment(void* hint, void* item){
	*(float*)item = (*(float*)item)+(*(float*)hint);
}

void test_forEach_should_do_square_of_all_elements_of_INTEGER_array(){
	int array[5] = {4,5,6,7,8},i;
	util = (ArrayUtil){array,sizeof(int),5};
	forEach(util,square,null);
	for (i = 0; i < util.length; ++i)
	{
		assertEqual(pow(i+4,2),array[i]);
	}
}

void test_forEach_should_increment_all_elements_by_given_hint_of_FLOAT_array(){
	float array[5] = {4.12,5.00,6.1243,7.5436,8.7854},hint = 2.3096;
	int i;
	util = (ArrayUtil){array,sizeof(float),5};
	forEach(util,float_increment,&hint);
		assertEqual((float)6.429600,array[0]);
		assertEqual((float)7.309600,array[1]);
		assertEqual((float)8.433900,array[2]);
		assertEqual((float)9.853200,array[3]);
		assertEqual((float)11.095000,array[4]);
}

void test_forEach_should_convert_alphabets_in_upperCase_of_CHAR_array(){
	char array[5] = {'a','e','I','o','U'};
	util = (ArrayUtil){array,sizeof(char),5};
	forEach(util,charToUpper,null);
	assertEqual('A',array[0]);
	assertEqual('E',array[1]);
	assertEqual('I',array[2]);
	assertEqual('O',array[3]);
	assertEqual('U',array[4]);
}

void intAddOperation(void* hint, void* item) {
	*((int *)item) = *((int *)hint) + *((int *)item);	
}

void test_forEach_gives_2_3_4_5_6_for_1_2_3_4_5_in_same_array(){
	ArrayUtil src = create(sizeof(int),5);
	int *arr,i,hint = 1,*list;
	arr = (int*)src.base;
	for(i=0;i<5;i++){
		arr[i] = i+1;
	}
	list = ((int*)src.base);
	forEach(src,intAddOperation,&hint);
	assertEqual(list[0],2);
	assertEqual(list[1],3);
	assertEqual(list[2],4);
	assertEqual(list[3],5);
	assertEqual(list[4],6);
	dispose(src);
}

void test_forEach_should_convert_alphabets_in_upperCase_of_char_STRING(){
	char array[] = {"Amar Akbar Anthony"};
	char expectedArray[] = {"AMAR AKBAR ANTHONY"};
	util = (ArrayUtil){array,sizeof(char),strlen(array)+1};
	expectedUtil = (ArrayUtil){expectedArray,sizeof(char),strlen(array)+1};
	forEach(util,charToUpper,null);
	assertEqual(areEqual(util, expectedUtil),1);
}

void element_into_element_plus_one(void* hint, void* item){
	*((int *)item)= *((int *)item) * ((*((int *)item))+1);
}


void test_forEach_does_multiplication_of_item_with_item_plus_one(){
	void *hint;
	int array[]={1,2,3,4,5};
	int incremented[]={2,6,12,20,30};
	ArrayUtil util={array,sizeof(int),5};
	ArrayUtil expected={incremented,sizeof(int),5};
	forEach(util,element_into_element_plus_one,&hint);
	assert(areEqual(util,expected));
}

void *add_all(void* hint, void* previousItem, void* item){
	*((int*)item)= *((int*)previousItem) + *((int*)item);
	return ((int*)item);
}


void test_reduce_gives_15_when_elements_are_1_2_3_4_5_and_initial_value_is_0(){
	int intialValue=0;
	int array[]={1,2,3,4,5};
	ArrayUtil util={array,sizeof(int),5};
	void *return_value=reduce(util,add_all,null,&intialValue);
	assertEqual(*((int*)return_value),15);
}

void test_reduce_gives_30_when_elements_are_1_2_3_4_5_and_initial_value_is_15(){
	int intialValue=15;
	int array[]={1,2,3,4,5};
	ArrayUtil util={array,sizeof(int),5};
	void *return_value=reduce(util,add_all,null,&intialValue);
	assertEqual(*((int*)return_value),30);
}

void test_reduce_returns_sum_of_all_integers_of_array (){
	int hint = 2,result;
	int initial_value = 0;
	int array[] = {1,2,3};
	ArrayUtil util = create(sizeof(int),3);
	util.base = (void*)array;
	result = *(int*)reduce(util,add_all,(void*)&hint,(void*)&initial_value);
	assertEqual(result,6);
}

void* float_add_all(void* hint, void* previousItem, void* item){
	*((float*)item)= *((float*)previousItem) + *((float*)item);
	return ((float*)item);
}

void test_reduce_float_should_return_sum_of_all_elemnts_including_initial_value(){
	float intialValue=100.85671;
	float array[5] = {0.000314,2.3412,9.076,99.999,5.8970};
	util=(ArrayUtil){array,sizeof(float),5};
	assertEqual(*(float*)reduce(util,float_add_all,null,&intialValue),(float)218.170227);
}

void* greatest_char(void* hint, void* previousItem, void* item){
	return (*((char*)previousItem) > *((char*)item)) ? previousItem : item;
}

void test_reduce_char_should_return_greatest_character_in_given_STRING(){
	char intialValue='A';
	char array[] = "Mujhe peene ka shock nahin";
	util=(ArrayUtil){array,sizeof(char),strlen(array)};
	assertEqual(*(char*)reduce(util,greatest_char,null,&intialValue),'u');
}

void test_create_001(){
	int array_0_0[2] = {0, 0};
	log("returns an ArrayUtil with bytes initialized to ZERO for int");
	ArrayUtil util1 = {array_0_0, sizeof(int), 2};
	ArrayUtil util2 = create(sizeof(int), 2);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}

void test_create_002(){
	log("returns an ArrayUtil with bytes initialized to NULL for char");
	char array_null_null[2] = {'\0', '\0'};
	ArrayUtil util1 = {array_null_null, sizeof(char), 2};
	ArrayUtil util2 = create(sizeof(char), 2);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_003(){
	log("returns an ArrayUtil with bytes initialized to ZERO for float");
	float array_flt_flt[2] = {0, 0};
	ArrayUtil util1 = {array_flt_flt, sizeof(float), 2};
	ArrayUtil util2 = create(sizeof(float), 2);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_004(){
	log("returns an ArrayUtil with bytes initialized to ZERO for double");
	double array_dble_dble[2] = {0, 0};
	ArrayUtil util1 = {array_dble_dble, sizeof(double), 2};
	ArrayUtil util2 = create(sizeof(double), 2);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_005(){
	typedef char String[256];
	log("returns an ArrayUtil with bytes initialized to ZERO for char[256]");
	String array_empty_strings[2] = {"", ""};
	ArrayUtil util1 = {array_empty_strings, sizeof(String), 2};
	ArrayUtil util2 = create(sizeof(String), 2);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_006(){
	typedef int int10[10];
	log("returns an ArrayUtil with bytes initialized to ZERO for int[10]");
	int10 array_int10_0s[1] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	ArrayUtil util1 = {array_int10_0s, sizeof(int10), 1};
	ArrayUtil util2 = create(sizeof(int10), 1);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_007(){
	typedef float float5[5];
	float5 array_float5_0s[1] = {{0.0, 0.0, 0.0, 0.0, 0.0}};
	log("returns an ArrayUtil with bytes initialized to ZERO for float[5]");
	ArrayUtil util1 = {array_float5_0s, sizeof(float5), 1};
	ArrayUtil util2 = create(sizeof(float5), 1);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_008(){
	log("returns an ArrayUtil with bytes initialized to ZERO for struct");
	typedef struct Stud { char name[27]; int std; float percentage; } Student;
	Student array_Students[1] = {{"", 0, 0.0}};
	ArrayUtil util1 = {array_Students, sizeof(Student), 1};
	ArrayUtil util2 = create(sizeof(Student), 1);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_009(){
	log("returns an ArrayUtil with bytes initialized to ZERO for void *");
	typedef void *void_star;
	void_star array_void_stars[1] = {0x0};
	ArrayUtil util1 = {array_void_stars, sizeof(void_star), 1};
	ArrayUtil util2 = create(sizeof(void_star), 1);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_010(){
	log("returns an ArrayUtil with bytes initialized to ZERO for char *");
	typedef char *char_star;
	char_star array_char_stars[1] = {(char *)('\0')};
	ArrayUtil util1 = {array_char_stars, sizeof(char_star), 1};
	ArrayUtil util2 = create(sizeof(char_star), 1);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}
void test_create_011(){
	log("returns an ArrayUtil with bytes initialized to ZERO for int *");
	typedef int *int_star;
	int_star array_int_stars[1] = {(int *)(0)};
	ArrayUtil util1 = {array_int_stars, sizeof(int_star), 1};
	ArrayUtil util2 = create(sizeof(int_star), 1);
	assertEqual(areEqual(util1, util2), 1);
	dispose(util2);
}

 //findFirst and findLas with STRUCT>>>>>
typedef struct Stud { char name[27]; int std; float percentage; } Student_siddhu;
Student_siddhu array_3_Students[3] = {{"Abu", 2, 88.5},{"Babu", 2, 98.25},{"Cbabu", 2, 68.0}};
int hasPassed(void* hint, void *item){
	Student_siddhu student = *(Student_siddhu*)item;
	float passMark = *(float*)hint;
	return (student.percentage >= passMark);
}
void test_findLast_returns_the_last_student_who_has_passed_the_exam_struct_array(){
	ArrayUtil a = {array_3_Students,sizeof(Student_siddhu),3};
	Student_siddhu *got;
	String name;
	float passMark = 80.0;
	got = (Student_siddhu*)findLast(a,hasPassed,&passMark);
	assertEqual(strcmp((*got).name,"Babu"),0);
}
void test_findFirst_returns_the_first_student_who_has_passed_the_exam_struct_array(){
	ArrayUtil a = {array_3_Students,sizeof(Student_siddhu),3};
	Student_siddhu *got;
	String name;
	float passMark = 80.0;
	got = (Student_siddhu*)findFirst(a,hasPassed,&passMark);
	assertEqual(strcmp((*got).name,"Abu"),0);
}