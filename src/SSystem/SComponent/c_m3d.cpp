//
// Generated by dtk
// Translation Unit: c_m3d.cpp
//

#include "SSystem/SComponent/c_m3d.h"
#include "SSystem/SComponent/c_m3d_g_aab.h"
#include "SSystem/SComponent/c_m3d_g_cir.h"
#include "SSystem/SComponent/c_m3d_g_cps.h"
#include "SSystem/SComponent/c_m3d_g_cyl.h"
#include "SSystem/SComponent/c_m3d_g_lin.h"
#include "SSystem/SComponent/c_m3d_g_pla.h"
#include "SSystem/SComponent/c_m3d_g_sph.h"
#include "SSystem/SComponent/c_m3d_g_tri.h"
#include "SSystem/SComponent/c_math.h"
#include "float.h"

// TODO: these should be in .sdata2
f32 G_CM3D_F_ABS_MIN = 3.814697e-06;
u32 BPCP_OUTCODE0 = 0x00000001;
u32 BPCP_OUTCODE1 = 0x00000002;
u32 BPCP_OUTCODE4 = 0x00000010;
u32 BPCP_OUTCODE5 = 0x00000020;
u32 BPCP_OUTCODE2 = 0x00000004;
u32 BPCP_OUTCODE3 = 0x00000008;
u32 BEVEL2D_OUTCODE0 = 0x00000001;
u32 BEVEL2D_OUTCODE1 = 0x00000002;
u32 BEVEL2D_OUTCODE2 = 0x00000004;
u32 BEVEL2D_OUTCODE3 = 0x00000008;
u32 BEVEL2D_OUTCODE4 = 0x00000010;
u32 BEVEL2D_OUTCODE5 = 0x00000020;
u32 BEVEL2D_OUTCODE6 = 0x00000040;
u32 BEVEL2D_OUTCODE7 = 0x00000080;
u32 BEVEL2D_OUTCODE8 = 0x00000100;
u32 BEVEL2D_OUTCODE9 = 0x00000200;
u32 BEVEL2D_OUTCODE10 = 0x00000400;
u32 BEVEL2D_OUTCODE11 = 0x00000800;
u32 BEVEL3D_OUTCODE0 = 0x00000001;
u32 BEVEL3D_OUTCODE1 = 0x00000002;
u32 BEVEL3D_OUTCODE2 = 0x00000004;
u32 BEVEL3D_OUTCODE3 = 0x00000008;
u32 BEVEL3D_OUTCODE4 = 0x00000010;
u32 BEVEL3D_OUTCODE5 = 0x00000020;
u32 BEVEL3D_OUTCODE6 = 0x00000040;
u32 BEVEL3D_OUTCODE7 = 0x00000080;

/* 8024A400-8024A450       .text cM3d_InDivPos1__FPC3VecPC3VecfP3Vec */
void cM3d_InDivPos1(const Vec* v0, const Vec* v1, f32 scale, Vec* pDst) {
    Vec tmp;
    VECScale(v1, &tmp, scale);
    VECAdd(&tmp, v0, pDst);
}

/* 8024A450-8024A4B4       .text cM3d_InDivPos2__FPC3VecPC3VecfP3Vec */
void cM3d_InDivPos2(const Vec* v0, const Vec* v1, f32 scale, Vec* pDst) {
    Vec tmp;
    VECSubtract(v1, v0, &tmp);
    cM3d_InDivPos1(v0, &tmp, scale, pDst);
}

inline f32 cM3d_Len2dSq(f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 x = x0 - x1;
    f32 y = y0 - y1;
    return x*x + y*y;
}

/* 8024A4B4-8024A56C       .text cM3d_Len2dSqPntAndSegLine__FffffffPfPfPf */
bool cM3d_Len2dSqPntAndSegLine(f32 xp, f32 yp, f32 x0, f32 y0, f32 x1, f32 y1, f32* outx, f32* outy, f32* seg) {
    /* Nonmatching */
    bool ret = false;
    f32 xd = x1 - x0;
    f32 yd = y1 - y0;
    f32 dot = (xd*xd + yd*yd);
    if (cM3d_IsZero(dot)) {
        *seg = 0.0f;
        return ret;
    }

    f32 t = (x1 * (xp - x0) + y1 * (yp - y0)) / dot;
    if (t >= 0.0f && t <= 1.0f) {
        ret = true;
    }

    *outx = x0 + xd * t;
    *outy = y0 + yd * t;
    *seg = cM3d_Len2dSq(*outx, *outy, xp, yp);
    return ret;
}

/* 8024A56C-8024A670       .text cM3d_Len3dSqPntAndSegLine__FPC8cM3dGLinPC3VecP3VecPf */
bool cM3d_Len3dSqPntAndSegLine(const cM3dGLin*, const Vec*, Vec*, f32*) {
    /* Nonmatching */
}

/* 8024A670-8024A6F0       .text cM3d_SignedLenPlaAndPos__FPC8cM3dGPlaPC3Vec */
f32 cM3d_SignedLenPlaAndPos(const cM3dGPla* plane, const Vec* pos) {
    f32 len = VECMag(plane->GetNP());
    if (cM3d_IsZero(len))
        return 0.0f;
    else
        return plane->getPlaneFunc(pos) / len;
}

/* 8024A6F0-8024A7BC       .text cM3d_CalcPla__FPC3VecPC3VecPC3VecP3VecPf */
void cM3d_CalcPla(const Vec* p0, const Vec* p1, const Vec* p2, Vec* pDst, f32* pT) {
    cM3d_VectorProduct(p0, p1, p2, pDst);
    f32 t = VECMag(pDst);
    if (fabsf(t) >= 0.02f) {
        VECScale(pDst, pDst, 1.0f / t);
        *pT = -VECDotProduct(pDst, p0);
    } else {
        pDst->y = 0.0f;
        *pT = 0.0f;
        pDst->z = 0.0f;
        pDst->x = 0.0f;
    }
}

inline bool cM3d_CrossNumSection(f32 lMinX, f32 lMaxX, f32 rMinX, f32 rMaxX) {
    if (lMinX > rMaxX) {
        return false;
    } else if (lMaxX < rMinX) {
        return false;
    } else if (rMinX > lMaxX) {
        return false;
    } else if (rMaxX < lMinX) {
        return false;
    } else {
        return true;
    }
}

/* 8024A7BC-8024A8E0       .text cM3d_Cross_AabAab__FPC8cM3dGAabPC8cM3dGAab */
bool cM3d_Cross_AabAab(const cM3dGAab* a, const cM3dGAab* b) {
    if (cM3d_CrossNumSection(a->GetMinP()->x, a->GetMaxP()->x, b->GetMinP()->x, b->GetMaxP()->x) &&
        cM3d_CrossNumSection(a->GetMinP()->y, a->GetMaxP()->y, b->GetMinP()->y, b->GetMaxP()->y) &&
        cM3d_CrossNumSection(a->GetMinP()->z, a->GetMaxP()->z, b->GetMinP()->z, b->GetMaxP()->z)) {
        return true;
    } else {
        return false;
    }
}

/* 8024A8E0-8024A988       .text cM3d_Cross_AabCyl__FPC8cM3dGAabPC8cM3dGCyl */
bool cM3d_Cross_AabCyl(const cM3dGAab* aab, const cM3dGCyl* cyl) {
    if (aab->GetMinP()->x > cyl->GetCP()->x + cyl->GetR()) {
        return false;
    } else if (aab->GetMaxP()->x < cyl->GetCP()->x - cyl->GetR()) {
        return false;
    } else if (aab->GetMinP()->z > cyl->GetCP()->z + cyl->GetR()) {
        return false;
    } else if (aab->GetMaxP()->z < cyl->GetCP()->z - cyl->GetR()) {
        return false;
    } else if (aab->GetMinP()->y > cyl->GetCP()->y + cyl->GetH()) {
        return false;
    } else if (aab->GetMaxP()->y < cyl->GetCP()->y) {
        return false;
    } else {
        return true;
    }
}

/* 8024A988-8024AA30       .text cM3d_Cross_AabSph__FPC8cM3dGAabPC8cM3dGSph */
bool cM3d_Cross_AabSph(const cM3dGAab* aab, const cM3dGSph* sph) {
    f32 radius = sph->GetR();
    f32 cx = sph->GetC().x;
    if (aab->GetMinX() > cx + radius) {
        return false;
    }
    else if (aab->GetMaxX() < cx - radius) {
        return false;
    }

    f32 cz = sph->GetC().z;
    if (aab->GetMinZ() > cz + radius) {
        return false;
    } else if (aab->GetMaxZ() < cz - radius) {
        return false;
    }
    
    f32 cy = sph->GetC().y;
    if (aab->GetMinY() > cy + radius) {
        return false;
    } else if (aab->GetMaxY() < cy - radius) {
        return false;
    }
    return true;
}

/* 8024AA30-8024ACA8       .text cM3d_Check_LinLin__FPC8cM3dGLinPC8cM3dGLinPfPf */
int cM3d_Check_LinLin(const cM3dGLin* lin_a, const cM3dGLin* lin_b, f32* dst_a, f32* dst_b) {
    Vec linAVec;
    Vec linBVec;
    lin_a->CalcVec(&linAVec);
    lin_b->CalcVec(&linBVec);
    f32 linALen = VECMag(&linAVec);
    f32 linBLen = VECMag(&linBVec);
    if (cM3d_IsZero(linALen) || cM3d_IsZero(linBLen)) {
        return 1;
    } else {
        f32 invLinALen = 1.0f / linALen;
        f32 invLinBLen = 1.0f / linBLen;
        VECScale(&linAVec, &linAVec, invLinALen);
        VECScale(&linBVec, &linBVec, invLinBLen);
        Vec tmp;
        VECSubtract(lin_a->GetStartP(), lin_b->GetStartP(), &tmp);
        f32 tmpF = -VECDotProduct(&linAVec, &linBVec);
        f32 tmpF2 = VECDotProduct(&tmp, &linAVec);
        VECSquareMag(&tmp);  // result not used
        f32 tmpF3 = fabsf(1.0f - (tmpF * tmpF));
        if (!cM3d_IsZero(tmpF3)) {
            f32 tmpF4 = -VECDotProduct(&tmp, &linBVec);
            f32 tmpF7 = 1.0f / tmpF3;
            f32 outFloatAtmp = ((tmpF * tmpF4) - tmpF2) * tmpF7;
            *dst_a = outFloatAtmp * invLinALen;
            f32 outFloatBtmp = ((tmpF * tmpF2) - tmpF4) * tmpF7;
            *dst_b = outFloatBtmp * invLinBLen;
            return 3;
        } else {
            f32 tmpF5 = -tmpF2;
            f32 tmpF6 = 0.0f;
            if (tmpF5 < 0.0f || (tmpF5 > linALen)) {
                tmpF6 = linBLen;
                tmpF5 = (tmpF6 * tmpF) - tmpF2;
            }
            f32 tmpF7 = VECDotProduct(&tmp, &linBVec);
            if (tmpF5 < 0.0f || tmpF5 > linALen) {
                tmpF5 = 0.0f;
                tmpF6 = tmpF7;
            }
            if (tmpF6 < 0.0f || tmpF6 > linBLen) {
                tmpF5 = linALen;
                tmpF6 = tmpF7 + (-linALen * tmpF);
            }
            *dst_a = tmpF5 * invLinALen;
            *dst_b = tmpF6 * invLinBLen;
            return 2;
        }
    }
}

/* 8024ACA8-8024AE3C       .text cM3d_Cross_LinPla__FPC8cM3dGLinPC8cM3dGPlaP3Vecbb */
bool cM3d_Cross_LinPla(const cM3dGLin* lin, const cM3dGPla* pla, Vec* dst, bool a, bool b) {
    f32 startVal = pla->getPlaneFunc(lin->GetStartP());
    f32 endVal = pla->getPlaneFunc(lin->GetEndP());
    if (startVal * endVal > 0.0f) {
        *dst = lin->GetEnd();
        return false;
    } else {
        if (startVal >= 0.0f && endVal <= 0.0f) {
            if (a) {
                return cM3d_CrossInfLineVsInfPlane_proc(startVal, endVal, lin->GetStartP(), lin->GetEndP(), dst);
            }
        } else {
            if (b) {
                return cM3d_CrossInfLineVsInfPlane_proc(startVal, endVal, lin->GetStartP(), lin->GetEndP(), dst);
            }
        }
        *dst = lin->GetEnd();
        return false;
    }
}

/* 8024AE3C-8024BA18       .text cM3d_Cross_MinMaxBoxLine__FPC3VecPC3VecPC3VecPC3Vec */
bool cM3d_Cross_MinMaxBoxLine(const Vec*, const Vec*, const Vec*, const Vec*) {
    /* Nonmatching */
}

/* 8024BA18-8024BB50       .text cM3d_InclusionCheckPosIn3PosBox3d__FPC3VecPC3VecPC3VecPC3Vecf */
bool cM3d_InclusionCheckPosIn3PosBox3d(const Vec* pVecA, const Vec* pVecB, const Vec* pVecC, const Vec* pVecD, f32 pF) {
    f32 min, max;
    if (pVecA->x < pVecB->x) {
        min = pVecA->x;
        max = pVecB->x;
    } else {
        min = pVecB->x;
        max = pVecA->x;
    }
    if (min > pVecC->x) {
        min = pVecC->x;
    } else if (max < pVecC->x) {
        max = pVecC->x;
    }
    if (min - pF > pVecD->x || max + pF < pVecD->x) {
        return false;
    }

    if (pVecA->z < pVecB->z) {
        min = pVecA->z;
        max = pVecB->z;
    } else {
        min = pVecB->z;
        max = pVecA->z;
    }
    if (min > pVecC->z) {
        min = pVecC->z;
    } else if (max < pVecC->z) {
        max = pVecC->z;
    }
    if (min - pF > pVecD->z || max + pF < pVecD->z) {
        return false;
    }

    if (pVecA->y < pVecB->y) {
        min = pVecA->y;
        max = pVecB->y;
    } else {
        min = pVecB->y;
        max = pVecA->y;
    }
    if (min > pVecC->y) {
        min = pVecC->y;
    } else if (max < pVecC->y) {
        max = pVecC->y;
    }
    if (min - pF > pVecD->y || max + pF < pVecD->y) {
        return false;
    }
    return true;
}

/* 8024BB50-8024BD34       .text cM3d_CrossX_Tri__FPC8cM3dGTriPC3Vecf */
bool cM3d_CrossX_Tri(const cM3dGTri*, const Vec*, f32) {
    /* Nonmatching */
}

/* 8024BD34-8024BF1C       .text cM3d_CrossX_Tri__FPC8cM3dGTriPC3Vec */
bool cM3d_CrossX_Tri(const cM3dGTri*, const Vec*) {
    /* Nonmatching */
}

/* 8024BF1C-8024BFA0       .text cM3d_CrossX_Tri__FPC8cM3dGTriPC3VecPf */
void cM3d_CrossX_Tri(const cM3dGTri*, const Vec*, f32*) {
    /* Nonmatching */
}

/* 8024BFA0-8024C188       .text cM3d_CrossY_Tri__FPC8cM3dGTriPC3Vec */
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*) {
    /* Nonmatching */
}

/* 8024C188-8024C370       .text cM3d_CrossY_Tri__FRC3VecRC3VecRC3VecRC8cM3dGPlaPC3Vec */
bool cM3d_CrossY_Tri(const Vec&, const Vec&, const Vec&, const cM3dGPla&, const Vec*) {
    /* Nonmatching */
}

/* 8024C370-8024C4D0       .text cM3d_CrossY_Tri_Front__FRC3VecRC3VecRC3VecPC3Vec */
bool cM3d_CrossY_Tri_Front(const Vec&, const Vec&, const Vec&, const Vec*) {
    /* Nonmatching */
}

/* 8024C4D0-8024C554       .text cM3d_CrossY_Tri__FPC8cM3dGTriPC3VecPf */
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*, f32*) {
    /* Nonmatching */
}

/* 8024C554-8024C738       .text cM3d_CrossY_Tri__FPC8cM3dGTriPC3Vecf */
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*, f32) {
    /* Nonmatching */
}

/* 8024C738-8024C828       .text cM3d_CrossY_Tri__FPC8cM3dGTriPC3VecPC10cM3d_RangePf */
bool cM3d_CrossY_Tri(const cM3dGTri*, const Vec*, const cM3d_Range*, f32*) {
    /* Nonmatching */
}

/* 8024C828-8024CA0C       .text cM3d_CrossZ_Tri__FPC8cM3dGTriPC3Vecf */
bool cM3d_CrossZ_Tri(const cM3dGTri*, const Vec*, f32) {
    /* Nonmatching */
}

/* 8024CA0C-8024CBF4       .text cM3d_CrossZ_Tri__FPC8cM3dGTriPC3Vec */
bool cM3d_CrossZ_Tri(const cM3dGTri*, const Vec*) {
    /* Nonmatching */
}

/* 8024CBF4-8024CC78       .text cM3d_CrossZ_Tri__FPC8cM3dGTriPC3VecPf */
void cM3d_CrossZ_Tri(const cM3dGTri*, const Vec*, f32*) {
    /* Nonmatching */
}

/* 8024CC78-8024CD50       .text cM3d_Cross_LinTri__FPC8cM3dGLinPC8cM3dGTriP3Vecbb */
bool cM3d_Cross_LinTri(const cM3dGLin*, const cM3dGTri*, Vec*, bool, bool) {
    /* Nonmatching */
}

/* 8024CD50-8024CE0C       .text cM3d_Cross_LinTri_Easy__FPC8cM3dGTriPC3Vec */
bool cM3d_Cross_LinTri_Easy(const cM3dGTri*, const Vec*) {
    /* Nonmatching */
}

/* 8024CE0C-8024CE54       .text cM3d_Cross_SphPnt__FPC8cM3dGSphPC3Vec */
bool cM3d_Cross_SphPnt(const cM3dGSph*, const Vec*) {
    /* Nonmatching */
}

/* 8024CE54-8024D0BC       .text cM3d_Cross_LinSph__FPC8cM3dGLinPC8cM3dGSphP3Vec */
bool cM3d_Cross_LinSph(const cM3dGLin*, const cM3dGSph*, Vec*) {
    /* Nonmatching */
}

/* 8024D0BC-8024D378       .text cM3d_Cross_LinSph_CrossPos__FRC8cM3dGSphRC8cM3dGLinP3VecP3Vec */
int cM3d_Cross_LinSph_CrossPos(const cM3dGSph&, const cM3dGLin&, Vec*, Vec*) {
    /* Nonmatching */
}

/* 8024D378-8024DB34       .text cM3d_Cross_CylSph__FPC8cM3dGCylPC8cM3dGSphP3VecPf */
bool cM3d_Cross_CylSph(const cM3dGCyl*, const cM3dGSph*, Vec*, f32*) {
    /* Nonmatching */
}

/* 8024DB34-8024E1B4       .text cM3d_Cross_SphSph__FPC8cM3dGSphPC8cM3dGSphPfPf */
bool cM3d_Cross_SphSph(const cM3dGSph*, const cM3dGSph*, f32*, f32*) {
    /* Nonmatching */
}

/* 8024E1B4-8024E288       .text cM3d_Cross_SphSph__FPC8cM3dGSphPC8cM3dGSphP3Vec */
bool cM3d_Cross_SphSph(const cM3dGSph* sph_a, const cM3dGSph* sph_b, Vec* dst) {
    f32 centerDist;
    f32 overlapLen;
    if (cM3d_Cross_SphSph(sph_a, sph_b, &centerDist, &overlapLen)) {
        if (!cM3d_IsZero(centerDist)) {
            // could be an inlined function
            f32 tmpF = sph_b->GetR() / centerDist;
            Vec tmp;
            VECSubtract(&sph_a->GetC(), &sph_b->GetC(), &tmp);
            VECScale(&tmp, &tmp, tmpF);
            VECAdd(&tmp, &sph_b->GetC(), dst);
        } else {
            *dst = sph_a->GetC();
        }
        return true;
    } else {
        return false;
    }
}

/* 8024E288-8024E330       .text cM3d_CalcSphVsTriCrossPoint__FPC8cM3dGSphPC8cM3dGTriP3Vec */
void cM3d_CalcSphVsTriCrossPoint(const cM3dGSph* sph, const cM3dGTri* tri, Vec* dst) {
    Vec tmp2;
    Vec tmp;
    VECAdd(&tri->mA, &tri->mB, &tmp);
    VECScale(&tmp, &tmp2, 0.5f);
    f32 sqDist = VECSquareDistance(&tmp2, &sph->GetC());
    if (cM3d_IsZero(sqDist)) {
        *dst = sph->GetC();
    } else {
        cM3d_InDivPos2(&sph->GetC(), &tmp2, sph->GetR() / sqDist, dst);
    }
}

/* 8024E330-8024E694       .text cM3d_Cross_SphTri__FPC8cM3dGSphPC8cM3dGTriP3Vec */
bool cM3d_Cross_SphTri(const cM3dGSph*, const cM3dGTri*, Vec*) {
    /* Nonmatching */
}

/* 8024E694-8024EF80       .text cM3d_Cross_CylCyl__FPC8cM3dGCylPC8cM3dGCylPf */
bool cM3d_Cross_CylCyl(const cM3dGCyl*, const cM3dGCyl*, f32*) {
    /* Nonmatching */
}

/* 8024EF80-8024F11C       .text cM3d_Cross_CylCyl__FPC8cM3dGCylPC8cM3dGCylP3Vec */
bool cM3d_Cross_CylCyl(const cM3dGCyl*, const cM3dGCyl*, Vec*) {
    /* Nonmatching */
}

/* 8024F11C-8024F410       .text cM3d_Cross_CylTri__FPC8cM3dGCylPC8cM3dGTriP3Vec */
bool cM3d_Cross_CylTri(const cM3dGCyl*, const cM3dGTri*, Vec*) {
    /* Nonmatching */
}

/* 8024F410-8024FA90       .text cM3d_Cross_CylLin__FPC8cM3dGCylPC8cM3dGLinP3VecP3Vec */
int cM3d_Cross_CylLin(const cM3dGCyl*, const cM3dGLin*, Vec*, Vec*) {
    /* Nonmatching */
}

/* 8024FA90-8024FB04       .text cM3d_Cross_CylPntPnt__FPC8cM3dGCylPC3VecPC3VecP3VecP3Vec */
int cM3d_Cross_CylPntPnt(const cM3dGCyl* cyl, const Vec* a, const Vec* b, Vec* dst_a, Vec* dst_b) {
    cM3dGLin lin;
    lin.SetStartEnd(*a, *b);
    return cM3d_Cross_CylLin(cyl, &lin, dst_a, dst_b);
}

/* 8024FB04-8024FB68       .text cM3d_Cross_CylPnt__FPC8cM3dGCylPC3Vec */
bool cM3d_Cross_CylPnt(const cM3dGCyl* cyl, const Vec* pt) {
    /* Nonmatching */
    f32 dX = cyl->GetCP()->x - pt->x;
    f32 dZ = cyl->GetCP()->z - pt->z;
    f32 maxY = cyl->GetCP()->y + cyl->GetH();
    if (dX * dX + dZ * dZ < cyl->GetR() * cyl->GetR() && cyl->GetCP()->y < pt->y && maxY > pt->y) {
        return true;
    } else {
        return false;
    }
}

/* 8024FB68-8024FF10       .text cM3d_Cross_CpsCps__FRC8cM3dGCpsRC8cM3dGCpsP3Vec */
bool cM3d_Cross_CpsCps(const cM3dGCps&, const cM3dGCps&, Vec*) {
    /* Nonmatching */
}

/* 8024FF10-802506D4       .text cM3d_Cross_CpsCyl__FRC8cM3dGCpsRC8cM3dGCylP3Vec */
bool cM3d_Cross_CpsCyl(const cM3dGCps&, const cM3dGCyl&, Vec*) {
    /* Nonmatching */
}

/* 802506D4-80250840       .text cM3d_Cross_CpsSph_CrossPos__FRC8cM3dGCpsRC8cM3dGSphRC3VecP3Vec */
bool cM3d_Cross_CpsSph_CrossPos(const cM3dGCps&, const cM3dGSph&, const Vec&, Vec*) {
    /* Nonmatching */
}

/* 80250840-802509B0       .text cM3d_Cross_CpsSph__FRC8cM3dGCpsRC8cM3dGSphP3Vec */
bool cM3d_Cross_CpsSph(const cM3dGCps&, const cM3dGSph&, Vec*) {
    /* Nonmatching */
}

/* 802509B0-80250D70       .text cM3d_Cross_TriTri__FRC8cM3dGTriRC8cM3dGTriP3Vec */
bool cM3d_Cross_TriTri(const cM3dGTri&, const cM3dGTri&, Vec*) {
    /* Nonmatching */
}

/* 80250D70-80251280       .text cM3d_Cross_CpsTri__FRC8cM3dGCps8cM3dGTriP3Vec */
bool cM3d_Cross_CpsTri(const cM3dGCps&, cM3dGTri, Vec*) {
    /* Nonmatching */
}

/* 80251280-802514EC       .text cM3d_NearPos_Cps__FRC8cM3dGCpsRC3VecP3Vec */
void cM3d_NearPos_Cps(const cM3dGCps&, const Vec&, Vec*) {
    /* Nonmatching */
}

/* 802514EC-80251560       .text cM3d_CalcVecAngle__FRC3VecPsPs */
void cM3d_CalcVecAngle(const Vec& vec, s16* a, s16* b) {
    *a = -cM_atan2s(-vec.z * vec.y, 1.0f);
    *b = cM_atan2s(-vec.x * vec.y, 1.0f);
}

/* 80251560-80251634       .text cM3d_CalcVecZAngle__FRC3VecP5csXyz */
void cM3d_CalcVecZAngle(const Vec&, csXyz*) {
    /* Nonmatching */
}

/* 80251634-8025172C       .text cM3d_UpMtx_Base__FRC3VecRC3VecPA4_f */
void cM3d_UpMtx_Base(const Vec&, const Vec&, f32(*)[4]) {
    /* Nonmatching */
}

/* 8025172C-80251758       .text cM3d_PlaneCrossLineProcWork__FfffffffPfPf */
void cM3d_PlaneCrossLineProcWork(f32 v0, f32 v1, f32 v2, f32 v3, f32 v4, f32 v5, f32 v6, f32* p0, f32* p1) {
    *p0 = (v1 * v6 - v3 * v5) / v4;
    *p1 = (v2 * v5 - v0 * v6) / v4;
}

/* 80251758-802518F0       .text cM3d_2PlaneCrossLine__FRC8cM3dGPlaRC8cM3dGPlaP8cM3dGLin */
int cM3d_2PlaneCrossLine(const cM3dGPla& pPlaneA, const cM3dGPla& pPlaneB, cM3dGLin* pLinOut) {
    Vec tmp;
    VECCrossProduct(pPlaneA.GetNP(), pPlaneB.GetNP(), &tmp);
    if (cM3d_IsZero(tmp.x) && cM3d_IsZero(tmp.y) && cM3d_IsZero(tmp.z)) {
        return 0;
    } else {
        f32 absTX = fabsf(tmp.x);
        f32 absTY = fabsf(tmp.y);
        f32 absTZ = fabsf(tmp.z);
        if (absTX >= absTY && absTX >= absTZ) {
            cM3d_PlaneCrossLineProcWork(pPlaneA.GetNP()->y, pPlaneA.GetNP()->z, pPlaneB.GetNP()->y,
                                        pPlaneB.GetNP()->z, tmp.x, pPlaneA.GetD(), pPlaneB.GetD(),
                                        &pLinOut->GetStartP()->y, &pLinOut->GetStartP()->z);
            pLinOut->GetStartP()->x = 0.0f;
        } else if (absTY >= absTX && absTY >= absTZ) {
            cM3d_PlaneCrossLineProcWork(pPlaneA.GetNP()->z, pPlaneA.GetNP()->x, pPlaneB.GetNP()->z,
                                        pPlaneB.GetNP()->x, tmp.y, pPlaneA.GetD(), pPlaneB.GetD(),
                                        &pLinOut->GetStartP()->z, &pLinOut->GetStartP()->x);
            pLinOut->GetStartP()->y = 0.0f;
        } else {
            cM3d_PlaneCrossLineProcWork(pPlaneA.GetNP()->x, pPlaneA.GetNP()->y, pPlaneB.GetNP()->x,
                                        pPlaneB.GetNP()->y, tmp.z, pPlaneA.GetD(), pPlaneB.GetD(),
                                        &pLinOut->GetStartP()->x, &pLinOut->GetStartP()->y);
            pLinOut->GetStartP()->z = 0.0f;
        }
        f32 scale = VECMag(pLinOut->GetStartP());
        VECScale(&tmp, &tmp, scale);
        VECAdd(pLinOut->GetStartP(), &tmp, pLinOut->GetEndP());
        return 1;
    }
}

/* 802518F0-80251A10       .text cM3d_3PlaneCrossPos__FRC8cM3dGPlaRC8cM3dGPlaRC8cM3dGPlaP3Vec */
bool cM3d_3PlaneCrossPos(const cM3dGPla& p0, const cM3dGPla& p1, const cM3dGPla& p2, Vec* pDst) {
    cM3dGLin lin;
    if (!cM3d_2PlaneCrossLine(p0, p1, &lin))
        return false;

    Vec& start = lin.GetStart();
    Vec& end = lin.GetEnd();
    if (!cM3d_CrossInfLineVsInfPlane_proc(p2.getPlaneFunc(&start), p2.getPlaneFunc(&end), &start, &end, pDst))
        return false;

    return true;
}

/* 80251A10-80251AE4       .text cM3d_lineVsPosSuisenCross__FPC8cM3dGLinPC3VecP3Vec */
f32 cM3d_lineVsPosSuisenCross(const cM3dGLin* g_lin, const Vec* pt, Vec* dst) {
    Vec lin;

    g_lin->CalcVec(&lin);
    f32 len = VECSquareMag(&lin);
    if (cM3d_IsZero(len)) {
        *dst = *pt;
    }

    Vec p0_v;
    VECSubtract(pt, g_lin->GetStartP(), &p0_v);
    f32 dot = VECDotProduct(&p0_v, &lin);
    f32 v = dot / len;

    Vec ret;
    VECScale(&lin, &ret, v);
    VECAdd(&ret, g_lin->GetStartP(), dst);
    return v;
}

/* 80251AE4-80251BC0       .text cM3d_lineVsPosSuisenCross__FRC3VecRC3VecRC3VecP3Vec */
f32 cM3d_lineVsPosSuisenCross(const Vec& a, const Vec& b, const Vec& pt, Vec* dst) {
    Vec lin;
    VECSubtract(&b, &a, &lin);

    f32 len = VECSquareMag(&lin);
    if (cM3d_IsZero(len)) {
        *dst = pt;
        return 0.0f;
    }

    Vec p0_v;
    VECSubtract(&pt, &a, &p0_v);
    f32 dot = VECDotProduct(&p0_v, &lin);
    f32 v = dot / len;
    Vec ret;
    VECScale(&lin, &ret, v);
    VECAdd(&ret, &a, dst);
    return v;
}

/* 80251BC0-80251C44       .text cM3d_2PlaneLinePosNearPos__FRC8cM3dGPlaRC8cM3dGPlaPC3VecP3Vec */
int cM3d_2PlaneLinePosNearPos(const cM3dGPla& p0, const cM3dGPla& p1, const Vec* line, Vec* pDst) {
    cM3dGLin lin;
    if (cM3d_2PlaneCrossLine(p0, p1, &lin) == 0)
        return false;

    cM3d_lineVsPosSuisenCross(&lin, line, pDst);
    return true;
}

/* 80251C44-80251CC4       .text cM3d_CrawVec__FRC3VecRC3VecP3Vec */
void cM3d_CrawVec(const Vec& v0, const Vec& v1, Vec* pDst) {
    Vec tmp;
    f32 sq = fabsf(v1.x * v0.x + v1.y * v0.y + v1.z * v0.z);
    VECScale(&v0, &tmp, sq);
    VECAdd(&tmp, &v1, pDst);
}
