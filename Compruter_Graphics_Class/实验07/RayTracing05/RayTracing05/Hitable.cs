using System.Numerics;

namespace RayTracing05
{
    /**
     * 保存光线和场景中的物体交点信息类
     */
    public class HitRecord
    {
        // 光线和物体相交点的参数
        public float T { get; set; }

        // 光线和物体相交点的坐标
        public Vector3 P { get; set; }

        // 光线和物体相交点的法向量
        public Vector3 N { get; set; }

        public HitRecord(float t, Vector3 p, Vector3 n)
        {
            T = t;
            P = p;
            N = n;
        }

        /**
         * 返回一个空的对象
         */
        public static HitRecord Empty => new(0, Vector3.Zero, Vector3.Zero);
    }

    /**
     * 任何和光线有可能相交的类型都要实现这个接口
     */
    public interface IHitable
    {
        bool Hit(Ray ray, float tMin, float tMax, HitRecord rec);
    }
}
