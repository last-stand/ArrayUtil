#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayUtil.h"

int areEqual(ArrayUtil a, ArrayUtil b){
	int i=0;
	int *a_array = (int*)a.base;
	int *b_array = (int*)b.base;
	if(a.length != b.length)
		return 0;
	while(i < a.length){
		if(a_array[i] != b_array[i])
			return 0;;
		++i;
	}
	return 1;
}

ArrayUtil create(int typeSize, int length){
	void * array = calloc(length,typeSize);
	ArrayUtil new_array;
	new_array.length = length;
	new_array.typeSize = typeSize;
	new_array.base = array;
	return new_array;
}

ArrayUtil resize(ArrayUtil util, int length) {
	int *old_array = (int *)(util.base);
	int *array = calloc(length,sizeof(util.typeSize));
	int i=0;
	while(i<length){
		if(i < util.length)
			array[i]=old_array[i];
		i++;
	}
	util.base = array;
	util.length = length;
	return util;
}

int findIndex(ArrayUtil util, void* element){
	int *array = (int*)util.base;
	int i;
	int element_to_search = *(int*)element;
	for(i=0;i<util.length;i++){
		if(array[i] == element_to_search)
			return i;
	}
	return -1;
}

void dispose(ArrayUtil util){
	util.typeSize = 0;
	util.length = 0;
	util.base = 0;
	free((void *)util.base);
}