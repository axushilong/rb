/**
 * @file    rb.c
 * @github  https://github.com/axushilong
 * @version v0.0.1
 * @date    2022.04.07
 * @brief   
 */
#include "rb.h"

void vRbInit(stRbType *pstRb,unsigned char *pucArray,RbSizeType usArrayLength){
    pstRb->pucBuffer = pucArray;
    pstRb->usBufferLength = usArrayLength;
    pstRb->usHeadIndex = 0;
    pstRb->usTailIndex = 0;
}
void vRbWrite(stRbType *pstRb,unsigned char ucData){
    pstRb->pucBuffer[pstRb->usHeadIndex] = ucData;
    pstRb->usHeadIndex = ((pstRb->usHeadIndex + 1) & pstRb->usBufferLength);
}
void vRbWriteArray(stRbType *pstRb,unsigned char *pucArray,RbSizeType usArrayLength){
    RbSizeType usI;
    for(usI = 0;usI<usArrayLength;usI++){
        vRbWrite(pstRb,pucArray[usI]);
    }
}
unsigned char ucRbRead(stRbType *pstRb,unsigned char *pucData){
    if(ucRbIsEmpty(pstRb)){
        return 0;
    }else{}
    *pucData = pstRb->pucBuffer[pstRb->usTailIndex];
    pstRb->usTailIndex = ((pstRb->usTailIndex +1) & pstRb->usBufferLength);
    return 1;
}
RbSizeType usRbReadArray(stRbType *pstRb,unsigned char *pucArray,RbSizeType usArrayLength){
    RbSizeType usI = 0;
    unsigned char *pucData = pucArray;
    if(ucRbIsEmpty(pstRb)){
        return 0;
    }else{}
    while( (usI < usArrayLength) && ucRbRead(pstRb,pucData) ){
        usI++;
        pucData++;
    }
    return usI;
}
unsigned char ucRbView(stRbType *pstRb,RbSizeType usIndex,unsigned char *pucData){
    RbSizeType usViewIndex;
    if( usIndex >= usRbDataLength(pstRb) ){/*查看处无数据*/
        return 0;
    }else{}
    usViewIndex = ( (pstRb->usTailIndex+usIndex) & pstRb->usBufferLength );
    *pucData = pstRb->pucBuffer[usViewIndex];
    return 1;
}
RbSizeType usRbViewArray(stRbType *pstRb,RbSizeType usIndex,RbSizeType usArrayLength,unsigned char *pucArray){
    RbSizeType usViewLength = 0;
    unsigned char *pucArrayTmp = pucArray;
//    RbSizeType usViewIndex;
    RbSizeType usRbLength = usRbDataLength(pstRb);
    if( usIndex >= usRbLength ){/*查看处无数据*/
        return 0;
    }else{}
    // usViewIndex = ( (pstRb->usTailIndex+usIndex) & pstRb->usBufferLength );
    // *pucData = pstRb->pucBuffer[usViewIndex];
    while( (usViewLength < usArrayLength) && ucRbView(pstRb,usIndex+usViewLength,pucArrayTmp) ){
        usViewLength++;
        pucArrayTmp++;
    }
    return usViewLength;
    // usViewLength = usRbLength - usIndex;/*可查看长度*/
    // if(usArrayLength > usViewLength){
    //     memcpy();
    //     return usViewLength;
    // }else{
    //     memcpy();
    //     return usArrayLength;
    // }
}

// extern INLINE void vRbReset(stRbType *pstRb);
// extern INLINE unsigned char ucRbIsEmpty(stRbType *pstRb);
// extern INLINE unsigned char ucRbIsFull(stRbType *pstRb);
// extern INLINE RbSizeType ucRbDataLength(stRbType *pstRb);
