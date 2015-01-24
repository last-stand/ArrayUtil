#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayUtil.h"

int areEqual(ArrayUtil a, ArrayUtil b){
	int i;
	char *a_array = (char*)a.base;
	char *b_array = (char*)b.base;
	if(a.length != b.length || a.typeSize != b.typeSize)
		return 0;
	for(i=0;i<a.length;i++){
		if(a_array[i*a.typeSize] != b_array[i*b.typeSize])
			return 0;
	}
	return 1;
}

ArrayUtil create(int typeSize, int length){
	ArrayUtil new_array;
	new_array.length = length;
	new_array.typeSize = typeSize;
	new_array.base =  calloc(length,typeSize);
	return new_array;
}

ArrayUtil resize(ArrayUtil util, int length) {
	char *previousArray = (char *)(util.base);
	char *resizedArray = calloc(length,util.typeSize);
	if(util.typeSize*length > util.typeSize*util.length)
		memcpy(resizedArray, previousArray, util.typeSize*util.length);
	else
		memcpy(resizedArray, previousArray, util.typeSize*length);
	util.base = resizedArray;
	util.length=length;
	return util;
}

int findIndex(ArrayUtil util,void* element)
{
	int i,exist,*item;
	for(i=0;i<util.length;i++)
	{
		item = util.base+(util.typeSize*i);
		exist = memcmp(item,element,util.typeSize);
		if(exist==0) return i;
	}
	return -1;
}

void dispose(ArrayUtil util){
	util.typeSize = 0;
	util.length = 0;
	free(util.base);
}

void* findFirst(ArrayUtil util, MatchFunc* match, void* hint){
	char *array = util.base;
	int i,*element;
	for(i=0;i<util.length;i++){
		element = util.base+util.typeSize*i;
		if(match(hint, element)){
			return util.base + (i * util.typeSize);
		}
	}
	return NULL;
}

void* findLast(ArrayUtil util, MatchFunc* match, void* hint){
	int *array = util.base;
	int i,*element;
	for(i=util.length-1;i>=0;i--){
		element = util.base+util.typeSize*i;
		if(match(hint,element)){
			return util.base + (i*util.typeSize);
		}
	}
	return NULL;
}

int count(ArrayUtil util, MatchFunc* match, void* hint){
	int i,count = 0;
	for(i=0;i<util.length;i++){
		count +=  match(hint, util.base + (i*util.typeSize));
	}
	return count;
}

int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems ){
	int i,count=0;
	void* item;
	*destination = calloc(maxItems,util.typeSize);
	for (i = 0; i < util.length && count < maxItems; ++i)
	{ 
		item = util.base + (i*util.typeSize);
		if(match(hint, item)){
			memcpy(&((*destination)[count*util.typeSize]),item,util.typeSize);
			++count;
		}
	}
	return count;
}

void map(ArrayUtil source, ArrayUtil destination, ConvertFunc* convert, void* hint){
	int i;
	void *sourceItem = source.base, *destinationItem = destination.base;
	for (i = 0; i < source.length; ++i){
		convert(hint, &sourceItem[i*source.typeSize], &destinationItem[i*destination.typeSize]);
	}
};

void forEach(ArrayUtil util, OperationFunc* operation, void* hint){
	int i;
	void **item;
	for (i = 0; i < util.length; ++i){
		item = util.base + (util.typeSize*i);
		operation(hint,item);
	}
};