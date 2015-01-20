typedef struct ArrayUtil ArrayUtil;
struct ArrayUtil {
	void *base;
	int typeSize;
	int length;
};
int areEqual(ArrayUtil, ArrayUtil);
ArrayUtil create(int , int);
ArrayUtil resize(ArrayUtil, int);
int findIndex(ArrayUtil, void*);
void dispose(ArrayUtil);
typedef int (MatchFunc)(void *, void *);
void* findFirst(ArrayUtil, MatchFunc*, void*);