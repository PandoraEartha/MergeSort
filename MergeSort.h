#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <new>

template<typename Type>
static inline void MergeSort(Type* array,const unsigned long long length);

namespace MergeSortImplementation{

const unsigned SmallSortLength=16;

template<typename Type>
struct MergeSortStackData{
    Type* array0;
    Type* array1;
    unsigned long long mergeLength;
};

template<typename Type>
struct MergeSortStack{
    unsigned length;
    MergeSortStackData<Type> data[64];
};

template<typename Type>
static inline void Swap(Type* array,const unsigned long long index0,const unsigned long long index1){
    Type temporary=std::move(array[index0]);
    array[index0]=std::move(array[index1]);
    array[index1]=std::move(temporary);
}

template<typename Type>
static inline bool Compare(const Type* array0,const Type* array1,const unsigned long long index0,const unsigned long long index1){
    return array0[index0]<=array1[index1];
}

template<typename Type>
static inline void CompareSwap(Type* array,const unsigned long long index0,const unsigned long long index1){
    if(array[index0]>array[index1]){
        Swap(array,index0,index1);
    }
}

template<typename Type>
static inline void MemoryCopy(Type* destination,Type* source,const unsigned long long count){
    if constexpr(std::is_trivially_copyable_v<Type>){
        memcpy((void*)destination,(const void*)source,sizeof(Type)*count);
    }else{
        for(unsigned long long index=0;index<count;index=index+1){
            destination[index]=std::move(source[index]);
        }
    }
}

template<typename Type>
static inline Type* MemoryAllocate(const unsigned long long count){
    if constexpr(std::is_trivially_copyable_v<Type>){
        return (Type*)malloc(sizeof(Type)*count);
    }else{
        Type* array=(Type*)malloc(sizeof(Type)*count);
        for(unsigned long long index=0;index<count;index=index+1){
            new(array+index)Type();
        }
        return array;
    }
}

template<typename Type>
static inline void MemoryFree(Type* pointer,const unsigned long long count){
    for(unsigned long long index=0;index<count;index=index+1){
        pointer[count].~Type();
    }
    free(pointer);
}

template<typename Type>
static inline long long int BinarySearch(const Type* array,Type number,long long int right){
    long long int left=0;
    do{
        long long int index=(left+right)>>1;
        if(array[index]>number){
            right=index;
            continue;
        }
        if(array[index]<number){
            left=index+1;
            continue;
        }
        return index+1;
    }while(right>left);
    return left;
}

template<typename Type>
static inline void BubbleSort(Type* array){
    for(unsigned index0=0;index0<SmallSortLength;index0=index0+1){
        for(unsigned index1=0;index1<SmallSortLength-index0-1;index1=index1+1){
            CompareSwap(array,index1,index1+1);
        }
    }
}

template<typename Type>
static inline void InsertSort(Type* array,const unsigned char length){
    for(unsigned index=1;index<length;index=index+1){
        const Type temporary=std::move(array[index]);
        unsigned indexCompare=index-1;
        while(array[indexCompare]>temporary){
            array[indexCompare+1]=std::move(array[indexCompare]);
            if(!indexCompare){
                break;
            }
            indexCompare=indexCompare-1;
        }
        array[indexCompare]=std::move(temporary);
    }
}

template<typename Type>
static inline void SmallSizeSort(Type* array){
    #if 0
    BubbleSort(array);
    #endif
    #if 0
    // shell sort
    // gap=1,2,4,8
    const unsigned length=SmallSortLength;
    for(unsigned gap=SmallSortLength>>1;gap>0;gap=gap>>1){
        for(unsigned begin=0;begin<gap;begin=begin+1){
            for(unsigned order=begin+gap;order<length;order=order+gap){
                Type biggest=array[order];
                long long int indexCompare=order-gap;
                while(indexCompare>=0&&array[indexCompare]>biggest){
                    array[indexCompare+gap]=array[indexCompare];
                    indexCompare=indexCompare-gap;
                }
                array[indexCompare+gap]=biggest;
            }
        }
    }
    #endif
    #if 1
    // insert sort
    #if 0
    for(unsigned index=1;index<SmallSortLength;index=index+1){
        Type biggest=array[index];
        unsigned long long indexInsert=BinarySearch(array,biggest,index);
        for(unsigned long long indexSwap=index;indexSwap>indexInsert;indexSwap=indexSwap-1){
            array[indexSwap]=array[indexSwap-1];
        }
        array[indexInsert]=biggest;
    }
    #else
    InsertSort(array,SmallSortLength);
    #endif
    #endif
    #if 0
    CompareSwap(array,0, 1);CompareSwap(array, 2, 3);CompareSwap(array, 4, 5);CompareSwap(array, 6, 7);
    CompareSwap(array,8, 9);CompareSwap(array,10,11);CompareSwap(array,12,13);CompareSwap(array,14,15);
    CompareSwap(array,0, 2);CompareSwap(array, 1, 3);CompareSwap(array, 4, 6);CompareSwap(array, 5, 7);
    CompareSwap(array,8,10);CompareSwap(array, 9,11);CompareSwap(array,12,14);CompareSwap(array,13,15);
    CompareSwap(array,0, 4);CompareSwap(array, 1, 5);CompareSwap(array, 2, 6);CompareSwap(array, 3, 7);
    CompareSwap(array,8,12);CompareSwap(array, 9,13);CompareSwap(array,10,14);CompareSwap(array,11,15);
    CompareSwap(array,0, 8);CompareSwap(array, 1, 9);CompareSwap(array, 2,10);CompareSwap(array, 3,11);
    CompareSwap(array,4,12);CompareSwap(array, 5,13);CompareSwap(array, 6,14);CompareSwap(array, 7,15);
    CompareSwap(array,5,10);CompareSwap(array, 6, 9);
    CompareSwap(array,3,12);CompareSwap(array, 7,11);CompareSwap(array,13,14);CompareSwap(array, 1, 2);CompareSwap(array, 4, 8);
    CompareSwap(array,1, 4);CompareSwap(array, 7,13);CompareSwap(array, 2, 8);CompareSwap(array,11,14);
    CompareSwap(array,2, 4);CompareSwap(array, 5, 6);CompareSwap(array, 9,10);CompareSwap(array,11,13);
    CompareSwap(array,3, 8);CompareSwap(array, 7,12);
    CompareSwap(array,6, 8);CompareSwap(array,10,12);CompareSwap(array, 3, 5);CompareSwap(array, 7, 9);
    CompareSwap(array,3, 4);CompareSwap(array, 5, 6);CompareSwap(array, 7, 8);CompareSwap(array, 9,10);CompareSwap(array,11,12);
    CompareSwap(array,6, 7);CompareSwap(array, 8, 9);
    #endif
    #if 0
    std::sort(array,array+SmallSortLength);
    #endif
}

template<typename Type>
static inline void PushStack(MergeSortStack<Type>* stack,Type* array0,Type* array1,const unsigned long long mergeLength){
    stack->data[stack->length].array0=array0;
    stack->data[stack->length].array1=array1;
    stack->data[stack->length].mergeLength=mergeLength;
    stack->length=stack->length+1;
}

template<typename Type>
static inline void PopStack(MergeSortStack<Type>* stack,const bool exchangeArray0){
    stack->data[stack->length-2].mergeLength=stack->data[stack->length-2].mergeLength+stack->data[stack->length-1].mergeLength;
    if(exchangeArray0){
        Type* temporary=stack->data[stack->length-2].array0;
        stack->data[stack->length-2].array0=stack->data[stack->length-2].array1;
        stack->data[stack->length-2].array1=temporary;
    }
    stack->length=stack->length-1;
}

template<typename Type>
static inline bool NeedToMerge(MergeSortStack<Type>* stack,Type** mergeArray0,Type** mergeArray1,Type** copyArray,unsigned long long* mergeLength){
    if(stack->length>1&&stack->data[stack->length-1].mergeLength==stack->data[stack->length-2].mergeLength){
        *(mergeArray0)=stack->data[stack->length-2].array0;
        *(mergeArray1)=stack->data[stack->length-1].array0;
        *(copyArray)=stack->data[stack->length-2].array1;
        *(mergeLength)=stack->data[stack->length-2].mergeLength;
        return true;
    }
    return false;
}

template<typename Type>
static inline void ClearStack(MergeSortStack<Type>* stack){
    stack->length=0;
}

template<typename Type>
static inline void Merge(Type* mergeArray0,Type* mergeArray1,Type* mergeCopyArray,const unsigned long long mergeLength0,const unsigned long long mergeLength1){
    unsigned long long index0=0;
    unsigned long long index1=0;
    unsigned long long indexCopy=0;
    while(true){
        if(Compare(mergeArray0,mergeArray1,index0,index1)){
            mergeCopyArray[indexCopy]=std::move(mergeArray0[index0]);
            index0=index0+1;
            indexCopy=indexCopy+1;
            if(index0==mergeLength0){
                MemoryCopy(mergeCopyArray+indexCopy,mergeArray1+index1,mergeLength1-index1);
                break;
            }
        }else{
            mergeCopyArray[indexCopy]=std::move(mergeArray1[index1]);
            index1=index1+1;
            indexCopy=indexCopy+1;
            if(index1==mergeLength1){
                MemoryCopy(mergeCopyArray+indexCopy,mergeArray0+index0,mergeLength0-index0);
                break;
            }
        }
    }
}

namespace UnequalLength{

template<typename Type>
static inline bool NeedToMerge(MergeSortStack<Type>* stack,Type** mergeArray0,Type** mergeArray1,Type** copyArray,unsigned long long* mergeLength0,unsigned long long* mergeLength1){
    if(stack->length>1){
        *(mergeArray0)=stack->data[stack->length-2].array0;
        *(mergeArray1)=stack->data[stack->length-1].array0;
        *(copyArray)=stack->data[stack->length-2].array1;
        *(mergeLength0)=stack->data[stack->length-2].mergeLength;
        *(mergeLength1)=stack->data[stack->length-1].mergeLength;
        return true;
    }
    return false;
}

}

// length can be any number
template<typename Type>
static inline void MergeSort(Type* array,const unsigned long long length){
    if((!array)||(length<2)){
        return;
    }
    if(length<=SmallSortLength){
        InsertSort(array,length);
        return;
    }
    unsigned long long maxSortedLength=2;
    if(array[0]>array[1]){
        bool allReserve=true;
        for(unsigned long long index=2;index<length;index=index+1){
            if(array[index-1]>=array[index]){
                maxSortedLength=maxSortedLength+1;
            }else{
                allReserve=false;
                break;
            }
        }
        for(unsigned long long index0=0,index1=maxSortedLength-1;index0<index1;index0=index0+1,index1=index1-1){
            Swap(array,index0,index1);
        }
        if(allReserve){
            return;
        }
    }else{
        bool allSorted=true;
        for(unsigned long long index=2;index<length;index=index+1){
            if(array[index-1]<=array[index]){
                maxSortedLength=maxSortedLength+1;
            }else{
                allSorted=false;
                break;
            }
        }
        if(allSorted){
            return;
        }
    }
    maxSortedLength=(maxSortedLength/(unsigned long long)SmallSortLength)*(unsigned long long)SmallSortLength;
    unsigned long long regularLength=(length/SmallSortLength)*SmallSortLength;
    Type* copyArray=MemoryAllocate<Type>(length);
    MergeSortStack<Type> stack;
    ClearStack(&stack);
    Type* mergeArray0;
    Type* mergeArray1;
    Type* mergeCopyArray;
    if(maxSortedLength){
        PushStack(&stack,array,copyArray,maxSortedLength);
    }
    for(unsigned long long shellIndex=maxSortedLength;shellIndex<regularLength;shellIndex=shellIndex+SmallSortLength){
        SmallSizeSort(array+shellIndex);
        PushStack(&stack,array+shellIndex,copyArray+shellIndex,SmallSortLength);
        unsigned long long mergeLength;
        while(NeedToMerge(&stack,&mergeArray0,&mergeArray1,&mergeCopyArray,&mergeLength)){
            bool exchangeArray0=true;
            if(mergeArray0[mergeLength-1]>mergeArray1[0]){
                Merge(mergeArray0,mergeArray1,mergeCopyArray,mergeLength,mergeLength);
            }else{
                exchangeArray0=false;
                if(mergeArray0+mergeLength!=mergeArray1){
                    MemoryCopy(mergeArray0+mergeLength,mergeArray1,mergeLength);
                }
            }
            PopStack(&stack,exchangeArray0);
        }
    }
    unsigned long long mergeLength0,mergeLength1;
    if(length>regularLength){
        InsertSort(array+regularLength,length-regularLength);
        PushStack(&stack,array+regularLength,copyArray+regularLength,length-regularLength);
    }
    while(UnequalLength::NeedToMerge(&stack,&mergeArray0,&mergeArray1,&mergeCopyArray,&mergeLength0,&mergeLength1)){
        bool exchangeArray0=true;
        if(mergeArray0[mergeLength0-1]>mergeArray1[0]){
            Merge(mergeArray0,mergeArray1,mergeCopyArray,mergeLength0,mergeLength1);
        }else{
            exchangeArray0=false;
            if(mergeArray0+mergeLength0!=mergeArray1){
                MemoryCopy(mergeArray0+mergeLength0,mergeArray1,mergeLength1);
            }
        }
        PopStack(&stack,exchangeArray0);
    }
    if(stack.data[0].array0==copyArray){
        MemoryCopy(array,copyArray,length);
    }
    MemoryFree(copyArray,length);
}

}

// length can be any number
template<typename Type>
static inline void MergeSort(Type* array,const unsigned long long length){
    MergeSortImplementation::MergeSort(array,length);
}

#endif // MergeSort.h