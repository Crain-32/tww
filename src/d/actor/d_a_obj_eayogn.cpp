//
// Generated by dtk
// Translation Unit: d_a_obj_eayogn.cpp
//

#include "f_op/f_op_actor_mng.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

class daObjEayogn_c : public fopAc_ac_c {
public:
    s32 _create();
    bool _execute();
    bool _draw();
    bool _delete();
    bool create_heap();
    static bool solidHeapCB(fopAc_ac_c *i_this);
    void init_mtx();
    BOOL check_ev_bit() const;
    static const char M_arcname[7];

public:
    /* 0x290 */ J3DModel * mpModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x2A0 */ dBgW * mpBgW;
};

const char daObjEayogn_c::M_arcname[7] = "Eayogn";

/* 00000078-00000098       .text solidHeapCB__13daObjEayogn_cFP10fopAc_ac_c */
bool daObjEayogn_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjEayogn_c*)i_this)->create_heap();
}

/* 00000098-00000198       .text create_heap__13daObjEayogn_cFv */
bool daObjEayogn_c::create_heap() {
    bool ret = false;

    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, 0x04));
    JUT_ASSERT(0x5c, mdl_data != 0);

    if (mdl_data != NULL) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x00, 0x11020203);
        if (mpModel != NULL) {
            mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, 0x07), cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx());
            if (mpBgW != NULL)
                ret = true;
        }
    }

    return ret;
}

/* 00000198-0000029C       .text _create__13daObjEayogn_cFv */
s32 daObjEayogn_c::_create() {
    s32 ret = cPhs_ERROR_e;

    fopAcM_SetupActor(this, daObjEayogn_c);

    if (check_ev_bit()) {
        ret = dComIfG_resLoad(&mPhs, M_arcname);

        if (ret == cPhs_COMPLEATE_e) {
            ret = cPhs_ERROR_e;
            if (fopAcM_entrySolidHeap(this, (heapCallbackFunc)solidHeapCB, 0x0)) {
                fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
                init_mtx();
                dComIfG_Bgsp()->Regist(mpBgW, this);
                mpBgW->Move();
                fopAcM_setCullSizeBox(this, -550.0f, -50.0f, -600.0f, 550.0f, 50.0f, 600.0f);
                ret = cPhs_COMPLEATE_e;
            }
        }
    }

    return ret;
}

/* 0000029C-00000330       .text _delete__13daObjEayogn_cFv */
bool daObjEayogn_c::_delete() {
    if (heap != NULL && mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
            mpBgW = NULL;
        }
    }

    dComIfG_resDelete(&mPhs, M_arcname);

    return true;
}

/* 00000330-00000360       .text check_ev_bit__13daObjEayogn_cCFv */
BOOL daObjEayogn_c::check_ev_bit() const {
    return dComIfGs_isSymbol(1);
}

/* 00000360-000003E8       .text init_mtx__13daObjEayogn_cFv */
void daObjEayogn_c::init_mtx() {
    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(getPosition());
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000003E8-000003F0       .text _execute__13daObjEayogn_cFv */
bool daObjEayogn_c::_execute() {
    return true;
}

/* 000003F0-00000490       .text _draw__13daObjEayogn_cFv */
bool daObjEayogn_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, getPositionP(), &mTevStr);
    g_env_light.setLightTevColorType(mpModel, &mTevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return true;
}

namespace {
    /* 00000490-000004B0       .text Mthd_Create__28@unnamed@d_a_obj_eayogn_cpp@FPv */
    s32 Mthd_Create(void* i_this) {
        return ((daObjEayogn_c*)i_this)->_create();
    }

    /* 000004B0-000004D4       .text Mthd_Delete__28@unnamed@d_a_obj_eayogn_cpp@FPv */
    BOOL Mthd_Delete(void* i_this) {
        return ((daObjEayogn_c*)i_this)->_delete();
    }

    /* 000004D4-000004F8       .text Mthd_Execute__28@unnamed@d_a_obj_eayogn_cpp@FPv */
    BOOL Mthd_Execute(void* i_this) {
        return ((daObjEayogn_c*)i_this)->_execute();
    }

    /* 000004F8-0000051C       .text Mthd_Draw__28@unnamed@d_a_obj_eayogn_cpp@FPv */
    BOOL Mthd_Draw(void* i_this) {
        return ((daObjEayogn_c*)i_this)->_draw();
    }

    /* 0000051C-00000524       .text Mthd_IsDelete__28@unnamed@d_a_obj_eayogn_cpp@FPv */
    BOOL Mthd_IsDelete(void* i_this) {
        return TRUE;
    }

    static actor_method_class Eayogn_Mthd_Table = {
        (process_method_func)Mthd_Create,
        (process_method_func)Mthd_Delete,
        (process_method_func)Mthd_Execute,
        (process_method_func)Mthd_IsDelete,
        (process_method_func)Mthd_Draw,
    };
}

actor_process_profile_definition g_profile_Obj_Eayogn = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 3,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Eayogn,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daObjEayogn_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x004C,
    /* Actor SubMtd */ &Eayogn_Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
