using System.Numerics;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace RayTracing04
{
    /**
     * 球体类
     */
    public class Sphere
    {
        // 球体中心
        public Vector3 Center
        {
            get;
        }

        // 球体半径
        public float Radius
        {
            get;
        }

        // 构造方法
        public Sphere(Vector3 center, float radius)
        {
            Center = center;
            Radius = radius;
        }

        // 判断某一条光线是否与球体相交
        public bool Hit(Ray ray)
        {
            
            Vector3 oc = ray.Origin - Center;
            float a = Vector3.Dot(ray.Direction, ray.Direction);
            float b = 2.0f * Vector3.Dot(oc, ray.Direction); 
            float c = Vector3.Dot(oc, oc) - Radius * Radius;
            float discriminant = b * b - 4.0f * a * c;
            return discriminant >= 0;

        }
    }
}
