/**
 * @file    rb.h
 * @github  https://github.com/axushilong
 * @version v0.0.1
 * @date    2022.04.07
 * @brief   
 */
#ifndef __RB_H_
#define __RB_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned short RbSizeType;

typedef struct {
    unsigned char  *pucBuffer;
    RbSizeType usBufferLength;/*从0开始算，实际值+1为真实长度*/
    RbSizeType usHeadIndex;
    RbSizeType usTailIndex;
}stRbType;

/**
 * @brief   Rb初始
 * @param   [in] pstRb 要初始化的Rb
 * @param   [in] pucArray 关联的数组名
 * @param   [in] usArrayLength 数组长度
 * @return  VOID_T
 * @note    长度必须是2^x。
 */
void vRbInit(stRbType *pstRb,unsigned char *pucArray,RbSizeType usArrayLength);
/**
 * @brief   Rb复位
 * @param   [in] pstRb 要复位的Rb
 * @return  VOID_T
 * @note    Rb复位就是将Rb清空到初始状态。
 */
static inline void vRbReset(stRbType *pstRb){
    pstRb->usHeadIndex = 0;
    pstRb->usTailIndex = 0;
}
/**
 * @brief   写一个字节到Rb,必须要保证有可写空间时才可写入
 * @param   [in] pstRb 要写入的Rb
 * @param   [in] ucData 要写入的字节
 * @return  VOID_T
 * @note    必须要保证有可写空间时才可写入
 */
void vRbWrite(stRbType *pstRb,unsigned char ucData);
/**
 * @brief   写一个数组到Rb,必须要保证有足够的可写空间时才可写入
 * @param   [in] pstRb 要写入的Rb
 * @param   [in] pucArray 要写入的数组
 * @param   [in] usArrayLength 要写入的数组长度
 * @return  VOID_T
 * @note    必须要保证有足够的可写空间时才可写入
 */
void vRbWriteArray(stRbType *pstRb,unsigned char *pucArray,RbSizeType usArrayLength);
/**
 * @brief   从Rb读出一个字节
 * @param   [in] pstRb 要读的Rb
 * @param   [out] pucData 要读出的字节
 * @return  1 成功读出, 0 读出失败或其他
 * @note    
 */
unsigned char ucRbRead(stRbType *pstRb,unsigned char *pucData);
/**
 * @brief   从pstRb读出usArrayLength个数据到数组pucArray
 * @param   [in] pstRb 要读的Rb
 * @param   [out] pucArray 要读出的数组
 * @param   [in] usArrayLength 要读出的数组长度
 * @return  RbSizeType 返回实际读出的数据长度。
 * @note    
 */
RbSizeType usRbReadArray(stRbType *pstRb,unsigned char *pucArray,RbSizeType usArrayLength);
/**
 * @brief   查看 pstRb 的 usIndex 处的数据到pucData
 * @param   [in] pstRb 要查看的Rb
 * @param   [in] usIndex 要查看到的位置
 * @param   [out] pucData 要查看到的字节
 * @return  1 成功查看, 0 查看失败或其他
 * @note    usIndex是相对pstRb->usTailIndex处从0开始的。
 */
unsigned char ucRbView(stRbType *pstRb,RbSizeType usIndex,unsigned char *pucData);
/**
 * @brief   查看pstRb的usIndex处开始的usArrayLength个数据到pucArray中,保证pucArray的空间有足够的长度(>=usArrayLength)
 * @param   [in] pstRb 要查看的Rb
 * @param   [in] usIndex 要查看到的起始位置
 * @param   [in] usArrayLength 要查看的长度
 * @param   [out] pucArray 查看到的数组
 * @return  RbSizeType 返回实际查看到的长度
 * @note    保证pucArray的空间有足够的长度(>=usArrayLength)
 */
RbSizeType usRbViewArray(stRbType *pstRb,RbSizeType usIndex,RbSizeType usArrayLength,unsigned char *pucArray);
/**
 * @brief   判断Rb是否空
 * @param   pstRb 要判断的Rb
 * @return  1 空 0 其他
 * @note    
 */
static inline unsigned char ucRbIsEmpty(stRbType *pstRb){
    return (pstRb->usHeadIndex == pstRb->usTailIndex);
}
/**
 * @brief   判断Rb是否已满
 * @param   pstRb 要判断的Rb
 * @return  1 满 0 其他
 * @note    只剩一个字节可写为满状态
 */
static inline unsigned char ucRbIsFull(stRbType *pstRb){
    return ((pstRb->usHeadIndex - pstRb->usTailIndex) & pstRb->usBufferLength) == pstRb->usBufferLength;//只剩最后一个字节
}
/**
 * @brief   返回Rb中可取出数据长度
 * @param   pstRb 要查验的Rb
 * @return  返回实际可取出数据长度
 * @note    
 */
static inline RbSizeType usRbDataLength(stRbType *pstRb){
    return ((pstRb->usHeadIndex - pstRb->usTailIndex) & pstRb->usBufferLength);
}





#ifdef __cplusplus
}
#endif
#endif
