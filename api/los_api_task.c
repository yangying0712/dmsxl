/*----------------------------------------------------------------------------
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2021. All rights reserved.
 * Description: LiteOS Kernel Task Demo Implementation
 * Author: Huawei LiteOS Team
 * Create: 2013-01-01
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --------------------------------------------------------------------------- */
/*
对应中文翻译：
版权所有 (c) 华为技术有限公司 2013-2021。保留所有权利。

描述：LiteOS内核任务演示实现

作者：华为LiteOS团队

创建日期：2013-01-01

以源代码和二进制形式重新分发和使用，无论是否经过修改，

都必须满足以下条件：

源代码的重新分发必须保留上述版权声明、本条件列表及以下免责声明。

以二进制形式重新分发时，必须在文档和/或其他材料中复制上述版权声明、

本条件列表及以下免责声明，并提供分发内容。

未经版权持有人事先书面特别许可，不得使用版权持有人或其贡献者的名称

来认可或推广基于此软件的衍生产品。

本软件按"原样"提供，版权持有人及贡献者不提供任何明示或默示担保，

包括但不限于对适销性和特定用途适用性的默示担保。无论在任何情况下，

版权持有人或贡献者均不对任何直接、间接、附带、特殊、示范性或

结果性损害（包括但不限于采购替代商品或服务；使用、数据或利润损失；

或业务中断）承担责任，无论是因何种责任理论（无论是合同责任、严格责任

或侵权行为（包括疏忽或其他））引起，即使已被告知发生此类损害的可能性。
*/
#include "los_api_task.h"
#include "los_task.h"
#include "los_inspect_entry.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define HI_TASK_PRIOR       4
#define LO_TASK_PRIOR       5
#define DELAY_INTERVAL1     5
#define DELAY_INTERVAL2     10
#define DELAY_INTERVAL3     40

STATIC UINT32 g_demoTaskHiId;
STATIC UINT32 g_demoTaskLoId;

STATIC UINT32 HiTaskEntry(VOID)
{
    UINT32 ret;

    printf("Enter high priority task handler.\n");
    //中文：进入高优先级任务处理程序
    /* task delay 5 ticks, task will be suspend */
    //中文：延迟5个tick，任务将被挂起
    ret = LOS_TaskDelay(DELAY_INTERVAL1);
    if (ret != LOS_OK) {
        printf("Delay task failed.\n");
        return LOS_NOK;
    }

    /* task resumed */
    //中文：任务恢复
    printf("High priority task LOS_TaskDelay successfully.\n");
    //中文：高优先级任务延迟成功
    
    /* suspend self */
    //中文：挂起自己
    ret = LOS_TaskSuspend(g_demoTaskHiId);
    if (ret != LOS_OK) {
        printf("Suspend high priority task failed.\n");
        //中文：挂起高优先级任务失败
        ret = InspectStatusSetById(LOS_INSPECT_TASK, LOS_INSPECT_STU_ERROR);
        if (ret != LOS_OK) {
            printf("Set inspect status failed.\n");
            //中文：设置检查状态失败
        }
        return LOS_NOK;
    }

    printf("High priority task LOS_TaskResume successfully.\n");
    //中文：高优先级任务恢复成功
    ret = InspectStatusSetById(LOS_INSPECT_TASK, LOS_INSPECT_STU_SUCCESS);
    if (ret != LOS_OK) {
        printf("Set inspect status failed.\n");
        //中文：设置检查状态失败
    }

    /* delete self */
    //中文：删除自己
    if (LOS_TaskDelete(g_demoTaskHiId) != LOS_OK) {
        printf("Delete high priority task failed.\n");
        //中文：删除高优先级任务失败
        return LOS_NOK;
    }

    return LOS_OK;
}

STATIC UINT32 LoTaskEntry(VOID)
{
    UINT32 ret;

    printf("Enter low priority task handler.\n");
    //中文：进入低优先级任务处理程序

    /* task delay 10 ticks, task will be suspend */
    //中文：延迟10个tick，任务将被挂起
    ret = LOS_TaskDelay(DELAY_INTERVAL2);
    if (ret != LOS_OK) {
        printf("Delay low priority task failed.\n");
        //中文：延迟低优先级任务失败
        return LOS_NOK;
    }

    printf("High priority task LOS_TaskSuspend successfully.\n");
    //中文：高优先级任务挂起成功

    /* resumed task g_demoTaskHiId */
    //中文：恢复任务g_demoTaskHiId
    ret = LOS_TaskResume(g_demoTaskHiId);
    if (ret != LOS_OK) {
        printf("Resume high priority task failed.\n");
        //中文：恢复高优先级任务失败
        ret = InspectStatusSetById(LOS_INSPECT_TASK, LOS_INSPECT_STU_ERROR);
        if (LOS_OK != ret) {
            printf("Set inspect status failed.\n");
            //中文：设置检查状态失败
        }
        return LOS_NOK;
    }

    /* delete self */
    //中文：删除自己
    if (LOS_TaskDelete(g_demoTaskLoId) != LOS_OK) {
        printf("Delete low priority task failed.\n");
        //中文：删除低优先级任务失败
        return LOS_NOK;
    }

    return LOS_OK;
}

UINT32 TaskDemo(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S taskInitParam;
    printf("\nKernel task demo start to run.\n");
    //中文：内核任务演示开始运行
    printf("\nKernel task demo start to run.\n");
    //中文：内核任务演示开始运行
    /* lock task schedule */
    //中文：锁定任务调度
    LOS_TaskLock();

    /* create task */
    //中文：创建任务
    ret = memset_s(&taskInitParam, sizeof(TSK_INIT_PARAM_S), 0, sizeof(TSK_INIT_PARAM_S));
    if (ret != EOK) {
        return ret;
    }
    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)HiTaskEntry;
    taskInitParam.usTaskPrio = HI_TASK_PRIOR;
    taskInitParam.pcName = "TaskDemoHiTask";
    taskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
#ifdef LOSCFG_KERNEL_SMP
    taskInitParam.usCpuAffiMask = CPUID_TO_AFFI_MASK(ArchCurrCpuid());
#endif
    ret = LOS_TaskCreate(&g_demoTaskHiId, &taskInitParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();
        printf("Create high priority task failed.\n");
        //中文：创建高优先级任务失败
        return LOS_NOK;
    }
    printf("Create high priority task successfully.\n");
    //中文：创建高优先级任务成功

    taskInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)LoTaskEntry;
    taskInitParam.usTaskPrio = LO_TASK_PRIOR;
    taskInitParam.pcName = "TaskDemoLoTask";
    taskInitParam.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
    ret = LOS_TaskCreate(&g_demoTaskLoId, &taskInitParam);
    if (ret != LOS_OK) {
        /* delete high prio task */
        if (LOS_OK != LOS_TaskDelete(g_demoTaskHiId)) {
            printf("Delete high priority task failed.\n");
            //中文：删除高优先级任务失败
        }
        LOS_TaskUnlock();
        printf("Create low priority task failed.\n");
        //中文：创建低优先级任务失败
        return LOS_NOK;
    }
    printf("Create low priority task successfully.\n");
    //中文：创建低优先级任务成功

    /* unlock task schedule */
    //中文：解锁任务调度
    LOS_TaskUnlock();
    LOS_TaskDelay(DELAY_INTERVAL3);

    return ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
