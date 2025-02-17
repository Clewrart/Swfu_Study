using System.Numerics;

namespace RayTracing07
{
    /**
     * 保存光线和场景中的物体相交信息类
     */
    public class HitRecord
    {
        // 光线和物体相交点的参数
        public float T { get; set; }

        // 光线和物体相交点的坐标
        public Vector3 P { get; set; }

        // 光线和物体相交点的法向量
        public Vector3 N { get; set; }

        // 光线和物体相交点的材质属性
        public Material M { get; set; }

        public HitRecord(float t, Vector3 p, Vector3 n, Material m)
        {
            T = t;
            P = p;
            N = n;
            M = m;
        }

        /**
         * 返回一个空的对象
         */
        public static HitRecord Empty => new HitRecord(0, Vector3.Zero, Vector3.Zero, null);
    }

    /**
     * 任何和光线有可能相交的类型都要实现这个接口
     */
    public interface IHitable
    {
        bool Hit(Ray ray, float tMin, float tMax, HitRecord rec);
    }
}
