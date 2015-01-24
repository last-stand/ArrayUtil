#include "expr_assert.h"
#include "arrayUtil.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void test_areEqual_returns_0_when_length_is_equal_but_typeSize_is_not_equal(){
	int array1[]={1,2,3,4,5};
	char array2[]={'a','b','c','d','\0'};
	ArrayUtil u1={array1,sizeof(int),5};
	ArrayUtil u2={array2,sizeof(char),5};
	assertEqual(areEqual(u1,u2), 0);
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

void test_filter_should_filter_those_elements_which_are_matching_given_the_criteria(){
	int arr[] = {1,2,3,4,5},result,i,expected[] = {2,4};
	void *destination;
	util = create(sizeof(int),5);
	util.base = arr;
	result = filter(util, isEven, null, &destination, 5);	
	for (i = 0; i < 2; ++i)
	{
		assert(((int*)destination)[i] == expected[i]);
	}
	assert(result == 2);
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
	void *hint;
	int array[]={1,2,3,4,5}, newArray[]={1,4,9,16,25};
	util=(ArrayUtil){calloc(5,sizeof(int)),sizeof(int),5};
	util = (ArrayUtil){array,sizeof(int),5};
	expectedUtil = (ArrayUtil){newArray,sizeof(int),5};
	map(util,util,square_elements,&hint);
	assert(areEqual(expectedUtil, util));
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