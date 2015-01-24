typedef struct ArrayUtil ArrayUtil;
struct ArrayUtil {
	void *base;
	int typeSize;
	int length;
};
#define null '\0'
typedef struct{
	char name[3];
	int roll;
	float percentage;
} student;

int areEqual(ArrayUtil, ArrayUtil);
ArrayUtil create(int , int);
ArrayUtil resize(ArrayUtil, int);
int findIndex(ArrayUtil, void*);
void dispose(ArrayUtil);
typedef int (MatchFunc)(void *, void *);
typedef char* String;
void* findFirst(ArrayUtil, MatchFunc*, void*);
void* findLast(ArrayUtil, MatchFunc*, void*);
int count(ArrayUtil ,MatchFunc*, void*);
int filter(ArrayUtil, MatchFunc*, void*, void**, int);
typedef void (ConvertFunc)(void*, void*, void*);
void map(ArrayUtil, ArrayUtil, ConvertFunc*, void*);
typedef void (OperationFunc)(void*, void*);
void forEach(ArrayUtil, OperationFunc*, void*);