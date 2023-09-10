//
// Generated by dtk
// Translation Unit: f_pc_manager.cpp
//

#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_creator.h"
#include "f_pc/f_pc_draw.h"
#include "f_pc/f_pc_deletor.h"
#include "f_pc/f_pc_fstcreate_req.h"
#include "f_pc/f_pc_layer_iter.h"
#include "f_pc/f_pc_line.h"
#include "f_pc/f_pc_pause.h"
#include "f_pc/f_pc_priority.h"
#include "dolphin/dvd/DVD.h"
#include "m_Do/m_Do_Reset.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_API_graphic.h"
#include "JSystem/JUtility/JUTAssert.h"

/* 8003E318-8003E338       .text fpcM_Draw__FPv */
void fpcM_Draw(void* i_proc) {
    fpcDw_Execute((base_process_class*)i_proc);
}

/* 8003E338-8003E370       .text fpcM_DrawIterater__FPFPvPv_i */
s32 fpcM_DrawIterater(fpcM_DrawIteraterFunc i_drawIterFunc) {
    return fpcLyIt_OnlyHere(fpcLy_RootLayer(), (fpcLyIt_OnlyHereFunc)i_drawIterFunc, NULL);
}

/* 8003E370-8003E390       .text fpcM_Execute__FPv */
s32 fpcM_Execute(void* i_proc) {
    return fpcEx_Execute((base_process_class*)i_proc);
}

/* 8003E390-8003E3B0       .text fpcM_Delete__FPv */
s32 fpcM_Delete(void* i_proc) {
    return fpcDt_Delete((base_process_class*)i_proc);
}

/* 8003E3B0-8003E3D0       .text fpcM_IsCreating__FUi */
BOOL fpcM_IsCreating(unsigned int pID) {
    return fpcCt_IsCreatingByID(pID);
}

/* 8003E3D0-8003E9F0       .text messageSet__FUl */
void messageSet(unsigned long) {
    /* Nonmatching */
}

/* 8003E9F0-8003EBD4       .text drawDvdCondition__Fl */
void drawDvdCondition(long status) {
    /* Nonmatching */
}

/* 8003EBD4-8003EC84       .text checkDvdCondition__Fv */
static int checkDvdCondition() {
    static int l_dvdError = 0;
    
    int status = DVDGetDriveStatus();
    if (status != 0 && status != 1)
        l_dvdError = 1;

    if (l_dvdError != 0) {
        if (status == 0) {
            l_dvdError = 0;
        } else if (mDoRst::isReset()) {
            mDoRst::offReset();
            mDoRst_reset(1, 0x80000000, 0);
        } else {
            drawDvdCondition(status);
        }
    }

    return l_dvdError;
}

/* 8003EC84-8003ED90       .text fpcM_Management__FPFv_vPFv_v */
void fpcM_Management(fpcM_ManagementFunc callBack1, fpcM_ManagementFunc callBack2) {
    MtxInit();

    if (checkDvdCondition())
        return;

    cAPIGph_Painter();
    fpcDt_Handler();
    if (!fpcPi_Handler())
        JUT_ASSERT("f_pc_manager.cpp", 548, 0);

    if (!fpcCt_Handler())
        JUT_ASSERT("f_pc_manager.cpp", 552, 0);

    if (callBack1 != NULL)
        callBack1();

    fpcEx_Handler((fpcLnIt_QueueFunc)fpcM_Execute);
    fpcDw_Handler((fpcDw_HandlerFuncFunc)fpcM_DrawIterater, (fpcDw_HandlerFunc)fpcM_Draw);

    if (callBack2 != NULL)
        callBack2();
}

/* 8003ED90-8003EDCC       .text fpcM_Init__Fv */
void fpcM_Init() {
    static layer_class rootlayer;
    static node_list_class queue[10];

    fpcLy_Create(&rootlayer, NULL, queue, 10);
    fpcLn_Create();
}

/* 8003EDCC-8003EE20       .text fpcM_FastCreate__FsPFPv_iPvPv */
base_process_class* fpcM_FastCreate(s16 i_procTypeID, FastCreateReqFunc i_createReqFunc,
                                    void* i_createData, void* i_data) {
    return fpcFCtRq_Request(fpcLy_CurrentLayer(), i_procTypeID, (fstCreateFunc)i_createReqFunc,
                            i_createData, i_data);
}


/* 8003EE20-8003EE44       .text fpcM_IsPause__FPvUc */
s32 fpcM_IsPause(void* i_proc, u8 i_flag) {
    return fpcPause_IsEnable((base_process_class*)i_proc, i_flag & 0xFF);
}

/* 8003EE44-8003EE68       .text fpcM_PauseEnable__FPvUc */
void fpcM_PauseEnable(void* i_proc, u8 i_flag) {
    fpcPause_Enable((process_node_class*)i_proc, i_flag & 0xFF);
}

/* 8003EE68-8003EE8C       .text fpcM_PauseDisable__FPvUc */
void fpcM_PauseDisable(void* i_proc, u8 i_flag) {
    fpcPause_Disable((process_node_class*)i_proc, i_flag & 0xFF);
}

/* 8003EE8C-8003EF00       .text fpcM_JudgeInLayer__FUiPFPvPv_PvPv */
void* fpcM_JudgeInLayer(unsigned int i_layerID, fpcCtIt_JudgeFunc i_judgeFunc, void* i_data) {
    layer_class* layer = fpcLy_Layer(i_layerID);
    if (layer != NULL) {
        void* ret = fpcCtIt_JudgeInLayer(i_layerID, i_judgeFunc, i_data);
        if (ret == NULL) {
            ret = fpcLyIt_Judge(layer, i_judgeFunc, i_data);
        }
        return ret;
    } else {
        return NULL;
    }
}
