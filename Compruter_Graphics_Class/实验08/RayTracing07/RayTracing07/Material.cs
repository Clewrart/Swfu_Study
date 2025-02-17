using System.Numerics;

namespace RayTracing07
{
    /**
     * 抽象材质类
     */
    public abstract class Material
    {
        public abstract bool Scatter(Ray ray,                   // 入射光线
                                     HitRecord rec,             // 交点记录
                                     out Vector3 attenuation,   // 衰减系数
                                     out Ray scattered);        // 散射光线
    }
}
