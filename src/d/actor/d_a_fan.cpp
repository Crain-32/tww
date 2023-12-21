//
// Generated by dtk
// Translation Unit: d_a_fan.cpp
//

#include "d/actor/d_a_fan.h"
#include "f_op/f_op_kankyo_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_level_se.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/JUtility/JUTAssert.h"

const char* daFan_c::m_arcname[3] = { "Hsen1", "Hsen1", "Hsen3", };
const char daFan_c::m_arcname2[8] = "Yaflw00";
const s16 daFan_c::m_bdlidx[3] = { 0x05, 0x05, 0x04, };
const s16 daFan_c::m_dzbidx[3] = { 0x0C, 0x0C, 0x07, };
const f32 daFan_c::m_wind_length[3] = { 1600.0f, 1600.0f, 1220.0f, };
const f32 daFan_c::m_wind_r[3] = { 120.0f, 120.0f, 780.0f, };
const Vec daFan_c::m_wind_model_scale[3] = { { 1.0f, 1.6f, 1.0f, }, { 1.0f, 1.6f, 1.0f, }, { 3.0f, 2.9f, 3.0f, }, };
const s16 daFan_c::m_fan_speed[3] = { 0x2000, 0x2000, 0x1D4C, };
const u32 daFan_c::m_heapsize[3] = { 0x23C0, 0x23C0, 0x8000, };
const Vec daFan_c::m_cull_min[3] = { { -200.0f, -200.0f, -50.0f, }, { -200.0f, -200.0f, -50.0f, }, { -600.0f, -600.0f, -50.0f, }, };
const Vec daFan_c::m_cull_max[3] = { { 200.0f, 200.0f, 1600.0f, }, { 200.0f, 200.0f, 1600.0f, }, { 600.0f, 600.0f, 3500.0f, }, };

static dCcD_SrcCps l_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_LEAF_WIND,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0x0F,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0x02,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0x04,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {
        /* P0 */ 0.0f, 0.0f, 0.0f,
        /* P1 */ 0.0f, 0.0f, 0.0f,
        /* Hieght */ 100.0f,
    },
};

/* 00000078-000000F0       .text Delete__7daFan_cFv */
BOOL daFan_c::Delete() {
    dComIfG_resDelete(&mPhs, m_arcname[mType]);
    dComIfG_resDelete(&mWindPhs, m_arcname2);
    if (mWindSePId != -1) {
        dLevelSe_c* se = (dLevelSe_c*)fopKyM_SearchByID(mWindSePId);
        if (se != NULL)
            fopKyM_Delete(se);
    }
    return TRUE;
}

/* 000000F0-0000040C       .text CreateHeap__7daFan_cFv */
int daFan_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname[mType], m_bdlidx[mType]);
    JUT_ASSERT(0x15e, modelData != 0);

    mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mModel == NULL)
        return FALSE;
    mModel->setUserArea((u32)this);

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname2, 0x08);
    JUT_ASSERT(0x17f, modelData != 0);
    mWindModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
    if (mWindModel == NULL)
        return FALSE;

    J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arcname2, 0x0B);
    JUT_ASSERT(400, pbtk != 0);
    if (!mWindBtkAnm0.init(modelData, pbtk, TRUE, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0,-1, false, 0))
        return FALSE;

    pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arcname2, 0x0C);
    JUT_ASSERT(0x19c, pbtk != 0);
    if (!mWindBtkAnm1.init(modelData, pbtk, TRUE, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, 0,-1, false, 0))
        return FALSE;

    J3DAnmTransform* pbck = (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname2, 0x05);
    JUT_ASSERT(0x1a9, pbck != 0);
    if (!mWindBckAnm.init(modelData, pbck, TRUE, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0,-1, false))
        return FALSE;

    return TRUE;
}

static int nodeCallBack(J3DNode*, int);

/* 0000040C-00000640       .text Create__7daFan_cFv */
int daFan_c::Create() {
    /* Nonmatching */
    f32 wind_len = m_wind_length[mType];
    fopAcM_SetMtx(this, mModel->getBaseTRMtx());
    Vec cullMin = m_cull_min[mType];
    Vec cullMax = m_cull_max[mType];
    fopAcM_setCullSizeBox(this, cullMin.x, cullMin.y, cullMin.z, cullMax.x, cullMax.y, cullMax.z);
    mStts.Init(0xFF, 0xFF, this);
    mCps.Set(l_cps_src);
    mCps.SetStts(&mStts);
    mWindScale = m_wind_model_scale[mType];
    set_cps(wind_len);
    mCps.cM3dGCps::Set(mCpsS);
    mCps.CalcAtVec();
    set_mtx();
    mSwitchNo = daFan_prm::getSwitchNo(this);

    JUTNameTab* jointName = mModel->getModelData()->getJointName();
    for (u16 i = 0; i < mModel->getModelData()->getJointNum(); i++) {
        if (strcmp(jointName->getName(i), "puro") == 0) {
            mModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            break;
        }
    }

    mModel->calc();
    mWindSePId = fopKyM_create(PROC_LEVEL_SE, JA_SE_OBJ_WIND_TAG, &mEyePos);
    return TRUE;
}

/* 00000640-000006F4       .text nodeCallBack__FP7J3DNodei */
static int nodeCallBack(J3DNode* node, int timing) {
    if (timing == 0) {
        J3DJoint* joint = (J3DJoint*)node;
        u32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daFan_c* i_this = (daFan_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->mFanAngle += i_this->mFanSpeed;
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::ZrotM(i_this->mFanAngle);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
            mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
        }
    }
    return TRUE;
}

/* 000006F4-00000900       .text _create__7daFan_cFv */
s32 daFan_c::_create() {
    const char* arcname = m_arcname2;

    fopAcM_SetupActor(this, daFan_c);

    mType = daFan_prm::getType(this);
    s32 rt1 = dComIfG_resLoad(&mPhs, m_arcname[mType]);
    if (rt1 != cPhs_COMPLEATE_e)
        return rt1;

    s32 rt2 = dComIfG_resLoad(&mWindPhs, arcname);
    if (rt2 != cPhs_COMPLEATE_e)
        return rt2;

    if (rt1 == cPhs_COMPLEATE_e && rt2 == cPhs_COMPLEATE_e) {
        rt1 = MoveBGCreate(m_arcname[mType], m_dzbidx[mType], dBgS_MoveBGProc_TypicalRotY, m_heapsize[mType]);
        if (rt1 == cPhs_ERROR_e)
            return cPhs_ERROR_e;
    }

    return rt2;
}

/* 00000C28-00000D28       .text set_mtx__7daFan_cFv */
void daFan_c::set_mtx() {
    mModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), mBgMtx);

    mWindModel->setBaseScale(mWindScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle.x + 0x4000, current.angle.y, current.angle.z);
    mWindModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000D28-00000D64       .text set_wind_length__7daFan_cFf */
void daFan_c::set_wind_length(f32 h) {
    /* Nonmatching */
    set_cps(m_wind_length[mType] * h);
}

/* 00000D64-00000E54       .text set_cps__7daFan_cFf */
void daFan_c::set_cps(f32 h) {
    mCpsS.mRadius = m_wind_r[mType];
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle.x + 0x4000, current.angle.y, current.angle.z);
    mDoMtx_stack_c::push();
    mDoMtx_stack_c::transM(0.0f, mCpsS.mRadius, 0.0f);
    mDoMtx_stack_c::multVec(&cXyz::Zero, &mCpsS.mStart);
    mDoMtx_stack_c::pop();
    mDoMtx_stack_c::transM(0.0f, mCpsS.mRadius + h, 0.0f);
    mDoMtx_stack_c::multVec(&cXyz::Zero, &mCpsS.mEnd);
}

/* 00000E54-00001088       .text Execute__7daFan_cFPPA3_A4_f */
int daFan_c::Execute(Mtx** mtxP) {
    /* Nonmatching */
    s32 speed = m_fan_speed[mType];
    f32 len = mFanSpeed / (f32)speed;

    if ((mType == 0 && !fopAcM_isSwitch(this, mSwitchNo)) || (mType == 1 && fopAcM_isSwitch(this, mSwitchNo))) {
        cLib_chaseS(&mFanSpeed, speed, 100);
        mWindBtkAnm1.setPlaySpeed(1.0f);
    } else if (mType == 2) {
        cLib_chaseS(&mFanSpeed, speed, 100);
        mWindBtkAnm1.setPlaySpeed(1.0f);
    } else {
        cLib_chaseS(&mFanSpeed, 0, 100);
        mWindBtkAnm1.setPlaySpeed(-1.0f);
    }

    if (mWindSePId != -1) {
        dLevelSe_c* se = (dLevelSe_c*)fopKyM_SearchByID(mWindSePId);
        if (se != NULL)
            se->setReverb(len * 100.0f, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }

    if (len > 0.1f) {
        set_wind_length(len * len);
        mCps.cM3dGCps::Set(mCpsS);
        dComIfG_Ccsp()->Set(&mCps);
        mWindBtkAnm0.play();
        mWindBtkAnm1.play();
        mWindBckAnm.play();
    }

    set_mtx();
    *mtxP = &mBgMtx;
    return TRUE;
}

/* 00001088-0000118C       .text Draw__7daFan_cFv */
BOOL daFan_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mModel, &mTevStr);
    g_env_light.setLightTevColorType(mWindModel, &mTevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel);
    dComIfGd_setList();
    mWindBckAnm.entry(mWindModel->getModelData());
    mWindBtkAnm0.entry(mWindModel->getModelData());
    mWindBtkAnm1.entry(mWindModel->getModelData());
    mDoExt_modelUpdateDL(mWindModel);
    return TRUE;
}

/* 0000118C-000011AC       .text daFan_Create__FPv */
static BOOL daFan_Create(void* i_this) {
    return ((daFan_c*)i_this)->_create();
}

/* 000011AC-000011CC       .text daFan_Delete__FPv */
static BOOL daFan_Delete(void* i_this) {
    return ((daFan_c*)i_this)->MoveBGDelete();
}

/* 000011CC-000011F8       .text daFan_Draw__FPv */
static BOOL daFan_Draw(void* i_this) {
    return ((daFan_c*)i_this)->Draw();
}

/* 000011F8-00001218       .text daFan_Execute__FPv */
static BOOL daFan_Execute(void* i_this) {
    return ((daFan_c*)i_this)->MoveBGExecute();
}

/* 00001218-00001220       .text daFan_IsDelete__FPv */
static BOOL daFan_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daFanMethodTable = {
    (process_method_func)daFan_Create,
    (process_method_func)daFan_Delete,
    (process_method_func)daFan_Execute,
    (process_method_func)daFan_IsDelete,
    (process_method_func)daFan_Draw,
};

actor_process_profile_definition g_profile_Fan = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_FAN,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daFan_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0011B,
    /* Actor SubMtd */ &daFanMethodTable,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_UNK4000_e | fopAcStts_CULL_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
