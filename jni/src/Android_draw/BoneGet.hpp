#include "diRW/kernelRW.h"
#include "DataStruct.h"
class BoneGet
{

    struct FMatrix
    {
        float M[4][4];
    };

    struct FTransform
    {
        Vector4D Rotation;
        Vector3D Translation;
        float chunk;
        Vector3D Scale3D;
    };

public:
    mainRW *rw;

    void initRW(class mainRW *rw)
    {
        this->rw = rw;
    }

    FTransform getBone(uintptr_t addr)
    {
        FTransform transform;
        rw->readv(addr, &transform, 4 * 11);
        return transform;
    }

    Vector3D MarixToVector(FMatrix matrix)
    {
        return Vector3D{matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]};
    }

    FMatrix MatrixMulti(FMatrix m1, FMatrix m2)
    {
        FMatrix matrix = FMatrix();
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    matrix.M[i][j] += m1.M[i][k] * m2.M[k][j];
                }
            }
        }
        return matrix;
    }

    FMatrix TransformToMatrix(FTransform transform)
    {
        FMatrix matrix;
        matrix.M[3][0] = transform.Translation.X;
        matrix.M[3][1] = transform.Translation.Y;
        matrix.M[3][2] = transform.Translation.Z;
        float x2 = transform.Rotation.X + transform.Rotation.X;
        float y2 = transform.Rotation.Y + transform.Rotation.Y;
        float z2 = transform.Rotation.Z + transform.Rotation.Z;
        float xx2 = transform.Rotation.X * x2;
        float yy2 = transform.Rotation.Y * y2;
        float zz2 = transform.Rotation.Z * z2;
        matrix.M[0][0] = (1 - (yy2 + zz2)) * transform.Scale3D.X;
        matrix.M[1][1] = (1 - (xx2 + zz2)) * transform.Scale3D.Y;
        matrix.M[2][2] = (1 - (xx2 + yy2)) * transform.Scale3D.Z;
        float yz2 = transform.Rotation.Y * z2;
        float wx2 = transform.Rotation.W * x2;
        matrix.M[2][1] = (yz2 - wx2) * transform.Scale3D.Z;
        matrix.M[1][2] = (yz2 + wx2) * transform.Scale3D.Y;
        float xy2 = transform.Rotation.X * y2;
        float wz2 = transform.Rotation.W * z2;
        matrix.M[1][0] = (xy2 - wz2) * transform.Scale3D.Y;
        matrix.M[0][1] = (xy2 + wz2) * transform.Scale3D.X;
        float xz2 = transform.Rotation.X * z2;
        float wy2 = transform.Rotation.W * y2;
        matrix.M[2][0] = (xz2 + wy2) * transform.Scale3D.Z;
        matrix.M[0][2] = (xz2 - wy2) * transform.Scale3D.X;
        matrix.M[0][3] = 0;
        matrix.M[1][3] = 0;
        matrix.M[2][3] = 0;
        matrix.M[3][3] = 1;
        return matrix;
    }

    void 更新骨骼数据(uintptr_t HuManAddress, uintptr_t Bone, Vector3D 骨骼坐标[17])
    {
        // 计算骨节
        FTransform meshtrans = getBone(HuManAddress);
        FMatrix c2wMatrix = TransformToMatrix(meshtrans);
        // 头部
        FTransform headtrans = getBone(Bone + 5 * 48);
        FMatrix boneMatrix = TransformToMatrix(headtrans);
        骨骼坐标[0] = MarixToVector(MatrixMulti(boneMatrix, c2wMatrix));
        骨骼坐标[0].Z += 7; // 脖子长度
        FTransform chesttrans = getBone(Bone + 4 * 48);
        FMatrix boneMatrix1 = TransformToMatrix(chesttrans);
        骨骼坐标[1] = MarixToVector(MatrixMulti(boneMatrix1, c2wMatrix));
        // 盆骨
        FTransform pelvistrans = getBone(Bone + 1 * 48);
        FMatrix boneMatrix2 = TransformToMatrix(pelvistrans);
        骨骼坐标[2] = MarixToVector(MatrixMulti(boneMatrix2, c2wMatrix));
        // 左肩膀
        FTransform lshtrans = getBone(Bone + 11 * 48);
        FMatrix boneMatrix3 = TransformToMatrix(lshtrans);
        骨骼坐标[3] = MarixToVector(MatrixMulti(boneMatrix3, c2wMatrix));
        // 右肩膀
        FTransform rshtrans = getBone(Bone + 32 * 48);
        FMatrix boneMatrix4 = TransformToMatrix(rshtrans);
        骨骼坐标[4] = MarixToVector(MatrixMulti(boneMatrix4, c2wMatrix));
        // 左手肘
        FTransform lelbtrans = getBone(Bone + 12 * 48);
        FMatrix boneMatrix5 = TransformToMatrix(lelbtrans);
        骨骼坐标[5] = MarixToVector(MatrixMulti(boneMatrix5, c2wMatrix));
        // 右手肘
        FTransform relbtrans = getBone(Bone + 33 * 48);
        FMatrix boneMatrix6 = TransformToMatrix(relbtrans);
        骨骼坐标[6] = MarixToVector(MatrixMulti(boneMatrix6, c2wMatrix));
        // 左手腕
        FTransform lwtrans = getBone(Bone + 63 * 48);
        FMatrix boneMatrix7 = TransformToMatrix(lwtrans);
        骨骼坐标[7] = MarixToVector(MatrixMulti(boneMatrix7, c2wMatrix));
        // 右手腕
        FTransform rwtrans = getBone(Bone + 62 * 48);
        FMatrix boneMatrix8 = TransformToMatrix(rwtrans);
        骨骼坐标[8] = MarixToVector(MatrixMulti(boneMatrix8, c2wMatrix));
        // 左大腿
        FTransform Llshtrans = getBone(Bone + 52 * 48);
        FMatrix boneMatrix9 = TransformToMatrix(Llshtrans);
        骨骼坐标[9] = MarixToVector(MatrixMulti(boneMatrix9, c2wMatrix));
        // 右大腿
        FTransform Lrshtrans = getBone(Bone + 56 * 48);
        FMatrix boneMatrix10 = TransformToMatrix(Lrshtrans);
        骨骼坐标[10] = MarixToVector(MatrixMulti(boneMatrix10, c2wMatrix));
        // 左膝盖
        FTransform Llelbtrans = getBone(Bone + 53 * 48);
        FMatrix boneMatrix11 = TransformToMatrix(Llelbtrans);
        骨骼坐标[11] = MarixToVector(MatrixMulti(boneMatrix11, c2wMatrix));
        // 右膝盖
        FTransform Lrelbtrans = getBone(Bone + 57 * 48);
        FMatrix boneMatrix12 = TransformToMatrix(Lrelbtrans);
        骨骼坐标[12] = MarixToVector(MatrixMulti(boneMatrix12, c2wMatrix));
        // 左脚腕
        FTransform Llwtrans = getBone(Bone + 54 * 48);
        FMatrix boneMatrix13 = TransformToMatrix(Llwtrans);
        骨骼坐标[13] = MarixToVector(MatrixMulti(boneMatrix13, c2wMatrix));
        // 右脚腕
        FTransform Lrwtrans = getBone(Bone + 58 * 48);
        FMatrix boneMatrix14 = TransformToMatrix(Lrwtrans);
        骨骼坐标[14] = MarixToVector(MatrixMulti(boneMatrix14, c2wMatrix));
        // Max
        FTransform Maxs = getBone(Bone + 6 * 48);
        FMatrix boneMatrix15 = TransformToMatrix(Maxs);
        骨骼坐标[15] = MarixToVector(MatrixMulti(boneMatrix15, c2wMatrix));
        // Min
        FTransform Mins = getBone(Bone + 58 * 48);
        FMatrix boneMatrix16 = TransformToMatrix(Mins);
        骨骼坐标[16] = MarixToVector(MatrixMulti(boneMatrix16, c2wMatrix));
        if (骨骼坐标[13].Z < 骨骼坐标[14].Z)
        {
            骨骼坐标[14].Z = 骨骼坐标[13].Z;
        }
    }
};
