//
// Generated by dtk
// Translation Unit: d_a_itembase.cpp
//

#include "d/actor/d_a_itembase.h"
#include "d/d_item_data.h"
#include "d/d_resorce.h"
#include "d/d_drawlist.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_item_data.h"
#include "d/d_com_inf_game.h"
#include "dolphin/types.h"

/* 800F8A14-800F8A3C       .text DeleteBase__12daItemBase_cFPCc */
s32 daItemBase_c::DeleteBase(const char* resName) {
    dComIfG_resDelete(&mPhs, resName);
    return 1;
}

/* 800F8A3C-800F8A44       .text clothCreate__12daItemBase_cFv */
s32 daItemBase_c::clothCreate() {
    return 1;
}

/* 800F8A44-800F9074       .text CreateItemHeap__12daItemBase_cFPCcsssssss */
s32 daItemBase_c::CreateItemHeap(const char* resName, short resIdx, short btkAnm1, short btkAnm2, short brkAnm1, short brkAnm2, short bckAnm, short) {
    /* Nonmatching */
    JUT_ASSERT(78, 0 <= m_itemNo && m_itemNo <= 255);
    
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(resName, resIdx);
    JUT_ASSERT(85, modelData != 0);
    
    mModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (!mModel) {
        return 0;
    }
    
    switch (m_itemNo) {
    case ARROW_30:
        mModelArrow[0] = mDoExt_J3DModel__create(modelData, 8, 0x11000002);
        if (!mModelArrow[0]) {
            return 0;
        }
    case ARROW_20:
        mModelArrow[1] = mDoExt_J3DModel__create(modelData, 8, 0x11000002);
        if (!mModelArrow[1]) {
            return 0;
        }
        break;
    default:
        mModelArrow[1] = NULL;
        mModelArrow[0] = NULL;
    }
    
    mBtkAnm1 = NULL;
    if (btkAnm1 != -1) {
        J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(resName, btkAnm1);
        JUT_ASSERT(140, pbtk != 0);
        mBtkAnm1 = new mDoExt_btkAnm();
        if (!mBtkAnm1 || !mBtkAnm1->init(modelData, pbtk, true, 2, 1.0, 0, -1, false, false)) {
            return 0;
        }
    }
    
    mBtkAnm2 = NULL;
    if (btkAnm2 != -1) {
        J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(resName, btkAnm2);
        JUT_ASSERT(172, pbtk != 0);
        mBtkAnm2 = new mDoExt_btkAnm();
        if (!mBtkAnm2 || !mBtkAnm2->init(modelData, pbtk, true, 2, 1.0, 0, -1, false, false)) {
            return 0;
        }
    }
    
    mBrkAnm1 = NULL;
    if (brkAnm1 != -1) {
        J3DAnmTevRegKey* pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(resName, brkAnm1);
        JUT_ASSERT(172, pbrk != 0);
        int shouldAnimate = dItem_data::item_resource[m_itemNo].mTevRegAnimFrameIndex == 0xFF;
        mBrkAnm1 = new mDoExt_brkAnm();
        if (!mBrkAnm1 || !mBrkAnm1->init(modelData, pbrk, shouldAnimate, 2, 1.0, 0, -1, false, false)) {
            return 0;
        }
    }
    
    mBrkAnm2 = NULL;
    if (brkAnm2 != -1) {
        J3DAnmTevRegKey* pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(resName, brkAnm2);
        JUT_ASSERT(197, pbrk != 0);
        mBrkAnm2 = new mDoExt_brkAnm();
        if (!mBrkAnm2 || !mBrkAnm2->init(modelData, pbrk, true, 2, 1.0, 0, -1, false, false)) {
            return 0;
        }
    }
    
    mBckAnm = NULL;
    if (bckAnm != -1) {
        J3DAnmTransform* pbck = (J3DAnmTransform*)dComIfG_getObjectRes(resName, bckAnm);
        JUT_ASSERT(212, pbck != 0);
        mBckAnm = new mDoExt_bckAnm();
        if (!mBckAnm || !mBckAnm->init(modelData, pbck, true, 2, 1.0, 0, -1, false)) {
            return 0;
        }
    }
    
    if (!clothCreate()) {
        return 0;
    }
    
    return 1;
}

/* 800F9074-800F9130       .text DrawBase__12daItemBase_cFv */
s32 daItemBase_c::DrawBase() {
    setTevStr();
    animEntry();
    setListStart();
    settingBeforeDraw();
    
    mDoExt_modelUpdateDL(mModel);
    
    if (mModelArrow[0]) {
        mDoExt_modelUpdateDL(mModelArrow[0]);
    }
    if (mModelArrow[1]) {
        mDoExt_modelUpdateDL(mModelArrow[1]);
    }
    
    setListEnd();
    setShadow();
    
    return 1;
}

/* 800F9130-800F9184       .text setListStart__12daItemBase_cFv */
void daItemBase_c::setListStart() {
    /* Nonmatching */
}

/* 800F9184-800F91A8       .text setListEnd__12daItemBase_cFv */
void daItemBase_c::setListEnd() {
    /* Nonmatching */
}

/* 800F91A8-800F9244       .text settingBeforeDraw__12daItemBase_cFv */
void daItemBase_c::settingBeforeDraw() {
    /* Nonmatching */
}

/* 800F9244-800F92DC       .text setTevStr__12daItemBase_cFv */
void daItemBase_c::setTevStr() {
    /* Nonmatching */
}

/* 800F92DC-800F93A8       .text setShadow__12daItemBase_cFv */
void daItemBase_c::setShadow() {
    /* Nonmatching */
}

/* 800F93A8-800F94C0       .text animEntry__12daItemBase_cFv */
void daItemBase_c::animEntry() {
    /* Nonmatching */
    if (mBrkAnm1) {
        int constantFrame = dItem_data::item_resource[m_itemNo].mTevRegAnimFrameIndex;
        if (constantFrame != -1) {
            mBrkAnm1->entry(mModel->getModelData(), constantFrame);
        } else {
            mBrkAnm1->entry(mModel->getModelData());
        }
    }
    if (mBtkAnm1) {
        mBtkAnm1->entry(mModel->getModelData());
    }
    if (mBrkAnm2) {
        mBrkAnm2->entry(mModel->getModelData());
    }
    if (mBtkAnm2) {
        mBtkAnm2->entry(mModel->getModelData());
    }
    if (mBckAnm) {
        mBckAnm->entry(mModel->getModelData());
    }
}

/* 800F94C0-800F95B8       .text animPlay__12daItemBase_cFfffff */
void daItemBase_c::animPlay(float, float, float, float, float) {
    /* Nonmatching */
}
